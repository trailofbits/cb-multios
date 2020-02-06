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
#ifndef __DOUBLE_QUEUE_H__
#define __DOUBLE_QUEUE_H__

class CDoubleItemLink;

class CDoubleItemList
{
public:
    CDoubleItemList();
    ~CDoubleItemList();

    void DeleteAll();

    CDoubleItemLink *GetFirst( void )
    {
        return (m_pFirst);
    }

    CDoubleItemLink *GetLast( void )
    {
        return (m_pLast);
    }

    CDoubleItemLink *GetNext( CDoubleItemLink *pItem );
    CDoubleItemLink *GetPrev( CDoubleItemLink *pItem );

    CDoubleItemLink *RemoveFirst( void );
    CDoubleItemLink *RemoveLast( void );

    CDoubleItemLink *RemoveItem( CDoubleItemLink *pItem );

    CDoubleItemLink *AddFirst( CDoubleItemLink *pItem );
    CDoubleItemLink *AddAfter( CDoubleItemLink *pPrev, CDoubleItemLink *pItem );
    CDoubleItemLink *AddLast( CDoubleItemLink *pItem );

protected:
    CDoubleItemLink *m_pFirst;
    CDoubleItemLink *m_pLast;
};

class CDoubleItemLink
{
friend class CDoubleItemList;

public:
    CDoubleItemLink();
    ~CDoubleItemLink();

    void Unlink( void );

private:
    void AddList( CDoubleItemList *pList )
    {
        m_pList = pList;
    }

    void ClearList( void )
    {
        m_pList = NULL;
    }

private:
    CDoubleItemLink *m_pNext;
    CDoubleItemLink *m_pPrev;
    CDoubleItemList *m_pList;
};

class CDoubleQueue : public CDoubleItemList
{
public:
    CDoubleQueue();
    ~CDoubleQueue();

    uint32_t GetCount( void ) const
    {
        return (m_itemCount);
    }

    CDoubleItemLink *PopFront( void )
    {
        CDoubleItemLink *pItem;

        if ( (pItem = RemoveFirst()) )
            m_itemCount--;

        return (pItem);
    }

    CDoubleItemLink *PopBack( void )
    {
        CDoubleItemLink *pItem;

        if ( (pItem = RemoveLast()) )
            m_itemCount--;

        return (pItem);
    }

    void PushFront( CDoubleItemLink *pItem )
    {
        if ( AddFirst( pItem ) )
            m_itemCount++;
    }

    void PushBack( CDoubleItemLink *pItem )
    {
        if ( AddLast( pItem ) )
            m_itemCount++;
    }

    CDoubleItemLink *GetFront( void )
    {
        return (m_pFirst);
    }

    CDoubleItemLink *GetBack( void )
    {
        return (m_pLast);
    }

    bool DeleteItem( CDoubleItemLink *pItem )
    {
        CDoubleItemLink *pRemovedItem = CDoubleItemList::RemoveItem( pItem );

        if ( pRemovedItem )
            m_itemCount--;
        else
            return (false);

        delete pItem;

        return (true);
    }
private:
    uint32_t m_itemCount;
};

#endif // __DOUBLE_QUEUE_H__
