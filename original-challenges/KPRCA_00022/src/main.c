/*
 * Copyright (c) 2014 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */
#include <libcgc.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define RESP_SIZE 1024
#define FALSE 0
#define TRUE 1


typedef int (*verify_input_t) (char *str, size_t size);
typedef struct app_input
{
    char *text_field;
    char *input_specification;
    char is_required;
    size_t max_input_length;
    char *input;
    verify_input_t verify_input;
} app_input_t;


typedef enum {NOOP, INPUT, PREV, NEXT, UPDATE, HELP, EXIT } page_option;
typedef enum {CAND, CONT, ADDR, EDUC, EMPL, SCRN, FIN} page_alias;
typedef int (*application_page_t) ();

int candidate_info();
int contact();
int address();
int education();
int employment_history();
int final_screening();
int finished();

//GLOBAL VARIABLES
application_page_t job_application_page[] = { candidate_info, contact, address, education,
                                              employment_history, final_screening, finished };

char g_page_idx = CAND;
char g_last_page_completed = -1;
char g_user_resp[RESP_SIZE];

app_input_t applicant_id[] = {
    {"Last Name", "", TRUE, 32, NULL, verify_name},
    {"First Name", "", TRUE, 32, NULL, verify_name},
    {"Middle Name", " [MI or Middle Name]", FALSE, 32, NULL, verify_name},
    {"Suffix", " [Jr, Sr, II, etc]", FALSE, 8, NULL, verify_suffix},
    {"DOB Month", " [MM]", TRUE, 3, NULL, verify_month},
    {"DOB Day", " [DD]", TRUE, 3, NULL, verify_day},
    {"DOB Year", " [YYYY]", TRUE, 5, NULL, verify_year},
    {"Height-Feet", " [1-9]", TRUE, 2, NULL, verify_height_feet},
    {"Height-Inches", " [0-11]", TRUE, 3, NULL, verify_height_inches},
    {"Weight", "", TRUE, 4, NULL, verify_weight},
    {"Sex", "", TRUE, 2, NULL, verify_sex},
    {"Hair Color", "", TRUE, 32, NULL, verify_hair},
    {"Eye Color", "", TRUE, 16, NULL, verify_eye}
};

app_input_t check_other_name[] = {
    {"Ever Changed Name", "? [Y/N]", TRUE, 2, NULL, verify_yes_no}
};

app_input_t other_name_used[] = {
    {"Last Name", "", TRUE, 32, NULL, verify_name},
    {"First Name", "", TRUE, 32, NULL, verify_name},
    {"Middle Name", " [MI or Middle Name]", FALSE, 32, NULL, verify_name},
    {"Suffix", " [Jr, Sr, II, etc]", FALSE, 8, NULL, verify_suffix},
    {"Begin Month", " [MM]", TRUE, 3, NULL, verify_month},
    {"Begin Year", " [YYYY]", TRUE, 5, NULL, verify_year},
    {"End Month", " [MM]", TRUE, 3, NULL, verify_month},
    {"End Year", " [YYYY]", TRUE, 5, NULL, verify_year},
    {"Maiden Name", "? [Y/N]", TRUE, 2, NULL, verify_yes_no},
    {"Reason for name change", "", TRUE, 64, NULL, verify_text}
};


app_input_t contact_info[] = {
    {"Personal e-mail", "", TRUE, 64, NULL, verify_email},
    {"Work e-mail", "", FALSE, 64, NULL, verify_email},
    {"Home telephone number", " [XXX-XXX-XXXX]", TRUE, 13, NULL, verify_phone},
    {"Work telephone number", " [XXX-XXX-XXXX]", FALSE, 13, NULL, verify_phone}
};


app_input_t current_address[] = {
    {"Move-In Month", " [MM]", TRUE, 3, NULL, verify_month},
    {"Move-In Year", " [YYYY]", TRUE, 5, NULL, verify_year},
    {"Street", "", TRUE, 64, NULL, verify_street},
    {"City", "", TRUE, 32, NULL, verify_city},
    {"State", "", TRUE, 3, NULL, verify_state},
    {"Zip Code", "", TRUE, 6, NULL, verify_zip_code},
    {"Owned by you", "? [Y/N]", TRUE, 2, NULL, verify_yes_no}
};


app_input_t highest_education[] = {
    {"Highest Education", " [HS/COLLEGE/ADV]", TRUE, 10, NULL, verify_education},
    {"Start Month", " [MM]", TRUE, 3, NULL, verify_month},
    {"Start Year", " [YYYY]", TRUE, 5, NULL, verify_year},
    {"End Month", " [MM]", TRUE, 3, NULL, verify_month},
    {"End Year", " [YYYY]", TRUE, 5, NULL, verify_year},
    {"School Name", "", TRUE, 64, NULL, verify_text},
    {"Street", "", TRUE, 64, NULL, verify_street},
    {"City", "", TRUE, 32, NULL, verify_city},
    {"State", "", TRUE, 3, NULL, verify_state},
    {"Zip Code", "", TRUE, 6, NULL, verify_zip_code},
    {"GPA", " [X.XX]", TRUE, 5, NULL, verify_gpa},
    {"Major", " [NA for HS]", TRUE, 64, NULL, verify_text}
};


