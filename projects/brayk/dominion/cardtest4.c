#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "interface.h"

#define TESTCARD "remodel"

int main (int argc, char** argv)
{
    int trashedCost = 0;
    int ceResult = 0;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	int thatPlayer = 1;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, remodel, minion, great_hall, cutpurse,
			sea_hag, tribute, smithy, council_room};
	//char cardName[16];

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

    // test that trashed card is not in hand
    // test that trasshed card didn't go to discard pile
    // test no change to other player
    // test that you can gain a card costing 2 more than it
    // test that you can't gain a card costing 3 more than it
   	// check no change to victory card pile


		// ----------- TEST 1:test that trashed card is not in hand --------------
	printf("TEST 1: test that trashed card is not in hand\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(remodel, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("hand count = %d, expected = %d: ", testG.handCount[thisPlayer], G.handCount[thisPlayer] - 2);
	assertTrue(testG.handCount[thisPlayer] == G.handCount[thisPlayer] - 2);

	// ----------- TEST 2: test that trasshed card didn't go to discard pile --------------
	printf("TEST 2: test that trasshed card didn't go to discard pile\n");
	
	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(remodel, choice1, choice2, choice3, &testG, handpos, &bonus);
	
	printf("deck count = %d, expected = %d: ", testG.deckCount[thisPlayer], G.deckCount[thisPlayer]);
	assertTrue(testG.deckCount[thisPlayer] == G.deckCount[thisPlayer]);

	// ----------- TEST 3: Check that there is no change to player 2's hand --------------
	printf("TEST 3: Check that there is no change to player 2's hand\n");

    // copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(remodel, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("other player hand count = %d, expected = %d: ", testG.deckCount[thatPlayer], G.deckCount[thatPlayer]);
	assertTrue(testG.handCount[thatPlayer] == G.handCount[thatPlayer]);

	printf("other player deck count = %d, expected = %d: ", testG.deckCount[thatPlayer], G.deckCount[thatPlayer]);
	assertTrue(testG.deckCount[thatPlayer] == G.deckCount[thatPlayer]);


	// ----------- TEST 4: test that you can gain a card costing 2 more than it --------------
	printf("TEST 4: test that you can gain a card costing 2 more than it\n");

    // copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	choice1 = 0;  // card 0 is copper, which costs 0
	choice2 = 1;  // card 1 is embargo, which costs 2
	ceResult = cardEffect(remodel, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("Attempting to gain card that costs 2 more than trashed card: ");
    if (ceResult < 0)
    {
        printf("FAILED\n");
    }
    else
    {
        printf("PASSED\n");        
    }

	// ----------- TEST 5: test that you can gain a card costing 3 more than it --------------
	printf("TEST 5: test that you can gain a card costing 3 more than it\n");

    //trashedCost = getCost(handCard(choice1, &G)); 
    //printf("trashed card: %d, cost: %d\n", handCard(choice1, &G), trashedCost);


    // copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	
	choice1 = 0;  // card 0 is copper, which costs 0
	choice2 = 5;  // card 5 is great_hall, which costs 3
	ceResult = cardEffect(remodel, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("Attempting to gain card that costs 3 more than trashed card: ");
    if (ceResult < 0)
    {
        printf("PASSED\n");   // expected value is taht you can't buy it, so this is a pass
    }
    else
    {
        printf("FAILED\n");   // expected result is that you can't buy it, so this is a fail
    }

	// ----------- TEST 5: Verify no change to victory card pile --------------
	printf("TEST 6: Verify no change to victory card piles\n");

	// copy the game state to a test case
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(remodel, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("Verifying no change to victory card piles...\n");
	printf("%d estates before == %d estates after:     ", G.supplyCount[estate], testG.supplyCount[estate]);
	assertTrue(G.supplyCount[estate] == testG.supplyCount[estate]);
	printf("%d duchies before == %d duchies after:     ", G.supplyCount[duchy], testG.supplyCount[duchy]);
	assertTrue(G.supplyCount[duchy] == testG.supplyCount[duchy]);
	printf("%d provinces before == %d provinces after: ", G.supplyCount[province], testG.supplyCount[province]);
	assertTrue(G.supplyCount[province] == testG.supplyCount[province]);

	return 0;
}