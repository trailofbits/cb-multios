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

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "form.h"

static const char *valid_education_levels[] = {
  "HS", "COLLEGE", "ADV", NULL
};

static const char *valid_eye_colors[] = {
  "Black", "Blue", "Brown", "Gray", "Green", "Hazel", "Maroon", "Multicolored",
  "Pink", "Unknown", NULL
};

static const char *valid_hair_colors[] = {
  "Bald", "Black", "Blonde or Strawbery", "Brown", "Gray or Partially Gray",
  "Red or Auburn", "Sandy", "White", "Blue", "Green", "Orange", "Pink",
  "Purple", "Unspecified or Unknown", NULL
};

static const char *valid_states[] = {
  "AL", "AK", "AZ", "AR", "CA", "CO", "CT", "DE", "DC", "FL", "GA", "HI", "ID",
  "IL", "IN", "IA", "KS", "KY", "LA", "ME", "MD", "MA", "MI", "MN", "MS", "MO",
  "MT", "NE", "NV", "NH", "NJ", "NM", "NY", "NC", "ND", "OH", "OK", "OR", "PA",
  "RI", "SC", "SD", "TN", "TX", "UT", "VT", "VA", "WA", "WV", "WI", "WY", NULL
};

static const char *valid_suffixes[] = {
  "Jr", "Sr", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX", "X", "Other", NULL
};

int contains(const char *arr[], char *e)
{
  const char **cur = arr;
  while (*cur != NULL) {
    if (strncmp((char *)*cur, e, strlen(*cur)) == 0) {
      return 1;
    } else {
      cur++;
    }
  }

  return 0;
}

int validate_edu(char *input)
{
  return contains(valid_education_levels, input);
}

int validate_eye_color(char *input)
{
  return contains(valid_eye_colors, input);
}

int validate_hair_color(char *input)
{
  return contains(valid_hair_colors, input);
}

int validate_state(char *input)
{
  return contains(valid_states, input);
}

int validate_suffix(char *input)
{
  return contains(valid_suffixes, input);
}


int within(int min, int max, int x)
{
  return x >= min && x <= max;
}

int all_digits(char *input)
{
  for (size_t i = 0; i < strlen(input); i++)
    if (!isdigit(input[i])) {
      return 0;
    }

  return 1;
}

int validate_day(char *input)
{
  if (!all_digits(input)) return 0;
  return within(1, 31, strtol(input, NULL, 10));
}

int validate_month(char *input)
{
  if (!all_digits(input)) return 0;
  return within(1, 12, strtol(input, NULL, 10));
}

int validate_year(char *input)
{
  if (!all_digits(input)) return 0;
  return within(1900, 2014, strtol(input, NULL, 10));
}

int validate_height_inches(char *input)
{
  if (!all_digits(input)) return 0;
  return within(0, 11, strtol(input, NULL, 10));
}

int validate_height_feet(char *input)
{
  if (!all_digits(input)) return 0;
  return within(1, 9, strtol(input, NULL, 10));
}

int validate_weight(char *input)
{
  if (!all_digits(input)) return 0;
  return within(50, 500, strtol(input, NULL, 10));
}

int validate_name(char *input)
{
  for (size_t i = 0; i < strlen(input); i++)
    if (!isprint(input[i]) && input[i] != '\'')
      return 0;

  return 1;
}

int validate_email(char *input)
{
  int has_at = 0;
  char c;

  if (strlen(input) < 3 || strlen(input) > 64)
    return 0;

  for (size_t i = 0; i < strlen(input); i++) {
    c = input[i];

    if (c == '@') {
      if (has_at) {
        return 0;
      } else {
        has_at = 1;
        continue;
      }
    }

    if (!(isalnum(c) || c == '.' || c == '-' || c == '_'))
      return 0;
  }

  return has_at;
}

int validate_street(char *input)
{
  if (strlen(input) > 32 || strlen(input) < 3)
    return 0;

  for (size_t i = 0; i < strlen(input); i++)
    if (!(isalnum(input[i]) || isspace(input[i]) || ispunct(input[i])))
      return 0;

  return 1;
}

int validate_city(char *input)
{
  if (strlen(input) > 32 || strlen(input) < 4)
    return 0;

  for (size_t i = 0; i < strlen(input); i++)
    if (!(isalnum(input[i]) || isspace(input[i]) || ispunct(input[i])))
      return 0;

  return 1;
}

int validate_zip(char *input)
{
  if (strlen(input) != 5)
    return 0;

  for (int i = 0; i < 5; i++)
    if (!isdigit(input[i]))
      return 0;

  return 1;
}

int validate_phone(char *input)
{
  if (strlen(input) != 12)
    return 0;

  for (int i = 0; i < 12; i++)
    if ((i == 3 || i == 7)) {
      if (input[i] != '-')
        return 0;
    } else {
      if (!isdigit(input[i]))
        return 0;
    }

  return 1;
}

