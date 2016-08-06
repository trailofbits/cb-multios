#include <libcgc.h>
#include "mylibc.h"
#include "sample_shipgame.h"

//Simple protocol - 5 bytes followed by a newline
//Command - first letter //PARAMS - latter letters - 
static const char CMD_NEW = 'N'; //N.... -- only first character is looked at
static const char CMD_PLACE = 'P'; //Prcd1 -- 1 is the ship number, r is Row, C is Column, d is direction (Up or Down)
static const char CMD_START = 'S'; //S....
static const char CMD_MAP = 'M'; //M....
static const char CMD_EXIT = 'E'; //E.... 
static const char CMD_TARGET = 'T'; //Trc.. -- targets row and column
static const char CMD_HELP = 'H'; //H....
static const char CMD_UNKNOWN = 'U'; //U....

static const char SHIP2 = '2';
static const char SHIP3 = '3';
static const char SHIP4 = '4';
static const char SHIP5 = '5';
static const char EMPTY_CELL = '.';
static const char HIT_CELL = 'X';

static const char DIR_R = 'R';
static const char DIR_D = 'D';

static const char ROW_BASE = '0';
static const char COL_BASE = 'A';

const char* SHIP2_SUNK_MSG = "You have sunk my SHIP 2\n";
const char* SHIP3_SUNK_MSG = "You have sunk my SHIP 3\n";
const char* SHIP4_SUNK_MSG = "You have sunk my SHIP 4\n";
const char* SHIP5_SUNK_MSG = "You have sunk my SHIP 5\n";
const char* MISSED_MSG = "You missed\n";
const char* HIT_MSG = "OUCH!!\n";

const char* BAD_COMMAND_MSG = "Bad Command - Try again\n";
const char* GAME_ALREADY_STARTED_MSG = "Game already started - try to hit something\n";
const char* GAME_NOT_STARTED_MSG = "Game not started yet\n";
const char* HELP_MSG = "Sorry, I am not very helpful\n";
const char* YOU_WIN_MSG = "You win. Congrats\n";
const char* GAME_ALREADY_ENDED_MSG = "Game ended already. Try a new one\n";
const char* EXIT_MSG = "You are stuck...\n";
const char* READ_ERROR_MSG = "ERROR reading from user -- time to die\n";

const char* P0_PROMPT = "Player1:$ ";
const char* P1_PROMPT = "Player2:$ ";

#define ROW_TO_NUM(_x) (_x - ROW_BASE)
#define COL_TO_NUM(_x) (_x - COL_BASE)


/***********************************************************/
/**               shipgame related functions              **/
/***********************************************************/

int getCommand(Command* cmd)
{
  int ret = 0;

  char buf[512]; //overflow me please
  buf[0] = '\0';

  if (cmd == NULL)
  {
    return (-1);
  }
  
  ret = readLine(STDIN, buf, 512); 
  if (ret < 0)
  {
    return (-2); //-2 is 
  }

  //now that we have a command - lets parse it out
  //unrolling the switch statement so we can link things back up to the 
  //global - characters

  if (buf[0] == CMD_NEW)
  {
    cmd->cmdNum = CMD_NEW;
  }
  else if (buf[0] == CMD_PLACE)
  {
    cmd->cmdNum = CMD_PLACE;
    //no loop here
    cmd->row = buf[1];
    cmd->col = buf[2];
    cmd->dir = buf[3]; 
    cmd->shipNum = buf[4];
  }
  else if (buf[0] == CMD_TARGET)
  {
    cmd->cmdNum = CMD_TARGET;
    cmd->row = buf[1];
    cmd->col = buf[2];
  }
  else if (buf[0] == CMD_MAP)
  {
    cmd->cmdNum = CMD_MAP;
  }
  else if (buf[0] == CMD_EXIT)
  {
    cmd->cmdNum = CMD_EXIT;
  }
  else if (buf[0] == CMD_HELP)
  {
    cmd->cmdNum = CMD_HELP;
  }
  else if (buf[0] == CMD_START)
  {
    cmd->cmdNum = CMD_START;
  }
  else
  {
    cmd->cmdNum = CMD_UNKNOWN;
    return (-1);
  }

  return (0);
}

