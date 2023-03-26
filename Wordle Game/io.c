/**
 * @file io.c
 * @author Daniel Avisse (djavisse)
 * This component is used to handle IO operations that happen in terminal. 
 * In the wordle game it is needed for some of the letters to change colors
 * and this component will be able to handle changing colors and is also
 * able to read in input if needed.
 */
#include "io.h"

bool readLine( FILE *fp, char str[], int n )
{
    //Get a char and check that the line isn't empty
    char charOfGuess = fgetc( fp );
    if ( charOfGuess == EOF ) {
        return false;
    }
    else {
        //Continue scanning for chars until length n is reached or the next char is a new line.
        for ( int i = 0; i < n; i++ ) {
            str[i] = charOfGuess;
            charOfGuess = fgetc( fp );
            /* If the new line appears before the end of the input then return true and
            add the null terminator */
            if (charOfGuess == '\n') {
                str[i + 1] = '\0';
                return true;
            }
        }
        //Add null terminator after scanning
        str[n + 1] = '\0';
    }
    //Discard chars that are past n
    while ( charOfGuess != '\n' ) {
        charOfGuess = fgetc( fp );
    }
    return true;
}

void colorGreen()
{
    printf( GREEN );
}

void colorYellow()
{
    printf( YELLOW );
}

void colorDefault()
{
    printf( COLOR_DEFAULT );
}
