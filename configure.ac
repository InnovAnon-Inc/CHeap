AC_INIT([libcheap], [1.0], [InnovAnon-Inc@protonmail.com])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
AM_PROG_AR
LT_INIT([])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
 src/Makefile
 src/libcheap.pc
 src/cheap-test.pc
])

PKG_PROG_PKG_CONFIG

AC_ARG_ENABLE([use-submodules],
    AS_HELP_STRING([--enable-use-submodules], [Enable use submodules]))
AM_CONDITIONAL([USE_SUBMODULES], [test x"$enable_use_submodules" = "xyes"])

AC_CONFIG_MACRO_DIR([m4])

AC_CHECK_HEADERS([stdlib.h sys/types.h])
#AC_CHECK_HEADERS([math.h])
#AC_CHECK_HEADERS([glitter.h array.h mmalloc.h])

#AC_CHECK_LIB([stdlib],[])
#AC_CHECK_LIB([array],[init_array,alloc_array,free_array,get_array,set_array])
#AC_CHECK_LIB([mmalloc],[mmalloc,mfree])
#AC_CHECK_LIB([math],[fabs])

PKG_CHECK_MODULES([GLITTER],[glitter],,)
PKG_CHECK_MODULES([ARRAY],[libarray],,)
PKG_CHECK_MODULES([MMALLOC],[libmmalloc],,)
PKG_CHECK_MODULES([SIMON],[libsimon],,)

INNOVANON_WARNINGS([])

AC_OUTPUT

