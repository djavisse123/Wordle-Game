/**
 * @file lexicon.h
 * @author Daniel Avisse (djavisse)
 * This is the header file for lexicon.c. This file holds all
 * the constants and function protypes that are used in lexcion.c
 */
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/** Maximum lengh of a word on the word list. */
#define WORD_LEN 5

/** Maximum number of words on the word list. */
#define WORD_LIMIT 100000

/** Value that is over the WORD_LIMIT to allow for strings longer than the limit */
#define OVER_WORD_LIMIT 7

/**
 * This fuction is used to read in words into the wordList. For a wordList to be
 * valid, it must not have any duplicates, uppercase letters, and no words
 * that aren't exaclty 5 letters. This function will be able to check for invalid files
 * and then report that to stderr. If the file can't be opened then the program will exit.
 * @param filename The name of the file being read
 */
void readWords( char const filename[] );

/**
 * This function is used to check for words in the wordList and also duplicates.
 * If a duplicate is found then the wordList is invalid and this function returns false.
 * If the word is in the wordList then this function will return true.
 * @param word The word being checked to see if it is in the wordList
 * @return true if the word is in the wordList
 * @return false if the word is a duplicate or is not in the wordList
 */
bool inList( char const word[] );

/** 
 * Helper function that is used to if a word is lowerCase or not. If a character
 * is found to be uppercase then this function will return false.
 * @param word The word being checked to see if it is lowercase
 * @return true if the word is lowercase
 * @return false if the word is not lowercase
 */
bool checkIfLowerCase( char word[] );

/**
 * This function is used to choose a random word from the wordList. This
 * uses the seed value inputted from the command-line but if there is no
 * seed then the time is used to pick the word.
 * @param seed The seed or time used to pick te random word
 * @param word The array that will hold the chosen word
 */
void chooseWord( long seed, char word[] );
