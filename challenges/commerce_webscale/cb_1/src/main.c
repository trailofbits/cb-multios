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
#include "cgc_stdlib.h"
#include "cgc_string.h"
#include "cgc_db_client.h"

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

void cgc_read_until(int fd, char * buf, cgc_size_t length, char end)
{
    cgc_size_t i;
    for (i = 0; i < length; i++)
    {
        cgc_size_t bytes;
        if (cgc_receive(fd, &buf[i], 1, &bytes) != 0 || bytes != 1)
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

void cgc_list()
{
    char buf[4096];
    key k;
    result res;
    cgc_size_t bytes;

    buf[0] = 0;
    k.data.count = 0;
    res = cgc_db_next(k);
    while (res.status == SUCCESS)
    {
#ifdef PATCHED
        if (cgc_strlen(buf) + cgc_strlen((char*)res.rec.data->k.data.data) + 30 > sizeof(buf))
            break;
#endif
        item_details *d = (item_details *)res.rec.data->data.data;
        cgc_sprintf(buf, "%s%s (Price: %d.%02d, Count: %d)\n", buf, res.rec.data->k.data.data,
            (int)(d->price / 100), abs(d->price % 100), d->count);
        res = cgc_db_next(res.rec.data->k);
    }
    cgc_transmit(STDOUT, buf, cgc_strlen(buf), &bytes);
}

void cgc_buy()
{
    char name[200];
    key k;
    result res;

    cgc_read_until(STDIN, name, 200, '\n');
    k.data.count = cgc_strlen(name) + 1;
    k.data.data = (opaque *)name;

    res = cgc_db_lookup(k);
    if (res.status == SUCCESS)
    {
        item_details *d = (item_details *)res.rec.data->data.data;
        if (d->count < 1)
        {
            cgc_printf("Not enought items\n");
        }
        else
        {
            d->count--;
            if (d->count == 0)
                cgc_db_delete(k);
            else
                cgc_db_insert(*res.rec.data);
        }
    }
    else
    {
        cgc_printf("Item not found\n");
    }
}

void cgc_sell()
{
    char *name;
    char tmp[50];
    cgc_size_t bytes;
    record rec;
    item_details d;

    name = cgc_malloc(200);
    cgc_read_until(STDIN, name, 200, '\n');
    cgc_read_until(STDIN, tmp, sizeof(tmp), '\n');
    d.price = cgc_strtol(tmp, NULL, 10);
    cgc_read_until(STDIN, tmp, sizeof(tmp), '\n');
    d.count = cgc_strtoul(tmp, NULL, 10);

    rec.k.data.count = cgc_strlen(name) + 1;
    rec.k.data.data = (opaque *)name;
    rec.data.count = sizeof(d);
    rec.data.data = (opaque *)&d;
    cgc_db_insert(rec);
}

char cgc_menu()
{
    char choice;
    cgc_size_t bytes;

    cgc_printf("\nPlease make a selection:\n\ta) List products\n\tb) Buy a product\n\tc) Sell a product\n");

    if (cgc_receive(STDIN, &choice, 1, &bytes) != 0 || bytes != 1)
        return 0;

    return choice;
}

void cgc_init_db()
{
    int i;
    record rec;
    cgc_memset(&rec, 0, sizeof(rec));

    for (i = 0; i < sizeof(g_items) / sizeof(g_items[0]); i++)
    {
        rec.k.data.count = cgc_strlen(g_items[i].name) + 1;
        rec.k.data.data = (opaque *)g_items[i].name;
        rec.data.count = sizeof(g_items[i].details);
        rec.data.data = (opaque *)&g_items[i].details;
        cgc_db_insert(rec);
    }
}

int main(int cgc_argc, char *cgc_argv[])
{
    cgc_database_init(4, 5);
    cgc_init_db();

    cgc_printf("Welcome to eCommerce v0.1\n");

    while (1)
    {
        char choice = cgc_menu();
        if (choice == 0)
            break;
        else if (choice == 'a')
            cgc_list();
        else if (choice == 'b')
            cgc_buy();
        else if (choice == 'c')
            cgc_sell();
        else
            cgc_printf("Invalid selection\n");
    }

    cgc_database_close();
    return 0;
}
