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
#ifndef __CPU_H__
#define __CPU_H__

#include <cutil_string.h>

class CDMA;
class CMMU;
class CVM;

#define MAX_INSTRUCTION_COUNT	(400)

#define MAX_CPU_REGISTERS	16
#define REG_PC			15
#define REG_SP			14

class CCPU
{
public:
	CCPU( void *pMagicPage );
	~CCPU( );

	bool Init( CMMU *pMMU, CVM *pVM, CDMA *pDMA, uint16_t entryAddress );
	bool Run( void );

	bool HasException( void ) { return m_bException; };
	CUtil::String GetExceptionText( void ) { return m_sExceptionText; };

	CUtil::String DumpRegisters( void );

protected:
	bool RunSingleInstruction( void );

	uint16_t FetchNextInstruction( void );
#if 0	
	uint16_t Read16( uint16_t address );
	void Write16( uint16_t address, uint16_t value );
#endif

	void LoadImmediateHI( uint8_t reg, uint8_t immediate );
	void LoadImmediateLO( uint8_t reg, uint8_t immediate );

	void AddReg( uint8_t regD, uint8_t regL, uint8_t regR );
	void SubReg( uint8_t regD, uint8_t regL, uint8_t regR );
	void MulReg( uint8_t regD, uint8_t regL, uint8_t regR );
	void DivReg( uint8_t regD, uint8_t regL, uint8_t regR );

	void AddImm( uint8_t reg, uint8_t immediate );
	void SubImm( uint8_t reg, uint8_t immediate );
	void MulImm( uint8_t reg, uint8_t immediate );
	void DivImm( uint8_t reg, uint8_t immediate );

	void MovReg( uint8_t regL, uint8_t regR );
	void SwapReg( uint8_t regL, uint8_t regR );

	void JumpOffsetZero( uint8_t reg, uint8_t sign, uint8_t imm );
	void JumpOffsetNotZero( uint8_t reg, uint8_t sign, uint8_t imm );

	void JumpLTReg( uint8_t regL, uint8_t regR, uint8_t offsetReg );
	void JumpGTReg( uint8_t regL, uint8_t regR, uint8_t offsetReg );

	void JumpReg( uint8_t offsetReg );
	void JumpOffset( uint8_t sign, uint16_t offset );

	void JumpRegZero( uint8_t reg, uint8_t offsetReg );
	void JumpRegNotZero( uint8_t reg, uint8_t offsetReg );

	void DMAInit( uint8_t deviceID );
	void DMARead( uint8_t regFrom, uint8_t regLen );
	void DMAWrite( uint8_t regFrom, uint8_t regLen );

	void GetInstructionCount( uint8_t regL, uint8_t regR );

	void GetRand( uint8_t reg );
	void GetSeedMaterial( uint8_t reg );

	void LoadRegister( uint8_t regD, uint8_t regAddr );
	void StoreRegister( uint8_t regD, uint8_t regAddr );

private:
	uint16_t GetMagicPageSeed( void );

private:
	CDMA *m_pDMA;
	CMMU *m_pMMU;
	CVM *m_pVM;

	uint16_t m_regs[MAX_CPU_REGISTERS];

	uint32_t m_instrCount;	// Counts number of instructions executed
	bool m_bException;

	CUtil::String m_sExceptionText;	// Exception text

	void *m_pMagicPage;

	uint8_t m_dmaDeviceID;
};

#endif // _CPU_H__
