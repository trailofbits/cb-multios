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

DLQueue::DLQueue( )
    : m_pFirst( NULL ), m_pLast( NULL ), m_count( 0 )
{

}

DLQueue::~DLQueue( )
{
    DeleteAll();
}

void DLQueue::AddFirst( DLItem *pItem )
{
    if ( pItem == NULL )
        return;

    if ( m_pFirst == NULL )
    {
        pItem->m_pNext = NULL;
        pItem->m_pPrev = NULL;

        m_pFirst = pItem;
        m_pLast = pItem;
    }
    else
    {
        pItem->m_pNext = m_pFirst;
        pItem->m_pPrev = NULL;

        m_pFirst->m_pPrev = pItem;

        m_pFirst = pItem;
    }

    // Increment count
    m_count++;
}

void DLQueue::AddLast( DLItem *pItem )
{
    if ( pItem == NULL )
        return;

    if ( m_pLast == NULL )
    {
        pItem->m_pNext = NULL;
        pItem->m_pPrev = NULL;

        m_pFirst = pItem;
        m_pLast = pItem;
    }
    else
    {
        pItem->m_pNext = NULL;
        pItem->m_pPrev = m_pLast;

        m_pLast->m_pNext = pItem;

        m_pLast = pItem;
    }

    // Increment count
    m_count++;
}

void DLQueue::AddAfter( DLItem *pPrev, DLItem *pItem )
{
    if ( pPrev == NULL || pItem == NULL )
        return;

    pItem->m_pNext = pPrev->m_pNext;
    pItem->m_pPrev = pPrev;

    if ( pPrev->m_pNext )
        pPrev->m_pNext->m_pPrev = pItem;

    pPrev->m_pNext = pItem;

    if ( m_pLast == pPrev )
        m_pLast = pItem;

    // Increment count
    m_count++;
}

void DLQueue::Unlink( DLItem *pItem )
{
    if ( pItem->m_pNext )
        pItem->m_pNext->m_pPrev = pItem->m_pPrev;

    if ( pItem->m_pPrev )
        pItem->m_pPrev->m_pNext = pItem->m_pNext;

    if ( m_pFirst == pItem )
        m_pFirst = pItem->m_pNext;

    if ( m_pLast == pItem )
        m_pLast = pItem->m_pPrev;

    m_count--;
}

void DLQueue::DeleteItem( DLItem *pItem )
{
    Unlink( pItem );

    delete pItem;
}

void DLQueue::RemoveItem( DLItem *pItem )
{
    Unlink( pItem );
}

DLItem *DLQueue::RemoveFirst( void )
{
    DLItem *pItem = m_pFirst;
    Unlink( pItem );

    return (pItem);
}

DLItem *DLQueue::RemoveLast( void )
{
    DLItem *pItem = m_pLast;
    Unlink( pItem );

    return (pItem);
}

void DLQueue::DeleteAll( void )
{
    // Fast delete all items
    DLItem *pCur = m_pFirst;
    DLItem *pNext = NULL;

    for ( ; pCur; pCur = pNext )
    {
        pNext = pCur->m_pNext;

        delete pCur;
    }

    m_count = 0;
    m_pFirst = m_pLast = NULL;
}
