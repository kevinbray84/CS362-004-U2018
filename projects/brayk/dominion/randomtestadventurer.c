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
#define NUMTESTS 10000
#define MAX_CHOICE 3
#define MAX_HANDPOS 256
#define MAX_PLAYERS 4
#define MIN_TREASURES 3
#define MIN_DECK 3
#define MIN_HAND 5

int countTreasures(int *deck, int deckSize)
{
	int count = 0;
	for (int i = 0; i < deckSize; ++i)
	{
		if (deck[i] == copper || deck[i] == silver || deck[i] == gold)
			{
				count++;
			}
	}
	return count;
}

int checkAdventurer(int card, int choice1, int choice2, int choice3, struct gameState *post, int handPos, int *bonus)
{
	struct gameState pre;
	int result;
	int preTreasureCount;
	int postTreasureCount;
	int player = post->whoseTurn;
	int foundError = 0;

	memcpy(&pre, post, sizeof(struct gameState));
	assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);  // verify memory copied correctly

	result = cardEffect(card, choice1, choice2, choice3, post, handPos, bonus);
	
	// check function returned correctly
	assert(result == 0);

	// check that hand increased by 2
	if (pre.handCount[player] != post->handCount[player] - 2)
	{
		printf("ERROR handCount: Expected %d got %d\n", pre.handCount[player] + 2, post->handCount[player]);
		foundError++;
	}

    // check that the two new cards are treasure cards
	preTreasureCount = countTreasures(pre.hand[player], pre.handCount[player]);
	postTreasureCount = countTreasures(post->hand[player], post->handCount[player]);
	if (preTreasureCount != postTreasureCount - 2)
	{
		printf("ERROR treasureCount: Expected %d got %d\n", preTreasureCount + 2, postTreasureCount);
		foundError++;
	}

	return foundError;
}


int main (int argc, char** argv)
{
	int card = adventurer;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
    struct gameState G;
	int handPos = 0;
	int bonus = 0;
	int player;
	int m, k, whichDeck;
	int treasureRoll;
	int count = 0;
	int foundError = 0;

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
		G.numPlayers = rand() % MAX_PLAYERS + 1;
		if (G.numPlayers < 2)
		{
			G.numPlayers = 2;
		}
		player = rand() % G.numPlayers;
		G.whoseTurn = player;
		G.deckCount[player] = rand() % MAX_DECK / 2;
		G.handCount[player] = rand() % MAX_HAND / 2;  // MAX_HAND = 500
		if (G.handCount[player] < MIN_HAND)
		{
			G.handCount[player] = MIN_HAND;   // enforce a minimum hand size
		}
		if (G.deckCount[player] < MIN_DECK)
		{
			G.deckCount[player] = MIN_DECK;   // enforce a minimum deck size
		}
		if (G.deckCount[player] + G.handCount[player] > MAX_DECK)
		{
			G.handCount[player] = MAX_DECK - rand() % G.deckCount[player];  // ensure sum of deck and hand are < MAX
		}

		G.discardCount[player] = MAX_DECK - G.deckCount[player] - G.handCount[player];
		if (G.discardCount[player] < 0) {G.discardCount[player] = 0;}

		// there must be some treasures in the deck and discard, otherwise it adventurer loops for ever
		// some treasures must go into the discard or it will never shuffle
		while (countTreasures(G.deck[player], G.deckCount[player]) + countTreasures(G.discard[player], G.discardCount[player]) < MIN_TREASURES)
		{
			k = rand() % G.deckCount[player];
			if (G.discardCount[player] != 0)
			{
				m = rand() % G.discardCount[player];
				whichDeck = rand() % 2;   // determine if we put in discard pile or regular deck
			}
			else
			{
				m = 0;
				whichDeck = 0;
			}
			treasureRoll = rand() % 3;

			// put some treasures in the deck and some in the discard
			if (whichDeck == 0)
			{
				if (G.deck[player][k] != copper &&
					G.deck[player][k] != silver &&
					G.deck[player][k] != gold)
					{
						if (treasureRoll == 0) { G.deck[player][k] = copper; }
						if (treasureRoll == 1) { G.deck[player][k] = silver; }
						if (treasureRoll == 2) { G.deck[player][k] = gold; }
						count++;
					}
			}
			else
			{
				if (G.discard[player][m] != copper &&
					G.discard[player][m] != silver &&
					G.discard[player][m] != gold)
					{
						if (treasureRoll == 0) { G.discard[player][m] = copper; }
						if (treasureRoll == 1) { G.discard[player][m] = silver; }
						if (treasureRoll == 2) { G.discard[player][m] = gold; }
						count++;
					}
			}
		};

		// print test state
		// printf("**** TESTING ****\n");
		// printf("player: %d of %d\n", player + 1, G.numPlayers);
		// printf("deckCount: %d\n", G.deckCount[player]);
		// printf("discardCount: %d (%d total)\n", G.discardCount[player], G.deckCount[player] + G.discardCount[player] + G.handCount[player]);
		// printf("handCount: %d\n", G.handCount[player]);
		
		foundError += checkAdventurer(card, choice1, choice2, choice3, &G, handPos, &bonus);

	}

	printf("******************** %s testing complete ********************\n", TESTCARD);
	if (foundError)
	{
		printf("Found %d errors.  See log for details\n", foundError);
	}
	else
	{
		printf("SUCCESS - All tests successful\n");
	}

	return 0;
}