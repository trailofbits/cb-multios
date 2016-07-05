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
/*
extern "C" {
#include <libcgc.h>
#include <stdlib.h>
}
*/

#include "common.h"

CommandHandler::CommandHandler() :
    m_bDiverInitialized( false )
{

}

CommandHandler::~CommandHandler()
{

}

bool CommandHandler::CmdChangeDiverInfo( void )
{
    printf( "\n" );

    if ( m_bDiverInitialized )
    {
        String sFirstName;
        String sLastName;
        String sStreet;
        String sCity;
        String sState;
        String sZipCode;
        String sPhoneNumber;
        String sPadiNumber;
        String sPadiDate;

        printf( "First Name (@s): ", m_oDiver.GetFirstName().c_str() );
        ReadLine( sFirstName );
        sFirstName.Trim( 20 );

        printf( "Last Name (@s): ", m_oDiver.GetLastName().c_str() );
        ReadLine( sLastName );
        sLastName.Trim( 20 );

        printf( "Street (@s): ", m_oDiver.GetStreet().c_str() );
        ReadLine( sStreet );
        sStreet.Trim( 29 );

        printf( "City (@s): ", m_oDiver.GetCity().c_str() );
        ReadLine( sCity );
        sCity.Trim( 19 );

        printf( "State (@s): ", m_oDiver.GetState().c_str() );
        ReadLine( sState );
        sState.Trim( 2 );

        printf( "Zip Code (@s): ", m_oDiver.GetZipCode().c_str() );
        ReadLine( sZipCode );
        sZipCode.Trim( 10 );

        printf( "Phone Number (@s): ", m_oDiver.GetPhoneNumber().c_str() );
        ReadLine( sPhoneNumber );
        sPhoneNumber.Trim( 15 );

        printf( "PADI Diver Number (@s): ", m_oDiver.GetPadiNumber().c_str() );
        ReadLine( sPadiNumber );
        sPadiNumber.Trim( 19 );

        printf( "PADI Cert Date (@s): ", m_oDiver.GetPadiDate().c_str() );
        ReadLine( sPadiDate );
        sPadiDate.Trim( 10 );

        // Only change them if they entered information
        if ( sFirstName != "" )
            m_oDiver.SetFirstName( sFirstName );

        if ( sLastName != "" )
            m_oDiver.SetLastName( sLastName );

        if ( sStreet != "" )
            m_oDiver.SetStreet( sStreet );

        if ( sCity != "" )
            m_oDiver.SetCity( sCity );

        if ( sState != "" )
            m_oDiver.SetState( sState );

        if ( sZipCode != "" )
            m_oDiver.SetZipCode( sZipCode );

        if ( sPhoneNumber != "" )
            m_oDiver.SetPhoneNumber( sPhoneNumber );

        if ( sPadiNumber != "" )
            m_oDiver.SetPadiNumber( sPadiNumber );

        if ( sPadiDate != "" )
            m_oDiver.SetPadiDate( sPadiDate );
    }
    else
    {
        String sFirstName;
        String sLastName;
        String sStreet;
        String sCity;
        String sState;
        String sZipCode;
        String sPhoneNumber;
        String sPadiNumber;
        String sPadiDate;

        printf( "First Name: " );
        ReadLine( sFirstName );
        sFirstName.Trim( 20 );

        printf( "Last Name: " );
        ReadLine( sLastName );
        sLastName.Trim( 20 );

        printf( "Street: " );
        ReadLine( sStreet );
        sStreet.Trim( 29 );

        printf( "City: " );
        ReadLine( sCity );
        sCity.Trim( 19 );

        printf( "State: " );
        ReadLine( sState );
        sState.Trim( 2 );

        printf( "Zip Code: " );
        ReadLine( sZipCode );
        sZipCode.Trim( 10 );

        printf( "Phone Number: " );
        ReadLine( sPhoneNumber );
        sPhoneNumber.Trim( 15 );

        printf( "PADI Diver Number: " );
        ReadLine( sPadiNumber );
        sPadiNumber.Trim( 19 );

        printf( "PADI Cert Date: " );
        ReadLine( sPadiDate );
        sPadiDate.Trim( 10 );

        m_oDiver.SetFirstName( sFirstName );
        m_oDiver.SetLastName( sLastName );
        m_oDiver.SetStreet( sStreet );
        m_oDiver.SetCity( sCity );
        m_oDiver.SetState( sState );
        m_oDiver.SetZipCode( sZipCode );
        m_oDiver.SetPhoneNumber( sPhoneNumber );
        m_oDiver.SetPadiNumber( sPadiNumber );
        m_oDiver.SetPadiDate( sPadiDate );
    }

    m_bDiverInitialized = true;

    PrintDiverInfo();

    return (false);
}

