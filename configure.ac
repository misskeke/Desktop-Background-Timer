#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([Desktop-Backgrand-Timer], [0.1], [micromaomao@gmail.com])
# AM_INIT_AUTOMAKE
AM_INIT_AUTOMAKE()
# AC_CONFIG_SRCDIR(["src/main.c"])
AC_CONFIG_SRCDIR([src])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX

# Checks for libraries.

AC_SEARCH_LIBS([main],[config++],[],[exit -1])
AC_SEARCH_LIBS([main],[cairo2],[],[exit -1])

# Checks for header files.
AC_CHECK_HEADERS([libconfig.h],[],[exit -1])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
