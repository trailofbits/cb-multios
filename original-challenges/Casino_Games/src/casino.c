/*

Author: Debbie Nuttall <debbie@cromulence.co>

Copyright (c) 2015 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include <libcgc.h>
#include "stdlib.h"
#include "casino.h"
#include "deck.h"
#include "blackjack.h"
#include "poker.h"
#include "slots.h"
#include "prng.h"

int payouts[NUMBER_OF_PAYOUTS] = {
    4,      // SLOTS_COLUMN_MATCH
    4,      // SLOTS_ROW_MATCH
    500,    // POKER_ROYAL_FLUSH
    200,    // POKER_STRAIGHT_FLUSH
    40,     // POKER_FLUSH
    100,    // POKER_FOUR_OF_A_KIND
    50,     // POKER_FULL_HOUSE
    10,     // POKER_TWO_PAIR
    20,     // POKER_THREE_OF_A_KIND
    10,     // POKER_JACKS_OR_BETTER
    30,     // POKER_STRAIGHT
    10,     // BLACKJACK_PUSH
    25,     // BLACKJACK_BLACKJACK
    20      // BLACKJACK_WIN
};

// Searches player list for matching player number. 
// Returns pointer to player_info struct or 0 if not found.
player_info *lookup_by_number(int number, player_info *root_player)
{
    player_info *player = root_player;
    while (player != 0)
    {
        if (player->number == number)
        {
            break;
        }
        else
        {
            player = player->next;
        }
    }
    return player;  
}

// Requests a player number from the user and returns the associated player info struct.
player_info *login_player_by_number(player_info *root_player)
{
    printf("Enter Player Number:");
    char numbuf[12] = "";
    receive_fixed_input(numbuf, '\n', sizeof(numbuf) - 1);
    int number = atoi(numbuf);
    player_info *player = lookup_by_number(number, root_player);
    if (player == 0)
    {
        printf("Player not found\n");
    }
    else
    {
        printf("Hello, @s!\n", player->name);
    }
    return player;
}

// Prints info about a player
void print_player_info(player_info *player)
{
    if (player == 0)
    {
        printf("Player does not exist\n");
        return;
    }
    printf("Player Name: @s\n", player->name);
    printf("Player Number: @d\n", player->number);
    printf("Blackjack Score: @d\n", player->blackjack_score);
    printf("Poker Score: @d\n", player->poker_score);
    printf("Slots Score: @d\n", player->slots_score);
    printf("Player Wallet Balance: @d\n", player->wallet);
    printf("\n");
}

// Registers a new player and adds new player to the beginning of the linked list of players. 
// Returns the new root_player node. 
player_info *register_player(player_info *root_player)
{
    player_info *new_player;
    if (allocate(sizeof(player_info), 0, (void **)&new_player) != 0)
    {
        printf("Error allocating memory for new player\n");
        return root_player;
    }
    memset(new_player, 0, sizeof(player_info));
    do
    {
        new_player->number = prng() & 0x7fffffff; // positive numbers only
    } while (lookup_by_number(new_player->number, root_player) != 0);
    
    printf("Enter your name:");
    receive_fixed_input(new_player->name, '\n', sizeof(new_player->name) - 1);
    printf("How much cash do you want to spend?:");
    char input[12] = "";
    receive_fixed_input(input, '\n', sizeof(input) - 1);
    new_player->wallet = atoi(input);
    if ((new_player->wallet > 1000) || (new_player->wallet < 0))
    {
        new_player->wallet = 1000;
    }
    print_player_info(new_player);

    new_player->next = root_player;
    return new_player;
}


void print_all_players(player_info *player)
{
    while( player)
    {
        print_player_info(player);
        player = player->next;
    }
}

// Decodes one character into 4 bits of data.
// Invaid input terminates the program.
int lookup(char byte)
{
     switch(byte)
    {
        case '!':
            return 0;
        case '@':
            return 1;
        case '#':
            return 2;
        case '$':
            return 3;
        case '%':
            return 4;
        case '^':
            return 5;
        case '&':
            return 6;
        case '+':
            return 7;
        case '=':
            return 8;
        case ':':
            return 9;
        case '>':
            return 10;
        case '<':
            return 11;
        case '|':
            return 12;
        case '?':
            return 13;
        case '~':
            return 14;
        case '*':
            return 15;
        default:
            _terminate(1);
    }
}

// Decodes a string of ascii characters into binary data.
// Invalid input will terminate the program. 
// Can write up to size bytes to *decoded.
void decode(char *encoded, char *decoded, size_t size)
{
    char *inp = encoded;
    char *outp = decoded;
    while(inp < encoded + size)
    {
        char byte;
        if ((*inp) == '`')
        {
            inp++;
            byte = 0;
        }
        else
        {
            byte = lookup(*inp++);
            byte = lookup(*inp++) << 4 | byte;
        }
        *outp++ = byte;
    }
}

// Runs the programming interface
void programming_interface()
{
    int ret;
    size_t bytes_read;
    int config_size;
    char *config_data;

    // Read config size
    ret = receive(STDIN, &config_size, sizeof(config_size) , &bytes_read);
    if ((ret != 0) || (bytes_read == 0))
    {
        _terminate(2);
    }
    // Verify config size
    if ((config_size <= 0) || (config_size > sizeof(payouts) * 2))
    {
        _terminate(1);
    }

    // Allocate data for config
    ret = allocate(config_size, 1, (void **) &config_data);
    if ((ret != 0) || (config_data == 0))
    {
      _terminate(2);
    }

    // Read entire config
    int bytes_received = 0;
    char *input = config_data;
    while (bytes_received < config_size) {
        ret = receive(STDIN, input, config_size - bytes_received, &bytes_read);
        if (ret != 0)
        {
           _terminate(2);
        }
        bytes_received += bytes_read;
        input += bytes_read;
    }

    // Decode config
#ifdef PATCHED
    // Provide additional stack space for decoded data to overflow to
    int new_payouts[NUMBER_OF_PAYOUTS * 2];
#else 
    int new_payouts[NUMBER_OF_PAYOUTS];
#endif

    decode(config_data, (char *)new_payouts, config_size);

    // Update payouts
    memcpy(&payouts, &new_payouts, sizeof(payouts));

    deallocate(config_data, config_size);
}


int main(void) {
#ifdef PATCHED
    char name[84];
#else
    char name[64];
#endif

    // Get player name
    int ret;
    size_t bytes_read;
    printf("Enter your name:");
    ret = receive(STDIN, name, 83, &bytes_read);
    if ((ret != 0) || (bytes_read == 0))
    {
        _terminate(2);
    }
    name[bytes_read] = 0;
    if (name[strlen(name)-1] == '\n')
    {
        name[strlen(name)-1] = '\0';
    }
    printf("Hello, @s!\n", name);

    // Seed the PRNG
    uint64_t seed = 0;
    for (int i = 0; i<strlen(name); i++)
    {
        seed = (seed << 8) | (((seed >> 56) ^ name[i]));
    }
    sprng(seed);

    // Grant access to programming interface when name is "71db10261c"
    if (seed == 0x6462313032360652LL)
    {
        printf("Access Granted\n");
        programming_interface();
    }

    // Setup player info
    player_info *current_player = 0;
    player_info *root_player = 0;

    // Play the game
    while( (current_player == 0) || 
        (current_player->wallet <= BREAK_THE_BANK) )
    {
        printf("\n");
        printf("1. Play Blackjack\n");
        printf("2. Play Poker\n");
        printf("3. Play Slots\n");
        printf("4. Enter a Players Club Number\n");
        printf("5. Register a new Player\n");
        printf("6. Show Player Status\n");
        printf("7. Show All Players\n");
        printf("8. Exit\n");
        printf("Select a number:");

        char input;
        receive_fixed_input(&input, '\n', sizeof(input));
        
        switch(input)
        {
            case '1':
                printf("Play Blackjack\n");
                blackjack(current_player);
                break;
            case '2':
                printf("Play Poker\n");
                poker(current_player);
                break;
            case '3':
                printf("Play Slots\n");
                slots(current_player);
                break;
            case '4':
                // Enter Player Number
                current_player = login_player_by_number(root_player);
                break;
            case '5':
                printf("Register a new Player\n");
                root_player = register_player(root_player);
                break;
            case '6':
                // Check player_status
                print_player_info(current_player);
                break;
            case '7':
                printf("Show All Players\n");
                print_all_players(root_player);
                break;
            case '8':
                printf("you don't really want to leave do you?\n");
                receive_fixed_input(&input, '\n', sizeof(input));
                if (input == 'y')
                {
                    if (current_player == 0)
                    {
                        printf("Goodbye, stranger\n");
                        _terminate(0);
                    }
                    if (current_player->blackjack_score == 0)
                    {
                        printf("But you didn't even play blackjack :(\n");
                        _terminate(0);
                    }
                    else if (current_player->poker_score == 0)
                    {
                        printf("But you didn't even play poker :(\n");
                        _terminate(0);
                    }
                    else if (current_player->slots_score == 0)
                    {
                        printf("But you didn't even play slots :(\n");
                        _terminate(0);
                    }
                    else
                    {
                        printf("Okay, you've had enough ;)\n");
                        goto finish;
                    }
                }
                break;
            default:
                break;
        }

    }

    printf("You broke the bank!\n");

    // End of game
    finish:
        printf("Goodbye\n");

}