int validate_sex(char *input)
{
  if (strlen(input) != 1)
    return 0;

  if (input[0] != 'M' && input[0] != 'F')
    return 0;

  return 1;
}

int validate_yes_no(char *input)
{
  if (strlen(input) != 1)
    return 0;

  if (input[0] != 'Y' && input[0] != 'N')
    return 0;

  return 1;
}

int validate_gpa(char *input)
{
  if (strlen(input) != 4)
    return 0;

  for (int i = 0; i < 4; i++) {
    if (i == 1) {
      if (input[i] != '.')
        return 0;
    } else if (!isdigit(input[i]))
      return 0;
  }

  return 1;
}

// Questions
// Personal
DEC_Q(last_name, "Last Name", NULL, 0, validate_name);
DEC_Q(first_name, "First Name", NULL, 0, validate_name);
DEC_Q(middle_name, "Middle Name", " [MI or Middle Name]", 1, validate_name);
DEC_Q(suffix, "Suffix", " [Jr, Sr, II, etc]", 1, validate_suffix);
DEC_Q(dob_month, "DOB Month", " [MM]", 0, validate_month);
DEC_Q(dob_day, "DOB Day", " [DD]", 0, validate_day);
DEC_Q(dob_year, "DOB Year", " [YYYY]", 0, validate_year);
DEC_Q(height_feet, "Height-Feet", " [1-9]", 0, validate_height_feet);
DEC_Q(height_inches, "Height-Inches", " [0-11]", 0, validate_height_inches);
DEC_Q(weight, "Weight", NULL, 0, validate_weight);
DEC_Q(sex, "Sex", NULL, 0, validate_sex);
DEC_Q(hair_color, "Hair Color", NULL, 0, validate_hair_color);
DEC_Q(eye_color, "Eye Color", NULL, 0, validate_eye_color);

// Contact
DEC_Q(pemail, "Personal e-mail", NULL, 0, validate_email);
DEC_Q(wemail, "Work e-mail", NULL, 1, validate_email);
DEC_Q(hphone, "Home telephone number", " [XXX-XXX-XXXX]", 0, validate_phone);
DEC_Q(wphone, "Work telephone number", " [XXX-XXX-XXXX]", 1, validate_phone);

// Address
DEC_Q(mim, "Move-In Month", " [MM]", 0, validate_month);
DEC_Q(miy, "Move-In Year", " [YYYY]", 0, validate_year);
DEC_Q(street, "Street", NULL, 0, validate_street);
DEC_Q(city, "City", NULL, 0, validate_city);
DEC_Q(state, "State", NULL, 0, validate_state);
DEC_Q(zip, "Zip Code", NULL, 0, validate_zip);
DEC_Q(owned, "Owned by you", "? [Y/N]", 0, validate_yes_no);

// Education
DEC_Q(highest_edu, "Highest Education", " [HS/COLLEGE/ADV]", 0, validate_edu);
DEC_Q(esm, "Start Month", " [MM]", 0, validate_month);
DEC_Q(esy, "Start Year", " [YYYY]", 0, validate_year);
DEC_Q(eem, "End Month", " [MM]", 0, validate_month);
DEC_Q(eey, "End Year", " [YYYY]", 0, validate_year);
DEC_Q(school_name, "School Name", NULL, 0, validate_name);
DEC_Q(estreet, "Street", NULL, 0, validate_street);
DEC_Q(ecity, "City", NULL, 0, validate_city);
DEC_Q(estate, "State", NULL, 0, validate_state);
DEC_Q(ezip, "Zip Code", NULL, 0, validate_zip);
DEC_Q(gpa, "GPA", " [X.XX]", 0, validate_gpa);
DEC_Q(major, "Major", " [NA for HS]", 0, validate_name);

// Last Employer
DEC_Q(employeer, "Most Recent Employer", NULL, 0, validate_name);
DEC_Q(wsm, "Start Month", " [MM]", 0, validate_month);
DEC_Q(wsy, "Start Year", " [YYYY]", 0, validate_year);
DEC_Q(wem, "End Month", " [MM]", 1, validate_month);
DEC_Q(wey, "End Year", " [YYYY]", 1, validate_year);
DEC_Q(wstreet, "Street", NULL, 0, validate_street);
DEC_Q(wcity, "City", NULL, 0, validate_city);
DEC_Q(wstate, "State", NULL, 0, validate_state);
DEC_Q(wzip, "Zip Code", NULL, 0, validate_zip);
DEC_Q(sup_last_name, "Supervisor Last Name", NULL, 0, validate_name);
DEC_Q(sup_first_name, "Supervisor First Name", NULL, 0, validate_name);
DEC_Q(sup_title, "Supervisor Title", NULL, 0, validate_name);
DEC_Q(sphone, "Supervisor Telephone Number", " [XXX-XXX-XXXX]", 0, validate_phone);
DEC_Q(semail, "Supervisor e-mail", NULL, 1, validate_email);

