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
#include "cgc_ctype.h"
#include "cgc_stdlib.h"
#include "cgc_stdint.h"
#include "cgc_string.h"

#include "cgc_modem.h"

#define PAGE_LINES 40

typedef struct thread {
    struct thread *next;
    struct message *messages;
    unsigned int id;
    char topic[64];
} thread_t;

typedef struct message {
    struct message *next;
    unsigned int id;
    char topic[64];
    const char *body;
} message_t;

static thread_t *g_threads;
static unsigned int g_next_id = 1000;
static struct {
#define S_MENU 0
#define S_LIST_THREAD 1
#define S_LIST_MESSAGE 2
#define S_POST_WAIT_TOPIC 3
#define S_POST_WAIT_BODY 4
    int state;
    union {
        struct {
            thread_t *next_thread;
            message_t *next_message;
        } list;
        struct {
            thread_t *thread;
            char topic[64];
        } post;
    };
} g_state;

static void send_string(const char *str)
{
#ifdef DEBUG
    fdprintf(STDERR, "%s\n", str);
#endif
    cgc_modem_output((void *)str, cgc_strlen(str));
}

void cgc_bbs_help()
{
    const static char help_text[] = \
        "Available commands:\n" \
        "\t(L)ist [thread-id]\n" \
        "\t\tList all threads, or messages in a thread\n" \
        "\t(P)ost [thread-id]\n" \
        "\t\tPost a new thread, or a reply to a thread\n" \
        "\t(R)ead message-id\n" \
        "\t\tGet message contents\n" \
        "\t(H)elp\n" \
        "\t\tThis screen\n";
    send_string(help_text);
}

void cgc_bbs_menu()
{
    const static char menu_text[] = \
        "(L)ist, (H)elp, (P)ost, (R)ead\n";
    send_string(menu_text);
}

thread_t *cgc_find_thread(int id)
{
    thread_t *t;
    for (t = g_threads; t != NULL; t = t->next)
    {
        if (t->id < id)
            break;

        if (t->id == id)
            return t;
    }

    return NULL;
}

message_t *cgc_find_message(int id)
{
    thread_t *t;
    message_t *m;

    for (t = g_threads; t != NULL; t = t->next)
    {
        for (m = t->messages; m != NULL; m = m->next)
        {
            if (m->id < id)
                break;

            if (m->id == id)
                return m;
        }
    }

    return NULL;
}

void cgc_send_thread(thread_t *t)
{
    char buf[100];
    cgc_sprintf(buf, "%08d - %s\n", t->id, t->topic);
    send_string(buf);
}

void cgc_send_message_brief(message_t *m)
{
    char buf[100];
    cgc_sprintf(buf, "%08d - %s\n", m->id, m->topic);
    send_string(buf);
}

void cgc_send_message(message_t *m)
{
    char buf[100];
    cgc_sprintf(buf, "%08d - %s\n", m->id, m->topic);
    send_string(buf);
    send_string(m->body);
}

void cgc_send_thread_list(thread_t *t)
{
    int i;
    for (i = 0; i < PAGE_LINES && t != NULL; i++, t = t->next)
        cgc_send_thread(t);
    if (t)
    {
        g_state.state = S_LIST_THREAD;
        g_state.list.next_thread = t;
        send_string("(N)ext page, (Q)uit\n");
    }
    else
    {
        g_state.state = S_MENU;
    }
}

void cgc_send_message_list(message_t *t)
{
    int i;
    for (i = 0; i < PAGE_LINES && t != NULL; i++, t = t->next)
        cgc_send_message_brief(t);
    if (t)
    {
        g_state.state = S_LIST_MESSAGE;
        g_state.list.next_message = t;
        send_string("(N)ext page, (Q)uit\n");
    }
    else
    {
        g_state.state = S_MENU;
    }
}

void cgc_do_list(const char *str)
{
    if (str[1] == ' ')
    {
        int id = cgc_strtol(&str[2], NULL, 10);
        thread_t *t = cgc_find_thread(id);
        if (t)
            cgc_send_message_list(t->messages);
        else
            send_string("Thread ID not found.\n");
    }
    else
    {
        cgc_send_thread_list(g_threads);
    }
}

