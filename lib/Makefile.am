AUTOMAKE_OPTIONS = foreign subdir-objects
AM_CPPFLAGS = $(LTDLINCL)
lib_LTLIBRARIES = libopsopenvswitch.la
libopsopenvswitch_la_LDFLAGS = $(AM_LDFLAGS)
libopsopenvswitch_la_CPPFLAGS = $(AM_CPPFLAGS)
libopsopenvswitch_la_CFLAGS = $(AM_CFLAGS) \
        -I $(top_builddir)/sandbox/ovs/lib \
        -I $(top_builddir)/sandbox/ovs/include
libopsopenvswitch_la_SOURCES = \
	ops-netdev.h \
	ops-netdev.c \
	ops-netdev-provider.h
