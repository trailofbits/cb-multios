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

CDoubleList::CDoubleList( ) :
    m_pFirst( NULL ), m_pLast( NULL )
{

}

CDoubleList::~CDoubleList( )
{
    DeleteAll();
}

void CDoubleList::DeleteAll( void )
{
    CDoubleListElement *pNext;
    CDoubleListElement *pCur;

    for ( pCur = m_pFirst; pCur; pCur = pNext )
    {
        pNext = pCur->GetNext();

        delete pCur;
    }

    m_pFirst = NULL;
    m_pLast = NULL;
}

void CDoubleList::InsertHead( CDoubleListElement *pItem )
{
    if ( pItem == NULL )
        return;

    if ( m_pFirst == NULL )
    {
        // Easy add in first
        m_pFirst = m_pLast = pItem;
        pItem->m_pNext = NULL;
        pItem->m_pPrev = NULL;
    }
    else
    {
        pItem->m_pPrev = NULL;
        pItem->m_pNext = m_pFirst;

        m_pFirst->m_pPrev = pItem;

        m_pFirst = pItem;
    }
}

void CDoubleList::InsertTail( CDoubleListElement *pItem )
{
    if ( pItem == NULL )
        return;

    if ( m_pLast == NULL )
    {
        // Easy add in first
        m_pLast = m_pFirst = pItem;
        pItem->m_pNext = NULL;
        pItem->m_pPrev = NULL;
    }
    else
    {
        pItem->m_pNext = NULL;
        pItem->m_pPrev = m_pLast;

        m_pLast->m_pNext = pItem;

        m_pLast = pItem;
    }
}

void CDoubleList::InsertAfter( CDoubleListElement *pBefore, CDoubleListElement *pItem )
{
    if ( pItem == NULL )
        return;

    if ( pBefore == NULL )
    {
        InsertHead( pItem );
        return;
    }

    if ( pBefore == m_pLast )
    {
        InsertTail( pItem );
    }
    else
    {
        pItem->m_pNext = pBefore->m_pNext;
        pItem->m_pPrev = pBefore;

        pBefore->m_pNext = pItem;

        if ( pItem->m_pNext )
            pItem->m_pNext->m_pPrev = pItem;
    }
}

void CDoubleList::Unlink( CDoubleListElement *pItem )
{
    if ( pItem == m_pFirst )
    {
        if ( m_pFirst == m_pLast )
            m_pFirst = m_pLast = NULL;
        else
        {
            m_pFirst = m_pFirst->m_pNext;
            m_pFirst->m_pPrev = NULL;
        }

        pItem->m_pNext = NULL;
        pItem->m_pPrev = NULL;
    }
    else if ( pItem == m_pLast )
    {
        if ( m_pFirst == m_pLast )
            m_pFirst = m_pLast = NULL;
        else
        {
            m_pLast = m_pLast->m_pPrev;
            m_pLast->m_pNext = NULL;
        }

        pItem->m_pNext = NULL;
        pItem->m_pPrev = NULL;
    }
    else
    {
        if ( pItem->m_pNext )
            pItem->m_pNext->m_pPrev = pItem->m_pPrev;

        if ( pItem->m_pPrev )
            pItem->m_pPrev->m_pNext = pItem->m_pNext;

        pItem->m_pNext = NULL;
        pItem->m_pPrev = NULL;
    }
}
