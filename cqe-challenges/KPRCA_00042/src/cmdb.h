#ifndef CMDB_H_
#define CMDB_H_

void init_movies();
int rent_movie(int id);
int return_movie(int id);
void list_all_movies();
void list_owned_movies();
void list_rented_movies();
int get_num_owned_movies();
int get_num_rented_movies();

#endif
