/**
 * @file wordle.c
 * @author Daniel Avisse (djavisse)
 * Main component in the wordle program. This component will start the wordle
 * program by taking an inputted word list and seed value. The seed value will be used
 * to choose a word but if no seed is inputted then a random word will be picked
 * using the time of the computer. When the program is started this componet will 
 * take the input of the user and check to see if this matches with the chosen word.
 * The program will keep asking for guesses until the guess matches with the chsoen word
 * or the user decides to quit using the word quit. To also help the user guess the correct 
 * word the program will also print the guess into different colors. If the guess contains
 * letters that are in the chosen word then they will be printed yellow. If the guess 
 * contains letters that are in the chosen word and are in the same index 
 * then they are green. Letters that aren't in the chosen word are just the default color
 * of the terminal. 
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "history.h"
#include "lexicon.h"
#include "io.h"

/** Max number of arguments the program needs to run */
#define MAX_NUM_OF_ARGS 3

/** String of the word quit used in the char array quit */
#define QUIT "quit"

/** Value used for the index of the args and also the amount */
#define ARGS_TWO 2

/**
 * This function is a helper function used to print the inputted guess with the colors.
 * This function will each letter of the guess with each letter of the chosen word
 * to see which letters need to be green, yellow, or black(default color).
 * @param word The guess word the user inputted
 * @param wordToGuess The chosen word that is being guessed
 */
static void printColoredWords( char word[], char wordToGuess[] ) { 
    //Create an array of pointers
    char *charPtr [WORD_LEN];
    //Create flags that check to see if a certain color is being used
    bool isGreen = false;
    bool isYellow = false;
    bool isDefault = true;
    //Set the pointers in the array to null
    for ( int i = 0; i < WORD_LEN; i++ ) {
        charPtr[i] = NULL;
    }
    //For loop that will start the comparsion of letters
    for( int i = 0; i < WORD_LEN; i++ ) {
        //Flag to check if a green or yellow has been applied
        bool colorCheck = false;
        //Flag to check if there is a possible next letter that could be green
        bool nextLetterGreenCheck = false;
        for( int j = 0; j < WORD_LEN; j++ ) {
            //Check to see if the letter should be green
            if ( word[i] == wordToGuess[j] && j == i ) {
                //Check if the color is already green
                if ( !isGreen ) {
                    colorGreen();
                    isGreen = true;
                    isYellow = false;
                    isDefault = false;
                }
                //Print the letter and break out of the loop to move to the next letter
                printf( "%c", word[i] );
                colorCheck = true;
                /*Assign the point to the address of the wordToGuess letter so this 
                letter doesn't get checked again */
                charPtr[j] = &wordToGuess[j];
                break;
            }
            //Check to see if the letter should be yellow
            else if ( word[i] == wordToGuess[j] && charPtr[j] == NULL ) {
                //For loop that checks for a possible next letter that could be green
                for ( int k = i; k < WORD_LEN; k++ ) {
                    if( word[k] == wordToGuess[j] && j == k ) {
                        if( !isDefault ) {
                            colorDefault();
                            isDefault = true;
                            isGreen = false;
                            isYellow = false;
                        }
                        nextLetterGreenCheck = true;
                        /*Assign the point to the address of the wordToGuess letter so this 
                        letter doesn't get checked again */
                        charPtr[j] = &wordToGuess[j];
                        printf( "%c", word[i] );
                        break;
                    }
                }
                //Get out of the for loop and move to next letter if true
                if ( nextLetterGreenCheck ) {
                    break;
                }
                //Another check to see if the letter should be green instead of yellow
                if ( word[i] == wordToGuess[i] ) {
                    if ( !isGreen ) {
                    colorGreen();
                    isYellow = false;
                    isGreen = true;
                    isDefault = false;
                    }
                    printf( "%c", word[i] );
                    colorCheck = true;
                    /*Assign the point to the address of the wordToGuess letter so this 
                    letter doesn't get checked again */
                    charPtr[j] = &wordToGuess[j];
                    break;
                }
                //Checks if the color is already yellow
                if ( !isYellow ) {
                    colorYellow();
                    isYellow = true;
                    isGreen = false;
                    isDefault = false;
                }
                //Print the letter and break out of the loop to move to the next letter
                printf( "%c", word[i] );
                colorCheck = true;
                /*Assign the point to the address of the wordToGuess letter so this letter doesn't 
                get checked again */
                charPtr[j] = &wordToGuess[j];
                break;
            }
        }
        //Check to see if the color is already black (default color)
        if ( !colorCheck ) {
            if ( !isDefault ) {
                colorDefault();
                isDefault = true;
                isGreen = false;
                isYellow = false;
            }
            //If there is no next Green then print the letter in black (default color)
            if ( !nextLetterGreenCheck ) {
                printf( "%c", word[i] );
            }
        }
    }
    //Check to see if the color is not default so it can be reset at the end
    if ( !isDefault ) {
        colorDefault();
    }
}

