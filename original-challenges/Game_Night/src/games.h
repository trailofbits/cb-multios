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

#ifndef GAMES_H_
#define GAMES_H_

#define PACKED __attribute__((packed))

struct game_state {
    unsigned char spew[0xfff4];
    unsigned int defcon_level;
    union {
        struct {
            unsigned int cookie;
            unsigned int round;
        } PACKED hugman;
        struct {
            char move[4];
        } PACKED chess;
        struct {
            unsigned int cookie;
            unsigned int unused;
            int fitness;
        } PACKED sudoku;
        struct {
            unsigned int cookie;
            unsigned int encounter_data;
            unsigned short unused;
            unsigned char party[6];
        } PACKED safari_zone;
        struct {
            unsigned int cookie;
            unsigned int unused;
            unsigned short tank_size;
        } PACKED gallon_challenge;
        struct {
            unsigned int cookie;
            unsigned char unused[6];
            unsigned char options[6];
        } PACKED chance_of_survival;
        struct {
            unsigned int cookie;
        } PACKED lesson_in_futility;
    } games;
} PACKED;

extern struct game_state game_state;

/**
 * Initialize the cookie protecting the main game structure.
 */
void init_cookie(void);

/**
 * Verify the cookie protecting the main game structure.
 *
 * @param cookie The value of the cookie to check
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int check_cookie(unsigned int cookie);

/** 
 * Play a game of hugman.
 *
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int do_hugman(void);

/** 
 * Play a game of chess.
 *
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int do_chess(void);

/** 
 * Play a game of sudoku.
 *
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int do_sudoku(void);

/** 
 * Play a game of gallon challenge.
 *
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int do_gallon_challenge(void);

/** 
 * Play a game of safari zone.
 *
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int do_safari_zone(void);

/** 
 * Play a game of chance of survival.
 *
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int do_chance_of_survival(void);

/** 
 * Play a game of lesson in futility.
 *
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on failure
 */
int do_lesson_in_futility(void);

#endif /* GAMES_H_ */

