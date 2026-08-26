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
bigletters -t text [-c color] [-f font] [-b] [-u] [-i]
```

Options:

- `-t text` renders up to 20 ASCII characters.
- `-c 1` through `-c 15` selects an ANSI color.
- `-c r` selects the rainbow effect.
- `-f name` or `--font name` selects a font pack.
- `--list-fonts` prints the installed font packs.
- `-b` switches from the default CGA Thin face to the bold EGA face.
- `-u` adds an underline below the glyphs.
- `-i` renders with ANSI background colors.

Terminal-title examples:

```bash
./bigletters -t "HOST: ATLAS-01" -c 6
./bigletters -t "HOST: ATLAS-01" -b -c 6
./bigletters -t "BUILD SERVER" -f phoenix -c r
./bigletters -t "devbox.local" -f cga-thin -c 2
```

For a login-shell title, build BigLetters and add something like this to
`~/.bash_profile`:

```bash
/path/to/bigletters -t "HOST: $(hostname -s)" -c 6
```

## Font packs

Each printable character is stored as eight bytes: one byte per 8-pixel row.
The renderer combines each pair of rows into `▀`, `▄`, `█`, or a space. See
[FONTS.md](FONTS.md) for the C contract and regeneration workflow.

## License

BigLetters program code is available under the Apache License 2.0. Derived font
data has the separate license described in [FONT-LICENSE.md](FONT-LICENSE.md).
