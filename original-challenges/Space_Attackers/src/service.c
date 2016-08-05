/*
 * Copyright (c) 2015 Kaprica Security, Inc.
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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int rows = 25;
int columns = 25;
int turnCounter = 0;
int** board;
int* shipCords;
char* playerName;
int** enemies;
int rowCount = 2;
int** userBullets;
int** enemyBullets;
int lost = 0;
unsigned int seed1 = 0;
unsigned int seed2 = 0;

void seedRandomGen(unsigned int inc1, unsigned int inc2) {
    if (strcmp(playerName, "magic") == 0) {
        seed1 = 0;
        seed2 = 0;
    }
    else
    {
        seed1 = inc1;
        seed2 = inc2;
    }
}

int getRandomInt() {
    
    seed1 = 42871 * (seed1 & 0xFFFF) + (seed1 >> 16);
    seed2 = 28172 * (seed2 & 0xFFFF) + (seed2 >> 16);
    unsigned int val = (seed1 << 16) + seed2;
    //printf("%d\n", val%1000);
    return val;
}

void createEnemies() {
    // allocate enemies array
    // 0 means dead
    // 1,2,3,4 is the quadrant they are in, clockwise starting from top left
    enemies = calloc(rowCount, sizeof(int*));
    for (int i = 0; i < rowCount; i++)
    {
        enemies[i] = calloc(columns/2, sizeof(int));
        for (int j = 0; j < columns/2; j++)
        {
            enemies[i][j] = 1;
        }
    }
    
}

int** createBoard (int m, int n) {
    int** board = malloc(m * sizeof(int*));
    for (int i= 0; i < m; ++i)
    {
        board[i] = malloc(n * sizeof(int));
    }
    // clear board
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            board[i][j] = 0;
        }
    }
    
    return board;
}

void clearEnemies() {
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (board[i][j] == 3)
            {
                board[i][j] = 0;
            }
        }
    }
}

void setEnemies() {
    // calc how far down the enemies have moved
    int depressCount = turnCounter/20;
    
    // for each enemy, place it in the correct place
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < columns/2; j++)
        {
            switch (enemies[i][j]) {
                case 1:
                    board[depressCount+(i*2)][j*2] = 3;
                    break;
                case 2:
                    board[depressCount+(i*2)][(j*2)+1] = 3;
                    break;
                case 3:
                    board[(depressCount+(i*2))+1][(j*2)+1] = 3;
                    break;
                case 4:
                    board[(depressCount+(i*2))+1][(j*2)] = 3;
                    break;
                    
                default:
                    break;
            }
        }
    }
    
    
}

int movePieces () {
    
    return 0;
}

int canEnemyFire(int m, int n) {
    
    // check if you are on the bottom row
    if (m == rowCount-1) {
        return 0;
    }
    // if not, see if people are in your way
    for (int i = m+1; i < rowCount; i++) {
        // if there is an enemy, then error
        if (enemies[i][n] != 0) {
            return 1;
        }
        
    }
    // this means there were no enemies below you so you are allowed to shoot
    return 0;
}

void enemyFire(int x, int y) {
    // look for empty bullet location
    int emptyLoc = -1;
    for (int i = 0; i < (rows * (columns/2)); i++) {
        if (enemyBullets[i][0] == -1) {
            emptyLoc = i;
            break;
        }
    }
    
    // now that we have found place, put bullet on
    enemyBullets[emptyLoc][0] = y;
    enemyBullets[emptyLoc][1] = x;
}

void updateEnemies() {
    // for each enemie decide whether or not they should move or fire
    int isThereAnEnemy = 0;
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < columns/2; j++)
        {
            // only move alive enemies
            if (enemies[i][j] != 0)
            {
                isThereAnEnemy = 1;
                unsigned int gen = getRandomInt();
                unsigned int r = gen%7;
                
                //decide if enemy wants to fire
                if (r == 1)
                {
                    int x = -1;
                    int y = -1;
                    if (canEnemyFire(i, j) == 0) {
                        // switch on which quadrant the enemy is in to decide where the
                        // bullet should come from
                        switch (enemies[i][j]) {
                            case 1:
                                x = j*2;
                                y = (turnCounter/20) + (i*2);
                                break;
                            case 2:
                                x = j*2;
                                x = x+1;
                                y = (turnCounter/20) + (i*2);
                                break;
                            case 3:
                                x = j*2;
                                x = x+1;
                                y = (turnCounter/20) + (i*2);
                                y = y+1;
                                break;
                            case 4:
                                x = j*2;
                                y = (turnCounter/20) + (i*2);
                                y = y+1;
                                break;
                                
                            default:
                                break;
                        }
                        // fire!
                        enemyFire(x, y);
                    }
                }
                else
                {
                    // 1/3 of time move left, right or stay still
                    switch (gen%3) {
                            // move left
                        case 0:
                            if (enemies[i][j] == 1)
                            {
                                enemies[i][j] = 4;
                            }
                            else
                            {
                                enemies[i][j] = enemies[i][j] - 1;
                            }
                            break;
                            
                            // move right
                        case 1:
                            if (enemies[i][j] == 4)
                            {
                                enemies[i][j] = 1;
                            }
                            else
                            {
                                enemies[i][j] = enemies[i][j] + 1;
                            }
                            break;
                            
                        default:
                            break;
                    }
                }
            }
            
        }
    }
    // if there are no more enemies, then win
    if (isThereAnEnemy == 0) {
        lost = -1;
    }
}

void clearScreen() {
    //fprintf(stdout, "\x1B[2J");
}

int drawBoard() {
    //cause computer pieces to update
    movePieces();
    
    // clear the screen for new game board to come down
    clearScreen();
    
    // write the users name at the top
    fprintf(stdout, "\tWelcome to Attackers General %s!\n", playerName);
    
    //draw current board
    //draw top
    for (int i = 0; i < columns+2; i++)
    {
        fprintf(stdout, "-");
    }
    fprintf(stdout, "\n");
    
    // print the actors
    for (int i = 0; i < rows; i++)
    {
        //fprintf(stdout, "%02d|", i);
        fprintf(stdout, "|");
        for (int j = 0; j < columns; j++)
        {
            
            switch (board[i][j]) {
                case 1:
                    fprintf(stdout, "=");
                    break;
                case 2:
                    fprintf(stdout, "W");
                    break;
                case 3:
                    fprintf(stdout, "#");
                    break;
                case 4:
                    fprintf(stdout, "!");
                    break;
                case 5:
                    fprintf(stdout, "+");
                    break;
                default:
                    fprintf(stdout, " ");
                    break;
            }
            
        }
        fprintf(stdout, "|\n");
    }
    
    
    //draw bottom
    //fprintf(stdout, "  ");
    for (int i = 0; i < columns+2; i++)
    {
        fprintf(stdout, "-");
    }
    fprintf(stdout, "\n");
    
    return 0;
}

int setupNewGame() {
    // create the board
    board = createBoard(rows, columns);
    
    // create the ship
    shipCords = (int*) calloc(2, sizeof(int));
    shipCords[0] = 0;
    shipCords[1] = rows-1;
    board[shipCords[1]][shipCords[0]] = 2;
    
    // get the user's name
    fprintf(stdout, "Please input your name:\n");
    playerName = (char*) calloc(sizeof(char), 256);
    fflush(stdout);
    freaduntil(playerName, 256, '\n', stdin);
    
#if 0
    // if someone put in more than 255 characters, throw the extra away
    if ((playerName[255] != '\n') && (playerName[255] != 0x0))
    {
        char junk = 0x0;
        while (junk != '\n') {
            fread(&junk, 1, stdin);
        }
    }
#endif
    
    // get rid of \n character and 'sanatize' input
    for (int i = 0; i < sizeof(playerName); i++)
    {
        if (((int)playerName[i] < 97) || ((int)playerName[i] > 122))
        {
            playerName[i] = 0x0;
            
        }
        if (playerName[i] == '\n') {
            playerName[i] = 0x0;
        }
        
    }
    
    // create the enemies
    createEnemies();
    setEnemies();
    
    // instantiate user bullets array
    userBullets = (int**)calloc(rows, sizeof(int*));
    for (int i = 0; i < rows; i++)
    {
        userBullets[i] = (int*)calloc(2, sizeof(int));
        userBullets[i][0] = -1;
        userBullets[i][1] = -1;
    }
    
    // instantiate enemy bullets array
    enemyBullets = (int**)calloc(rows*(columns/2), sizeof(int*));
    for (int i = 0; i < (rows*(columns/2)); i++)
    {
        enemyBullets[i] = (int*) calloc(2, sizeof(int));
        enemyBullets[i][0] = -1;
        enemyBullets[i][1] = -1;
    }
    
    return 0;
}

char getUserInput() {
    //get the first char that the user hit
    char* buffer = (char*) calloc(256, sizeof(char));
    fflush(stdout);
    freaduntil(buffer, 200, '\n', stdin);
    
    return buffer[0];
}

void clearShip() {
    board[shipCords[1]][shipCords[0]] = 0;
}

void setShip() {
	//fprintf(stderr, "prev thing: %d\n", board[shipCords[1]][shipCords[0]]);
	if (board[shipCords[1]][shipCords[0]] == 5)
		lost = 1;
    board[shipCords[1]][shipCords[0]] = 2;
}

void userFire() {
    // find empty bullet
    int emptyLoc = -1;
    for (int i = 0; i < rows; i++)
    {
        if (userBullets[i][0] == -1)
        {
            emptyLoc = i;
            break;
        }
    }
    
    // check if user can fire
    if (shipCords[1] > 0)
    {
        // add bullet
        userBullets[emptyLoc][0] = shipCords[0];
        userBullets[emptyLoc][1] = shipCords[1];
    }
}

void moveUser() {
    // get the user's movement
    char move = getUserInput();
    // move the ship based on the key
    switch (move) {
        case 'w':
            //move up
            if (shipCords[1] > 0) {
                clearShip();
                shipCords[1] = shipCords[1]-1;
                setShip();
            }
            break;
            
        case 'a':
            //move up
            if (shipCords[0] > 0) {
                clearShip();
                shipCords[0] = shipCords[0]-1;
                setShip();
            }
            break;
            
        case 'd':
            //move up
            if (shipCords[0] < columns-1) {
                clearShip();
                shipCords[0] = shipCords[0]+1;
                setShip();
            }
            break;
            
        case 's':
            //move up
            if (shipCords[1] < rows-1) {
                clearShip();
                shipCords[1] = shipCords[1]+1;
                setShip();
            }
            break;
            
        default:
            userFire();
            break;
    }
}

void updateBullets() {
    // go through all user bullets and advance them by 1
    // if the advance would move them off the map, then delete them
    for (int i = 0; i < rows; i++)
    {
        // check if there is a bullet
        if (userBullets[i][0] != -1) {
            // check if bullet about to go off map
            if(userBullets[i][1] == 0)
            {
                // delete the bullet
                userBullets[i][0] = -1;
                userBullets[i][1] = -1;
            }
            else
            {
                //advance the bullet
                userBullets[i][1] = userBullets[i][1]-1;
            }
        }
    }
    
    // go through all enemy bullets and advance them by 1
    // if the advance would move them off the map, then delete them
    for (int i = 0; i < (rows*(columns/2)); i++)
    {
        // check if there is a bullet
        if (enemyBullets[i][0] != -1) {
            // check if bullet about to go off map
            if(enemyBullets[i][0] == (rows-1))
            {
                // delete the bullet
                enemyBullets[i][0] = -1;
                enemyBullets[i][1] = -1;
            }
            else
            {
                //advance the bullet
                enemyBullets[i][0] = enemyBullets[i][0]+1;
            }
        }
    }
}

void clearBullets() {
    for (int i = 0; i < rows; i++) {
        if((userBullets[i][0] != -1) && (board[userBullets[i][1]][userBullets[i][0]] == 4))
        {
            board[userBullets[i][1]][userBullets[i][0]] = 0;
        }
    }
    
    for (int i = 0; i < (rows*(columns/2)); i++) {
        if((enemyBullets[i][0] != -1) && (board[enemyBullets[i][0]][enemyBullets[i][1]] == 5))
        {
            board[enemyBullets[i][0]][enemyBullets[i][1]] = 0;
        }
    }
}

void setBullets() {
    for (int i = 0; i < rows; i++) {
        if(userBullets[i][0] != -1)
        {
            // if there is a ship where the bullet now is, delete them both
            if (board[userBullets[i][1]][userBullets[i][0]] == 3) {
                // clear board
                board[userBullets[i][1]][userBullets[i][0]] = 0;
                // delete ship
                int hold = (userBullets[i][1]-(turnCounter/20))/2;
                //fprintf(stdout, "There is a ship at: (%i, %i)\n I want to delete enemy: [%i][%i]\n", userBullets[i][1], userBullets[i][0], hold, (userBullets[i][0]/2));
                
                enemies[hold][(userBullets[i][0]/2)] = 0;
                //fprintf(stdout, "BOOM\n");
                //delete bullet
                userBullets[i][0] = -1;
                userBullets[i][1] = -1;
                
            }
            else
            {
                board[userBullets[i][1]][userBullets[i][0]] = 4;
            }
        }
    }
    
    // set enemy bullets
    for (int i = 0; i < (rows*(columns/2)); i++) {
        if(enemyBullets[i][0] != -1)
        {
            // if the user is where the bullet is, then lose
            if (board[enemyBullets[i][0]][enemyBullets[i][1]] == 2) {
                // set lost to true
                lost = 1;
            }
            else
            {
                board[enemyBullets[i][0]][enemyBullets[i][1]] = 5;
            }
        }
    }
}

int __attribute__((fastcall)) main(int secret_page_i, char *unused[]) {
    void *secret_page = (void *)secret_page_i;

    (void) secret_page;
    
    fbuffered(stdout, 1);
    if (turnCounter == 0) {
        setupNewGame();
        
        // seed the random number generator
        seedRandomGen(((int *)secret_page)[0] ^ ((int *)secret_page)[1] , ((int *)secret_page)[2] ^ ((int *)secret_page)[3]);
    }
    while (turnCounter < 10000 && lost == 0)
    {
        //printf("%d %d\n", seed1, seed2);
        if (turnCounter != 0) {
            // update enemies
            clearEnemies();
            updateEnemies();
            setEnemies();
            
            // update bullets
            clearBullets();
            updateBullets();
            setBullets();
        }
        // check if ship is hit, if not, draw it
        if (shipCords[0] != -1)
        {
            setShip();
        }
        
        //draw the board
		//fprintf(stderr,"lost: %d, turnCounter: %d\n", lost, turnCounter);
        drawBoard();
        fprintf(stdout, "\t\tLevel #%d\n", (turnCounter/20)+1);
        
        //get user move and update their piece
        moveUser();
        
        
        turnCounter++;
        // check if the invaders have reached the bottom
        if (((turnCounter/20)+1) == (rows-2)) {
            lost = 1;
        }
    }
    
    
    
    // check if we lost
    if (lost == 1) {
        clearScreen();
        fprintf(stdout, "\t\tyou lose\n\n\n\n\n");
    }
    // check if we won
    else if (lost == -1)
    {
        int shipX = 4;
        int shipY = 5;
        
        // let them overwrite a buffer
        int i;
        char targetBuffer[256];
        char* srcBuffer = (char*) calloc(100000, sizeof(char));
        char currentChar = 0;
        int counter = 0;
        
        for (i = 0; i < 100000; i++)
        {
            
            //draw board
            //clearScreen();
            //draw top
            fprintf(stdout, "\t\t!!!DANCE MODE!!!\n\n\n\n\n");
            fprintf(stdout, "\n\n\n");
            for (int j = 0; j < 12; j++) {
                fprintf(stdout, "-");
            }
            fprintf(stdout, "\n");
            // draw middle
            for (int q = 0; q < 10; q++) {
                fprintf(stdout, "|");
                for (int k = 0; k < 10; k++) {
                    if (shipX == q && shipY == k) {
                        fprintf(stdout, "W");
                    }
                    else
                    {
                        fprintf(stdout, " ");
                    }
                }
                fprintf(stdout, "|\n");
            }
            //draw bottom
            for (int j = 0; j < 12; j++) {
                fprintf(stdout, "-");
            }
            fprintf(stdout, "\n");
            
            // get user input
            fprintf(stdout, "Bust a move (w = +1, s=SaveDigit, d=FIRE, q=Quit)\n%x\n", currentChar);
            fflush(stdout);
            char response = (char)calloc(1, sizeof(char));
            response = getUserInput();
            if (response == 'q')
                break;
            switch (response) {
                case 'w':
                    currentChar = (currentChar + 1)%256;
                    break;
                case 's':
                    srcBuffer[counter] = currentChar;
                    currentChar = 0;
                    counter = counter + 1;
                    break;
                case 'd':
#ifdef PATCHED_1
                    strncpy(targetBuffer, srcBuffer, sizeof(targetBuffer));
#else
                    strncpy(targetBuffer, srcBuffer, counter);
#endif
                    break;
                default:
                    break;
                    
            }
            
            //move the ship randomly (i.e. dancing)
            int r = getRandomInt()%4;
            
            switch (r) {
                case 0:
                    if (shipX == 9)
                    {
                        shipX = 0;
                    }
                    else
                    {
                        shipX = (shipX + 1)%10;
                    }
                    break;
                    
                case 1:
                    if (shipX == 0)
                    {
                        shipX = 9;
                    }
                    else
                    {
                        shipX = (shipX - 1)%10;
                    }
                    break;
                    
                case 2:
                    if (shipY == 9)
                    {
                        shipY = 0;
                    }
                    else
                    {
                        shipY = (shipY + 1)%10;
                    }
                    break;
                    
                case 3:
                    if (shipY == 0)
                    {
                        shipY = 9;
                    }
                    else
                    {
                        shipY = (shipY - 1)%10;
                    }
                    break;
                    
                    
                default:
                    break;
            }
        }
    }

    fflush(stdout);
    return 0;
}