// Final
DEC_Q(drugz, "Drug Test", "? [Y/N]", 0, validate_yes_no);
DEC_Q(background, "Background Investigation", "? [Y/N]", 0, validate_yes_no);

// Pages
DEC_P(candidate, "Candidate Info");
DEC_P(contact, "Contact Info");
DEC_P(address, "Address");
DEC_P(education, "Education");
DEC_P(employment, "Employment");
DEC_P(final, "Final Questions");
DEC_P(fin, NULL);

void init_af86(void)
{
  // Pages
  LINK(candidate, NULL, &contact);
  LINK(contact, &candidate, &address);
  LINK(address, &contact, &education);
  LINK(education, &address, &employment);
  LINK(employment, &education, &final);
  LINK(final, &employment, &fin);
  LINK(fin, &final, NULL);

  candidate.questions = &last_name;
  contact.questions = &pemail;
  address.questions = &mim;
  education.questions = &highest_edu;
  employment.questions = &employeer;
  final.questions = &drugz;

  // Questions
  LINK(last_name, NULL, &first_name);
  LINK(first_name, &last_name, &middle_name);
  LINK(middle_name, &first_name, &suffix);
  LINK(suffix, &middle_name, &dob_month);
  LINK(dob_month, &suffix, &dob_day);
  LINK(dob_day, &dob_month, &dob_year);
  LINK(dob_year, &dob_day, &height_feet);
  LINK(height_feet, &dob_year, &height_inches);
  LINK(height_inches, &height_feet, &weight);
  LINK(weight, &height_inches, &sex);
  LINK(sex, &weight, &hair_color);
  LINK(hair_color, &sex, &eye_color);
  LINK(eye_color, &hair_color, NULL);

  LINK(pemail, NULL, &wemail);
  LINK(wemail, &pemail, &hphone);
  LINK(hphone, &wemail, &wphone);
  LINK(wphone, &hphone, NULL);

  LINK(mim, NULL, &miy);
  LINK(miy, &mim, &street);
  LINK(street, &miy, &city);
  LINK(city, &street, &state);
  LINK(state, &city, &zip);
  LINK(zip, &state, &owned);
  LINK(owned, &zip, NULL);

  LINK(highest_edu, NULL, &esm);
  LINK(esm, &highest_edu, &esy);
  LINK(esy, &esm, &eem);
  LINK(eem, &esy, &eey);
  LINK(eey, &eem, &school_name);
  LINK(school_name, &eey, &estreet);
  LINK(estreet, &school_name, &ecity);
  LINK(ecity, &estreet, &estate);
  LINK(estate, &ecity, &ezip);
  LINK(ezip, &estate, &gpa);
  LINK(gpa, &ezip, &major);
  LINK(major, &gpa, NULL);

  LINK(employeer, NULL, &wsm);
  LINK(wsm, &employeer, &wsy);
  LINK(wsy, &wsm, &wem);
  LINK(wem, &wsy, &wey);
  LINK(wey, &wem, &wstreet);
  LINK(wstreet, &wey, &wcity);
  LINK(wcity, &wstreet, &wstate);
  LINK(wstate, &wcity, &wzip);
  LINK(wzip, &wstate, &sup_last_name);
  LINK(sup_last_name, &wzip, &sup_first_name);
  LINK(sup_first_name, &sup_last_name, &sup_title);
  LINK(sup_title, &sup_first_name, &sphone);
  LINK(sphone, &sup_title, &semail);
  LINK(semail, &sphone, NULL);

  LINK(drugz, NULL, &background);
  LINK(background, &drugz, NULL);
}

form_t af86 = {
  .ending = "\n\n"
    "You have completed your application with the Sea Eye Association.\nYou "
    "may review the form. Navigate through the application with **prev and "
    "**next.\nOnce your are satisfied type **exit to exit and submit the "
    "form\nIf you wish to discard your application, please use Control-C\n",

  .greeting = "\n\n"
    "Thanks for your interest in the Sea Eye Association.\n"
    "In order to be considered for the job complete the preliminary online "
    "background check\nDue to the secure nature of the position you are "
    "applying for you may be asked to\nsubmit additional paperwork after "
    "your preliminary background check has been approved.\nThank you for "
    "your cooperation\n",

  .help = "All commands begin with '**' and may be entered at any time\n"
    "**prev <Return to the previous page>\n"
    "**next <Move to the next page>\n"
    "**update [id] <Update field, ex: \"Update First Name\">\n"
    "**help <Print this dialogue>\n"
    "**exit <Exit application>\n",

  .init = init_af86,

  .handlers = {
    handle_next,
    handle_prev,
    handle_update,
    handle_help,
    handle_exit
  },

  .pages = &candidate,
  .cur_page = &candidate,
  .cur_question = &last_name
};
