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

#include "libcgc.h"
#include "cgc_libc.h"
#include "cgc_viewscript.h"

/*
 * View scripts are incredibly simple, so much so that we don't have any kind of a simple parser.
 * There are four commands:
 * new <type> <name> <type args>
 * get <var> <arg>
 * set <var> <descriptor> <new val>
 * delete <var>
 *
 * Commands are newline delimeted.
 */

#define NEWTOK "new"
#define GETTOK "get"
#define SETTOK "set"
#define DELTOK "del"

#define NUM "num"
#define ARR "arr"
#define VIEW "view"

#define ERRSHORT 1
#define ERRBADFMT 2
#define ERRNOARG 3
#define ERRNOSUCHTYPE 4
#define ERRNOSUCHCMD 5
#define ERRNOTYPE 6
#define ERRNONAME 7
#define ERRALREADYEXISTS 8
#define ERRNOSUCHVAR 9
#define ERRNOMEM 10
#define ERRTOOBIG 11
#define ERRWRONGTYPE 12
#define ERRINVALIDIDX 13

//max array size in ints
#define MAXARRSIZE 2*1024*1024
#define MAXSCRIPTSIZE 2*1024*1024

typedef enum {NUMTYPE, ARRTYPE, VIEWTYPE} varenum;

typedef struct viewtype {
    char *name;
    cgc_size_t size;
    int sign;
} viewtype_t;

static viewtype_t viewtypes[] = { 
                            {"int", sizeof(int), 1},
                            {"uint", sizeof(unsigned int), 0},
                            {"short", sizeof(short), 1},
                            {"ushort", sizeof(unsigned short), 0},
                            {"byte", sizeof(char), 1},
                            {"ubyte", sizeof(unsigned char), 0}
};

typedef struct var {
    struct var *next;
    char *name;
    varenum type;
    int refcount;
} var_t;

typedef struct numvar {
    var_t v;
    int num;
} numvar_t;

typedef struct arrvar {
    var_t v;
    cgc_size_t size;
    uint8_t arr[0];
} arrvar_t;

typedef struct viewvar {
    var_t v;
    arrvar_t *arr;
    viewtype_t *view;
    int sign;
    char *bytesize;
} viewvar_t;

typedef struct nspace {
    var_t *first;
    var_t *last;
    int count;
} nspace_t;

/**
 * Create new number variable.
 *
 * @param name Name of new variable
 * @param arg String containing constructor args
 * @return 0 on success, err number on error
 */
static int cgc_newnum(char *name, char *arg); 

/**
 * Create new array variable.
 *
 * @param name Name of new variable
 * @param arg String containing constructor args
 * @return 0 on success, err number on error
 */
static int cgc_newarr(char *name, char *arg);

/**
 * Create new view variable.
 *
 * @param name Name of new variable
 * @param arg String containing constructor args
 * @return 0 on success, err number on error
 */
static int cgc_newview(char *name, char *arg);

/**
 * Handle "new" command
 *
 * @return 0 on success, err number on error
 */
static int cgc_handlenew();

/**
 * Handle "get" command
 *
 * @return 0 on success, err number on error
 */
static int cgc_handleget();

/**
 * Handle "set" command
 *
 * @return 0 on success, err number on error
 */
static int cgc_handleset();

/**
 * Handle "del" command
 *
 * @return 0 on success, err number on error
 */
static int cgc_handledel();

/**
 * Delete a variable from the namespace, by name.
 *
 * @param name Name of variable
 * @return 0 on success, err number on error
 */
static int delvar(char *name); 

/**
 * Add a variable to the namespace.
 *
 * @param var Allocated variable struct
 * @param name Name of variable
 * @param type Type of the variable
 * @return 0 on success, err number on error
 */
static int addvar(var_t *var, char *name, varenum type); 

/**
 * Get variable by name
 *
 * @param name Name of variable
 * @return variable on success, NULL on error
 */
static var_t *getvar(char *name); 

/**
 * Calculate the total number, in bytes, of a view, from a list of num vars.
 *
 * @param varlist List of variable names
 * @return Size in bytes on success, 0 on error
 */
