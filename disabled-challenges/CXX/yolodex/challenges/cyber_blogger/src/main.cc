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
#include "cgc_blog.h"
#include "cgc_io.h"
#include "cgc_user.h"

void call_ctors(void);

void print_menu(User *current_user)
{
    cgc_printf("Select an option\n");
    if (!current_user) {
        cgc_printf("1. Register\n");
        cgc_printf("2. Log in\n");
        cgc_printf("3. View a user's posts\n");
        cgc_printf("4. View a user's profile\n");
        cgc_printf("5. Quit\n");
    } else {
        cgc_printf("1. Add new blog post\n");
        cgc_printf("2. Delete blog post\n");
        cgc_printf("3. Update profile\n");
        cgc_printf("4. Add a friend\n");
        cgc_printf("5. View my friends\n");
        cgc_printf("6. Unfriend someone\n");
        cgc_printf("7. View my posts\n");
        cgc_printf("8. View my profile\n");
        cgc_printf("9. View a user's posts\n");
        cgc_printf("10. View a user's profile\n");
        cgc_printf("11. Log out\n");
    }
}

bool make_selection(User *&current_user)
{
    cgc_size_t selection = 0;
    cgc_printf("Selection: ");
    selection = IO::readnum();
    if (!current_user) {
        switch(selection) {
        case 1:
            Blog::register_user(); break;
        case 2:
            current_user = Blog::log_in(); break;
        case 3:
            Blog::view_user_posts(); break;
        case 4:
            Blog::view_user_profile(); break;
        case 5:
            cgc_printf("Quitting\n");
            return false;
        default:
            cgc_printf("Bad Selection\n");
        }
    } else {
        switch(selection) {
        case 1:
            current_user->add_post(); break;
        case 2:
            current_user->delete_post(); break;
        case 3:
            current_user->edit_profile(); break;
        case 4:
            Blog::add_friend(current_user); break;
        case 5:
            current_user->list_friends(); break;
        case 6:
            current_user->unfriend(); break;
        case 7:
            Blog::view_user_posts(current_user, current_user); break;
        case 8:
            Blog::view_user_profile(current_user); break;
        case 9:
            Blog::view_user_posts(current_user); break;
        case 10:
            Blog::view_user_profile(); break;
        case 11:
            cgc_printf("Logging Out\n");
            current_user = NULL;
            break;
        default:
            cgc_printf("Bad Selection\n");
        }
    }

    return true;
}

int main(int cgc_argc, char *cgc_argv[])
{
    User *current_user = NULL;
    cgc_size_t selection = 0;
    bool not_done = true;

    

    while (not_done) {
        print_menu(current_user);
        not_done = make_selection(current_user);
    }
}
