
# A list of all the files in the current directory which can be regenerated
MAINTAINERCLEANFILES = Makefile.in

bin_PROGRAMS = famppgtk

INCLUDES =                                              \
	-I. 						\
	-I$(srcdir) -I$(top_srcdir) -I$(top_srcdir)/src	\
	-I$(top_builddir)				\
        -I$(includedir)                                 \
	@GTK_CFLAGS@                                    \
	@CFLAGS@

famppgtk_SOURCES = famppgtk.cpp
famppgtk_LDADD = $(top_builddir)/src/libfampp.la -lpopt -lfam
famppgtk_LDFLAGS = $(GTK_LIBS)