static uint32_t cgc_calc_bytesize(char *varlist); 

/**
 * Run a line from a script
 *
 * @param cmd Line from script
 * @return 0 on success, err number on failure
 */
static int runcmd(char *cmd); 


static char *cmds[4] = { NEWTOK, GETTOK, SETTOK, DELTOK };
static int (*handlers[4])() = { cgc_handlenew, cgc_handleget, cgc_handleset, cgc_handledel };
static char *types[3] = { NUM, ARR, VIEW }; 
static int (*constructors[3])(char *, char *) = { cgc_newnum, cgc_newarr, cgc_newview };
static nspace_t global_nspace = {NULL, 0, 0};

static int delvar(char *name) {
    var_t *cur = global_nspace.first;
    var_t *last = NULL;
    while (cur) {
        if (cgc_streq(cur->name,name)) {
            if (last)
                last->next = cur->next;
            else
                global_nspace.first = cur->next;

            if (!cur->next)
                global_nspace.last = last;

            if (cur->type == VIEWTYPE) {
                if (!(--(((viewvar_t*)cur)->arr->v.refcount)))
                    cgc_free(((viewvar_t*)cur)->arr);
            }

            //we keep arrays around until all outstanding refs are gone
            if (cur->refcount <= 0) //should be 0
                cgc_free(cur);

            global_nspace.count--;

            return 0;
        }
        last = cur;
        cur = cur->next;
    }
    return ERRNOSUCHVAR;
}

static int addvar(var_t *var, char *name, varenum type) {

    if (!(var->name = cgc_calloc(cgc_strlen(name)+1)))
        return ERRNOMEM;

    cgc_strcpy(var->name, name);

    var->type = type;
    if (global_nspace.last)
        global_nspace.last->next = var;
    global_nspace.last = var;
    if (!global_nspace.first)
        global_nspace.first = var; 
    var->next = NULL; //just to be safe
    global_nspace.count++;
    return 0;
}

static var_t *getvar(char *name) {
    var_t *cur = NULL;
    if (global_nspace.count <= 0 || !global_nspace.first)
        return NULL;

    cur = global_nspace.first;
    while (cur) {
        if (cgc_streq(cur->name, name))
            return cur;
        cur = cur->next;
    }
    return NULL;
}

static uint32_t cgc_calc_bytesize(char *varlist) {
    char *varname = NULL;
    char *varlistcpy = NULL;
    char *varlistcpy_strtok = NULL;
    var_t *var = NULL;
    uint32_t val = 0;

    if (!(varlistcpy = cgc_calloc(cgc_strlen(varlist)+1)))
        return 0;

    cgc_strcpy(varlistcpy,varlist);
    varlistcpy_strtok = varlistcpy;

    //we allow this to overflow, but result is checked for size elsewhere
    while ((varname = cgc_strtok(varlistcpy_strtok,','))) {
        varlistcpy_strtok = NULL; //for strtok
        if (cgc_strlen(varname) == 0)
            break;
        if (!(var = getvar(varname))) {
            val = 0;
            break;
        }
        if (var->type != NUMTYPE) {
            val = 0;
            break;
        }
        val += ((numvar_t*)var)->num;
    }
    cgc_free(varlistcpy);
    return val;
}

static int cgc_newnum(char *name, char *arg) {
    numvar_t *n = NULL;
    int res = 0;

    if (!(n = cgc_calloc(sizeof(numvar_t))))
        return ERRNOMEM;

    n->num = cgc_str2int(arg);

    res = addvar((var_t*)n, name, NUMTYPE);

    if(res)
        cgc_free(n);

    return res;
}

static int cgc_newarr(char *name, char *arg) {
    arrvar_t *a = NULL; 
    int res = 0;

    uint32_t size = cgc_str2uint(arg);

    if (size > MAXARRSIZE)
        return ERRTOOBIG;

    if (!(a = cgc_calloc(sizeof(arrvar_t)+(size*sizeof(int)))))
        return ERRNOMEM;

    a->size = size*sizeof(int);

    res = addvar((var_t*)a, name, ARRTYPE);

    if (res)
        cgc_free(a);

    return res;
}

