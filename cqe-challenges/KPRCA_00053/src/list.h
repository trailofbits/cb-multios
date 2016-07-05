#ifndef LIST_H_
#define LIST_H_

#define MAX_LIST_SIZE 50000

extern "C"
{
#include <libcgc.h>
};

template <typename T>
class List
{
private:
    struct node
    {
        node *next;
        node *prev;
        T data;
    };

    size_t len;
    node *head;
    node *tail;
public:
    List();
    ~List();
    int length();
    bool find(T item);
    bool add(T item);
    bool remove(size_t idx);
    bool pop(T &item);
    void clear_list(bool delete_memory=false);
    bool is_empty();

    T operator[](size_t idx) const;

};

template <typename T>
List<T>::List()
{
    len = 0;
    head = NULL;
    tail = NULL;
}

template <typename T>
List<T>::~List()
{
    len = 0;
    clear_list();
}

template <typename T>
int List<T>::length()
{
    return len;
}


template <typename T>
bool List<T>::find(T item)
{
    for (node *iter = head; iter; iter=iter->next) {
        if(iter->data == item)
            return true;
    }

    return false;
}

template <typename T>
bool List<T>::add(T item)
{
    node *new_node = new node;
    if (!new_node)
        return false;

    new_node->prev = tail;
    new_node->next = NULL;
    new_node->data = item;

    if(!head)
        head = new_node;
    if(tail)
        tail->next = new_node;

    tail = new_node;
    len++;
    return true;
}

template <typename T>
bool List<T>::remove(size_t idx)
{
    if (idx >= len || len == 0)
        return false;

    if (len == 1) {
        delete head;
        head = NULL;
        tail = NULL;

        len--;
        return true;
    }

    int i = 0;
    node *iter = NULL;
    for (iter = head; i != idx; iter=iter->next, i++);

    if (iter == head) {
        head = head->next;
        head->prev = NULL;
    } else if (iter == tail) {
        tail = tail->prev;
        tail->next = NULL;
    } else {
        iter->prev->next = iter->next;
        iter->next->prev = iter->prev;
    }

    delete iter;
    len--;
    return true;
}

template <typename T>
bool List<T>::pop(T &item)
{
    if (len == 0)
        return false;

    node *temp;
    item = tail->data;
    if (len == 1) {
        delete head;
        head = NULL;
        tail = NULL;
        return true;
    }

    temp = tail;
    tail = tail->prev;
    tail->next = NULL;

    delete temp;
    len--;
    return true;
}

template <typename T>
void List<T>::clear_list(bool delete_memory)
{
    T temp;
    while (pop(temp)) {
        if (delete_memory)
            delete temp;
    }
}

template <typename T>
bool List<T>::is_empty()
{
    return (len == 0);
}

template <typename T>
T List<T>::operator[](size_t idx) const
{
    if (idx >= len)
        return T();

    int i = 0;
    node *iter = NULL;
    for (iter = head; i != idx; iter=iter->next, i++);

    return iter->data;
}

#endif
