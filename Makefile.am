# Makefile.am
bin_PROGRAMS = bigletters
bigletters_SOURCES = bigletters.c
bigletters_CFLAGS = @CFLAGS@

# Regular clean target for build artifacts
clean:
	rm -f *.o *.obj *.lo *.la bigletters a.out

# Distclean target for autoconf-generated files
distclean: clean
	rm -f Makefile config.h config.log config.status

# Maintainer-clean target to remove all autotools-generated files
maintainer-clean: distclean
	rm -f aclocal.m4 configure Makefile.in config.h.in autoscan.log
	rm -rf autom4te.cache .deps .libs
	rm -f install-sh depcomp missing stamp-h1