int dumpBoard(PlayerState* ps)
{
  int i = 0;
  int j = 0;
  char tempStr[8];

  if (ps == NULL)
  {
    return (-1);
  }

  for (i = 0; i < BOARD_SIZE; i++)
  {
    if (i == 0)
    {
      tempStr[0] = '\t';
      tempStr[1] = COL_BASE;
      write(STDOUT, tempStr, 2);
    }
    else
    {
      //this will mess up if i > 26
      tempStr[0] = COL_BASE + (char)i;
      write(STDOUT, tempStr, 1);
    }
  }
  tempStr[0] = '\n';
  write(STDOUT, tempStr, 1);

  for (i = 0; i < BOARD_SIZE; i++)
  {
    tempStr[0] = ' ';
    tempStr[1] = ' ';
    tempStr[2] = ' ';
    tempStr[3] = ROW_BASE + (char)i;
    tempStr[4] = ':';
    tempStr[5] = '\t';
    write(STDOUT, tempStr, 6);

    for (j = 0; j < BOARD_SIZE; j++)
    {
      tempStr[0] = ps->board[i][j];
      write(STDOUT, tempStr, 1);
    }
  
    tempStr[0] = '\n';
    write(STDOUT, tempStr, 1);
  }
  return (0);
}

int clearPlayerState(PlayerState* ps)
{
  int i = 0; 
  int j = 0;

  if (ps == NULL)
  {
    return (-1);
  }
  
  for (i = 0; i < BOARD_SIZE; i++)
  { 
    for (j = 0; j < BOARD_SIZE; j++)
    {
      ps->board[i][j] = EMPTY_CELL;
    }
  }

  ps->ship2Life = 0; //these are life points
  ps->ship3Life = 0;
  ps->ship4Life = 0;
  ps->ship5Life = 0;

  return (0);
}

static inline int isGoodRow(char c)
{
  return ( (c >= ROW_BASE) && (c <= (ROW_BASE + BOARD_SIZE - 1)) );
}

static inline int isGoodCol(char c)
{
  return ( (c >= COL_BASE) && (c <= (COL_BASE + BOARD_SIZE - 1)) );
}

//assumes that r and c are good
static inline int isOnBoard(char r, char c, char d, int num)
{
  if ( d == DIR_R )
  {
    if ( (c - COL_BASE + num) <= BOARD_SIZE )
    {
      return (1);
    }
  }
  if (d == DIR_D )
  {
    if ( (r - ROW_BASE + num) <= BOARD_SIZE )
    {
      return (1);
    }
  }
  return (0);
}

