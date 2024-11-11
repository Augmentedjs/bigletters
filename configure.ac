# configure.ac
AC_INIT([bigletters], [1.0], [jedi.master@augmentedjs.com])
AC_PREREQ([2.69])
AM_INIT_AUTOMAKE([foreign]) # Adds support for automake
AC_CONFIG_SRCDIR([bigletters.c])
AC_CONFIG_HEADERS([config.h])

# Check for the C compiler
AC_PROG_CC

# Enable default optimization options
AC_ARG_ENABLE([optimize],
    [AS_HELP_STRING([--enable-optimize], [Enable optimization (default is on)])],
    [case "${enableval}" in
        yes) CFLAGS="$CFLAGS -O2" ;;
        no) CFLAGS="$CFLAGS -O0" ;;
        *) AC_MSG_ERROR([bad value ${enableval} for --enable-optimize]) ;;
    esac],
    [CFLAGS="$CFLAGS -O2"])

# Output the Makefile
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
