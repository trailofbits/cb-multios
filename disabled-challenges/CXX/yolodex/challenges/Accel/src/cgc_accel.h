#ifndef ACCEL_H_
#define ACCEL_H_

int cgc_init_sheet();
char *cgc_show_cell(char *cell_id, int is_repr, char* val_str, cgc_size_t size);
int cgc_set_cell(char *cell_id, char *cell_str, cgc_size_t size);
int cgc_clear_cell(char *cell_id);
void cgc_print_assigned_cells();

#endif /* ACCELL_H */
