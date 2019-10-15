#ifndef BLOGPOST_H_
#define BLOGPOST_H_

#include "cgc_list.h"
#include "cgc_file.h"
#include "cgc_user.h"

class User;
class BlogPost
{
private:
    char title[128];
    List<char *> text_blocks;
    List<File *> files;
    char post_order[32];

    int total_views;
    List<User *> likes;
    User *owner;

    BlogPost(User *user, char *_title);
public:
    static BlogPost *create_blog_post(User *user, char *_title);
    virtual ~BlogPost();
    char *get_title();
    bool add_text_block(char *text);
    bool add_file(File *file);
    void like(User *user);

    void print_post();
};

#endif

