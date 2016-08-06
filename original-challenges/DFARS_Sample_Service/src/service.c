#include "cgc_libc.h"
#include "cgc_malloc.h"
#include "cgc_types.h"

typedef struct _program_state program_state;
typedef int (*process_t)(program_state *, char *);

#define BOOK_SECTION_SIZE 4*25
// #define BOOK_NAME_SIZE 4*148
// #define BOOK_DATA_SIZE 4*250

#define MAX_CHAR 0xFF

#define TOLOWER(x) ((x >= 'A' && x <= 'Z') ? x | 0x20 : x)

#define COMMAND_NAME_SIZE 12
#define INPUT_SIZE 50
#define DIRECTORY_SIZE BOOK_SECTION_SIZE

#define DELIM '|'
#define TRAVERSAL '+'

typedef struct book {
    char *section;
    char *name;
    char *data;
    struct book *next;
} __attribute__((__packed__)) book_t;

typedef struct command {
    struct command *sibling;
    struct command *child;
    process_t method;
    unsigned char value;
} command_t;

struct _program_state {
    char current_dir[DIRECTORY_SIZE];
    command_t command_list;
    char book_count;
    char input_buf[INPUT_SIZE];
    book_t book_list;
};

char *compress(char *string);
int cmd_search(program_state *s, char *args);
int cmd_ch_sec(program_state *s, char *args);
int cmd_compress(program_state *s, char *args);
int cmd_cur_sec(program_state *s, char *args);
int cmd_get(program_state *s, char *args);
int cmd_list(program_state *s, char *args);
int cmd_put(program_state *s, char *args);
int cmd_quit(program_state *s, char *args);
int cmd_make_sec(program_state *s, char *args);
int normalize_path(char *path);
int process(program_state *s);
void register_book(program_state *s, char *section, char *name, char *data);
process_t get_command(program_state *s, char *name);
void remove_newline(char *line);

void register_book(program_state *s, char *section, char *name, char *data) {
    book_t *bk = &(s->book_list);

    if (!section)
        err(1, "invalid section");
    
    if (!name)
        err(1, "invalid name");
       
    if (!data)
        err(1, "invalid data");

    while (bk != NULL) {
        if (0 == strlen(bk->section)) {
            bk->section = strdup(section);
            bk->name = strdup(name);
            bk->data = strdup(data);
            bk->next = (book_t *) calloc(1, sizeof(book_t));

            if (!bk->next)
                err(1, "unable to allocate memory");

            s->book_count++;
            break;
        } else
            bk = bk->next;
    }
}

/* This is the vulnerable function.
*
* This function's intent is to normalize "|foo|++|" into "|".  The method is to
* identify a traversal marker "++|", and seek backwards until the previous
* marker "|" is identified, then replace from that location until the next
* marker "|" is found.
*
* If the input does not begin with the marker "|", then the program will
* continue the search into unspecified memory regions.  If the marker is found
* elsewhere, the program will write the input after the traversal marker "++|"
* at the found location.
*
* By placing a a marker "|" in a known location, a specified input may be able
* to leverage the marker "|" to modify memory in a fashion that can be leveraged
* gain execution control.
*/
int normalize_path(char *path) {
    char *p;
    char *q;
    char *previous_delim = NULL;
    char *current_delim  = NULL;
    int depth = 0;

    if (path == NULL)
        return -1;

    const size_t len = strlen(path);
    char *end_of_path = path + len;
    q = p = path;

    while (*p != 0) {
        if (*p == DELIM) {
            previous_delim = current_delim;
            current_delim = p;
            p++;
            continue;
        }

        if (*p == TRAVERSAL) {
            if (current_delim == p - 1 || p == path) {
                if (p[1] == TRAVERSAL && (p[2] == DELIM || p[2] == '\0')) {
                    depth++;

                    if (depth > 2)
                        goto fail;

                    if (previous_delim == NULL)
                        goto done;

                    strlcpy(previous_delim, p + 2, len);

                    if (p[2] == '\0')
                        goto done;

                    current_delim = previous_delim;
                    p = previous_delim;
                    q = p - 1;

                    while (*q != DELIM && q != path) {
#ifdef PATCHED

                        if (q <= path)
                            goto done;

#endif
                        q--;
                    }

                    if (p[0] == DELIM)
                        previous_delim = q;
                    else
                        previous_delim = NULL;
                } else if (p[1] == DELIM) {
                    if (current_delim != NULL) {
                        if (current_delim >= end_of_path)
                            goto done;

                        strlcpy(current_delim, (char *)(end_of_path - current_delim), len);
                        continue;
                    } else {
                        if (p >= end_of_path)
                            goto done;

                        strlcpy(p, (char *)(end_of_path - p), len);
                        continue;
                    }
                } else if (p[1] != '\0') {
                    if (current_delim != NULL)
                        p = current_delim;

                    *p = '\0';
                    goto done;
                }
            }
        }

        p++;
    }

done:
    return 0;
fail:
    return -1;
}