void cgc_do_post(const char *str)
{
    thread_t *t = NULL;
    if (str[1] == ' ')
    {
        int id = cgc_strtol(&str[2], NULL, 10);
        t = cgc_find_thread(id);
        if (t == NULL)
        {
            send_string("Thread ID not found.\n");
            return;
        }
    }

    send_string("Subject?\n");
    g_state.state = S_POST_WAIT_TOPIC;
    g_state.post.thread = t;
}

void cgc_do_read(const char *str)
{
    if (str[1] != ' ')
    {
        send_string("Missing required argument.\n");
        return;
    }

    int id = cgc_strtol(&str[2], NULL, 10);
    message_t *m = cgc_find_message(id);
    if (m)
        cgc_send_message(m);
    else
        send_string("Message ID not found.\n");
}

void cgc_handle_post(const char *str)
{
    if (g_state.state == S_POST_WAIT_TOPIC)
    {
        cgc_strncpy(g_state.post.topic, str, sizeof(g_state.post.topic)-1);
        g_state.post.topic[sizeof(g_state.post.topic)-1] = 0;

        send_string("Body?\n");
        g_state.state = S_POST_WAIT_BODY;
    }
    else if (g_state.state == S_POST_WAIT_BODY)
    {
        thread_t *t = g_state.post.thread;
        if (t == NULL)
        {
            t = cgc_malloc(sizeof(thread_t));
            if (t == NULL)
                goto fail;

            cgc_strcpy(t->topic, g_state.post.topic);
            t->id = g_next_id++;
            t->next = g_threads;
            t->messages = NULL;
            g_threads = t;
        }

        message_t *m = cgc_malloc(sizeof(message_t));
        if (m)
        {
            m->id = g_next_id++;
            cgc_strcpy(m->topic, g_state.post.topic);
            m->body = cgc_strdup(str);
            if (m->body == NULL)
                goto fail;

            m->next = t->messages;
            t->messages = m;
        }

fail:
        g_state.state = S_MENU;
    }
}

void cgc_handle_list(const char *str)
{
    if (cgc_tolower(str[0]) == 'q')
    {
        g_state.state = S_MENU;
    }
    else if (cgc_tolower(str[0]) == 'n')
    {
        if (g_state.state == S_LIST_THREAD)
            cgc_send_thread_list(g_state.list.next_thread);
        else
            cgc_send_message_list(g_state.list.next_message);
    }
    else
    {
        send_string("Bad input.\n");
    }
}

void cgc_handle_menu(const char *str)
{
    int cmd = str[0];

    /* either nothing comes after command or a space delimiter */
    if (str[1] != 0 && str[1] != ' ')
        cmd = 0;

    switch (cmd)
    {
    case 'H':
    case 'h':
    case '?':
        cgc_bbs_help();
        break;
    case 'L':
    case 'l':
        cgc_do_list(str);
        break;
    case 'P':
    case 'p':
        cgc_do_post(str);
        break;
    case 'R':
    case 'r':
        cgc_do_read(str);
        break;
    case 'Q':
    case 'q':
        cgc_exit(0);
        break;
    default:
        send_string("Bad input. Unknown command.\n");
        break;
    }
}

void cgc_bbs_rx(const uint8_t *data, cgc_size_t count)
{
    char str[101];

#ifdef PATCHED
    if (count > sizeof(str)-1)
        count = sizeof(str)-1;
#endif

    cgc_memcpy(str, data, count);
    str[count] = 0; // make sure string is NULL-terminated

    if (cgc_strlen(str) == 0)
        return;

#ifdef DEBUG
    fdprintf(STDERR, "%s\n", str);
#endif

    if (g_state.state == S_MENU)
    {
        cgc_handle_menu(str);
    }
    else if (g_state.state == S_LIST_THREAD || g_state.state == S_LIST_MESSAGE)
    {
        cgc_handle_list(str);
    }
    else if (g_state.state == S_POST_WAIT_TOPIC || g_state.state == S_POST_WAIT_BODY)
    {
        cgc_handle_post(str);
    }

    if (g_state.state == S_MENU)
        cgc_bbs_menu();
}

int main(int cgc_argc, char *cgc_argv[])
{
    cgc_modem_init();

    cgc_bbs_menu();
    cgc_modem_loop(cgc_bbs_rx);
    return 0;
}

