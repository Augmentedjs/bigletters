#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WIDTH 6
#define MAX_HEIGHT 6
#define MAX_CHARS 20

// Define ANSI color codes for colors 1-15 (standard CLI colors)
const char *colors[] = {
    "\x1b[30m", // 0: Black (not used)
    "\x1b[31m", // 1: Red
    "\x1b[32m", // 2: Green
    "\x1b[33m", // 3: Yellow
    "\x1b[34m", // 4: Blue
    "\x1b[35m", // 5: Magenta
    "\x1b[36m", // 6: Cyan
    "\x1b[37m", // 7: White
    "\x1b[90m", // 8: Bright Black (Gray)
    "\x1b[91m", // 9: Bright Red
    "\x1b[92m", // 10: Bright Green
    "\x1b[93m", // 11: Bright Yellow
    "\x1b[94m", // 12: Bright Blue
    "\x1b[95m", // 13: Bright Magenta
    "\x1b[96m", // 14: Bright Cyan
    "\x1b[97m"  // 15: Bright White
};

// Define each letter's pattern using full block characters
char *letters[26][MAX_HEIGHT] = {
     {"▄▀▀▀▀▄",
      "█    █",
      "█▀▀▀▀█",
      "█    █",
      "█    █",
      "      "}, // A
     {"█▀▀▀▀▄",
      "█    █",
      "█▀▀▀▀▄",
      "█    █",
      "█▄▄▄▄▀",
      "      "}, // B
     {"▄▀▀▀▀▄",
      "█     ",
      "█     ",
      "█     ",
      "▀▄▄▄▄▀",
      "      "}, // C
     {"█▀▀▄  ",
      "█   ▀▄",
      "█    █",
      "█   ▄▀",
      "█▄▄▀  ",
      "      "}, // D
     {"█▀▀▀▀▀",
      "█     ",
      "█▀▀▀▀ ",
      "█     ",
      "█▄▄▄▄▄",
      "      "}, // E
     {"█▀▀▀▀▀",
      "█     ",
      "█▀▀▀▀ ",
      "█     ",
      "█     ",
      "      "}, // F
     {"▄▀▀▀▀▄",
      "█     ",
      "█  ▀▀█",
      "█    █",
      "▀▄▄▄▄▀",
      "      "}, // G
     {"█    █",
      "█    █",
      "█▀▀▀▀█",
      "█    █",
      "█    █",
      "      "}, // H
     {" ▀█▀  ",
      "  █   ",
      "  █   ",
      "  █   ",
      " ▄█▄  ",
      "      "}, // I
     {"    ▀█",
      "     █",
      "     █",
      "█    █",
      "▀▄▄▄▄▀",
      "      "}, // J
     {"█    █",
      "█  ▄▀ ",
      "█▄▀▄  ",
      "█   ▀▄",
      "█    █",
      "      "}, // K
     {"█     ",
      "█     ",
      "█     ",
      "█     ",
      "█▄▄▄▄▄",
      "      "}, // L
     {"█    █",
      "██  ██",
      "█ ██ █",
      "█    █",
      "█    █",
      "      "}, // M
     {"█▄   █",
      "█▀▄  █",
      "█ ▀▄ █",
      "█  ▀▄█",
      "█   ▀█",
      "      "}, // N
     {"▄▀▀▀▀▄",
      "█    █",
      "█    █",
      "█    █",
      "▀▄▄▄▄▀",
      "      "}, // O
     {"█▀▀▀▀▄",
      "█    █",
      "█▀▀▀▀ ",
      "█     ",
      "█     ",
      "      "}, // P
     {"▄▀▀▀▀▄",
      "█    █",
      "█    █",
      "█ ▀▄ █",
      "▀▄▄▄▀▄",
      "      "}, // Q
     {"█▀▀▀▀▄",
      "█    █",
      "█▀▀█▀ ",
      "█   █ ",
      "█    █",
      "      "}, // R
     {"▄▀▀▀▀▄",
      "█     ",
      " ▀▀▀▀▄",
      "     █",
      "▀▄▄▄▄▀",
      "      "}, // S
     {"▀▀█▀▀ ",
      "  █   ",
      "  █   ",
      "  █   ",
      "  █   ",
      "      "}, // T
     {"█    █",
      "█    █",
      "█    █",
      "█    █",
      "▀▄▄▄▄▀",
      "      "}, // U
     {"█    █",
      "█    █",
      " █  █ ",
      " █  █ ",
      "  ██  ",
      "      "}, // V
     {"█    █",
      "█    █",
      "█ ██ █",
      "██  ██",
      "█    █",
      "      "}, // W
     {"█    █",
      " █  █ ",
      "  ██  ",
      " █  █ ",
      "█    █",
      "      "}, // X
     {"█   █ ",
      " █ █  ",
      "  █   ",
      "  █   ",
      "  █   ",
      "      "}, // Y
     {"▀▀▀▀█▀",
      "   ▄▀ ",
      "  ▄▀  ",
      " ▄▀   ",
      "▄█▄▄▄▄",
      "      "}  // Z
};

