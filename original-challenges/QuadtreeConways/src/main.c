/*
 * Copyright (c) 2014 Kaprica Security, Inc.
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

#include <libcgc.h>
#include <stdlib.h>
#include <string.h>

#include <ctype.h>

#include "gld.h"

#define MIN_STEPS 100
#define MAX_STEPS 1000
#define STEPS_PER_GAME 10000
#define SHOTS_PER_GAME 125
#define BOMBS_PER_GAME 5
#define RUNNERS_PER_GAME 25

#define MAX_LINE_SIZE 512

static unsigned int a=111111111, b=222222222, c=333333333, d=444444444;

/*** GLOBAL VARIABLES ***/
static qtree_t *g_game_board = NULL;
static int g_board_revealed = FALSE;
static int g_high_score = 0;
static int g_current_score = 0;
static int g_num_steps_left = 0;
static int g_shots_left = 0;
static int g_bombs_left = 0;
static char g_buf[MAX_LINE_SIZE];

static char readopt(int fd) {
    char c = 0;
    char d = 0;
    char delim = '\n';

    size_t rx;
    if (receive(fd, &c, 1, &rx) != 0 || rx == 0)
        return -1;

    if (receive(fd, &d, 1, &rx) != 0 || rx == 0)
        return -1;

    if(d != delim) {
        while(d != delim) {
            if (receive(fd, &d, 1, &rx) != 0 || rx == 0)
                return -1;
        }
        return -1;
    }

    return c;
}

static int readline(int fd, char *line, size_t line_size)
{
    size_t i;
    size_t rx;

    for (i = 0; i < line_size; i++) {
        if (receive(fd, line, 1, &rx) != 0 || rx == 0)
            exit(0);
        if (*line == '\n')
            break;
        line++;
    }

    if (i == line_size && *line != '\n')
        return -1;
    else if (*line != '\n')
        return 1;
    else
        *line = '\0';

    return 0;
}

static int parse_num_steps(char *line, size_t line_size)
{
    char *temp = line;
    while(*temp) {
        if (!isdigit(*temp++))
            return -1;
    }

    int num_steps = strtol(line, NULL, 10);
    if (num_steps < MIN_STEPS || num_steps > MAX_STEPS)
        return -1;

    num_steps = g_num_steps_left < num_steps ? g_num_steps_left : num_steps;
    return num_steps;
}

static coord_t parse_coordinate(char *line, size_t line_size)
{
    coord_t coord;
    UNSET_COORD(coord);
    char *xcoord = strsep(&line, ",");
    char *ycoord = strsep(&line, " ");
    if (line != NULL)
        ycoord = line;

    if(!xcoord || !ycoord || !strlen(xcoord) || !strlen(ycoord))
        return coord;

    char *temp = xcoord;
    while(*temp) {
        if (!isdigit(*temp++))
            return coord;
    }

    temp = ycoord;
    while(*temp) {
        if (!isdigit(*temp++))
            return coord;
    }

    coord.x = strtol(xcoord, NULL, 10);
    coord.y = strtol(ycoord, NULL, 10);

    return coord;
}

static void take_shot()
{
    int score = 0;
    coord_t coord;

    printf("Enter Shot Coordinates Ex: 100, 100:: ");
    if (readline(STDIN, g_buf, MAX_LINE_SIZE) != 0) {
        printf("Invalid coordinates\n");
        return;
    }

    coord = parse_coordinate(g_buf, MAX_LINE_SIZE);
    if (coord.x < 0 || coord.y < 0) {
        printf("Invalid coordinates\n");
        return;
    }

    if (g_shots_left == 0) {
        printf("You're out of bullets.\n");
        return;
    } else {
        score = g_game_board->shoot_pixel(coord);
        g_shots_left--;
    }

    if (score != 0) {
        printf("Great shot! You got one\n");
        printf("Scored: %d points\n", score);
    } else {
        printf("You missed. Better luck next time.\n");
    }

    g_current_score += score;
}

