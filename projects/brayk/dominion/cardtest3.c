#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "interface.h"

#define TESTCARD "council_room"

int main (int argc, char** argv)
{
    int newCards = 4;
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

    // check that player hand is +4
	// check that player has +1 buy
	// check +1 draw to other player
	// check no change to victory card pile
	// chekc no change to kingdom card pile

		// ----------- TEST 1: Gain 3 cards --------------
	printf("TEST 1: Gain 4 cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("hand count = %d, expected = %d: ", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards - 1);
	assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards - 1);

	// ----------- TEST 2: Deck size reduced by 4 cards --------------
	printf("TEST 2: Deck size reduced by 4 cards\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	printf("deck count = %d, expected = %d: ", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
	assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] - newCards);


	// ----------- TEST 3: Check that there is one more card in player 2's hand and 1 less in deck --------------
	printf("TEST 3: Check that there is one more card in player 2's hand and 1 less in deck\n");

    // copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("other player hand count = %d, expected = %d: ", testG.handCount[thatPlayer], G.handCount[thatPlayer] + 1);
	assertTrue(testG.handCount[thatPlayer] == G.handCount[thatPlayer] + 1);

	printf("other player deck count = %d, expected = %d: ", testG.deckCount[thatPlayer], G.deckCount[thatPlayer] - 1);
	assertTrue(testG.deckCount[thatPlayer] == G.deckCount[thatPlayer] - 1);

	// ----------- TEST 4: Check that player has 1 more buy --------------
	printf("TEST 4: Check that player has 1 more buy\n");

    // copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("num buys = %d, expected = %d: ", testG.numBuys, G.numBuys + 1);
	assertTrue(testG.numBuys == G.numBuys + 1);

	// ----------- TEST 5: Verify no change to victory card pile --------------
	printf("TEST 5: Verify no change to victory card piles\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(council_room, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("Verifying no change to victory card piles...\n");
	printf("%d estates before == %d estates after: ", G.supplyCount[estate], testG.supplyCount[estate]);
	assertTrue(G.supplyCount[estate] == testG.supplyCount[estate]);
	printf("%d duchies before == %d duchies after: ", G.supplyCount[duchy], testG.supplyCount[duchy]);
	assertTrue(G.supplyCount[duchy] == testG.supplyCount[duchy]);
	printf("%d provinces before == %d provinces after: ", G.supplyCount[province], testG.supplyCount[province]);
	assertTrue(G.supplyCount[province] == testG.supplyCount[province]);

	// ----------- TEST 6: Verify no change to kingdom card pile --------------
	for (int i = 0; i < 10; i++)
	{
		// cardNumToName(k[i], cardName);
		// printf("%d %s before == %d %s after: ", G.supplyCount[k[i]], cardName, G.supplyCount[k[i]], cardName);
		printf("%d Kingdom card %d before == %d kingdom card %d after: ", G.supplyCount[k[i]], i, G.supplyCount[k[i]], i);
		assertTrue(G.supplyCount[k[i]] == testG.supplyCount[k[i]]);
	}

	return 0;
}