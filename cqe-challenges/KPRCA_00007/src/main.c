/*
 * Author: Andrew Wesie <andrew.wesie@kapricasecurity.com>
 *
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

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

//#define DEBUG
//#define LINEECHO

#define PROMPT "> "
#define ENABLE_PROMPT "$ "
#define ENABLE_PASSWORD "racoiaws"
#define INVALID_ASN 0
#define MAX_ROUTERS 0xFFFF
#define MAX_ROUTE_ALLOCATIONS 1024

typedef struct {
    unsigned int asn;
    char name[256];
    unsigned int ip;
} router_t;

typedef struct route {
    struct route *left;
    struct route *right;
    uint32_t ip;
    uint16_t asn;
    uint8_t reserved;
    uint8_t flag1 : 1;
    uint8_t drop : 1;
    uint8_t free : 1;
    uint8_t length : 5;
} route_t;

typedef struct {
    unsigned int free_head;
    unsigned int reserved1;
    unsigned int reserved2;
    unsigned int reserved3;

    route_t routes[4095];
} route_mem_t;

char g_buffer[1024];
size_t g_buffer_bytes;
unsigned int g_num_routers;
router_t g_routers[MAX_ROUTERS];
route_t g_default_route;
int g_enable;
int g_route_mem_length;
route_mem_t **g_route_memory;

static void print(const char *s)
{
    size_t bytes;
    transmit(STDOUT, s, strlen(s), &bytes);
}

static char *readline(const char *prompt)
{
    size_t idx = 0, bytes;
    print(prompt);
    while (1)
    {
        int status = receive(STDIN, &g_buffer[idx], 1, &bytes);
        if (status != 0 || bytes != 1)
            return NULL;
        if (g_buffer[idx] == '\n')
            break;
        if (++idx == sizeof(g_buffer))
            return NULL;
    }
    g_buffer[idx] = 0;
#ifdef LINEECHO
    print(g_buffer);
    print("\n");
#endif
    return g_buffer;
}

static int parse_ip(char *line, unsigned int *out)
{
    char *s1, *s2, *s3, *s4;
    if ((s1 = strsep(&line, ".")) == NULL)
        return 0;
    if ((s2 = strsep(&line, ".")) == NULL)
        return 0;
    if ((s3 = strsep(&line, ".")) == NULL)
        return 0;
    if ((s4 = strsep(&line, ".")) == NULL)
        return 0;
    unsigned int i1, i2, i3, i4;
    if ((i1 = strtoul(s1, NULL, 10)) >= 256)
        return 0;
    if ((i2 = strtoul(s2, NULL, 10)) >= 256)
        return 0;
    if ((i3 = strtoul(s3, NULL, 10)) >= 256)
        return 0;
    if ((i4 = strtoul(s4, NULL, 10)) >= 256)
        return 0;
    *out = (i1 << 24) | (i2 << 16) | (i3 << 8) | i4;
    return 1;
}

static int valid_router(router_t *router)
{
    return router->asn != INVALID_ASN && router->asn <= MAX_ROUTERS;
}

static router_t *get_router(unsigned int asn)
{
    return &g_routers[asn-1];
}

static int mask_to_length(unsigned int mask)
{
    int length;
    if (mask == 0)
        return 0;
    if (mask == 0xFFFFFFFF)
        return 32;
    for (length = 0; length <= 32; length++)
        if (0xFFFFFFFF << (32 - length) == mask)
            break;
    return length;
}

static unsigned route_mask(route_t *route)
{
    if (route == &g_default_route)
        return 0;
    return 0xFFFFFFFF << (31 - route->length);
}

static unsigned route_bit(route_t *route)
{
    if (route == &g_default_route)
        return 1 << 31;
    else
        return 1 << (31 - route->length - 1);
}

static route_t *route_child(route_t *parent, uint32_t ip)
{
    return (ip & route_bit(parent)) == 0 ? parent->left : parent->right;
}

#ifdef DEBUG
static void print_route(route_t *route, int level)
{
    unsigned int mask = route_mask(route);
    printf(" [%d] %08x %08x %d\n", level,
        route->ip,
        mask,
        route->asn);

}

static void print_routes(route_t *root, int level)
{
    print_route(root, level);
    if (root->left)
        print_routes(root->left, level+1);
    if (root->right)
        print_routes(root->right, level+1);
}
#endif

static route_t *lookup_route(uint32_t ip, unsigned int length, route_t **parent)
{
    if (length == 0)
    {
        if (ip == 0)
        {
            if (parent) *parent = NULL;
            return &g_default_route;
        }
        else
        {
            return NULL;
        }
    }

    route_t *p = &g_default_route, *route;
    while ((route = route_child(p, ip)) != NULL)
    {
        uint32_t mask = route_mask(route);
        if (route->ip == ip && route->length == length - 1)
        {
            if (parent) *parent = p;
            return route;
        }
        if ((route->ip & mask) != (ip & mask))
            break;
        if (route->length == 31)
            break;
        p = route;
    }

    return NULL;
}

static void prompt_edit_router(router_t *router)
{
    char *line;
    printf("AS %d\n", router->asn);
    printf(" Name: %s\n", router->name);
    printf(" IP: %d.%d.%d.%d\n", router->ip >> 24, 
        (router->ip >> 16) & 0xff,
        (router->ip >> 8) & 0xff,
        (router->ip >> 0) & 0xff);

    line = readline("Modify name? ");
    if (line && strcmp(line, "y") == 0)
    {
        line = readline("New name? ");
        if (line)
        {
            strncpy(router->name, line, sizeof(router->name));
            router->name[sizeof(router->name)-1] = 0;
        }
    }
    line = readline("Modify IP? ");
    if (line && strcmp(line, "y") == 0)
    {
        unsigned int ip;
        line = readline("New IP? ");
        if (line && parse_ip(line, &ip))
        {
            router->ip = ip;
        }
    }
}

static route_t *allocate_route()
{
    int i;
    route_mem_t *avail_mem = NULL;
    for (i = 0; i < g_route_mem_length; i++)
    {
        route_mem_t *mem = g_route_memory[i];
        if (mem == NULL)
            continue;
        if (mem->free_head != 0)
        {
            avail_mem = mem;
            break;
        }
    }
    if (avail_mem == NULL)
    {
        if (g_route_mem_length == MAX_ROUTE_ALLOCATIONS)
            return NULL;
        if (allocate(sizeof(route_mem_t), 0, (void **)&avail_mem) != 0)
            return NULL;
        avail_mem->free_head = 1;
        for (i = 1; i <= sizeof(avail_mem->routes) / sizeof(avail_mem->routes[0]); i++)
        {
            route_t *route = &avail_mem->routes[i - 1];
            route->free = 1;
            if (i == sizeof(avail_mem->routes) / sizeof(avail_mem->routes[0]))
                route->ip = 0;
            else
                route->ip = i + 1;
        }
        g_route_memory[g_route_mem_length++] = avail_mem;
    }
    route_t *route = &avail_mem->routes[avail_mem->free_head - 1];
    avail_mem->free_head = route->ip;
    memset(route, 0, sizeof(route_t));
    return route;
}

static void free_route(route_t *route)
{
    int i;
    for (i = 0; i < g_route_mem_length; i++)
    {
        route_mem_t *mem = g_route_memory[i];
        if (mem == NULL)
            continue;
        if ((intptr_t)route - (intptr_t)mem < sizeof(route_mem_t))
        {
            route->free = 1;
            route->ip = mem->free_head;
            mem->free_head = ((intptr_t)route - (intptr_t)mem) / sizeof(route_t);
            return;
        }
    }
    exit(9);
}

static void delete_route(route_t *route, route_t *parent)
{
    if (parent == NULL)
        if (lookup_route(route->ip, route->length + 1, &parent) == NULL)
            exit(1);
    if (parent == NULL)
        exit(2);

    route_t *sibling, **slot;
    if (parent->left == route)
    {
        slot = &parent->left;
        sibling = parent->right;
    }
    else if (parent->right == route)
    {
        slot = &parent->right;
        sibling = parent->left;
    }
    else
    {
        exit(3);
    }

    route->asn = INVALID_ASN;
    route->drop = 0;

    if (route->left && route->right)
    {
        // keep this node around
    }
    else if (route->left)
    {
        // replace with left child
        *slot = route->left;
        free_route(route);
    }
    else if (route->right)
    {
        // replace with right child
        *slot = route->right;
        free_route(route);
    }
    else if (parent != &g_default_route && parent->asn == INVALID_ASN && !parent->drop && sibling)
    {
        route_t *pp;
        if (lookup_route(parent->ip, parent->length + 1, &pp) != NULL && pp != NULL)
        {
            // parent is a NOOP
            // replace parent with the remaining sibling
            if (pp->left == parent)
                pp->left = sibling;
            else
                pp->right = sibling;
            free_route(parent);
            free_route(route);
        }
    }
    else
    {
        // parent has a purpose, keep it around
        *slot = NULL;
        free_route(route);
    }
}

static void cmd_add_route(char *line)
{
    unsigned int ip, mask, asn;
    char *word = strsep(&line, " ");
    if (word == NULL || !parse_ip(word, &ip))
        goto bad_arguments;
    word = strsep(&line, " ");
    if (word == NULL || !parse_ip(word, &mask))
        goto bad_arguments;
    word = strsep(&line, " ");
    if (word == NULL)
        goto bad_arguments;
    asn = strtoul(word, NULL, 10);
    if (asn > MAX_ROUTERS)
        goto bad_arguments;

    if (asn != INVALID_ASN && !valid_router(get_router(asn)))
        goto bad_arguments;

    int length = mask_to_length(mask);
    if (length > 32)
        goto bad_arguments;

    if ((ip & ~mask) != 0)
        goto bad_arguments;

    if (length == 0)
    {
        // modify default route
        g_default_route.asn = asn;
        return;
    }
    length--;

    route_t *next, *route, *parent = &g_default_route;
    while (1)
    {
        int bit = route_bit(parent);
        next = (ip & bit) == 0 ? parent->left : parent->right;
        if (next == NULL)
        {
            route = allocate_route();
            if (route == NULL)
            {
                print("OUT OF MEMORY\n");
                return;
            }
            if ((ip & bit) == 0)
                parent->left = route;
            else
                parent->right = route;
            break;
        }

        uint32_t mask = route_mask(next);
        if ((next->ip & mask) != (ip & mask) || next->length > length)
        {
            mask = 0xFFFFFFFF << (31 - length);
            if ((next->ip & mask) == (ip & mask))
            {
                // create a new internal node
                route = allocate_route();
                if (route == NULL)
                {
                    print("OUT OF MEMORY\n");
                    return;
                }
                if ((ip & bit) == 0)
                    parent->left = route;
                else
                    parent->right = route;
                bit = 1 << (31 - length - 1);
                if ((next->ip & bit) == 0)
                    route->left = next;
                else
                    route->right = next;
            }
            else
            {
                // create a new internal node
                // and a new leaf node
                route = allocate_route();
                if (route == NULL)
                {
                    print("OUT OF MEMORY\n");
                    return;
                }

                if ((ip & bit) == 0)
                    parent->left = route;
                else
                    parent->right = route;
                parent = route;

                route = allocate_route();
                if (route == NULL)
                {
                    print("OUT OF MEMORY\n");
                    return;
                }

                unsigned int diff = ip ^ next->ip;
                for (bit = 31; bit >= 0; bit--)
                    if ((1 << bit) & diff)
                        break;

                bit++;

                parent->length = 31 - bit;
                mask = 0xFFFFFFFF << bit;
                parent->ip = ip & mask;
                if (ip & (1 << (bit-1)))
                {
                    parent->left = next;
                    parent->right = route;
                }
                else
                {
                    parent->left = route;
                    parent->right = next;
                }
            }
            break;
        }
        else
        {
            if (next->length == length)
            {
                // edit next
                route = next;
                break;
            }
            else
            {
                parent = next;
            }
        }
    }

    route->ip = ip;
    route->asn = asn;
    route->length = length;

#ifdef DEBUG
    print_routes(&g_default_route, 0);
#endif

    return;

bad_arguments:
    print("BAD ARGUMENTS\n");
    return;
}

static void cmd_delete_route(char *line)
{
    unsigned int ip, mask;
    char *word = strsep(&line, " ");
    if (word == NULL || !parse_ip(word, &ip))
        goto bad_arguments;
    word = strsep(&line, " ");
    if (word == NULL || !parse_ip(word, &mask))
        goto bad_arguments;

    int length = mask_to_length(mask);
    if (length > 32)
        goto bad_arguments;

    if (length == 0)
    {
        if (ip == 0)
            g_default_route.asn = INVALID_ASN;
        else
            print("ROUTE NOT FOUND\n");
        return;
    }

    route_t *parent, *route;
    route = lookup_route(ip, length, &parent);
    if (route && (route->asn != INVALID_ASN || route->drop))
        delete_route(route, parent);
    else
        print("ROUTE NOT FOUND\n");
    return;

bad_arguments:
    print("BAD ARGUMENTS\n");
    return;
}

static void cmd_query_route(char *line)
{
    unsigned int ip;
    char *word = strsep(&line, " ");
    if (word == NULL || !parse_ip(word, &ip))
        goto bad_arguments;

    unsigned int next_hop = INVALID_ASN;
    route_t *route = &g_default_route;
    while (route != NULL)
    {
        uint32_t mask;
        if (route == &g_default_route)
            mask = 0;
        else
            mask = 0xFFFFFFFF << (31 - route->length);
        if ((route->ip & mask) != (ip & mask))
            break;
        if (route->asn != INVALID_ASN || route->drop)
            next_hop = route->asn;
        if (route->length == 31)
            break;
        int bit;
        if (route == &g_default_route)
            bit = 1 << 31;
        else
            bit = 1 << (30 - route->length);     
        route = (ip & bit) == 0 ? route->left : route->right;
    }

    printf("Next hop for %d.%d.%d.%d is ", ip >> 24,
        (ip >> 16) & 0xff,
        (ip >> 8) & 0xff,
        (ip >> 0) & 0xff);
    if (next_hop == INVALID_ASN)
    {
        printf("BLACKHOLE.\n");
    }
    else
    {
        router_t *router = get_router(next_hop);
        printf("%d.%d.%d.%d, AS %d (%s)\n", router->ip >> 24,
            (router->ip >> 16) & 0xff,
            (router->ip >> 8) & 0xff,
            (router->ip >> 0) & 0xff,
            router->asn, router->name);
    }
    return;

bad_arguments:
    print("BAD ARGUMENTS\n");
    return;
}

static void cmd_add_router(char *line)
{
    char *word = strsep(&line, " ");
    if (word == NULL)
        goto bad_arguments;
    
    unsigned int asn = strtoul(word, NULL, 10);
    if (asn == INVALID_ASN || asn > MAX_ROUTERS)
        goto bad_arguments;

    router_t *router = get_router(asn);
    if (valid_router(router))
        goto bad_arguments;

    memset(router, 0, sizeof(router_t));
    router->asn = asn;
    prompt_edit_router(router);
    return;

bad_arguments:
    print("BAD ARGUMENTS\n");
    return;
}

static void cmd_delete_router(char *line)
{
    char *word = strsep(&line, " ");
    if (word == NULL)
        goto bad_arguments;
    
    unsigned int asn = strtoul(word, NULL, 10);
    if (asn == INVALID_ASN || asn > MAX_ROUTERS)
        goto bad_arguments;

    router_t *router = get_router(asn);
    if (!valid_router(router))
        goto bad_arguments;

    // delete all routes with this router
    int i, j;
    for (i = 0; i < g_route_mem_length; i++)
    {
        route_mem_t *mem = g_route_memory[i];
        for (j = 0; j < sizeof(mem->routes)/sizeof(mem->routes[0]); j++)
        {
            route_t *route = &mem->routes[j];
            if (!route->free && route->asn == asn)
            {
                delete_route(route, NULL);
            }
        }
    }
    if (g_default_route.asn == asn)
    {
        g_default_route.asn = INVALID_ASN;
        g_default_route.drop = 0;
    }

    router->asn = INVALID_ASN;
    return;

bad_arguments:
    print("BAD ARGUMENTS\n");
    return;
}

static void cmd_edit_router(char *line)
{
    char *word = strsep(&line, " ");
    if (word == NULL)
        goto bad_arguments;
    
    unsigned int asn = strtoul(word, NULL, 10);
#ifdef PATCHED
    if (asn == INVALID_ASN || asn > MAX_ROUTERS)
        goto bad_arguments;
#else
    if (asn > MAX_ROUTERS)
        goto bad_arguments;
#endif

    router_t *router = get_router(asn);
    if (!valid_router(router))
        goto bad_arguments;

    prompt_edit_router(router);
    return;

bad_arguments:
    print("BAD ARGUMENTS\n");
    return;
}

static void cmd_list_router(char *line)
{
    int i;
    for (i = 1; i <= MAX_ROUTERS; i++)
    {
        router_t *router = get_router(i);
        if (!valid_router(router))
            continue;
        printf("AS %d\n", router->asn);
        printf(" Name: %s\n", router->name);
        printf(" IP: %d.%d.%d.%d\n", router->ip >> 24, 
            (router->ip >> 16) & 0xff,
            (router->ip >> 8) & 0xff,
            (router->ip >> 0) & 0xff);
    }
}

static void cmd_enable_mode(char *line)
{
    char *word = strsep(&line, " ");
    if (word == NULL)
        print("BAD ARGUMENTS\n");
    else if (strcmp(word, ENABLE_PASSWORD) == 0)
        g_enable = 1;
    else
        print("BAD PASSWORD\n");
}

int main()
{
    if (allocate(sizeof(g_route_memory[0])*MAX_ROUTE_ALLOCATIONS, 0, (void*)&g_route_memory) != 0)
        return 0;
    while (1)
    {
        char *line = readline(g_enable ? ENABLE_PROMPT : PROMPT);
        if (line == NULL)
            break;
        char *word = strsep(&line, " ");
        if (g_enable == 0)
        {
            if (strcmp(word, "add") == 0)
                cmd_add_route(line);
            if (strcmp(word, "delete") == 0)
                cmd_delete_route(line);
            if (strcmp(word, "query") == 0)
                cmd_query_route(line);
            if (strcmp(word, "enable") == 0)
                cmd_enable_mode(line);
            if (strcmp(word, "quit") == 0)
                break;
        }
        else
        {
            if (strcmp(word, "add") == 0)
                cmd_add_router(line);
            if (strcmp(word, "delete") == 0)
                cmd_delete_router(line);
            if (strcmp(word, "edit") == 0)
                cmd_edit_router(line);
            if (strcmp(word, "list") == 0)
                cmd_list_router(line);
            if (strcmp(word, "quit") == 0)
                g_enable = 0;
        }
    }
    print("GOOD-BYE\n");
    return 0;
}