bool CommandHandler::CmdLogNewDive( void )
{
    String sDiveSite;
    String sDate;
    String sTime;
    String sLocation;
    String sMaxDepth;
    String sAvgDepth;
    String sDiveDuration;
    String sO2Percentage;
    String sPressureIn;
    String sPressureOut;

    // Capture dive information
    printf( "\n" );

    printf( "Dive Site: " );
    ReadLine( sDiveSite );
    sDiveSite.Trim( 25 );

    printf( "Date: " );
    ReadLine( sDate );
    sDate.Trim( 10 );

    printf( "Time: " );
    ReadLine( sTime );
    sTime.Trim( 8 );

    printf( "Location (area/city): " );
    ReadLine( sLocation );
    sLocation.Trim( 25 );

    printf( "Max Depth in ft: " );
    ReadLine( sMaxDepth );

    printf( "Avg Depth in ft: " );
    ReadLine( sAvgDepth );

    printf( "Dive Duration (mins): " );
    ReadLine( sDiveDuration );

    printf( "O2 Percentage: " );
    ReadLine( sO2Percentage );

    printf( "Pressure In (psi): " );
    ReadLine( sPressureIn );

    printf( "Pressure Out (psi): " );
    ReadLine( sPressureOut );

    // Add new dive to dive table -- parse data formats
    Dive *pNewDive = new Dive();

    Date oDiveDate;
    oDiveDate.SetDate( sDate );

    Time oDiveTime;
    oDiveTime.SetTime( sTime );

    pNewDive->SetDate( oDiveDate );
    pNewDive->SetTime( oDiveTime );
    pNewDive->SetDiveSite( sDiveSite );
    pNewDive->SetLocation( sLocation );
    pNewDive->SetMaxDepth( StringToInt( sMaxDepth ) );
    pNewDive->SetAvgDepth( StringToInt( sAvgDepth ) );
    pNewDive->SetDuration( StringToInt( sDiveDuration ) );
    pNewDive->SetO2Percentage( StringToInt( sO2Percentage ) );
    pNewDive->SetStartPressure( StringToInt( sPressureIn ) );
    pNewDive->SetEndPressure( StringToInt( sPressureOut ) );

    m_diveQueue.AddLast( pNewDive );

    return (false);
}

