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
#ifndef ui_h
#define ui_h
#define Change_Diver_Info 		0x43
#define Log_New_Dive 			0x4c
#define Download_Dive_Data 		0x44
#define Edit_Dive				0x45
#define Print_Dive_Logs			0x50
#define Remove_Dive				0x52
#define Diver_Statistics        0x53
#define Exit					0x58

void MainMenu ( pDiverInfo );
void ChangeDiverInfo( pDiverInfo );
void ChangeDive( pDiveEntry );
void SanitizeDate(char date[32]);
void LogNewDive( pDiverInfo );
void DownloadDiveData( pDiverInfo );
void EditDive( pDiverInfo );
void PrintDiveLogs( pDiverInfo );
void RemoveDive( pDiverInfo );
void DiverStatistics( pDiverInfo );
#endif