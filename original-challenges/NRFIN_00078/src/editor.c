/*
 * Copyright (C) Narf Industries <info@narfindustries.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "editor.h"
#include "regex.h"

struct line {
    struct list_node list;
    char buf[0];
};

typedef char __attribute__((regparm(1))) (*transform_function)(unsigned int, void *);

static char __attribute((regparm(1))) invertcase_transform(unsigned int, void *);
static char __attribute((regparm(1))) tolowercase_transform(unsigned int, void *);
static char __attribute((regparm(1))) touppercase_transform(unsigned int, void *);
static char __attribute((regparm(1))) debug_transform(unsigned int, void *);

static struct {
    struct list line_list;
    struct line *marks[28];
    int debug_mode;
    transform_function transforms[27];
} state = {
    { 0 },
    { 0 },
    0,
    {
        ['i' - 'a'] = invertcase_transform,
        ['l' - 'a'] = tolowercase_transform,
        ['u' - 'a'] = touppercase_transform,
        [26] = debug_transform
    }
};

static struct line *
get_line_by_address(int address)
{
    struct list_node *cur = state.line_list.head;

#ifdef PATCHED_1
    if (address < 0 && address >= DOLLAR_MARK)
#else
    if (address < 0)
#endif
        return state.marks[-address - 1];

    while (cur && address--)
        cur = cur->next;

    return cur ? list_entry(struct line, list, cur) : NULL;
}

static int
do_insert(struct command *command, struct result **result, int append)
{
    int i;
    struct line *newline, *line = NULL;
    char *tok;
    unsigned int line_count;

    *result = NULL;

    if ((line = get_line_by_address(command->start)) == NULL)
        line = list_entry(struct line, list, state.line_list.tail);

    if (!append && line)
        line = line->list.prev ? list_entry(struct line, list, line->list.prev) : NULL;

    for (i = 0; i < command->size; i++)
        if (command->buf[i] == '\0')
            return EXIT_FAILURE;

    line_count = list_length(&state.line_list);

    // We always ensure that commands end with at least one NULL byte
    tok = strtok(command->buf, '\n');
    while (tok != NULL) {
        if (strlen(tok) > MAX_LINE_SIZE)
            return EXIT_FAILURE;

        if (++line_count > MAX_LINE_COUNT)
            return EXIT_FAILURE;

        if ((newline = calloc(sizeof(struct line) + strlen(tok) + 1)) == NULL)
            return EXIT_FAILURE;

        strcpy(newline->buf, tok);
        list_insert_entry_after(struct line, list, &state.line_list, line, newline);

        line = newline;
        tok = strtok(NULL, '\n');
    }

    // Update special marks
    state.marks[-DOT_MARK - 1] = line;
    state.marks[-DOLLAR_MARK - 1] = state.line_list.tail ?
        list_entry(struct line, list, state.line_list.tail) : NULL;

    return EXIT_SUCCESS;
}

static int
append_command(struct command *command, struct result **result)
{
    *result = NULL;
    return do_insert(command, result, 1);
}

static int
insert_command(struct command *command, struct result **result)
{
    *result = NULL;
    return do_insert(command, result, 0);
}

static int
delete_command(struct command *command, struct result **result)
{
    int i;
    struct line *start, *end, *cur, *tofree = NULL;

    *result = NULL;

    if (state.line_list.head == NULL)
        return EXIT_FAILURE;

    if ((start = get_line_by_address(command->start)) == NULL)
        return EXIT_FAILURE;

    if ((end = get_line_by_address(command->end)) == NULL)
        return EXIT_FAILURE;

    for (cur = start; cur && cur != list_entry(struct line, list, end->list.next);
            cur = list_entry(struct line, list, cur->list.next)) {
        free(tofree);
        tofree = cur;

        // Remove stale marks
        for (i = 0; i < sizeof(state.marks) / sizeof(state.marks[0]); i++)
            if (state.marks[i] == cur)
                state.marks[i] = NULL;

        list_remove_entry(struct line, list, &state.line_list, cur);
    }

    free(tofree);

    // Update special marks
    state.marks[-DOT_MARK - 1] = get_line_by_address(command->start);
    state.marks[-DOLLAR_MARK - 1] = state.line_list.tail ?
        list_entry(struct line, list, state.line_list.tail) : NULL;

    return EXIT_SUCCESS;
}

static int
change_command(struct command *command, struct result **result)
{
    *result = NULL;

    if (delete_command(command, result) != EXIT_SUCCESS)
        return EXIT_FAILURE;

    return append_command(command, result);
}

static int
join_command(struct command *command, struct result **result)
{
    int i;
    size_t size = 0;
    struct line *start, *end, *newline, *cur, *tofree = NULL;
    char *c;

    *result = NULL;

    if (state.line_list.head == NULL)
        return EXIT_FAILURE;

    if ((start = get_line_by_address(command->start)) == NULL)
        return EXIT_FAILURE;

    if ((end = get_line_by_address(command->end)) == NULL)
        return EXIT_FAILURE;

    // Calculate our size
    for (cur = start; cur && cur != list_entry(struct line, list, end->list.next);
            cur = list_entry(struct line, list, cur->list.next))
        size += strlen(cur->buf);

    if ((newline = calloc(sizeof(struct line) + size + 1)) == NULL)
        return EXIT_FAILURE;

    c = newline->buf;
    for (cur = start; cur && cur != list_entry(struct line, list, end->list.next);
            cur = list_entry(struct line, list, cur->list.next)) {

        // Remove stale marks
        for (i = 0; i < sizeof(state.marks) / sizeof(state.marks[0]); i++)
            if (state.marks[i] == cur)
                state.marks[i] = NULL;

        if (cur != start) {
            free(tofree);
            tofree = cur;
            list_remove_entry(struct line, list, &state.line_list, cur);
        }

        strcpy(c, cur->buf);
        c += strlen(cur->buf);
    }

    // Insert the new line, remove old start line
    list_insert_entry_before(struct line, list, &state.line_list, start, newline);
    list_remove_entry(struct line, list, &state.line_list, start);
    free(start);

    // Update special marks
    state.marks[-DOT_MARK - 1] = newline;
    state.marks[-DOLLAR_MARK - 1] = state.line_list.tail ?
        list_entry(struct line, list, state.line_list.tail) : NULL;

    return EXIT_SUCCESS;
}

static int
mark_command(struct command *command, struct result **result)
{
    unsigned int index;
    struct line *start;

    *result = NULL;

    if (state.line_list.head == NULL)
        return EXIT_FAILURE;

    if (command->size != sizeof(unsigned int))
        return EXIT_FAILURE;

    index = *(unsigned int *)command->buf;
    if (index > (sizeof(state.marks) / sizeof(state.marks[0]) - 2))
        return EXIT_FAILURE;

    if ((start = get_line_by_address(command->start)) == NULL)
        return EXIT_FAILURE;

    state.marks[index] = start;

    // Update special marks
    state.marks[-DOT_MARK - 1] = start;
    state.marks[-DOLLAR_MARK - 1] = state.line_list.tail ?
        list_entry(struct line, list, state.line_list.tail) : NULL;

    return EXIT_SUCCESS;
}

static int
get_mark_command(struct command *command, struct result **result)
{
    unsigned int index;
    struct line *start;

    *result = NULL;

    if (command->size != sizeof(unsigned int))
        return EXIT_FAILURE;

    index = *(unsigned int *)command->buf;
    if (index > (sizeof(state.marks) / sizeof(state.marks[0]) - 2))
        return EXIT_FAILURE;

    if ((*result = calloc(sizeof(struct result) + sizeof(unsigned int))) == NULL)
        return EXIT_FAILURE;

    (*result)->size = sizeof(unsigned int);
    memcpy((*result)->buf, &state.marks[index], sizeof(unsigned int));

    // Update special marks
    state.marks[-DOT_MARK - 1] = state.marks[index];
    state.marks[-DOLLAR_MARK - 1] = state.line_list.tail ?
        list_entry(struct line, list, state.line_list.tail) : NULL;

    return EXIT_SUCCESS;
}

static int
list_command(struct command *command, struct result **result)
{
    size_t size = 0;
    struct line *start, *end, *cur;
    char *c;

    *result = NULL;

    if (state.line_list.head == NULL)
        return EXIT_FAILURE;

    if ((start = get_line_by_address(command->start)) == NULL)
        return EXIT_FAILURE;

    if ((end = get_line_by_address(command->end)) == NULL)
        return EXIT_FAILURE;

    // Calculate our size
    for (cur = start; cur && cur != list_entry(struct line, list, end->list.next);
            cur = list_entry(struct line, list, cur->list.next))
        size += strlen(cur->buf) + 1;

    if ((*result = calloc(sizeof(struct result) + size + 1)) == NULL)
        return EXIT_FAILURE;

    (*result)->size = size;
    c = (*result)->buf;
    for (cur = start; cur && cur != list_entry(struct line, list, end->list.next);
            cur = list_entry(struct line, list, cur->list.next)) {

        strcpy(c, cur->buf);
        strcat(c, "\n");
        c += strlen(cur->buf) + 1;
    }

    // Update special marks
    state.marks[-DOT_MARK - 1] = end;
    state.marks[-DOLLAR_MARK - 1] = state.line_list.tail ?
        list_entry(struct line, list, state.line_list.tail) : NULL;

    return EXIT_SUCCESS;
} 

static int
num_command(struct command *command, struct result **result)
{
    int start_line = 0;
    size_t size = 0;
    struct line *start, *end, *cur;
    char *c, *buf, s[20];

    *result = NULL;

    if (state.line_list.head == NULL)
        return EXIT_FAILURE;

    if ((start = get_line_by_address(command->start)) == NULL)
        return EXIT_FAILURE;

    if ((end = get_line_by_address(command->end)) == NULL)
        return EXIT_FAILURE;

    for (cur = list_entry(struct line, list, state.line_list.head);
            cur != start;
            cur = list_entry(struct line, list, cur->list.next))
        start_line++;

    // Calculate our size
    for (cur = start; cur && cur != list_entry(struct line, list, end->list.next);
            cur = list_entry(struct line, list, cur->list.next))
#ifdef PATCHED_2
        size += strlen(cur->buf) + 5;
#else
        size += strlen(cur->buf) + 4;
#endif

    if ((*result = calloc(sizeof(struct result) + size + 1)) == NULL)
        return EXIT_FAILURE;

    if ((buf = calloc(size + 1)) == NULL)
        return EXIT_FAILURE;

    c = buf;
    for (cur = start; cur && cur != list_entry(struct line, list, end->list.next);
            cur = list_entry(struct line, list, cur->list.next)) {

        start_line++;

        strcpy(c, itoa(start_line, s));
        strcat(c, " ");
        strcat(c, cur->buf);
        strcat(c, "\n");
        c += strlen(c);
    }
    strcpy((*result)->buf, buf);
    (*result)->size = strlen((*result)->buf);

    free(buf);

    // Update special marks
    state.marks[-DOT_MARK - 1] = end;
    state.marks[-DOLLAR_MARK - 1] = state.line_list.tail ?
        list_entry(struct line, list, state.line_list.tail) : NULL;

    return EXIT_SUCCESS;
} 

static int
do_search_command(struct command *command, struct result **result, int invert)
{
    size_t size = 0;
    struct line *start, *end, *cur;
    char *c, *match_begin, *match_end;

    *result = NULL;

    if (state.line_list.head == NULL)
        return EXIT_FAILURE;

    if ((start = get_line_by_address(command->start)) == NULL)
        return EXIT_FAILURE;

    if ((end = get_line_by_address(command->end)) == NULL)
        return EXIT_FAILURE;

    // Calculate our size
    for (cur = start; cur && cur != list_entry(struct line, list, end->list.next);
            cur = list_entry(struct line, list, cur->list.next))
        if (!invert && regex_match(command->buf, cur->buf, &match_begin, &match_end) == EXIT_SUCCESS)
            size += strlen(cur->buf) + 1;
        else if (invert && regex_match(command->buf, cur->buf, &match_begin, &match_end) == EXIT_FAILURE)
            size += strlen(cur->buf) + 1;

    if (size == 0)
        return EXIT_FAILURE;

    if ((*result = calloc(sizeof(struct result) + size + 1)) == NULL)
        return EXIT_FAILURE;

    (*result)->size = size;
    c = (*result)->buf;
    for (cur = start; cur && cur != list_entry(struct line, list, end->list.next);
            cur = list_entry(struct line, list, cur->list.next)) {

        if (!invert && regex_match(command->buf, cur->buf, &match_begin, &match_end) == EXIT_SUCCESS) {
            strcpy(c, cur->buf);
            strcat(c, "\n");
            c += strlen(cur->buf) + 1;
        } else if (invert && regex_match(command->buf, cur->buf, &match_begin, &match_end) == EXIT_FAILURE) {
            strcpy(c, cur->buf);
            strcat(c, "\n");
            c += strlen(cur->buf) + 1;
        }
    }

    // Update special marks
    state.marks[-DOT_MARK - 1] = end;
    state.marks[-DOLLAR_MARK - 1] = state.line_list.tail ?
        list_entry(struct line, list, state.line_list.tail) : NULL;

    return EXIT_SUCCESS;
}

static int
search_command(struct command *command, struct result **result)
{
    *result = NULL;
    return do_search_command(command, result, 0);
}

static int
inverse_search_command(struct command *command, struct result **result)
{
    *result = NULL;
    return do_search_command(command, result, 1);
}

static int
transform_command(struct command *command, struct result **result)
{
    unsigned int index;
    struct line *start, *end, *cur;
    char *c;

    *result = NULL;

    if (state.line_list.head == NULL)
        return EXIT_FAILURE;

    if (state.debug_mode) {
        if (command->size != 2 * sizeof(unsigned int))
            return EXIT_FAILURE;

        index = 26;
    } else {
        if (command->size != sizeof(unsigned int))
            return EXIT_FAILURE;

        index = *(unsigned int *)command->buf;
        index -= 'a';
        if (index > (sizeof(state.transforms) / sizeof(state.transforms[0])))
            return EXIT_FAILURE;
    }

    if (state.transforms[index] == NULL)
        return EXIT_FAILURE;

    if ((start = get_line_by_address(command->start)) == NULL)
        return EXIT_FAILURE;

    if ((end = get_line_by_address(command->end)) == NULL)
        return EXIT_FAILURE;

    for (cur = start; cur && cur != list_entry(struct line, list, end->list.next);
            cur = list_entry(struct line, list, cur->list.next)) {

        for (c = cur->buf; *c; c++)
            *c = state.transforms[index](*c, command->buf);
    }

    // Update special marks
    state.marks[-DOT_MARK - 1] = end;
    state.marks[-DOLLAR_MARK - 1] = state.line_list.tail ?
        list_entry(struct line, list, state.line_list.tail) : NULL;

    return EXIT_SUCCESS;
}

static char __attribute__((regparm(1)))
debug_transform(unsigned int c, void *data)
{
    struct {
        transform_function t;
        unsigned int c;
    } __attribute__((packed)) *dt = data;

    return dt->t(dt->c, NULL);
}

static char __attribute__((regparm(1)))
invertcase_transform(unsigned int c, void *data)
{
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 'A';
    else if (c >= 'A' && c <= 'Z')
        return c - 'A' + 'a';
    else
        return c;
}

static char __attribute__((regparm(1)))
tolowercase_transform(unsigned int c, void *data)
{
    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 'a';
    else
        return c;
}

static char __attribute__((regparm(1)))
touppercase_transform(unsigned int c, void *data)
{
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 'A';
    else
        return c;
}

int
run_command(struct command *command, struct result **result)
{
    *result = NULL;

    switch (command->command) {
    case 'a':
        return append_command(command, result);
    case 'c':
        return change_command(command, result);
    case 'd':
        return delete_command(command, result);
    case 'g':
        return search_command(command, result);
    case 'i':
        return insert_command(command, result);
    case 'j':
        return join_command(command, result);
    case 'l':
        return list_command(command, result);
    case 'm':
        return mark_command(command, result);
    case 'n':
        return num_command(command, result);
    case 'q':
        _terminate(0);
    case 't':
        return transform_command(command, result);
    case 'v':
        return inverse_search_command(command, result);
    case '=':
        return get_mark_command(command, result);
    }

    return EXIT_FAILURE;
}
