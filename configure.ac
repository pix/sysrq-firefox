#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
AC_PREREQ([2.64])

AC_INIT([sysrq-firefox],
        [m4_esyscmd_s([./get-version])],
        [camille@moncelier.fr])
AC_CONFIG_SRCDIR([src/sysrq-firefox.c])
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_HEADER([config.h])
AC_CONFIG_FILES([Makefile src/Makefile])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign -Wall -Werror tar-ustar])
AM_MAINTAINER_MODE
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES(yes)])
m4_pattern_allow([AM_PROG_AR])
AM_PROG_AR

# Configure libtool
LT_INIT

# Checks for programs.
AC_PROG_CC
AC_PROG_CC_C99
AC_PROG_CXX
AM_PROG_CC_C_O
AC_PROG_LIBTOOL
AC_PROG_LN_S
AC_PROG_EGREP

# Configure kernel module
AC_PATH_KERNEL_SOURCE

DEFAULT_MODULEDIR=/lib/modules/`uname -r`/misc

AC_ARG_WITH(KERNELDIR,
            [--kernel-dir=DIR path to configured kernel directory (/lib/modules/`uname -r`)],
            KERNELDIR=${withval},
            KERNELDIR=${DEFAULT_KERNELDIR})
AC_ARG_WITH(KERNELSRCS,
            [--kernel-sources=DIR path to full kernel sources (/lib/modules/`uname -r`)],
            KERNELSRCS=${withval},
            KERNELSRCS=${DEFAULT_KERNELSRCS})
AC_ARG_WITH(KERNELVER,
            [--kernel-version=VER specifiy the kernel version (`uname -r`],
            KERNELVER=${withval},
            KERNELVER=${DEFAULT_KERNELVER})
AC_ARG_WITH(MODULEDIR,
            [--with-moduledir=DIR kernel modules in DIR (/lib/modules/`uname -r`/misc)],
            MODULEDIR=${withval},
            MODULEDIR=${DEFAULT_MODULEDIR})

# Check some compiler flags
AX_CFLAGS_GCC_OPTION([-fdiagnostics-show-option])
AX_CFLAGS_GCC_OPTION([-pipe])
AX_CFLAGS_GCC_OPTION([-Wall])
AX_CFLAGS_GCC_OPTION([-W])
AX_CFLAGS_GCC_OPTION([-Wextra])
AX_CFLAGS_GCC_OPTION([-Wformat])
AX_CFLAGS_GCC_OPTION([-Wformat-security])
AX_CFLAGS_GCC_OPTION([-Wfatal-errors])
AX_CFLAGS_GCC_OPTION([-Wcast-align])
AX_CFLAGS_GCC_OPTION([-Winline])
AX_CFLAGS_GCC_OPTION([-fstack-protector])
AX_CFLAGS_GCC_OPTION([-D_FORTIFY_SOURCE=2])
AX_CFLAGS_GCC_OPTION([-Wno-unused-parameter])
AX_CFLAGS_GCC_OPTION([-Wno-missing-field-initializers])
AX_LDFLAGS_OPTION([-Wl,-z,relro])
AX_LDFLAGS_OPTION([-Wl,-z,now])

AX_CFLAGS_GCC_OPTION([-D_GNU_SOURCE])    # GNU systems (asprintf, ...)
case $host_os in
   solaris*)
     AX_CFLAGS_GCC_OPTION([-D__EXTENSIONS__]) # (CMSG_*)
     AX_CFLAGS_GCC_OPTION([-D_XPG4_2])        # (CMSG_*)
     ;;
   hpux*)
     AX_CFLAGS_GCC_OPTION([-D_XOPEN_SOURCE=500])      # HP-UX
     AX_CFLAGS_GCC_OPTION([-D_XOPEN_SOURCE_EXTENDED]) # HP-UX
     ;;
esac

AC_CACHE_SAVE

## XXX: Add the dependencies of your project here.

AC_CACHE_SAVE

## XXX: Add compile-time options here. They are
## XXX: usually overridable using the command-line.

AC_OUTPUT

cat <<EOF

------------------ Summary ------------------
 $PACKAGE_NAME version $PACKAGE_VERSION
  Prefix.............: $prefix
  C Compiler.........: $CC $CFLAGS $CPPFLAGS
  Linker.............: $LD $LDFLAGS $LIBS
  Linux Kernel dir...: $MODULEDIR
---------------------------------------------

Check the above options and compile with:
 ${MAKE-make}

EOF
