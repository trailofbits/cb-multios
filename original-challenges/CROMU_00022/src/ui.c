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
#include <libcgc.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>
#include <mymath.h>
#include "service.h"
#include "ui.h"
#define DELIM 0x0A //\n
#define LONGSTRING 64
#define SHORTSTRING 32
#define MAXDIVECOUNT 128
#define MAXBINCOUNT 100000
#define NOVAL	-999999

int GetLongString(char pString[LONGSTRING]){
	bzero(pString,LONGSTRING);
	unsigned int result = receive_until_flush(pString, DELIM, LONGSTRING);
	if (result<LONGSTRING){
		pString[result] = 0x00;
	}
	pString[LONGSTRING-1] = 0x00;
	return result;
}

int GetShortString(char pString[SHORTSTRING]){
	bzero(pString,SHORTSTRING);
	unsigned int result = receive_until_flush(pString, DELIM, SHORTSTRING);
	if (result<SHORTSTRING){
		pString[result] = 0x00;
	}
	pString[SHORTSTRING-1] = 0x00;
	return result;
}

char GetChar(){
	char temp[2];
	receive_until_flush(temp, DELIM, 2);
	if (islower(temp[0])){
		temp[0] = temp[0]-0x20;
	}
	return temp[0];
}

long int GetInt(){
	char ctemp[32];
	memset(ctemp, 0, 32);

	int retval = 0;
	int len = receive_until_flush(ctemp, DELIM, 10);
	ctemp[len+1] = 0x00;
	retval = atoi( (const char*) ctemp );
	if ( len == 0 ){retval = NOVAL;}
	return retval;
}

long int GetPositiveInt(){
	//returns positive int or noval if no value entered
	long int retval = GetInt();
	if ( retval == NOVAL ){return NOVAL;}
	if ( retval < 0 ){retval = 0;}
	return retval;
}

void EpochToDate(int date[6], long int epoch){
	//date[0] month | date[1] day | date[2] year
	//date[3] hour | date[4] minute | date[5] second
	const int SinH = 3600; //60*60
	const int SinD = 86400; //60*60*24
	const int SinY = 31536000; //86400*365
	const int SinLY = 31622400; //86400*366
	int remainder = 0;
	int temp = 0;
	int count = 0;
	//if epoch is negative, bail. 
	if ( epoch < 0 ){
		date[0] = 0;
		return;
	}
	//year
	temp = epoch;
	while (temp >= 0){
		remainder = temp;
		if ( count%4 == 0 ) {
			temp = remainder - SinLY;
		}else{
			temp = remainder - SinY;
		}
		count += 1;
	}
	count -= 1;
	date[2] = ( 1970 + count );
	int	monthD[]={31,28,31,30,31,30,31,31,30,31,30,31};
	temp = remainder;
	if ( count%4 == 0 ){
		monthD[1]=28;
	}
	count = 0;
	int SinM = 0;
	while ( temp >=0 ){
		remainder = temp;
		SinM = (  86400 * ( monthD[count] )  ); 
		temp = remainder - SinM;
		count += 1;
	}
	date[0] = count;
	//day
	int day = ( remainder/SinD )+1;
	date[1] = day;
	//hour
	//no zero day, day is counted if partially complete, hours are counted after complete
	//ie first day is less than 24 hours after months starts,
	//hour 1 only happens after 60 minutes has passed
	remainder = (  remainder - ( SinD * (date[1]-1) )  );
	date[3] = ( remainder/SinH );
	//minute
	remainder = (  remainder - ( SinH * date[3] )  );
	date[4] = ( remainder/60 );
	//seconds
	date[5] = (  remainder - ( 60 * date[4] )  ); 
}