static int cgc_newview(char *name, char *arg) {
    viewvar_t *v = NULL;
    arrvar_t *a = NULL;
    int i = 0;
    int res = 0;

    char *type = cgc_strtok(NULL,' ');

    if (!type || cgc_strlen(type) == 0)
        return ERRNOTYPE;

    if (!(a = (arrvar_t*)getvar(arg))) 
        return ERRNOSUCHVAR;

    if (a->v.type != ARRTYPE) 
        return ERRWRONGTYPE;

    if (!(v = cgc_calloc(sizeof(viewvar_t))))
        return ERRNOMEM;

    for (i=0; i < sizeof(viewtypes)/sizeof(viewtype_t); i++) {
        if (cgc_streq(type,viewtypes[i].name)) {
            v->view = &viewtypes[i];
            break;
        }
    }

    if (!v->view) {
        cgc_free(v);
        return ERRNOSUCHTYPE;
    }

    v->arr = a;

    res = addvar((var_t*)v, name, VIEWTYPE);

    if (res)
        cgc_free(v);

    return res;
}

static int cgc_handlenew() {
    char *type = NULL;
    char *name = NULL;
    char *arg = NULL;
    int i = 0;

    type = cgc_strtok(NULL,' ');

    if (!type || cgc_strlen(type) == 0)
        return ERRNOTYPE;

    name = cgc_strtok(NULL,' ');

    if (!name)
        return ERRNONAME;

    if (getvar(name))
        return ERRALREADYEXISTS;

    arg = cgc_strtok(NULL, ' ');

    if (!arg || cgc_strlen(arg) == 0)
        return ERRNOARG;

    for (i = 0; i < sizeof(types)/sizeof(types[0]); i+=1) {
        if (cgc_streq(type,types[i]))
            return constructors[i](name,arg);
    }

    return ERRNOSUCHTYPE;

}

static int cgc_handleget() {
    var_t *var = NULL;
    viewvar_t *view = NULL;
    char out[12] = {0};
    char *name = cgc_strtok(NULL, ' ');
    char *arg = NULL;
    char *subarg = NULL;
    uint32_t val = 0;
    uint32_t mask = 0;
    int idx = 0;
    int i = 0;

    if (!name || cgc_strlen(name) == 0)
        return ERRNONAME;

    if (!(var = getvar(name)))
        return ERRNOSUCHVAR;

    switch (var->type) {
        case NUMTYPE:
            cgc_int2str(out, sizeof(out), ((numvar_t*)var)->num);
            break;

        case ARRTYPE:
            if (!(arg = cgc_strtok(NULL, ' ')))
                return ERRNOARG;
            
            idx = cgc_str2uint(arg);

            if (idx >= ((arrvar_t*)var)->size/sizeof(int))
                return ERRINVALIDIDX;

            cgc_int2str(out, sizeof(out), ((int*)((arrvar_t*)var)->arr)[idx]);
            break;

        case VIEWTYPE:
            view = (viewvar_t*)var;

            if (!(arg = cgc_strtok(NULL, ' ')))
                return ERRNOARG;
            
            idx = cgc_str2uint(arg)*view->view->size;

            if (view->bytesize) {
                #ifndef PATCHED
                if (!(idx+view->view->size < cgc_calc_bytesize(view->bytesize)))
                #else
                if (!(idx+view->view->size < cgc_calc_bytesize(view->bytesize) && cgc_calc_bytesize(view->bytesize) < view->arr->size))
                #endif
                    return ERRINVALIDIDX;
            } else if (idx+view->view->size > view->arr->size) {
                return ERRINVALIDIDX;
            }

            for(i=0; i < view->view->size; i++) 
                val |=  view->arr->arr[i+idx] << (i*8);

            if (view->view->sign) {
                if (view->view->size == sizeof(int))
                    cgc_int2str(out, sizeof(out), val);
                else if (view->view->size == sizeof(short))
                    cgc_int2str(out, sizeof(out), (short)val);
                else if (view->view->size == sizeof(char))
                    cgc_int2str(out, sizeof(out), (char)val);
            } else {
                cgc_uint2str(out, sizeof(out), val);
            }

            break;
        default:
            return ERRNOSUCHTYPE;
    }

    SSENDL(cgc_strlen(out),out);
    return 0;
}

