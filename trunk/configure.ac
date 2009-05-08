dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(grib_contour, 0.33)

AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AM_CONFIG_HEADER(config.h)
AM_MAINTAINER_MODE

AC_ISC_POSIX
AC_PROG_CC

AM_PROG_CC_STDC
AC_HEADER_STDC

AC_ARG_WITH(www,
  [AS_HELP_STRING([--with-www=someurl],
    [base url to use in kml output])],
  if test -n "$withval"
  then
    WWW="$withval"
    AC_SUBST(WWW)
  else
		[AC_MSG_FAILURE([--with-www=someurl MUST be specified])]
	fi,
  [AC_MSG_FAILURE([--with-www=someurl MUST be specified])]
)

AC_ARG_WITH(wwwdisk,
  [AS_HELP_STRING([--with-wwwdisk=/some/path],
    [base dir to output kml and images])],
  if test -n "$withval"
  then
    WWWDISK="$withval"
    AC_SUBST(WWWDISK)
  else
		[AC_MSG_FAILURE([--with-wwwdisk=/some/path MUST be specified])]
	fi,
  [AC_MSG_FAILURE([--with-wwwdisk=/some/path MUST be specified])]
)

AC_CHECK_PROG(HAVE_BASH, bash, true, false)
if test $HAVE_BASH = "false"; then
  AC_MSG_FAILURE([bash not found])
fi

AC_CHECK_PROG(HAVE_DEGRIB, degrib, true, false)
if test $HAVE_DEGRIB = "false"; then
  AC_MSG_FAILURE([degrib not found])
fi

PKG_CHECK_MODULES(DEPS, libogr2kml >= 0.4 weathercalc >= 0.5)
AC_SUBST(DEPS_CFLAGS)
AC_SUBST(DEPS_LIBS)



AC_ARG_WITH(gdal-config,
[  --with-gdal-config=GDAL_CONFIG    use gdal-config specified ],
[
  GDAL_CONFIG=$withval;
  echo "using "$GDAL_CONFIG" for gdal-config";
],[
  PROG="gdal-config";
  AC_PATH_PROG(GDAL_CONFIG, $PROG, "", $PATH)
])

if test "x$GDAL_CONFIG" != "x"; then
  GDAL_CFLAGS=`$GDAL_CONFIG --cflags`
  GDAL_LIBS=`$GDAL_CONFIG --libs`
  AC_SUBST(GDAL_CFLAGS)
  AC_SUBST(GDAL_LIBS)
  found_gdal="yes"
else
  found_gdal="no"
fi
AM_CONDITIONAL(HAVE_GDAL, test "x$GDAL_CONFIG" != "x")


AC_OUTPUT([
Makefile
cgi/Makefile
etc/Makefile
images/Makefile
kml/Makefile
page/Makefile
screenshot/Makefile
scripts/Makefile
share/Makefile
src/Makefile

])