void MainMenu (pDiverInfo DiverInfo) {
	char result = 0x01;
	while (result == 0x01){			
		puts ("");
		puts ("C - Change Diver Info");
		puts ("L - Log a New Dive");
		puts ("D - Download Dive Data");	
		puts ("E - Edit Dives");	
		puts ("P - Print Dive Logs");	
		puts ("R - Remove Dives");
		puts ("S - Diver Statistics");
		puts ("X - Exit Application");
		printf (":");
		result = GetChar();
		switch (result){
			case Change_Diver_Info:
			ChangeDiverInfo(DiverInfo);
			result = 0x01;
			break;
			case Log_New_Dive:
			LogNewDive(DiverInfo);
			result = 0x01;
			break;
			case Download_Dive_Data:
			DownloadDiveData(DiverInfo);
			result = 0x01;
			break;
			case Edit_Dive:
			EditDive(DiverInfo);
			result = 0x01;
			break;
			case Print_Dive_Logs:
			PrintDiveLogs(DiverInfo);
			result = 0x01;
			break;
			case Remove_Dive:
			RemoveDive(DiverInfo);
			result = 0x01;
			break;
			case Diver_Statistics:
			DiverStatistics(DiverInfo);
			result = 0x01;
			break;
			case Exit:
			destroy_data(DiverInfo);
			break;
			default:
			result = 0x01;
			break;
		}
	}
	return;
}

void SetParam(char paramName[64], char *param, int len) {
	char temp[64];
	int result;
	if (!(strcmp(param, ""))) {
		printf("@s: ",paramName);
	}else {
		printf("@s (@s): ",paramName, param);
	}

	result = GetLongString(temp);
	if (result > 0){
		temp[len] = 0x00;
		strcpy(param, temp);
	}
	return;
}

void SetInt(char paramName[64], long int *param){
	//
	long int temp = 0;
	if ( *param == 0 ){
		printf("@s: ",paramName);
	}else{
		printf("@s (@d): ", paramName, *param);
	}
	temp = GetInt();
	if ( temp != NOVAL ){
			*param = temp;
	}
	return;
}

void PrintDiverInfo( pDiverInfo DiverInfo ){
	puts("");
	printf( "     Name: @s @s\n", 	DiverInfo->FName, DiverInfo->LName );
	printf( "  Address: @s\n", 		DiverInfo->Street);
	printf( "     City: @s\n", 		DiverInfo->City );
	printf( "    State: @s\n", 		DiverInfo->State );
	printf( " Zip Code: @s\n", 		DiverInfo->Zip );
	printf( "    Phone: @s\n", 		DiverInfo->Phone );
	printf( " PADI Num: @s\n", 		DiverInfo->PADINum );
	printf( "Cert Date: @s\n", 	DiverInfo->PADIDate );
	puts("");
}


void PrintDiveEntry( pDiveEntry DiveEntryNew ){
	puts("");
	printf( "          Date: @s\n",	DiveEntryNew->DiveDate    	);
	printf( "          Time: @s\n",	DiveEntryNew->DiveTime     	);
	printf( "     Dive Site: @s\n",	DiveEntryNew->SiteName 		);
	printf( "      Location: @s\n",	DiveEntryNew->DiveLocation	);
	printf( "     Max Depth: @d\n",	DiveEntryNew->MaxDepth		);
	printf( "     Avg Depth: @d\n",	DiveEntryNew->AvgDepth		);
	printf( "      Duration: @d\n",	DiveEntryNew->DiveDuration	);
	printf( "    O2 Percent: @d\n",	DiveEntryNew->O2			);
	printf( "Start Pressure: @d\n",	DiveEntryNew->PressureIn	);
	printf( "  End Pressure: @d\n",	DiveEntryNew->PressureOut	);
	printf( "     Bin Count: @d\n",	DiveEntryNew->Dive_BinCount );
	puts("");

}

void ChangeDiverInfo( pDiverInfo DiverInfo ) {
	puts("");
	SetParam( "First Name", 		DiverInfo->FName, 		20 );
	SetParam( "Last Name", 			DiverInfo->LName, 		20 );
	SetParam( "Street", 	 		DiverInfo->Street, 		29 );
	SetParam( "City",				DiverInfo->City, 		19 );
	SetParam( "State", 		 		DiverInfo->State, 		2 );
	SetParam( "Zip Code", 	 		DiverInfo->Zip, 		10 );
	SetParam( "Phone Number", 		DiverInfo->Phone, 		15 );
	SetParam( "PADI Diver Number", 	DiverInfo->PADINum, 	19 );
	SetParam( "PADI Cert Date", 	DiverInfo->PADIDate, 	10 );
	SanitizeDate( DiverInfo->PADIDate );
	PrintDiverInfo( DiverInfo );
	return;
} 

