#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bigletters.h"

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

void print_large_text(const char *text, int color_code, int bold) {
    const char *(*letters)[MAX_HEIGHT] = bold ? letters_bold : letters_normal;
    const char *(*numbers)[MAX_HEIGHT] = bold ? numbers_bold : numbers_normal;

    if (color_code < 1 || color_code > 15) {
        color_code = 7; // Default to white if the color is out of range
    }

    printf("%s", colors[color_code]); // Set the color
    for (int row = 0; row < MAX_HEIGHT; row++) {
        for (size_t i = 0; i < strlen(text); i++) {
            char ch = toupper(text[i]);
            if (ch >= 'A' && ch <= 'Z') {
                printf("%s ", letters[ch - 'A'][row]);
            } else if (ch >= '0' && ch <= '9') {
                printf("%s ", numbers[ch - '0'][row]);
            } else {
                printf("       "); // Space for blank character
            }
        }
        printf("\n");
    }
    printf("\x1b[0m"); // Reset color to default
}

int parse_arguments(int argc, char *argv[], char *text, int *color, int *bold) {
    *color = 7; // Default to white
    *bold = 0;  // Default to non-bold
    text[0] = '\0';
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            strncpy(text, argv[++i], MAX_CHARS);
            text[MAX_CHARS] = '\0';
        } else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
            *color = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-b") == 0) {
            *bold = 1;
        } else {
            return 0; // Invalid argument
        }
    }
    return 1;
}

int validate_input(const char *text, int color_code) {
    if (strlen(text) == 0 || strlen(text) > MAX_CHARS || color_code < 1 || color_code > 15) {
        return 0;
    }
    return 1;
}

void display_usage() {
    printf("Usage: bigletters [-t text] [-c color] [-b]\n");
    printf("Options:\n");
    printf("  -t text    Specify the text to display (max %d characters)\n", MAX_CHARS);
    printf("  -c color   Specify the color code (1-15)\n");
    printf("  -b         Use bold font\n");
}

int main(int argc, char *argv[]) {
    char text[MAX_CHARS + 1];
    int color, bold;

    if (!parse_arguments(argc, argv, text, &color, &bold) || !validate_input(text, color)) {
        display_usage();
        return 1;
    }

    print_large_text(text, color, bold);
    return 0;
}
