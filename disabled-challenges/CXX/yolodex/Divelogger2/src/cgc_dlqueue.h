/*

Author: Jason Williams <jdw@cromulence.com>

Copyright (c) 2014 Cromulence LLC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/
#ifndef __DLQUEUE_H__
#define __DLQUEUE_H__

class DLQueue;

class DLItem
{
public:
    DLItem( ) : m_pNext( NULL ), m_pPrev( NULL ) { };
    ~DLItem( ) { };

    DLItem *GetNext( void ) { return m_pNext; };
    DLItem *GetPrev( void ) { return m_pPrev; };

    friend class DLQueue;

private:
    DLItem *m_pNext;
    DLItem *m_pPrev;
};

class DLQueue
{
public:
    DLQueue( );
    ~DLQueue( );

    void DeleteAll( void );

    void AddFirst( DLItem *pItem );
    void AddLast( DLItem *pItem );
    void AddAfter( DLItem *pPrev, DLItem *pItem );

    void Unlink( DLItem *pItem );

    void DeleteItem( DLItem *pItem );
    void RemoveItem( DLItem *pItem );
    DLItem *RemoveFirst( void );
    DLItem *RemoveLast( void );

    DLItem *GetFirst( void ) { return m_pFirst; };
    DLItem *GetLast( void ) { return m_pLast; };

    cgc_size_t GetCount( void ) { return m_count; };

private:
    DLItem *m_pFirst;
    DLItem *m_pLast;
    cgc_size_t m_count;
};

#endif // __DLQUEUE_H___
