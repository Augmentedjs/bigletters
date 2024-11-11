# BigLetters CLI Program

**BigLetters** is a simple C-based CLI program that prints large letters made from Unicode block characters. It also includes an option to colorize the output in any of the standard 16 terminal colors.

## Features

- Generates large letters using full block Unicode characters
- Supports letters from A-Z (uppercase only)
- Allows you to choose a color for the text (from 1 to 15)
- Clean and portable design with a Makefile for easy compilation

## Requirements

- GCC compiler

## Installation

1. Clone the repository or copy the `bigletters.c` and `Makefile` files into a directory.
2. Compile the program using `make`:

   ```bash
   make
   ```

This will produce an executable named `bigletters` in the directory.

## Usage

Run the program by specifying a string and a color code (1-15):

```bash
./bigletters
```

### Example

```bash
$ ./bigletters
Enter a string (A-Z only): BOB
Enter a color (1-15): 4
```

This will print "BOB" in large letters with the chosen color (blue in this example).

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

> **Note:** If you enter an invalid color, the program defaults to white.

## Cleanup

To remove the compiled files, use:

```bash
make clean
```

## Code Structure

- **`bigletters.c`**: Contains the main program logic, including the letter patterns and functions to print colored, large-text letters.
- **`Makefile`**: Provides targets to compile (`make`), run (`make run`), and clean (`make clean`) the program.

## License

This project is open source and available under the Apache 2.0 License.
