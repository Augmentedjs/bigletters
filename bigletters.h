#ifndef BIGLETTERS_H
#define BIGLETTERS_H

#define MAX_WIDTH 6
#define MAX_HEIGHT 6
#define MAX_CHARS 20

// ANSI color codes for CLI colors
extern const char *colors[];

// Extern declarations for normal and bold fonts
extern const char *letters_normal[26][MAX_HEIGHT];
extern const char *numbers_normal[10][MAX_HEIGHT];
extern const char *letters_bold[26][MAX_HEIGHT];
extern const char *numbers_bold[10][MAX_HEIGHT];

// Function declarations
void print_large_text(const char *text, int color_code, int bold, int rainbow, int underline);
int parse_arguments(int argc, char *argv[], char *text, int *color, int *bold, int *rainbow, int *underline);
int validate_input(const char *text, int color_code, int rainbow);
void display_usage();

#endif // BIGLETTERS_H
