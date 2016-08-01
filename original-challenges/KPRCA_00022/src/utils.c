#include <libcgc.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

static int verify_choice(char **valid_choices, char *choice, size_t num_elements)
{
    size_t i;
    for (i = 0; i < num_elements; i++) {
#ifdef PATCHED
        if (strlen(valid_choices[i]) == strlen(choice) &&
                memcmp(valid_choices[i], choice, strlen(valid_choices[i])) == 0)
#else
        if (memcmp(valid_choices[i], choice, strlen(valid_choices[i])) == 0)
#endif
            return 0;
    }

    return -1;
}

int verify_hair(char *str, size_t size) {
    return verify_choice(valid_hair_colors, str, sizeof(valid_hair_colors)/sizeof(char*));
}

int verify_eye(char *str, size_t size) {
    return verify_choice(valid_eye_colors, str, sizeof(valid_eye_colors)/sizeof(char*));
}


int verify_suffix(char *str, size_t size) {
    return verify_choice(valid_suffixes, str, sizeof(valid_suffixes)/sizeof(char*));
}

int verify_state(char *str, size_t size) {
    return verify_choice(valid_states, str, sizeof(valid_states)/sizeof(char*));
}

int verify_education(char *str, size_t size) {
    return verify_choice(education_levels, str, sizeof(education_levels)/sizeof(char*));
}

int verify_month(char *str, size_t size) {
    int len = strlen(str) + 1;
    if (len != size)
        return -1;

    int month;
    month = strtol(str, NULL, 10);
    if (month <= 0 || month > 12)
        return -1;

    return 0;
}

int verify_day(char *str, size_t size) {
    int len = strlen(str) + 1;
    if (len != size)
        return -1;

    int day = strtol(str, NULL, 10);
    if (day <= 0 || day > 31)
        return -1;

    return 0;
}

int verify_year(char *str, size_t size) {
    int len = strlen(str) + 1;
    if (len != size)
        return -1;

    int year = strtol(str, NULL, 10);
    if (year < 1900 || year > 2014)
        return -1;

    return 0;
}

int verify_height_feet(char *str, size_t size) {
    int len = strlen(str) + 1;
    if (len > size)
        return -1;

    int feet = strtol(str, NULL, 10);
    if (feet < 1 || feet > 9)
        return -1;

    return 0;
}

int verify_height_inches(char *str, size_t size) {
    int len = strlen(str) + 1;
    if (len > size)
        return -1;

    int inches = strtol(str, NULL, 10);
    if (inches < 0 || inches > 11)
        return -1;

    return 0;
}

int verify_weight(char *str, size_t size) {
    int len = strlen(str) + 1;
    if (len > size)
        return -1;

    int weight = strtol(str, NULL, 10);
    if (weight < 50 || weight > 500)
        return -1;

    return 0;
}

int verify_sex(char *str, size_t size) {
    int len = strlen(str) + 1;
    if (len != size)
        return -1;

    if (str[0] != 'M' && str[0] != 'F')
        return -1;

    return 0;
}

int verify_yes_no(char *str, size_t size) {
    int len = strlen(str) + 1;
    if (len != size)
        return -1;

    if (str[0] != 'Y' && str[0] != 'N')
        return -1;

    return 0;
}

int verify_name(char *str, size_t size)
{
    int i, len = strlen(str) + 1;
    if (len > size || len < 2)
        return -1;
    len--;

    for (i = 0; i < len; i++)
        if (!isalpha(str[i]) && str[i] != '\'')
            return -1;

    return 0;
}

int verify_street(char *str, size_t size)
{
    int i, len = strlen(str) + 1;
    if (len > size || len < 5)
        return -1;
    len--;

    for (i = 0; i < len; i++) {
        char c = str[i];
        if (!isalnum(c) && c != '\'' && c != ' ' && c != ',')
            return -1;
    }

    return 0;
}

int verify_city(char *str, size_t size)
{
    int i, len = strlen(str) + 1;
    if (len > size || len < 5)
        return -1;
    len--;

    for (i = 0; i < len; i++) {
        char c = str[i];
        if (!isalpha(c) && c != '\'' && c != ' ')
            return -1;
    }

    return 0;
}

int verify_zip_code(char *str, size_t size)
{
    int i, len = strlen(str) + 1;
    if (len != size)
        return -1;
    len--;

    if (str[0] == '0')
        return -1;

    for (i = 0; i < len; i++) {
        char c = str[i];
        if (!isdigit(c))
            return -1;
    }

    return 0;
}


int verify_gpa(char *str, size_t size)
{
    int i, len = strlen(str) + 1;
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
        if (!isdigit(c)) {
            return -1;
        }
    }

    return 0;
}

int verify_email(char *str, size_t size)
{
    int i, len = strlen(str) + 1, at_count = 0;
    if (len > size || len < 3)
        return -1;
    len--;

    for (i = 0; i < len; i++) {
        char c = str[i];
        if (!isalnum(c) && c != '@' && c != '-' && c != '.' && c != '_')
            return -1;
        if (c == '@' && ++at_count == 2)
            return -1;
    }

    if (at_count != 1)
        return -1;

    return 0;
}

int verify_phone(char *str, size_t size)
{
    int i, len = strlen(str) + 1, at_count = 0;
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
        if (!isdigit(c)) {
            return -1;
        }
    }

    return 0;
}

int verify_number(char *str, size_t size)
{
    int i, len = strlen(str) + 1;
    if (len > size)
        return -1;
    len--;

    for (i = 0; i < len; i++)
        if (!isdigit(str[i]))
            return -1;

    return 0;
}

int verify_text(char *str, size_t size)
{
    int i, len = strlen(str) + 1;
    if (len > size)
        return -1;
    len--;

    for (i = 0; i < len; i++)
        if (!isprint(str[i]))
            return -1;

    return 0;
}

