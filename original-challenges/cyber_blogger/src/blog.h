#ifndef BLOG_H_
#define BLOG_H_

#include "user.h"

namespace Blog {
    User *get_user(char *username);
    void register_user();
    User *log_in();
    void add_friend(User *user);
    void view_user_profile(User *user=NULL);
    void view_user_posts(User *reg_user=NULL, User *user=NULL, int post_selection=0);
    void view_post();;
}

#endif