process_t get_command(program_state *s, char *name) {
    command_t *cmd = &(s->command_list);
    process_t method = NULL;

    while (name) {
        if (cmd->value == *name) {
            name++;

            if (cmd->method) {
                method = cmd->method;
                break;
            }
          
            if (cmd->child)
                cmd = cmd->child;
            else
                break;
        } else {
            if (cmd->sibling)
                cmd = cmd->sibling;
            else /* cannot continue */
                break;
        }
    }
    return method;
}

int cmd_cur_sec(program_state *s, char *args) {
    (void) args;
    transmit_str(STDOUT, s->current_dir);
    transmit_str(STDOUT, "\n");
    return 1;
}

int skip_search(size_t *skip_dict, char *needle, size_t needle_len, char *haystack, size_t haystack_len) {
    size_t scan;
    size_t last = needle_len - 1;

    while (haystack_len >= needle_len) {
        for (scan = last; needle[scan] == TOLOWER(haystack[scan]); scan--) {
            if (scan == 0) {
                return 1;
            }
        }

        haystack_len -= skip_dict[(unsigned char) haystack[last]];
        haystack += skip_dict[(unsigned char) haystack[last]];
    }

    return 0;
}

int cmd_search(program_state *s, char *args) {
    book_t *cur_book = &(s->book_list);
    size_t scan;
    size_t last;
    size_t skip_dict[MAX_CHAR + 1];
    size_t scan_len;
    (void) args;

    scan_len = strlen(args);

    if (scan_len == 0) {
        return 1;
    }

    for (scan = 0; scan < scan_len; scan++) {
        args[scan] = TOLOWER(args[scan]);
    }

    for (scan = 0; scan <= MAX_CHAR; scan++) {
        skip_dict[scan] = scan_len;
    }

    last = scan_len - 1;

    for (scan = 0; scan < last; scan++) {
        skip_dict[(unsigned char) args[scan]] = last - scan;
    }

    while (cur_book != NULL) {
        if (skip_search((size_t *)&skip_dict, args, scan_len, cur_book->data, strlen(cur_book->data)) == 1) {
            printf("%s : %s\n", cur_book->section, cur_book->name);
        }

        cur_book = cur_book->next;
    }

    return 1;
}

int cmd_ch_sec(program_state *s, char *args) {
    int changed = 0;
    size_t sub_section_len;
    book_t *cur_book = &(s->book_list);

    sub_section_len = strlen(args);

    if (sub_section_len == 0)
        return 1;

    if (args[0] != DELIM) {
        int ret;
        char *tmpname;
        tmpname = strdup(args);
        assert(tmpname != NULL);

        ret = strlcpy(s->input_buf, s->current_dir, sizeof(s->input_buf));
        assert(ret <= sizeof(s->input_buf));

        ret = strlcat(s->input_buf, tmpname, sizeof(s->input_buf));
        assert(ret <= sizeof(s->input_buf));
        args = s->input_buf;
        free(tmpname);
    }

    if (normalize_path(args) != 0)
        return -1;
        
    sub_section_len = strlen(args);
    
    if (args[0] != DELIM)
        return 0;

    if (args[sub_section_len - 1] != DELIM)
        return 0;
   
    while (cur_book != NULL) {
        size_t section_len = strlen(cur_book->section);

        if (section_len >= sub_section_len) {
            if (0 == strcmp(cur_book->section, args)) {
                strlcpy(s->current_dir, args, sizeof(s->current_dir));
                changed = 1;
                break;
            }
        }

        cur_book = cur_book->next;
    }

    if (changed == 0) {
        cur_book = &(s->book_list);
        while (cur_book != NULL) {
            size_t section_len = strlen(cur_book->section);

            if (section_len >= sub_section_len) {
                if (0 == strncmp(cur_book->section, args, sub_section_len)) {
                    strlcpy(s->current_dir, args, sizeof(s->current_dir));
                    changed = 1;
                    break;
                }
            }

            cur_book = cur_book->next;
        }
    } else {
    }

    return 1;
}

