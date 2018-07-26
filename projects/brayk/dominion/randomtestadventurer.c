#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include "interface.h"
#include <time.h>
#include <math.h>

#define TESTCARD "adventurer"
#define NUMTESTS 10000000
#define MAX_CHOICE 3
#define MAX_HANDPOS 256
#define MAX_PLAYERS 4
#define MIN_TREASURES 3
#define MIN_DECK 3

// struct gameState {
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

int countTreasures(int *deck, int deckSize)
{
	int count = 0;
	for (int i = 0; i < deckSize; ++i)
	{
		if (deck[i] == copper ||
		    deck[i] == silver ||
			deck[i] == gold)
			{
				count++;
			}
	}
	return count;
}

int checkAdventurer(int card, int choice1, int choice2, int choice3, struct gameState *post, int handPos, int *bonus, int player)
{
	struct gameState pre;
	int result;
	int preTreasureCount;
	int postTreasureCount;

	memcpy(&pre, post, sizeof(struct gameState));
	assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);  // verify memory copied correctly

    // check that tehre was no change to player 2
    // check that there was no change to kingdom or treasure decks

	result = cardEffect(card, choice1, choice2, choice3, post, handPos, bonus);
	
	// check function returned correctly
	assert(result == 0);

	// check that hand increased by 2
	if (pre.handCount[player] != post->handCount[player] - 2)
	{
		printf("ERROR handCount: Expected %d got %d\n", pre.handCount[player], post->handCount[player]);
	}


    // check that the two new cards are treasure cards
	preTreasureCount = countTreasures(pre.hand[player], pre.handCount[player]);
	postTreasureCount = countTreasures(post->hand[player], post->handCount[player]);
	if (preTreasureCount != postTreasureCount - 2)
	{
		printf("ERROR treasureCount: Expected %d got %d\n", preTreasureCount, postTreasureCount);
	}

	// check that tehre was no change to other players
	for (int i = 0; i < MAX_PLAYERS; ++i)
	{
		if (memcmp(pre.hand[i], post->hand[i], sizeof(pre.handCount[i])) != 0)
		{
			printf("ERROR %d: Hand value mismatch\n", i);
		}
	}


	return 0;
}

// void printDeck(struct gameState *G)
// {
// 	printf("Deck size %d: ", G.deckCount[G.whoseTurn]);
// 	for (int i = 0; i < G.deckCount[G.whoseTurn]; ++i)
// 	{
// 		printf("%d ", G.deck[G.whoseTurn][i]);
// 	}
// 	printf("\n***********************************\n");
// }



int main (int argc, char** argv)
{
	//int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
	//		sea_hag, tribute, smithy, council_room};
	int card = adventurer;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
    struct gameState G;
	int handPos = 0;
	int bonus = 0;
	int player;
	int k;
	int treasureRoll;
	int count = 0;

	srand(time(NULL));

	// generate random values
	for (int i = 0; i < NUMTESTS; ++i)
	{
		choice1 = floor(Random() * MAX_CHOICE);
		choice2 = floor(Random() * MAX_CHOICE);
		choice3 = floor(Random() * MAX_CHOICE);
		for (int j = 0; j < sizeof(struct gameState); ++j)
		{
			((char*)&G)[j] = floor(Random() * 256);
		}
		G.numPlayers = floor(Random() * MAX_PLAYERS);
		player = rand() % MAX_PLAYERS;
		G.whoseTurn = player;
		G.deckCount[player] = rand() % MAX_DECK;
		if (G.deckCount[player] < MIN_DECK)
		{
			G.deckCount[player] = MIN_DECK;   // enforce a minimum deck size
		}
		G.discardCount[player] = 0; //rand() % MAX_DECK * 2;

		// TODO:  enforce a minimum here
		G.handCount[player] = rand() % MAX_HAND;  // MAX_HAND = 500
		if (G.handCount[player] < 5)
		{
			G.handCount[player] = 5;   // enforce a minimum hand size
		}
		// if (G.handCount[player] > MAX_HAND - G.handCount[player])
		// {
		// 	G.handCount[player] = MAX_HAND - G.handCount[player];   // enforce a minimum deck size
		// }
		// G.handCount[player] = 5;
		// put at least MIN_TREASURES in random places in the player's
		//printDeck(player, &G);
		while (countTreasures(G.deck[player], G.deckCount[player]) < MIN_TREASURES)
		{
			k = rand() % G.deckCount[player];
			treasureRoll = rand() % 3;
			if (G.deck[player][k] != copper &&
			    G.deck[player][k] != silver &&
				G.deck[player][k] != gold)
				{
					if (treasureRoll == 0) { G.deck[player][k] = copper; }
					if (treasureRoll == 1) { G.deck[player][k] = silver; }
					if (treasureRoll == 2) { G.deck[player][k] = gold; }
					count++;
				}
		};

		// printf("Deck size %d, treasures %d, handCount: %d\n", G.deckCount[player], countTreasures(G.deck[player], G.deckCount[player]), G.handCount[player]);
		// for (int i = 0; i < G.deckCount[player]; ++i)
		// {
		// 	printf("%d ", G.deck[player][i]);
		// }
		// printf("\n***********************************\n");
		// printDeck(player, &G);

		checkAdventurer(card, choice1, choice2, choice3, &G, handPos, &bonus, player);
	}

	return 0;
}