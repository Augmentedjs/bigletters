# BigLetters 8×8 font packs

Font packs store native 8×8 bitmap cells. They are compiled into the executable,
so rendering needs no runtime font library, file parsing, or allocation.

## Bitmap contract

`BiglettersGlyph` contains eight bytes. Each byte is one pixel row and its most
significant bit is the leftmost pixel:

```c
typedef struct BiglettersGlyph {
    uint8_t rows[8];
} BiglettersGlyph;
```

A pack provides 95 glyphs in printable-ASCII order (`0x20` through `0x7e`) and a
replacement glyph. Each pair of bitmap rows becomes one terminal row:

| Top pixel | Bottom pixel | Terminal cell |
|---:|---:|:---:|
| 0 | 0 | space |
| 1 | 0 | `▀` |
| 0 | 1 | `▄` |
| 1 | 1 | `█` |

An 8×8 source glyph therefore prints as eight columns by four terminal rows.
Consecutive glyph cells are placed directly beside one another because their
spacing is already part of each 8×8 bitmap.

## Regenerating the legacy packs

The checked-in arrays were generated from the three TTF source artifacts listed
in [FONT-LICENSE.md](FONT-LICENSE.md). Regeneration requires Python and Pillow:

```bash
python3 tools/generate_font_pack.py \
  /path/to/Px437_IBM_EGA_8x8.ttf \
  --symbol bigletters_font_ega \
  --name ega \
  --description "IBM EGA 8x8 chunky title font" \
  > font_ega.c
```

The generator requires an exact eight-pixel character advance and rejects any
glyph extending outside its 8×8 cell. After regeneration, run `make check` and
confirm that the source-artifact hash in `FONT-LICENSE.md` is current.

## Adding a pack

1. Generate or define a 95-entry `BiglettersGlyph` array.
2. Export a `BiglettersFontPack` descriptor with its name, description,
   replacement glyph, attribution, and license.
3. Declare the descriptor in `bigletters.h`.
4. Add it to `font_packs` in `font_pack.c`.
5. Add its source to both source lists in `Makefile.am`.
6. Extend `tests/test_font_packs.c` and run `./build.sh && make check`.

Keep generated font data under its source license. A font pack's license does
not automatically become the license of the surrounding renderer code.
