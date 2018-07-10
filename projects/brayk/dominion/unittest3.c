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
    int curseCost = 0;
    int estateCost = 2;
    int duchyCost = 5;
    int provinceCost = 8;
    int copperCost = 0;
    int silverCost = 3;
    int goldCost = 6;
    int adventurerCost = 6;
    int council_roomCost = 5;
    int feastCost = 4;
    int gardensCost = 4;
    int mineCost = 5;
    int remodelCost = 4;
    int smithyCost = 4;
    int villageCost = 3;
    int baronCost = 4;
    int great_hallCost = 3;
    int minionCost = 5;
    int stewardCost = 3;
    int tributeCost = 5;
    int ambassadorCost = 3;
    int cutpurseCost = 4;
    int embargoCost =  2;
    int outpostCost = 5;
    int salvagerCost = 4;
    int sea_hagCost = 4;
    int treasure_mapCost = 4;

    int seed = 1000;
    int numPlayers = 2;
	struct gameState G;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &G);

	// ----------- TEST 1: Check each value --------------
	printf("********* Testing getCost(): Expected == Actual? *********\n");

    printf("curse: %d == %d:        ", curseCost, getCost(curse));
    assertTrue(curseCost ==  getCost(curse));

    printf("estate: %d == %d:       ", estateCost, getCost(estate));
    assertTrue(estateCost ==  getCost(estate));    

    printf("duchy: %d == %d:        ", duchyCost, getCost(duchy));
    assertTrue(duchyCost ==  getCost(duchy));

    printf("province: %d == %d:     ", provinceCost, getCost(province));
    assertTrue(provinceCost ==  getCost(province));

    printf("province: %d == %d:     ", provinceCost, getCost(province));
    assertTrue(copperCost ==  getCost(copper));  

    printf("copper: %d == %d:       ", copperCost, getCost(copper));
    assertTrue(copperCost ==  getCost(copper));

    printf("silver: %d == %d:       ", silverCost, getCost(silver));
    assertTrue(silverCost ==  getCost(silver));

    printf("gold: %d == %d:         ", goldCost, getCost(gold));
    assertTrue(goldCost ==  getCost(gold));  

    printf("adventurer: %d == %d:   ", adventurerCost, getCost(adventurer));
    assertTrue(adventurerCost ==  getCost(adventurer));

    printf("council_room: %d == %d: ", council_roomCost, getCost(council_room));
    assertTrue(council_roomCost ==  getCost(council_room));

    printf("feast: %d == %d:        ", feastCost, getCost(feast));
    assertTrue(feastCost ==  getCost(feast));   

    printf("gardens: %d == %d:      ", gardensCost, getCost(gardens));
    assertTrue(gardensCost ==  getCost(gardens));

    printf("mine: %d == %d:         ", mineCost, getCost(mine));
    assertTrue(mineCost ==  getCost(mine));

    printf("remodel: %d == %d:      ", remodelCost, getCost(remodel));
    assertTrue(remodelCost ==  getCost(remodel));    

    printf("smithy: %d == %d:       ", smithyCost, getCost(smithy));
    assertTrue(smithyCost ==  getCost(smithy));

    printf("village: %d == %d:      ", villageCost, getCost(village));
    assertTrue(villageCost ==  getCost(village));

    printf("baron: %d == %d:        ", baronCost, getCost(baron));
    assertTrue(baronCost ==  getCost(baron));    

    printf("great_hall: %d == %d:   ", great_hallCost, getCost(great_hall));
    assertTrue(great_hallCost ==  getCost(great_hall));

    printf("minion: %d == %d:       ", minionCost, getCost(minion));
    assertTrue(minionCost ==  getCost(minion));

    printf("steward: %d == %d:      ", stewardCost, getCost(steward));
    assertTrue(stewardCost ==  getCost(steward));    

    printf("tribute: %d == %d:      ", tributeCost, getCost(tribute));
    assertTrue(tributeCost ==  getCost(tribute));

    printf("ambassador: %d == %d:   ", ambassadorCost, getCost(ambassador));
    assertTrue(ambassadorCost ==  getCost(ambassador));

    printf("cutpurse: %d == %d:     ", cutpurseCost, getCost(cutpurse));
    assertTrue(cutpurseCost ==  getCost(cutpurse));  

    printf("embargo: %d == %d:      ", embargoCost, getCost(embargo));
    assertTrue(embargoCost ==  getCost(embargo));

    printf("outpost: %d == %d:      ", outpostCost, getCost(outpost));
    assertTrue(outpostCost ==  getCost(outpost)); 

    printf("salvager: %d == %d:     ", salvagerCost, getCost(salvager));
    assertTrue(salvagerCost ==  getCost(salvager));

    printf("sea_hag: %d == %d:      ", sea_hagCost, getCost(sea_hag));
    assertTrue(sea_hagCost ==  getCost(sea_hag)); 

    printf("treasure_map: %d == %d: ", treasure_mapCost, getCost(treasure_map));
    assertTrue(treasure_mapCost ==  getCost(treasure_map));

    return 0;
}