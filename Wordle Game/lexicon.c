/**
 * @file lexicon.c
 * @author Daniel Avisse (djavisse)
 * This component is used to maintain the word list and also choose the word
 * that the user will guess. When the word list is imported into this component
 * the word list should not contain any duplicates, uppercase letter, or words
 * that are not exaclty 5 letters long.
 */
#include "lexicon.h"

/** Large prime multiplier used to choose a word pseudo-randomly. */
#define MULTIPLIER 4611686018453

//Word list that has a max word limit of 100,000 words
static char wordList [WORD_LIMIT][WORD_LEN + 1];
//Number that counts how many words that are in the word list
static int wordListCount = 0;

bool inList( char const word[] )
{
    //Count that checks for duplicates
    int duplicateCount = 0;
    for ( int i = 0; i < wordListCount; i++ ) {
        if ( strcmp(word, wordList[i]) == 0 ){
            duplicateCount++;
        }
    }
    //If the duplicateCount is one then that means it's in the word list
    if ( duplicateCount == 1 ) {
        return true;
    }
    //If the count is greater than one it means there is a duplicate
    if ( duplicateCount > 1 ) {
        return false;
    }
    //Not in the list
    return false;
}

bool checkIfLowerCase( char word[] )
{
    //For loop that checks each letter in the word to see if it is uppercase or nnot
    for ( int i = 0; i < WORD_LEN; i++ ) {
        if ( word[i] >= 'A' && word[i] <= 'Z' ) {
            return false;
        }
    }
    //Is lowercase
    return true;
}

void readWords( char const filename[] )
{
    //Open up the file
    FILE *stream = fopen( filename, "r" );
    //If the file can't be read then exit the program
    if  ( !stream ) {
        fprintf( stderr, "Can't open word list: %s\n", filename );
        exit( EXIT_FAILURE );
    }
    //Check if the file is empty or not
    char ch = fgetc( stream );
    if ( ch == EOF ) {
        printf( "Invalid word file" );
        exit( EXIT_FAILURE );
    }
    else {
        ungetc( ch, stream );
    }
    char str[OVER_WORD_LIMIT];   
    int length;
    int matches = 0;
    //Start scanning the file until it reaches the end
    matches = fscanf ( stream, "%s", str );
    while ( matches != EOF ) {
        length = strlen( str );     
        //Check if the word is exactly 5 letters 
        if ( length != WORD_LEN ) {
            fprintf( stderr, "Invalid word file\n" );
            exit( EXIT_FAILURE );
        }
        //Check if the word is lowerCase
        if ( !checkIfLowerCase(str) ) {
            fprintf( stderr, "Invalid word file\n" );
            exit( EXIT_FAILURE );
        }
        //Copy the word into the wordList
        strcpy( wordList[wordListCount++], str );
        //Check if the wordList is at it's limit
        if ( wordListCount + 1 > WORD_LIMIT ) {
            fprintf( stderr, "Invalid word file\n" );
            exit( EXIT_FAILURE );
        }
        matches = fscanf ( stream, "%s", str );
    }
    fclose( stream );
    //Check for duplicates in the wordList
    for ( int j = 0; j < wordListCount; j++ ) {
        if ( !inList( wordList[j] ) ) {
            fprintf( stderr, "Invalid word file\n");
            exit( EXIT_FAILURE );
        }
    }
}

void chooseWord( long seed, char word[] )
{
    //Used the value of the seed to pick a random word in the list
    int choosenWordIndex = ( seed % wordListCount ) * MULTIPLIER % wordListCount;
    strcpy( word, wordList[choosenWordIndex] );
}
