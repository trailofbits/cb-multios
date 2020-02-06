#ifndef SAMPLE_SHIPGAME_H
#define SAMPLE_SHIPGAME_H

//doesn't work for other sizes
#define BOARD_SIZE 10

#if (BOARD_SIZE != 10)
#warn "Only tested for board size of 10"
#endif

typedef struct _Command
{
  char cmdNum;
  //changed from the array into individual 
  char row;
  char col;
  char dir; 
  char shipNum;
}Command;

typedef struct _PlayerState
{
  int playerNum; //player number
  int ship2Life; //these are life points
  int ship3Life;
  int ship4Life;
  int ship5Life;
  char board[BOARD_SIZE][BOARD_SIZE]; //the board itself
} PlayerState;

int cgc_getCommand(Command* cmd);

int cgc_clearPlayerState(PlayerState* ps);

int cgc_dumpBoard(PlayerState* ps);

int cgc_processPlace(PlayerState* ps, Command* cmd);
int cgc_processTarget(PlayerState* ps, Command* cmd);

int printHelp();
#endif//SAMPLE_SHIPGAME_H
