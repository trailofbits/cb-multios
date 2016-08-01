#ifndef CMDB_BACKEND_H_
#define CMDB_BACKEND_H_

typedef struct {
    char *name;
    char *desc;
    short year;
    char score;
    char *type;
    char *mpaa;
    char is_checked_out;
}  cmdb_entry_t;

typedef enum {ALL, OWNED, RENTED} filter_e;

char *get_genre(int id);
char *get_rating(int id);
size_t get_list_length();
size_t get_num_rented();
int add_movie(char *name, char *desc, short year, char score, char *type, char *mpaa);
int add_entry(cmdb_entry_t *entry);
int delete_entry(int id);
int rent_entry(int id);
int return_entry(int id);
cmdb_entry_t *find_entry(char *name);
cmdb_entry_t *get_entry(int id);
void print_entry(cmdb_entry_t *entry);
void print_movies(filter_e filter);
void print_genres();
void print_ratings();
void dag(char *new_genre);
void dar(char *new_rating);

#endif
