/*
 * Copyright (C) 2015 Hewlett-Packard Development Company, L.P.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#if 0
#include <config.h>
#include "netdev.h"

#include <errno.h>
#include <inttypes.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "coverage.h"
#include "dpif.h"
#include "dynamic-string.h"
#include "fatal-signal.h"
#include "hash.h"
#include "list.h"
#include "netdev-dpdk.h"
#include "netdev-vport.h"
#include "ofpbuf.h"
#include "openflow/openflow.h"
#include "packets.h"
#include "plugins.h"
#include "poll-loop.h"
#include "seq.h"
#include "sset.h"
#include "svec.h"
#endif
#include "netdev-provider.h"
#include "ops-netdev-provider.h"
#include "smap.h"
#include "shash.h"
#include "openvswitch/vlog.h"

VLOG_DEFINE_THIS_MODULE(ops_netdev);

/* Contains alls netdevs, even those that are "netdev_remove"d, but are
 * still not unrefed and freed. Allows netdev_open to resurrect those netdevs
 * avoiding creation of duplicates */
static struct shash netdev_refd_shash OVS_GUARDED_BY(netdev_mutex)
    = SHASH_INITIALIZER(&netdev_refd_shash);

int
netdev_set_hw_intf_info(struct netdev *netdev, const struct smap *args)
    OVS_EXCLUDED(netdev_mutex)
{
    if (((struct ops_netdev_class *)netdev->netdev_class)->set_hw_intf_info) {
        const struct smap no_args = SMAP_INITIALIZER(&no_args);
        int error;

        error = ((struct ops_netdev_class *)netdev->netdev_class)->set_hw_intf_info(netdev,
                                                       args ? args : &no_args);
        if (error) {
            VLOG_WARN("%s: could not set hardware info (%s)",
                      netdev_get_name(netdev), ovs_strerror(error));
        }
        return error;
    } else if (args && !smap_is_empty(args)) {
        VLOG_WARN("%s: arguments provided to device that doesn't support hardware info",
                  netdev_get_name(netdev));
    }
    return 0;
}

int
netdev_set_hw_intf_config(struct netdev *netdev, const struct smap *args)
    OVS_EXCLUDED(netdev_mutex)
{
    if (((struct ops_netdev_class *)netdev->netdev_class)->set_hw_intf_config) {
        const struct smap no_args = SMAP_INITIALIZER(&no_args);
        int error;

        error = ((struct ops_netdev_class *)netdev->netdev_class)->set_hw_intf_config(netdev,
                                                         args ? args : &no_args);
        if (error) {
            VLOG_WARN("%s: could not set hardware config (%s)",
                      netdev_get_name(netdev), ovs_strerror(error));
        }
        return error;
    } else if (args && !smap_is_empty(args)) {
        VLOG_WARN("%s: arguments provided to device that doesn't support hardware config",
                  netdev_get_name(netdev));
    }
    return 0;
}
