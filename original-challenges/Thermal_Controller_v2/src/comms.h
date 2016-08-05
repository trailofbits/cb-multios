/*

Author: James Nuttall <james@cromulence.com>

Copyright (c) 2016 Cromulence LLC

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

#ifndef COMMS_H
#define COMMS_H

#include <cutil_string.h>


//
// Handles all return messages
//
class CommsMessage
{
protected:

	// uint16_t header
	// uint16_t version
	// uint8_t* body
	// uint16_t body length

	// uint16_t message type
	// uint16_t status
	// uint32_t extended body len

	// Entire message
	CUtil::String m_message;

	// Body of message
	CUtil::String m_body;

public:
	CommsMessage();
	~CommsMessage();
	
	void SetBody(CUtil::String);
	CUtil::String GetBody() { return m_body; }
	CUtil::String GetMessage() { return m_message; }
	uint16_t GetType();
	uint16_t GetValue();
	uint16_t GetLenValue();
};

class IncomingMessage : public CommsMessage
{
private:
	bool m_checksum_passed;

public:

	// read from input
	// store all variables
	void ReadInput();

	uint16_t GetSensorId();
	uint32_t GetSensorAddress();
	uint32_t GetSensorCoefficient();

	void GetProgramValues( uint32_t, uint32_t &, uint32_t &, uint32_t & );

};

class OutgoingMessage : public CommsMessage
{
private:
	CUtil::String m_version;
	uint16_t m_response;
	CUtil::String m_message;

public:

	void SetResponse( uint16_t resp ) { m_response = resp; }
	void SetVersion( uint16_t ); 
	void SetExtMessage( uint32_t, uint8_t* );

	void SendAsExtended();
	void SendAsBasic();

	void Reset() { m_version = ""; m_response = 0; }
};

#endif