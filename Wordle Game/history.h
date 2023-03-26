/**
 * @file history.h
 * @author Daniel Avisse (djavisse)
 * This is the header file for history.c. This file holds all
 * the constants and function protypes for history.c. 
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/** The name of the file we will be outputting the scores of the game */
#define FILENAME "scores.txt"

/** The size of the scoreHistory array */
#define SCORES_LENGTH 10

/** 
 * This function is used to update the scores.txt file and also print out the scores of
 * the wordle game to stdin. This method first checks to see if the scores.txt file already 
 * exists. If it doesn't then it will be created and the scores will be added into it.
 * If the file does exist then the existing scores are read into the scoreHistory array
 * and then are updated with the new scores which then get printed
 * onto the file and stdin.
 * @param guessCount The number of guesses it took to get the correct answer
 */
void updateScore( int guessCount );
