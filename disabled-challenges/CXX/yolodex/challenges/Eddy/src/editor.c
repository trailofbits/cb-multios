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

#include "cgc_editor.h"
#include "cgc_regex.h"

struct line {
    struct list_node list;
    char buf[0];
};

typedef char __attribute__((regparm(1))) (*transform_function)(unsigned int, void *);

static char __attribute((regparm(1))) cgc_invertcase_transform(unsigned int, void *);
static char __attribute((regparm(1))) cgc_tolowercase_transform(unsigned int, void *);
static char __attribute((regparm(1))) cgc_touppercase_transform(unsigned int, void *);
static char __attribute((regparm(1))) cgc_debug_transform(unsigned int, void *);

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
        ['i' - 'a'] = cgc_invertcase_transform,
        ['l' - 'a'] = cgc_tolowercase_transform,
        ['u' - 'a'] = cgc_touppercase_transform,
        [26] = cgc_debug_transform
    }
};

static struct line *
cgc_get_line_by_address(int address)
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
cgc_do_insert(struct command *command, struct result **result, int append)
{
    int i;
    struct line *newline, *line = NULL;
    char *tok;
    unsigned int line_count;

    *result = NULL;

    if ((line = cgc_get_line_by_address(command->start)) == NULL)
        line = list_entry(struct line, list, state.line_list.tail);

    if (!append && line)
        line = line->list.prev ? list_entry(struct line, list, line->list.prev) : NULL;

    for (i = 0; i < command->size; i++)
        if (command->buf[i] == '\0')
            return EXIT_FAILURE;

    line_count = cgc_list_length(&state.line_list);

    // We always ensure that commands end with at least one NULL byte
    tok = cgc_strtok(command->buf, '\n');
    while (tok != NULL) {
        if (cgc_strlen(tok) > MAX_LINE_SIZE)
            return EXIT_FAILURE;

        if (++line_count > MAX_LINE_COUNT)
            return EXIT_FAILURE;

        if ((newline = cgc_calloc(sizeof(struct line) + cgc_strlen(tok) + 1)) == NULL)
            return EXIT_FAILURE;

        cgc_strcpy(newline->buf, tok);
        list_insert_entry_after(struct line, list, &state.line_list, line, newline);

        line = newline;
        tok = cgc_strtok(NULL, '\n');
    }

    // Update special marks
    state.marks[-DOT_MARK - 1] = line;
    state.marks[-DOLLAR_MARK - 1] = state.line_list.tail ?
        list_entry(struct line, list, state.line_list.tail) : NULL;

    return EXIT_SUCCESS;
}

static int
cgc_append_command(struct command *command, struct result **result)
{
    *result = NULL;
    return cgc_do_insert(command, result, 1);
}

static int
cgc_insert_command(struct command *command, struct result **result)
{
    *result = NULL;
    return cgc_do_insert(command, result, 0);
}

static int
cgc_delete_command(struct command *command, struct result **result)
{
    int i;
    struct line *start, *end, *cur, *tofree = NULL;

    *result = NULL;

    if (state.line_list.head == NULL)
        return EXIT_FAILURE;

    if ((start = cgc_get_line_by_address(command->start)) == NULL)
        return EXIT_FAILURE;

    if ((end = cgc_get_line_by_address(command->end)) == NULL)
        return EXIT_FAILURE;

    for (cur = start; cur && cur != list_entry(struct line, list, end->list.next);
            cur = list_entry(struct line, list, cur->list.next)) {
        cgc_free(tofree);
        tofree = cur;

        // Remove stale marks
        for (i = 0; i < sizeof(state.marks) / sizeof(state.marks[0]); i++)
            if (state.marks[i] == cur)
                state.marks[i] = NULL;

        list_remove_entry(struct line, list, &state.line_list, cur);
    }

    cgc_free(tofree);

    // Update special marks
    state.marks[-DOT_MARK - 1] = cgc_get_line_by_address(command->start);
    state.marks[-DOLLAR_MARK - 1] = state.line_list.tail ?
        list_entry(struct line, list, state.line_list.tail) : NULL;

    return EXIT_SUCCESS;
}