void LogNewDive( pDiverInfo DiverInfo ) {
	puts ("");
	if ( DiverInfo->DiveEntryCount < MAXDIVECOUNT ){
		pDiveEntry DiveEntryNew = AddDive(DiverInfo);
		ChangeDive( DiveEntryNew );
	}
	return;
}
void SanitizeDate(char date[32]){
	char tempDate[32];
	char *dayString = NULL;
	char *monthString = NULL;
	char *yearString = NULL;


	unsigned long int day = 0;
	unsigned long int month = 0;
	unsigned long int year = 0;
	int validDate = 0;
	bzero(tempDate, 32);
	monthString = date;

	if ( monthString !=NULL ) {
		dayString = strchr( monthString, '/' );
		if ( dayString != NULL ) {
			dayString++;
			yearString = strchr( dayString, '/');
			if ( yearString != NULL ){
				yearString++;
				month = atoi(monthString);
				day = atoi(dayString);
				year = atoi(yearString);
			}
		}
	}
	//sanity check date
	if (  ( year >= 1900 )&&( year <= 2100 )  ){
		if (  ( month >= 1 )&&( month <= 12 )  ){
			if ( month == 2 ){
				if (  ( year%4 == 0)&&( year != 1900 )  ){
					if (  ( day >= 1 )&&( day <= 29 )  ){
						validDate = 1;
					}
				}else {
					if (  ( day >= 1 )&&( day <= 28 )  ){
						validDate = 1;
					}
				}
			}else{
				if (  ( month == 4 )||( month == 6 )||( month == 9 )||( month == 11 )  ){
					if (  ( day >= 1 )&&( day <= 30 )  ){
						validDate = 1;
					}
				}else {
					if (  ( day >= 1 )&&( day <= 31 )  ){
						validDate = 1;
					}
				} 
			}
		}
	}
	//set date if valid, or set to 1/1/1900
	if ( validDate == 1 ){
		sprintf( tempDate, "@d/@d/@d",month, day, year );
	}else {
		sprintf( tempDate, "1/1/1900");
	}
	strcpy(date, tempDate);
	return;
}

void SanitizeTime( char timeString[32] ){
	char tempString[16];
	char *hourString = NULL;
	char *minuteString = NULL;
	char *secondString = NULL;

	int hour = 0;
	int minute = 0;
	int second = 0;
	int validTime = 0;

	hourString = timeString;
	if ( hourString != NULL ){
		minuteString = strchr(hourString, ':');
		if (minuteString != NULL ){
			minuteString++;
			secondString = strchr(minuteString, ':');
			if ( secondString != NULL ){
				secondString++;
				hour = atoi(hourString);
				minute = atoi(minuteString);
				second = atoi(secondString);
			}
		}
	}
#ifdef PATCHED
	//sanity check time
	if (  ( hour >= 0 )&&( hour <= 23 )  ){
		if (  ( minute >= 0 )&&( minute <= 59 )  ){
			if (  ( second >= 0)&&( second <= 59 )  ){
				validTime = 1;
			}
		}
	}
#endif
#ifndef PATCHED
	//sanity check time
	//CWE-839
	if ( hour <= 23 )  {
		if ( minute <= 59 ){
			if ( second <= 59 ){
				validTime = 1;
			}
		}
	}
#endif
	bzero(tempString, 16);

	if ( validTime == 1 ){
		sprintf( tempString, "@02d:@02d:@02d", hour, minute, second );
	}else {
		sprintf( tempString, "00:00:00");
	}
	strncpy( timeString, tempString, 16);
	return;
}

