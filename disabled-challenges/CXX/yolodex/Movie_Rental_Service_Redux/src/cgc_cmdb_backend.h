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

char *cgc_get_genre(int id);
char *cgc_get_rating(int id);
cgc_size_t cgc_get_list_length();
cgc_size_t cgc_get_num_rented();
int cgc_add_movie(char *name, char *desc, short year, char score, char *type, char *mpaa);
int cgc_add_entry(cmdb_entry_t *entry);
int cgc_delete_entry(int id);
int cgc_rent_entry(int id);
int cgc_return_entry(int id);
cmdb_entry_t *cgc_find_entry(char *name);
cmdb_entry_t *cgc_get_entry(int id);
void cgc_print_entry(cmdb_entry_t *entry);
void cgc_print_movies(filter_e filter);
void cgc_print_genres();
void cgc_print_ratings();
void cgc_dag(char *new_genre);
void cgc_dar(char *new_rating);

#endif
