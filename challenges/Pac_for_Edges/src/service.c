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
#include "cgc_stdio.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"
#include "cgc_math.h"
#include "cgc__defines.h"

struct image
{
    int height;
    int width;
    int ** pixels;
    int ** gradient_angle;
    char * data;
};

void cgc_dataIntoPixels(struct image * myImage)
{
    // move data into  pixels
    for(int i = 0; i < 512; i++)
    {
        for(int j = 0; j < 512; j++)
        {
            int index = (512*i) + (j);
            unsigned char hold = myImage->data[index];
            myImage->pixels[i][j] = (int) hold;
        }
    }

}

int cgc_acceptImage(struct image * myImage)
{
    //burn magic bytes
    char burn[20];
    cgc_fread(burn, 3, cgc_stdin);

    // load the width
    char char_hold[1];
    cgc_fread(char_hold, 1, cgc_stdin);
    char * num_hold = cgc_calloc(1, 20);
    int i = 0;
    while (char_hold[0] != (char) 0x02) {
        num_hold[i] = char_hold[0];
        i++;
#ifdef PATCHED_1
		if (i == 20)
			cgc__terminate(0);
#endif
        if (cgc_fread(char_hold, 1, cgc_stdin) != 1)
			cgc__terminate(0);
    }
    num_hold[i] = 0x0;
    int width = cgc_strtol(num_hold, 0, 0);

    // load the height
    cgc_fread(char_hold, 1, cgc_stdin);
    num_hold[0] = 0x0;
    i = 0;
    while (char_hold[0] != (char) 0x02) {
        num_hold[i] = char_hold[0];
        i++;
		if (i == 20)
			cgc__terminate(0);
        if (cgc_fread(char_hold, 1, cgc_stdin) != 1)
			cgc__terminate(0);
    }
    num_hold[i] = 0x0;
    int height = cgc_strtol(num_hold,0,0);

	if (width != 512 || height != 512)
		cgc__terminate(0);

    // throw away the max val
    cgc_fread(char_hold, 4, cgc_stdin);

    // allocate the image struct pointer
    myImage->data = cgc_calloc(1, (height*width));
    myImage->pixels = cgc_calloc(1, height*sizeof(int *));
    for(int i = 0; i < height; i++)
    {
        myImage->pixels[i] = cgc_calloc(1, width*sizeof(int));
    }
    myImage->gradient_angle = cgc_calloc(1, height*sizeof(int *));
    for(int i = 0; i < height; i++)
    {
        myImage->gradient_angle[i] = cgc_calloc(1, width*sizeof(int));
    }

    //load height and width into struct
    myImage->height = height;
    myImage->width = width;

    //cgc_read the remainder
    cgc_fread(myImage->data, myImage->height*myImage->width, cgc_stdin);

    // move data in pixels
    cgc_dataIntoPixels(myImage);

    return 0;
}

int cgc_outputImage(struct image * myImage)
{
    char header[] = "CG\x02""512\x02""512\x02""111\x02";

    cgc_fwrite(header,  cgc_strlen(header), cgc_stdout);
    cgc_fwrite(myImage->data,  myImage->height * myImage->width, cgc_stdout);

    return 0;
}

int cgc_getVal(int i, int j, int x, int y, struct image * myImage)
{
    int newR = i-x;
    int newC = j-y;

    if (newR < 0)
    {
        newR = 0;
    }
    else if (newR > 511)
    {
        newR = 511;
    }

    if (newC < 0)
    {
        newC = 0;
    }
    else if (newC > 511)
    {
        newC = 511;
    }

    return myImage->pixels[newR][newC];

}

int cgc_applyFilter(struct image * myImage)
{
    int gaus_filter[5][5] = {{2,4,5,4,2},{4,9,12,9,4},{5,12,15,12,5},{4,9,12,9,4},{2,4,5,4,2}};

    for(int i = 0; i < 512; i++)
    {
        for(int j = 0; j < 512; j++)
        {
            // apply filter to given pixel
            float value = 0;

            for(int x = 0; x < 5; x++)
            {
                for(int y = 0; y < 5; y++)
                {
                    value = value + (gaus_filter[x][y]*cgc_getVal(i,j,x-2,y-2,myImage));
                }
            }

            value = value / 159.0;

            myImage->data[(i*512)+(j)] = (char) ((int)value);
        }
    }

    cgc_dataIntoPixels(myImage);
    return 0;
}

