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
#include "user.h"
#include "io.h"

User::User(char *_username, char *_pw, char *_friend_code)
{
    profile = NULL;
    memcpy(username, _username, sizeof(username));
    memcpy(pw, _pw, sizeof(pw));
    memcpy(friend_code, _friend_code, sizeof(friend_code));
    total_likes = 0;

}

User::~User()
{
    posts.clear_list(true);
    friends.clear_list(true);
    if (profile)
        delete profile;
}

BlogPost *User::get_post(int idx)
{
    if (idx < posts.length())
        return posts[idx];
    else
        return NULL;
}

char *User::get_username()
{
    return username;
}

bool User::is_full_user()
{
    //printf("f len = %d, p len = %d, tot_like = %d\n", friends.length(), posts.length(), total_likes);
    return (friends.length() >= 3 && posts.length() >= 5 && total_likes > 5);
}

bool User::check_password(char *pw_attempt)
{
    return (strcmp(pw, pw_attempt) == 0);
}

bool User::add_friend(User *new_friend, char *fc_attempt)
{
    if (new_friend == this) {
        printf("Trying to add self\n");
        return false;
    }

    if (!new_friend || strcmp(new_friend->friend_code, fc_attempt))
        return false;

    if (!friends.find(new_friend))
        return friends.add(new_friend);
    else
        return false;
}

bool User::edit_profile()
{
    char *temp_profile;
    printf("Enter new profile info (end with: ```)\n");
    temp_profile = IO::iotextdup(1024);
    if (temp_profile) {
        if (profile)
            delete[] profile;
        profile = temp_profile;
        return true;
    } else {
        return false;
    }
}

bool User::add_post()
{
    char *text = NULL;
    File *file = NULL;
    int selection = 0;
    BlogPost *post = NULL;
    printf("Enter post title: \n\t");
    if(!IO::readline(128)) {
        printf("Bad title. Try again\n");
            return false;
    } else {
        post = BlogPost::create_blog_post(this, IO::buf());
    }

    while(true) {
        printf("Enter Post Text (end with: ```):\n");
        text = IO::iotextdup(4096);
        if(text) {
            post->add_text_block(text);
        }

        if (is_full_user()) {
            printf("Upload Image?\n");
            printf("1. Yes\n");
            printf("2. No\n");
            printf("Selection: ");
            selection = IO::readnum();

            if (selection == 1) {
                file = IO::upload_file();
                if (file)
                    post->add_file(file);
            }
        }

        printf("Add more Text?\n");
        printf("1. Yes\n");
        printf("2. No\n");
        printf("Selection: ");
        selection = IO::readnum();

        if (selection == 1) {
            continue;
        }
        break;
    }

    return posts.add(post);
}

bool User::delete_post()
{
    int selection;
    printf("Select a post to delete:\n");
    printf("0. Go Back\n");
    list_posts();
    printf("Selection: ");
    selection = IO::readnum();

    if (selection == 0) {
        printf("Returning to main menu\n");
        return false;
    }

    if (selection > posts.length()) {
        printf("Bad Selection\n");
        printf("Returning to main menu\n");
        return false;
    }

    return posts.remove(--selection);
}

size_t User::num_posts()
{
    return posts.length();
}

void User::print_profile()
{
    printf("User %s's profile:\n", username);
    if (profile && strlen(profile))
        printf("%s\n", profile);
    else
        printf("No profile yet!\n");
}

void User::list_posts()
{
    for (int i = 0; i < posts.length(); i++)
        printf("%d - %s\n", i+1, posts[i]->get_title());
}

void User::print_post(size_t idx)
{
    if (idx < 1 || idx > posts.length()) {
        printf("%s's post id, %d, was not found\n", username, idx);
        return;
    }

    printf("Post by: %s\n", username);
    posts[--idx]->print_post();
}

void User::like_post(User *reg_user, size_t idx)
{
    if (!reg_user) {
        printf("Only registered users can like a post\n");
        return;
    }

    if (reg_user == this) {
        printf("Sorry, you can't like your own post...\n");
        return;
    }

    if (idx < 1 || idx > posts.length()) {
        printf("%s's post id, %d, was not found\n", username, idx);
        return;
    }

    posts[--idx]->like(reg_user);
    printf("Liked!\n");
}

void User::list_friends() {
    for (int i = 0; i < friends.length(); i++)
        printf("%d - %s\n", i+1, friends[i]->username);
}

bool User::unfriend()
{
    int selection;
    printf("Select a user to unfriend:\n");
    printf("0. Go Back\n");
    list_friends();
    printf("Selection: ");
    selection = IO::readnum();

    if (selection == 0) {
        printf("Returning to main menu\n");
        return false;
    }

    if (selection > friends.length()) {
        printf("Bad Selection\n");
        printf("Returning to main menu\n");
        return false;
    }

    return friends.remove(--selection);
}

void User::add_like()
{
    total_likes++;
}