int processPlace(PlayerState* ps, Command* cmd)
{
  if ( (ps == NULL) || (cmd == NULL) )
  {
    return (-1);
  }

  //check and convert the row and column fields
  if ( !isGoodRow(cmd->row) || !isGoodCol(cmd->col) )
  {
    return (-1);
  }

  //yes more non-switch statements
  if (cmd->shipNum == SHIP2)
  {
    //if its outside of the board area then error
    if (!isOnBoard(cmd->row, cmd->col, cmd->dir, 2) || (ps->ship2Life > 0))
    {
      return (-1);
    }

    //if the slots are already taken -- error 
    if (cmd->dir == DIR_R)
    {
      if ( (ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col)] != EMPTY_CELL) 
           || ( ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col) + 1] != EMPTY_CELL)
         )
      {
        return (-1);
      }

      ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col)] = cmd->shipNum;
      ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col) + 1] = cmd->shipNum;
      //We can totally go overboard and assign this to be cmd->shipNum as well
      ps->ship2Life = 2;
    }
    else if (cmd->dir == DIR_D)
    {
      if ( (ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col)] != EMPTY_CELL) 
           || ( ps->board[ROW_TO_NUM(cmd->row) + 1][COL_TO_NUM(cmd->col)] != EMPTY_CELL)
         )
      {
        return (-1);
      }

      ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col)] = cmd->shipNum;
      ps->board[ROW_TO_NUM(cmd->row) + 1][COL_TO_NUM(cmd->col)] = cmd->shipNum;
      ps->ship2Life = 2;
    }
    else
    {
      //should never be here in this else
      return (-1);
    }
  }
  else if (cmd->shipNum == SHIP3)
  {
    if (!isOnBoard(cmd->row, cmd->col, cmd->dir, 3) || (ps->ship3Life > 0))
    {
      return (-1);
    }
      
    //if the slots are already taken -- error 
    if (cmd->dir == DIR_R)
    {
      if ( (ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col)] != EMPTY_CELL) 
           || ( ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col) + 1] != EMPTY_CELL)
           || ( ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col) + 2] != EMPTY_CELL)
         )
      {
        return (-1);
      }

      ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col)] = cmd->shipNum;
      ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col) + 1] = cmd->shipNum;
      ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col) + 2] = cmd->shipNum;
      ps->ship3Life = 3;
    }
    else if (cmd->dir == DIR_D)
    {
      if ( (ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col)] != EMPTY_CELL) 
           || ( ps->board[ROW_TO_NUM(cmd->row) + 1][COL_TO_NUM(cmd->col)] != EMPTY_CELL)
           || ( ps->board[ROW_TO_NUM(cmd->row) + 2][COL_TO_NUM(cmd->col)] != EMPTY_CELL)
         )
      {
        return (-1);
      }

      ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col)] = cmd->shipNum;
      ps->board[ROW_TO_NUM(cmd->row) + 1][COL_TO_NUM(cmd->col)] = cmd->shipNum;
      ps->board[ROW_TO_NUM(cmd->row) + 2][COL_TO_NUM(cmd->col)] = cmd->shipNum;
      ps->ship3Life = 3;
    }
    else
    {
      //should never be here in this else
      return (-1);
    }
  }
  else if (cmd->shipNum == SHIP4)
  {
    if (!isOnBoard(cmd->row, cmd->col, cmd->dir, 4) || (ps->ship4Life > 0))
    {
      return (-1);
    }
 
    //if the slots are already taken -- error 
    if (cmd->dir == DIR_R)
    {
      if ( (ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col)] != EMPTY_CELL) 
           || ( ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col) + 1] != EMPTY_CELL)
           || ( ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col) + 2] != EMPTY_CELL)
           || ( ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col) + 3] != EMPTY_CELL)
         )
      {
        return (-1);
      }

      ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col)] = cmd->shipNum;
      ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col) + 1] = cmd->shipNum;
      ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col) + 2] = cmd->shipNum;
      ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col) + 3] = cmd->shipNum;
      ps->ship4Life = 4;
    }
    else if (cmd->dir == DIR_D)
    {
      if ( (ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col)] != EMPTY_CELL) 
           || ( ps->board[ROW_TO_NUM(cmd->row) + 1][COL_TO_NUM(cmd->col)] != EMPTY_CELL)
           || ( ps->board[ROW_TO_NUM(cmd->row) + 2][COL_TO_NUM(cmd->col)] != EMPTY_CELL)
           || ( ps->board[ROW_TO_NUM(cmd->row) + 3][COL_TO_NUM(cmd->col)] != EMPTY_CELL)
         )
      {
        return (-1);
      }

      ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col)] = cmd->shipNum;
      ps->board[ROW_TO_NUM(cmd->row) + 1][COL_TO_NUM(cmd->col)] = cmd->shipNum;
      ps->board[ROW_TO_NUM(cmd->row) + 2][COL_TO_NUM(cmd->col)] = cmd->shipNum;
      ps->board[ROW_TO_NUM(cmd->row) + 3][COL_TO_NUM(cmd->col)] = cmd->shipNum;
      ps->ship4Life = 4;
    }
    else
    {
      //should never be here in this else
      return (-1);
    }
 
  }
  else if (cmd->shipNum == SHIP5)
  {
    if (!isOnBoard(cmd->row, cmd->col, cmd->dir, 5) || (ps->ship5Life > 0))
    {
      return (-1);
    }

    //if the slots are already taken -- error 
    if (cmd->dir == DIR_R)
    {
      if ( (ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col)] != EMPTY_CELL) 
           || ( ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col) + 1] != EMPTY_CELL)
           || ( ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col) + 2] != EMPTY_CELL)
           || ( ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col) + 3] != EMPTY_CELL)
           || ( ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col) + 4] != EMPTY_CELL)
         )
      {
        return (-1);
      }

      ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col)] = cmd->shipNum;
      ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col) + 1] = cmd->shipNum;
      ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col) + 2] = cmd->shipNum;
      ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col) + 3] = cmd->shipNum;
      ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col) + 4] = cmd->shipNum;
      ps->ship5Life = 5;
    }
    else if (cmd->dir == DIR_D)
    {
      if ( (ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col)] != EMPTY_CELL) 
          || ( ps->board[ROW_TO_NUM(cmd->row) + 1][COL_TO_NUM(cmd->col)] != EMPTY_CELL)
          || ( ps->board[ROW_TO_NUM(cmd->row) + 2][COL_TO_NUM(cmd->col)] != EMPTY_CELL)
          || ( ps->board[ROW_TO_NUM(cmd->row) + 3][COL_TO_NUM(cmd->col)] != EMPTY_CELL)
          || ( ps->board[ROW_TO_NUM(cmd->row) + 4][COL_TO_NUM(cmd->col)] != EMPTY_CELL)
         )
      {
        return (-1);
      }

      ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col)] = cmd->shipNum;
      ps->board[ROW_TO_NUM(cmd->row) + 1][COL_TO_NUM(cmd->col)] = cmd->shipNum;
      ps->board[ROW_TO_NUM(cmd->row) + 2][COL_TO_NUM(cmd->col)] = cmd->shipNum;
      ps->board[ROW_TO_NUM(cmd->row) + 3][COL_TO_NUM(cmd->col)] = cmd->shipNum;
      ps->board[ROW_TO_NUM(cmd->row) + 4][COL_TO_NUM(cmd->col)] = cmd->shipNum;
      ps->ship5Life = 5;
    }
    else
    {
      //should never be here in this else
      return (-1);
    }
  }  
  else
  {
    return (-1);
  }

  return (0);
}

