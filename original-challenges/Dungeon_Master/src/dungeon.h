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

#define INVALID_MOVE -1
#define RESULT_WIN 1
#define RESULT_DIE 2
#define RESULT_QUIT 3

#define FLOOR_SYM '-'
#define WALL_SYM '|'
#define PLAYER_SYM 'R'
#define TREASURE_SYM '@'
#define BAT_SYM 'v'
#define ZOMBIE_SYM '&'
#define EMPTY_SYM ' '

#define FLOOR_NUM 1
#define WALL_NUM 2
#define PLAYER_NUM 3
#define TREASURE_NUM 4
#define BAT_NUM 5
#define ZOMBIE_NUM 6
#define EMPTY_NUM 7

#define EXTEND_MOVE 64

#define ROOM_WIDTH 24
#define ROOM_HEIGHT 9

// Make sure these are odd, or else a NULL will be sent with the string
#define VIEW_HEIGHT 13
#define VIEW_WIDTH 25

#define INVALID_OBJ_SYMBOL 11
#define OBJECT_NOT_FOUND_ERROR 12

#define JUMP_HEIGHT 2

#define DIR_LEFT 1
#define DIR_RIGHT 2
#define DIR_UP 3
#define DIR_DOWN 4

#define MAX_NAME_SIZE 50

#define SECRET_NUM 300

#define BAT_KILL_MSG "You were killed by a bat"
#define ZOMBIE_KILL_MSG "You were killed by a zombie"
#define MOVELIST_HDR "Move list: "
#define HIGHSCORE_MSG "Please enter your name: "
#define NO_SCORES_MSG "NO HIGH SCORES!\n"
#define HIGHSCORE_HDR "\n-------------------\n moves   |   name  \n-------------------\n"
#define MASTER_MSG "Dungeon conquered in !U moves !X"

#define FLAG_PAGE 0x4347C000

typedef struct {
	unsigned int x;
	unsigned int y;
} Coordinate;

typedef struct {
	char symbol;
	unsigned int id;
	Coordinate* position;
	Coordinate* direction;
	unsigned int moves;
} Object;

typedef struct {
	char quit;
	char left;
	char right;
	char jump;
	char jumpleft;
	char jumpright;
	char wait;
	char play;
	char instructions;
	char scores;
} Moves;

typedef struct {
	Object* contents[ROOM_HEIGHT][ROOM_WIDTH];
	void* next;
} Room;

typedef struct {
	char* name;
	unsigned int score;
	void* next;
} Score;

typedef struct {
	Moves moveTypes;
	Room* start;
	char* moveList;
	Score* highScores;
} Dungeon;

void buildDungeon(Dungeon* dungeon);
void destroyDungeon(Dungeon* dungeon);
void sendCurrentDungeonView(Room* start);
int isValidMove(Moves moves, char move);
int makeMove(Dungeon* dungeon, char move);
void playerWon(Dungeon* dungeon);
void playerDied(Dungeon dungeon);
Score* insertNewScore(Score* highScores, Score* newScore);


static const char first_room_string[ROOM_HEIGHT][ROOM_WIDTH] = 
{"------------------------",
 "|R                   v |",
 "|-                     |",
 "| -                   v|", 
 "|  -                   |", 
 "|   -                  |", 
 "|    -                 |",
 "|------&     --       -|", 
 "------------------------"};

static const char room_string[3][ROOM_HEIGHT][ROOM_WIDTH] = 
{
{"------------------------",
 "|                    v |",
 "|       --             |",
 "|     -     -          |", 
 "|            |        v|", 
 "|   -        |  -      |", 
 "             | -       |",
 "|------&     --&      -|", 
 "------------------------"},
 {"------------------------",
  "|&       &            v|",
  "|--------------  |-    |",
  "|                |     |", 
  "|---    ---------|     |", 
  "|   ---          |     |", 
  "       ---       |     |",
  "|                |&  --|", 
  "------------------------"},
 {"------------------------",
  "|                     @|",
  "|       -           ---|",
  "|     v- -        v-   |", 
  "|     -   -       -    |", 
  "|    -     -     -     |", 
  "    -       -   -      |",
  "|  &|       |&  |      |", 
  "------------------------"}
};
