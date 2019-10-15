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
extern "C" {
#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"
};

#include "cgc_orderiomanager.h"


#define BUF_SIZE 512

void print_banner()
{
    cgc_printf("Welcome to the CGC Pizzeria order management system.\n");
}

int main(int cgc_argc, char *cgc_argv[])
{
    OrderIoManager oim;
    IoManager pwio(BUF_SIZE);
    bool authenticated = false, shutdown = false;
    int choice;
    int pw_attempts;

    while (!shutdown) {
        pw_attempts = 10;
        while (!authenticated) {
            cgc_printf("Enter system password: ");
            if(!pwio.readline()) {
                cgc_printf("Incorrect Password!\n");
            } else if (cgc_strcmp("pizzapass", pwio.get_last_input()) == 0) {
            //else if (strcmp("pp", pwio.get_last_input()) == 0) {
                authenticated = true;
                cgc_printf("\n");
                print_banner();
            }  else if (cgc_strcmp("quit", pwio.get_last_input()) == 0) {
                cgc_printf("Received termination string\n");
                shutdown = true;
                break;
            } else {
                cgc_printf("Incorrect Password!\n");
                if (!(--pw_attempts)) {
                    cgc_printf("Too many bad attempts\n");
                    shutdown = true;
                    break;
                }
            }
        }

        while (authenticated) {
            cgc_printf("1. Input Order\n");
            cgc_printf("2. Update Order\n");
            cgc_printf("3. View One Orders\n");
            cgc_printf("4. View All Orders\n");
            cgc_printf("5. Delete Order\n");
            cgc_printf("6. Clear All Orders\n");
            cgc_printf("7. Logout\n");
            cgc_printf("Choice: ");

            choice = oim.readnum();
            switch(choice) {
            case 1:
                if(!oim.input_order(-1))
                    cgc_printf("Wow. that failed pretty bad");
                break;
            case 2:
                oim.update_order();
                break;
            case 3:
                oim.view_single_order();
                break;
            case 4:
                oim.print_orders();
                break;
            case 5:
                if (oim.delete_order())
                    cgc_printf("Succesfully removed order\n");
                break;
            case 6:
                oim.clear_all_orders();
                cgc_printf("Cleared all previous orders\n");
                break;
            case 7:
                oim.clear_all_orders(true);
                cgc_printf("Logging out\n");
                authenticated = false;
                break;
            default:
                cgc_printf("Bad Selection\n");
            }
        }
    }
}
