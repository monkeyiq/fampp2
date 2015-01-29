
MAINTAINERCLEANFILES = Makefile.in
#EXTRA_DIST = 


INCLUDES =                                              \
	@STLPORT_CFLAGS@                                \
	-I. 						\
	-I$(srcdir) -I$(top_srcdir) 			\
	-I$(top_builddir)				\
        -I$(includedir)                                 \
	-I/usr/local/include                            \
	@GLIB_CFLAGS@                                   \
	@CFLAGS@


lib_LTLIBRARIES      = libfampp.la

include_HEADERS = \
	Fampp2.hh               \
	FamppEvents.hh          \
	FamppExceptions.hh	\
	Fampp2GlibSupport.hh    \
	Fampp2Handle.hh		

libfampp_la_SOURCES =           \
	Fampp2.cpp              \
	Fampp2_private.hh       \
	FamppEvents.cpp         \
	Fampp2.hh               \
	FamppEvents.hh          \
	FamppExceptions.hh      \
	Fampp2GlibSupport.cpp Fampp2GlibSupport.hh \
	Fampp2Handle.hh         


#libfampp_la_LIBADD = -lfam #-Wl,-Bstatic -lstlport_gcc  -Wl,-Bdynamic
libfampp_la_LIBADD = -lfam @STLPORT_LIBS@
libfampp_la_LDFLAGS = $(GLIB_LIBS)  -version-info 2:0:0



##########################################################################
##########################################################################
##########################################################################

