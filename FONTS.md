# BigLetters font packs

Font packs keep glyph data separate from rendering and effects. They are
compiled into the executable, so rendering has no runtime file parsing or
allocation.

## Contract

Each glyph is exactly `MAX_WIDTH` visible columns by `MAX_HEIGHT` rows. In the
current format that is six by six. Rows may contain spaces and Unicode block or
half-block characters, but each code point must occupy one terminal column.

A pack provides:

- 26 uppercase glyphs in `A-Z` order
- 26 lowercase glyphs in `a-z` order
- 10 number glyphs in `0-9` order
- 33 symbols in the printable-ASCII order used by `font_symbols.c`
- one replacement glyph for unsupported input bytes

The 33-symbol order is the four contiguous ASCII ranges `0x20-0x2f`,
`0x3a-0x40`, `0x5b-0x60`, and `0x7b-0x7e`.

## Adding a pack

Create a source file such as `font_outline.c`. Keep the glyph tables private and
export one pack descriptor:

```c
#include "bigletters.h"

static const BiglettersGlyph uppercase_outline[26] = {
    /* A through Z */
};

static const BiglettersGlyph lowercase_outline[26] = {
    /* a through z */
};

static const BiglettersGlyph numbers_outline[10] = {
    /* 0 through 9 */
};

const BiglettersFontPack bigletters_font_outline = {
    "outline",
    "Outlined block font",
    uppercase_outline,
    lowercase_outline,
    numbers_outline,
    bigletters_ascii_symbols,
    &bigletters_replacement_glyph
};
```

Then:

1. Declare the exported descriptor in `bigletters.h`.
2. Add its address to `font_packs` in `font_pack.c`.
3. Add the source file to `bigletters_SOURCES` and
   `font_pack_test_SOURCES` in `Makefile.am`.
4. Run `./build.sh && make check`.

Use a private 33-entry symbol table instead of `bigletters_ascii_symbols` when
the pack needs symbols with a distinct visual style. The font-pack test checks
every printable character and rejects rows that are not exactly six code points
wide.