char *compress(char *string) {
    char curr;
    size_t length;
    char *encoded;
    char count = 0x30;
    int i = 0;

    if (string == NULL)
        return NULL;

    curr = *string;
    length = strlen(string);
    encoded = (char *)calloc(((length * 2) + 1), sizeof(char));

    if (encoded == NULL)
        return NULL;

    while (*string) {
        if (curr == *(++string) && count < 0x39)
            count++;
        else {
            encoded[i++] = curr;
            encoded[i++] = count;
            count = 1;
            curr = *string;
        }
    }

    return encoded;
}

int cmd_compress(program_state *s, char *args) {
    book_t *cur_book = &(s->book_list);
    char *compressed = NULL;

    if (args == NULL)
        return -1;

    if (0 == strlen(args))
        return -1;

    if (0 == strlen(s->current_dir))
        return -1;

    while (cur_book != NULL) {
        if (0 == strcmp(cur_book->section, s->current_dir)) {
            if (0 == strcmp(cur_book->name, args)) {
                compressed = compress(cur_book->data);

                if (compressed == NULL)
                    return -1;

                transmit_str(STDOUT, cur_book->name);
                transmit_str(STDOUT, "\n");
                transmit_str(STDOUT, compressed);
                transmit_str(STDOUT, "\n\n");
                free(compressed);
                return 1;
            }
        }

        cur_book = cur_book->next;
    }

    return 1;
}

int cmd_quit(program_state *s, char *args) {
    (void) s;
    (void) args;
    return 0;
}

int cmd_get(program_state *s, char *args) {
    book_t *cur_book = &(s->book_list);

    if (args == NULL)
        return -1;

    if (0 == strlen(args))
        return -1;

    if (NULL == s->current_dir)
        return -1;

    if (0 == strlen(s->current_dir))
        return -1;

    while (cur_book != NULL) {
        if (strlen(cur_book->section) == strlen(s->current_dir)) {
            if (0 == strcmp(cur_book->section, s->current_dir)) {
                if (0 == strcmp(cur_book->name, args)) {
                    transmit_str(STDOUT, cur_book->name);
                    transmit_str(STDOUT, "\n");
                    transmit_str(STDOUT, cur_book->data);
                    transmit_str(STDOUT, "\n\n");
                }
            }
        }

        cur_book = cur_book->next;
    }

    return 1;
}

int cmd_make_sec(program_state *s, char *args) {
    size_t out = 0;
    size_t len = 3;
    char *name;

    if (strlen(args) == 0) {
        return -1;
    }
    
    assert((SIZE_MAX - len) - strlen(args) > strlen(s->current_dir));

    len += strlen(s->current_dir);
    len += strlen(args);

    name = calloc(1, len);
    assert(name != NULL);

    if (strlen(s->current_dir) > 0) {
        out = strlcat(name, s->current_dir, len);
        assert(out <= len);
    } else {
        out = strlcat(name, "|", len);
        assert(out <= len);
    }
    
    out = strlcat(name, args, len);
    assert(out <= len);
    
    out = strlcat(name, "|", len);
    assert(out <= len);

    register_book(s, name, "", "");
    return 1;
}

int cmd_put(program_state *s, char *args) {
    char *name;
    char *data;

    if (strlen(s->current_dir) == 0) {
        return -1;
    }

    name = strtok(args, " ");

    if (name == NULL) {
        return -1;
    }

    data = strtok(NULL, "\x00");

    if (data == NULL) {
        return -1;
    }

    register_book(s, s->current_dir, name, data);
    return 1;
}

int cmd_list(program_state *s, char *args) {
    (void) args;
    book_t *cur_book = &(s->book_list);
    transmit_str(STDOUT, "current section: ");
    transmit_str(STDOUT, s->current_dir);
    transmit_str(STDOUT, "\n");

    while (cur_book != NULL) {
        if (0 == strlen(cur_book->section))
            break;

        if (0 == strncmp(cur_book->section, s->current_dir, strlen(s->current_dir))) {
            if (strlen(cur_book->section) - strlen(s->current_dir) > 0) {
                transmit_all(STDOUT, cur_book->section + strlen(s->current_dir), strlen(cur_book->section) - strlen(s->current_dir));
                transmit_str(STDOUT, ":");
            }

            transmit_str(STDOUT, cur_book->name);
            transmit_str(STDOUT, "\n");
        }

        cur_book = cur_book->next;
    }

    transmit_str(STDOUT, "\n");
    return 1;
}