app_input_t last_employer[] = {
    {"Most Recent Employer", "", TRUE, 64, NULL, verify_text},
    {"Start Month", " [MM]", TRUE, 3, NULL, verify_month},
    {"Start Year", " [YYYY]", TRUE, 5, NULL, verify_year},
    {"End Month", " [MM]", FALSE, 3, NULL, verify_month},
    {"End Year", " [YYYY]", FALSE, 5, NULL, verify_year},
    {"Street", "", TRUE, 64, NULL, verify_street},
    {"City", "", TRUE, 32, NULL, verify_city},
    {"State", "", TRUE, 3, NULL, verify_state},
    {"Zip Code", "", TRUE, 6, NULL, verify_zip_code},
    {"Supervisor Last Name", "", TRUE, 32, NULL, verify_name},
    {"Supervisor First Name", "", TRUE, 32, NULL, verify_name},
    {"Supervisor Title", "", TRUE, 64, NULL, verify_text},
    {"Supervisor Telephone Number", " [XXX-XXX-XXXX]", TRUE, 13, NULL, verify_phone},
    {"Supervisor e-mail", "", FALSE, 64, NULL, verify_email},
};


app_input_t screening_questions[] = {
    {"Drug Test", "? [Y/N]", TRUE, 2, NULL, verify_yes_no},
    {"Background Investigation", "? [Y/N]", TRUE, 2, NULL, verify_yes_no}
};


static page_option get_response()
{
    size_t i;
    size_t rx;
    int fd = STDIN;
    size_t size = RESP_SIZE;
    char *buf = g_user_resp;
    char *response = g_user_resp;

    for (i = 0; i < size; i++) {
        if (receive(fd, buf, 1, &rx) != 0 || rx == 0)
            break;
        if (*buf == '\n')
            break;
        buf++;
    }

    if (i == size && *buf != '\n')
        return -1;
    else if (*buf != '\n')
        return -2;
    else
        *buf = '\0';

    if (i > 2 && response[0] == '*' && response[1] == '*') {
        //parse command
        if( memcmp(&response[2], "prev", strlen("prev")) == 0 )
            return PREV;
        if( memcmp(&response[2], "next", strlen("next")) == 0 )
            return NEXT;
        if( memcmp(&response[2], "update ", strlen("update ")) == 0 )
            return UPDATE;
        if( memcmp(&response[2], "help", strlen("help")) == 0 )
            return HELP;
        if( memcmp(&response[2], "exit", strlen("exit")) == 0 )
            return EXIT;
    }

    return INPUT;
}

void print_menu()
{
    printf("All commands begin with '**' and may be entered at any time\n");
    printf("**prev <Return to the previous page>\n");
    printf("**next <Move to the next page>\n");
    printf("**update [id] <Update field, ex: \"Update First Name\">\n");
    printf("**help <Print this dialogue>\n");
    printf("**exit <Exit application>\n");
}

int main(void)
{
    page_option pg_opt = NOOP;
    printf("\n\n");
    printf("Thanks for your interest in the Sea Eye Association.\n");
    printf("In order to be considered for the job complete the preliminary online background check\n");
    printf("Due to the secure nature of the position you are applying for you may be asked to\n");
    printf("submit additional paperwork after your preliminary background check has been approved.\n");
    printf("Thank you for your cooperation\n");
    g_page_idx = CAND;

    while(pg_opt != EXIT) {
        pg_opt = job_application_page[g_page_idx]();

        switch(pg_opt) {
        case PREV:
            g_page_idx = g_page_idx == CAND ? g_page_idx : g_page_idx - 1;
            break;
        case NEXT:
            g_page_idx = g_page_idx == FIN ? g_page_idx : g_page_idx + 1;
            break;
        case HELP:
            print_menu();
            break;
        case UPDATE:
        case INPUT:
            //This should never happen
        case EXIT:
        default:
            //not sure if there is something better
            break;
        }
    }

    printf("Thank you!\n");
    return 0;
}

int fill_out_form(app_input_t form_questions[], int num_fields)
{
    int i;
    page_option pg_opt;
    for (i = 0; i < num_fields; i++) {
        app_input_t *form_question = &form_questions[i];
        while (form_question->input == NULL) {
            printf("%s%s: ", form_question->text_field, form_question->input_specification);
            pg_opt = get_response();
            if (pg_opt < 0) {
                continue;
            } else if (pg_opt != INPUT) {
                goto page_option_selected;
            } else if (!form_question->is_required && memcmp(g_user_resp, "", 1) == 0) {
                form_question->input = calloc(1, form_question->max_input_length);
                break;
            } else if (form_question->verify_input(g_user_resp, form_question->max_input_length) != 0) {
                continue;
            }

            form_question->input = calloc(1, form_question->max_input_length);
            strcpy(form_question->input, g_user_resp);
        }
    }

    return NOOP;

page_option_selected:
    return pg_opt;
}

