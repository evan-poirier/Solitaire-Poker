/*
 SolitairePoker.c
 
 Notes: The 52 cards of a deck are represented as integers: 0 .. 51
 0..12 are clubs Ace, 2, ..., King
 13..25 are diamonds Ace, 2, ..., King
 26..38 are hearts Ace, 2, ..., King
 39..51 are spades Ace, 2, ..., King

 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

//do not remove
#include "include.code" //Include custom header file (it contains necessary functions)
//A version of the file:include.code is available from the assignment page
//as studentinclude.code which you should save locally as include.code
//include.code contains implementations for seed, instructions, and private_nextcard(int)
//used by shuffle and next card.
//The version used during testing is slightly different but will not affect your efforts.
//For testing you may modify studentinclude.code -- it will not be part of your submission.


// Function to shuffle the deck
//you should call this before each deal (including the first)
void shuffle() {
    private_nextcard(1); // Call a custom function to shuffle
}

// Function to get the next card to be dealt
//call this to deal a card. Do not call rand().
int nextcard() {
    return private_nextcard(0); // Call a custom function to get the next card
}

// Enumeration for different poker hands
enum hands { UNKNOWN, HIGHCARD, PAIR, TWOPAIR, TRIPS, STRAIGHT,
    FLUSH, FULLHOUSE, QUADS, STRAIGHTFLUSH, ROYALFLUSH };
char * handNames[] ={ "UNKNOWN", "HIGHCARD", "PAIR", "TWOPAIR", "TRIPS", "STRAIGHT",
    "FLUSH", "FULLHOUSE", "QUADS", "STRAIGHTFLUSH", "ROYALFLUSH" }; // Names of each hand

// Enumeration for card suits
enum suits {CLUB, DIAMOND, HEART, SPADE};
char * suitNames[] ={ "CLUB", "DIAMOND", "HEART", "SPADE"}; // Names of card suits

// Enumeration for card ranks
enum ranks {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};
char * rankNames[] ={ "ACE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN",
    "EIGHT", "NINE", "TEN", "JACK", "QUEEN", "KING"}; // Names of card ranks

//FUNCTION PROTOTYPES: YOU MUST IMPLEMENT THESE FUNCTIONS

// Function to get the rank of a card
enum ranks getrank(int card);

// Function to get the suit of a card
enum suits getsuit(int card);

// Function to evaluate the poker hand
enum hands eval(int []);

// Function to check for a royal flush
int royalflush(int []);

// Function to check for a straight flush
int straightflush(int []);

// Function to check for four of a kind
int fourofkind(int []);

// Function to check for a full house
int fullhouse(int []);

// Function to check for a flush
int flush(int []);

// Function to check for a straight
int straight(int []);

// Function to check for three of a kind
int threekind(int []);

// Function to check for two pairs
int twopair(int []);

// Function to check for a pair
int pair(int []);


// My functions and declarations
void printHand(int hand[]) {
    for (int i = 0; i < 5; i ++) {
        printf("%s-%s\t", suitNames[getsuit(hand[i])], rankNames[getrank(hand[i])]);
    }
    printf("\n");
}

void printHandFinal(int hand[]) {
    for (int i = 0; i < 5; i ++) {
        printf("%d\t%s-%s\t", hand[i], suitNames[getsuit(hand[i])], rankNames[getrank(hand[i])]);
    }
}

void replaceCards(int hand[]) {
    char input[10];
    int cardsToReplace[3];

    fgets(input, 9, stdin);

    int numReplacements = sscanf(input, "%d %d %d", &cardsToReplace[0], &cardsToReplace[1], &cardsToReplace[2]);

    for (int i = 0; i < numReplacements; i ++) {
        printf("cardsToReplace[%d] = %d\n", i, cardsToReplace[i]);
        hand[cardsToReplace[i] - 1] = nextcard();
    }
}

int handScores[] ={ 0, 1, 3, 7, 11, 17,
    26, 32, 40, 45, 50 };

int main(int argc, char ** argv) {
    //do not remove
    seed(argc, argv); // Seed the random number generator
    instructions(); // Display game instructions

    //TODO:
        //WRITE CODE TO PLAY 10 HANDS OF POKER
            //DEAL 5 CARDS
            //SHOW DEALT HAND
            //DRAW UP TO 3 CARDS
            //SHOW FINAL HAND
            //EVAL REPORT AND SAVE INFO FOR LATER
        //GENERATE SCORESHEET USING INFO

    // global variables
    int hands[10][5];
    int totalPoints = 0;

    for (int i = 0; i < 10; i ++) {
        // shuffle before starting hand
        shuffle();

        // deal hand
        for (int j = 0; j < 5; j ++) {
            hands[i][j] = nextcard();
        }
        
        // print each card in hand
        printHand(hands[i]);

        // prompt card replacement
        printf("Select up to three cards to replace[1-5] and press enter\n");

        // replace cards
        replaceCards(hands[i]);

        // print result
        printHand(hands[i]);
        printf("\n");
        printHand(hands[i]);
        printf("Hand %d: Score:\t %d %s\n\n\n\n", i + 1, handScores[eval(hands[i])], handNames[eval(hands[i])]);
    }

    // print final results

    printf("********************************************************************************\n");
    printf("***                         S C O R E S H E E T                              ***\n");
    printf("********************************************************************************\n");

    for (int i = 0; i < 10; i ++) {
        totalPoints += handScores[eval(hands[i])];

        printf("Hand %d: Score:\t %d %s\t", i + 1, handScores[eval(hands[i])], handNames[eval(hands[i])]);
        printf("[");
        printHandFinal(hands[i]);
        printf("\t]\n");
    }

    printf("==============================================================================");
    printf("Total Points:\t\t%d", totalPoints);
    printf("==============================================================================");


    // populate hands (TESTING ONLY)
    /*
    for (int i = 0; i < 10; i ++) {

        shuffle();

        for (int j = 0; j < 5; j ++) {
            hands[i][j] = nextcard();
        }
    }
    */

    // print hands (TESTING ONLY)
    /*
    for (int i = 0; i < 10; i ++) {
        printf("Hand #%d\n", i + 1);
        for (int j = 0; j < 5; j ++) {
            // get card info
            int suit = getsuit(hands[i][j]);
            int rank = getrank(hands[i][j]);

            // print info for each card
            //printf("Raw card value: %d, ", hands[i][j]);
            printf("Suit: %s ", suitNames[suit]);
            printf("Rank: %s\n", rankNames[rank]);
        }

        // to test particular hand scanners
        printf("\n");
        printf("Result: %s\n", handNames[eval(hands[i])]);
        printf("\n");
    }
    */
    
    return 0;
}

