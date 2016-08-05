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
#include <cstdio.h>
#include <cstring.h>
#include "gridder.h"

#define ROW(_idx) ((_idx)/(SET_SIZE))
#define COL(_idx) ((_idx)%(SET_SIZE))
#define SET(_num) ((_num)%(SET_SIZE)+1)


Gridder::Gridder()
{
    ResetBoard();
}

Gridder::Gridder(const Gridder &copy)
{
    memcpy(board_, copy.board_, sizeof(board_));
}

bool Gridder::CopyGridder(unsigned int *pboard, int size)
{
    if (size < sizeof(board_))
        return false;

    memcpy(board_, pboard, sizeof(board_));
    return true;
}

bool Gridder::GenerateNewGridder(int cell_idx, NumGen *pngen)
{
    if (cell_idx == 0)
    {
        ResetBoard();
        pngen->Reset();
    }

    if (cell_idx == NUM_CELLS)
        return true;

    int next_num = 0;
    int num_cached = 0;
    int valid_nums[SET_SIZE];
    memset(valid_nums, UNUSED, sizeof(valid_nums));

    while(pngen->AvailableNumbers())
    {
        int row = ROW(cell_idx);
        int col = COL(cell_idx);
        next_num = pngen->GetRandomNumber();
        if (!next_num)
            continue;

        if (valid_nums[SET(next_num) - 1] != UNUSED || !ValidAddNumber(SET(next_num), row, col))
        {
            valid_nums[SET(next_num) - 1] = USED;
            pngen->CacheNumber(next_num);
            ++num_cached;
        }
        else
        {
            pngen->FlushCache(num_cached);
            valid_nums[SET(next_num) - 1] = USED;
            pngen->CacheNumber(next_num);
            num_cached = 1;

            if (GenerateNewGridder(cell_idx + 1, pngen))
                return true;
            board_[row][col] = UNUSED;
        }

    }
    pngen->FlushCache(num_cached);
    return false;
}

void Gridder::MakeGridderSolveable(int difficulty, NumGen *pngen)
{
    Gridder *solution = (Gridder *)NULL;
    pngen->Reset();

    difficulty = difficulty < DIFFICULTY ? DIFFICULTY : difficulty;
    while(difficulty < pngen->AvailableNumbers())
    {
        if (solution)
        {
            delete solution;
            solution = (Gridder *)NULL;
        }
        int cell_idx  = pngen->GetRandomNumber();
        if (!cell_idx)
            return;

        --cell_idx;
        int row = ROW(cell_idx);
        int col = COL(cell_idx);
        int prev_val = board_[row][col];
        board_[row][col] = UNUSED;

        Gridder orig = *this;
        solution = orig.FindSolution(0);
        if (solution)
        {
            bool exit = false;
            orig = *this;
            if (!orig.HasUniqueSolution(0, solution, &exit))
                board_[row][col] = prev_val;
        }
        else
        {
            board_[row][col] = prev_val;
        }

    }

    if (solution)
        delete solution;
}

bool Gridder::ValidateGridder(const Gridder &master)
{
    for (int r = 0; r < SET_SIZE; r++)
    {
        for (int c = 0; c < SET_SIZE; c++)
        {
            if (master.board_[r][c] != 0 && master.board_[r][c] != board_[r][c])
                return false;
            if (!ValidCell(r, c))
                return false;
        }
    }

    return true;
}

void Gridder::Serialize(FILE *out)
{
    unsigned int board_size = sizeof(board_);
    fwrite(&board_size, sizeof(board_size), out);
    fwrite(board_, sizeof(board_), out);
}

unsigned int *Gridder::GetRawGridder(int *size)
{
    *size = sizeof(board_);
    return &board_[0][0];

    return (unsigned int *)NULL;
}

Gridder *Gridder::FindSolution(int cell_idx)
{
    if (cell_idx == NUM_CELLS)
        return new Gridder(*this);

    int row = ROW(cell_idx);
    int col = COL(cell_idx);
    if (board_[row][col])
        return FindSolution(cell_idx+1);

    for (int i = 1; i <= SET_SIZE; i++)
    {
        board_[row][col] = i;
        if (ValidCell(row,col))
        {
            Gridder *solution = FindSolution(cell_idx+1);
            if (solution)
                return solution;
        }
    }

    board_[row][col] = UNUSED;
    return (Gridder *)NULL;
}

bool Gridder::HasUniqueSolution(int cell_idx, const Gridder *s1, bool *exit)
{
    if (cell_idx == NUM_CELLS)
    {
        *exit = true;
        if (memcmp(board_, s1->board_, sizeof(board_)) != 0)
            return false;
        else
            return true;
    }

    int row = ROW(cell_idx);
    int col = COL(cell_idx);
    if (board_[row][col])
        return HasUniqueSolution(cell_idx+1, s1, exit);

    for (int i = SET_SIZE; i > 0; i--)
    {
        if (*exit)
            return false;
        board_[row][col] = i;
        if (ValidCell(row,col) && HasUniqueSolution(cell_idx+1, s1, exit))
            return true;
    }

    board_[row][col] = UNUSED;
    return false;
}

void Gridder::ResetBoard()
{
    memset(board_, UNUSED, sizeof(board_));
}

bool Gridder::ValidAddNumber(int val, int row, int col)
{
    if (board_[row][col] != UNUSED)
        return false;

    board_[row][col] = val;
    if (ValidCell(row, col))
        return true;

    board_[row][col] = UNUSED;
    return false;
}

bool Gridder::ValidCell(int row, int col)
{
    int cell = board_[row][col];
    for (int i = 0; i < SET_SIZE; i++)
        if ((row != i && cell == board_[i][col]) || (col != i && cell == board_[row][i]))
            return false;

    for (int r = (row/SET_SUBSIZE) * SET_SUBSIZE; r < ((row/SET_SUBSIZE) + 1) * SET_SUBSIZE; r++)
    {
        for (int c = (col/SET_SUBSIZE) * SET_SUBSIZE; c < ((col/SET_SUBSIZE) + 1) * SET_SUBSIZE; c++)
        {
            if (row == r && col == c)
                continue;

            if (cell == board_[r][c])
                return false;
        }
    }
    return true;
}


void Gridder::Debug()
{
    for (int r = 0; r < SET_SIZE; r++)
    {
        if (r)
        {
            if (r % SET_SUBSIZE == 0)
                fprintf(stderr, "\n------+-------+------\n");
            else
                fprintf(stderr, "\n");
        }

        for (int c = 0; c < SET_SIZE; c++)
        {
            if (c && c % SET_SUBSIZE == 0)
                fprintf(stderr, "| ");
            fprintf(stderr, "%d ", board_[r][c]);
        }
    }
    fprintf(stderr, "\n\n");
}
