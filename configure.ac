
# require autoconf 2.13
AC_PREREQ(2.13)

AC_INIT(src/Fampp2.hh)

PACKAGE=fampp2
FAMPPTWO_MAJOR=9
FAMPPTWO_MINOR=0
FAMPPTWO_BETA=0
FAMPP_VERSION=$FAMPPTWO_MAJOR.$FAMPPTWO_MINOR.$FAMPPTWO_BETA
FAMPPTWO_FULLV=$FAMPP_VERSION
LT_RELEASE=$FAMPPTWO_MAJOR.$FAMPPTWO_MINOR
VERSION=$FAMPP_VERSION

AC_SUBST(FAMPPTWO_MAJOR)
AC_SUBST(FAMPPTWO_MINOR)
AC_SUBST(FAMPPTWO_BETA)
AC_SUBST(FAMPPTWO_FULLV)
AC_SUBST(FAMPP_VERSION)
AC_SUBST(LT_RELEASE)

AM_CONFIG_HEADER(config.h)
AM_INIT_AUTOMAKE($PACKAGE, $VERSION)
AM_MAINTAINER_MODE

AC_CANONICAL_HOST
AC_ISC_POSIX

AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXX

AC_STDC_HEADERS
AC_DISABLE_FAST_INSTALL
AC_DISABLE_STATIC
AM_PROG_LIBTOOL

LIBFERRIS_PLATFORM_SPECIFICS


###############################################################################
###############################################################################
###############################################################################
###############################################################################

AC_CHECK_LIB(fam, FAMOpen)

AM_FERRIS_BOOST_NEEDED
AM_PATH_GLIB_2_0( 2.0.0 )

#AM_PATH_GTK_2_0( 2.0.0 )
AM_CONDITIONAL(HAVE_GTK, test x$enable_gtk_example = xyes)



###############################################################################
###############################################################################


CFLAGS="   $CFLAGS -O0 -g  "
CXXFLAGS=" $CXXFLAGS -O0 -g  "
LDFLAGS="  $LDFLAGS "
AC_SUBST(CFLAGS)
AC_SUBST(CPPFLAGS)
AC_SUBST(LDFLAGS)
AC_SUBST(CXXFLAGS)
AC_SUBST(CXXCPPFLAGS)

REQUIREMENTS=" ferrisstreams "
AC_SUBST(REQUIREMENTS)


#
# All done.
#
AC_OUTPUT([
Makefile
src/Makefile
examples/Makefile
examples/gtk/Makefile
examples/console_test/Makefile
fampp2-config
fampp.spec
fampp2.pc
],
[
chmod +x fampp2-config
])

