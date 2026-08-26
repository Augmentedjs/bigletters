# BigLetters

BigLetters is a C command-line program that renders text with pre-baked Unicode
block and half-block glyphs. It supports every printable base-ASCII character
(`0x20` through `0x7e`), including distinct uppercase and lowercase letters,
numbers, punctuation, and symbols.

## Features

- Printable ASCII: `A-Z`, `a-z`, `0-9`, spaces, punctuation, and symbols
- Named, compile-time font packs
- Built-in `normal` and `bold` packs
- ANSI colors 1-15 and row-based rainbow color
- Underline and inverse-color effects
- A visible replacement glyph for bytes outside the supported ASCII range

## Build

Requirements are a C compiler, Autoconf, and Automake.

```bash
./build.sh
make check
```

The resulting executable is `./bigletters`.

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
- `-b` remains as an alias for `--font bold`.
- `-u` adds an underline below the glyphs.
- `-i` renders with ANSI background colors.

Examples:

```bash
./bigletters -t "Hello, world!" -c 4
./bigletters -t "Score: 12,500" --font bold -c r
./bigletters -t "[ready] 100%" -u -i -c 2
./bigletters --list-fonts
```

## Font packs

A font pack is a `BiglettersFontPack` containing six-row, six-column pre-baked
glyph tables. Each pack owns uppercase, lowercase, and number glyphs and may
provide its own printable-ASCII symbols. The built-in packs share the standard
symbol table.

See [FONTS.md](FONTS.md) for the pack contract and an example of adding a pack.

## Source layout

- `bigletters.c` contains CLI parsing, effects, and row rendering.
- `font_pack.c` contains pack discovery and ASCII glyph lookup.
- `font_symbols.c` contains the shared punctuation and replacement glyphs.
- `font_normal.c` and `font_bold.c` are self-contained built-in packs.
- `tests/test_font_packs.c` verifies the complete printable-ASCII contract.

## License

BigLetters is available under the Apache License 2.0.
