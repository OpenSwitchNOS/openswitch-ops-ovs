AUTOMAKE_OPTIONS = foreign subdir-objects
lib_LTLIBRARIES = libopsofproto.la
libopsofproto_la_LDFLAGS = $(AM_LDFLAGS)
libopsofproto_la_SOURCES = \
        ops-ofproto-provider.h \
	ops-ofproto.h \
	ops-ofproto.c \
	ops-bond.h
libopsofproto_la_CPPFLAGS = $(AM_CPPFLAGS)
libopsofproto_la_CFLAGS = $(AM_CFLAGS) \
        -I $(top_builddir)/lib \
        -I $(top_builddir)/sandbox/ovs/lib \
        -I $(top_builddir)/sandbox/ovs/include \
        -I $(top_builddir)/sandbox/ovs
