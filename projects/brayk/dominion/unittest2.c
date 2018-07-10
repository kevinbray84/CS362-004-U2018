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
    int initialHandCards = 5;
    int seed = 1000;
    int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	// ----------- TEST 1: Check hand counts during initial state --------------
	printf("********* Testing numHandCards(): Expected == Actual? *********\n");
    printf("TEST 1: Check all card counts during initial state\n");

    printf("Num hand cards: %d == %d:     ", initialHandCards, numHandCards(&G));
    assertTrue(initialHandCards == numHandCards(&G));

	// ----------- TEST 2: Check after playing a smithy --------------

    memcpy(&testG, &G, sizeof(struct gameState));
    playSmithy(&testG, 1);
    printf("After smithy: %d == %d:       ", numHandCards(&G) + 3, numHandCards(&testG));
    assertTrue(numHandCards(&G) + 3 == numHandCards(&testG));

    return 0;
}