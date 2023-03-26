/**
 * @file history.c
 * @author Daniel Avisse (djavisse)
 * This component is used to maintain the score of the player of the 
 * wordle program. Once a game of wordle is complete the function in this class
 * will be used to create a file name scores.txt which will hold the scores of all
 * the games played. 
 */
#include "history.h"

void updateScore( int guessCount )
{
    //Create an array that will hold the scores
    int scoreHistory[SCORES_LENGTH] = {};
    //Open the scores.txt file
    FILE *stream = fopen( FILENAME, "r" );
    int scoreNumber = 0;
    //If the file doesn't exist then switch to write mode and create a new file
    if ( !stream ) {
       stream = fopen( FILENAME, "w" );
    }
    //Check that the file isn't empty and then scan all the scores inside
    if ( fscanf( stream, "%d", &scoreNumber ) != EOF ) {
        scoreHistory[0] = scoreNumber;
         for ( int i = 1; i < SCORES_LENGTH; i++ ) {
            fscanf( stream, "%d", &scoreNumber );
            scoreHistory[i] = scoreNumber;
        }
        //Switch to write+ mode to overwrite the contents of the file
        stream = fopen( FILENAME, "w+" );
    }
    //Input the scores of the game into scoreHistory using the guessCount  
    if ( guessCount > SCORES_LENGTH - 1 ) {
        scoreHistory[SCORES_LENGTH - 1] = scoreHistory[SCORES_LENGTH - 1] + 1;
    }
    else {
        scoreHistory[guessCount - 1] = scoreHistory[guessCount - 1] + 1;
    }
    //Print the new scores into the the scores.txt file
    for ( int i = 0; i < SCORES_LENGTH - 1; i++ ) {
        fprintf(stream, "%d ", scoreHistory[i]);
    }
    fprintf( stream, "%d\n", scoreHistory[SCORES_LENGTH - 1] );
    //Print the the scores to stdin
    for ( int i = 0; i < SCORES_LENGTH - 1; i++ ) {
        printf( "%2d  :%5d\n", i + 1, scoreHistory[i] );
    }
    printf( "10+ :%5d\n", scoreHistory[SCORES_LENGTH - 1] );
    fclose( stream );
}