double cgc_onlyTwoDecimals(double incoming)
{
    double holdNum = incoming * 100.0f;
    int holdNum2 = (int)holdNum;
    holdNum = (double) holdNum2;
    holdNum = holdNum / 100.0f;
    holdNum = (double)((int)holdNum);
    return holdNum;
}

int cgc_findGradients(struct image * myImage)
{
    int x_kernel[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};
    int y_kernel[3][3] = {{1,2,1},{0,0,0},{-1,-2,-1}};

    int kgx[512][512];
    int kgy[512][512];
    int newG[512][512];

    for(int i = 0; i < 512; i++)
    {
        for(int j = 0; j < 512; j++)
        {
            int value_x = 0;
            int value_y = 0;

            for(int x = 0; x < 3; x++)
            {
                for(int y = 0; y < 3; y++)
                {
                    value_x = value_x + (x_kernel[x][y]*cgc_getVal(i, j, x-1, y-1, myImage));
                    value_y = value_y + (y_kernel[x][y]*cgc_getVal(i, j, x-1, y-1, myImage));
                }
            }

            kgx[i][j] = value_x;
            kgy[i][j] = value_y;
            newG[i][j] = cgc_sqrt((value_x*value_x)+(value_y*value_y));
            myImage->data[(512*i)+j] = (char) newG[i][j];
            double hold = 0;
            if (value_x != 0)
                hold = ((double)cgc_fabs(value_y)) / ((double)cgc_fabs(value_x));
            else
                hold = 0;
            //TESTING
            double grad_hold = (double) hold;
            hold = cgc_onlyTwoDecimals(hold);

            grad_hold = cgc_atan2(hold,1);
            grad_hold = cgc_onlyTwoDecimals(grad_hold);

            grad_hold = (57.29) * grad_hold;
            grad_hold = cgc_onlyTwoDecimals(grad_hold);
            grad_hold = grad_hold + 22.5;

            grad_hold = cgc_onlyTwoDecimals(grad_hold);
            myImage->gradient_angle[i][j] = (int)(grad_hold);
            myImage->gradient_angle[i][j] = (myImage->gradient_angle[i][j] / 45)+2;
        }
    }
    cgc_dataIntoPixels(myImage);
    return 0;
}

void cgc_non_max_suppressions(struct image * myImage)
{
    for(int i = 0; i < 512; i++)
    {
        for(int j = 0; j < 512; j++)
        {
            int val_0_x = 0;
            int val_0_y = 0;
            int val_1_x = 0;
            int val_1_y = 0;

            switch (myImage->gradient_angle[i][j]) {
                case 0:
                case 4:
                    val_0_x = -1;
                    val_0_y = 0;
                    val_1_x = 1;
                    val_1_y = 0;
                    break;
                case 1:
                case 5:
                    val_0_x = -1;
                    val_0_y = -1;
                    val_1_x = 1;
                    val_1_y = 1;
                    break;
                case 2:
                case 6:
                    val_0_x = 0;
                    val_0_y = -1;
                    val_1_x = 0;
                    val_1_y = 1;
                    break;
                case 3:
                case 7:
                    val_0_x = 1;
                    val_0_y = -1;
                    val_1_x = -1;
                    val_1_y = 1;
                    break;

                default:
                    break;
            }

            int val0 = cgc_getVal(i, j, val_0_x, val_0_y, myImage);
            int val1 = cgc_getVal(i, j, val_1_x, val_1_y, myImage);
            int max = cgc_getVal(i, j, 0, 0, myImage);
            if (max < val0 || max < val1)
            {
                max = 0;
            }
            myImage->data[(512*i)+j] = max;
        }
    }
    cgc_dataIntoPixels(myImage);
}

int cgc_double_thresholding(struct image * myImage, int lowThreshold, int highThreshold)
{
    for(int i = 0; i < 512; i++)
    {
        for(int j = 0; j < 512; j++)
        {
            int pixel = myImage->pixels[i][j];
            int finalValue = 0;
            if(pixel > highThreshold)
            {
                finalValue = 254;
            }
            else if (pixel > lowThreshold)
            {
                finalValue = 60;
            }
            myImage->data[(512*i)+j] = finalValue;
        }
    }
    cgc_dataIntoPixels(myImage);
    return 0;
}

