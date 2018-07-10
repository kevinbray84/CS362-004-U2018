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
    int numKingdomCards = 10;
    int numVictoryCard = 8;
    int seed = 1000;
    int numPlayers = 2;
	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	// ----------- TEST 1: Check all supply counts during initial state --------------
	printf("********* Testing supplyCount(): Expected == Actual? *********\n");
    printf("TEST 1: Check all supply counts during initial state\n");

    printf("*** Victory Cards: Expected == Actual ***\n");
    printf("estate: %d == %d:         ", numVictoryCard, supplyCount(estate, &G));
    assertTrue(numVictoryCard == supplyCount(estate, &G));
    printf("duchy: %d == %d:          ", numVictoryCard, supplyCount(duchy, &G));
    assertTrue(numVictoryCard == supplyCount(duchy, &G));
    printf("province: %d == %d:       ", numVictoryCard, supplyCount(province, &G));
    assertTrue(numVictoryCard == supplyCount(province, &G));

    printf("*** Kingdom Cards: Expected == Actual ***\n");
    printf("adventurer: %d == %d:   ", numKingdomCards, supplyCount(adventurer, &G));
    assertTrue(numKingdomCards == supplyCount(adventurer, &G));
    printf("embargo: %d == %d:      ", numKingdomCards, supplyCount(embargo, &G));
    assertTrue(numKingdomCards == supplyCount(embargo, &G));
    printf("village: %d == %d:      ", numKingdomCards, supplyCount(village, &G));
    assertTrue(numKingdomCards == supplyCount(village, &G));    
    printf("minion: %d == %d:       ", numKingdomCards, supplyCount(minion, &G));
    assertTrue(numKingdomCards == supplyCount(minion, &G));
    printf("mine: %d == %d:         ", numKingdomCards, supplyCount(mine, &G));
    assertTrue(numKingdomCards == supplyCount(mine, &G));
    printf("cutpurse: %d == %d:     ", numKingdomCards, supplyCount(cutpurse, &G));
    assertTrue(numKingdomCards == supplyCount(cutpurse, &G));
    printf("sea_hag: %d == %d:      ", numKingdomCards, supplyCount(sea_hag, &G));
    assertTrue(numKingdomCards == supplyCount(sea_hag, &G));
    printf("tribute: %d == %d:      ", numKingdomCards, supplyCount(tribute, &G));
    assertTrue(numKingdomCards == supplyCount(tribute, &G));    
    printf("smithy: %d == %d:       ", numKingdomCards, supplyCount(smithy, &G));
    assertTrue(numKingdomCards == supplyCount(smithy, &G));
    printf("council_room: %d == %d: ", numKingdomCards, supplyCount(council_room, &G));
    assertTrue(numKingdomCards == supplyCount(council_room, &G));

	// ----------- TEST 2: Check after buying a card --------------
	printf("TEST 1: Check after buying a card\n");
    memcpy(&testG, &G, sizeof(struct gameState));
    buyCard(embargo, &testG);
    printf("embargo: %d == %d:        ", supplyCount(embargo, &G) - 1, supplyCount(embargo, &testG));
    assertTrue(supplyCount(embargo, &G) - 1 == supplyCount(embargo, &testG));

    return 0;
}