# BigLetters

BigLetters is a C command-line program for chunky terminal titles. It renders
real 8×8 legacy bitmap fonts with Unicode half-block characters, preserving all
eight source columns while packing two source rows into each terminal row. Each
glyph supplies its own spacing inside its 8×8 cell, so adjacent glyphs are
rendered without an extra separator column.

## Built-in font packs

- `cga-thin` — IBM CGA Thin 8×8, the default non-bold face
- `ega` — IBM EGA 8×8, the bold chunky title face
- `phoenix` — Phoenix EGA 8×8, a heavier alternate face

The packs cover every printable ASCII character from `0x20` through `0x7e`.
Invocations without a font option use `cga-thin`. `normal` remains an alias for
`cga-thin`, while `bold` and `-b` select `ega` for compatibility with earlier
releases.

The bitmap data is derived from fonts by VileR and is separately licensed under
CC BY-SA 4.0. See [FONT-LICENSE.md](FONT-LICENSE.md) for attribution, source
hashes, and licensing details.

## Build

Requirements are a C compiler, Autoconf, and Automake.

```bash
./build.sh
make check
```

## Usage

```text
bigletters -t text [-c color | -r R,G,B] [-f font] [-b] [-s] [-x] [-u] [-i] [-v]
```

Options:

- `-t text` or `--text text` renders up to 20 ASCII characters.
- `-c 1` through `-c 15`, or `--color`, selects an ANSI color.
- `-c r` or `--color r` selects the rainbow effect.
- `-r R,G,B` or `--rgb R,G,B` selects a 24-bit terminal color with components
  from `0` through `255`. RGB takes precedence over color, regardless of
  argument order.
- `-f name` or `--font name` selects a font pack.
- `--list-fonts` prints the installed font packs.
- `-b` or `--bold` switches from the default CGA Thin face to bold EGA.
- `-s` or `--slant` uses row offsets of `3`, `2`, `1`, and `0` columns from top
  to bottom. Glyph bitmap data is unchanged.
- `-x` or `--extra-large` renders every source pixel as two adjacent full
  blocks, producing a 16×8 terminal glyph. With slant, its row offsets are `7`
  through `0`.
- `-u` or `--underline` adds an underline below the glyphs.
- `-i` or `--inverse` renders with ANSI background colors.
- `-v` or `--version` prints the BigLetters version and exits.

Terminal-title examples:

```bash
./bigletters -t "HOST: ATLAS-01" -c 6
./bigletters -t "HOST: ATLAS-01" -r 64,200,255
./bigletters -t "HOST: ATLAS-01" -r 64,200,255 -s
./bigletters -t "HOST: ATLAS-01" -b -x -s -r 64,200,255
./bigletters --text "HOST: ATLAS-01" --bold --extra-large --slant \
  --rgb 64,200,255
./bigletters -t "HOST: ATLAS-01" -b -c 6
./bigletters -t "BUILD SERVER" -f phoenix -c r
./bigletters -t "devbox.local" -f cga-thin -c 2
./bigletters -v
```

For a login-shell title, build BigLetters and add something like this to
`~/.bash_profile`:

```bash
/path/to/bigletters -t "HOST: $(hostname -s)" -c 6
```

## Font packs

Each printable character is stored as eight bytes: one byte per 8-pixel row.
The normal renderer combines each pair of rows into `▀`, `▄`, `█`, or a space.
Extra-large mode interprets the same bits as doubled full blocks; it does not
carry a second copy of the font. See [FONTS.md](FONTS.md) for the C contract and
regeneration workflow.

## License

BigLetters program code is available under the Apache License 2.0. Derived font
data has the separate license described in [FONT-LICENSE.md](FONT-LICENSE.md).
