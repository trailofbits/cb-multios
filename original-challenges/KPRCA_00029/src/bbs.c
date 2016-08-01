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
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "modem.h"

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
    modem_output((void *)str, strlen(str));
}

void bbs_help()
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

void bbs_menu()
{
    const static char menu_text[] = \
        "(L)ist, (H)elp, (P)ost, (R)ead\n";
    send_string(menu_text);
}

thread_t *find_thread(int id)
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

message_t *find_message(int id)
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

void send_thread(thread_t *t)
{
    char buf[100];
    sprintf(buf, "%08d - %s\n", t->id, t->topic);
    send_string(buf);
}

void send_message_brief(message_t *m)
{
    char buf[100];
    sprintf(buf, "%08d - %s\n", m->id, m->topic);
    send_string(buf);
}

void send_message(message_t *m)
{
    char buf[100];
    sprintf(buf, "%08d - %s\n", m->id, m->topic);
    send_string(buf);
    send_string(m->body);
}

void send_thread_list(thread_t *t)
{
    int i;
    for (i = 0; i < PAGE_LINES && t != NULL; i++, t = t->next)
        send_thread(t);
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

void send_message_list(message_t *t)
{
    int i;
    for (i = 0; i < PAGE_LINES && t != NULL; i++, t = t->next)
        send_message_brief(t);
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

void do_list(const char *str)
{
    if (str[1] == ' ')
    {
        int id = strtol(&str[2], NULL, 10);
        thread_t *t = find_thread(id);
        if (t)
            send_message_list(t->messages);
        else
            send_string("Thread ID not found.\n");
    }
    else
    {
        send_thread_list(g_threads);
    }
}

void do_post(const char *str)
{
    thread_t *t = NULL;
    if (str[1] == ' ')
    {
        int id = strtol(&str[2], NULL, 10);
        t = find_thread(id);
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

void do_read(const char *str)
{
    if (str[1] != ' ')
    {
        send_string("Missing required argument.\n");
        return;
    }

    int id = strtol(&str[2], NULL, 10);
    message_t *m = find_message(id);
    if (m)
        send_message(m);
    else
        send_string("Message ID not found.\n");
}

void handle_post(const char *str)
{
    if (g_state.state == S_POST_WAIT_TOPIC)
    {
        strncpy(g_state.post.topic, str, sizeof(g_state.post.topic)-1);
        g_state.post.topic[sizeof(g_state.post.topic)-1] = 0;

        send_string("Body?\n");
        g_state.state = S_POST_WAIT_BODY;
    }
    else if (g_state.state == S_POST_WAIT_BODY)
    {
        thread_t *t = g_state.post.thread;
        if (t == NULL)
        {
            t = malloc(sizeof(thread_t));
            if (t == NULL)
                goto fail;

            strcpy(t->topic, g_state.post.topic);
            t->id = g_next_id++;
            t->next = g_threads;
            t->messages = NULL;
            g_threads = t;
        }

        message_t *m = malloc(sizeof(message_t));
        if (m)
        {
            m->id = g_next_id++;
            strcpy(m->topic, g_state.post.topic);
            m->body = strdup(str);
            if (m->body == NULL)
                goto fail;

            m->next = t->messages;
            t->messages = m;
        }

fail:
        g_state.state = S_MENU;
    }
}

void handle_list(const char *str)
{
    if (tolower(str[0]) == 'q')
    {
        g_state.state = S_MENU;
    }
    else if (tolower(str[0]) == 'n')
    {
        if (g_state.state == S_LIST_THREAD)
            send_thread_list(g_state.list.next_thread);
        else
            send_message_list(g_state.list.next_message);
    }
    else
    {
        send_string("Bad input.\n");
    }
}

void handle_menu(const char *str)
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
        bbs_help();
        break;
    case 'L':
    case 'l':
        do_list(str);
        break;
    case 'P':
    case 'p':
        do_post(str);
        break;
    case 'R':
    case 'r':
        do_read(str);
        break;
    case 'Q':
    case 'q':
        exit(0);
        break;
    default:
        send_string("Bad input. Unknown command.\n");
        break;
    }
}

void bbs_rx(const uint8_t *data, size_t count)
{
    char str[101];

#ifdef PATCHED
    if (count > sizeof(str)-1)
        count = sizeof(str)-1;
#endif

    memcpy(str, data, count);
    str[count] = 0; // make sure string is NULL-terminated

    if (strlen(str) == 0)
        return;

#ifdef DEBUG
    fdprintf(STDERR, "%s\n", str);
#endif

    if (g_state.state == S_MENU)
    {
        handle_menu(str);
    }
    else if (g_state.state == S_LIST_THREAD || g_state.state == S_LIST_MESSAGE)
    {
        handle_list(str);
    }
    else if (g_state.state == S_POST_WAIT_TOPIC || g_state.state == S_POST_WAIT_BODY)
    {
        handle_post(str);
    }

    if (g_state.state == S_MENU)
        bbs_menu();
}

int main()
{
    modem_init();

    bbs_menu();
    modem_loop(bbs_rx);
    return 0;
}

