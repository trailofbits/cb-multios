#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"
#include "cgc_ctype.h"

char *valid_hair_colors[] = { "Bald", "Black", "Blonde or Strawbery", "Brown", "Gray or Partially Gray",
                             "Red or Auburn", "Sandy", "White", "Blue", "Green", "Orange", "Pink", "Purple",
                             "Unspecified or Unknown" };
char *valid_eye_colors[] = { "Black", "Blue", "Brown", "Gray", "Green", "Hazel", "Maroon", "Multicolored",
                            "Pink", "Unknown" };

char *valid_suffixes[] = { "Jr", "Sr", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "Other"};

char *valid_states[] = { "AL", "AK", "AZ", "AR", "CA", "CO", "CT", "DE", "DC", "FL", "GA", "HI", "ID", "IL",
                         "IN", "IA", "KS", "KY", "LA", "ME", "MD", "MA", "MI", "MN", "MS", "MO", "MT", "NE",
                         "NV", "NH", "NJ", "NM", "NY", "NC", "ND", "OH", "OK", "OR", "PA", "RI", "SC", "SD",
                         "TN", "TX", "UT", "VT", "VA", "WA", "WV", "WI", "WY" };


char *education_levels[] = { "HS", "COLLEGE", "ADV" };

static int cgc_verify_choice(char **valid_choices, char *choice, cgc_size_t num_elements)
{
    cgc_size_t i;
    for (i = 0; i < num_elements; i++) {
#ifdef PATCHED
        if (cgc_strlen(valid_choices[i]) == cgc_strlen(choice) &&
                cgc_memcmp(valid_choices[i], choice, cgc_strlen(valid_choices[i])) == 0)
#else
        if (cgc_memcmp(valid_choices[i], choice, cgc_strlen(valid_choices[i])) == 0)
#endif
            return 0;
    }

    return -1;
}

int cgc_verify_hair(char *str, cgc_size_t size) {
    return cgc_verify_choice(valid_hair_colors, str, sizeof(valid_hair_colors)/sizeof(char*));
}

int cgc_verify_eye(char *str, cgc_size_t size) {
    return cgc_verify_choice(valid_eye_colors, str, sizeof(valid_eye_colors)/sizeof(char*));
}


int cgc_verify_suffix(char *str, cgc_size_t size) {
    return cgc_verify_choice(valid_suffixes, str, sizeof(valid_suffixes)/sizeof(char*));
}

int cgc_verify_state(char *str, cgc_size_t size) {
    return cgc_verify_choice(valid_states, str, sizeof(valid_states)/sizeof(char*));
}

int cgc_verify_education(char *str, cgc_size_t size) {
    return cgc_verify_choice(education_levels, str, sizeof(education_levels)/sizeof(char*));
}

int cgc_verify_month(char *str, cgc_size_t size) {
    int len = cgc_strlen(str) + 1;
    if (len != size)
        return -1;

    int month;
    month = cgc_strtol(str, NULL, 10);
    if (month <= 0 || month > 12)
        return -1;

    return 0;
}

int cgc_verify_day(char *str, cgc_size_t size) {
    int len = cgc_strlen(str) + 1;
    if (len != size)
        return -1;

    int day = cgc_strtol(str, NULL, 10);
    if (day <= 0 || day > 31)
        return -1;

    return 0;
}

int cgc_verify_year(char *str, cgc_size_t size) {
    int len = cgc_strlen(str) + 1;
    if (len != size)
        return -1;

    int year = cgc_strtol(str, NULL, 10);
    if (year < 1900 || year > 2014)
        return -1;

    return 0;
}

int cgc_verify_height_feet(char *str, cgc_size_t size) {
    int len = cgc_strlen(str) + 1;
    if (len > size)
        return -1;

    int feet = cgc_strtol(str, NULL, 10);
    if (feet < 1 || feet > 9)
        return -1;

    return 0;
}

int cgc_verify_height_inches(char *str, cgc_size_t size) {
    int len = cgc_strlen(str) + 1;
    if (len > size)
        return -1;

    int inches = cgc_strtol(str, NULL, 10);
    if (inches < 0 || inches > 11)
        return -1;

    return 0;
}

