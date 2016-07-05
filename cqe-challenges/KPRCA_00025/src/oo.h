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
#ifndef OO_H_
#define OO_H_

#include <stdlib.h>
#include <string.h>

#define DeclareClass(name,parent) \
    static const int __level_##name = __level_##parent + 1; \
    typedef struct __instance_##name name; \
    name * __new_##name (); \
    struct __class_##name { \
        struct __class_##parent;
#define EndDeclareClass(name,parent) }; \
    struct __instance_##name { \
        parent super[0]; \
        struct __vtable_##name *__vtable; \
        struct __class_##name; \
    }; \

#define DefineClass(name,parent) \
    static void __init_##name () { \
        if (sizeof(__default_vtable_##parent)) \
        memcpy(&__default_vtable_##name, &__default_vtable_##parent, sizeof(__default_vtable_##parent)); \
    }; \
    const __init_array_t __init_array_##cls##_##name __attribute__((section(".rodata.init"))) = { __level_##name, __init_##name }; \
    name * __new_##name () { \
        name *o = malloc(sizeof(name)); \
        ASSERT_ALLOC(o); \
        o->__vtable = & __default_vtable_##name ; \
        if (o->__vtable->$init) $(o, $init); \
        return o; \
    };

#define DeclareClassFunctions(name,parent) \
    struct __vtable_##name { \
        struct __vtable_##parent;
#define EndDeclareClassFunctions(name) } __default_vtable_##name;

#define DeclareFunction(cls,rtype,name,...) \
    rtype (* name) ( cls *, ##__VA_ARGS__);

#define DefineFunction(cls,rtype,name,...) \
    rtype __##cls##_##name (cls * this, ##__VA_ARGS__); \
    static void __init_##cls##_##name () { \
        __default_vtable_##cls.name = (void *)__##cls##_##name; \
    }; \
    const __init_array_t __init_array_##cls##_##name __attribute__((section(".rodata.init"))) = { __level_##cls, __init_##cls##_##name }; \
    rtype __##cls##_##name (cls * this, ##__VA_ARGS__)

#define $super(cls,this,func,...) __default_vtable_##cls.func((void *)(this), ##__VA_ARGS__)
#define $(this,func,...) (this)->__vtable->func((void *)(this), ##__VA_ARGS__)

// superclass of all other classes
typedef struct __instance_Object Object;
struct __class_Object {
};
struct __instance_Object {
    struct __vtable_Object *__vtable;
    struct __class_Object;
};
extern struct __vtable_Object {
    void (*$init) (Object *X);
    void (*$destroy) (Object *X);
} __default_vtable_Object;
static const int __level_Object = 0;

// initialization
typedef struct {
    int level;
    void (*func) ();
} __init_array_t;

extern const __init_array_t __init_array_begin;
extern const __init_array_t __init_array_end;

#define InitClasses() do { \
        const __init_array_t* init_array; \
        int level, max_level = 0; \
        for (init_array = &__init_array_begin + 1; init_array != &__init_array_end; init_array++) \
            if (init_array->level > max_level) max_level = init_array->level; \
        for (level = 0; level <= max_level; level++) \
            for (init_array = &__init_array_begin + 1; init_array != &__init_array_end; init_array++) \
                if (init_array->level == level) init_array->func(); \
    } while (0)

// helpers for object constrution and destruction
#define new(X) __new_##X()
#define delete(X) __delete((Object *)(X))
static void __delete(Object *X)
{
    if (X->__vtable->$destroy)
        X->__vtable->$destroy(X);
    free(X);
}

// exception support
typedef struct __except_state {
    struct __except_state *next;
    jmp_buf jmpbuf;
    int raise;
} __except_state_t;
extern __except_state_t *__except_current;
#define Try { \
    __except_state_t __except_state; \
    __except_state.raise = 1; \
    __except_state.next = __except_current; \
    __except_current = &__except_state; \
    int __except_result = setjmp(__except_state.jmpbuf); \
    if (__except_result == 0) {
#define Catch(x) } \
    if (__except_result == (x)) { \
        __except_state.raise = 0;
#define Finally } \
    {
#define EndTry  } \
    __except_current = __except_state.next; \
    if (__except_state.raise) raise(__except_result); \
    }
#define exc_code() __except_result
void raise(int exc) __attribute__((__noreturn__));

#define EXC_NO_MEMORY 1
#define EXC_BAD_STATE 2
#define EXC_IO 3
#define EXC_NOT_IMPLEMENTED 4

#define ASSERT_OR_RAISE(x, y) do { \
    if (!(x)) raise((y)); \
} while(0)

#define ASSERT_ALLOC(x) ASSERT_OR_RAISE((x) != NULL, EXC_NO_MEMORY)

#endif
