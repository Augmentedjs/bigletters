bin_PROGRAMS = bigletters
bigletters_SOURCES = \
	bigletters.c \
	color.c \
	font_pack.c \
	font_ega.c \
	font_phoenix.c \
	font_cga_thin.c \
	bigletters.h

bigletters_CFLAGS = @CFLAGS@

AM_CPPFLAGS = -I$(srcdir)

check_PROGRAMS = font-pack-test
font_pack_test_SOURCES = \
	tests/test_font_packs.c \
	color.c \
	font_pack.c \
	font_ega.c \
	font_phoenix.c \
	font_cga_thin.c \
	bigletters.h
TESTS = font-pack-test tests/test_cli.sh

EXTRA_DIST = \
	FONTS.md \
	FONT-LICENSE.md \
	tests/test_cli.sh \
	tools/generate_font_pack.py

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

all: $(bin_PROGRAMS)
