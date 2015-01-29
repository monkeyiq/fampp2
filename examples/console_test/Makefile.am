
# A list of all the files in the current directory which can be regenerated
MAINTAINERCLEANFILES = Makefile.in

bin_PROGRAMS = famppct

INCLUDES =                                              \
	-I. 						\
	-I$(srcdir) -I$(top_srcdir) -I$(top_srcdir)/src	\
	-I$(top_builddir)				\
        -I$(includedir)                                 \
	@GLIB_CFLAGS@                                   \
	@CFLAGS@

famppct_SOURCES = famppct.cpp
famppct_LDADD = $(top_builddir)/src/libfampp.la -lpopt -lfam
famppct_LDFLAGS = @SIGC_LIBS@ @GLIB_LIBS@

