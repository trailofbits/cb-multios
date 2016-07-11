/*

Author: Debbie Nuttall <debbie@cromulence.co>

Copyright (c) 2015 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
#include <libcgc.h>
#include "stdlib.h"
#include "error.h"
#include "malloc.h"
#include "page.h"

int AddPageVar(PageVar *varlist, char *cmd) {
  char *name = strchr(cmd, ':') + 1;
  char *value = strchr(name, ':') + 1;
  char *end = strchr(cmd, ']');
  if (value - name > sizeof(varlist->name)) {
    // Invalid name length
    return -1;
  } 
  PageVar *pagevar = GetPageVar(varlist, name, value -1);
  if (pagevar != NULL) {
    // Special case, variable already exists
    if (pagevar->value != NULL) {
      free(pagevar->value);
    }
  } else {
    // Add new variable to end of list
    pagevar = varlist;
    while (pagevar->next != NULL) {
      pagevar = pagevar->next;
    }
    pagevar->next = calloc(sizeof(PageVar), 1);
    VerifyPointerOrTerminate(pagevar->next, "New PageVar");
    pagevar = pagevar->next;
  }
  memcpy(pagevar->name, name, value - 1 - name);
  #ifdef PATCHED
  if (end - value <= 0) {
    return -1;
  }
  #endif 
  pagevar->value = calloc(end - value + 1, 1);
  VerifyPointerOrTerminate(pagevar->value, "PageVar->value");
  memcpy(pagevar->value, value, end - value);
  return 1;
}

PageVar *GetPageVar(PageVar *varlist, char *name, char *end) {
  while (varlist != NULL) {
    if (strncmp(varlist->name, name, end - name) == 0) {
      return varlist;
    }
    varlist = varlist->next;
  }
  return NULL;
}

void DestroyVarList(PageVar *varlist) {
  if (varlist == NULL) {
    return;
  }
  if (varlist->next != NULL) {
    DestroyVarList(varlist->next);
    varlist->next = NULL;
  }
  if (varlist->value != NULL) {
    free(varlist->value);
    varlist->value = NULL;
  }
  free(varlist);
}

// Processes user supplied variable definitions and then serves the requested
// page using those variables. 
// Variable definitions are in the same syntax as those scripted in a page
// eg. [var:name:value][var:name2:value2]
int InteractWithPage(char *page, int page_size, char *override_data) {
#ifdef PATCHED
  if (override_data == NULL) {
    return ServePageWithOverride(page, page_size, NULL);
  }
#endif 
  PageVar *override_list = calloc(sizeof(PageVar), 1);
  VerifyPointerOrTerminate(override_list, "Override_list initialization");
  // Process override variable definitions
  while(*override_data != '\0' && *override_data != ']') {
    // Check for start of var definition
    if (*override_data != '[') { break; }
    // Process var definition
    AddPageVar(override_list, override_data);
    // Locate end of var definition
    char *end_of_var = strchr(override_data, ']');
    if (end_of_var == NULL) { break; }
    // Step over var definition
    override_data = end_of_var + 1;
  }
  // Serve page with overridden variables
  return ServePageWithOverride(page, page_size, override_list);
}

// Serve a page without supplying override variables.
int ServePage(char *page, int page_size) {
  return ServePageWithOverride(page, page_size, NULL);
}

int in_a_box = 0;
char line[81];
int line_length;

void FlushOutput() {
  printf("@s\n", line);
  memset(line, '\0', sizeof(line));
  if (in_a_box) {
    memset(line, ' ', sizeof(line) - 1);
    line[0] = '*';
    line[79] = '*';
    line_length = 2;
  } else {
    line_length = 0;
  }
}

void OutputChar(char c) {
  line[line_length++] = c;
  if (in_a_box && line_length == 78) {
    FlushOutput();
  } else if (line_length == 80) {
    FlushOutput();
  }
}

void OutputStr(char *s) {
  if (strlen(s) + line_length > 80) {
    FlushOutput();
  }
  if (strlen(s) > 80) {
    printf("@s\n", s);
  } else {
    memcpy(&line[line_length],s, strlen(s));
    line_length += strlen(s);
  }
} 

// Serves a page by interpreting command codes, processing script commands,
// and handling variable substitution. Any variables provided in the override_list
// will take precedence over variables of the same name defined in the page. 
int ServePageWithOverride(char *page, int page_size, PageVar *override_list) {
  // Initialize varlist
  PageVar *varlist = calloc(sizeof(PageVar), 1);
  VerifyPointerOrTerminate(varlist, "VarList initialization");
  in_a_box = 0;
  memset(line, '\0', sizeof(line));
  line_length = 0;
  
  #ifdef PATCHED
  if (page == NULL) {
    goto error;
  }
  #endif

  while ((*page != '\0')&&(page < page + page_size)) {
    if (*page == '~') {
      // Command character, process command
      page++;
      switch (*page) {
        case 't': {
          for (int i=0; i<4; i++) {
            OutputChar(' ');
          }
          break;
        }
        case 'n': {
          FlushOutput();
          break;
        }
        case '[': {
          OutputChar('[');
          break;
        }
        case ']': {
          OutputChar(']');
          break;
        }
        case '~': {
          OutputChar('~');
          break;
        }
        case '#': {
          OutputChar('#');
          break;
        }
        default: {
          printf("ERROR: Invalid control code\n");
          goto error;
        }
      }
      page++;
    } else if (*page == '[') {
      // Script tag, find closing tag and process script
      char *close = ++page;
      while (*close != ']' && *close != '\0') close++;
      if (*close == '\0') {
        goto error;
      }
      // Process script commands
      if (strncmp(page, "line", strlen("line")) == 0) {
        page += strlen("line");
        if (*page != ':') {
          goto error;
        }
        char c = *(++page);
        if (*(++page) != ':') {
          goto error;
        }
        int length = atoi(++page);
        for (int i = 0; i < length; i++) {
          OutputChar(c);
        }
        page = close + 1;
      } else if (strncmp(page, "var", strlen("var")) == 0) {
        AddPageVar(varlist, page);
        page = close + 1;
      } else if (strncmp(page, "box", strlen("box")) == 0) {
        in_a_box = 1;
        FlushOutput();
        for (int i = 0; i < 80; i++) {
          putc('*');
        }
        printf("\n");
        page += 4;
      } 
    } else if (*page == ']') {
      page++;
      if (in_a_box) {
        in_a_box = 0;
        FlushOutput();
        for (int i = 0; i < 80; i++) {
          putc('*');
        }
        printf("\n");
      } else {
        goto error;
      }
    } else if (*page == '#') {
      // Variable substitution
      char *end = ++page;
      while (*end != '\0' && *end != '#') { end++; }
      if (*end != '#') {
        goto error;
      }
      PageVar *var = NULL;
      // Check for overridden variables
      if (override_list != NULL) {
        var = GetPageVar(override_list, page, end);
      }
      // Fall back to default values if override doesn't exist
      if (var == NULL) {
        var = GetPageVar(varlist, page, end);
      }
      // If a value has been found, output it
      if (var != NULL) {
        OutputStr(var->value);
      }
      page = end + 1;
    } else {
      // Normal character, send to output
      OutputChar(*page);
      page++;
    }
  }
  if (line_length != 0) {
    FlushOutput();
  }
  DestroyVarList(varlist);
  DestroyVarList(override_list);
  return 0;

error:
  printf("ERROR: Invalid syntax\n");
  DestroyVarList(varlist);
  DestroyVarList(override_list);
  return -1;
}