void remove_newline(char *line) {
    size_t new_line = strlen(line) - 1;

    if (line[new_line] == '\n')
        line[new_line] = '\0';
}

int receive_delim(int fd, char *buf, const size_t size, char delim) {
    size_t rx = 0;
    size_t rx_now = 0;
    int ret;

    if (!buf)
        return 1;

    if (!size)
        return 2;

    while (rx < size) {
        ret = receive(fd, buf + rx, 1, &rx_now);
        if (rx_now == 0) {
            //should never return until at least something was received
            //so consider this an error too
            return 3;
        }
        if (ret != 0) {
            return 3;
        }
        if (buf[rx] == delim) {
            break;
        }
        rx += rx_now;
    }

    return 0;
}

int process(program_state *s) {
    int ret;
    // size_t size;
    char *name;
    char *args;
    process_t method;

    while (1) {
        memset(s->input_buf, 0, sizeof(s->input_buf));
        transmit_str(STDOUT, "> ");

        if (0 != receive_delim(0, s->input_buf, sizeof(s->input_buf) - 1, '\n')) {
            return -1;
        }

        remove_newline(s->input_buf);

        if (strlen(s->input_buf) == 0)
            continue;

        name = strtok(s->input_buf, " ");
        args = strtok(NULL, "\x00");

        if (strlen(name) >= COMMAND_NAME_SIZE)
            return -1;

        method = get_command(s, name);

        if (method == NULL) {
            transmit_str(STDOUT, "invalid command: ");
            transmit_str(STDOUT, name);
            transmit_str(STDOUT, "\n");
            continue;
        }

        ret = (method)(s, args);
        
        if (ret == -1) {
            transmit_str(STDOUT, "command failed: ");
            transmit_str(STDOUT, name);
            transmit_str(STDOUT, "\n");
            return -1;
        }

        if (ret == 0) {
            return 0;
        }
    }
}

