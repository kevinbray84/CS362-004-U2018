#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "interface.h"


int main (int argc, char** argv)
{
    int seed = 1000;
    int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("********* Testing isGameOver(): Expected == Actual? *********\n");
	
    // ----------- TEST 1: Check at start of the game (all decks full) --------------
    printf("TEST 1: Check at start of the game (all decks full)\n");

    printf("Full decks.  0 == %d?  ", isGameOver(&G));
    assertTrue(0 == isGameOver(&G));

    // ----------- TEST 2 Check when victory cards are empty --------------
    printf("TEST 2: Check when victory cards are empty\n");

    memcpy(&testG, &G, sizeof(struct gameState));
    testG.supplyCount[estate] = 0;
    printf("estate empty.  0 == %d?    ", isGameOver(&testG));
    assertTrue(0 == isGameOver(&testG));

    memcpy(&testG, &G, sizeof(struct gameState));
    testG.supplyCount[duchy] = 0;
    printf("duchy empty.  0 == %d?     ", isGameOver(&testG));
    assertTrue(0 == isGameOver(&testG));

    memcpy(&testG, &G, sizeof(struct gameState));
    testG.supplyCount[province] = 0;
    printf("province empty.  1 == %d?  ", isGameOver(&testG));
    assertTrue(1 == isGameOver(&testG));

    // ----------- TEST 3 Check when kingdom cards are empty --------------
    printf("TEST 3: Check when kingdom cards are empty\n");
    memcpy(&testG, &G, sizeof(struct gameState));

    printf("%2d of 10 kingdom decks empty.  0 == %d?  ", 0, isGameOver(&testG));
    assertTrue(0 == isGameOver(&testG));

    for (int i = 0; i < 10; i++)
    {
        testG.supplyCount[i] = 0;
        if (i < 2)
        {
            printf("%2d of 10 kingdom decks empty.  0 == %d?  ", i + 1, isGameOver(&testG));
            assertTrue(0 == isGameOver(&testG));
        } 
        else
        {
            printf("%2d of 10 kingdom decks empty.  1 == %d?  ", i + 1, isGameOver(&testG));
            assertTrue(1 == isGameOver(&testG));
        }
    }

    return 0;
}