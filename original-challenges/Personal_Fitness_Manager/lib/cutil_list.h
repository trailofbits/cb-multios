/*

Copyright (c) 2016 Cromulence LLC

Authors: Jason Williams <jdw@cromulence.com>

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
#ifndef __CUTIL_LIST_H__
#define __CUTIL_LIST_H__

extern "C"
{
#include <stdint.h>
#include <libcgc.h>
#include <stddef.h>
}

#ifdef NULL
#undef NULL
#define NULL 0
#endif

// Cromulence Utilities Library
// Doubly linked list class

namespace CUtil
{
	// Easy means of declaring linked list data structures
#define DLL_LINK( T ) DoubleLink<T>
#define DLL_LIST( T, link ) DoubleListDeclare<T, offsetof( T, link )>
#define DLL_PTR( T ) DoubleList<T> *

	template<class T>
	class DoubleLink
	{
	public:
		DoubleLink();
		~DoubleLink();

		DoubleLink *GetNext( void ) { return m_pNext; };
		DoubleLink *GetPrev( void ) { return m_pPrev; };

		const DoubleLink* GetNext( void ) const { return m_pNext; };
		const DoubleLink* GetPrev( void ) const { return m_pPrev; };

		void Unlink( void );

	private:
		template<class U> friend class DoubleList;

		DoubleLink<T> *m_pNext;
		DoubleLink<T> *m_pPrev;
	};

	template<class T>
	class DoubleList
	{
	public:
		DoubleList();
		~DoubleList();

		void AddFirst( T *pItem );
		void AddLast( T *pItem );

		void AddAfter( T *pBefore, T *pItem );

		T *GetFirst( void );
		T *GetLast( void );

		T *RemoveFirst( void );
		T *RemoveLast( void );

		T *GetNext( T *pCur );
		T *GetPrev( T *pPrev );

		bool IsEmpty();

		// Delets all items (calls delete operator)
		void DeleteAll( void );

		// Clears the list items -- unlinks them but does not delete the elements!
		void ClearAll( void );

	private:
		DoubleList( uint32_t offset );

		template<class U, uint32_t linkOffset> friend class DoubleListDeclare;

		uint32_t m_listLinkOffset;	// Contains the offset for the list link member variable in the item class

		DoubleLink<T> m_first;
		DoubleLink<T> m_last;
	};

	template<class T, uint32_t linkOffset>
	class DoubleListDeclare : public DoubleList<T>
	{
	public:
		DoubleListDeclare();
	};

	// Declare a double list class with the appropriate link offset
	template<class T, uint32_t linkOffset>
	DoubleListDeclare<T, linkOffset>::DoubleListDeclare()
		: DoubleList<T>( linkOffset )
	{

	}

	template<class T>
	DoubleLink<T>::DoubleLink( )
	        : m_pNext( NULL ), m_pPrev( NULL )
	{

	}

	template<class T>
	DoubleLink<T>::~DoubleLink()
	{
		Unlink();
	}

	template<class T>
	void DoubleLink<T>::Unlink( void )
	{
	        if ( m_pPrev )
	                m_pPrev->m_pNext = m_pNext;

	        if ( m_pNext )
	                m_pNext->m_pPrev = m_pPrev;

		m_pNext = NULL;
		m_pPrev = NULL;	
	}

	template<class T>
	DoubleList<T>::DoubleList()
		: m_listLinkOffset( -1 )
	{
		m_first.m_pNext = &m_last;
		m_first.m_pPrev = NULL;

		m_last.m_pPrev = &m_first;
		m_last.m_pNext = NULL;
	}

	template<class T>
	DoubleList<T>::DoubleList( uint32_t offset )
		: m_listLinkOffset( offset )
	{
		m_first.m_pNext = &m_last;
		m_first.m_pPrev = NULL;

		m_last.m_pPrev = &m_first;
		m_last.m_pNext = NULL;
	}

	template<class T>
	DoubleList<T>::~DoubleList()
	{
	        DeleteAll();
	}

	template<class T>
	bool DoubleList<T>::IsEmpty( void )
	{
		return (m_first.m_pNext == &m_last);
	}

	template<class T>
	void DoubleList<T>::AddFirst( T *pItem )
	{
	        if ( !pItem )
	        	return;

		DoubleLink<T> *pItemLink = (DoubleLink<T> *)((uint8_t*)pItem + m_listLinkOffset);

		pItemLink->m_pNext = m_first.m_pNext;
		pItemLink->m_pPrev = &m_first;
	
		m_first.m_pNext->m_pPrev = pItemLink;	
		m_first.m_pNext = pItemLink;
	}

	template<class T>
	void DoubleList<T>::AddLast( T *pItem )
	{
		if ( !pItem )
	        	return;

		DoubleLink<T> *pItemLink = (DoubleLink<T> *)((uint8_t*)pItem + m_listLinkOffset);

		pItemLink->m_pNext = &m_last;
		pItemLink->m_pPrev = m_last.m_pPrev;

		m_last.m_pPrev->m_pNext = pItemLink;
		m_last.m_pPrev = pItemLink;
	}

	template<class T>
	void DoubleList<T>::AddAfter( T *pBefore, T *pItem )
	{
		if ( !pItem )
			return;

		if ( !pBefore )
		{
			AddFirst( pItem );
			return;
		}

		DoubleLink<T> *pBeforeLink = (DoubleLink<T> *)((uint8_t*)pBefore + m_listLinkOffset);
		DoubleLink<T> *pItemLink = (DoubleLink<T> *)((uint8_t*)pItem + m_listLinkOffset);

		pItemLink->m_pNext = pBeforeLink->m_pNext;
		pItemLink->m_pPrev = pBeforeLink;

		if ( pBeforeLink->m_pNext )
			pBeforeLink->m_pNext->m_pPrev = pItemLink;

		pBeforeLink->m_pNext = pItemLink;
	}

	template<class T>
	T *DoubleList<T>::GetFirst( void )
	{
		if ( m_first.m_pNext == &m_last )
			return (NULL);
		else
			return (T*)((uint8_t*)m_first.m_pNext - m_listLinkOffset);
	}

	template<class T>
	T *DoubleList<T>::GetLast( void )
	{
		if ( m_last.m_pPrev == &m_first )
			return (NULL);
		else
			return (T*)((uint8_t*)m_last.m_pPrev - m_listLinkOffset);
	}

	template<class T>
	T *DoubleList<T>::GetNext( T *pCur )
	{
		if ( pCur == NULL )
			return (NULL);

		DoubleLink<T> *pItemLink = (DoubleLink<T> *)((uint8_t*)pCur + m_listLinkOffset);
		DoubleLink<T> *pLink = pItemLink->GetNext();

		if ( pLink == &m_last )
			return (NULL);
		else
			return (T*)((uint8_t*)pLink - m_listLinkOffset);
	}

	template<class T>
	T *DoubleList<T>::GetPrev( T *pCur )
	{
		if ( pCur == NULL )
			return (NULL);

		DoubleLink<T> *pItemLink = (DoubleLink<T> *)((uint8_t*)pCur + m_listLinkOffset);
		DoubleLink<T> *pLink = pItemLink->GetPrev();

		if ( pLink == &m_first )
			return (NULL);
		else
			return (T*)((uint8_t*)pLink - m_listLinkOffset);
	}

	template<class T>
	T *DoubleList<T>::RemoveFirst( void )
	{
		if ( m_first.m_pNext == &m_last )
			return (NULL);
		else
		{
			T *pItem = (T*)((uint8_t*)m_first.m_pNext - m_listLinkOffset);

			m_first.m_pNext->Unlink();

			return (pItem);
		}
	}

	template<class T>
	T *DoubleList<T>::RemoveLast( void )
	{
		if ( m_last.m_pPrev == &m_first )
			return (NULL);
		else
		{
			T *pItem = (T*)((uint8_t*)m_last.m_pPrev - m_listLinkOffset);

			m_last.m_pPrev->Unlink();

			return (pItem);
		}
	}
				
	//         // Delets all items (calls delete operator)
	template<class T>
	void DoubleList<T>::DeleteAll( void )
	{
		while ( !IsEmpty() )
			delete GetFirst();
	}

	// Clears the list items -- unlinks them but does not delete the elements!
	template<class T>
	void DoubleList<T>::ClearAll( void )
	{
		while ( !IsEmpty() )
			m_first.m_pNext->Unlink();
	}
}

#endif // __CUTIL_LIST_H__
