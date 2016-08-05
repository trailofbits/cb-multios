#pragma once

#include <cstdlib.h>

template <class T>
class vector
{
  public:
    vector();
    vector(size_t sz);
    vector(const vector<T> &vec);
    ~vector();

    bool empty() const;
    size_t size() const;
    size_t capacity() const;
    T& front();
    T& back();
    void push_back(const T& val);
    void pop_back();
    void reserve(size_t cap);

    vector<T>& operator= (const vector<T> &vec);
    T& operator[] (unsigned int idx);
    void clear();

  private:
    size_t m_size;
    size_t m_capacity;
    T* m_data;
};

template<class T>
vector<T>::vector()
{
  m_capacity = 0;
  m_size = 0;
  m_data = 0;
}

template<class T>
vector<T>::vector(size_t sz)
{
  m_capacity = m_size = sz;
  m_data = new T[sz];
}

template<class T>
vector<T>::vector(const vector<T>& vec)
{
  m_capacity = vec.m_capacity;
  m_size = vec.m_size;
  m_data = new T[m_capacity];
  for (unsigned int i = 0; i < m_size; ++i)
    m_data[i] = vec.m_data[i];
}

template<class T>
vector<T>::~vector()
{
  delete[] m_data;
}

template<class T>
T& vector<T>::front()
{
  return m_data[0];
}

template<class T>
T& vector<T>::back()
{
  return m_data[m_size - 1];
}

template<class T>
void vector<T>::push_back(const T& val)
{
  if (m_capacity == 0)
    reserve(16);
  if (m_size == m_capacity)
    reserve(m_capacity * 2);
  m_data[m_size++] = val;
}

template<class T>
void vector<T>::reserve(size_t cap)
{
  T* d = new T[cap];
  for (unsigned int i = 0; i < m_size; ++i)
    d[i] = m_data[i];
  m_capacity = cap;
  if (m_data)
    delete[] m_data;
  m_data = d;
}

template<class T>
bool vector<T>::empty() const
{
  return m_size == 0;
}

template<class T>
size_t vector<T>::size() const
{
  return m_size;
}

template<class T>
size_t vector<T>::capacity() const
{
  return m_capacity;
}

template<class T>
T& vector<T>::operator[] (unsigned int idx)
{
  return m_data[idx];
}

template<class T>
vector<T>& vector<T>::operator= (const vector<T> &vec)
{
  if (m_data)
    delete[] m_data;
  m_size = vec.m_size;
  m_capacity = vec.m_capacity;
  m_data = new T[m_capacity];
  for (unsigned int i = 0; i < m_size; ++i)
    m_data[i] = vec.m_data[i];
  return *this;
}

template<class T>
void vector<T>::clear()
{
  m_capacity = 0;
  m_size = 0;
  if (m_data)
    delete[] m_data;
  m_data = 0;
}