int main(void) {
    program_state s;
    memset(&s, 0, sizeof(s));
    
    command_t node_0x40f0;
    command_t node_0x40d0;
    command_t node_0x40b0;
    command_t node_0x4090;
    command_t node_0x4070;
    command_t node_0x4050;
    command_t node_0x4030;
    command_t node_0x4010;
    command_t node_0x3ff0;
    command_t node_0x3fd0;
    command_t node_0x3fb0;
    command_t node_0x3f90;
    command_t node_0x3f70;
    command_t node_0x3f50;
    command_t node_0x3f30;
    command_t node_0x3f10;
    command_t node_0x3ef0;
    command_t node_0x3ed0;
    command_t node_0x3eb0;
    command_t node_0x3e90;
    command_t node_0x3e70;
    command_t node_0x3e50;
    command_t node_0x3e30;
    command_t node_0x3e10;
    command_t node_0x3df0;
    command_t node_0x3dd0;
    command_t node_0x3db0;
    command_t node_0x3d90;
    command_t node_0x3d70;
    command_t node_0x3d50;
    command_t node_0x3d30;
    command_t node_0x3d10;
    command_t node_0x3cf0;
    command_t node_0x3cd0;
    command_t node_0x3cb0;
    command_t node_0x3c90;
    command_t node_0x3c70;
    command_t node_0x3c50;
    command_t node_0x3c30;
    command_t node_0x3c10;
    command_t node_0x3bf0;
    command_t node_0x3bd0;
    command_t node_0x3bb0;
    command_t node_0x3b90;
    command_t node_0x3b70;
    command_t node_0x3b50;

    node_0x40f0.value = 99; /* c */
    node_0x40f0.method = &cmd_ch_sec;
    node_0x40d0.value = 101; /* e */
    node_0x40d0.child = &node_0x40f0;
    node_0x40b0.value = 115; /* s */
    node_0x40b0.child = &node_0x40d0;
    node_0x4090.value = 95; /* _ */
    node_0x4090.child = &node_0x40b0;
    node_0x4070.value = 104; /* h */
    node_0x4070.child = &node_0x4090;
    node_0x4050.value = 115; /* s */
    node_0x4050.method = &cmd_compress;
    node_0x4030.value = 115; /* s */
    node_0x4030.child = &node_0x4050;
    node_0x4010.value = 101; /* e */
    node_0x4010.child = &node_0x4030;
    node_0x3ff0.value = 114; /* r */
    node_0x3ff0.child = &node_0x4010;
    node_0x3fd0.value = 112; /* p */
    node_0x3fd0.child = &node_0x3ff0;
    node_0x3fb0.value = 109; /* m */
    node_0x3fb0.child = &node_0x3fd0;
    node_0x3f90.value = 111; /* o */
    node_0x3f90.sibling = &node_0x4070;
    node_0x3f90.child = &node_0x3fb0;
    node_0x3f70.value = 99; /* c */
    node_0x3f70.method = &cmd_cur_sec;
    node_0x3f50.value = 101; /* e */
    node_0x3f50.child = &node_0x3f70;
    node_0x3f30.value = 115; /* s */
    node_0x3f30.child = &node_0x3f50;
    node_0x3f10.value = 95; /* _ */
    node_0x3f10.child = &node_0x3f30;
    node_0x3ef0.value = 114; /* r */
    node_0x3ef0.child = &node_0x3f10;
    node_0x3ed0.value = 117; /* u */
    node_0x3ed0.sibling = &node_0x3f90;
    node_0x3ed0.child = &node_0x3ef0;
    node_0x3eb0.value = 99; /* c */
    node_0x3eb0.child = &node_0x3ed0;
    node_0x3e90.value = 116; /* t */
    node_0x3e90.method = &cmd_get;
    node_0x3e70.value = 101; /* e */
    node_0x3e70.child = &node_0x3e90;
    node_0x3e50.value = 103; /* g */
    node_0x3e50.sibling = &node_0x3eb0;
    node_0x3e50.child = &node_0x3e70;
    node_0x3e30.value = 116; /* t */
    node_0x3e30.method = &cmd_list;
    node_0x3e10.value = 115; /* s */
    node_0x3e10.child = &node_0x3e30;
    node_0x3df0.value = 105; /* i */
    node_0x3df0.child = &node_0x3e10;
    node_0x3dd0.value = 108; /* l */
    node_0x3dd0.sibling = &node_0x3e50;
    node_0x3dd0.child = &node_0x3df0;
    node_0x3db0.value = 99; /* c */
    node_0x3db0.method = &cmd_make_sec;
    node_0x3d90.value = 101; /* e */
    node_0x3d90.child = &node_0x3db0;
    node_0x3d70.value = 115; /* s */
    node_0x3d70.child = &node_0x3d90;
    node_0x3d50.value = 95; /* _ */
    node_0x3d50.child = &node_0x3d70;
    node_0x3d30.value = 101; /* e */
    node_0x3d30.child = &node_0x3d50;
    node_0x3d10.value = 107; /* k */
    node_0x3d10.child = &node_0x3d30;
    node_0x3cf0.value = 97; /* a */
    node_0x3cf0.child = &node_0x3d10;
    node_0x3cd0.value = 109; /* m */
    node_0x3cd0.sibling = &node_0x3dd0;
    node_0x3cd0.child = &node_0x3cf0;
    node_0x3cb0.value = 116; /* t */
    node_0x3cb0.method = &cmd_put;
    node_0x3c90.value = 117; /* u */
    node_0x3c90.child = &node_0x3cb0;
    node_0x3c70.value = 112; /* p */
    node_0x3c70.sibling = &node_0x3cd0;
    node_0x3c70.child = &node_0x3c90;
    node_0x3c50.value = 116; /* t */
    node_0x3c50.method = &cmd_quit;
    node_0x3c30.value = 105; /* i */
    node_0x3c30.child = &node_0x3c50;
    node_0x3c10.value = 117; /* u */
    node_0x3c10.child = &node_0x3c30;
    node_0x3bf0.value = 113; /* q */
    node_0x3bf0.sibling = &node_0x3c70;
    node_0x3bf0.child = &node_0x3c10;
    node_0x3bd0.value = 104; /* h */
    node_0x3bd0.method = &cmd_search;
    node_0x3bb0.value = 99; /* c */
    node_0x3bb0.child = &node_0x3bd0;
    node_0x3b90.value = 114; /* r */
    node_0x3b90.child = &node_0x3bb0;
    node_0x3b70.value = 97; /* a */
    node_0x3b70.child = &node_0x3b90;
    node_0x3b50.value = 101; /* e */
    node_0x3b50.child = &node_0x3b70;
    s.command_list.value = 115; /* s */
    s.command_list.sibling = &node_0x3bf0;
    s.command_list.child = &node_0x3b50;

    register_book(&s, "|", "", "");

    cmd_ch_sec(&s, "|");
    #include "far-include.h"

    return process(&s);
}