void SanitizeDiveEntry( pDiveEntry DiveEntryThis ){

	SanitizeDate( DiveEntryThis->DiveDate );
	SanitizeTime( DiveEntryThis->DiveTime );
	
	return;
}

void ChangeDive( pDiveEntry DiveEntryNew ) {
	SetParam( 	"Dive Site",					DiveEntryNew->SiteName,		25);
	SetParam( 	"Date",						DiveEntryNew->DiveDate, 	10);
	SetParam( 	"Time",						DiveEntryNew->DiveTime,		32);
	SetParam( 	"Location (area/city)", 	DiveEntryNew->DiveLocation,	25);
	SetInt( 	"Max Depth in ft",			&DiveEntryNew->MaxDepth );
	SetInt( 	"Avg Depth in ft",			&DiveEntryNew->AvgDepth );
	SetInt( 	"Dive Duration (mins)",		&DiveEntryNew->DiveDuration );
	SetInt( 	"O2 Percentage",			&DiveEntryNew->O2 );
	SetInt( 	"Pressure In (psi)",		&DiveEntryNew->PressureIn );
	SetInt( 	"Pressure Out (psi)",		&DiveEntryNew->PressureOut );
	SanitizeDiveEntry( DiveEntryNew );
	return;
}

unsigned long int GetUInt32(){
	//need a new reveive function because receive_until checks for delim byte
	//mostly borrowed from stdlib.c
    size_t rx = 0;
    unsigned long int val = 0;
    int ok = 0;
	ok = receive( STDIN, &val, sizeof(val), &rx ) ;
	if ( ( ok !=0 )||( rx == 0) )
		_terminate( -1 );
    return val;
}

void DownloadDiveData( pDiverInfo DiverInfo ){

#ifdef PATCHED
	//although technically not a bug, it enables the bug. CWE-787
	if ( DiverInfo->DiveEntryCount >= MAXDIVECOUNT ){
		return;
	}
#endif

	pDiveEntry DiveEntryNew = AddDive(DiverInfo);

	unsigned long int timeS = 0;
	unsigned long int depthS = 0;
	unsigned long int avgDepth = 0;
	unsigned long int maxDepth = 0;
	unsigned long int lowestTime = 0;
	unsigned long int highestTime = 0;
	unsigned long int depthSum = 0;
	unsigned long int count = 0;
	int date[6] = {0,0,0,0,0,0};
	puts("");

	timeS = GetUInt32();
	depthS = GetUInt32();
	lowestTime = timeS;
	highestTime = timeS;
	maxDepth = depthS;
	depthSum = depthS;

	count = 1;

	while (  ( timeS != 0 )&&( count < MAXBINCOUNT )  ){
		timeS = GetUInt32();
		if ( timeS != 0 ){
			depthS = GetUInt32();

			if ( depthS > 3000 ){
				depthS = 3000;
			}

			count += 1;	
			depthSum += depthS;
			if ( timeS < lowestTime ){
				lowestTime = timeS;
			}
			if ( timeS > highestTime ){
				highestTime = timeS;
			}
			if ( depthS > maxDepth ){
				maxDepth = depthS;
			}
		}
	}
	EpochToDate(date, (long int)lowestTime);
	//maxDepth, avgDepth, diveDuration
	DiveEntryNew->MaxDepth = maxDepth;
	DiveEntryNew->DiveDuration = ( ( highestTime - lowestTime )/60 );
	DiveEntryNew->AvgDepth = ( depthSum/count );
	DiveEntryNew->Dive_BinCount = count;
	sprintf( DiveEntryNew->DiveDate, "@d/@d/@d",date[0],date[1],date[2] );
	sprintf( DiveEntryNew->DiveTime, "@02d:@02d:@02d",date[3],date[4],date[5] );  
	ChangeDive( DiveEntryNew );
	return;	
}

