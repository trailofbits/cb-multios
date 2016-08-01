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
#include <stdlib.h>
#include <string.h>
#include "db_client.h"

typedef struct {
    unsigned int count;
    int price;
} item_details;

static struct {
    char *name;
    item_details details;
} g_items[] = {
    {"Apple", { 10, 110 }},
    {"Banana", { 25, 30 }},
    {"Orange", { 10, 120 }},
    {"Computer", { 1, 100000 }}
};

void read_until(int fd, char * buf, size_t length, char end)
{
    size_t i;
    for (i = 0; i < length; i++)
    {
        size_t bytes;
        if (receive(fd, &buf[i], 1, &bytes) != 0 || bytes != 1)
            break;
        if (buf[i] == end)
            break;
    }
    buf[i] = 0;
}

static int abs(int v)
{
    if (v < 0)
        return -v;
    return v;
}

void list()
{
    char buf[4096];
    key k;
    result res;
    size_t bytes;
    
    buf[0] = 0;
    k.data.count = 0;
    res = db_next(k);
    while (res.status == SUCCESS)
    {
#ifdef PATCHED
        if (strlen(buf) + strlen((char*)res.rec.data->k.data.data) + 30 > sizeof(buf))
            break;
#endif
        item_details *d = (item_details *)res.rec.data->data.data;
        sprintf(buf, "%s%s (Price: %d.%02d, Count: %d)\n", buf, res.rec.data->k.data.data,
            (int)(d->price / 100), abs(d->price % 100), d->count);
        res = db_next(res.rec.data->k);
    }
    transmit(STDOUT, buf, strlen(buf), &bytes);
}

void buy()
{
    char name[200];
    key k;
    result res;

    read_until(STDIN, name, 200, '\n');
    k.data.count = strlen(name) + 1;
    k.data.data = (opaque *)name;

    res = db_lookup(k);
    if (res.status == SUCCESS)
    {
        item_details *d = (item_details *)res.rec.data->data.data;
        if (d->count < 1)
        {
            printf("Not enought items\n");
        }
        else
        {
            d->count--;
            if (d->count == 0)
                db_delete(k);
            else
                db_insert(*res.rec.data);
        }
    }
    else
    {
        printf("Item not found\n");
    }
}

void sell()
{
    char *name;
    char tmp[50];
    size_t bytes;
    record rec;
    item_details d;

    name = malloc(200);
    read_until(STDIN, name, 200, '\n');
    read_until(STDIN, tmp, sizeof(tmp), '\n');
    d.price = strtol(tmp, NULL, 10);
    read_until(STDIN, tmp, sizeof(tmp), '\n');
    d.count = strtoul(tmp, NULL, 10);
    
    rec.k.data.count = strlen(name) + 1;
    rec.k.data.data = (opaque *)name;
    rec.data.count = sizeof(d);
    rec.data.data = (opaque *)&d;
    db_insert(rec);
}

char menu()
{
    char choice;
    size_t bytes;

    printf("\nPlease make a selection:\n\ta) List products\n\tb) Buy a product\n\tc) Sell a product\n");

    if (receive(STDIN, &choice, 1, &bytes) != 0 || bytes != 1)
        return 0;

    return choice;
}

void init_db()
{
    int i;
    record rec;
    memset(&rec, 0, sizeof(rec));

    for (i = 0; i < sizeof(g_items) / sizeof(g_items[0]); i++)
    {
        rec.k.data.count = strlen(g_items[i].name) + 1;
        rec.k.data.data = (opaque *)g_items[i].name;
        rec.data.count = sizeof(g_items[i].details);
        rec.data.data = (opaque *)&g_items[i].details;
        db_insert(rec);
    }
}

int main()
{
    database_init(3);
    init_db();

    printf("Welcome to eCommerce v0.1\n");

    while (1)
    {
        char choice = menu();
        if (choice == 0)
            break;
        else if (choice == 'a')
            list();
        else if (choice == 'b')
            buy();
        else if (choice == 'c')
            sell();
        else
            printf("Invalid selection\n");
    }

    database_close();
    return 0;
}
