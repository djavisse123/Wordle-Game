/**
 * @file io.h
 * @author Daniel Avisse (djavsse)
 * This is the header file for io.c. This file holds 
 * all the constants and function protypes for io.c.
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/** The Escape Sequence that changes the termianl to print green characters */
#define GREEN "\x1B\x5B\x33\x32\x6D"

/** The Escape Sequence that changes the termianl to print yellow characters */
#define YELLOW "\x1B\x5B\x33\x33\x6D"

/** The Escape Sequence that changes the termianl to print black (default color) characters */
#define COLOR_DEFAULT "\x1B\x5B\x30\x6D"

/**
 * This function is used in the wordle program to read in a line of input 
 * for a users guess and then return true or false depending on if it was 
 * able to read it. Whatever is read of that input is then copied over into a char array. 
 * A number is also inputted and this tells the function how many 
 * characters to read. If a line is longer than n then 
 * the rest of the letters are discarded.
 * @param fp The input stream of the line being read
 * @param str The array that will form a string of the letters in the line
 * @param n The number of characters that should be read
 * @return true if the line was read 
 * @return false if there is no input in the line
 */
bool readLine( FILE *fp, char str[], int n );

/**
 * Function that changes the colors in the terminal to green when using printf
 */
void colorGreen();

/**
 * Function that changes the colors in the terminal to yellow when using printf
 */
void colorYellow();

/**
 * Function that changes the colors in the terminal to black (default color) when using printf
 */
void colorDefault();
