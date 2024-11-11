# BigLetters CLI Program

**BigLetters** is a versatile C-based CLI program that prints large letters and numbers made from Unicode block characters. It offers various styling options, such as color customization, bold fonts, underline effects, and inverse colors. Additionally, the program supports a rainbow mode to create a colorful gradient across each line of text.

## Features

- Generates large letters and numbers using full block Unicode characters.
- Supports uppercase letters (A-Z), numbers (0-9), and spaces.
- Provides CLI options for:
  - Choosing text color (1-15) or a rainbow gradient.
  - Bold font option.
  - Underline option to underline text using block characters.
  - Inverse colors, setting background colors instead of the foreground.
- Clean, portable design with Makefile for easy compilation.
- Includes comprehensive error handling and parameter parsing.

## Requirements

- GCC compiler

## Installation

1. Clone the repository or copy the `bigletters.c`, `font_normal.c`, `font_bold.c`, and `Makefile` files into a directory.
2. Compile the program using the following command:

   ```bash
   make
   ```

This will produce an executable named `bigletters` in the directory.

## Usage

You can run the program with various command-line arguments for customization:

```bash
./bigletters [-t text] [-c color] [-b] [-u] [-i]
```

### Options

- **`-t text`**: Specify the text to display (max 20 characters).
- **`-c color`**: Specify the color code (1-15) or 'r' for rainbow gradient.
- **`-b`**: Enable bold font.
- **`-u`**: Underline the text.
- **`-i`**: Inverse colors, setting the background instead of the foreground color.

### Example Commands

#### Basic Usage

```bash
$ ./bigletters -t "HELLO" -c 4
```

This will print "HELLO" in large blue letters.

#### With Bold and Underline

```bash
$ ./bigletters -t "WORLD" -c 2 -b -u
```

This prints "WORLD" in a bold, green font with an underline.

#### Using Rainbow Colors

```bash
$ ./bigletters -t "RAINBOW" -c r
```

This command prints "RAINBOW" with a rainbow gradient applied to each line.

#### Inverse Colors with Underline

```bash
$ ./bigletters -t "INVERSE" -c 5 -i -u
```

This command prints "INVERSE" with an inverted magenta background and an underline.

### Color Codes

| Color Code | Color          |
|------------|----------------|
| 1          | Red            |
| 2          | Green          |
| 3          | Yellow         |
| 4          | Blue           |
| 5          | Magenta        |
| 6          | Cyan           |
| 7          | White          |
| 8          | Gray (Bright Black) |
| 9          | Bright Red     |
| 10         | Bright Green   |
| 11         | Bright Yellow  |
| 12         | Bright Blue    |
| 13         | Bright Magenta |
| 14         | Bright Cyan    |
| 15         | Bright White   |

> **Note:** If the color code is invalid, the program defaults to white.

## Cleanup

To remove the compiled files, use:

```bash
make clean
```

## Code Structure

- **`bigletters.c`**: Contains the main program logic, including the printing functions and argument parsing.
- **`bigletters.h`**: Header file with external declarations and function prototypes.
- **`font_normal.c` and `font_bold.c`**: Source files defining the normal and bold fonts as Unicode block characters.
- **`Makefile`**: Defines targets for building, running, and cleaning up the program.

## License

This project is open source and available under the Apache 2.0 License.
