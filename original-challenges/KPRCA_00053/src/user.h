#ifndef USER_H_
#define USER_H_

#include "list.h"
#include "blogpost.h"

class BlogPost;

class User
{
private:
    char username[16];
    char pw[16];
    char friend_code[16];
    char *profile;
    unsigned int total_likes;

    List<BlogPost *> posts;
    List<User *> friends;
public:
    User(char *_username, char *_pw, char *_friend_code);
    ~User();

    BlogPost *get_post(int idx);
    char *get_username();
    bool is_full_user(); //more than 2 posts and more than 10 likes
    bool check_password(char *pw_attempt);
    bool add_friend(User *user, char *fcode_attempt);
    bool edit_profile();
    bool add_post();
    bool delete_post();
    size_t num_posts();

    void print_profile();
    void list_posts();
    void print_post(size_t idx);
    void like_post(User *reg_user, size_t idx);
    void list_friends();
    bool unfriend();
    void add_like();
};

#endif
