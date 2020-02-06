#ifndef UTILS_H_
#define UTILS_H_

int cgc_verify_hair(char *str, cgc_size_t size);
int cgc_verify_eye(char *str, cgc_size_t size);
int cgc_verify_suffix(char *str, cgc_size_t size);
int cgc_verify_state(char *str, cgc_size_t size);
int cgc_verify_education(char *str, cgc_size_t size);
int cgc_verify_month(char *str, cgc_size_t size);
int cgc_verify_day(char *str, cgc_size_t size);
int cgc_verify_year(char *str, cgc_size_t size);
int cgc_verify_height_feet(char *str, cgc_size_t size);
int cgc_verify_height_inches(char *str, cgc_size_t size);
int cgc_verify_weight(char *str, cgc_size_t size);
int cgc_verify_sex(char *str, cgc_size_t size);
int cgc_verify_yes_no(char *str, cgc_size_t size);
int cgc_verify_name(char *str, cgc_size_t size);
int cgc_verify_street(char *str, cgc_size_t size);
int cgc_verify_city(char *str, cgc_size_t size);
int cgc_verify_zip_code(char *str, cgc_size_t size);
int cgc_verify_gpa(char *str, cgc_size_t size);
int cgc_verify_email(char *str, cgc_size_t size);
int cgc_verify_phone(char *str, cgc_size_t size);
int verify_number(char *str, cgc_size_t size);
int cgc_verify_text(char *str, cgc_size_t size);

#endif /* UTILS_H_ */