//TODO:
//THE FOLLOWING STUBS NEED TO BE IMPLEMENTED CORRECTLY

// Function to get the suit of a card (COMPLETE)
enum suits getsuit(int card){
    if (card >= 0 && card <= 12) {
        return CLUB;
    } else if (card <= 25) {
        return DIAMOND;
    } else if (card <= 38) {
        return HEART;
    } else if (card <= 51) {
        return SPADE;
    }
}

// Function to get the rank of a card (COMPLETE)
enum ranks getrank(int card){
    for (int i = 0; i < 13; i ++) {
        if (((card - i) % 13) == 0) {
            return i;
        }
    }
}

// Function to evaluate the poker hand (INCOMPLETE)
enum hands eval(int hand[]){
    if (royalflush(hand)) {
        return 10;
    } else if (straightflush(hand)) {
        return 9;
    } else if (fourofkind(hand)) {
        return 8;
    } else if (fullhouse(hand)) {
        return 7;
    } else if (flush(hand)) {
        return 6;
    } else if (straight(hand)) {
        return 5;
    } else if (threekind(hand)) {
        return 4;
    } else if (twopair(hand)) {
        return 3;
    } else if (pair(hand)) {
        return 2;
    } else {
        return 1;
    }
}

// Function to check for a royal flush (COMPLETE)
int royalflush(int hand[]){
    int rankAppearances[13] = {0};

    for (int i = 0; i < 5; i ++) {
        rankAppearances[getrank(hand[i])] ++;
    }

    for (int i = 1; i < 9; i ++) {
        if (rankAppearances[i] > 0) {
            return 0;
        } 
    }

    if (straight(hand) && flush(hand)) {
        return 1;
    } else {
        return 0;
    }
}

