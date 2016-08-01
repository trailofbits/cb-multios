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
#include "common.h"

CDoubleItemList::CDoubleItemList( )
    : m_pFirst( NULL ), m_pLast( NULL )
{

}

CDoubleItemList::~CDoubleItemList( )
{
    DeleteAll();
}

void CDoubleItemList::DeleteAll( void )
{
    CDoubleItemLink *pNext;
    CDoubleItemLink *pCur;

    for ( pCur = m_pFirst; pCur; pCur = pNext )
    {
        pNext = pCur->m_pNext;

        // Delete entry
        delete pCur;

        pCur = pNext;
    }
}

CDoubleItemLink *CDoubleItemList::GetNext( CDoubleItemLink *pItem )
{
    if ( pItem->m_pList != this )
        return (NULL);

    return (pItem->m_pNext);
}

CDoubleItemLink *CDoubleItemList::GetPrev( CDoubleItemLink *pItem )
{
    if ( pItem->m_pList != this )
        return (NULL);

    return (pItem->m_pPrev);
}

CDoubleItemLink *CDoubleItemList::RemoveFirst( void )
{
    CDoubleItemLink *pItem = m_pFirst;

    RemoveItem( pItem );

    return (pItem);
}

CDoubleItemLink *CDoubleItemList::RemoveLast( void )
{
    CDoubleItemLink *pItem = m_pLast;

    RemoveItem( pItem );

    return (pItem);
}

CDoubleItemLink *CDoubleItemList::RemoveItem( CDoubleItemLink *pItem )
{
    // Check if item is in list...
    if ( pItem->m_pList != this )
        return (NULL);

    if ( pItem->m_pNext )
        pItem->m_pNext->m_pPrev = pItem->m_pPrev;

    if ( pItem->m_pPrev )
        pItem->m_pPrev->m_pNext = pItem->m_pNext;

    if ( pItem == m_pLast )
        m_pLast = pItem->m_pPrev;

    if ( pItem == m_pFirst )
        m_pFirst = pItem->m_pNext;

    // Remove our list pointer
    pItem->ClearList();

    return (pItem);
}

CDoubleItemLink *CDoubleItemList::AddFirst( CDoubleItemLink *pItem )
{
    if ( pItem == NULL )
        return (NULL);

    if ( pItem->m_pList != NULL )
        return (NULL);  // Already in a list!

    if ( m_pFirst == NULL )
    {
        // Empty list
        pItem->m_pPrev = NULL;
        pItem->m_pNext = NULL;

        m_pFirst = m_pLast = pItem;
    }
    else
    {
        pItem->m_pNext = m_pFirst;

        pItem->m_pPrev = NULL;
        m_pFirst->m_pPrev = pItem;

        m_pFirst = pItem;
    }

    // Item tracks what list it is in
    pItem->AddList( this );

    return (pItem);
}

CDoubleItemLink *CDoubleItemList::AddAfter( CDoubleItemLink *pPrev, CDoubleItemLink *pItem )
{
    // SANITY check
    if ( pItem == NULL )
        return (NULL);

    if ( pItem->m_pList != NULL )
        return (NULL);

    if ( pPrev == NULL )
        return (AddFirst( pItem ));

    if ( pPrev->m_pList != this )
        return (NULL);

    pItem->m_pNext = pPrev->m_pNext;
    pItem->m_pPrev = pPrev;

    if ( pPrev->m_pNext )
        pPrev->m_pNext->m_pPrev = pItem;

    pPrev->m_pNext = pItem;

    if ( m_pLast == pPrev )
        m_pLast = pItem;

    // Item tracks what list it is in
    pItem->AddList( this );

    return (pItem);
}

CDoubleItemLink *CDoubleItemList::AddLast( CDoubleItemLink *pItem )
{
    // SANITY check
    if ( pItem == NULL )
        return (NULL);

    if ( pItem->m_pList != NULL )
        return (NULL);  // Already in a list!

    if ( m_pLast == NULL )
    {
        // Empty list
        pItem->m_pNext = NULL;
        pItem->m_pPrev = NULL;

        m_pFirst = m_pLast = pItem;
    }
    else
    {
        pItem->m_pNext = NULL;
        pItem->m_pPrev = m_pLast;

        m_pLast->m_pNext = pItem;

        m_pLast = pItem;
    }

    // Item tracks what list it is in
    pItem->AddList( this );

    return (pItem);
}

CDoubleItemLink::CDoubleItemLink( )
    : m_pNext( NULL ), m_pPrev( NULL ), m_pList( NULL )
{

}

CDoubleItemLink::~CDoubleItemLink( )
{
    Unlink();
}

void CDoubleItemLink::Unlink( void )
{
    if ( m_pList == NULL )
        return;

    m_pList->RemoveItem( this );
}

CDoubleQueue::CDoubleQueue()
    : m_itemCount( 0 ), CDoubleItemList()
{

}

CDoubleQueue::~CDoubleQueue()
{

}
