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

extern "C"
{
	#include <libcgc.h>
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include <prng.h>
}

#include "cutil_string.h"
#include "cutil_list.h"
#include "common.h"
#include "controller.h"
#include "sensor.h"
#include "service.h"
#include "comms.h"

//#define NO_ERROR 0

//#define CHECKSUM_NUM_BYTES 4
#define HEADER_NUM_BYTES 4


//
//	read input, parse command, respond to command
//
int main( void )
{
	uint8_t *magic_page = ( uint8_t* )MAGIC_PAGE;

	Controller ctlr;

	ctlr.GetMsgOut()->SetVersion(ctlr.GetVersion());

	while ( 1 ) 
	{
		ctlr.GetMsgIn()->ReadInput();

		// if given length is longer than the string, NO
		if ( ctlr.GetMsgIn()->GetLenValue() != ctlr.GetMsgIn()->GetMessage().GetLength()/2 - HEADER_NUM_BYTES)
		{
			printf("Error: length is too long\n");
			continue;
		}

		//
		// PARSE BODY
		//
		switch ( ctlr.GetMsgIn()->GetType() )
		{
			case POWER_ON_OFF:
			{
				int val = ctlr.GetMsgIn()->GetValue();
				
				ctlr.setPowerOn( ( val == 1 ) ? true : false );

				ctlr.GetMsgOut()->SetResponse( NO_ERROR );
				ctlr.GetMsgOut()->SendAsBasic();

				break;
			}
			case TEMP_SET:
			{
				int val = ctlr.GetMsgIn()->GetValue();
				
				if ( ctlr.setSetTemp( val ) == false )
				{
					// failed to set temp
					ctlr.GetMsgOut()->SetResponse( ERROR_TEMP_RANGE );
					ctlr.GetMsgOut()->SendAsBasic();
				}
				else
				{
					ctlr.GetMsgOut()->SetResponse( NO_ERROR );
					ctlr.GetMsgOut()->SendAsBasic();
				}

				break;
			}
			case SENSOR_ADD:
			{
				if ( ctlr.IsSensorInList( ctlr.GetMsgIn()->GetSensorId() ) )
				{
					ctlr.GetMsgOut()->SetResponse( ERROR_ID_INUSE );
					ctlr.GetMsgOut()->SendAsBasic();
					break;
				}

				if ( ctlr.GetSensorCount() >= MAX_SENSORS )
				{
					ctlr.GetMsgOut()->SetResponse( ERROR_SENSORS_FULL );
					ctlr.GetMsgOut()->SendAsBasic();
					break;
				}
  
  				uint16_t a = ctlr.GetMsgIn()->GetSensorId();
  				uint32_t b = ctlr.GetMsgIn()->GetSensorAddress();
  				uint32_t c = ctlr.GetMsgIn()->GetSensorCoefficient();

				ctlr.AddSensor( new Sensor( a, b, c, true ) );
				
				ctlr.GetMsgOut()->SetResponse( NO_ERROR );
				ctlr.GetMsgOut()->SendAsBasic();

				break;
			}
			case SENSOR_REMOVE:
			{
				int val = ctlr.GetMsgIn()->GetValue();

				if ( ctlr.IsSensorInList( val ) == false)
				{
					ctlr.GetMsgOut()->SetResponse( ERROR_BAD_ID );
					ctlr.GetMsgOut()->SendAsBasic();
					break;
				}
				ctlr.RemoveSensor( val );
				ctlr.GetMsgOut()->SetResponse( NO_ERROR );
				ctlr.GetMsgOut()->SendAsBasic();
				break;
			}
			case SENSOR_SMOKE:
			{
				if ( ctlr.GetMsgIn()->GetValue() )
					ctlr.EnableSmokeSensor();
				else
					ctlr.DisableSmokeSensor();

				ctlr.GetMsgOut()->SetResponse( NO_ERROR );
				ctlr.GetMsgOut()->SendAsBasic();
				break;
			}
			case PROGRAM_UPDATE:
			{
				// update our program with one sent by the CRS

				// use ctlr.m_controllerProgram from incoming message
				int num_program_steps = ctlr.GetMsgIn()->GetValue();

				if ( num_program_steps > MAX_PROGRAM_STEPS )
				{
					// Too many steps. Return error
					ctlr.GetMsgOut()->SetResponse( ERROR_BAD_PROGRAM );
					ctlr.GetMsgOut()->SendAsBasic();
					break;
				}

				// in a loop, read each program variables into ctlr.m_controllerProgram[i]

				int num_nibbles_to_start = 16; // 8 bytes
				int num_nibbles_for_each_program = 24; // 12 bytes


				// keep original copy in the backup
				// write all new values to the main program
				// clear backup when done

				ctlr.BackupProgram();
				ctlr.ClearProgram();

				int j = 0;
				for ( int i = 0; i < num_program_steps; i++ )
				{
					uint32_t a, b, c;
					int offset = num_nibbles_to_start + ( i * num_nibbles_for_each_program );

					ctlr.GetMsgIn()->GetProgramValues( offset, a, b, c );

					// verify values here
					if ( a == 0 ) 
					{
						if ( ctlr.IsSensorInList( b ) == false && b != 0 )
						{
							ctlr.GetMsgOut()->SetResponse( ERROR_NO_SENSOR );
							ctlr.GetMsgOut()->SendAsBasic();
							ctlr.RevertProgram();
							goto leave_case;
						}
					}
					else if ( a == 1 )
					{
						if ( b < ( 30 * 60 ) )
						{
							ctlr.GetMsgOut()->SetResponse( ERROR_TIME_VALUE );
							ctlr.GetMsgOut()->SendAsBasic();
							ctlr.RevertProgram();
							goto leave_case;
						}
					}
					else
					{
						ctlr.GetMsgOut()->SetResponse( ERROR_BAD_PROGRAM );
						ctlr.GetMsgOut()->SendAsBasic();
						ctlr.RevertProgram();
						goto leave_case;
					}

					// save program here
					ctlr.m_controllerProgram[ j ].setStepType( a );

					if ( a == 0 )
						ctlr.m_controllerProgram[ j ].setSensorId( b );
					else
						ctlr.m_controllerProgram[ j ].setDuration( b );

					if ( c < 175 || c > 350 )
					{
						ctlr.GetMsgOut()->SetResponse( ERROR_TEMP_RANGE );
						ctlr.GetMsgOut()->SendAsBasic();
						ctlr.RevertProgram();
						goto leave_case;
					}

					ctlr.m_controllerProgram[ j ].setSetTemp( c );

					j++;
				}
				
				ctlr.GetMsgOut()->SetResponse( NO_ERROR );
				ctlr.GetMsgOut()->SendAsBasic();
				ctlr.ClearBackupProgram();
leave_case:
				break;
			}
			case PROGRAM_SEND:
			{
				// Send the CRS our current program
				uint8_t buffer[ MAX_PROGRAM_STEPS * 3 * sizeof( int ) ];
				bzero( buffer, MAX_PROGRAM_STEPS * 3 * sizeof( int ) );

				uint16_t tmpValue;

				for ( int i = 0; i < MAX_PROGRAM_STEPS; i++ ) 
				{
					tmpValue = ctlr.m_controllerProgram[i].getStepType();
					
					*( int32_t * )( buffer + ( i * 12 ) ) = tmpValue;

					if ( tmpValue == 0 ) 
						tmpValue = ctlr.m_controllerProgram[i].getSensorId();
					else
						tmpValue = ctlr.m_controllerProgram[i].getDuration();

					*( int32_t * )( buffer + ( i * 12 + 4 ) ) = tmpValue;

					tmpValue = ctlr.m_controllerProgram[i].getSetTemp();

					*( int32_t * )( buffer + ( i * 12 + 8 ) ) = tmpValue;

				}

				ctlr.GetMsgOut()->SetResponse(PROGRAM_SEND);
				ctlr.GetMsgOut()->SetExtMessage( sizeof( buffer ), buffer );
				ctlr.GetMsgOut()->SendAsExtended();
				break;
			}
			case SIMULATE:
			{
				// uses current temp, set temp, power on, heater on

				// duration is number of iterations over for loop

				// 
				int sim_duration = ctlr.GetMsgIn()->GetValue();

				double current_temp = ctlr.getCurrentTemp();
				bool power_on = ctlr.getPowerOn();
				bool heater_on = ctlr.getHeaterOn();
				int32_t set_temp = ctlr.getSetTemp();

				uint32_t i;
				for ( i = 0; i < sim_duration; i++ ) 
				{
					if ( power_on == true ) 
					{
						// power on

						if ( heater_on == true ) 
						{
							// power on, heater on

							current_temp += 1.0;

							if ( current_temp > ( set_temp + 5 ) ) 
							{
								heater_on = false;
							}

						} 
						else 
						{
							// power on, heater off
							if (current_temp > AMBIENT_TEMP)
							{
								current_temp -= 0.25;
							}

							if (current_temp < (set_temp-5))
								heater_on = true;
						}
					} 
					else 
					{
						// power off

						if (current_temp > AMBIENT_TEMP)
						{
							current_temp -= 0.25;
						}
					}
				}

				ctlr.setCurrentTemp( current_temp );
				ctlr.setPowerOn( power_on );
				ctlr.setHeaterOn( heater_on );

				break;
			}
			case STATUS_SEND:
			{
				unsigned char buffer[ 24 ];

				*( int32_t * )buffer = ctlr.GetVersion();

				*( int32_t * )( buffer+4 ) = ctlr.getSetTemp();
				*( int32_t * )( buffer+8 ) = ( int32_t )ctlr.getCurrentTemp(); 
				*( int32_t * )( buffer+12 ) = ( ctlr.getPowerOn() == true ) ? 1 : 0; 
				*( int32_t * )( buffer+16 ) = ( ctlr.getHeaterOn() == true ) ? 1 : 0; 
				*( int32_t * )( buffer+20 ) = ( ctlr.IsSmokeSensorEnabled() == true ) ? 1 : 0;

				ctlr.GetMsgOut()->SetResponse( STATUS_SEND );
				ctlr.GetMsgOut()->SetExtMessage( sizeof( buffer ), buffer );
				ctlr.GetMsgOut()->SendAsExtended();
				break;
			}
			case FIRMWARE_CHECK:
			{
				uint32_t val = 0;
				if ( ctlr.GetVersion() != VERSION )
				{
					val = 1;
				}
				for ( int32_t i = 0; i < 4096; i++ )
					val = val + *( magic_page + i ) * ( i + 1 );

				ctlr.GetMsgOut()->SetResponse( FIRMWARE_CHECK );

				ctlr.GetMsgOut()->SetExtMessage( sizeof( uint32_t ), ( uint8_t* )&val );
				ctlr.GetMsgOut()->SendAsExtended();
				break;
			}
			case END:
			{
				return 0;	
			}
			default:
			{
				ctlr.GetMsgOut()->SetResponse( ERROR_BAD_COMMAND );
				ctlr.GetMsgOut()->SendAsBasic();
			}
		}
	}

	return 0;
}