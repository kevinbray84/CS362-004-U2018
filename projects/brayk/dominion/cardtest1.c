#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "interface.h"

#define TESTCARD "smithy"



int main (int argc, char** argv)
{
    int newCards = 0;

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

	// ----------- TEST 1: Gain 3 cards --------------
	printf("TEST 1: Gain 3 cards\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
	newCards = 3;

	printf("hand count = %d, expected = %d: ", testG.handCount[thisPlayer], G.handCount[thisPlayer] + newCards);
	assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] + newCards);



	// ----------- TEST 2: Deck size reduced by 3 cards --------------
	printf("TEST 2: Deck size reduced by 3 cards\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	printf("deck count = %d, expected = %d: ", testG.deckCount[thisPlayer], G.deckCount[thisPlayer] - newCards);
	assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer] + newCards);
	

	// ----------- TEST 3: Verify no change to other player --------------
	printf("TEST 3: Verify no change to other players\n");
	
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


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


// 	struct gameState {
//   int numPlayers; //number of players
//   int supplyCount[treasure_map+1];  //this is the amount of a specific type of card given a specific number.
//   int embargoTokens[treasure_map+1];
//   int outpostPlayed;
//   int outpostTurn;
//   int whoseTurn;
//   int phase;
//   int numActions; /* Starts at 1 each turn */
//   int coins; /* Use as you see fit! */
//   int numBuys; /* Starts at 1 each turn */
//   int hand[MAX_PLAYERS][MAX_HAND];
//   int handCount[MAX_PLAYERS];
//   int deck[MAX_PLAYERS][MAX_DECK];
//   int deckCount[MAX_PLAYERS];
//   int discard[MAX_PLAYERS][MAX_DECK];
//   int discardCount[MAX_PLAYERS];
//   int playedCards[MAX_DECK];
//   int playedCardCount;
// };

	return 0;
}