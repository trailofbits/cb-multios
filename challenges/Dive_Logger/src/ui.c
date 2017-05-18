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
#include "libcgc.h"
#include "cgc_stdarg.h"
#include "cgc_stdlib.h"
#include "cgc_stdint.h"
#include "cgc_mymath.h"
#include "cgc_service.h"
#include "cgc_ui.h"
#define DELIM 0x0A //\n
#define LONGSTRING 64
#define SHORTSTRING 32
#define MAXDIVECOUNT 128
#define MAXBINCOUNT 100000
#define NOVAL	-999999

int cgc_GetLongString(char pString[LONGSTRING]){
	cgc_bzero(pString,LONGSTRING);
	unsigned int result = cgc_receive_until_flush(pString, DELIM, LONGSTRING);
	if (result<LONGSTRING){
		pString[result] = 0x00;
	}
	pString[LONGSTRING-1] = 0x00;
	return result;
}

int cgc_GetShortString(char pString[SHORTSTRING]){
	cgc_bzero(pString,SHORTSTRING);
	unsigned int result = cgc_receive_until_flush(pString, DELIM, SHORTSTRING);
	if (result<SHORTSTRING){
		pString[result] = 0x00;
	}
	pString[SHORTSTRING-1] = 0x00;
	return result;
}

char cgc_GetChar(){
	char temp[2];
	cgc_receive_until_flush(temp, DELIM, 2);
	if (cgc_islower(temp[0])){
		temp[0] = temp[0]-0x20;
	}
	return temp[0];
}

long int cgc_GetInt(){
	char ctemp[32];
	cgc_memset(ctemp, 0, 32);

	int retval = 0;
	int len = cgc_receive_until_flush(ctemp, DELIM, 10);
	ctemp[len+1] = 0x00;
	retval = cgc_atoi( (const char*) ctemp );
	if ( len == 0 ){retval = NOVAL;}
	return retval;
}

long int cgc_GetPositiveInt(){
	//returns positive int or noval if no value entered
	long int retval = cgc_GetInt();
	if ( retval == NOVAL ){return NOVAL;}
	if ( retval < 0 ){retval = 0;}
	return retval;
}