int cgc_verify_weight(char *str, cgc_size_t size) {
    int len = cgc_strlen(str) + 1;
    if (len > size)
        return -1;

    int weight = cgc_strtol(str, NULL, 10);
    if (weight < 50 || weight > 500)
        return -1;

    return 0;
}

int cgc_verify_sex(char *str, cgc_size_t size) {
    int len = cgc_strlen(str) + 1;
    if (len != size)
        return -1;

    if (str[0] != 'M' && str[0] != 'F')
        return -1;

    return 0;
}

int cgc_verify_yes_no(char *str, cgc_size_t size) {
    int len = cgc_strlen(str) + 1;
    if (len != size)
        return -1;

    if (str[0] != 'Y' && str[0] != 'N')
        return -1;

    return 0;
}

int cgc_verify_name(char *str, cgc_size_t size)
{
    int i, len = cgc_strlen(str) + 1;
    if (len > size || len < 2)
        return -1;
    len--;

    for (i = 0; i < len; i++)
        if (!cgc_isalpha(str[i]) && str[i] != '\'')
            return -1;

    return 0;
}

int cgc_verify_street(char *str, cgc_size_t size)
{
    int i, len = cgc_strlen(str) + 1;
    if (len > size || len < 5)
        return -1;
    len--;

    for (i = 0; i < len; i++) {
        char c = str[i];
        if (!cgc_isalnum(c) && c != '\'' && c != ' ' && c != ',')
            return -1;
    }

    return 0;
}

int cgc_verify_city(char *str, cgc_size_t size)
{
    int i, len = cgc_strlen(str) + 1;
    if (len > size || len < 5)
        return -1;
    len--;

    for (i = 0; i < len; i++) {
        char c = str[i];
        if (!cgc_isalpha(c) && c != '\'' && c != ' ')
            return -1;
    }

    return 0;
}

int cgc_verify_zip_code(char *str, cgc_size_t size)
{
    int i, len = cgc_strlen(str) + 1;
    if (len != size)
        return -1;
    len--;

    if (str[0] == '0')
        return -1;

    for (i = 0; i < len; i++) {
        char c = str[i];
        if (!cgc_isdigit(c))
            return -1;
    }

    return 0;
}


int cgc_verify_gpa(char *str, cgc_size_t size)
{
    int i, len = cgc_strlen(str) + 1;
    if (len > size)
        return -1;
    len--;

    for (i = 0; i < len; i++) {
        char c = str[i];
        if (i == 1) {
            if (c != '.')
                return -1;
            else
                continue;
        }
        if (!cgc_isdigit(c)) {
            return -1;
        }
    }

    return 0;
}

int cgc_verify_email(char *str, cgc_size_t size)
{
    int i, len = cgc_strlen(str) + 1, at_count = 0;
    if (len > size || len < 3)
        return -1;
    len--;

    for (i = 0; i < len; i++) {
        char c = str[i];
        if (!cgc_isalnum(c) && c != '@' && c != '-' && c != '.' && c != '_')
            return -1;
        if (c == '@' && ++at_count == 2)
            return -1;
    }

    if (at_count != 1)
        return -1;

    return 0;
}

int cgc_verify_phone(char *str, cgc_size_t size)
{
    int i, len = cgc_strlen(str) + 1, at_count = 0;
    if (len != size)
        return -1;
    len--;

    for (i = 0; i < len; i++) {
        char c = str[i];
        if (i == 3 || i == 7) {
            if (c != '-')
                return -1;
            else
                continue;
        }
        if (!cgc_isdigit(c)) {
            return -1;
        }
    }

    return 0;
}

int cgc_verify_number(char *str, cgc_size_t size)
{
    int i, len = cgc_strlen(str) + 1;
    if (len > size)
        return -1;
    len--;

    for (i = 0; i < len; i++)
        if (!cgc_isdigit(str[i]))
            return -1;

    return 0;
}

int cgc_verify_text(char *str, cgc_size_t size)
{
    int i, len = cgc_strlen(str) + 1;
    if (len > size)
        return -1;
    len--;

    for (i = 0; i < len; i++)
        if (!cgc_isprint(str[i]))
            return -1;

    return 0;
}

