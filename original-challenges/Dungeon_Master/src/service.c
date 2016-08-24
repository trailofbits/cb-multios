/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include <libcgc.h>
#include "dungeon.h"
#include "cbstring.h"
#include "cbstdio.h"
#include "comms.h"
#include "malloc.h"

unsigned int flag_index = 0;
/**
 * Get a random name of length 10. String will contain upper and lower
 * case alpha characters.
 * @return      The address of the new random name
 */
char* getRandomName() {
	char* string;
	unsigned int idx=0;
	const unsigned char *randomBuffer = (const unsigned char*) FLAG_PAGE;

	if(!(string = malloc(11)))
		return NULL;

	bzero(string, 11);


	for(int c=0; c<10; c++) {
		unsigned int randomVal;

		randomVal = randomBuffer[c+flag_index];

		if(randomVal % 2 == 0) {
			string[c] = 'A' + randomBuffer[c+flag_index] % 26;
		} else {
				string[c] = 'a' + randomBuffer[c+flag_index] % 26;
		}

	}

	flag_index = (flag_index + 10) % 100;

	return string;
}

/**
* Get the next move from the player
* NOTE: The current view will only show a partial view of the dungeon
*       based on the players current position.
* 
* @param None
*
* @return A char representing the next move of the player
*/
char getMove() {
	char tmp[4];
	size_t bytes;
	bzero(tmp, 4);

	if(read_n_bytes(STDIN, tmp, 2, &bytes))
		_terminate(READ_ERROR);

	if(bytes)
		return tmp[0];

	return 0;

}

/**
* Send the player a description of the game, including instructions
* on how to play.
* NOTE: Characters representing moves are randomly generated and must
* be parsed from the directions to know how to move.
* 
* @param dungeon A copy of the dungeon structure
*
* @return None
*/
void sendGameDescription(Dungeon dungeon) {
	char buffer[1024];
	size_t len=0;
	int ret=0;

	bzero(buffer, 1024);
	sprintf(buffer, "Game moves\n----------\nLeft: !C\nRight: !C\nJump: !C\nJump Left: !C\nJump Right: !C\nWait: !C\nQuit game: !C\n",
					dungeon.moveTypes.left, dungeon.moveTypes.right, dungeon.moveTypes.jump, dungeon.moveTypes.jumpleft,
					dungeon.moveTypes.jumpright, dungeon.moveTypes.wait, dungeon.moveTypes.quit);

	len = strlen(buffer);
	if((ret = transmit_all(STDOUT, buffer, len)))
		_terminate(TRANSMIT_ERROR);
}

/**
* Send the player a description of the game, including instructions
* on how to navigate the menu.
* NOTE: Characters representing moves are randomly generated and must
* be parsed from the directions to know how to select menu options.
* 
* @param dungeon A copy of the dungeon structure
*
* @return None
*/
void sendMenuInstruction(Dungeon dungeon) {
	char buffer[1024];
	size_t len=0;
	int ret=0;

	bzero(buffer, 1024);
	sprintf(buffer, "Menu\n-----\nPlay game: !C\nGet instructions: !C\nHigh Scores: !C\nQuit game: !C\n",
			dungeon.moveTypes.play, dungeon.moveTypes.instructions, dungeon.moveTypes.scores, dungeon.moveTypes.quit);

	len = strlen(buffer);
	if((ret = transmit_all(STDOUT, buffer, len)))
		_terminate(TRANSMIT_ERROR);
}

/**
* Play the game
* 
* @param dungeon A pointer to the dungeon for this round of the game
*
* @return RESULT_WIN if the player has won the game
*         RESULT_DIE if the player has died in the game
*         else 0
*/
int playGame(Dungeon* dungeon) {
	char move=0;
	int result=0;

	sendCurrentDungeonView(dungeon->start);

	while(1) {
		move = getMove();
		if(move == dungeon->moveTypes.quit) {
			return RESULT_QUIT;
		} else {
			result = makeMove(dungeon, move);
			if(result == RESULT_WIN) {
				playerWon(dungeon);
				return RESULT_WIN;
			}
			else if (result == RESULT_DIE) {
				playerDied(*dungeon);
				return RESULT_DIE;
			}

		}
	}

	return 0;
}

