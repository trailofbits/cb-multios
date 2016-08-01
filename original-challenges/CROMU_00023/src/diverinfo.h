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
#ifndef __DIVER_INFO_H__
#define __DIVER_INFO_H__

#include <string.h>

class DiverInfo
{
public:
    DiverInfo() { };
    ~DiverInfo() { };

    void SetFirstName( const String& sName ) { m_firstName = sName; };
    void SetLastName( const String& sName ) { m_lastName = sName; };
    void SetStreet( const String& sStreet ) { m_street = sStreet; };
    void SetCity( const String& sCity ) { m_city = sCity; };
    void SetState( const String& sState ) { m_state = sState; };
    void SetZipCode( const String& sZipCode ) { m_zipcode = sZipCode; };
    void SetPhoneNumber( const String& sPhoneNumber ) { m_phoneNumber = sPhoneNumber; };
    void SetPadiNumber( const String& sPadiNumber ) { m_padiNumber = sPadiNumber; };
    void SetPadiDate( const String& sPadiDate ) { m_padiDate = sPadiDate; };

    const String& GetFirstName( void ) const { return m_firstName; };
    const String& GetLastName( void ) const { return m_lastName; };
    const String& GetStreet( void ) const { return m_street; };
    const String& GetCity( void ) const { return m_city; };
    const String& GetState( void ) const { return m_state; };
    const String& GetZipCode( void ) const { return m_zipcode; };
    const String& GetPhoneNumber( void ) const { return m_phoneNumber; };
    const String& GetPadiNumber( void ) const { return m_padiNumber; };
    const String& GetPadiDate( void ) const { return m_padiDate; };

private:
    String m_firstName;
    String m_lastName;
    String m_street;
    String m_city;
    String m_state;
    String m_zipcode;
    String m_phoneNumber;
    String m_padiNumber;
    String m_padiDate;
};

#endif // __DIVER_INFO_H___