static int
cgc_change_command(struct command *command, struct result **result)
{
    *result = NULL;

    if (cgc_delete_command(command, result) != EXIT_SUCCESS)
        return EXIT_FAILURE;

    return cgc_append_command(command, result);
}

static int
cgc_join_command(struct command *command, struct result **result)
{
    int i;
    cgc_size_t size = 0;
    struct line *start, *end, *newline, *cur, *tofree = NULL;
    char *c;

    *result = NULL;

    if (state.line_list.head == NULL)
        return EXIT_FAILURE;

    if ((start = cgc_get_line_by_address(command->start)) == NULL)
        return EXIT_FAILURE;

    if ((end = cgc_get_line_by_address(command->end)) == NULL)
        return EXIT_FAILURE;

    // Calculate our size
    for (cur = start; cur && cur != list_entry(struct line, list, end->list.next);
            cur = list_entry(struct line, list, cur->list.next))
        size += cgc_strlen(cur->buf);

    if ((newline = cgc_calloc(sizeof(struct line) + size + 1)) == NULL)
        return EXIT_FAILURE;

    c = newline->buf;
    for (cur = start; cur && cur != list_entry(struct line, list, end->list.next);
            cur = list_entry(struct line, list, cur->list.next)) {

        // Remove stale marks
        for (i = 0; i < sizeof(state.marks) / sizeof(state.marks[0]); i++)
            if (state.marks[i] == cur)
                state.marks[i] = NULL;

        if (cur != start) {
            cgc_free(tofree);
            tofree = cur;
            list_remove_entry(struct line, list, &state.line_list, cur);
        }

        cgc_strcpy(c, cur->buf);
        c += cgc_strlen(cur->buf);
    }

    // Insert the new line, remove old start line
    list_insert_entry_before(struct line, list, &state.line_list, start, newline);
    list_remove_entry(struct line, list, &state.line_list, start);
    cgc_free(start);

    // Update special marks
    state.marks[-DOT_MARK - 1] = newline;
    state.marks[-DOLLAR_MARK - 1] = state.line_list.tail ?
        list_entry(struct line, list, state.line_list.tail) : NULL;

    return EXIT_SUCCESS;
}

static int
cgc_mark_command(struct command *command, struct result **result)
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

    if ((start = cgc_get_line_by_address(command->start)) == NULL)
        return EXIT_FAILURE;

    state.marks[index] = start;

    // Update special marks
    state.marks[-DOT_MARK - 1] = start;
    state.marks[-DOLLAR_MARK - 1] = state.line_list.tail ?
        list_entry(struct line, list, state.line_list.tail) : NULL;

    return EXIT_SUCCESS;
}

static int
cgc_get_mark_command(struct command *command, struct result **result)
{
    unsigned int index;
    struct line *start;

    *result = NULL;

    if (command->size != sizeof(unsigned int))
        return EXIT_FAILURE;

    index = *(unsigned int *)command->buf;
    if (index > (sizeof(state.marks) / sizeof(state.marks[0]) - 2))
        return EXIT_FAILURE;

    if ((*result = cgc_calloc(sizeof(struct result) + sizeof(unsigned int))) == NULL)
        return EXIT_FAILURE;

    (*result)->size = sizeof(unsigned int);
    cgc_memcpy((*result)->buf, &state.marks[index], sizeof(unsigned int));

    // Update special marks
    state.marks[-DOT_MARK - 1] = state.marks[index];
    state.marks[-DOLLAR_MARK - 1] = state.line_list.tail ?
        list_entry(struct line, list, state.line_list.tail) : NULL;

    return EXIT_SUCCESS;
}