int processTarget(PlayerState* ps, Command* cmd)
{
  if ( (ps == NULL) || (cmd == NULL) )
  {
    return (-1);
  }

  //check and convert the row and column fields
  if ( !isGoodRow(cmd->row) || !isGoodCol(cmd->col) )
  {
    return (-1);
  }

  //should I make this extremely explicit?
  if ( ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col)] == SHIP2 )
  {
    ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col)] = HIT_CELL;
    ps->ship2Life--;
    write(STDOUT, HIT_MSG, myStrLen(HIT_MSG));
    if (ps->ship2Life == 0)
    {
      write(STDOUT, SHIP2_SUNK_MSG, myStrLen(SHIP2_SUNK_MSG));
    }
  }
  else if ( ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col)] == SHIP3 )
  {
    ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col)] = HIT_CELL;
    ps->ship3Life--;
    write(STDOUT, HIT_MSG, myStrLen(HIT_MSG));
    if (ps->ship3Life == 0)
    {
      write(STDOUT, SHIP3_SUNK_MSG, myStrLen(SHIP3_SUNK_MSG));
    }
  }
  else if ( ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col)] == SHIP4 )
  {
    ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col)] = HIT_CELL;
    ps->ship4Life--;
    write(STDOUT, HIT_MSG, myStrLen(HIT_MSG));
    if (ps->ship4Life == 0)
    {
      write(STDOUT, SHIP4_SUNK_MSG, myStrLen(SHIP4_SUNK_MSG));
    }
  }
  else if ( ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col)] == SHIP5 )
  {
    ps->board[ROW_TO_NUM(cmd->row)][COL_TO_NUM(cmd->col)] = HIT_CELL;
    ps->ship5Life--;
    write(STDOUT, HIT_MSG, myStrLen(HIT_MSG));
    if (ps->ship5Life == 0)
    {
      write(STDOUT, SHIP5_SUNK_MSG, myStrLen(SHIP5_SUNK_MSG));
    }
  }
  else
  {
    write(STDOUT, MISSED_MSG, myStrLen(MISSED_MSG));
  }

  return (0);
}

static inline int allShipsSunk(PlayerState* ps)
{
  if (ps == NULL)
  {
    return (0);
  }
 
  return ( (ps->ship2Life == 0)
           && (ps->ship3Life == 0)
           && (ps->ship4Life == 0)
           && (ps->ship5Life == 0)
         ); 
}

