dnl Process this file with autoconf to produce a configure script.
dnl Created by Anjuta application wizard.

AC_INIT(grib_contour, 0.25)

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

AC_CHECK_LIB(weathercalc, uv2velocity, HAVE_WEATHERCALC=true, HAVE_WEATHERCALC=false)
if test $HAVE_WEATHERCALC = "false"; then
  AC_MSG_FAILURE([weathercalc not found])
fi

AC_CHECK_LIB(KML, KML_new, HAVE_LIBKML=true, HAVE_LIBKML=false)
if test $HAVE_LIBKML = "false"; then
  AC_MSG_FAILURE([libKML not found])
fi

AC_CHECK_LIB(gdal, GDALAllRegister, HAVE_GDAL=true, HAVE_GDAL=false)
if test $HAVE_GDAL = "false"; then
  AC_MSG_FAILURE([gdal not found])
fi


AC_OUTPUT([
Makefile
etc/Makefile
images/Makefile
kml/Makefile
page/Makefile
screenshot/Makefile
scripts/Makefile
share/Makefile
src/Makefile

])
