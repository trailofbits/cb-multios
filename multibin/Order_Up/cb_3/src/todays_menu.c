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
#include <libcgc.h>
#include <stdint.h>
#include "libc.h"
#include "memcpy.h"
#include "memset.h"
#include "malloc.h"
#include "string.h"

#include "menu.h"
#include "todays_menu.h"

/**
 * Add an appetizer to the menu.
 *
 * @param m     Menu
 * @param a     Appetizer to add to menu
 */
static void add_appetizer(Menu *m, Appetizer *a) {
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
static void add_meal(Menu *m, Meal *meal) {
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
static void add_dessert(Menu *m, Dessert *d) {
    Dessert *cur = m->dessert_list;
    if (NULL == cur) {
        m->dessert_list = d;
    } else {
        for (; NULL != cur->next; cur=(Dessert *)cur->next);

        cur->next = d;
    }
}

void load_menu(Menu *menu) {
    Appetizer *a = NULL;
    Meal *m = NULL;
    Dessert *d = NULL;
    const char *name = NULL;
    const char *main = NULL;
    const char *veggies = NULL;
    const char *side = NULL;

    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "ZbWWNoNM";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "eDsELei";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "WSpBFJFOZgwszDffv";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "OjZiYi";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "AnGOULFOGC";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "cSOLkHLjNiSr";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "dNlwfQlb";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "Jdubqqhp";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "ypDpTEmYTJNbgwuAAuk";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "PxSfXOLhtqroMQEYuI";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "KGLHaywX";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "wTopgFWuWqFm";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "exxhtKZQ";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "JxQkslh";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "OKtn";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "sZlmZGiQPtIAh";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "KvBPV";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "YMiRPnuTZ";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "vSyFUX";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "koaVbUY";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "vGlLNtRWMBPrSQIGBl";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "VsdLokjwQPOmqX";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "uMcUfcpDItFDs";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "bdQ";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "Snt";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "BfJB";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "eJpMHmjqGbdtZTaC";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "BN";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "OhPbcBnJFNBsfKxc";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "MAEwIQ";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "FbZsPlRYOfBimieMN";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "tMyziPnmnv";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "ENGodOMkSCcdp";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "oW";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "jqBfeUjRYCpwb";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "I";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "ZTRhTQBKSyHSvnA";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "AAYAcqLF";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "GdO";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "OJGbM";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "CvqK";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "irsRWLUz";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "apwd";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "HbTGG";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "giSPcyLgGK";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "gBXDWHZEILFekw";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "XLWfktopVr";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "JhDmBevCueHq";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "tve";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    a = malloc(sizeof(Appetizer));
    MALLOC_OK(a);
    memset(a, '\0', sizeof(Appetizer));
    a->ftype = APP_TYPE;
    name = "aUWYXBp";
    memcpy(a->name, name, strlen(name, '\0'));
    add_appetizer(menu,a);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "Zj";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "elHXoEkGJHTfXydBj";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "BkngOfUoTmqtHOMAsSC";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "XjMM";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "eZlRse";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "NTOvguiPgjPlEc";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "RDyNWXZu";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "gPRF";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "XLmGtNwx";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "DRgdveNnWklqvg";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "peSjRFwkVUTWaBqkUZc";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "vEicQun";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "mEOcRZWoWATCb";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "A";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "uX";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "C";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "qk";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "DImoNaZRWzYbjunIA";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "HZQqWOurDrFhZYi";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "jfKqdlVACidsVYrKT";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "vhKkoZ";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "QluJoiBdiPSjTREbfCV";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "RGqRxjI";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "jdoZXCoKrCHis";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "KhVzoF";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "TvAMOyYghpritkQKt";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "YlkFYBvSqtQxU";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "ossUKKxCsEPwAQuRc";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "cGsWHxAeFkByvPuAnb";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "u";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "UYBeUiccXeIdacmo";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "skLRiJW";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "Dzs";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "hUN";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "RrvWQClGLc";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "E";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "LPWgXP";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "ZgQkrAsglrUFknMGX";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "MOoJtdbGKwI";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "CzfnjxBK";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "mD";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "Es";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "uqiFNVKzPFeoMm";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "GoAPHgyqAHYxl";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "DvCF";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "pHIEymqeAycJijjFFk";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "e";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "IyWZnR";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "QblFGrOfyuS";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "T";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "BZzN";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "GtrPWzKW";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "FXEHUTFUF";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "McSUxQepzTIeu";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "VIfO";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "qg";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "hqWsFPYCvuQ";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "fPIeUkgPhYG";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "mWWjU";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "NBmQapgAdNh";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "hEftYexRZsXkUncI";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "oWQHyVMOfSyaKEib";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "PHdBEJSkmyKM";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "WuHadHwnipvH";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "gbK";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "r";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "g";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "CHSfCaUqj";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "FyYzVa";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "X";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "ImwYuQymbIIGAb";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "vZmZhVnBnTwEUnuNKAh";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "QjLlpYhdEwffGsyObxr";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "mIUZITpftBvcMifY";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "EqSfGGewaUntOuFNlRQ";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "zWOFfCwKkwDTnIFX";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "E";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "AtjGgIxYASTCOC";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "aOVAVDAvqbpKPQzs";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "GTzDwFtOZBGsbbM";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "lZhdeTslbTBK";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "pwqEZDoh";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "gmpwZynj";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "cr";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "Hcb";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "Tqzl";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "VoiXIgGAtoNHMq";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "mROScjgKBz";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "caloY";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "KYlwUCwgkhh";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "MLxIEz";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "SxzeyKTHsODuUk";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "cwoMLL";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "sKykXwqm";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "NXaG";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "qryLVWWEwEx";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "hoPyZCWLbzlEdS";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "nJNOemZLRA";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "QqpfnCul";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "hKxFhOFanfnrmMMo";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "HBjxBFrofPKcLh";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "HQXkYe";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "HVtZCfTbqD";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "TrkhFsCcoSRkwftoT";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "tsiK";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "bYqcAspvb";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "zuFxOQEXKMHzJCHmTX";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "urVZe";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "hBfkvxWNYNKAWOzmasc";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "gxqlPTpMapFtlDNcN";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "svzMcxufKVy";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "oLvwcIJsXjzJYrnK";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "wuXVqAIWyTbaeTq";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "ucayTRX";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "jLIxECdyrhWfwuhZ";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "OFpbDRbVfx";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "zkbsnHsQYNpgrMw";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "TgHn";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "PrzysxmuxvWGic";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "LLEdnN";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "n";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "KoXHZsrHnUtQi";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "FriJyufIKULUYxS";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "KkUZp";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "kcIlkHphxKeZWiyh";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "wAkD";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "oNKz";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "QlpxCsSSsfAsT";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "IPZfoyxxrvYzwNmcndJ";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "HwOSnePDOXk";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "BNqrexKmxzwYqR";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "ZzTFYA";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "xGimYTMbTGurv";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "yg";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "fVAqrTHHLKaZimlJqjI";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "VbDaKZELJ";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "UmXu";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "ormjxbdGdKYIQejskBV";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "pSBIfScXYfA";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "OZIGfmINguZcpfi";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "vZgXTmEfJrxpukXLiy";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "iAQFY";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "iCw";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "ipsiSSCBtPZzgLWkRby";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "GatLliocExXqUDhGGg";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "BdCRYrsIW";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "UvmPPZRWNmeKuh";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "BUIfblmlpKYpnXzK";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "mxCEajsFOx";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "jMHek";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "oqBIFUSsfGLwuqp";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "tpQdTrVfwEbVqCGC";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "Ie";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "yvwHDjpJGkOO";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "eQgFSsFgTQtQT";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "VhbNDL";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "MW";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "pVAbrgTmfsf";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "NDkwNvbbHkmg";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "eqlYvUouwSFcet";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "PZVEoFhIc";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "tCfePusRu";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "d";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "IyghjY";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "AsY";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "pfvxYeTqc";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "ZTxaQoNQYaIBBY";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "YRbgJKV";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "k";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "rwUiJ";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "RrNSfpsriLJXJAn";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "YtC";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "EBzXJGYjGffCyBiPp";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "QSILluzPFyZZbEsE";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "wtddywMhBwD";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "mLyAdUlsMGFhP";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "vbWrs";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "xWBdzcvZQTf";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "QdjRhFJ";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "UhIQDYCNZ";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "mCObWa";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "An";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "AFygdlesQryFQJPbBiq";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "gWvmtTG";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "JssjKtCzNVAeX";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "IXrWDMTGKTAPatTSl";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "CtvtzAZHCYnxfk";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "TeWfgjhdilcO";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "HakKrdXeRCpQJ";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "FKnGclTRQFvjz";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "vJpUnutIkgpm";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "bLsFqgMw";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "VdI";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "rDnCfN";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "qe";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "EijGXvaPpbk";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    m = malloc(sizeof(Meal));
    MALLOC_OK(m);
    memset(m, '\0', sizeof(Meal));
    m->ftype = MEAL_TYPE;
    name = "wePMzfShzImZDOTgLc";
    memcpy(m->name, name, strlen(name, '\0'));
    main = "Zxpb";
    memcpy(m->main, main, strlen(main, '\0'));
    veggies = "YsiGeamwZgFEp";
    memcpy(m->veggies, veggies, strlen(veggies, '\0'));
    side = "HDeBa";
    memcpy(m->side, side, strlen(side, '\0'));
    add_meal(menu, m);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "AKPReWjkKZRnRsGvRDU";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "xvvfIjwJxxoX";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "EcVatQDxgHwEwd";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "xL";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "CGabmQUFBiTiyg";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "OLgmcumpKx";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "ZOrnojF";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "ejxWijyBhfjzOi";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "wZyEJHaU";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "SQGmFKASiGI";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "tmdsFsKDge";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "cOkXtVctEuoeCFHQGzT";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "FZSdmjxmSVL";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "dKRAFyzUnzoKLKD";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "fegevMNqQD";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "VCmTydTBVQCeLQ";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "loyAbN";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "JnOZlrmpv";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "YZdBWVBsuGQ";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "suwkMLdoZTwWHsivcVs";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "nvoEWCpENpxDVuUGh";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "kDnXpp";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "jsffGu";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "VSJGQCLjpWi";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "yaSAoGMePbTvXYszZpd";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "YQOfPYMomTxSMKIZJPj";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "pesQByVw";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "Y";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "jqkl";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "CrBjW";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "TWYFRqe";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "UalYcxsnHdUOwB";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "GRBycFmDIEcoTP";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "oleZre";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "kXwjlceRFOuSLDl";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "qWyXwZXJFkDH";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "GbjNxstDxKmrM";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "NMLxnTqga";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "PneNgwQjz";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "yQyOP";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "ozox";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "AcdZXwJxQVoZbt";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "smmGG";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "XR";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "Amb";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "hBKpQJTqUVKJ";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "gBuAyZnrOXNVwInMU";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "m";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "cJVIJ";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);
    //
    d = malloc(sizeof(Dessert));
    MALLOC_OK(d);
    memset(d, '\0', sizeof(Dessert));
    d->ftype = DES_TYPE;
    name = "Jhu";
    memcpy(d->name, name, strlen(name, '\0'));
    add_dessert(menu,d);

}

