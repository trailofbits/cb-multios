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
#include "cgc_stdint.h"
#include "cgc_libc.h"
#include "cgc_memcpy.h"
#include "cgc_memset.h"
#include "cgc_malloc.h"
#include "cgc_string.h"

#include "cgc_menu.h"
#include "cgc_todays_menu.h"

/**
 * Add an appetizer to the menu.
 *
 * @param m     Menu
 * @param a     Appetizer to add to menu
 */
static void cgc_add_appetizer(Menu *m, Appetizer *a) {
    Appetizer *cur = m->appetizer_list;
    if (NULL == cur) {
        m->appetizer_list = a;
    } else {
        for (; NULL != cur->next; cur=(Appetizer *)cur->next);

        cur->next = a;
    }
}

/**
 * Add a meal to the menu.
 *
 * @param m     Menu
 * @param meal  Meal to add to menu
 */
static void cgc_add_meal(Menu *m, Meal *meal) {
    Meal *cur = m->meal_list;
    if (NULL == cur) {
        m->meal_list = meal;
    } else {
        for (; NULL != cur->next; cur=(Meal *)cur->next);

        cur->next = meal;
    }
}

/**
 * Add a dessert to the menu
 *
 * @param m     Menu
 * @param d     Dessert to add to menu
 */
static void cgc_add_dessert(Menu *m, Dessert *d) {
    Dessert *cur = m->dessert_list;
    if (NULL == cur) {
        m->dessert_list = d;
    } else {
        for (; NULL != cur->next; cur=(Dessert *)cur->next);

        cur->next = d;
    }
}