bool CommandHandler::CmdDownloadDiveData( void )
{
    // Get download data (timeval and depth as uint32 values)
    printf( "\n" );

    Dive *pNewDive = new Dive();

    // Begin reading samples
    bool bDone = false;
    uint32_t timeval, depth;

    // Always get first sample
    ReadUint32( timeval );
    ReadUint32( depth );
    pNewDive->AddDiveBin( timeval, depth );

    // Get remaining samples (exit on timeval of 0)
    for (;;)
    {
        ReadUint32( timeval );

        if ( timeval == 0 )
            break;

        ReadUint32( depth );
        pNewDive->AddDiveBin( timeval, depth );
    }

    // Collect information about the dives
    uint32_t binIndex;

    uint32_t maxDepth = 0;
    uint32_t depthSum = 0;
    for ( binIndex = 0; binIndex < pNewDive->GetBinCount(); binIndex++ )
    {
        if ( pNewDive->GetDiveBin( binIndex ).GetDepth() > maxDepth )
            maxDepth = pNewDive->GetDiveBin( binIndex ).GetDepth();

        depthSum += pNewDive->GetDiveBin( binIndex ).GetDepth();
    }

    uint32_t depthAvg = (depthSum / pNewDive->GetBinCount());

    // Get start time
    uint32_t startTime = pNewDive->GetDiveBin( 0 ).GetTimeVal();
    uint32_t endTime = pNewDive->GetDiveBin( pNewDive->GetBinCount()-1 ).GetTimeVal();

    uint32_t diveDurationInSeconds = endTime - startTime;
    uint32_t diveDurationInMinutes = (diveDurationInSeconds / 60);

    Date oDate;
    Time oTime;

    oDate.FromUnixTimeval( startTime );
    oTime.FromUnixTimeval( startTime );

    // Start collecting the rest of the dive information
    String sDiveSite;
    String sDate;
    String sTime;
    String sLocation;
    String sMaxDepth;
    String sAvgDepth;
    String sDiveDuration;
    String sO2Percentage;
    String sPressureIn;
    String sPressureOut;

    // Capture dive information
    printf( "Dive Site: " );
    ReadLine( sDiveSite );
    sDiveSite.Trim( 25 );

    printf( "Date (@s): ", oDate.GetString().c_str() );
    ReadLine( sDate );
    sDate.Trim( 10 );

    printf( "Time (@s): ", oTime.GetString().c_str() );
    ReadLine( sTime );
    sTime.Trim( 8 );

    printf( "Location (area/city): " );
    ReadLine( sLocation );
    sLocation.Trim( 25 );

    printf( "Max Depth in ft (@d): ", maxDepth );
    ReadLine( sMaxDepth );

    printf( "Avg Depth in ft (@d): ", depthAvg );
    ReadLine( sAvgDepth );

    printf( "Dive Duration (mins) (@d): ", diveDurationInMinutes );
    ReadLine( sDiveDuration );

    printf( "O2 Percentage: " );
    ReadLine( sO2Percentage );

    printf( "Pressure In (psi): " );
    ReadLine( sPressureIn );

    printf( "Pressure Out (psi): " );
    ReadLine( sPressureOut );

    // Update fields as necessary
    if ( sDate != "" )
        oDate.SetDate( sDate );

    if ( sTime != "" )
        oTime.SetTime( sTime );

    if ( sMaxDepth != "" )
        maxDepth = StringToInt( sMaxDepth );

    if ( sAvgDepth != "" )
        depthAvg = StringToInt( sAvgDepth );

    if ( sDiveDuration != "" )
        diveDurationInMinutes = StringToInt( sDiveDuration );

    // Add data
    pNewDive->SetDate( oDate );
    pNewDive->SetTime( oTime );
    pNewDive->SetDiveSite( sDiveSite );
    pNewDive->SetLocation( sLocation );
    pNewDive->SetMaxDepth( maxDepth );
    pNewDive->SetAvgDepth( depthAvg );
    pNewDive->SetDuration( diveDurationInMinutes );
    pNewDive->SetO2Percentage( StringToInt( sO2Percentage ) );
    pNewDive->SetStartPressure( StringToInt( sPressureIn ) );
    pNewDive->SetEndPressure( StringToInt( sPressureOut ) );

    m_diveQueue.AddLast( pNewDive );

    return (false);
}

bool CommandHandler::CmdEditDives( void )
{
    if ( m_diveQueue.GetCount() == 0 )
    {
        printf( "\n\nDive Log is empty\n" );
        return (false);
    }

    PrintDiveList();

    printf( "\nEnter Dive # to edit: " );

    String sDiveNumber;

    ReadLine( sDiveNumber );

    uint32_t diveNumber = StringToInt( sDiveNumber );

    if ( diveNumber == 0 || diveNumber > m_diveQueue.GetCount() )
    {
        printf( "Invalid dive number entered\n" );
        return (false);
    }

    Dive *pCur;
    uint32_t curPos = 1;
    for ( pCur = (Dive *)m_diveQueue.GetFirst(); pCur; pCur = (Dive *)pCur->GetNext() )
    {
        if ( diveNumber == curPos )
            break;

        curPos++;
    }

    if ( pCur == NULL )
    {
        printf( "Invalid dive number entered\n" );
        return (false);
    }

    String sDiveSite;
    String sDate;
    String sTime;
    String sLocation;
    String sMaxDepth;
    String sAvgDepth;
    String sDiveDuration;
    String sO2Percentage;
    String sPressureIn;
    String sPressureOut;

    // Capture dive information
    printf( "Editing dive number @d\n", diveNumber );

    printf( "Dive Site (@s): ", pCur->GetDiveSite().c_str() );
    ReadLine( sDiveSite );
    sDiveSite.Trim( 25 );

    printf( "Date (@s): ", pCur->GetDate().GetString().c_str() );
    ReadLine( sDate );
    sDate.Trim( 10 );

    printf( "Time (@s): ", pCur->GetTime().GetString().c_str() );
    ReadLine( sTime );
    sTime.Trim( 8 );

    printf( "Location (area/city) (@s): ", pCur->GetLocation().c_str() );
    ReadLine( sLocation );
    sLocation.Trim( 25 );

    printf( "Max Depth in ft (@d): ", pCur->GetMaxDepth() );
    ReadLine( sMaxDepth );

    printf( "Avg Depth in ft (@d): ", pCur->GetAvgDepth() );
    ReadLine( sAvgDepth );

    printf( "Dive Duration (mins) (@d): ", pCur->GetDuration() );
    ReadLine( sDiveDuration );

    printf( "O2 Percentage (@d): ", pCur->GetO2Percentage() );
    ReadLine( sO2Percentage );

    printf( "Pressure In (psi) (@d): ", pCur->GetStartPressure() );
    ReadLine( sPressureIn );

    printf( "Pressure Out (psi) (@d): ", pCur->GetEndPressure() );
    ReadLine( sPressureOut );

    Date oDiveDate;
    oDiveDate.SetDate( sDate );

    Time oDiveTime;
    oDiveTime.SetTime( sTime );

    pCur->SetDate( oDiveDate );
    pCur->SetTime( oDiveTime );
    pCur->SetDiveSite( sDiveSite );
    pCur->SetLocation( sLocation );
    pCur->SetMaxDepth( StringToInt( sMaxDepth ) );
    pCur->SetAvgDepth( StringToInt( sAvgDepth ) );
    pCur->SetDuration( StringToInt( sDiveDuration ) );
    pCur->SetO2Percentage( StringToInt( sO2Percentage ) );
    pCur->SetStartPressure( StringToInt( sPressureIn ) );
    pCur->SetEndPressure( StringToInt( sPressureOut ) );

    return (false);
}