static int
cgc_list_command(struct command *command, struct result **result)
{
    cgc_size_t size = 0;
    struct line *start, *end, *cur;
    char *c;

    *result = NULL;

    if (state.line_list.head == NULL)
        return EXIT_FAILURE;

    if ((start = cgc_get_line_by_address(command->start)) == NULL)
        return EXIT_FAILURE;

    if ((end = cgc_get_line_by_address(command->end)) == NULL)
        return EXIT_FAILURE;

    // Calculate our size
    for (cur = start; cur && cur != list_entry(struct line, list, end->list.next);
            cur = list_entry(struct line, list, cur->list.next))
        size += cgc_strlen(cur->buf) + 1;

    if ((*result = cgc_calloc(sizeof(struct result) + size + 1)) == NULL)
        return EXIT_FAILURE;

    (*result)->size = size;
    c = (*result)->buf;
    for (cur = start; cur && cur != list_entry(struct line, list, end->list.next);
            cur = list_entry(struct line, list, cur->list.next)) {

        cgc_strcpy(c, cur->buf);
        cgc_strcat(c, "\n");
        c += cgc_strlen(cur->buf) + 1;
    }

    // Update special marks
    state.marks[-DOT_MARK - 1] = end;
    state.marks[-DOLLAR_MARK - 1] = state.line_list.tail ?
        list_entry(struct line, list, state.line_list.tail) : NULL;

    return EXIT_SUCCESS;
} 

static int
cgc_num_command(struct command *command, struct result **result)
{
    int start_line = 0;
    cgc_size_t size = 0;
    struct line *start, *end, *cur;
    char *c, *buf, s[20];

    *result = NULL;

    if (state.line_list.head == NULL)
        return EXIT_FAILURE;

    if ((start = cgc_get_line_by_address(command->start)) == NULL)
        return EXIT_FAILURE;

    if ((end = cgc_get_line_by_address(command->end)) == NULL)
        return EXIT_FAILURE;

    for (cur = list_entry(struct line, list, state.line_list.head);
            cur != start;
            cur = list_entry(struct line, list, cur->list.next))
        start_line++;

    // Calculate our size
    for (cur = start; cur && cur != list_entry(struct line, list, end->list.next);
            cur = list_entry(struct line, list, cur->list.next))
#ifdef PATCHED_2
        size += cgc_strlen(cur->buf) + 5;
#else
        size += cgc_strlen(cur->buf) + 4;
#endif

    if ((*result = cgc_calloc(sizeof(struct result) + size + 1)) == NULL)
        return EXIT_FAILURE;

    if ((buf = cgc_calloc(size + 1)) == NULL)
        return EXIT_FAILURE;

    c = buf;
    for (cur = start; cur && cur != list_entry(struct line, list, end->list.next);
            cur = list_entry(struct line, list, cur->list.next)) {

        start_line++;

        cgc_strcpy(c, cgc_itoa(start_line, s));
        cgc_strcat(c, " ");
        cgc_strcat(c, cur->buf);
        cgc_strcat(c, "\n");
        c += cgc_strlen(c);
    }
    cgc_strcpy((*result)->buf, buf);
    (*result)->size = cgc_strlen((*result)->buf);

    cgc_free(buf);

    // Update special marks
    state.marks[-DOT_MARK - 1] = end;
    state.marks[-DOLLAR_MARK - 1] = state.line_list.tail ?
        list_entry(struct line, list, state.line_list.tail) : NULL;

    return EXIT_SUCCESS;
} 