int main(void)
{

  PlayerState player0, player1; //2 players
  int ret = 0;
  int curPlayer = 0;
  int bStarted = 0;
  int bEnded = 0;
  Command cmd;

  //initialize
  cmd.cmdNum = CMD_UNKNOWN;
  clearPlayerState(&player0);
  clearPlayerState(&player1);

  while(1)
  {
    if (curPlayer == 0)
    {
      write(STDOUT, P0_PROMPT, myStrLen(P0_PROMPT)); 
    }
    else
    {
      write(STDOUT, P1_PROMPT, myStrLen(P1_PROMPT)); 
    }

    ret = getCommand(&cmd);

    if (ret == 0) //if its okay
    {
      if (cmd.cmdNum == CMD_EXIT)
      {
        write(STDOUT, EXIT_MSG, myStrLen(EXIT_MSG)); 
        //break;
      }
      else if (cmd.cmdNum == CMD_NEW)
      {
        cmd.cmdNum = CMD_UNKNOWN;
        clearPlayerState(&player0);
        clearPlayerState(&player1);
        curPlayer = 0;
        bStarted = 0;
        bEnded = 0;
        continue;
      }
      else if (cmd.cmdNum == CMD_HELP)
      {
        write(STDOUT, HELP_MSG, myStrLen(HELP_MSG));
      }
      else if (bEnded)
      {
        write(STDOUT, GAME_ALREADY_ENDED_MSG, myStrLen(GAME_ALREADY_ENDED_MSG));
      }
      else if (cmd.cmdNum == CMD_MAP)
      { 
        if (curPlayer == 0)
        {
          dumpBoard(&player0);
        }
        else
        {
          dumpBoard(&player1);
        }
      }
      else if (cmd.cmdNum == CMD_START)
      {
        if (bStarted)
        {
          write(STDOUT, GAME_ALREADY_STARTED_MSG, myStrLen(GAME_ALREADY_STARTED_MSG));
        }
        else
        {
          bStarted = 1;
        }
      }
      else if (cmd.cmdNum == CMD_PLACE)
      {
        if (bStarted)
        {
          write(STDOUT, GAME_ALREADY_STARTED_MSG, myStrLen(GAME_ALREADY_STARTED_MSG));
        }
        else
        {
          if (curPlayer == 0)
          {
            ret = processPlace(&player0, &cmd);
          }
          else
          {
            ret = processPlace(&player1, &cmd);
          }

          if (ret == 0)
          {
            //swap players
            curPlayer = (curPlayer == 0) ? 1 : 0;
          }
          else
          {
            write(STDOUT, BAD_COMMAND_MSG, myStrLen(BAD_COMMAND_MSG));
          }
        }
      }
      else if (cmd.cmdNum == CMD_TARGET)
      {
        if (!bStarted)
        {
          write(STDOUT, GAME_NOT_STARTED_MSG, myStrLen(GAME_NOT_STARTED_MSG));
        }
        else
        {
          if (curPlayer == 0)
          {
            ret = processTarget(&player1, &cmd);
          }
          else
          {
            ret = processTarget(&player0, &cmd);
          }

          if (ret == 0)
          {
            //see if the current player won
            if (curPlayer == 0)
            {
              if (allShipsSunk(&player1))
              {
                write(STDOUT, YOU_WIN_MSG, myStrLen(YOU_WIN_MSG));
                bStarted = 0;
                bEnded = 1;
              }
            }
            else
            {
              if (allShipsSunk(&player0))
              {
                write(STDOUT, YOU_WIN_MSG, myStrLen(YOU_WIN_MSG));
                bStarted = 0;
                bEnded = 1;
              }
            }

            //swap players
            curPlayer = (curPlayer == 0) ? 1 : 0;
          }
          else
          {
            write(STDOUT, BAD_COMMAND_MSG, myStrLen(BAD_COMMAND_MSG));
          }
        }
      }
    }    
    else if (ret == -1)
    {
      write(STDOUT, BAD_COMMAND_MSG, myStrLen(BAD_COMMAND_MSG));
    }
    else if (ret == -2) //read error
    {
      write(STDOUT, READ_ERROR_MSG, myStrLen(READ_ERROR_MSG));
      break;
    }
  }

  return (0);
}