/**
 * Main function that starts the whole wordle program. Will use the command-line
 * arguments to get the name of the file and the seed. If no seed is inputted then
 * the time is used to choose the word. After the list is loaded then this function will
 * ask for input from the user and will keep asking until their guess is correct.
 * Once a correct guess is made then the score will be outputted.
 * @param argc Number of command-line arguments
 * @param argv Array containing the different command-line arguments
 * @return int EXIT_SUCCESS
 */
int main( int argc, char *argv[] ) 
{
    //Check to see if the program has the correct amount of arguments
    if ( argc > MAX_NUM_OF_ARGS || argc == 1 ) {
        fprintf( stderr, "usage: wordle <word-list-file> [seed-number]\n" );
        exit( EXIT_FAILURE );
    }
    //Reads in the word list
    readWords( argv[1] );
    char wordToGuess[WORD_LEN + 1];
    //If there is no seed then use the time to choose the word
    if ( argc == ARGS_TWO ) {
        chooseWord( time( NULL ), wordToGuess );
    }
    //If there is a seed then use it to choose the word
    else {
        long seed = atoi( argv[ARGS_TWO] );
        if ( seed < 0 ) {
            fprintf( stderr, "usage: wordle <word-list-file> [seed-number]\n" );
            exit( EXIT_FAILURE );
        }
        chooseWord( seed, wordToGuess );
    }
    int numOfGuesses = 1;
    char quit[] = QUIT;
    char guess[OVER_WORD_LIMIT];
    bool isThereInput = false;
    isThereInput = readLine(stdin, guess, OVER_WORD_LIMIT);
    if (isThereInput == false) {
        printf( "The word was \"%s\"\n", wordToGuess );
        exit( EXIT_SUCCESS );
    }
    //While loop that will keep asking for guesses from the user until they are correct
    while ( strcmp( guess, wordToGuess ) != 0 && isThereInput != false ) {
        //Exit the program is user types quit
        if ( strcmp( guess, quit ) == 0 ) {
            printf( "The word was \"%s\"\n", wordToGuess );
            exit( EXIT_SUCCESS );
        }
        //Checks for invalid guesses
        else if ( strlen( guess ) != WORD_LEN || !inList( guess ) || !checkIfLowerCase( guess ) ) {
            printf( "Invalid guess\n" );
            numOfGuesses--;
        }
        //Print the colored words
        else {
            printColoredWords( guess, wordToGuess );
            printf( "\n" );
        }
        isThereInput = readLine(stdin, guess, OVER_WORD_LIMIT);
        //End program if an input file is used and it reaches the end
        if ( isThereInput == false ) {
            printf( "The word was \"%s\"\n", wordToGuess );
            exit( EXIT_SUCCESS );
        }
        numOfGuesses++;
    }
    //Print how many guesses it took to solve
    if ( numOfGuesses == 1 ) {
        printf( "Solved in 1 guess\n" );
    }
    else {
        printf( "Solved in %d guesses\n", numOfGuesses );
    }
    //Update the score
    updateScore( numOfGuesses );
    return EXIT_SUCCESS;
}
