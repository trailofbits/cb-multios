/*
 * Copyright (c) 2016 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#include <cstring.h>
#include <cstdio.h>
#include "gridder.h"
#include "num_gen.h"
#include "enums.h"

#define DEFAULT_DIFFICULTY 40
#define INITIAL_HARDEST_DIFFICULTY 40
#define EASIEST_DIFFICULTY 50
#define DEFAULT_BOARD_SIZE 81

enum CMD_IDS
{
    EXIT = 0,
    NEW_GRIDDER,
    ASK_DIFFICULTY,
    GIVE_UP,
    SOLVE_GRIDDER,
    CHANGE_DIFFICULTY,
    CHANGE_BOARD_SIZE
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
    BAD_BOARD_SIZE,
    BAD_CMD_ID
};


unsigned int g_msgs_table[] =
{
    EXITING,
    SENDING_GRIDDER,
    RESPOND_DIFFICULTY,
    SENDING_SOLUTION,
    CORRECT_SOLUTION,
    DIFFICULTY_CHANGED,
    NOT_YET_IMPLEMENTED
};

unsigned int g_error_table[]
{
    NO_ERRORS,
    UNINITIALIZED_GRID,
    NOT_ENOUGH_DATA,
    BAD_SOLUTION,
    BAD_DIFFICULTY,
    NOT_UNLOCKED,
    BAD_BOARD_SIZE,
    BAD_CMD_ID
};


#ifndef PATCHED_1
unsigned short G_GRIDDER_SIZE = (NUM_CELLS + 1) * sizeof(unsigned int);
#else
unsigned short G_GRIDDER_SIZE = (NUM_CELLS) * sizeof(unsigned int);
#endif
unsigned int g_difficulty_hard = INITIAL_HARDEST_DIFFICULTY;
unsigned int g_difficulty_easy = EASIEST_DIFFICULTY;

unsigned int RecvCmdId()
{
    unsigned int cmd_id;
    if (fread(&cmd_id, sizeof(cmd_id), stdin) != sizeof(cmd_id))
        exit(0);
    return cmd_id;
}

void SendMsgId(unsigned int msg_id)
{
    fwrite(&msg_id, sizeof(msg_id), stdout);
}

void SendMsg(void *msg, unsigned int msg_size)
{
    fwrite(msg, msg_size, stdout);
}

void RecvBoard(unsigned int *pboard, unsigned int max_size)
{
    max_size = max_size > G_GRIDDER_SIZE ? G_GRIDDER_SIZE : max_size;
    fread(pboard, max_size, stdin);
}

extern "C" int __attribute__((fastcall)) main(int secret_page_i, char *unused[])
{
    unsigned char *secret_page = (unsigned char *)secret_page_i;

    bool exited = false;
    bool initialized_grid = false;
    unsigned int cmd_id = 0;

    Gridder grid, solution;
    NumGen ngen(secret_page);
    unsigned int cur_difficulty = DEFAULT_DIFFICULTY;

    unsigned int *pmsg_status = &g_error_table[0];
    unsigned int gridder_recv_buf[NUM_CELLS];

    while (!exited)
    {
        pmsg_status = &g_error_table[0];
        memset(gridder_recv_buf, 0, sizeof(gridder_recv_buf));
        cmd_id = RecvCmdId();
        switch (cmd_id)
        {
        case EXIT:
          {
            exited = true;
            SendMsgId(g_msgs_table[EXIT]);
            break;
          }
        case NEW_GRIDDER:
          {
            grid.GenerateNewGridder(0, &ngen);
            grid.MakeGridderSolveable(cur_difficulty, &ngen);
            SendMsgId(g_msgs_table[NEW_GRIDDER]);
            grid.Serialize(stdout);
            initialized_grid = true;
            break;
          }
        case ASK_DIFFICULTY:
          {
            SendMsgId(g_msgs_table[ASK_DIFFICULTY]);
            SendMsg(&g_difficulty_hard, sizeof(g_difficulty_hard));
            SendMsg(&g_difficulty_easy, sizeof(g_difficulty_easy));
            break;
          }
        case GIVE_UP:
          {
            if (!initialized_grid)
            {
                pmsg_status = &g_error_table[1];
                break;
            }

            grid.FindSolution(0);
            SendMsgId(g_msgs_table[GIVE_UP]);
            grid.Serialize(stdout);
            grid.ResetBoard();
            break;
          }
        case SOLVE_GRIDDER:
          {
            if (!initialized_grid)
            {
                pmsg_status = &g_error_table[1];
                break;
            }

            unsigned int gridder_size = RecvCmdId();
            if ((short)gridder_size != NUM_CELLS)
            {
                pmsg_status = &g_error_table[6];
                break;
            }
            gridder_size *= sizeof(unsigned int);
            RecvBoard(gridder_recv_buf, gridder_size);
            Gridder solution;
            solution.CopyGridder(gridder_recv_buf, gridder_size);
            if (solution.ValidateGridder(grid))
            {
                initialized_grid = false;
                SendMsgId(g_msgs_table[SOLVE_GRIDDER]);
            }
            else
            {
                pmsg_status = &g_error_table[3];
            }
            break;
          }
        case CHANGE_DIFFICULTY:
          {
            unsigned int difficulty_hard = RecvCmdId();
            if (difficulty_hard < g_difficulty_hard)
            {
                pmsg_status = &g_error_table[4];
                break;
            }
            cur_difficulty = difficulty_hard;
            SendMsgId(g_msgs_table[CHANGE_DIFFICULTY]);
            break;
          }
        case CHANGE_BOARD_SIZE:
          {
            int new_board_size;
            new_board_size = RecvCmdId();
            SendMsgId(g_msgs_table[CHANGE_BOARD_SIZE]);
            break;
          }
        default:
          {
            pmsg_status = &g_error_table[7];
            break;
          }
        }

        if (pmsg_status != &g_error_table[0])
            SendMsgId(*pmsg_status);
    }

    //grid.GenerateNewGridder(0, &ngen);
    //printf("pooooooooooooooop\n");
    //grid.Debug();
    //grid.MakeGridderSolveable(20, &ngen);
    //printf("pooooooooooooooop\n");
    //grid.Debug();
    //grid.FindSolution(0);
    //printf("pooooooooooooooop\n");
    //grid.Debug();
    //printf("pooooooooooooooop\n");
    return 0;
}