/**
* Send a list of winners of the game and the number of moves they made
* 
* @param dungeon A pointer to the first score in the list
*
* @return None
*/
void sendHighScores(Score* scoreList) {
#ifdef PATCHED_2
	char buffer[sizeof(MASTER_MSG)+MAX_NAME_SIZE+10];
	bzero((char*)buffer, sizeof(MASTER_MSG)+MAX_NAME_SIZE+10);
#else
	char buffer[10+MAX_NAME_SIZE+1];
	bzero((char*)buffer, 10+MAX_NAME_SIZE+1);
#endif
	Score* highScore = scoreList;
	int num=2;

	if(!highScore) {

		if(transmit_all(STDOUT, NO_SCORES_MSG, strlen(NO_SCORES_MSG)))
			_terminate(TRANSMIT_ERROR);

		return;
	}

	sprintf((char*)buffer, MASTER_MSG, highScore->score, highScore->name);
	if(transmit_all(STDOUT, buffer, strlen((char*)buffer)))
			_terminate(TRANSMIT_ERROR);

	if(transmit_all(STDOUT, HIGHSCORE_HDR, strlen(HIGHSCORE_HDR)))
		_terminate(TRANSMIT_ERROR);

	for(Score* score=highScore->next; score!=NULL; score=score->next) {
#ifdef PATCHED_2
		bzero((char*)buffer, sizeof(MASTER_MSG)+MAX_NAME_SIZE+10);
#else
		bzero((char*)buffer, 10+MAX_NAME_SIZE+1);
#endif
		sprintf((char*)buffer, "!U. !U  !X\n", num, score->score, score->name);
		num++;
		if(transmit_all(STDOUT, buffer, strlen((char*)buffer)))
			_terminate(TRANSMIT_ERROR);		
	}
}

/**
* Add initial high scores to the list
* 
* @param dungeon A pointer to the first score in the list
*
* @return None
*/
void initScoreboard(Dungeon* dungeon) {
	Score* newScore;


	if(!(newScore = malloc(sizeof(Score)))) 
		_terminate(ALLOCATE_ERROR);
	bzero((char*)newScore, sizeof(Score));
	newScore->name = getRandomName();
	newScore->score = 600;
	newScore->next = NULL;
	dungeon->highScores = insertNewScore(dungeon->highScores, newScore);

	if(!(newScore = malloc(sizeof(Score)))) 
		_terminate(ALLOCATE_ERROR);
	bzero((char*)newScore, sizeof(Score));
	newScore->name = getRandomName();
	newScore->score = 601;
	newScore->next = NULL;
	dungeon->highScores = insertNewScore(dungeon->highScores, newScore);

	if(!(newScore = malloc(sizeof(Score)))) 
		_terminate(ALLOCATE_ERROR);
	bzero((char*)newScore, sizeof(Score));
	newScore->name = getRandomName();
	newScore->score = 999999;
	newScore->next = NULL;
	dungeon->highScores = insertNewScore(dungeon->highScores, newScore);
}


int main(void) {
Dungeon dungeon;
char move=0;
int result=0;

	buildDungeon(&dungeon);
	initScoreboard(&dungeon);

	while(1) {
		sendMenuInstruction(dungeon);		
		move = getMove();
		if(move == dungeon.moveTypes.play) {
			result = playGame(&dungeon);
			if(result == RESULT_QUIT)
				return 0;

			destroyDungeon(&dungeon);
			buildDungeon(&dungeon);
		} else if(move == dungeon.moveTypes.instructions) {
			sendGameDescription(dungeon);
		} else if(move == dungeon.moveTypes.scores) {
			sendHighScores(dungeon.highScores);
		} else if(move == dungeon.moveTypes.quit) {
			return 0;	
		}		
	}


	return 0;
}