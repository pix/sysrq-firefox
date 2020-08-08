EXTRA_DIST = Makefile.kernel Makefile.common
EXTRA_PROGRAMS = automake_dummy
dist_man_MANS = sysrq-firefox.4

## TODO: When you want to add more files, add them below.
## TODO: Automake will find dependencies by itself. Run
## TODO: ./autogen.sh after modifying this file.

automake_dummy_SOURCES = sysrq-firefox.c
sysrq_firefox_DATA = sysrq-firefox.o

include ./Makefile.common

## TODO: Each time you have used `PKG_CHECK_MODULES` macro
## TODO: in `configure.ac`, you get two variables that
## TODO: you can substitute like above.
