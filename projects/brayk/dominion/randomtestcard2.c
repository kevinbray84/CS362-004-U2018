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

#define TESTCARD "council room"
#define NUMTESTS 5000
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

int checkCouncilRoom(int card, int choice1, int choice2, int choice3, struct gameState *post, int handPos, int *bonus)
{
	struct gameState pre;
	int result;
	int player = post->whoseTurn;
	int foundError = 0;

	memcpy(&pre, post, sizeof(struct gameState));
	assert(memcmp(&pre, post, sizeof(struct gameState)) == 0);  // verify memory copied correctly

	result = cardEffect(card, choice1, choice2, choice3, post, handPos, bonus);
	
	// check function returned correctly
	assert(result == 0);

	// check that hand increased by 4
	if (pre.handCount[player] != post->handCount[player] - 4)
	{
		printf("ERROR handCount: Expected %d got %d\n", pre.handCount[player] + 4, post->handCount[player]);
		foundError++;
	}

	// check that deck is decreased by 4
	if (pre.deckCount[player] != post->deckCount[player] + 4)
	{
		printf("ERROR deckCount: Expected %d got %d\n", pre.deckCount[player] - 4, post->deckCount[player]);
		foundError++;
	}

	// check that numBuys increased by 1
	if (pre.numBuys + 1 != post->numBuys)
	{
		printf("ERROR numBuys: Expected %d got %d\n", pre.numBuys + 1, post->numBuys);
		foundError++;
	}

	for (int i = 0; i < pre.numPlayers; i++)
	{
		if (i != player) 
		{
			if (pre.handCount[i] + 1 != post->handCount[i])
			{
				printf("ERROR other player handCount: Expected %d got %d\n", pre.handCount[i] + 1,  post->handCount[i]);
				foundError++;
			}
		}
  }

	return foundError;
}


int main (int argc, char** argv)
{
	int card = council_room;
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
		G.playedCardCount = 0;

		for (int currentPlayer = 0; currentPlayer < G.numPlayers; ++currentPlayer)
		{
			G.deckCount[currentPlayer] = rand() % MAX_DECK / 2;
			G.handCount[currentPlayer] = rand() % MAX_HAND / 2;  // MAX_HAND = 500
			if (G.handCount[currentPlayer] < MIN_HAND)
			{
				G.handCount[currentPlayer] = MIN_HAND;   // enforce a minimum hand size
			}
			if (G.deckCount[currentPlayer] < MIN_DECK)
			{
				G.deckCount[currentPlayer] = MIN_DECK;   // enforce a minimum deck size
			}
			if (G.deckCount[currentPlayer] + G.handCount[currentPlayer] > MAX_DECK)
			{
				G.handCount[currentPlayer] = MAX_DECK - rand() % G.deckCount[currentPlayer];  // ensure sum of deck and hand are < MAX
			}

			G.discardCount[currentPlayer] = MAX_DECK - G.deckCount[currentPlayer] - G.handCount[currentPlayer];
			if (G.discardCount[currentPlayer] < 0) {G.discardCount[currentPlayer] = 0;}

			// there must be some treasures in the deck and discard, otherwise it adventurer loops for ever
			// some treasures must go into the discard or it will never shuffle
			while (countTreasures(G.deck[currentPlayer], G.deckCount[currentPlayer]) + countTreasures(G.discard[currentPlayer], G.discardCount[currentPlayer]) < MIN_TREASURES)
			{
				k = rand() % G.deckCount[currentPlayer];
				if (G.discardCount[currentPlayer] != 0)
				{
					m = rand() % G.discardCount[currentPlayer];
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
					if (G.deck[currentPlayer][k] != copper &&
						G.deck[currentPlayer][k] != silver &&
						G.deck[currentPlayer][k] != gold)
						{
							if (treasureRoll == 0) { G.deck[currentPlayer][k] = copper; }
							if (treasureRoll == 1) { G.deck[currentPlayer][k] = silver; }
							if (treasureRoll == 2) { G.deck[currentPlayer][k] = gold; }
							count++;
						}
				}
				else
				{
					if (G.discard[currentPlayer][m] != copper &&
						G.discard[currentPlayer][m] != silver &&
						G.discard[currentPlayer][m] != gold)
						{
							if (treasureRoll == 0) { G.discard[currentPlayer][m] = copper; }
							if (treasureRoll == 1) { G.discard[currentPlayer][m] = silver; }
							if (treasureRoll == 2) { G.discard[currentPlayer][m] = gold; }
							count++;
						}
				}
			};
		}

		// print test state
		// printf("**** TESTING ****\n");
		// printf("player: %d of %d\n", player + 1, G.numPlayers);
		// printf("deckCount: %d\n", G.deckCount[player]);
		// printf("discardCount: %d (%d total)\n", G.discardCount[player], G.deckCount[player] + G.discardCount[player] + G.handCount[player]);
		// printf("handCount: %d\n", G.handCount[player]);
		
		foundError += checkCouncilRoom(card, choice1, choice2, choice3, &G, handPos, &bonus);

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