char *numbers[10][MAX_HEIGHT] = {
    {"▄▀▀▀▀▄",
     "█  ▄▀█",
     "█▄▀  █",
     "█    █",
     "▀▄▄▄▄▀",
     "      "}, // 0
    {"  ▄█  ",
     " ▀ █  ",
     "   █  ",
     "   █  ",
     " ▄▄█▄▄",
     "      "}, // 1
    {"▄▀▀▀▀▄",
     "    ▄▀",
     "  ▄▀  ",
     "▄▀    ",
     "█▄▄▄▄▄",
     "      "}, // 2
    {"▄▀▀▀▀▄",
     "     █",
     " ▀▀▀▀▄",
     "     █",
     "▀▄▄▄▄▀",
     "      "}, // 3
    {"█    █",
     "█    █",
     "▀▀▀▀▀█",
     "     █",
     "     █",
     "      "}, // 4
    {"█▀▀▀▀▀",
     "█     ",
     "▀▀▀▀▀▄ ",
     "     █",
     "▀▄▄▄▄▀",
     "      "}, // 5
    {"▄▀▀▀▀ ",
     "█     ",
     "█▀▀▀▀▄",
     "█    █",
     "▀▄▄▄▄▀",
     "      "}, // 6
    {"▀▀▀▀▀█",
     "     █",
     "    █ ",
     "   █  ",
     "  █   ",
     "      "}, // 7
    {"▄▀▀▀▀▄",
     "█    █",
     "▄▀▀▀▀▄",
     "█    █",
     "▀▄▄▄▄▀",
     "      "}, // 8
    {"▄▀▀▀▀▄",
     "█    █",
     "▀▄▄▄▄█",
     "     █",
     "▀▄▄▄▄▀",
     "      "}  // 9
};

void print_large_text(const char *text, int color_code) {
    if (color_code < 1 || color_code > 15) {
        color_code = 7; // Default to white if the color is out of range
    }

    printf("%s", colors[color_code]); // Set the color
    for (int row = 0; row < MAX_HEIGHT; row++) { // Each row of the pattern
        for (size_t i = 0; i < strlen(text); i++) { // Use size_t for i to match strlen's return type
            char ch = toupper(text[i]);
            if (ch >= 'A' && ch <= 'Z') {
                int index = ch - 'A';
                printf("%s ", letters[index][row]);
            } else if (ch >= '0' && ch <= '9') {
                int index = ch - '0';
                printf("%s ", numbers[index][row]);
            } else if (ch == ' ') {
                printf("       "); // Space for blank character
            } else {
                printf("       "); // Unsupported characters also print as spaces
            }
        }
        printf("\n");
    }
    printf("\x1b[0m"); // Reset color to default
}

int main() {
    char input[100];
    int color;

    printf("Enter a string (A-Z, 0-9, and spaces only, max 20 characters): ");
    fgets(input, 100, stdin);
    input[strcspn(input, "\n")] = 0; // Remove newline character from input

    if (strlen(input) == 0 || strlen(input) > 20) {
        fprintf(stderr, "Error: Please enter between 1 and 20 characters.\n");
        return 1;
    }

    printf("Enter a color (1-15): ");
    if (scanf("%d", &color) != 1 || color < 1 || color > 15) {
        fprintf(stderr, "Error: Invalid color. Please enter a number between 1 and 15.\n");
        return 1;
    }

    print_large_text(input, color);

    return 0;
}
