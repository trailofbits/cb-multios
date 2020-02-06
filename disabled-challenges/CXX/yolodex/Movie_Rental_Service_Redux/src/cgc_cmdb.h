#ifndef CMDB_H_
#define CMDB_H_

void cgc_init_movies();
int cgc_rent_movie(int id);
int cgc_return_movie(int id);
void cgc_list_all_movies();
void cgc_list_owned_movies();
void cgc_list_rented_movies();
int cgc_get_num_owned_movies();
int cgc_get_num_rented_movies();

#endif