static void place_bomb()
{
    coord_t coord;

    printf("Enter Bomb Coordinates Ex: 100, 100:: ");
    if (readline(STDIN, g_buf, MAX_LINE_SIZE) != 0) {
        printf("Invalid coordinates\n");
        return;
    }

    coord = parse_coordinate(g_buf, MAX_LINE_SIZE);
    if (coord.x < 0 || coord.y < 0 || coord.x >= MAX_BOARD_WIDTH || coord.y >= MAX_BOARD_WIDTH) {
        printf("Invalid coordinates\n");
        return;
    }

    if (g_bombs_left == 0) {
        printf("You're out of bombs.\n");
    } else if (g_game_board->set_bomb(coord)) {
        printf("Successfully planted bomb.\n");
        g_bombs_left--;
    } else {
        printf("There is already a bomb here. Try somewhere else.\n");
    }
}

static void reveal_board()
{
    g_board_revealed = TRUE;
    gld_print_board("GAME BOARD\n");
    printf("\n");
}

static void place_runner(int x, int y)
{
    conway_pixel_t px;
    px.is_alive = TRUE;
    px.bomb_set = 0;

    SET_COORD(px.point, x, y);
    g_game_board->insert(g_game_board, px);
    if (x < MAX_BOARD_WIDTH/2 && y < MAX_BOARD_WIDTH/2) {
        SET_COORD(px.point, x, y+1);
        g_game_board->insert(g_game_board, px);
        SET_COORD(px.point, x, y+2);
        g_game_board->insert(g_game_board, px);
        SET_COORD(px.point, x-1, y+2);
        g_game_board->insert(g_game_board, px);
        SET_COORD(px.point, x-2, y+1);
        g_game_board->insert(g_game_board, px);
    } else if (x >= MAX_BOARD_WIDTH/2 && y < MAX_BOARD_WIDTH/2) {
        SET_COORD(px.point, x, y+1);
        g_game_board->insert(g_game_board, px);
        SET_COORD(px.point, x, y+2);
        g_game_board->insert(g_game_board, px);
        SET_COORD(px.point, x+1, y+2);
        g_game_board->insert(g_game_board, px);
        SET_COORD(px.point, x+2, y+1);
        g_game_board->insert(g_game_board, px);
    } else if (x < MAX_BOARD_WIDTH/2 && y >= MAX_BOARD_WIDTH/2) {
        SET_COORD(px.point, x, y+1);
        g_game_board->insert(g_game_board, px);
        SET_COORD(px.point, x, y+2);
        g_game_board->insert(g_game_board, px);
        SET_COORD(px.point, x-1, y);
        g_game_board->insert(g_game_board, px);
        SET_COORD(px.point, x-2, y+1);
        g_game_board->insert(g_game_board, px);
    } else if (x >= MAX_BOARD_WIDTH/2 && y >= MAX_BOARD_WIDTH/2) {
        SET_COORD(px.point, x, y+1);
        g_game_board->insert(g_game_board, px);
        SET_COORD(px.point, x, y+2);
        g_game_board->insert(g_game_board, px);
        SET_COORD(px.point, x+1, y);
        g_game_board->insert(g_game_board, px);
        SET_COORD(px.point, x+2, y+1);
        g_game_board->insert(g_game_board, px);
    }
}

static void create_runner() {
    unsigned int temp = 0;
    unsigned int x = 0, y = 0;

    temp = a ^  (a << 11);
    a = b; b = c; c = d;
    d = (d ^ (d >> 19)) ^ (temp ^ (temp >> 8));
    x = d % MAX_BOARD_WIDTH;

    temp = a ^  (a << 11);
    a = b; b = c; c = d;
    d = (d ^ (d >> 19)) ^ (temp ^ (temp >> 8));
    y = d % MAX_BOARD_WIDTH;

    place_runner(x, y);
}

static void new_game()
{
    gld_clear_board();
    if(g_high_score < g_current_score)
        g_high_score = g_current_score;

    int i = 0;
    for(i = 0; i < RUNNERS_PER_GAME; i++)
        create_runner();

    g_board_revealed = FALSE;
    g_current_score = 0;
    g_num_steps_left = STEPS_PER_GAME;
    g_shots_left = SHOTS_PER_GAME;
    g_bombs_left = BOMBS_PER_GAME;
    printf("New Game -- Ready, set, go!\n");
}


