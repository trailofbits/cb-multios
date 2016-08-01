/*

Author: James Connor (jymbo@cromulence.co)

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

#ifndef service_h
#define service_h
typedef struct DiveEntry_s {
	char SiteName[64];
	char DiveDate[32];
	char DiveTime[32];
	char DiveLocation[32];
	long int MaxDepth;
	long int AvgDepth;
	long int DiveDuration;
	long int O2;
	long int PressureIn;
	long int PressureOut;
	int Dive_BinCount;
} sDiveEntry, *pDiveEntry;

typedef struct DiveEntryListNode_s {
	struct DiveEntryListNode_s *prev;
	pDiveEntry DiveEntry;
	struct DiveEntryListNode_s *next;
} sDiveEntryListNode, *pDiveEntryListNode;

typedef struct DiverInfo_s {
	char FName[32];
	char LName[32];
	char Street[64];
	char City[32];
	char State[32];
	char Zip[32];
	char Phone[32];
	char PADINum[32];
	char PADIDate[32];
	pDiveEntryListNode DiveEntryList;
	int DiveEntryCount;
} sDiverInfo, *pDiverInfo;

pDiveEntry AddDive( pDiverInfo );
pDiveEntryListNode DeleteDive( pDiverInfo, pDiveEntryListNode );
void destroy_data( pDiverInfo );
#endif
