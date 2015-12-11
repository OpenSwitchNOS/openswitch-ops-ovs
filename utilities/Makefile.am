AUTOMAKE_OPTIONS = foreign subdir-objects
sbin_PROGRAMS = ovs-appctl ovs-vsctl
ovs_appctl_SOURCES = ovs-appctl.c
ovs_appctl_LDADD = \
        $(LIBLTDL) $(LIBADD_DL) \
        $(top_builddir)/sandbox/ovs/lib/libopenvswitch.la
ovs_vsctl_SOURCES = ovs-vsctl.c
ovs_vsctl_LDADD = \
        $(LIBLTDL) $(LIBADD_DL) \
        $(top_builddir)/sandbox/ovs/ofproto/libofproto.la \
        $(top_builddir)/sandbox/ovs/lib/libopenvswitch.la
ovs_appctl_CPPFLAGS =  $(AM_CPPFLAGS) -DOPS -DOPS_TEMP
ovs_vsctl_CPPFLAGS =  $(AM_CPPFLAGS) -DOPS -DOPS_TEMP
ovs_appctl_CFLAGS = \
        -I $(top_builddir)/lib \
        -I $(top_builddir)/sandbox/ovs \
        -I $(top_builddir)/sandbox/ovs/lib \
        -I $(top_builddir)/sandbox/ovs/include
ovs_vsctl_CFLAGS = \
        -I $(top_builddir)/lib \
        -I $(top_builddir)/sandbox/ovs \
        -I $(top_builddir)/sandbox/ovs/lib \
        -I $(top_builddir)/sandbox/ovs/include
ovs_appctl_LDFLAGS = $(AM_LDFLAGS) -static
ovs_vsctl_LDFLAGS = $(AM_LDFLAGS) -static
