#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "interface.h"

#define TESTCARD "adventurer"

int main (int argc, char** argv)
{
    int newCards = 0;
    int testCard = 0;
    int numTreasure, testNumTreasure;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	int thatPlayer = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
	//char cardName[16];

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    // check that hand increased by 2
    // check that last 2 cards are treasure
    // check that tehre was no change to player 2
    // check that there was no change to kingdom or treasure decks

	// ----------- TEST 1: Gain 3 cards --------------
	printf("TEST 1: Gain 2 cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
	newCards = 2;

	printf("hand count = %d, expected = %d: ", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards);
	assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards);

	// ----------- TEST 2: The two new cards are treasure cards --------------
	printf("TEST 2: Check that the new cards are treasures\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

    // get previous number of treasures
    for (int i = 0; i < numHandCards(&G); i++)
    {
        testCard = handCard(i, &testG);
        if (testCard == copper || testCard == silver || testCard == gold)
        {
            numTreasure++;
        }
    }

    // get new number of treasrues
    for (int i = 0; i < numHandCards(&testG); i++)
    {
        testCard = handCard(i, &testG);
        if (testCard == copper || testCard == silver || testCard == gold)
        {
            testNumTreasure++;
        }
    }

	printf("num treasures = %d, expected = %d: ", testNumTreasure, numTreasure + newCards);
	assertTrue(testNumTreasure == numTreasure + newCards);

	// ----------- TEST 3: Check that there is no change to player 2's hand --------------
	printf("TEST 3: Check that there is no change to player 2's hand\n");

    // copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("other player hand count = %d, expected = %d: ", testG.deckCount[thatPlayer], G.deckCount[thatPlayer]);
	assertTrue(testG.handCount[thatPlayer] == G.handCount[thatPlayer]);

	printf("other player deck count = %d, expected = %d: ", testG.deckCount[thatPlayer], G.deckCount[thatPlayer]);
	assertTrue(testG.deckCount[thatPlayer] == G.deckCount[thatPlayer]);

	// ----------- TEST 4: Verify no change to victory card pile --------------
	printf("TEST 4: Verify no change to victory card piles\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("Verifying no change to victory card piles...\n");
	printf("%d estates before == %d estates after: ", G.supplyCount[estate], testG.supplyCount[estate]);
	assertTrue(G.supplyCount[estate] == testG.supplyCount[estate]);
	printf("%d duchies before == %d duchies after: ", G.supplyCount[duchy], testG.supplyCount[duchy]);
	assertTrue(G.supplyCount[duchy] == testG.supplyCount[duchy]);
	printf("%d provinces before == %d provinces after: ", G.supplyCount[province], testG.supplyCount[province]);
	assertTrue(G.supplyCount[province] == testG.supplyCount[province]);

	// ----------- TEST 5: Verify no change to kingdom card pile --------------
	for (int i = 0; i < 10; i++)
	{
		// cardNumToName(k[i], cardName);
		// printf("%d %s before == %d %s after: ", G.supplyCount[k[i]], cardName, G.supplyCount[k[i]], cardName);
		printf("%d Kingdom card %d before == %d kingdom card %d after: ", G.supplyCount[k[i]], i, G.supplyCount[k[i]], i);
		assertTrue(G.supplyCount[k[i]] == testG.supplyCount[k[i]]);
	}

	return 0;
}