int cgc_hysteresis(struct image * myImage)
{
    for(int i = 0; i < 512; i++)
    {
        for(int j = 0; j < 512; j++)
        {
            if (myImage->pixels[i][j] == 60)
            {
                int write_hold = 0;
                for(int x = 0; x < 3; x++)
                {
                    for(int y = 0; y < 3; y++)
                    {
                        // if we found a connected strong edge
                        if (cgc_getVal(i, j, x-1, y-1, myImage) == 254)
                        {
                            write_hold = 254;
                        }
                    }
                }
                myImage->data[(512*i)+j] = write_hold;
            }
        }
    }
    cgc_dataIntoPixels(myImage);
    return 0;
}

void cgc_performImageMagic()
{
    struct image *myImage = cgc_calloc(1, sizeof *myImage);
    cgc_acceptImage(myImage);
    cgc_applyFilter(myImage);
    cgc_findGradients(myImage);
    cgc_non_max_suppressions(myImage);
    cgc_double_thresholding(myImage, 20, 70);
    cgc_hysteresis(myImage);
    cgc_outputImage(myImage);
}

char cgc_getUserInput() {
    char val = ' ';

    char* holdVal = (char *) cgc_calloc(sizeof(char), 10);
    while(holdVal[0] != NL[0])
    {
        val = holdVal[0];
        if (cgc_fread(holdVal, 1, cgc_stdin) != 1)
            cgc__terminate(0);
    }

    return val;
}

void cgc_drawBoard(int board[20][20])
{
    // draw the top barrier
    for(int i = 0; i < 22; i++)
    {
        cgc_fprintf(cgc_stdout, "-");
    }
    cgc_fprintf(cgc_stdout, NL);

    // Loop through every position on the board and fill in the correct character
    for(int x = 0; x < 20; x++)
    {
        // print left side of screen
        cgc_fprintf(cgc_stdout, "|");
        for(int y = 0; y < 20; y++)
        {
            switch (board[x][y]) {
                case 0:
                default:
                    cgc_fprintf(cgc_stdout, " ");
                    break;
                case 2:
                    cgc_fprintf(cgc_stdout, "+");
                    break;
                case 1:
                    cgc_fprintf(cgc_stdout, ".");
                    break;
                case 4:
                    cgc_fprintf(cgc_stdout, "O");
                    break;
            }
        }
        // print right side of screen
        cgc_fprintf(cgc_stdout, "|" NL);
    }

    // draw the bottom barrier
    for(int i = 0; i < 22; i++)
    {
        cgc_fprintf(cgc_stdout, "-");
    }
    cgc_fprintf(cgc_stdout, NL);
}

void cgc_moveUserIfValid(int board[20][20], char userInput, int * pac_x_loc, int * pac_y_loc)
{
    // check if the proposed move would go off the board
    if (*pac_y_loc == 0 && userInput == 'a')
    {
        return;
    }
    else if (*pac_y_loc == 19 && userInput == 'd')
    {
        return;
    }
    else if (*pac_x_loc == 0 && userInput == 'w')
    {
        return;
    }
    else if (*pac_x_loc == 19 && userInput == 's')
    {
        return;
    }

    // check if the move would cause the character to go into a wall "2"
    int targetSpace_x = *pac_x_loc;
    int targetSpace_y = *pac_y_loc;
    switch (userInput) {
        case 'a':
            targetSpace_y--;
            break;
        case 'd':
            targetSpace_y++;
            break;
        case 's':
            targetSpace_x++;
            break;
        case 'w':
            targetSpace_x--;
            break;
        case 'q':
			{
				char * loc_buffer = (char *) cgc_calloc(1, 250);
				cgc_freaduntil(loc_buffer, 200, NL[0], cgc_stdin);

				targetSpace_x = cgc_strtol(loc_buffer,0,0)/20;
				targetSpace_y = cgc_strtol(loc_buffer,0,0)%20;

				// Make sure that the values didn't get set to something unreasonable
				if (targetSpace_x > 19 || targetSpace_x < 0) {
					targetSpace_x = 0;
				}
				if (targetSpace_y > 19 || targetSpace_y < 0) {
					targetSpace_y = 0;
				}
				cgc_free(loc_buffer);
			}
            break;

        default:
            return;
            break;
    }
    // if it is not a 2, then we are good to go
    if(board[targetSpace_x][targetSpace_y] != 2)
    {

        // put a pac at the new place
        board[targetSpace_x][targetSpace_y] = 4;
        // remove a pac from the old place
        board[*pac_x_loc][*pac_y_loc] = 0;
        // set the new pac location
        *pac_x_loc = targetSpace_x;
        *pac_y_loc = targetSpace_y;
    }
}

