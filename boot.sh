#!/bin/bash

set -o xtrace

OPS_USER=$USER
TOP_DIR=$PWD
SANDBOX=$TOP_DIR/sandbox
PATCH_DIR=$TOP_DIR/patches
mkdir -p $SANDBOX

declare -A GITREPO
declare -A GITBRANCH
declare -A GITDIR

OPS_REPOS=${OPS_REPOS:-""}

function trueorfalse {
    local xtrace
    xtrace=$(set +o | grep xtrace)
    set +o xtrace

    local default=$1

    if [ -z $2 ]; then
        die $LINENO "variable to normalize required"
    fi
    local testval=${!2:-}

    case "$testval" in
        "1" | [yY]es | "YES" | [tT]rue | "TRUE" ) echo "True" ;;
        "0" | [nN]o | "NO" | [fF]alse | "FALSE" ) echo "False" ;;
        * )                                       echo "$default" ;;
    esac

    $xtrace
}

function enable_repo {
    local name=$1
    local url=$2
    local branch=${3:-master}
    OPS_REPOS+=",$name"
    GITREPO[$name]=$url
    GITDIR[$name]=$SANDBOX/$name
    GITBRANCH[$name]=$branch
}

function git_timed {
    local count=0
    local timeout=0

    if [[ -n "${GIT_TIMEOUT}" ]]; then
        timeout=${GIT_TIMEOUT}
    fi

    until timeout -s SIGINT ${timeout} git "$@"; do
        if [[ $? -ne 124 ]]; then
            die $LINENO "git call failed: [git $@]"
        fi

        count=$(($count + 1))
        warn $LINENO "timeout ${count} for git call: [git $@]"
        if [ $count -eq 3 ]; then
            die $LINENO "Maximum of 3 git retries reached"
        fi
        sleep 5
    done
}

function git_clone {
    local git_remote=$1
    local git_dest=$2
    local git_ref=$3
    local orig_dir
    orig_dir=$(pwd)
    local git_clone_flags=""

    RECLONE=$(trueorfalse False RECLONE)
    if [[ "${GIT_DEPTH}" -gt 0 ]]; then
        git_clone_flags="$git_clone_flags --depth $GIT_DEPTH"
    fi

    if [[ "$OFFLINE" = "True" ]]; then
        echo "Running in offline mode, clones already exist"
        cd $git_dest
        git show --oneline | head -1
        cd $orig_dir
        return
    fi

    if echo $git_ref | egrep -q "^refs"; then
        if [[ ! -d $git_dest ]]; then
            if [[ "$ERROR_ON_CLONE" = "True" ]]; then
                echo "The $git_dest project was not found; if this is a gate job, add"
                echo "the project to the \$PROJECTS variable in the job definition."
                die $LINENO "Cloning not allowed in this configuration"
            fi
            git_timed clone $git_clone_flags $git_remote $git_dest
        fi
        cd $git_dest
        git_timed fetch $git_remote $git_ref && git checkout FETCH_HEAD
    else
        if [[ ! -d $git_dest ]]; then
            if [[ "$ERROR_ON_CLONE" = "True" ]]; then
                echo "The $git_dest project was not found; if this is a gate job, add"
                echo "the project to the \$PROJECTS variable in the job definition."
                die $LINENO "Cloning not allowed in this configuration"
            fi
            git_timed clone $git_clone_flags $git_remote $git_dest
            cd $git_dest
            git checkout $git_ref
        elif [[ "$RECLONE" = "True" ]]; then
            cd $git_dest
            git remote set-url origin $git_remote
            git_timed fetch origin
            find $git_dest -name '*.pyc' -delete

            # handle git_ref accordingly to type (tag, branch)
            if [[ -n "`git show-ref refs/tags/$git_ref`" ]]; then
                git_update_tag $git_ref
            elif [[ -n "`git show-ref refs/heads/$git_ref`" ]]; then
                git_update_branch $git_ref
            elif [[ -n "`git show-ref refs/remotes/origin/$git_ref`" ]]; then
                git_update_remote_branch $git_ref
            else
                die $LINENO "$git_ref is neither branch nor tag"
            fi

        fi
    fi

    cd $git_dest
    git show --oneline | head -1
    cd $orig_dir
}

function git_clone_by_name {
    local name=$1
    local repo=${GITREPO[$name]}
    local dir=${GITDIR[$name]}
    local branch=${GITBRANCH[$name]}
    git_clone $repo $dir $branch
}

function fetch_repos {
    local repos="${OPS_REPOS}"
    local repo

    if [[ -z $repos ]]; then
        return
    fi

    echo "Fetching repos"
    for repo in ${repos//,/ }; do
        git_clone_by_name $repo
    done
}

enable_repo ovs https://github.com/openvswitch/ovs.git
enable_repo ops https://git.openswitch.net/openswitch/ops

fetch_repos

python $SANDBOX/ops/schema/sanitize.py $SANDBOX/ops/schema/vswitch.extschema $SANDBOX/ovs/vswitchd/vswitch.ovsschema
(cd $SANDBOX/ovs && patch -p1 < $PATCH_DIR/ovs_01.patch)
(cd $SANDBOX/ovs && ./boot.sh)
(cd $SANDBOX/ovs && ./configure --disable-static --enable-shared)
make -C $SANDBOX/ovs ofproto/ipfix-entities.def \
        include/odp-netlink.h \
        lib/vswitch-idl.c lib/vswitch-idl.h \
        lib/vswitch-idl.ovsidl \
        lib/libopenvswitch.la \
        lib/libsflow.la \
        ofproto/libofproto.la

autoreconf --install --force