void cgc_EpochToDate(int date[6], long int epoch){
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


void cgc_MainMenu (pDiverInfo DiverInfo) {
	char result = 0x01;
	while (result == 0x01){			
		cgc_puts ("");
		cgc_puts ("C - Change Diver Info");
		cgc_puts ("L - Log a New Dive");
		cgc_puts ("D - Download Dive Data");	
		cgc_puts ("E - Edit Dives");	
		cgc_puts ("P - Print Dive Logs");	
		cgc_puts ("R - Remove Dives");
		cgc_puts ("S - Diver Statistics");
		cgc_puts ("X - Exit Application");
		cgc_printf (":");
		result = cgc_GetChar();
		switch (result){
			case Change_Diver_Info:
			cgc_ChangeDiverInfo(DiverInfo);
			result = 0x01;
			break;
			case Log_New_Dive:
			cgc_LogNewDive(DiverInfo);
			result = 0x01;
			break;
			case Download_Dive_Data:
			cgc_DownloadDiveData(DiverInfo);
			result = 0x01;
			break;
			case Edit_Dive:
			cgc_EditDive(DiverInfo);
			result = 0x01;
			break;
			case Print_Dive_Logs:
			cgc_PrintDiveLogs(DiverInfo);
			result = 0x01;
			break;
			case Remove_Dive:
			cgc_RemoveDive(DiverInfo);
			result = 0x01;
			break;
			case Diver_Statistics:
			cgc_DiverStatistics(DiverInfo);
			result = 0x01;
			break;
			case Exit:
			cgc_destroy_data(DiverInfo);
			break;
			default:
			result = 0x01;
			break;
		}
	}
	return;
}

void cgc_SetParam(char paramName[64], char *param, int len) {
	char temp[64];
	int result;
	if (!(cgc_strcmp(param, ""))) {
		cgc_printf("@s: ",paramName);
	}else {
		cgc_printf("@s (@s): ",paramName, param);
	}

	result = cgc_GetLongString(temp);
	if (result > 0){
		temp[len] = 0x00;
		cgc_strcpy(param, temp);
	}
	return;
}

void cgc_SetInt(char paramName[64], long int *param){
	//
	long int temp = 0;
	if ( *param == 0 ){
		cgc_printf("@s: ",paramName);
	}else{
		cgc_printf("@s (@d): ", paramName, *param);
	}
	temp = cgc_GetInt();
	if ( temp != NOVAL ){
			*param = temp;
	}
	return;
}

void cgc_PrintDiverInfo( pDiverInfo DiverInfo ){
	cgc_puts("");
	cgc_printf( "     Name: @s @s\n", 	DiverInfo->FName, DiverInfo->LName );
	cgc_printf( "  Address: @s\n", 		DiverInfo->Street);
	cgc_printf( "     City: @s\n", 		DiverInfo->City );
	cgc_printf( "    State: @s\n", 		DiverInfo->State );
	cgc_printf( " Zip Code: @s\n", 		DiverInfo->Zip );
	cgc_printf( "    Phone: @s\n", 		DiverInfo->Phone );
	cgc_printf( " PADI Num: @s\n", 		DiverInfo->PADINum );
	cgc_printf( "Cert Date: @s\n", 	DiverInfo->PADIDate );
	cgc_puts("");
}


void cgc_PrintDiveEntry( pDiveEntry DiveEntryNew ){
	cgc_puts("");
	cgc_printf( "          Date: @s\n",	DiveEntryNew->DiveDate    	);
	cgc_printf( "          Time: @s\n",	DiveEntryNew->DiveTime     	);
	cgc_printf( "     Dive Site: @s\n",	DiveEntryNew->SiteName 		);
	cgc_printf( "      Location: @s\n",	DiveEntryNew->DiveLocation	);
	cgc_printf( "     Max Depth: @d\n",	DiveEntryNew->MaxDepth		);
	cgc_printf( "     Avg Depth: @d\n",	DiveEntryNew->AvgDepth		);
	cgc_printf( "      Duration: @d\n",	DiveEntryNew->DiveDuration	);
	cgc_printf( "    O2 Percent: @d\n",	DiveEntryNew->O2			);
	cgc_printf( "Start Pressure: @d\n",	DiveEntryNew->PressureIn	);
	cgc_printf( "  End Pressure: @d\n",	DiveEntryNew->PressureOut	);
	cgc_printf( "     Bin Count: @d\n",	DiveEntryNew->Dive_BinCount );
	cgc_puts("");

}

void cgc_ChangeDiverInfo( pDiverInfo DiverInfo ) {
	cgc_puts("");
	cgc_SetParam( "First Name", 		DiverInfo->FName, 		20 );
	cgc_SetParam( "Last Name", 			DiverInfo->LName, 		20 );
	cgc_SetParam( "Street", 	 		DiverInfo->Street, 		29 );
	cgc_SetParam( "City",				DiverInfo->City, 		19 );
	cgc_SetParam( "State", 		 		DiverInfo->State, 		2 );
	cgc_SetParam( "Zip Code", 	 		DiverInfo->Zip, 		10 );
	cgc_SetParam( "Phone Number", 		DiverInfo->Phone, 		15 );
	cgc_SetParam( "PADI Diver Number", 	DiverInfo->PADINum, 	19 );
	cgc_SetParam( "PADI Cert Date", 	DiverInfo->PADIDate, 	10 );
	cgc_SanitizeDate( DiverInfo->PADIDate );
	cgc_PrintDiverInfo( DiverInfo );
	return;
} 

void cgc_LogNewDive( pDiverInfo DiverInfo ) {
	cgc_puts ("");
	if ( DiverInfo->DiveEntryCount < MAXDIVECOUNT ){
		pDiveEntry DiveEntryNew = cgc_AddDive(DiverInfo);
		cgc_ChangeDive( DiveEntryNew );
	}
	return;
}
void cgc_SanitizeDate(char date[32]){
	char tempDate[32];
	char *dayString = NULL;
	char *monthString = NULL;
	char *yearString = NULL;


	unsigned long int day = 0;
	unsigned long int month = 0;
	unsigned long int year = 0;
	int validDate = 0;
	cgc_bzero(tempDate, 32);
	monthString = date;

	if ( monthString !=NULL ) {
		dayString = cgc_strchr( monthString, '/' );
		if ( dayString != NULL ) {
			dayString++;
			yearString = cgc_strchr( dayString, '/');
			if ( yearString != NULL ){
				yearString++;
				month = cgc_atoi(monthString);
				day = cgc_atoi(dayString);
				year = cgc_atoi(yearString);
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
		cgc_sprintf( tempDate, "@d/@d/@d",month, day, year );
	}else {
		cgc_sprintf( tempDate, "1/1/1900");
	}
	cgc_strcpy(date, tempDate);
	return;
}

void cgc_SanitizeTime( char timeString[32] ){
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
		minuteString = cgc_strchr(hourString, ':');
		if (minuteString != NULL ){
			minuteString++;
			secondString = cgc_strchr(minuteString, ':');
			if ( secondString != NULL ){
				secondString++;
				hour = cgc_atoi(hourString);
				minute = cgc_atoi(minuteString);
				second = cgc_atoi(secondString);
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
	cgc_bzero(tempString, 16);

	if ( validTime == 1 ){
		cgc_sprintf( tempString, "@02d:@02d:@02d", hour, minute, second );
	}else {
		cgc_sprintf( tempString, "00:00:00");
	}
	cgc_strncpy( timeString, tempString, 16);
	return;
}

void cgc_SanitizeDiveEntry( pDiveEntry DiveEntryThis ){

	cgc_SanitizeDate( DiveEntryThis->DiveDate );
	cgc_SanitizeTime( DiveEntryThis->DiveTime );
	
	return;
}

void cgc_ChangeDive( pDiveEntry DiveEntryNew ) {
	cgc_SetParam( 	"Dive Site",					DiveEntryNew->SiteName,		25);
	cgc_SetParam( 	"Date",						DiveEntryNew->DiveDate, 	10);
	cgc_SetParam( 	"Time",						DiveEntryNew->DiveTime,		32);
	cgc_SetParam( 	"Location (area/city)", 	DiveEntryNew->DiveLocation,	25);
	cgc_SetInt( 	"Max Depth in ft",			&DiveEntryNew->MaxDepth );
	cgc_SetInt( 	"Avg Depth in ft",			&DiveEntryNew->AvgDepth );
	cgc_SetInt( 	"Dive Duration (mins)",		&DiveEntryNew->DiveDuration );
	cgc_SetInt( 	"O2 Percentage",			&DiveEntryNew->O2 );
	cgc_SetInt( 	"Pressure In (psi)",		&DiveEntryNew->PressureIn );
	cgc_SetInt( 	"Pressure Out (psi)",		&DiveEntryNew->PressureOut );
	cgc_SanitizeDiveEntry( DiveEntryNew );
	return;
}

unsigned long int cgc_GetUInt32(){
	//need a new reveive function because receive_until checks for delim byte
	//mostly borrowed from stdlib.c
    cgc_size_t rx = 0;
    unsigned long int val = 0;
    int ok = 0;
	ok = cgc_receive( STDIN, &val, sizeof(val), &rx ) ;
	if ( ( ok !=0 )||( rx == 0) )
		cgc__terminate( -1 );
    return val;
}

void cgc_DownloadDiveData( pDiverInfo DiverInfo ){

#ifdef PATCHED
	//although technically not a bug, it enables the bug. CWE-787
	if ( DiverInfo->DiveEntryCount >= MAXDIVECOUNT ){
		return;
	}
#endif

	pDiveEntry DiveEntryNew = cgc_AddDive(DiverInfo);

	unsigned long int timeS = 0;
	unsigned long int depthS = 0;
	unsigned long int avgDepth = 0;
	unsigned long int maxDepth = 0;
	unsigned long int lowestTime = 0;
	unsigned long int highestTime = 0;
	unsigned long int depthSum = 0;
	unsigned long int count = 0;
	int date[6] = {0,0,0,0,0,0};
	cgc_puts("");

	timeS = cgc_GetUInt32();
	depthS = cgc_GetUInt32();
	lowestTime = timeS;
	highestTime = timeS;
	maxDepth = depthS;
	depthSum = depthS;

	count = 1;

	while (  ( timeS != 0 )&&( count < MAXBINCOUNT )  ){
		timeS = cgc_GetUInt32();
		if ( timeS != 0 ){
			depthS = cgc_GetUInt32();

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
	cgc_EpochToDate(date, (long int)lowestTime);
	//maxDepth, avgDepth, diveDuration
	DiveEntryNew->MaxDepth = maxDepth;
	DiveEntryNew->DiveDuration = ( ( highestTime - lowestTime )/60 );
	DiveEntryNew->AvgDepth = ( depthSum/count );
	DiveEntryNew->Dive_BinCount = count;
	cgc_sprintf( DiveEntryNew->DiveDate, "@d/@d/@d",date[0],date[1],date[2] );
	cgc_sprintf( DiveEntryNew->DiveTime, "@02d:@02d:@02d",date[3],date[4],date[5] );  
	cgc_ChangeDive( DiveEntryNew );
	return;	
}

pDiveEntryListNode cgc_SelectDive( pDiverInfo DiverInfo, char prompt[32] ){
	pDiveEntryListNode DiveEntryListThis = DiverInfo->DiveEntryList;
	pDiveEntry DiveEntryThis = NULL;
	unsigned int count = 0;
	pDiveEntryListNode list[MAXDIVECOUNT];
	long int selection = 0;
	if ( DiveEntryListThis == NULL ){
		cgc_printf("\n\nDive Log is empty\n");
		return NULL;
	}
	cgc_printf("\n\nDive# Date       Time     Dive Site                 Location                 \n");
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
		cgc_printf("@4d: @-10s @-8s",count, DiveEntryThis->DiveDate, DiveEntryThis->DiveTime);
		cgc_printf(" @-25s @-25s\n", DiveEntryThis->SiteName, DiveEntryThis->DiveLocation );
		//DiveEntryListThis is ++, but doesn't matter because cgc_exit loop on count which is most certainly
		//greater then MAXDIVECOUNT 
		DiveEntryListThis = DiveEntryListThis->next;
	}
	cgc_printf("@s",prompt);
	selection = cgc_GetPositiveInt();
	//smashing count lets you cgc_select large int, and cgc_read past maloc in list[selection];
	//controllable by editing dive if count is selected to point to place to arbitrary cgc_write
	if (  (selection >= 1 )&&( selection <= count )  ){
		DiveEntryListThis = list[selection-1];
	}else {
		cgc_printf("Invalid dive number entered\n");
		DiveEntryListThis = NULL;
	}
	return DiveEntryListThis;
}

void cgc_EditDive( pDiverInfo DiverInfo ){
	pDiveEntryListNode DiveEntryListThis = cgc_SelectDive( DiverInfo, "\nEnter Dive # to edit: " );
	if ( DiveEntryListThis != NULL ){
		pDiveEntry DiveEntryThis = DiveEntryListThis->DiveEntry;
		cgc_puts("");
		cgc_ChangeDive( DiveEntryThis );
	}
	return;
}

void cgc_PrintDiveLogs( pDiverInfo DiverInfo ){
	pDiveEntryListNode DiveEntryListThis = cgc_SelectDive( DiverInfo, "\nEnter Dive # to display: " );
	if ( DiveEntryListThis !=  NULL ){
		pDiveEntry DiveEntryThis = DiveEntryListThis->DiveEntry;
		cgc_PrintDiveEntry( DiveEntryThis );
	}
	return;
}

void cgc_RemoveDive( pDiverInfo DiverInfo ){
	pDiveEntryListNode DiveEntryListThis = cgc_SelectDive( DiverInfo, "\nEnter Dive # to delete or blank to abort: " );
	if ( DiveEntryListThis != NULL ){
		pDiveEntryListNode prev = cgc_DeleteDive( DiverInfo, DiveEntryListThis );
	}
	return;
}

void cgc_DiverStatistics( pDiverInfo DiverInfo ){
	cgc_puts("");
	pDiveEntryListNode DiveEntryListThis = DiverInfo->DiveEntryList;
	pDiveEntry DiveEntryThis = NULL;
	long int count = 0;
	long int maxSum = 0;
	long int lengthSum = 0; 
	if ( DiveEntryListThis == NULL ){
		cgc_printf("\nDive Log is empty\n");
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
	cgc_printf("\nDives logged: @d\n",count);
	cgc_printf("Average Max Depth: @d\n",maxSum);
	cgc_printf("Average Dive Length: @d\n",lengthSum);
	return;
}

