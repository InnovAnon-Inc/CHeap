AC_INIT([libcheap], [0.0], [laurence.a.maddox@gmail.com])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AM_PROG_AR
LT_INIT([])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
 src/Makefile
])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SUBDIRS([glitter Array])

AC_CHECK_HEADERS([stdlib.h sys/types.h])
#AC_CHECK_HEADERS([math.h])
AC_CHECK_HEADERS([glitter.h array.h])

#AC_CHECK_LIB([stdlib],[])
AC_CHECK_LIB([array],[init_array,alloc_array,free_array,get_array,set_array])
#AC_CHECK_LIB([math],[fabs])

INNOVANON_WARNINGS([])

AC_OUTPUT
