# Overview
Wordle is a popular word game where the player must guess a 5-letter word in a limited number of attempts. To help the player guess the word, a letter will be colored to indicate if that letter is in the word. If a letter is green, then that means the player has the correct letter in the correct spot. If the letter is yellow, then that means the player has a correct letter but it’s not in the correct spot. If the letter is gray, then that means the letter is not in the word. This project is based on how this game plays but with a few changes. For example, in this version the number of attempts available to the player is unlimited and the player can use their own list of words for the game.

# Usage
To compile and run this project you must have gcc. This program was written in C and needs gcc to compile.
Follow these steps to run the implementation:
1. Run this command in Linux: `make`

### Starting the Game:

Use without a seed: `wordle <word-list-file>`

Use with a seed: `wordle <word-list-file> [seed-number]`

Note: For the best experience use the provided word list file `list-e.txt`.

### How To Play:
* Simply type in a 5-letter word you think would be the correct answer.
* Words are invalid if they are not 5 letters or are not in the provided word list.
* Use the color of the letters to help figure out the word and keep guessing until you get the correct word.
* Once the word is guessed correctly, the score will be outputted to the command line and a file titled scores.txt
* If you are having trouble guessing the word or would simply want to stop playing then type in the word “quit”, and the program will stop and show you the correct word.

# Design Requirements

### Programming Language
The implementation of this project was written in C.
### Components
The creation of this project requires the use of four components total. Descriptions of each of the components are provided below.
* The ***lexicon*** component is responsible for integrating the dictionary of valid words the player can guess and chooses the word the player will have to guess at the start of the game. This component also checks to see if the provided dictionary has no duplicates, no uppercase words, and only words consisting of only 5 letters.
* The ***io*** component is responsible for handling the input and output for the game. This component will read in a player’s input and help output the letters in the correct color.
* The ***history*** component is responsible for reporting the score after a game is successfully played. This component will create the scores.txt file containing the scores of each game played and will update it each time another game is successfully completed.
* The ***wordle*** component is responsible for starting the game and interacting with the player. This component works with lexicon, io, and history to fully recreate the wordle experience.

### Additional Information
This project was implemented individually. Any code that was provided belongs entirely to the NCSU CSC Department.
# Implementation
For this project, the main focus was to try and learn how to use strings and manage a large number of strings in a 2D array. In the Lexicon component I needed to create a 2D char array that would be used to hold a max of 100,000 words for the game. This would act as the game’s dictionary. I then needed to implement some functions in this component that would be able to check the validity of each word when trying to import a word list. If any word was not 5 letters, not lowercase, or if the list contained duplicates, then that entire word list was invalid. Inside the wordle component, a special algorithm was created in order to mimic the color matching featured in the Wordle game. This algorithm would go step by step and compare each letter of the player’s guess with every letter in the guess word. If it spots that two letters are the same and have the same index, then a hex code would be used to change the terminal to output the letter in green. This algorithm tries to find all green letters first before trying to look for yellow letters next. Yellow letters are found when the algorithm notices two letters that are the same but are in different indexes. Gray letters are printed if neither of the conditions for green or yellow were met. Pointers were also used in this algorithm. Once a letter has been found, the address of that letter is assigned to an array of pointers to prevent that letter from being checked in the guess again. This helps deal with words that may contain multiple of the same letter.
