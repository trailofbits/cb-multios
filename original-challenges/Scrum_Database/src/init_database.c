/*

Author: Steve Wood <swood@cromulence.com>

Copyright (c) 2015 Cromulence LLC

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

#include <libcgc.h>
#include "stdlib.h"
#include "service.h"
#include "stdio.h"
#include "string.h"
#include "malloc.h"

int init_database( productDefType **database ) {


	productDefType *pTemp;

	pTemp = *database;


	if (pTemp == 0) {

		pTemp = malloc(sizeof(productDefType));

		if (pTemp == 0) 
			_terminate(-1);

	}

	return 0;

}


int destroy_database ( productDefType **database ) {

productDefType *productPtr, *tmpProduct;
sprintEntryType *sprintPtr, *tmpSprintPtr;
backlogItemType *pblPtr, *tmpPBIPtr;
backlogItemType *sblPtr, *tmpSBLPtr;


	productPtr = *database;

	while (productPtr != 0) {

		pblPtr = productPtr->productBacklog;

		// first delete the product backlog
		while( pblPtr != 0) {


			if (pblPtr->description != 0)
				free(pblPtr->description);

			tmpPBIPtr = pblPtr;

			pblPtr = pblPtr->next;

			free(tmpPBIPtr);

		}


		sprintPtr = productPtr->sprintList;

		while ( sprintPtr != 0) {

			sblPtr = sprintPtr->sprintBacklogList;

			while ( sblPtr != 0) {


				if (sblPtr->description != 0)
					free(sblPtr->description);

				tmpSBLPtr = sblPtr;
				sblPtr = sblPtr->next;

				free(tmpSBLPtr);

			}

			if (sprintPtr->title != 0 ) 
				free(sprintPtr->title);

			tmpSprintPtr = sprintPtr;
			sprintPtr = sprintPtr->next;

			free(tmpSprintPtr);


		}

		if (productPtr->title != 0)
			free(productPtr->title);

		tmpProduct = productPtr;
		productPtr = productPtr->next;

		free(tmpProduct);


	}

	*database = 0;

	return 0;

}