static void run()
{
    int num_steps = 0, score = 0;
    printf("Enter amount of time to run: [%d-%d]:: ", MIN_STEPS, MAX_STEPS);
    if (readline(STDIN, g_buf, MAX_LINE_SIZE) != 0) {
        printf("Invalid amount of time\n");
        return;
    }

    num_steps = parse_num_steps(g_buf, MAX_LINE_SIZE);
    if (num_steps == -1) {
        printf("Invalid amount of time\n");
        return;
    }

    score = g_game_board->step(num_steps);
    if (score > 0)
        printf("Nice bombing! You racked up %d points.\n", score);

    g_num_steps_left = g_num_steps_left > num_steps ? g_num_steps_left - num_steps : 0;
    g_current_score += score;
    g_board_revealed = FALSE;
}

static int quit()
{
    printf("Thanks for Playing\n");
    return 0;
}


static void print_menu()
{
    if (g_num_steps_left <= 0 || (!g_shots_left && !g_bombs_left)) {
        g_num_steps_left = 0;
        printf("GAME OVER!\n");
        if(g_current_score > g_high_score) {
            printf("A new high score!!\n\n");
            g_high_score = g_current_score;
        }
        printf("                              --GAME OVER--\n");
        printf("1. New Game\n");
        printf("2. Quit\n\n");
        printf("High Score = %d\n\n", g_high_score);
    } else if (!g_board_revealed) {
        printf("                              --Board: HIDDEN--\n");
        printf("1. Shoot!\n");
        printf("2. Reveal Board\n");
        printf("3. New Game\n");
        printf("4. Quit\n");
        printf("Current Score = %d | Total Time Remaining: %d | High Score = %d \n",
                g_current_score, g_num_steps_left, g_high_score);
        printf("Shots Remaining: %d | Bombs Remaining: %d\n\n",
                g_shots_left, g_bombs_left);
    } else {
        printf("                              --Board: REVEALED--\n");
        printf("1. Place Bomb\n");
        printf("2. Reveal Board\n");
        printf("3. Let them Run!\n");
        printf("4. New Game\n");
        printf("5. Quit\n");
        printf("Current Score = %d | Total Time Remaining: %d | High Score = %d \n",
                g_current_score, g_num_steps_left, g_high_score);
        printf("Shots Remaining: %d | Bombs Remaining: %d\n\n",
                g_shots_left, g_bombs_left);
    }

    printf("Selection-: ");
}

static int game_selection()
{
    char choice = readopt(STDIN);

    if (choice == -1) {
        printf("Bad Input\n");
        return -1;
    }

    if (g_num_steps_left <= 0) {
        switch(choice) {
        case '1':
            new_game();
            break;
        case '2':
            quit();
            return 0;
        default:
            printf("Bad Choice\n");
            return -1;
        }
    } else if (!g_board_revealed) {
        switch(choice) {
        case '1':
            take_shot();
            break;
        case '2':
            reveal_board();
            break;
        case '3':
            new_game();
            break;
        case '4':
            quit();
            return 0;
        default:
            printf("Bad Choice\n");
            return -1;
        }
    } else {
        switch(choice) {
        case '1':
            place_bomb();
            break;
        case '2':
            reveal_board();
            break;
        case '3':
            run();
            break;
        case '4':
            new_game();
            break;
        case '5':
            quit();
            return 0;
        default:
            printf("Bad Choice\n");
            return -1;
        }
    }

    return 1;
}
static void init_randomness()
{
    char *temp;

try_again:
    printf("Before we begin. Enter a number [1 - 4294967295]\n"     \
            "Or any number. We'll figure it out: ");

    while (readline(STDIN, g_buf, MAX_LINE_SIZE) != 0) {
        printf("Bad input\n");
    }

    temp = g_buf;
    while(temp && *temp) {
        if(!isdigit(*temp++)) {
            printf("Invalid number\n");
            goto try_again;
        }
    }
    a = strtol(g_buf, NULL, 10);
}
int main() {
    init_randomness();
    g_game_board = gld_init_game();
    new_game();
    int status = 1;
    do {
        print_menu();
        status = game_selection();
    } while (status);

    printf("EXITING...\n");
    return 0;
}