static int
cgc_do_search_command(struct command *command, struct result **result, int invert)
{
    cgc_size_t size = 0;
    struct line *start, *end, *cur;
    char *c, *match_begin, *match_end;

    *result = NULL;

    if (state.line_list.head == NULL)
        return EXIT_FAILURE;

    if ((start = cgc_get_line_by_address(command->start)) == NULL)
        return EXIT_FAILURE;

    if ((end = cgc_get_line_by_address(command->end)) == NULL)
        return EXIT_FAILURE;

    // Calculate our size
    for (cur = start; cur && cur != list_entry(struct line, list, end->list.next);
            cur = list_entry(struct line, list, cur->list.next))
        if (!invert && cgc_regex_match(command->buf, cur->buf, &match_begin, &match_end) == EXIT_SUCCESS)
            size += cgc_strlen(cur->buf) + 1;
        else if (invert && cgc_regex_match(command->buf, cur->buf, &match_begin, &match_end) == EXIT_FAILURE)
            size += cgc_strlen(cur->buf) + 1;

    if (size == 0)
        return EXIT_FAILURE;

    if ((*result = cgc_calloc(sizeof(struct result) + size + 1)) == NULL)
        return EXIT_FAILURE;

    (*result)->size = size;
    c = (*result)->buf;
    for (cur = start; cur && cur != list_entry(struct line, list, end->list.next);
            cur = list_entry(struct line, list, cur->list.next)) {

        if (!invert && cgc_regex_match(command->buf, cur->buf, &match_begin, &match_end) == EXIT_SUCCESS) {
            cgc_strcpy(c, cur->buf);
            cgc_strcat(c, "\n");
            c += cgc_strlen(cur->buf) + 1;
        } else if (invert && cgc_regex_match(command->buf, cur->buf, &match_begin, &match_end) == EXIT_FAILURE) {
            cgc_strcpy(c, cur->buf);
            cgc_strcat(c, "\n");
            c += cgc_strlen(cur->buf) + 1;
        }
    }

    // Update special marks
    state.marks[-DOT_MARK - 1] = end;
    state.marks[-DOLLAR_MARK - 1] = state.line_list.tail ?
        list_entry(struct line, list, state.line_list.tail) : NULL;

    return EXIT_SUCCESS;
}

static int
cgc_search_command(struct command *command, struct result **result)
{
    *result = NULL;
    return cgc_do_search_command(command, result, 0);
}

static int
cgc_inverse_search_command(struct command *command, struct result **result)
{
    *result = NULL;
    return cgc_do_search_command(command, result, 1);
}

static int
cgc_transform_command(struct command *command, struct result **result)
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

    if ((start = cgc_get_line_by_address(command->start)) == NULL)
        return EXIT_FAILURE;

    if ((end = cgc_get_line_by_address(command->end)) == NULL)
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
cgc_debug_transform(unsigned int c, void *data)
{
    struct {
        transform_function t;
        unsigned int c;
    } __attribute__((packed)) *dt = data;

    return dt->t(dt->c, NULL);
}

static char __attribute__((regparm(1)))
cgc_invertcase_transform(unsigned int c, void *data)
{
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 'A';
    else if (c >= 'A' && c <= 'Z')
        return c - 'A' + 'a';
    else
        return c;
}

static char __attribute__((regparm(1)))
cgc_tolowercase_transform(unsigned int c, void *data)
{
    if (c >= 'A' && c <= 'Z')
        return c - 'A' + 'a';
    else
        return c;
}

static char __attribute__((regparm(1)))
cgc_touppercase_transform(unsigned int c, void *data)
{
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 'A';
    else
        return c;
}

int
cgc_run_command(struct command *command, struct result **result)
{
    *result = NULL;

    switch (command->command) {
    case 'a':
        return cgc_append_command(command, result);
    case 'c':
        return cgc_change_command(command, result);
    case 'd':
        return cgc_delete_command(command, result);
    case 'g':
        return cgc_search_command(command, result);
    case 'i':
        return cgc_insert_command(command, result);
    case 'j':
        return cgc_join_command(command, result);
    case 'l':
        return cgc_list_command(command, result);
    case 'm':
        return cgc_mark_command(command, result);
    case 'n':
        return cgc_num_command(command, result);
    case 'q':
        cgc__terminate(0);
    case 't':
        return cgc_transform_command(command, result);
    case 'v':
        return cgc_inverse_search_command(command, result);
    case '=':
        return cgc_get_mark_command(command, result);
    }

    return EXIT_FAILURE;
}
