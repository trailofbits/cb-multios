/*

Author: Jason Williams <jdw@cromulence.com>

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
extern "C"
{
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <prng.h>
}

#define DEBUG_INSTRUCTION_EXECUTION	(1)

#include <cutil_string.h>

#include "cpu.h"
#include "mmu.h"
#include "vm.h"

#ifdef NULL
#undef NULL
#define NULL (0)
#endif

#define GET_BIT( val, x ) ((val >> x) & 0x1)
#define GET_BITS( val, x, y ) ((val >> x) & ((1<<((y-x)+1))-1))

CCPU::CCPU( void *pMagicPage )
	: m_pMagicPage( pMagicPage )
{

}

CCPU::~CCPU( )
{

}

bool CCPU::Init( CMMU *pMMU, CVM *pVM, CDMA *pDMA, uint16_t entryAddress )
{
	if ( !pMMU )
		return (false);

	if ( !pVM )
		return (false);

	if ( !pDMA )
		return (false);

	m_pDMA = pDMA;
	m_pMMU = pMMU;
	m_pVM = pVM;

	// Initialize registers!
	for ( uint8_t i = 0; i < MAX_CPU_REGISTERS; i++ )
	{
		m_regs[i] = 0;
	}

	m_regs[REG_PC] = entryAddress;
	m_regs[REG_SP] = 0xFFFC;

	m_instrCount = 0;
	m_bException = false;

	m_sExceptionText = "";

	return (true);
}

bool CCPU::Run( void )
{
	if ( !m_pMMU || !m_pVM )
		return (false);

	while ( RunSingleInstruction() )
		;

	if ( m_bException )
		return (false);

	return (true);
}

CUtil::String CCPU::DumpRegisters( void )
{
	char szTemp[1024];

	sprintf( szTemp, "Instructions: $d\nR0  = $08X R1  = $08X R2  = $08X R3  = $08X\nR4  = $08X R5  = $08X R6  = $08X R7  = $08X\nR8  = $08X R9  = $08X R10 = $08X R11 = $08X\nR12 = $08X R13 = $08X SP  = $08X PC  = $08X", m_instrCount, m_regs[0], m_regs[1], m_regs[2], m_regs[3], m_regs[4], m_regs[5], m_regs[6], m_regs[7], m_regs[8], m_regs[9], m_regs[10], m_regs[11], m_regs[12], m_regs[13], m_regs[14], m_regs[15] );

	return CUtil::String(szTemp);	
}

bool CCPU::RunSingleInstruction( void )
{
	uint16_t instr = FetchNextInstruction( );

	if ( m_bException )
		return (false);

	if ( m_instrCount++ > MAX_INSTRUCTION_COUNT )
	{
		m_sExceptionText = "Max instructions reached";
		m_bException = true;
		return (false);
	}
#if DEBUG_INSTRUCTION_EXECUTION
	{
		printf( "DEBUG:$s\n=====\n", DumpRegisters().c_str() );
	}
#endif

	// Service DMA requests (1 at a time) per instruction -- run at the same clock as the instruction dispatch
	m_pDMA->ServiceDMA( m_pMMU );

	switch( GET_BITS( instr, 13, 15 ) )
	{
	case 0:
		if ( GET_BIT( instr, 12 ) == 0 )
		{
			// Load immediate value HI
			LoadImmediateHI( GET_BITS( instr, 8, 11 ), GET_BITS( instr, 0, 7 ) );
		}
		else
		{
			// Load immediate value LO
			LoadImmediateLO( GET_BITS( instr, 8, 11 ), GET_BITS( instr, 0, 7 ) );
		}	
		break;

	case 1:
		if ( GET_BIT( instr, 12 ) == 0 )
		{
			AddReg( GET_BITS( instr, 8, 11 ), GET_BITS( instr, 4, 7 ), GET_BITS( instr, 0, 3 ) );
		}
		else
		{
			SubReg( GET_BITS( instr, 8, 11 ), GET_BITS( instr, 4, 7 ), GET_BITS( instr, 0, 3 ) );
		}
		break;

	case 2:
		if ( GET_BIT( instr, 12 ) == 0 )
		{
			MulReg( GET_BITS( instr, 8, 11 ), GET_BITS( instr, 4, 7 ), GET_BITS( instr, 0, 3 ) );
		}
		else
		{
			DivReg( GET_BITS( instr, 8, 11 ), GET_BITS( instr, 4, 7 ), GET_BITS( instr, 0, 3 ) );
		}
		break;

	case 3:
		switch( GET_BITS( instr, 8, 11 ) )
		{
		case 0:
			MovReg( GET_BITS( instr, 4, 7 ), GET_BITS( instr, 0, 3 ) );
			break;

		case 1:
			SwapReg( GET_BITS( instr, 4, 7 ), GET_BITS( instr, 0, 3 ) );
			break;

		case 2:
			JumpRegZero( GET_BITS( instr, 4, 7 ), GET_BITS( instr, 0, 3 ) );
			break;

		case 3:
			JumpRegNotZero( GET_BITS( instr, 4, 7 ), GET_BITS( instr, 0, 3 ) );
			break;

		case 4:
			DMAInit( GET_BITS( instr, 0, 7 ) );
			break;

		case 5:
			DMARead( GET_BITS( instr, 4, 7 ), GET_BITS( instr, 0, 3 ) ); 
			break;

		case 6:
			DMAWrite( GET_BITS( instr, 4, 7 ), GET_BITS( instr, 0, 3 ) );
			break;

		case 7:
			JumpOffset( 0, GET_BITS( instr, 0, 7 ) );
			break;

		case 8:
			JumpOffset( 1, GET_BITS( instr, 0, 7 ) );
			break;

		case 9:
			JumpReg( GET_BITS( instr, 0, 3 ) );
			break;

		case 10:	// GetInstrCount
			GetInstructionCount( GET_BITS( instr, 0, 3 ), GET_BITS( instr, 4, 7 ) );
			break;

		case 11:	// GetRand
			GetRand( GET_BITS( instr, 0, 3 ) );
			break;

		case 12:
			GetSeedMaterial( GET_BITS( instr, 0, 3 ) );
			break;

		case 13:
			LoadRegister( GET_BITS( instr, 4, 7 ), GET_BITS( instr, 0, 3 ) );
			break;

		case 14:
			StoreRegister( GET_BITS( instr, 4, 7 ), GET_BITS( instr, 0, 3 ) );
			break;

		default:
			m_sExceptionText = "Invalid opcode";
			m_bException = true;
			break;
		}
		break;

	case 4:
		switch ( GET_BITS( instr, 11, 12 ) )
		{
		case 0:
			AddImm( GET_BITS( instr, 7, 10 ), GET_BITS( instr, 0, 6 ) );
			break;

		case 1:
			SubImm( GET_BITS( instr, 7, 10 ), GET_BITS( instr, 0, 6 ) ); 
			break;

		case 2:
			MulImm( GET_BITS( instr, 7, 10 ), GET_BITS( instr, 0, 6 ) );
			break;

		case 3:
			DivImm( GET_BITS( instr, 7, 10 ), GET_BITS( instr, 0, 6 ) );
			break;
		}
		break;

	case 5:
		if ( GET_BIT( instr, 12 ) == 0 )
		{
			JumpLTReg( GET_BITS( instr, 8, 11 ), GET_BITS( instr, 4, 7 ), GET_BITS( instr, 0, 3 ) );
		}
		else
		{
			JumpGTReg( GET_BITS( instr, 8, 11 ), GET_BITS( instr, 4, 7 ), GET_BITS( instr, 0, 3 ) );
		}
		break;

	case 6:
		JumpOffsetZero( GET_BITS( instr, 9, 12 ), GET_BIT( instr, 8 ), GET_BITS( instr, 0, 7 ) );
		break;	

	case 7:
		JumpOffsetNotZero( GET_BITS( instr, 9, 12 ), GET_BIT( instr, 8 ), GET_BITS( instr, 0, 7 ) );
		break;
	}

	if ( m_bException )
		return (false);

	return (true);
}

void CCPU::LoadImmediateHI( uint8_t reg, uint8_t immediate )
{
	m_regs[reg] = (m_regs[reg] & 0xFF) | ((uint16_t)immediate << 8);
}

void CCPU::LoadImmediateLO( uint8_t reg, uint8_t immediate )
{
	m_regs[reg] = (m_regs[reg] & 0xFF00) | immediate;
}

void CCPU::AddReg( uint8_t regD, uint8_t regL, uint8_t regR )
{
	m_regs[regD] = m_regs[regL] + m_regs[regR];
}

void CCPU::SubReg( uint8_t regD, uint8_t regL, uint8_t regR )
{
	m_regs[regD] = m_regs[regL] - m_regs[regR];
}

void CCPU::MulReg( uint8_t regD, uint8_t regL, uint8_t regR )
{
	m_regs[regD] = m_regs[regL] * m_regs[regR];
}

void CCPU::DivReg( uint8_t regD, uint8_t regL, uint8_t regR )
{
	if ( m_regs[regR] == 0 )
	{
		m_sExceptionText = "Divide by zero";
		m_bException = true;
		return;
	}

	m_regs[regD] = m_regs[regL] / m_regs[regR];
}

void CCPU::AddImm( uint8_t regD, uint8_t immediate )
{
	m_regs[regD] += immediate;
}

void CCPU::SubImm( uint8_t regD, uint8_t immediate )
{
	m_regs[regD] -= immediate;
}

void CCPU::MulImm( uint8_t regD, uint8_t immediate )
{
	m_regs[regD] *= immediate;
}

void CCPU::DivImm( uint8_t regD, uint8_t immediate )
{
	if ( immediate == 0 )
	{
		m_sExceptionText = "Divide by zero";
		m_bException = true;
		return;
	}

	m_regs[regD] /= immediate;
}

void CCPU::MovReg( uint8_t regL, uint8_t regR )
{
	m_regs[regL] =  m_regs[regR];
}

void CCPU::SwapReg( uint8_t regL, uint8_t regR )
{
	uint16_t temp = m_regs[regL];
	m_regs[regL] = m_regs[regR];
	m_regs[regR] = temp;
}

void CCPU::JumpOffsetZero( uint8_t reg, uint8_t sign, uint8_t imm )
{
	if ( m_regs[reg] == 0 )
	{
		if ( sign == 0 )
			m_regs[REG_PC] += ((uint16_t)imm) << 1;
		else
			m_regs[REG_PC] -= ((uint16_t)imm) << 1;
	}

}

void CCPU::JumpOffsetNotZero( uint8_t reg, uint8_t sign, uint8_t imm )
{
	if ( m_regs[reg] != 0 )
	{
		if ( sign == 0 )
			m_regs[REG_PC] += ((uint16_t)imm) << 1;
		else
			m_regs[REG_PC] -= ((uint16_t)imm) << 1;
	}
}

void CCPU::JumpRegZero( uint8_t reg, uint8_t offsetReg )
{
	if ( m_regs[reg] == 0 )
		m_regs[REG_PC] += m_regs[offsetReg];
}

void CCPU::JumpRegNotZero( uint8_t reg, uint8_t offsetReg )
{
	if ( m_regs[reg] != 0 )
		m_regs[REG_PC] += m_regs[offsetReg];
}

void CCPU::JumpLTReg( uint8_t regL, uint8_t regR, uint8_t offsetReg )
{
	if ( m_regs[regL] < m_regs[regR] )
		m_regs[REG_PC] += m_regs[offsetReg];
}

void CCPU::JumpGTReg( uint8_t regL, uint8_t regR, uint8_t offsetReg )
{
	if ( m_regs[regL] > m_regs[regR] )
		m_regs[REG_PC] += m_regs[offsetReg];
}

void CCPU::JumpReg( uint8_t offsetReg )
{
	m_regs[REG_PC] = m_regs[offsetReg];
}

void CCPU::JumpOffset( uint8_t sign, uint16_t offset )
{
	if ( sign == 0 )
		m_regs[REG_PC] += offset;
	else
		m_regs[REG_PC] -= offset;
}

void CCPU::DMAInit( uint8_t deviceID )
{
	m_dmaDeviceID = deviceID;
}

void CCPU::DMAWrite( uint8_t regFrom, uint8_t regLen )
{
	m_pDMA->InitWriteWorker( m_dmaDeviceID, m_regs[regFrom], m_regs[regLen] );
}

void CCPU::DMARead( uint8_t regFrom, uint8_t regLen )
{
	m_pDMA->InitReadWorker( m_dmaDeviceID, m_regs[regFrom], m_regs[regLen] );
}

void CCPU::GetInstructionCount( uint8_t reg1, uint8_t reg2 )
{
	m_regs[reg1] = (m_instrCount >> 16) & 0xFFFF;
	m_regs[reg2] = (m_instrCount & 0xFFFF);
}

void CCPU::GetRand( uint8_t reg )
{
	m_regs[reg] = prng()&0xFFFF;
}

uint16_t CCPU::GetMagicPageSeed( void )
{
	uint16_t offset = (m_instrCount % 256) << 2;

	return *((uint16_t*)((uint8_t*)m_pMagicPage + offset));
}

void CCPU::GetSeedMaterial( uint8_t reg )
{
	m_regs[reg] = (prng()&0xFFFF ^ GetMagicPageSeed( ) );
}

void CCPU::LoadRegister( uint8_t regD, uint8_t regAddr )
{
	uint16_t loadValue;

	if ( !m_pMMU->Read16( m_regs[regAddr], loadValue ) )
	{
		m_sExceptionText = "MMU Read Exception";
		m_bException = true;
		return;
	}

	m_regs[regD] = loadValue;
}

void CCPU::StoreRegister( uint8_t regD, uint8_t regAddr )
{
	if ( !m_pMMU->Write16( m_regs[regAddr], m_regs[regD] ) )
	{
		m_sExceptionText = "MMU Write Exception";
		m_bException = true;
		return;
	}
}

uint16_t CCPU::FetchNextInstruction( void )
{
	uint16_t instr;

	if ( !m_pMMU->Fetch16( m_regs[REG_PC], instr ) )
	{
		m_sExceptionText = "MMU Fetch Exception";
		m_bException = true;
		m_regs[REG_PC] += 2;
		return (0);
	}

	m_regs[REG_PC] += 2;

	return (instr);
}

#if 0 
uint16_t CCPU::Read16( uint16_t address )
{
	uint16_t value;

	if ( !m_pMMU->Read16( address, value ) )
	{
		m_bException = true;
		return (0);
	}

	return (value);
}

void CCPU::Write16( uint16_t address, uint16_t value )
{
	if ( !m_pMMU->Write16( address, value ) )
	{
		m_bException = true;
		return;
	}
}
#endif
