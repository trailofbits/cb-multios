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
#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"

#include "cgc_utils.h"

#define RESP_SIZE 1024
#define FALSE 0
#define TRUE 1


typedef int (*verify_input_t) (char *str, cgc_size_t size);
typedef struct app_input
{
    char *text_field;
    char *input_specification;
    char is_required;
    cgc_size_t max_input_length;
    char *input;
    verify_input_t verify_input;
} app_input_t;


typedef enum {NOOP, INPUT, PREV, NEXT, UPDATE, HELP, EXIT } page_option;
typedef enum {CAND, CONT, ADDR, EDUC, EMPL, SCRN, FIN} page_alias;
typedef int (*application_page_t) ();

int cgc_candidate_info();
int cgc_contact();
int cgc_address();
int cgc_education();
int cgc_employment_history();
int cgc_final_screening();
int cgc_finished();

//GLOBAL VARIABLES
application_page_t job_application_page[] = { cgc_candidate_info, cgc_contact, cgc_address, cgc_education,
                                              cgc_employment_history, cgc_final_screening, cgc_finished };

char cgc_g_page_idx = CAND;
char g_last_page_completed = -1;
char g_user_resp[RESP_SIZE];

app_input_t applicant_id[] = {
    {"Last Name", "", TRUE, 32, NULL, cgc_verify_name},
    {"First Name", "", TRUE, 32, NULL, cgc_verify_name},
    {"Middle Name", " [MI or Middle Name]", FALSE, 32, NULL, cgc_verify_name},
    {"Suffix", " [Jr, Sr, II, etc]", FALSE, 8, NULL, cgc_verify_suffix},
    {"DOB Month", " [MM]", TRUE, 3, NULL, cgc_verify_month},
    {"DOB Day", " [DD]", TRUE, 3, NULL, cgc_verify_day},
    {"DOB Year", " [YYYY]", TRUE, 5, NULL, cgc_verify_year},
    {"Height-Feet", " [1-9]", TRUE, 2, NULL, cgc_verify_height_feet},
    {"Height-Inches", " [0-11]", TRUE, 3, NULL, cgc_verify_height_inches},
    {"Weight", "", TRUE, 4, NULL, cgc_verify_weight},
    {"Sex", "", TRUE, 2, NULL, cgc_verify_sex},
    {"Hair Color", "", TRUE, 32, NULL, cgc_verify_hair},
    {"Eye Color", "", TRUE, 16, NULL, cgc_verify_eye}
};

app_input_t check_other_name[] = {
    {"Ever Changed Name", "? [Y/N]", TRUE, 2, NULL, cgc_verify_yes_no}
};

app_input_t other_name_used[] = {
    {"Last Name", "", TRUE, 32, NULL, cgc_verify_name},
    {"First Name", "", TRUE, 32, NULL, cgc_verify_name},
    {"Middle Name", " [MI or Middle Name]", FALSE, 32, NULL, cgc_verify_name},
    {"Suffix", " [Jr, Sr, II, etc]", FALSE, 8, NULL, cgc_verify_suffix},
    {"Begin Month", " [MM]", TRUE, 3, NULL, cgc_verify_month},
    {"Begin Year", " [YYYY]", TRUE, 5, NULL, cgc_verify_year},
    {"End Month", " [MM]", TRUE, 3, NULL, cgc_verify_month},
    {"End Year", " [YYYY]", TRUE, 5, NULL, cgc_verify_year},
    {"Maiden Name", "? [Y/N]", TRUE, 2, NULL, cgc_verify_yes_no},
    {"Reason for name change", "", TRUE, 64, NULL, cgc_verify_text}
};


app_input_t contact_info[] = {
    {"Personal e-mail", "", TRUE, 64, NULL, cgc_verify_email},
    {"Work e-mail", "", FALSE, 64, NULL, cgc_verify_email},
    {"Home telephone number", " [XXX-XXX-XXXX]", TRUE, 13, NULL, cgc_verify_phone},
    {"Work telephone number", " [XXX-XXX-XXXX]", FALSE, 13, NULL, cgc_verify_phone}
};


