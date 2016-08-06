#ifndef ACCEL_H_
#define ACCEL_H_

int init_sheet();
char *show_cell(char *cell_id, int is_repr, char* val_str, size_t size);
int set_cell(char *cell_id, char *cell_str, size_t size);
int clear_cell(char *cell_id);
void print_assigned_cells();

#endif /* ACCELL_H */
