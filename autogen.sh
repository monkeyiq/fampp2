#! /bin/sh

aclocal -I macros \
&& automake --gnu --add-missing \
&& autoconf