app_input_t current_address[] = {
    {"Move-In Month", " [MM]", TRUE, 3, NULL, cgc_verify_month},
    {"Move-In Year", " [YYYY]", TRUE, 5, NULL, cgc_verify_year},
    {"Street", "", TRUE, 64, NULL, cgc_verify_street},
    {"City", "", TRUE, 32, NULL, cgc_verify_city},
    {"State", "", TRUE, 3, NULL, cgc_verify_state},
    {"Zip Code", "", TRUE, 6, NULL, cgc_verify_zip_code},
    {"Owned by you", "? [Y/N]", TRUE, 2, NULL, cgc_verify_yes_no}
};


app_input_t highest_education[] = {
    {"Highest Education", " [HS/COLLEGE/ADV]", TRUE, 10, NULL, cgc_verify_education},
    {"Start Month", " [MM]", TRUE, 3, NULL, cgc_verify_month},
    {"Start Year", " [YYYY]", TRUE, 5, NULL, cgc_verify_year},
    {"End Month", " [MM]", TRUE, 3, NULL, cgc_verify_month},
    {"End Year", " [YYYY]", TRUE, 5, NULL, cgc_verify_year},
    {"School Name", "", TRUE, 64, NULL, cgc_verify_text},
    {"Street", "", TRUE, 64, NULL, cgc_verify_street},
    {"City", "", TRUE, 32, NULL, cgc_verify_city},
    {"State", "", TRUE, 3, NULL, cgc_verify_state},
    {"Zip Code", "", TRUE, 6, NULL, cgc_verify_zip_code},
    {"GPA", " [X.XX]", TRUE, 5, NULL, cgc_verify_gpa},
    {"Major", " [NA for HS]", TRUE, 64, NULL, cgc_verify_text}
};


app_input_t last_employer[] = {
    {"Most Recent Employer", "", TRUE, 64, NULL, cgc_verify_text},
    {"Start Month", " [MM]", TRUE, 3, NULL, cgc_verify_month},
    {"Start Year", " [YYYY]", TRUE, 5, NULL, cgc_verify_year},
    {"End Month", " [MM]", FALSE, 3, NULL, cgc_verify_month},
    {"End Year", " [YYYY]", FALSE, 5, NULL, cgc_verify_year},
    {"Street", "", TRUE, 64, NULL, cgc_verify_street},
    {"City", "", TRUE, 32, NULL, cgc_verify_city},
    {"State", "", TRUE, 3, NULL, cgc_verify_state},
    {"Zip Code", "", TRUE, 6, NULL, cgc_verify_zip_code},
    {"Supervisor Last Name", "", TRUE, 32, NULL, cgc_verify_name},
    {"Supervisor First Name", "", TRUE, 32, NULL, cgc_verify_name},
    {"Supervisor Title", "", TRUE, 64, NULL, cgc_verify_text},
    {"Supervisor Telephone Number", " [XXX-XXX-XXXX]", TRUE, 13, NULL, cgc_verify_phone},
    {"Supervisor e-mail", "", FALSE, 64, NULL, cgc_verify_email},
};


app_input_t screening_questions[] = {
    {"Drug Test", "? [Y/N]", TRUE, 2, NULL, cgc_verify_yes_no},
    {"Background Investigation", "? [Y/N]", TRUE, 2, NULL, cgc_verify_yes_no}
};


static page_option cgc_get_response()
{
    cgc_size_t i;
    cgc_size_t rx;
    int fd = STDIN;
    cgc_size_t size = RESP_SIZE;
    char *buf = g_user_resp;
    char *response = g_user_resp;

    for (i = 0; i < size; i++) {
        if (cgc_receive(fd, buf, 1, &rx) != 0 || rx == 0)
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
        if( cgc_memcmp(&response[2], "prev", cgc_strlen("prev")) == 0 )
            return PREV;
        if( cgc_memcmp(&response[2], "next", cgc_strlen("next")) == 0 )
            return NEXT;
        if( cgc_memcmp(&response[2], "update ", cgc_strlen("update ")) == 0 )
            return UPDATE;
        if( cgc_memcmp(&response[2], "help", cgc_strlen("help")) == 0 )
            return HELP;
        if( cgc_memcmp(&response[2], "cgc_exit", cgc_strlen("exit")) == 0 )
            return EXIT;
    }

    return INPUT;
}

