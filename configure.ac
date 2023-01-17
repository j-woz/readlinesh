#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([readlinesh], [1.0], [woz@anl.gov])
AC_CONFIG_SRCDIR([src/readlinesh.h])

m4_include([m4/ax_lib_readline.m4])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.
AX_LIB_READLINE()
if [[ ${ax_cv_lib_readline} == "no" ]] || \
   [[ ${ax_cv_lib_readline_history}  == "no" ]]
then
    AC_MSG_ERROR([You must have the readline and history development packages!])
fi

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL

# Checks for library functions.
AC_CHECK_FUNCS([strdup])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