void cgc_load_menu(Menu *menu) {
    Appetizer *a = NULL;
    Meal *m = NULL;
    Dessert *d = NULL;
    const char *name = NULL;
    const char *main = NULL;
    const char *veggies = NULL;
    const char *side = NULL;

    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "ZbWWNoNM";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "eDsELei";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "WSpBFJFOZgwszDffv";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "OjZiYi";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "AnGOULFOGC";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "cSOLkHLjNiSr";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "dNlwfQlb";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "Jdubqqhp";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "ypDpTEmYTJNbgwuAAuk";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "PxSfXOLhtqroMQEYuI";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "KGLHaywX";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "wTopgFWuWqFm";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "exxhtKZQ";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "JxQkslh";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "OKtn";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "sZlmZGiQPtIAh";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "KvBPV";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "YMiRPnuTZ";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "vSyFUX";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "koaVbUY";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "vGlLNtRWMBPrSQIGBl";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "VsdLokjwQPOmqX";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "uMcUfcpDItFDs";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "bdQ";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "Snt";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "BfJB";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "eJpMHmjqGbdtZTaC";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "BN";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "OhPbcBnJFNBsfKxc";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "MAEwIQ";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "FbZsPlRYOfBimieMN";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "tMyziPnmnv";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "ENGodOMkSCcdp";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "oW";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "jqBfeUjRYCpwb";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "I";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "ZTRhTQBKSyHSvnA";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "AAYAcqLF";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "GdO";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "OJGbM";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "CvqK";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "irsRWLUz";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "apwd";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "HbTGG";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "giSPcyLgGK";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "gBXDWHZEILFekw";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "XLWfktopVr";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "JhDmBevCueHq";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "tve";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    a = cgc_malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    cgc_memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "aUWYXBp";
    cgc_memcpy(a->name, name, cgc_strlen(name, '\0'));
    cgc_add_appetizer(menu,a);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "Zj";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "elHXoEkGJHTfXydBj";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "BkngOfUoTmqtHOMAsSC";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "XjMM";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "eZlRse";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "NTOvguiPgjPlEc";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "RDyNWXZu";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "gPRF";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "XLmGtNwx";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "DRgdveNnWklqvg";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "peSjRFwkVUTWaBqkUZc";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "vEicQun";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "mEOcRZWoWATCb";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "A";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "uX";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "C";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "qk";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "DImoNaZRWzYbjunIA";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "HZQqWOurDrFhZYi";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "jfKqdlVACidsVYrKT";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "vhKkoZ";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "QluJoiBdiPSjTREbfCV";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "RGqRxjI";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "jdoZXCoKrCHis";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "KhVzoF";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "TvAMOyYghpritkQKt";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "YlkFYBvSqtQxU";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "ossUKKxCsEPwAQuRc";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "cGsWHxAeFkByvPuAnb";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "u";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "UYBeUiccXeIdacmo";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "skLRiJW";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "Dzs";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "hUN";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "RrvWQClGLc";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "E";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "LPWgXP";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "ZgQkrAsglrUFknMGX";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "MOoJtdbGKwI";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "CzfnjxBK";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "mD";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "Es";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "uqiFNVKzPFeoMm";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "GoAPHgyqAHYxl";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "DvCF";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "pHIEymqeAycJijjFFk";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "e";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "IyWZnR";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "QblFGrOfyuS";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "T";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "BZzN";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "GtrPWzKW";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "FXEHUTFUF";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "McSUxQepzTIeu";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "VIfO";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "qg";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "hqWsFPYCvuQ";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "fPIeUkgPhYG";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "mWWjU";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "NBmQapgAdNh";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "hEftYexRZsXkUncI";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "oWQHyVMOfSyaKEib";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "PHdBEJSkmyKM";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "WuHadHwnipvH";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "gbK";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "r";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "g";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "CHSfCaUqj";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "FyYzVa";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "X";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "ImwYuQymbIIGAb";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "vZmZhVnBnTwEUnuNKAh";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "QjLlpYhdEwffGsyObxr";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "mIUZITpftBvcMifY";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "EqSfGGewaUntOuFNlRQ";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "zWOFfCwKkwDTnIFX";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "E";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "AtjGgIxYASTCOC";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "aOVAVDAvqbpKPQzs";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "GTzDwFtOZBGsbbM";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "lZhdeTslbTBK";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "pwqEZDoh";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "gmpwZynj";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "cr";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "Hcb";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "Tqzl";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "VoiXIgGAtoNHMq";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "mROScjgKBz";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "caloY";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "KYlwUCwgkhh";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "MLxIEz";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "SxzeyKTHsODuUk";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "cwoMLL";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "sKykXwqm";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "NXaG";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "qryLVWWEwEx";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "hoPyZCWLbzlEdS";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "nJNOemZLRA";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "QqpfnCul";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "hKxFhOFanfnrmMMo";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "HBjxBFrofPKcLh";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "HQXkYe";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "HVtZCfTbqD";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "TrkhFsCcoSRkwftoT";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "tsiK";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "bYqcAspvb";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "zuFxOQEXKMHzJCHmTX";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "urVZe";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "hBfkvxWNYNKAWOzmasc";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "gxqlPTpMapFtlDNcN";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "svzMcxufKVy";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "oLvwcIJsXjzJYrnK";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "wuXVqAIWyTbaeTq";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "ucayTRX";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "jLIxECdyrhWfwuhZ";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "OFpbDRbVfx";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "zkbsnHsQYNpgrMw";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "TgHn";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "PrzysxmuxvWGic";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "LLEdnN";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "n";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "KoXHZsrHnUtQi";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "FriJyufIKULUYxS";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "KkUZp";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "kcIlkHphxKeZWiyh";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "wAkD";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "oNKz";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "QlpxCsSSsfAsT";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "IPZfoyxxrvYzwNmcndJ";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "HwOSnePDOXk";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "BNqrexKmxzwYqR";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "ZzTFYA";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "xGimYTMbTGurv";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "yg";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "fVAqrTHHLKaZimlJqjI";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "VbDaKZELJ";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "UmXu";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "ormjxbdGdKYIQejskBV";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "pSBIfScXYfA";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "OZIGfmINguZcpfi";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "vZgXTmEfJrxpukXLiy";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "iAQFY";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "iCw";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "ipsiSSCBtPZzgLWkRby";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "GatLliocExXqUDhGGg";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "BdCRYrsIW";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "UvmPPZRWNmeKuh";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "BUIfblmlpKYpnXzK";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "mxCEajsFOx";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "jMHek";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "oqBIFUSsfGLwuqp";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "tpQdTrVfwEbVqCGC";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "Ie";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "yvwHDjpJGkOO";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "eQgFSsFgTQtQT";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "VhbNDL";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "MW";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "pVAbrgTmfsf";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "NDkwNvbbHkmg";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "eqlYvUouwSFcet";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "PZVEoFhIc";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "tCfePusRu";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "d";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "IyghjY";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "AsY";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "pfvxYeTqc";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "ZTxaQoNQYaIBBY";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "YRbgJKV";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "k";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "rwUiJ";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "RrNSfpsriLJXJAn";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "YtC";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "EBzXJGYjGffCyBiPp";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "QSILluzPFyZZbEsE";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "wtddywMhBwD";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "mLyAdUlsMGFhP";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "vbWrs";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "xWBdzcvZQTf";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "QdjRhFJ";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "UhIQDYCNZ";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "mCObWa";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "An";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "AFygdlesQryFQJPbBiq";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "gWvmtTG";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "JssjKtCzNVAeX";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "IXrWDMTGKTAPatTSl";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "CtvtzAZHCYnxfk";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "TeWfgjhdilcO";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "HakKrdXeRCpQJ";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "FKnGclTRQFvjz";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "vJpUnutIkgpm";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "bLsFqgMw";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "VdI";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "rDnCfN";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "qe";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "EijGXvaPpbk";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    m = cgc_malloc(sizeof(Meal));
    MALLOC_OK(m);
    cgc_memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "wePMzfShzImZDOTgLc";
    cgc_memcpy(m->name, name, cgc_strlen(name, '\0'));
    main = "Zxpb";
    cgc_memcpy(m->main, main, cgc_strlen(main, '\0'));
    veggies = "YsiGeamwZgFEp";
    cgc_memcpy(m->veggies, veggies, cgc_strlen(veggies, '\0'));
    side = "HDeBa";
    cgc_memcpy(m->side, side, cgc_strlen(side, '\0'));
    cgc_add_meal(menu, m);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "AKPReWjkKZRnRsGvRDU";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "xvvfIjwJxxoX";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "EcVatQDxgHwEwd";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "xL";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "CGabmQUFBiTiyg";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "OLgmcumpKx";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "ZOrnojF";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "ejxWijyBhfjzOi";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "wZyEJHaU";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "SQGmFKASiGI";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "tmdsFsKDge";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "cOkXtVctEuoeCFHQGzT";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "FZSdmjxmSVL";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "dKRAFyzUnzoKLKD";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "fegevMNqQD";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "VCmTydTBVQCeLQ";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "loyAbN";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "JnOZlrmpv";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "YZdBWVBsuGQ";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "suwkMLdoZTwWHsivcVs";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "nvoEWCpENpxDVuUGh";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "kDnXpp";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "jsffGu";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "VSJGQCLjpWi";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "yaSAoGMePbTvXYszZpd";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "YQOfPYMomTxSMKIZJPj";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "pesQByVw";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "Y";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "jqkl";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "CrBjW";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "TWYFRqe";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "UalYcxsnHdUOwB";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "GRBycFmDIEcoTP";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "oleZre";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "kXwjlceRFOuSLDl";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "qWyXwZXJFkDH";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "GbjNxstDxKmrM";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "NMLxnTqga";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "PneNgwQjz";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "yQyOP";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "ozox";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "AcdZXwJxQVoZbt";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "smmGG";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "XR";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "Amb";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "hBKpQJTqUVKJ";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "gBuAyZnrOXNVwInMU";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "m";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "cJVIJ";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);
    //
    d = cgc_malloc(sizeof(Dessert));
    MALLOC_OK(d);
    cgc_memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "Jhu";
    cgc_memcpy(d->name, name, cgc_strlen(name, '\0'));
    cgc_add_dessert(menu,d);

}