bool CommandHandler::CmdPrintDiveLogs( void )
{
    if ( m_diveQueue.GetCount() == 0 )
    {
        printf( "\n\nDive Log is empty\n" );
        return (false);
    }

    PrintDiveList();

    printf( "\nEnter Dive # to display: " );

    String sDiveNumber;

    ReadLine( sDiveNumber );

    uint32_t diveNumber = StringToInt( sDiveNumber );

    if ( diveNumber == 0 || diveNumber > m_diveQueue.GetCount() )
    {
        printf( "Invalid dive number entered\n" );
        return (false);
    }

    Dive *pCur;
    uint32_t curPos = 1;
    for ( pCur = (Dive *)m_diveQueue.GetFirst(); pCur; pCur = (Dive *)pCur->GetNext() )
    {
        if ( diveNumber == curPos )
            break;

        curPos++;
    }

    if ( pCur == NULL )
    {
        printf( "Invalid dive number entered\n" );
        return (false);
    }

    printf( "\n" );
    printf( "          Date: @s\n", pCur->GetDate().GetString().c_str() );
    printf( "          Time: @s\n", pCur->GetTime().GetString().c_str() );
    printf( "     Dive Site: @s\n", pCur->GetDiveSite().c_str() );
    printf( "      Location: @s\n", pCur->GetLocation().c_str() );
    printf( "     Max Depth: @d\n", pCur->GetMaxDepth() );
    printf( "     Avg Depth: @d\n", pCur->GetAvgDepth() );
    printf( "      Duration: @d\n", pCur->GetDuration() );
    printf( "    O2 Percent: @d\n", pCur->GetO2Percentage() );
    printf( "Start Pressure: @d\n", pCur->GetStartPressure() );
    printf( "  End Pressure: @d\n", pCur->GetEndPressure() );
    printf( "     Bin Count: @d\n", pCur->GetBinCount() );
    printf( "\n" );

    return (false);
}

bool CommandHandler::CmdRemoveDives( void )
{
    if ( m_diveQueue.GetCount() == 0 )
    {
        printf( "\n\nDive Log is empty\n" );
        return (false);
    }

    PrintDiveList();

    printf( "\nEnter Dive # to delete or blank to abort: " );

    String sDiveNumber;

    // Read input
    ReadLine( sDiveNumber );

    // Check for abort
    if ( sDiveNumber == "" )
    {
        // abort
        return (false);
    }

    uint32_t diveNumber = StringToInt( sDiveNumber );

    if ( diveNumber == 0 || diveNumber > m_diveQueue.GetCount() )
    {
        printf( "Invalid dive number entered\n" );
        return (false);
    }

    Dive *pCur;
    uint32_t curPos = 1;
    for ( pCur = (Dive *)m_diveQueue.GetFirst(); pCur; pCur = (Dive *)pCur->GetNext() )
    {
        if ( diveNumber == curPos )
            break;

        curPos++;
    }

    if ( pCur == NULL )
    {
        printf( "Invalid dive number entered\n" );
        return (false);
    }

    // Remove the item from the dive queue
    m_diveQueue.RemoveItem( pCur );

    // Delete it
    delete pCur;

    return (false);
}

