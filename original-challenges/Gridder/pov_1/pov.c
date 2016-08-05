#include <libpov.h>

#define DEFAULT_DIFFICULTY 60
#define INITIAL_HARDEST_DIFFICULTY 50
#define EASIEST_DIFFICULTY 70
#define DEFAULT_boardSIZE 81

#define ROW(_idx) ((_idx)/(SET_SIZE))
#define COL(_idx) ((_idx)%(SET_SIZE))
#define SET(_num) ((_num)%(SET_SIZE)+1)

typedef int bool;
enum {
    true = 1,
    false = 0
};

enum {
    UNUSED = 0,
    USED = 1,
    SET_SUBSIZE = 3,
    SET_SIZE = SET_SUBSIZE * SET_SUBSIZE,
    NUM_CELLS = SET_SIZE * SET_SIZE,
    DIFFICULTY = 25,
    POOL_SIZE = 4096
};

enum CMD_IDS
{
    EXIT = 0,
    NEW_GRIDDER,
    ASK_DIFFICULTY,
    GIVE_UP,
    SOLVE_GRIDDER,
    CHANGE_DIFFICULTY,
    CHANGE_BOARDSIZE
};

enum MSGS
{
    EXITING = 100,
    SENDING_GRIDDER,
    RESPOND_DIFFICULTY,
    SENDING_SOLUTION,
    CORRECT_SOLUTION,
    DIFFICULTY_CHANGED,
    NOT_YET_IMPLEMENTED
};

enum ERRORS
{
    NO_ERRORS = 200,
    UNINITIALIZED_GRID,
    NOT_ENOUGH_DATA,
    BAD_SOLUTION,
    BAD_DIFFICULTY,
    NOT_UNLOCKED,
    BAD_boardSIZE,
    BAD_CMD_ID
};

unsigned int boardsize;
unsigned int cmd;
unsigned int msg;
unsigned int board[SET_SIZE][SET_SIZE];
unsigned int secret_value;

#define PRINTSTR(x) \
    do \
    { \
        char a[] = x; \
        transmit_all(STDERR, a, sizeof(x)-1); \
    } while(0)

#define PRINTLN() PRINTSTR("\n")

unsigned char buf[2000];

//void send_ack()
//{
//    transmit_all(STDOUT, &ACK, sizeof(ACK));
//}
//
//int recv_ack()
//{
//    return recv_command(ACK);
//}
//
//int send_ack_fin()
//{
//    transmit_all(STDOUT, &ACK, sizeof(ACK));
//    return recv_command(FIN);
//}
//
//int recv_ack_fin()
//{
//    if (recv_command(ACK) != 0)
//        return -1;
//    transmit_all(STDOUT, &FIN, sizeof(FIN));
//    return 0;
//}


bool valid_cell(int row, int col)
{
    int cell = board[row][col];
    for (int i = 0; i < SET_SIZE; i++)
        if ((row != i && cell == board[i][col]) || (col != i && cell == board[row][i]))
            return false;

    for (int r = (row/SET_SUBSIZE) * SET_SUBSIZE; r < ((row/SET_SUBSIZE) + 1) * SET_SUBSIZE; r++)
    {
        for (int c = (col/SET_SUBSIZE) * SET_SUBSIZE; c < ((col/SET_SUBSIZE) + 1) * SET_SUBSIZE; c++)
        {
            if (row == r && col == c)
                continue;

            if (cell == board[r][c])
                return false;
        }
    }
    return true;
}


unsigned int recv_msg()
{
    unsigned int _msg;
    length_read(STDIN, (unsigned char *)&_msg, sizeof(_msg));
    return _msg;
}

void recv_board()
{
    length_read(STDIN, (unsigned char *)&boardsize, sizeof(boardsize));
    length_read(STDIN, (unsigned char *)&board[0][0], sizeof(board));
}


void new_game()
{
    cmd = NEW_GRIDDER;
    transmit_all(STDOUT, (unsigned char *)&cmd, sizeof(cmd));
    msg = recv_msg();
    recv_board();
}

void submit()
{
    cmd = SOLVE_GRIDDER;
    transmit_all(STDOUT, (unsigned char *)&cmd, sizeof(cmd));
}

void exit_pov()
{
    cmd = EXIT;
    transmit_all(STDOUT, (unsigned char *)&cmd, sizeof(cmd));
    msg = recv_msg();
}

bool solve(int cell_idx)
{
    if (cell_idx == NUM_CELLS)
        return true;

    int row = ROW(cell_idx);
    int col = COL(cell_idx);
    if (board[row][col])
        return solve(cell_idx+1);

    for (int i = 1; i <= SET_SIZE; i++)
    {
        board[row][col] = i;
        if (valid_cell(row,col) && solve(cell_idx+1))
            return true;
    }

    board[row][col] = UNUSED;
    return false;
}


int main()
{
    type2_vals t2;
    type2_negotiate(&t2);

    new_game();
    solve(0);

    submit();
    unsigned int num_cells = (1<<16) + NUM_CELLS;
    transmit_all(STDOUT, &num_cells, sizeof(num_cells));
    transmit_all(STDOUT, &board[0][0], sizeof(board));
    transmit_all(STDOUT, &t2.region_addr, sizeof(t2.region_addr));
    msg = recv_msg();
    msg = recv_msg();

    type2_submit((unsigned char *)&msg, sizeof(msg));
    exit_pov();
    return 0;
}