int update_field(char *field, app_input_t form_questions[], int num_fields)
{
    if (field == NULL || strlen(field) < 1) {
        printf("Bad field\n");
        return -1;
    }

    int i;
    page_option pg_opt;
    for (i = 0; i < num_fields; i++) {
        app_input_t *form_question = &form_questions[i];
        if (strlen(field) != strlen(form_question->text_field) ||
            memcmp(field, form_question->text_field, strlen(form_question->text_field)) != 0)
            continue;

        printf("%s%s: ", form_question->text_field, form_question->input_specification);
        pg_opt = get_response();
        if (pg_opt != INPUT) {
            printf("Bad command\n");
            return -2;
        } else if (!form_question->is_required && memcmp(g_user_resp, "", 1) == 0) {
            memset(form_question->input, 0, form_question->max_input_length);
            return 0;
        } else if (form_question->verify_input(g_user_resp, form_question->max_input_length) != 0) {
            printf("Bad input.\n");
            return -4;
        }

        memset(form_question->input, 0, form_question->max_input_length);
        strcpy(form_question->input, g_user_resp);
        return 0;
    }

    printf("Could not find specified field\n");
    return -1;
}

void print_page(char *banner, app_input_t form_questions[], int num_fields)
{
    int i;
    if (banner != NULL)
        printf("%s", banner);

    for (i = 0; i < num_fields; i++) {
        app_input_t *form_question = &form_questions[i];
        printf("%s=%s\n", form_question->text_field, form_question->input);
    }
}


int form(char *banner, app_input_t form_questions[], size_t num_fields)
{
    char *update_tok;
    page_option pg_opt;

    if (g_page_idx > g_last_page_completed + 1) {
        printf("You must complete the previous page before proceeding to this page\n");
        g_page_idx = g_last_page_completed + 1;
        return -1;
    }

    int i;
    int unfinished = FALSE;
    for (i=0; i < num_fields; i++) {
        if (form_questions[i].input == NULL) {
            unfinished = TRUE;
            g_last_page_completed = g_page_idx - 1;
            break;
        }
    }

    if ( g_page_idx == g_last_page_completed + 1 || unfinished) {
        pg_opt = fill_out_form(form_questions, num_fields);
        if (pg_opt == NOOP) {
            g_last_page_completed++;
        } else if (pg_opt == UPDATE) {
            printf("Cannot update field until all fields are inputted\n");
            return pg_opt;
        } else {
            return pg_opt;
        }
    }

    print_page(banner, form_questions, num_fields);
    printf("\nType **next to continue\n");

    pg_opt = get_response();
    if (pg_opt == UPDATE) {
        update_tok = g_user_resp;
        strsep(&update_tok, " ");
        if (update_field(update_tok, form_questions, num_fields) != 0)
            printf("Update Unsuccessful\n");
    }

    return pg_opt;
}

int candidate_info()
{
    printf("\nCandidate Info Form\n");
    return form("\n*********Candidate Info:*********\n", applicant_id, sizeof(applicant_id)/sizeof(app_input_t));
}

int contact()
{
    printf("\nContact Info Form\n");
    return form("\n*********Contact Info:*********\n",  contact_info, sizeof(contact_info)/sizeof(app_input_t));
}

int address()
{
    printf("\nAddress Form\n");
    return form("\n*********Address:*********\n", current_address, sizeof(current_address)/sizeof(app_input_t));
}

int education()
{
    printf("\nEducation Form\n");
    return form("\n*********Highest Education:*********\n", highest_education, sizeof(highest_education)/sizeof(app_input_t));
}

int employment_history()
{
    printf("\nEmployment Form\n");
    return form("\n*********Most Recent Employer:*********\n", last_employer, sizeof(last_employer)/sizeof(app_input_t));
}

int final_screening()
{

    printf("\nFinal Questions\n");
    return form("\n*********Final Screening:*********\n", screening_questions, sizeof(screening_questions)/sizeof(app_input_t));
}

int finished() {
    printf("\n\nYou have completed your application with the Sea Eye Association.\n");
    printf("You may review the form. Navigate through the application with **prev and **next.\n");
    printf("Once your are satisfied type **exit to exit and submit the form\n");
    printf("If you wish to discard your application, please use Control-C\n");

    if (g_page_idx > g_last_page_completed + 1) {
        printf("You must complete the previous page before proceeding to this page\n");
        g_page_idx = g_last_page_completed + 1;
        return -1;
    }

    return get_response();
}