bool CommandHandler::CmdDiverStatistics( void )
{
    if ( m_diveQueue.GetCount() == 0 )
    {
        printf( "\n\nNo dives are logged\n" );
        return (false);
    }

    uint32_t depthTotal = 0;
    uint32_t lengthTotal = 0;

    Dive *pCur;

    for ( pCur = (Dive *)m_diveQueue.GetFirst(); pCur; pCur = (Dive *)pCur->GetNext() )
    {
        depthTotal += pCur->GetMaxDepth();
        lengthTotal += pCur->GetDuration();
    }

    printf( "\n\n" );
    printf( "Dives logged: @d\n", m_diveQueue.GetCount() );
    printf( "Average Max Depth: @d\n", (depthTotal / m_diveQueue.GetCount()) );
    printf( "Average Dive Length: @d\n", (lengthTotal / m_diveQueue.GetCount()) );

    return (false);
}

bool CommandHandler::CmdExitApplication( void )
{
    // Return true to exit application
    return (true);
}

void CommandHandler::PrintDiverInfo( void )
{
    printf( "\n" );
    printf( "     Name: @s @s\n", m_oDiver.GetFirstName().c_str(), m_oDiver.GetLastName().c_str() );
    printf( "  Address: @s\n", m_oDiver.GetStreet().c_str() );
    printf( "     City: @s\n", m_oDiver.GetCity().c_str() );
    printf( "    State: @s\n", m_oDiver.GetState().c_str() );
    printf( " Zip Code: @s\n", m_oDiver.GetZipCode().c_str() );
    printf( "    Phone: @s\n", m_oDiver.GetPhoneNumber().c_str() );
    printf( " PADI Num: @s\n", m_oDiver.GetPadiNumber().c_str() );
    printf( "Cert Date: @s\n", m_oDiver.GetPadiDate().c_str() );
    printf( "\n" );
}

void CommandHandler::PrintCommandTable( tCommandFunction *pCommandTable )
{
    printf( "\n" );
    for ( uint32_t i = 0; pCommandTable[i].pCmdFunc != NULL; i++ )
        printf( "@s - @s\n", pCommandTable[i].szCommand, pCommandTable[i].szDescription );

    printf( ":" );
}

void CommandHandler::ParserLoop( void )
{
    tCommandFunction oCmdTable[] = {
        { "C", "Change Diver Info", &CommandHandler::CmdChangeDiverInfo },
        { "L", "Log a New Dive", &CommandHandler::CmdLogNewDive },
        { "D", "Download Dive Data", &CommandHandler::CmdDownloadDiveData },
        { "E", "Edit Dives", &CommandHandler::CmdEditDives },
        { "P", "Print Dive Logs", &CommandHandler::CmdPrintDiveLogs },
        { "R", "Remove Dives", &CommandHandler::CmdRemoveDives },
        { "S", "Diver Statistics", &CommandHandler::CmdDiverStatistics },
        { "X", "Exit Application", &CommandHandler::CmdExitApplication },
        { "", "", NULL }
    };

    bool bDone = false;
    while ( !bDone )
    {
        // Print table
        PrintCommandTable( oCmdTable );

        // Read a line
        String inputLine;
        ReadLine( inputLine );

        // Parse command
        for ( uint32_t i = 0; oCmdTable[i].pCmdFunc != NULL; i++ )
        {
            if ( inputLine.lower() == String( oCmdTable[i].szCommand ).lower() )
            {
                if ( (this->*(oCmdTable[i].pCmdFunc))() )
                    bDone = true;

                break;
            }
        }
    }
}

void CommandHandler::PrintDiveList( void )
{
    Dive *pCur;
    printf( "\n\n" );
    printf( "Dive# Date       Time     Dive Site                 Location                 \n" );

    uint32_t curPos = 1;
    for ( pCur = (Dive *)m_diveQueue.GetFirst(); pCur; pCur = (Dive *)pCur->GetNext() )
    {
        printf( "@4d: @-10s @-8s @-25s @-25s\n", curPos, pCur->GetDate().GetString().c_str(),
                pCur->GetTime().GetString().c_str(), pCur->GetDiveSite().c_str(), pCur->GetLocation().c_str() );
        curPos++;
    }
}