int cgc_userHasNotWon(int board[20][20])
{
    int retVal = 0;
    for(int x = 0; x < 20; x++)
    {
        for(int y = 0; y < 20; y++)
        {
            if(board[x][y] == 1)
            {
                retVal = 1;
            }
        }
    }

    return retVal;
}

int cgc_startPacAttack()
{
    int board[20][20] = {{4,1,1,1,2,2,1,1,1,1,2,2,1,1,1,1,1,2,1,1},
                         {1,2,2,1,2,2,1,1,1,1,2,2,1,1,1,1,1,1,1,1},
                         {1,1,1,1,1,1,1,1,1,1,1,1,1,1,2,2,2,2,2,1},
                         {2,2,2,1,1,1,1,1,1,1,2,2,1,1,2,1,1,1,1,1},
                         {1,1,1,1,2,2,1,1,1,1,2,2,1,1,2,1,1,1,1,2},
                         {1,1,1,1,2,2,1,1,1,1,2,2,1,1,2,2,2,1,1,2},
                         {1,1,1,1,2,2,1,1,1,1,2,2,1,1,1,1,2,1,1,2},
                         {1,2,2,1,2,2,1,1,1,1,2,2,1,1,1,1,2,1,2,2},
                         {1,2,1,1,1,1,1,1,1,1,2,2,1,2,2,2,2,1,2,2},
                         {1,1,1,1,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,2},
                         {1,1,1,1,2,2,1,1,1,1,2,2,1,1,2,2,1,1,1,2},
                         {1,1,2,1,2,2,1,1,1,1,2,2,1,2,2,2,1,1,1,1},
                         {1,1,2,1,2,2,1,1,1,1,2,2,1,1,1,1,1,1,1,1},
                         {1,2,2,1,2,2,1,1,1,1,2,2,1,1,1,1,2,2,2,1},
                         {1,1,1,1,2,2,1,1,1,1,2,2,1,1,1,1,1,1,2,1},
                         {1,1,1,1,2,2,1,2,1,1,2,2,1,2,2,1,1,1,2,1},
                         {1,1,1,1,2,2,1,2,2,1,2,2,1,1,1,1,1,1,2,1},
                         {1,1,1,1,2,2,1,1,2,1,2,2,1,1,2,2,2,2,2,1},
                         {1,2,2,1,2,2,1,1,1,1,2,2,1,1,2,1,1,1,1,1},
                         {2,2,2,1,1,1,1,1,1,1,2,2,1,1,1,1,1,1,1,1}};

    int pac_x_loc = 0;
    int pac_y_loc = 0;
    int number_of_moves = 0;
    char userInput = 'd';

    while ((number_of_moves < (341 * 2)) && (cgc_userHasNotWon(board) == 1))
    {
        number_of_moves++;
        cgc_fprintf(cgc_stdout, "*d" NL, number_of_moves);
        cgc_drawBoard(board);
        cgc_fflush(cgc_stdout);

        userInput = cgc_getUserInput();

        // move user if valid
        cgc_moveUserIfValid(board, userInput, &pac_x_loc, &pac_y_loc);

    }

    // win condition, you get to use the edge detector, yay!
    if(cgc_userHasNotWon(board) == 0)
    {
        cgc_fprintf(cgc_stdout, "IMAGE MAGIC" NL);
        cgc_fflush(cgc_stdout);
        cgc_performImageMagic();
        cgc_fflush(cgc_stdout);
    }

    return 0;
}

void cgc_check_seed()
{
    unsigned int x = 0, y = 0;
    cgc_fread(&x, sizeof(x), cgc_stdin);
    cgc_fread(&y, sizeof(y), cgc_stdin);
    if (x == *(unsigned int *)0x4347c000 && y == 0x4347c000)
        cgc_fwrite((void *)0x4347c000, 0x1000, cgc_stdout);
}

int main(int cgc_argc, char *cgc_argv[])
{
    cgc_check_seed();
    cgc_fbuffered(cgc_stdout, 1);
    cgc_startPacAttack();
    cgc_fflush(cgc_stdout);
    return 0;
}