pDiveEntryListNode SelectDive( pDiverInfo DiverInfo, char prompt[32] ){
	pDiveEntryListNode DiveEntryListThis = DiverInfo->DiveEntryList;
	pDiveEntry DiveEntryThis = NULL;
	unsigned int count = 0;
	pDiveEntryListNode list[MAXDIVECOUNT];
	long int selection = 0;
	if ( DiveEntryListThis == NULL ){
		printf("\n\nDive Log is empty\n");
		return NULL;
	}
	printf("\n\nDive# Date       Time     Dive Site                 Location                 \n");
#ifdef PATCHED
	while (  ( DiveEntryListThis != NULL )&&( count < MAXDIVECOUNT )  ){
#endif
#ifndef PATCHED
	//CWE-787 
	while (  ( DiveEntryListThis != NULL )&&( count <= MAXDIVECOUNT )  ){
#endif

		DiveEntryThis = DiveEntryListThis->DiveEntry;
		//129th pointer is written over count
		list[count] = DiveEntryListThis;		
		//count is incremented, count now points 1 bytes after start of DiveEntryList_s
		count += 1;
		printf("@4d: @-10s @-8s",count, DiveEntryThis->DiveDate, DiveEntryThis->DiveTime);
		printf(" @-25s @-25s\n", DiveEntryThis->SiteName, DiveEntryThis->DiveLocation );
		//DiveEntryListThis is ++, but doesn't matter because exit loop on count which is most certainly
		//greater then MAXDIVECOUNT 
		DiveEntryListThis = DiveEntryListThis->next;
	}
	printf("@s",prompt);
	selection = GetPositiveInt();
	//smashing count lets you select large int, and read past maloc in list[selection];
	//controllable by editing dive if count is selected to point to place to arbitrary write
	if (  (selection >= 1 )&&( selection <= count )  ){
		DiveEntryListThis = list[selection-1];
	}else {
		printf("Invalid dive number entered\n");
		DiveEntryListThis = NULL;
	}
	return DiveEntryListThis;
}

void EditDive( pDiverInfo DiverInfo ){
	pDiveEntryListNode DiveEntryListThis = SelectDive( DiverInfo, "\nEnter Dive # to edit: " );
	if ( DiveEntryListThis != NULL ){
		pDiveEntry DiveEntryThis = DiveEntryListThis->DiveEntry;
		puts("");
		ChangeDive( DiveEntryThis );
	}
	return;
}

void PrintDiveLogs( pDiverInfo DiverInfo ){
	pDiveEntryListNode DiveEntryListThis = SelectDive( DiverInfo, "\nEnter Dive # to display: " );
	if ( DiveEntryListThis !=  NULL ){
		pDiveEntry DiveEntryThis = DiveEntryListThis->DiveEntry;
		PrintDiveEntry( DiveEntryThis );
	}
	return;
}

void RemoveDive( pDiverInfo DiverInfo ){
	pDiveEntryListNode DiveEntryListThis = SelectDive( DiverInfo, "\nEnter Dive # to delete or blank to abort: " );
	if ( DiveEntryListThis != NULL ){
		pDiveEntryListNode prev = DeleteDive( DiverInfo, DiveEntryListThis );
	}
	return;
}

void DiverStatistics( pDiverInfo DiverInfo ){
	puts("");
	pDiveEntryListNode DiveEntryListThis = DiverInfo->DiveEntryList;
	pDiveEntry DiveEntryThis = NULL;
	long int count = 0;
	long int maxSum = 0;
	long int lengthSum = 0; 
	if ( DiveEntryListThis == NULL ){
		printf("\nDive Log is empty\n");
		return;
	}
	while ( DiveEntryListThis != NULL ){
		DiveEntryThis = DiveEntryListThis->DiveEntry;
		count += 1;
		maxSum = maxSum + DiveEntryThis->MaxDepth;
		lengthSum = lengthSum + DiveEntryThis->DiveDuration;
		DiveEntryListThis = DiveEntryListThis->next;
	}	
	maxSum = maxSum/count;
	lengthSum = lengthSum/count;
	printf("\nDives logged: @d\n",count);
	printf("Average Max Depth: @d\n",maxSum);
	printf("Average Dive Length: @d\n",lengthSum);
	return;
}

