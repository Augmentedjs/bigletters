# Define the program and its source files
bin_PROGRAMS = bigletters
bigletters_SOURCES = bigletters.c font_normal.c font_bold.c bigletters.h

# Use CFLAGS from the configure script
bigletters_CFLAGS = @CFLAGS@

# Clean up build artifacts
clean-local:
	rm -f *.o *.obj *.lo *.la bigletters a.out

# Clean up autoconf-generated files
distclean-local: clean-local
	rm -f Makefile config.h config.log config.status

# Clean up all automake and autoconf artifacts
maintainer-clean-local: distclean-local
	rm -f aclocal.m4 configure Makefile.in config.h.in autoscan.log
	rm -rf autom4te.cache .deps .libs
	rm -f install-sh depcomp missing stamp-h1

# Define the default build targets
all: $(bin_PROGRAMS)