static int cgc_handleset() {
    var_t *var = NULL;
    char *name = cgc_strtok(NULL, ' ');
    char *arg = NULL, *arg2 = NULL, *varlist = NULL;
    uint32_t idx = 0;
    uint32_t val = 0;

    if (!name || cgc_strlen(name) == 0)
        return ERRNONAME;

    if (!(var = getvar(name)))
        return ERRNOSUCHVAR;

    if (!(arg = cgc_strtok(NULL, ' ')))
        return ERRNOARG;

    switch (var->type) {
        case NUMTYPE:
            ((numvar_t*)var)->num = cgc_str2int(arg);
            return 0;
        case ARRTYPE:
            idx = cgc_str2int(arg);

            if (idx >= ((arrvar_t*)var)->size/sizeof(int))
                return ERRINVALIDIDX;

            if (!(arg = cgc_strtok(NULL, ' ')))
                return ERRNOARG;

            ((int*)&((arrvar_t*)var)->arr)[idx] = cgc_str2int(arg);

            return 0;
        case VIEWTYPE:
            if (!(arg2 = cgc_strtok(NULL, ' ')))
                return ERRNOARG;

            if (!(varlist = cgc_calloc(cgc_strlen(arg2)+1)))
                return ERRNOMEM;

            cgc_strcpy(varlist,arg2);

            if (!cgc_streq(arg,"byteSize")) {
                cgc_free(varlist);
                return ERRNOSUCHVAR;
            }

            val = cgc_calc_bytesize(arg2);

            if (!(var = getvar(name))) {
                cgc_free(varlist);
                return ERRNOSUCHVAR;
            }

            if (val > ((viewvar_t*)var)->arr->size) {
                cgc_free(varlist);
                return ERRTOOBIG;
            }

            if (((viewvar_t*)var)->bytesize)
                cgc_free(((viewvar_t*)var)->bytesize);

            ((viewvar_t*)var)->bytesize = varlist;

            return 0;

        default:
            return ERRNOSUCHTYPE;
    }
}

static int cgc_handledel() {
    char *name = cgc_strtok(NULL,' ');

    if (!name || cgc_strlen(name)==0)
        return ERRNONAME;

    return delvar(name);
}

static int runcmd(char *cmd) {
    int i;

    cmd = cgc_strtok(cmd,' ');

    if (!cmd || cgc_strlen(cmd) == 0)
        return ERRSHORT;

    for (i = 0; i < sizeof(cmds)/sizeof(cmds[0]); i+=1) {
        if (cgc_streq(cmd,cmds[i]))
            return handlers[i]();
    }

    return ERRNOSUCHCMD;
}

int cgc_run_viewscript(char *script) {

    char *cur = script;
    char **lines;
    int res = 0;
    int idx = 0;
    int count = 0;
    //this is properly null-terminated by main()
    int len = cgc_strlen(script);

    if (len > MAXSCRIPTSIZE)
        return ERRTOOBIG;

    while(*cur) {
        if (*cur == '\n')
            count++;
        cur++;
    }

    if (count == 0)
        return ERRSHORT;

    if (!(lines = cgc_calloc((count+1)*sizeof(char *))))
        return ERRNOMEM;

    lines[0] = cgc_strtok(script,'\n');
    #ifdef PATCHED
    while (idx < count && (lines[++idx] = cgc_strtok(NULL,'\n')));
    #else 
    while ((lines[++idx] = cgc_strtok(NULL,'\n')));
    #endif
    for (idx = 0; idx < count; idx++) {
        if ((res = runcmd(lines[idx])))
            return res;
    }

    cgc_free(lines);

    LOG("Done.");

    return 0;
}
