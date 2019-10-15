#ifndef LIST_H_
#define LIST_H_

#define MAX_LIST_SIZE 1024

extern "C"
{
#include "libcgc.h"
#include "cgc_stdlib.h"
#include "cgc_string.h"
};

template <typename T>
class List
{
private:
    T data[MAX_LIST_SIZE];
    cgc_size_t len;
public:
    List();
    ~List();
    int length();
    bool add(T item);
    bool remove(cgc_size_t idx);
    bool pop(T &item);
    bool is_empty();
    bool is_full();
    void print_list(void (*print_func)(void *));

    T operator[](cgc_size_t idx) const;
    T &operator[](cgc_size_t idx);

};

template <typename T>
List<T>::List()
{
    len = 0;
}

template <typename T>
List<T>::~List()
{
    len = 0;
}

template <typename T>
int List<T>::length()
{
    return len;
}

template <typename T>
bool List<T>::add(T item)
{
    if (len == MAX_LIST_SIZE)
        return false;

    data[len++] = item;
    return true;
}

template <typename T>
bool List<T>::remove(cgc_size_t idx)
{
    if (idx >= len)
        return false;

    cgc_memcpy(&data[idx], &data[idx+1], (len - idx) * sizeof(T));
    len--;
    return true;
}

template <typename T>
bool List<T>::pop(T &item)
{
    if (len == 0)
        return false;

    item = data[--len];
    return true;
}


template <typename T>
bool List<T>::is_empty()
{
    return (len == 0);
}

template <typename T>
bool List<T>::is_full()
{
    return (len == MAX_LIST_SIZE);
}

template <typename T>
T List<T>::operator[](cgc_size_t idx) const
{
    if (idx >= len)
        return data[0];

    return data[idx];
}

template <typename T>
T &List<T>::operator[](cgc_size_t idx)
{
    if (idx >= len)
        return data[len];

    return data[idx];
}

template <typename T>
void List<T>::print_list(void (*print_func)(void *))
{
    int i;
    for (i = 0; i < len; i++) {
        cgc_printf("\t%d. ", i+1);
        print_func(data[i]);
    }
}

#endif