void cgc_print_menu()
{
    cgc_printf("All commands begin with '**' and may be entered at any time\n");
    cgc_printf("**prev <Return to the previous page>\n");
    cgc_printf("**next <Move to the next page>\n");
    cgc_printf("**update [id] <Update field, ex: \"Update First Name\">\n");
    cgc_printf("**help <Print this dialogue>\n");
    cgc_printf("**exit <Exit application>\n");
}

int main(int cgc_argc, char *cgc_argv[])
{
    page_option pg_opt = NOOP;
    cgc_printf("\n\n");
    cgc_printf("Thanks for your interest in the Sea Eye Association.\n");
    cgc_printf("In order to be considered for the job complete the preliminary online background check\n");
    cgc_printf("Due to the secure nature of the position you are applying for you may be asked to\n");
    cgc_printf("submit additional paperwork after your preliminary background check has been approved.\n");
    cgc_printf("Thank you for your cooperation\n");
    cgc_g_page_idx = CAND;

    while(pg_opt != EXIT) {
        pg_opt = job_application_page[cgc_g_page_idx]();

        switch(pg_opt) {
        case PREV:
            cgc_g_page_idx = cgc_g_page_idx == CAND ? cgc_g_page_idx : cgc_g_page_idx - 1;
            break;
        case NEXT:
            cgc_g_page_idx = cgc_g_page_idx == FIN ? cgc_g_page_idx : cgc_g_page_idx + 1;
            break;
        case HELP:
            cgc_print_menu();
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

    cgc_printf("Thank you!\n");
    return 0;
}

int cgc_fill_out_form(app_input_t form_questions[], int num_fields)
{
    int i;
    page_option pg_opt;
    for (i = 0; i < num_fields; i++) {
        app_input_t *form_question = &form_questions[i];
        while (form_question->input == NULL) {
            cgc_printf("%s%s: ", form_question->text_field, form_question->input_specification);
            pg_opt = cgc_get_response();
            if (pg_opt < 0) {
                continue;
            } else if (pg_opt != INPUT) {
                goto page_option_selected;
            } else if (!form_question->is_required && cgc_memcmp(g_user_resp, "", 1) == 0) {
                form_question->input = cgc_calloc(1, form_question->max_input_length);
                break;
            } else if (form_question->verify_input(g_user_resp, form_question->max_input_length) != 0) {
                continue;
            }

            form_question->input = cgc_calloc(1, form_question->max_input_length);
            cgc_strcpy(form_question->input, g_user_resp);
        }
    }

    return NOOP;

page_option_selected:
    return pg_opt;
}

int cgc_update_field(char *field, app_input_t form_questions[], int num_fields)
{
    if (field == NULL || cgc_strlen(field) < 1) {
        cgc_printf("Bad field\n");
        return -1;
    }

    int i;
    page_option pg_opt;
    for (i = 0; i < num_fields; i++) {
        app_input_t *form_question = &form_questions[i];
        if (cgc_strlen(field) != cgc_strlen(form_question->text_field) ||
            cgc_memcmp(field, form_question->text_field, cgc_strlen(form_question->text_field)) != 0)
            continue;

        cgc_printf("%s%s: ", form_question->text_field, form_question->input_specification);
        pg_opt = cgc_get_response();
        if (pg_opt != INPUT) {
            cgc_printf("Bad command\n");
            return -2;
        } else if (!form_question->is_required && cgc_memcmp(g_user_resp, "", 1) == 0) {
            cgc_memset(form_question->input, 0, form_question->max_input_length);
            return 0;
        } else if (form_question->verify_input(g_user_resp, form_question->max_input_length) != 0) {
            cgc_printf("Bad input.\n");
            return -4;
        }

        cgc_memset(form_question->input, 0, form_question->max_input_length);
        cgc_strcpy(form_question->input, g_user_resp);
        return 0;
    }

    cgc_printf("Could not find specified field\n");
    return -1;
}

void cgc_print_page(char *banner, app_input_t form_questions[], int num_fields)
{
    int i;
    if (banner != NULL)
        cgc_printf("%s", banner);

    for (i = 0; i < num_fields; i++) {
        app_input_t *form_question = &form_questions[i];
        cgc_printf("%s=%s\n", form_question->text_field, form_question->input);
    }
}


int cgc_form(char *banner, app_input_t form_questions[], cgc_size_t num_fields)
{
    char *update_tok;
    page_option pg_opt;

    if (cgc_g_page_idx > g_last_page_completed + 1) {
        cgc_printf("You must complete the previous page before proceeding to this page\n");
        cgc_g_page_idx = g_last_page_completed + 1;
        return -1;
    }

    int i;
    int unfinished = FALSE;
    for (i=0; i < num_fields; i++) {
        if (form_questions[i].input == NULL) {
            unfinished = TRUE;
            g_last_page_completed = cgc_g_page_idx - 1;
            break;
        }
    }

    if ( cgc_g_page_idx == g_last_page_completed + 1 || unfinished) {
        pg_opt = cgc_fill_out_form(form_questions, num_fields);
        if (pg_opt == NOOP) {
            g_last_page_completed++;
        } else if (pg_opt == UPDATE) {
            cgc_printf("Cannot update field until all fields are inputted\n");
            return pg_opt;
        } else {
            return pg_opt;
        }
    }

    cgc_print_page(banner, form_questions, num_fields);
    cgc_printf("\nType **next to continue\n");

    pg_opt = cgc_get_response();
    if (pg_opt == UPDATE) {
        update_tok = g_user_resp;
        cgc_strsep(&update_tok, " ");
        if (cgc_update_field(update_tok, form_questions, num_fields) != 0)
            cgc_printf("Update Unsuccessful\n");
    }

    return pg_opt;
}

int cgc_candidate_info()
{
    cgc_printf("\nCandidate Info Form\n");
    return cgc_form("\n*********Candidate Info:*********\n", applicant_id, sizeof(applicant_id)/sizeof(app_input_t));
}

int cgc_contact()
{
    cgc_printf("\nContact Info Form\n");
    return cgc_form("\n*********Contact Info:*********\n",  contact_info, sizeof(contact_info)/sizeof(app_input_t));
}

int cgc_address()
{
    cgc_printf("\nAddress Form\n");
    return cgc_form("\n*********Address:*********\n", current_address, sizeof(current_address)/sizeof(app_input_t));
}

int cgc_education()
{
    cgc_printf("\nEducation Form\n");
    return cgc_form("\n*********Highest Education:*********\n", highest_education, sizeof(highest_education)/sizeof(app_input_t));
}

int cgc_employment_history()
{
    cgc_printf("\nEmployment Form\n");
    return cgc_form("\n*********Most Recent Employer:*********\n", last_employer, sizeof(last_employer)/sizeof(app_input_t));
}

int cgc_final_screening()
{

    cgc_printf("\nFinal Questions\n");
    return cgc_form("\n*********Final Screening:*********\n", screening_questions, sizeof(screening_questions)/sizeof(app_input_t));
}

int cgc_finished() {
    cgc_printf("\n\nYou have completed your application with the Sea Eye Association.\n");
    cgc_printf("You may review the form. Navigate through the application with **prev and **next.\n");
    cgc_printf("Once your are satisfied type **exit to exit and submit the form\n");
    cgc_printf("If you wish to discard your application, please use Control-C\n");

    if (cgc_g_page_idx > g_last_page_completed + 1) {
        cgc_printf("You must complete the previous page before proceeding to this page\n");
        cgc_g_page_idx = g_last_page_completed + 1;
        return -1;
    }

    return cgc_get_response();
}

