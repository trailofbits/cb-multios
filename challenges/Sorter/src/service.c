/*
 * Copyright (c) 2015 Kaprica Security, Inc.
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
#include "cgc_stdio.h"
#include "cgc_string.h"
#include "cgc_packed.h"

#define MALLOC(_FPTRS, _SZ) ((*((void *(*)(cgc_size_t))(_FPTRS)[0]))(((_SZ))))
#define FREE(_FPTRS, _PTR)  ((*((void *(*)(void *))(_FPTRS)[1]))(((_PTR))))
#define MEMCPY(_FPTRS, _DST, _SRC, _SZ) ((*(void *(*)(void *, void *, cgc_size_t))(_FPTRS)[2])((_DST), (_SRC), (_SZ)))
#define cgc_memmove(_FPTRS, _DST, _SRC, _SZ) ((*(void *(*)(void *, void *, cgc_size_t))(_FPTRS)[3])((_DST), (_SRC), (_SZ)))
#define PRINT_ARRAY(_FPTRS, _ARR, _SZ) ((*(void (*)(int *, cgc_size_t))(_FPTRS)[4])((_ARR), (_SZ)))
#define SWAP(_FPTRS, _FIRST, _SECOND) ((*(void (*)(int *, int *))(_FPTRS)[5])((_FIRST), (_SECOND)))
#define HEAPIFY(_FPTRS, _ARR, _SZ) ((*(int (*)(int *, cgc_size_t, int *))(_FPTRS)[6])((_ARR), (_SZ), (_FPTRS)))
#define HEAP_PROPAGATE(_FPTRS, _ARR, _SZ, _SWAP_IDX) \
                            ((*(int (*)(int *, cgc_size_t, cgc_size_t, int *))(_FPTRS)[7])((_ARR), (_SZ), (_SWAP_IDX), (_FPTRS)))
#define MERGE_HELPER(_FPTRS, _ARR1, _ARR2, _IDX1, _IDX2) \
                            ((*(int (*)(int *, int *, int, int, int *))(_FPTRS)[8])((_ARR1), (_ARR2), (_IDX1), (_IDX2), (_FPTRS)))
#define cgc_ALLOCATE(_FPTRS, _LEN, _IS_X, _PADDR) ((*(int (*)(cgc_size_t, int, void **))(_FPTRS)[9])((_LEN), (_IS_X), (_PADDR)))
#define DEALLOCATE(_FPTRS, _ADDR, _LEN) ((*(int (*)(void *, cgc_size_t))(_FPTRS)[10])((_ADDR), (_LEN)))

int (*insertion_sort_unpacked)(int *, cgc_size_t, int *);
unsigned char *insertion_sort_memory;

int (*selection_sort_unpacked)(int *, cgc_size_t, int *);
unsigned char *selection_sort_memory;

int (*heap_propagate_unpacked)(int *, cgc_size_t, cgc_size_t, int *);
unsigned char *heap_propagate_memory;

int (*heapify_unpacked)(int *, cgc_size_t, int *);
unsigned char * heapify_memory;

int (*heap_sort_unpacked)(int *, cgc_size_t, int *);
unsigned char *heap_sort_memory;

int (*merge_helper_unpacked)(int *, int *, int, int, int *);
unsigned char *merge_helper_memory;

int (*merge_sort_unpacked)(int *, cgc_size_t, int *);
unsigned char *merge_sort_memory;

void cgc_unpack(unsigned char *fn_bytes, cgc_size_t num_bytes)
{
    char unpack_key[] = "CS10FUN!";
    int i = 0;
    int keylen = cgc_strlen(unpack_key);

    for (i = 0; i < num_bytes; i++)
        fn_bytes[i] ^= unpack_key[i % keylen];
}

void cgc_init()
{
    cgc_allocate(sizeof(selection_sort_bytes), 1, (void **)&selection_sort_memory);
    cgc_memcpy(selection_sort_memory, selection_sort_bytes, sizeof(selection_sort_bytes));
    cgc_unpack(selection_sort_memory, sizeof(selection_sort_bytes));
    selection_sort_unpacked = (int (*)(int *, cgc_size_t, int *))selection_sort_memory;

    cgc_allocate(sizeof(heap_propagate_bytes), 1, (void **)&heap_propagate_memory);
    cgc_memcpy(heap_propagate_memory, heap_propagate_bytes, sizeof(heap_propagate_bytes));
    cgc_unpack(heap_propagate_memory, sizeof(heap_propagate_bytes));
    heap_propagate_unpacked = (int (*)(int *, cgc_size_t, cgc_size_t, int *))heap_propagate_memory;

    cgc_allocate(sizeof(heapify_bytes), 1, (void **)&heapify_memory);
    cgc_memcpy(heapify_memory, heapify_bytes, sizeof(heapify_bytes));
    cgc_unpack(heapify_memory, sizeof(heapify_bytes));
    heapify_unpacked = (int (*)(int *, cgc_size_t, int *))heapify_memory;

    cgc_allocate(sizeof(heap_sort_bytes), 1, (void **)&heap_sort_memory);
    cgc_memcpy(heap_sort_memory, heap_sort_bytes, sizeof(heap_sort_bytes));
    cgc_unpack(heap_sort_memory, sizeof(heap_sort_bytes));
    heap_sort_unpacked = (int (*)(int *, cgc_size_t, int *))heap_sort_memory;

    cgc_allocate(sizeof(merge_helper_bytes), 1, (void **)&merge_helper_memory);
    cgc_memcpy(merge_helper_memory, merge_helper_bytes, sizeof(merge_helper_bytes));
    cgc_unpack(merge_helper_memory, sizeof(merge_helper_bytes));
    merge_helper_unpacked = (int (*)(int *, int *, int, int, int *))merge_helper_memory;

    cgc_allocate(sizeof(merge_sort_bytes), 1, (void **)&merge_sort_memory);
    cgc_memcpy(merge_sort_memory, merge_sort_bytes, sizeof(merge_sort_bytes));
    cgc_unpack(merge_sort_memory, sizeof(merge_sort_bytes));
    merge_sort_unpacked = (int (*)(int *, cgc_size_t, int *))merge_sort_memory;

    cgc_allocate(sizeof(insertion_sort_bytes), 1, (void **)&insertion_sort_memory);
    cgc_memcpy(insertion_sort_memory, insertion_sort_bytes, sizeof(insertion_sort_bytes));
    cgc_unpack(insertion_sort_memory, sizeof(insertion_sort_bytes));
    insertion_sort_unpacked = (int (*)(int *, cgc_size_t, int *))insertion_sort_memory;
}

void cgc_swap(int *first, int *second)
{
    int swap_pos;
    swap_pos = *first;
    *first = *second;
    *second = swap_pos;
    return;
}

void cgc_print_array(int *array, cgc_size_t array_size) {
    if (!array || !array_size) {
        cgc_printf("Empty Array\n");
        return;
    }

    cgc_printf("Array data\n[");
    int i;
    for (i = 0; i < array_size; i++) {
        cgc_printf("%d", array[i]);
        if (i < array_size - 1)
            cgc_printf(", ");
        else
            cgc_printf("]\n");
    }
}

int *cgc_create_number_array(cgc_size_t *array_size) {
    char buf[64];
    int i = 0;
    int *array = cgc_malloc(2 * sizeof(int));
    int array_len = 0;
    *array_size = 2;

    cgc_printf("Enter a list of numbers to sort. End the list with ';;'\n");
    cgc_fflush(cgc_stdout);
    while (i < sizeof(buf) - 1) {
        cgc_fread(&buf[i], 1, cgc_stdin);
        if (i && buf[i] == ';' && buf[i-1] == ';')
            break;
        else if (buf[i] == ',') {
            buf[i] = '\0';
            if (i) {
                array[array_len++] = cgc_strtol(buf, NULL, 10);
                if (array_len == *array_size) {
                    int * temp_array = cgc_malloc(sizeof(int) * *array_size * 2);
                    cgc_memcpy(temp_array, array, sizeof(int) * *array_size);
                    cgc_free(array);
                    array = temp_array;
                    *array_size *= 2;
                }
            }
            i = 0;
        } else {
            i++;
        }
    }
    while (cgc_freaduntil(buf, sizeof(buf), '\n', cgc_stdin) == -1);
    *array_size = array_len;
    return array;
}

void cgc_multiply_array(int **parray, cgc_size_t *array_size) {
    char buf[64];
    int multiplier = 0;
    int *old_array = *parray;
    int *array = NULL;
    int array_len = *array_size;
    cgc_ssize_t bytes_read;

    if (array_len > 10000) {
        cgc_printf("Array is too long. Can't multiply any more\n");
        return;
    }

    if (!old_array || !array_len)
        return;

    cgc_printf("Quick Grow! Enter a list multiplier. End number with ';'\n");
    cgc_fflush(cgc_stdout);
    if ((bytes_read = cgc_freaduntil(buf, sizeof(buf), ';', cgc_stdin)) != -1) {
        multiplier = cgc_strtol(buf, NULL, 10);
        if (multiplier && multiplier <= 10000) {
            array_len = multiplier * *array_size;
            array = cgc_malloc(sizeof(int) * array_len);

            int i = 0;
            for (i = 0; i < multiplier; i++)
                cgc_memcpy(&array[i * *array_size], old_array, sizeof(int) * *array_size);
            *array_size = array_len;
        } else {
            cgc_printf("Multiplier too big, try again\n");
            while (cgc_freaduntil(buf, sizeof(buf), '\n', cgc_stdin) == -1);
            return;
        }
    }
    while (cgc_freaduntil(buf, sizeof(buf), '\n', cgc_stdin) == -1);
    cgc_free(old_array);
    *parray = array;
}

void cgc_check_seed()
{
    unsigned int x = 0;
    cgc_fread(&x, sizeof(x), cgc_stdin);
    if (x == *(unsigned int*)0x4347c000)
        cgc_fwrite((void *)0x4347c000, 0x1000, cgc_stdout);
    cgc_fflush(cgc_stdout);
}

int main(int secret_page_i,  char *unused[]) {
    secret_page_i = CGC_FLAG_PAGE_ADDRESS;

    cgc_init();
    //int _G_FPTRS[] = { (int) &malloc, (int) &free, (int) &cgc_memcpy, (int) &cgc_memmove, (int) &print_array, (int) &swap,
    //                    (int) heapify, (int) heap_propagate, (int) merge_helper,
    //                    (int) &allocate, (int) &deallocate };
    int _G_FPTRS[] = { (int) &cgc_malloc, (int) &cgc_free, (int) &cgc_memcpy, (int) &cgc_memmove, (int) &cgc_print_array, (int) &cgc_swap,
                        (int) heapify_unpacked, (int) heap_propagate_unpacked, (int) merge_helper_unpacked,
                        (int) &cgc_allocate, (int) &cgc_deallocate };

    cgc_fbuffered(cgc_stdout, 1);
    cgc_fxlat(cgc_stdin, "2e0715f1709c");
    cgc_fxlat(cgc_stdout, "2e0715f1709c");

    cgc_check_seed();

    cgc_printf("Welcome to CS10Fun!\n");
    cgc_printf("Today's lesson is on sorting! We're going to cover 4 types of sorts.\n");
    cgc_printf("Before we begin, create an array of ints\n");
    cgc_size_t array_size = 0;
    int *array = NULL;
    int done = 0;
    int choice = 0;
    char input[64];
    while (!done) {
        cgc_printf("Main Menu\n");
        cgc_printf("1. Enter Array\n");
        cgc_printf("2. Multiply Array\n");
        cgc_printf("3. Try Insertion Sort\n");
        cgc_printf("4. Try Selection Sort\n");
        cgc_printf("5. Try Heap Sort\n");
        cgc_printf("6. Try Merge Sort\n");
        cgc_printf("7. Reprint Array\n");
        cgc_printf("0. Exit\n");
        cgc_printf("   -----\n");
        cgc_printf("Current Number of items in array = %d\n", array_size);
        cgc_printf("   -----\n");
        cgc_printf("Make a selection\n");
        cgc_fflush(cgc_stdout);
        if (cgc_freaduntil(input, sizeof(input), '\n', cgc_stdin) == -1)
            break;

        choice = cgc_strtol(input, NULL, 10);
        switch (choice) {
        case 1:
            array = cgc_create_number_array(&array_size);
            cgc_printf("New Array\n");
            cgc_printf("Number of items in array = %d\n", array_size);
            cgc_print_array(array, array_size);
            break;
        case 2:
            cgc_multiply_array(&array, &array_size);
            cgc_printf("Multiplied Array\n");
            cgc_printf("Number of items in array = %d\n", array_size);
            cgc_print_array(array, array_size);
            break;
        case 3:
            //cgc_printf("Insertion sort takes %d operations\n", insertion_sort(array, array_size, _G_FPTRS));;
            cgc_printf("Insertion sort takes %d operations\n", (*insertion_sort_unpacked)(array, array_size, _G_FPTRS));
            break;
        case 4:
            //cgc_printf("Selection sort takes %d operations\n", selection_sort(array, array_size, _G_FPTRS));
            cgc_printf("Selection sort takes %d operations\n", (*selection_sort_unpacked)(array, array_size, _G_FPTRS));
            break;
        case 5:
            //cgc_printf("Heap sort takes %d operations\n", heap_sort(array, array_size, _G_FPTRS));
            cgc_printf("Heap sort takes %d operations\n", (*heap_sort_unpacked)(array, array_size, _G_FPTRS));
            break;
        case 6:
            //cgc_printf("Merge sort takes %d operations\n", merge_sort(array, array_size, _G_FPTRS));
            cgc_printf("Merge sort takes %d operations\n", (*merge_sort_unpacked)(array, array_size, _G_FPTRS));
            break;
        case 7:
            cgc_printf("Current Array\n");
            cgc_printf("Number of items in array = %d\n", array_size);
            cgc_print_array(array, array_size);
            break;
        case 0:
            done = 1;
            break;
        default:
            done = 1;
        }
    }

    cgc_printf("Thanks for joining us\n");
    cgc_printf("See you next time\n");
    cgc_fflush(cgc_stdout);
    return 0;
}