// Function to check for a straight flush (COMPLETE)
int straightflush(int hand[]){
    if (straight(hand) && flush(hand)) {
        return 1;
    } else {
        return 0;
    }
}

// Function to check for a flush (COMPLETE)
int flush(int hand[]){
    // if any card has a different suit than card 0, return 0 to indicate no flush
    for (int i = 1; i < 5; i ++) {
        if (getsuit(hand[0]) != getsuit(hand[i])) {
            return 0;
        }
    }

    // if all cards are the same,
    return 1;
}

// Function to check for a straight (COMPLETE) (assumes that aces are either high or low)
int straight(int hand[]){
    int rankAppearances[13] = {0};
    int inARow = 0;

    for (int i = 0; i < 5; i ++) {
        rankAppearances[getrank(hand[i])] ++;
    }

    for (int i = 0; i < 13; i ++) {
        if (rankAppearances[i] > 1) {
            return 0;
        } else if (rankAppearances[i] == 1) {
            inARow ++;
        } else {
            inARow = 0;
        }

        if (inARow == 5) {
            return 1;
        }

        // if last 4 cards are 10 J Q K, look for ace
        if (i == 12 && inARow == 4 && rankAppearances[0] == 1) {
            return 1;
        }
    }

    return 0;
}

// Function to check for four of a kind (COMPLETE)
int fourofkind(int hand[]){
    int rankAppearances[13] = {0};

    for (int i = 0; i < 5; i ++) {
        rankAppearances[getrank(hand[i])] ++;
    }

    for (int i = 0; i < 13; i ++) {
        if (rankAppearances[i] == 4) {
            return 1;
        } 
    }

    return 0;
}

// Function to check for a full house (COMPLETE)
int fullhouse(int hand[]){
    int rankAppearances[13] = {0};
    bool has2Pair = false;
    bool has3Pair = false;

    for (int i = 0; i < 5; i ++) {
        rankAppearances[getrank(hand[i])] ++;
    }

    for (int i = 0; i < 13; i ++) {
        if (rankAppearances[i] == 3) {
            has3Pair = true;
        }
        if (rankAppearances[i] == 2) {
            has2Pair = true;
        }
    }

    if (has3Pair && has2Pair) {
        return 1;
    } else {
        return 0;
    }
}

// Function to check for three of a kind (COMPLETE)
int threekind(int hand[]){
    int rankAppearances[13] = {0};

    for (int i = 0; i < 5; i ++) {
        rankAppearances[getrank(hand[i])] ++;
    }

    for (int i = 0; i < 13; i ++) {
        if (rankAppearances[i] >= 3) {
            return 1;
        }
    }

    return 0;
}

// Function to check for two pairs (COMPLETE)
int twopair(int hand[]){
    int rankAppearances[13] = {0};
    int pairCount = 0;

    for (int i = 0; i < 5; i ++) {
        rankAppearances[getrank(hand[i])] ++;
    }

    for (int i = 0; i < 13; i ++) {
        if (rankAppearances[i] >= 2) {
            pairCount ++;
        }
    }

    if (pairCount == 2) {
        return 1;
    } else {
        return 0;
    }
}

// Function to check for a pair (COMPLETE)
int pair(int hand[]){
    int rankAppearances[13] = {0};

    for (int i = 0; i < 5; i ++) {
        rankAppearances[getrank(hand[i])] ++;
    }

    for (int i = 0; i < 13; i ++) {
        if (rankAppearances[i] >= 2) {
            return 1;
        }
    }

    return 0;
}
