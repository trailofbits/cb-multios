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
#include "cgc_blogpost.h"
#include "cgc_asciiart.h"
#include "cgc_picture.h"

BlogPost *BlogPost::create_blog_post(User *user, char *_title)
{
    if (!user || !_title || !*_title)
        return NULL;

    return new BlogPost(user, _title);
}

BlogPost::BlogPost(User *user, char *_title)
{
    owner = user;
    cgc_strcpy(title, _title);
    cgc_memset(post_order, 0, sizeof(post_order));
    total_views = 0;
}

BlogPost::~BlogPost()
{

}

char *BlogPost::get_title()
{
    return title;
}

bool BlogPost::add_text_block(char *text)
{
    cgc_size_t len = cgc_strlen(post_order);
    if (!text || !*text) {
        cgc_printf("Can't add empty text\n");
        return false;
    }

    if (len >= sizeof(post_order)) {
        cgc_printf("Post is too big\n");
        return false;
    }

    text_blocks.add(text);
    post_order[len++] = 't';
    return true;
}

bool BlogPost::add_file(File *file)
{
    cgc_size_t len;
    if (!file) {
        cgc_printf("Bad file\n");
        return false;
    }

    len = cgc_strlen(post_order);
    if (len >= sizeof(post_order)) {
        cgc_printf("Post is too big\n");
        return false;
    }

    files.add(file);
    post_order[len] = 'f';
    post_order[++len] = '\0';
    return true;
}

void BlogPost::like(User *user)
{
    for (int i=0; i < likes.length(); i++) {
        if (likes[i] == user) {
            cgc_printf("You already liked this\n");
            return;
        }
    }

    likes.add(user);
    owner->add_like();
}

void BlogPost::print_post()
{
    cgc_size_t text_idx = 0, file_idx = 0;
    File *file;

    cgc_printf("---%s---\n", title);
    for(cgc_size_t i = 0; i < cgc_strlen(post_order); i++) {
        switch(post_order[i]) {
        case 't':
            cgc_printf("%s\n", text_blocks[text_idx++]); break;
        case 'f':
            file = files[file_idx++];
            switch(file->tell_filetype()) {
            case ASCIIART:
                ((AsciiArt *)(file))->print_asciiart(); break;
            case PICTURE:
                ((Picture *)(file))->print_picture(); break;
            default:
                cgc_printf("Unsupported file type\n");
            }
            break;
        default:
            cgc_printf("Bad post\n");
            return;
        }
    }
}
