#ifndef ALGORITHM_H_
#define ALGORITHM_H_

namespace std
{
    template <typename T>
    inline const T &min (const T &a, const T &b)
    {
        if (a < b)
            return a;
        else
            return b;
    }

    template <typename T>
    inline const T &max (const T &a, const T &b)
    {
        if (a > b)
            return a;
        else
            return b;
    }

    template <typename T>
    inline const T&& move (const T &&a)
    {
        return a;
    }

    template <typename T>
    inline T&& move (T &&a)
    {
        return a;
    }

    template <typename T>
    inline void swap (T &a, T &b)
    {
        T tmp = move(a);
        a = move(b);
        b = move(tmp);
    }
};

#endif
