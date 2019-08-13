#include "Config.h"
#include "Emulator.h"

//////////////////////////////////////////////////////////////////////////////////

// put 1 byte immediate data into reg
void Emulator::CPU_8BIT_LOAD( BYTE& reg )
{
	m_CyclesThisUpdate += 8 ;
	BYTE n = ReadMemory(m_ProgramCounter) ;
	m_ProgramCounter++ ;
	reg = n ;
}

//////////////////////////////////////////////////////////////////////////////////

// put 2 byte immediate data into reg
void Emulator::CPU_16BIT_LOAD( WORD& reg )
{
	m_CyclesThisUpdate += 12 ;
	WORD n = ReadWord() ;
	m_ProgramCounter+=2 ;
	reg = n ;
}

//////////////////////////////////////////////////////////////////////////////////

void Emulator::CPU_REG_LOAD(BYTE& reg, BYTE load, int cycles)
{
	m_CyclesThisUpdate += cycles ;
	reg = load ;
}

//////////////////////////////////////////////////////////////////////////////////

void Emulator::CPU_REG_LOAD_ROM(BYTE& reg, WORD address)
{
	m_CyclesThisUpdate+=8 ;
	reg = ReadMemory(address) ;
}

//////////////////////////////////////////////////////////////////////////////////

// apparently no flags affected
void Emulator::CPU_16BIT_DEC(WORD& word, int cycles)
{
	m_CyclesThisUpdate+=cycles ;
	word--;
}

//////////////////////////////////////////////////////////////////////////////////

// apparently no flags affected
void Emulator::CPU_16BIT_INC(WORD& word, int cycles)
{
	m_CyclesThisUpdate+=cycles;
	word++;
}

//////////////////////////////////////////////////////////////////////////////////

// add to reg. Can be immediate data, and can also add the carry flag to the result
void Emulator::CPU_8BIT_ADD(BYTE& reg, BYTE toAdd, int cycles, bool useImmediate, bool addCarry)
{
	m_CyclesThisUpdate+=cycles ;
	BYTE before = reg ;
	BYTE adding = 0 ;

	// are we adding immediate data or the second param?
	if (useImmediate)
	{
		BYTE n = ReadMemory(m_ProgramCounter) ;
		m_ProgramCounter++ ;
		adding = n ;
	}
	else
	{
		adding = toAdd ;
	}

	// are we also adding the carry flag?
	if (addCarry)
	{
		if (TestBit(m_RegisterAF.lo, FLAG_C))
			adding++ ;
	}

	reg+=adding ;

	// set the flags
	m_RegisterAF.lo = 0 ;

	if (reg == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;

	WORD htest = (before & 0xF) ;
	htest += (adding & 0xF) ;

	if (htest > 0xF)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_H) ;

	if ((before + adding) > 0xFF)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C) ;

//	_asm int 3; // IM UNSURE IF the flags for FLAG C and FLAG H are correct... Need to check
}

//////////////////////////////////////////////////////////////////////////////////

// subtracts away from reg, can also subtract the carry flag too
void Emulator::CPU_8BIT_SUB(BYTE& reg, BYTE subtracting, int cycles, bool useImmediate, bool subCarry)
{
	m_CyclesThisUpdate += cycles ;
	BYTE before = reg ;
	BYTE toSubtract = 0 ;

	if (useImmediate)
	{
		BYTE n = ReadMemory(m_ProgramCounter) ;
		m_ProgramCounter++ ;
		toSubtract = n ;
	}
	else
	{
		toSubtract = subtracting ;
	}

	if (subCarry)
	{
		if (TestBit(m_RegisterAF.lo, FLAG_C))
			toSubtract++ ;
	}

	reg -= toSubtract ;

	m_RegisterAF.lo = 0 ;

	if (reg == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;

	m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_N) ;

	// set if no borrow
	if (before < toSubtract)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C) ;

	SIGNED_WORD htest = (before & 0xF) ;
	htest -= (toSubtract & 0xF) ;

	if (htest < 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_H) ;

}

//////////////////////////////////////////////////////////////////////////////////

void Emulator::CPU_8BIT_AND(BYTE& reg, BYTE toAnd, int cycles, bool useImmediate)
{
	m_CyclesThisUpdate+=cycles ;
	BYTE myand = 0 ;

	if (useImmediate)
	{
		BYTE n = ReadMemory(m_ProgramCounter) ;
		m_ProgramCounter++ ;
		myand = n ;
	}
	else
	{
		myand = toAnd ;
	}

	reg &= myand ;

	m_RegisterAF.lo = 0 ;

	if (reg == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;

	m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_H) ;
}

//////////////////////////////////////////////////////////////////////////////////

void Emulator::CPU_8BIT_OR(BYTE& reg, BYTE toOr, int cycles, bool useImmediate)
{
	m_CyclesThisUpdate+=cycles ;
	BYTE myor = 0 ;

	if (useImmediate)
	{
		BYTE n = ReadMemory(m_ProgramCounter) ;
		m_ProgramCounter++ ;
		myor = n ;
	}
	else
	{
		myor = toOr ;
	}

	reg |= myor ;

	m_RegisterAF.lo = 0 ;

	if (reg == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;
}

//////////////////////////////////////////////////////////////////////////////////

void Emulator::CPU_8BIT_XOR(BYTE& reg, BYTE toXOr, int cycles, bool useImmediate)
{
	m_CyclesThisUpdate+=cycles ;
	BYTE myxor = 0 ;

	if (useImmediate)
	{
		BYTE n = ReadMemory(m_ProgramCounter) ;
		m_ProgramCounter++ ;
		myxor = n ;
	}
	else
	{
		myxor = toXOr ;
	}

	reg ^= myxor ;

	m_RegisterAF.lo = 0 ;

	if (reg == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;
}

//////////////////////////////////////////////////////////////////////////////////

// this does not affect any registers, hence why im not passing a reference

void Emulator::CPU_8BIT_COMPARE(BYTE reg, BYTE subtracting, int cycles, bool useImmediate)
{
	m_CyclesThisUpdate += cycles ;
	BYTE before = reg ;
	BYTE toSubtract = 0 ;

	if (useImmediate)
	{
		BYTE n = ReadMemory(m_ProgramCounter) ;
		m_ProgramCounter++ ;
		toSubtract = n ;
	}
	else
	{
		toSubtract = subtracting ;
	}

	reg -= toSubtract ;

	m_RegisterAF.lo = 0 ;

	if (reg == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;

	m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_N) ;

	// set if no borrow
	if (before < toSubtract)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C) ;


	SIGNED_WORD htest = before & 0xF ;
	htest -= (toSubtract & 0xF) ;

	if (htest < 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_H) ;

}

//////////////////////////////////////////////////////////////////////////////////

void Emulator::CPU_8BIT_INC(BYTE& reg, int cycles)
{
	// WHEN EDITING THIS FUNCTION DONT FORGET TO MAKE THE SAME CHANGES TO CPU_8BIT_MEMORY_INC

	m_CyclesThisUpdate+= cycles ;

	BYTE before = reg ;

	reg++ ;

	if (reg == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;
	else
		m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_Z) ;

	m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_N) ;

	if ((before & 0xF) == 0xF)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_H) ;
	else
		m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_H) ;
}

//////////////////////////////////////////////////////////////////////////////////

void Emulator::CPU_8BIT_MEMORY_INC(WORD address, int cycles)
{
	// WHEN EDITING THIS FUNCTION DONT FORGET TO MAKE THE SAME CHANGES TO CPU_8BIT_INC

	m_CyclesThisUpdate+= cycles ;

	BYTE before = ReadMemory( address ) ;
	WriteByte(address, (before+1)) ;
	BYTE now =  before+1 ;

	if (now == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;
	else
		m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_Z) ;

	m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_N) ;

	if ((before & 0xF) == 0xF)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_H) ;
	else
		m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_H) ;
}

//////////////////////////////////////////////////////////////////////////////////

void Emulator::CPU_8BIT_DEC(BYTE& reg, int cycles)
{
	// WHEN EDITING THIS FUNCTION DONT FORGET TO MAKE THE SAME CHANGES TO CPU_8BIT_MEMORY_DEC

	m_CyclesThisUpdate+=cycles ;
	BYTE before = reg ;

	reg-- ;

	if (reg == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;
	else
		m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_Z) ;

	m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_N) ;

	if ((before & 0x0F) == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_H) ;
	else
		m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_H) ;

}

//////////////////////////////////////////////////////////////////////////////////

void Emulator::CPU_8BIT_MEMORY_DEC(WORD address, int cycles)
{
	// WHEN EDITING THIS FUNCTION DONT FORGET TO MAKE THE SAME CHANGES TO CPU_8BIT_DEC

	m_CyclesThisUpdate+=cycles ;
	BYTE before = ReadMemory(address) ;
	WriteByte(address, (before-1)) ;
	BYTE now = before-1 ;

	if (now == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;
	else
		m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_Z) ;

	m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_N) ;

	if ((before & 0x0F) == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_H) ;
	else
		m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_H) ;
}

//////////////////////////////////////////////////////////////////////////////////

void Emulator::CPU_16BIT_ADD(WORD& reg, WORD toAdd, int cycles)
{
	m_CyclesThisUpdate += cycles ;
	WORD before = reg ;

	reg += toAdd ;

	m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_N) ;

	if ((before + toAdd) > 0xFFFF)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C) ;
	else
		m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_C) ;


	if (( (before & 0xFF00) & 0xF) + ((toAdd >> 8) & 0xF))
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_H) ;
	else
		m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_H) ;

//	_asm int 3; // not sure about flag h
}

//////////////////////////////////////////////////////////////////////////////////

void Emulator::CPU_JUMP(bool useCondition, int flag, bool condition)
{
	m_CyclesThisUpdate += 12 ;

	WORD nn = ReadWord( ) ;
	m_ProgramCounter += 2 ;

	if (!useCondition)
	{
		m_ProgramCounter = nn ;
		return ;
	}

	if (TestBit(m_RegisterAF.lo, flag) == condition)
	{
		m_ProgramCounter = nn ;
	}

}

//////////////////////////////////////////////////////////////////////////////////

void Emulator::CPU_JUMP_IMMEDIATE(bool useCondition, int flag, bool condition)
{
	m_CyclesThisUpdate += 8 ;

	SIGNED_BYTE n = (SIGNED_BYTE)ReadMemory(m_ProgramCounter) ;

	if (!useCondition)
	{
		m_ProgramCounter += n;
	}
	else if (TestBit(m_RegisterAF.lo, flag) == condition)
	{
		m_ProgramCounter += n ;
	}

	m_ProgramCounter++ ;
}

//////////////////////////////////////////////////////////////////////////////////

void Emulator::CPU_CALL(bool useCondition, int flag, bool condition)
{
	m_CyclesThisUpdate+=12 ;
	WORD nn = ReadWord( ) ;
	m_ProgramCounter += 2;

	if (!useCondition)
	{
		PushWordOntoStack(m_ProgramCounter) ;
		m_ProgramCounter = nn ;
		return ;
	}

	if (TestBit(m_RegisterAF.lo, flag)==condition)
	{
		PushWordOntoStack(m_ProgramCounter) ;
		m_ProgramCounter = nn ;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void Emulator::CPU_RETURN(bool useCondition, int flag, bool condition)
{
	m_CyclesThisUpdate += 8 ;
	if (!useCondition)
	{
		m_ProgramCounter = PopWordOffStack( ) ;
		return ;
	}

	if (TestBit(m_RegisterAF.lo, flag) == condition)
	{
		m_ProgramCounter = PopWordOffStack( ) ;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void Emulator::CPU_SWAP_NIBBLES(BYTE& reg)
{
	m_CyclesThisUpdate += 8 ;

	m_RegisterAF.lo = 0 ;

	reg = (((reg & 0xF0) >> 4) | ((reg & 0x0F) << 4));

	if (reg == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;

	// WHEN EDITING THIS FUNCTION ALSO EDIT CPU_SWAP_NIB_MEM
}

//////////////////////////////////////////////////////////////////////////////////

void Emulator::CPU_SWAP_NIB_MEM(WORD address)
{
	m_CyclesThisUpdate += 16 ;

	m_RegisterAF.lo = 0 ;

	BYTE mem = ReadMemory(address) ;
	mem = (((mem & 0xF0) >> 4) | ((mem & 0x0F) << 4));

	WriteByte(address,mem) ;

	if (mem == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;


	// WHEN EDITING THIS FUNCTION ALSO EDIT CPU_SWAP_NIBBLES


}

//////////////////////////////////////////////////////////////////////////////////

void Emulator::CPU_RESTARTS(BYTE n)
{
	PushWordOntoStack(m_ProgramCounter) ;
	m_CyclesThisUpdate += 32 ;
	m_ProgramCounter = n ;
}

//////////////////////////////////////////////////////////////////////////////////

void Emulator::CPU_SHIFT_LEFT_CARRY(BYTE& reg)
{
	// WHEN EDITING THIS FUNCTION ALSO EDIT CPU_SHIFT_LEFT_CARRY_MEMORY
	m_CyclesThisUpdate += 8 ;
	m_RegisterAF.lo = 0 ;
	if (TestBit(reg,7))
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C) ;

	reg = reg << 1 ;
	if (reg == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;
}

//////////////////////////////////////////////////////////////////////////////////

void Emulator::CPU_SHIFT_LEFT_CARRY_MEMORY(WORD address)
{
	// WHEN EDITING THIS FUNCTION ALSO EDIT CPU_SHIFT_LEFT_CARRY
	m_CyclesThisUpdate += 16 ;
	BYTE before = ReadMemory(address) ;

	m_RegisterAF.lo = 0 ;
	if (TestBit(before,7))
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C) ;

	before = before << 1 ;
	if (before == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;

	WriteByte(address, before) ;
}

//////////////////////////////////////////////////////////////////////////////////

void Emulator::CPU_RESET_BIT(BYTE& reg, int bit)
{
	// WHEN EDITING THIS ALSO EDIT CPU_RESET_BIT_MEMORY
	reg = BitReset(reg, bit) ;
	m_CyclesThisUpdate += 8 ;
}

//////////////////////////////////////////////////////////////////////////////////

void Emulator::CPU_RESET_BIT_MEMORY(WORD address, int bit)
{
	// WHEN EDITING THIS ALSO EDIT CPU_RESET_BIT
	BYTE mem = ReadMemory(address) ;
	mem = BitReset(mem, bit) ;
	WriteByte(address, mem) ;
	m_CyclesThisUpdate += 16 ;
}

//////////////////////////////////////////////////////////////////////////////////

void Emulator::CPU_TEST_BIT(BYTE reg, int bit, int cycles)
{
	if (TestBit(reg, bit))
		m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_Z) ;
	else
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;

	m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_N) ;
	m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_H) ;

	m_CyclesThisUpdate += cycles ;
}

//////////////////////////////////////////////////////////////////////////////////

void Emulator::CPU_SET_BIT(BYTE& reg, int bit)
{
	// WHEN EDITING THIS ALSO EDIT CPU_SET_BIT_MEMORY
	reg = BitSet(reg, bit) ;
	m_CyclesThisUpdate += 8 ;
}

//////////////////////////////////////////////////////////////////////////////////

void Emulator::CPU_SET_BIT_MEMORY(WORD address, int bit)
{
	// WHEN EDITING THIS ALSO EDIT CPU_SET_BIT
	BYTE mem = ReadMemory(address) ;
	mem = BitSet(mem, bit) ;
	WriteByte(address, mem) ;
	m_CyclesThisUpdate += 16 ;
}

//////////////////////////////////////////////////////////////////////////////////

// STOLEN
void Emulator::CPU_DAA( )
{
	m_CyclesThisUpdate += 4 ;

	if(TestBit(m_RegisterAF.lo, FLAG_N))
	{
		if((m_RegisterAF.hi &0x0F ) >0x09 || m_RegisterAF.lo &0x20 )
		{
			m_RegisterAF.hi -=0x06; //Half borrow: (0-1) = (0xF-0x6) = 9
			if((m_RegisterAF.hi&0xF0)==0xF0) m_RegisterAF.lo|=0x10; else m_RegisterAF.lo&=~0x10;
		}

		if((m_RegisterAF.hi&0xF0)>0x90 || m_RegisterAF.lo&0x10) m_RegisterAF.hi-=0x60;
	}
	else
	{
		if((m_RegisterAF.hi&0x0F)>9 || m_RegisterAF.lo&0x20)
		{
			m_RegisterAF.hi+=0x06; //Half carry: (9+1) = (0xA+0x6) = 10
			if((m_RegisterAF.hi&0xF0)==0) m_RegisterAF.lo|=0x10; else m_RegisterAF.lo&=~0x10;
		}

		if((m_RegisterAF.hi&0xF0)>0x90 || m_RegisterAF.lo&0x10) m_RegisterAF.hi+=0x60;
	}

	if(m_RegisterAF.hi==0) m_RegisterAF.lo|=0x80; else m_RegisterAF.lo&=~0x80;
}

//////////////////////////////////////////////////////////////////////////////////

// rotate right through carry
void Emulator::CPU_RR(BYTE& reg)
{
	// WHEN EDITING THIS ALSO EDIT CPU_RR_MEMORY
	m_CyclesThisUpdate += 8 ;

	bool isCarrySet = TestBit(m_RegisterAF.lo, FLAG_C) ;
	bool isLSBSet = TestBit(reg, 0) ;

	m_RegisterAF.lo = 0 ;

	reg >>= 1 ;

	if (isLSBSet)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C) ;

	if (isCarrySet)
		reg = BitSet(reg, 7) ;

	if (reg == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;
}

//////////////////////////////////////////////////////////////////////////////////

// rotate right through carry
void Emulator::CPU_RR_MEMORY(WORD address)
{
	// WHEN EDITING THIS ALSO EDIT CPU_RR

	m_CyclesThisUpdate += 16 ;

	BYTE reg = ReadMemory(address) ;

	bool isCarrySet = TestBit(m_RegisterAF.lo, FLAG_C) ;
	bool isLSBSet = TestBit(reg, 0) ;

	m_RegisterAF.lo = 0 ;

	reg >>= 1 ;

	if (isLSBSet)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C) ;

	if (isCarrySet)
		reg = BitSet(reg, 7) ;

	if (reg == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;

	WriteByte(address, reg) ;
}

//////////////////////////////////////////////////////////////////////////////////

// rotate left
void Emulator::CPU_RLC(BYTE& reg)
{
	//WHEN EDITING THIS FUNCTION ALSO EDIT CPU_RLC_MEMORY

	m_CyclesThisUpdate += 8 ;

	bool isMSBSet = TestBit(reg, 7) ;

	m_RegisterAF.lo = 0 ;

	reg <<= 1;

	if (isMSBSet)
	{
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C) ;
		reg = BitSet(reg,0) ;
	}

	if (reg == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;

}

//////////////////////////////////////////////////////////////////////////////////

// rotate left
void Emulator::CPU_RLC_MEMORY(WORD address)
{
	//WHEN EDITING THIS FUNCTION ALSO EDIT CPU_RLC

	m_CyclesThisUpdate += 16 ;

	BYTE reg = ReadMemory(address) ;

	bool isMSBSet = TestBit(reg, 7) ;

	m_RegisterAF.lo = 0 ;

	reg <<= 1;

	if (isMSBSet)
	{
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C) ;
		reg = BitSet(reg,0) ;
	}

	if (reg == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;

	WriteByte(address, reg) ;

}

//////////////////////////////////////////////////////////////////////////////////

// rotate right
void Emulator::CPU_RRC(BYTE& reg)
{
	// WHEN EDITING THIS FUNCTION ALSO EDIT CPU_RRC_MEMORY

	m_CyclesThisUpdate += 8 ;

	bool isLSBSet = TestBit(reg, 0) ;

	m_RegisterAF.lo = 0 ;

	reg >>= 1;

	if (isLSBSet)
	{
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C) ;
		reg = BitSet(reg,7) ;
	}

	if (reg == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;
}

//////////////////////////////////////////////////////////////////////////////////

// rotate right
void Emulator::CPU_RRC_MEMORY(WORD address)
{
	// WHEN EDITING THIS FUNCTION ALSO EDIT CPU_RRC

	m_CyclesThisUpdate += 16 ;

	BYTE reg = ReadMemory(address) ;

	bool isLSBSet = TestBit(reg, 0) ;

	m_RegisterAF.lo = 0 ;

	reg >>= 1;

	if (isLSBSet)
	{
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C) ;
		reg = BitSet(reg,7) ;
	}

	if (reg == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;

	WriteByte(address, reg) ;
}

//////////////////////////////////////////////////////////////////////////////////

// shift left arithmetically (basically bit 0 gets set to 0) (bit 7 goes into carry)
void Emulator::CPU_SLA(BYTE& reg)
{
	// WHEN EDITING THIS ALSO EDIT CPU_SLA_MEMORY

	m_CyclesThisUpdate += 8 ;

	bool isMSBSet = TestBit(reg, 7);

	reg <<= 1;

	m_RegisterAF.lo = 0 ;

	if (isMSBSet)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C) ;

	if (reg == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;
}

//////////////////////////////////////////////////////////////////////////////////

void Emulator::CPU_SLA_MEMORY(WORD address)
{
	// WHEN EDITING THIS ALSO EDIT CPU_SLA_MEMORY

	m_CyclesThisUpdate += 16 ;

	BYTE reg = ReadMemory(address) ;

	bool isMSBSet = TestBit(reg, 7);

	reg <<= 1;

	m_RegisterAF.lo = 0 ;

	if (isMSBSet)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C) ;

	if (reg == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;

	WriteByte(address, reg) ;
}
//////////////////////////////////////////////////////////////////////////////////

// shift right. LSB into carry. bit 7 doesn't change
void Emulator::CPU_SRA(BYTE& reg)
{
	// WHEN EDITING THIS FUNCTION ALSO EDIT CPU_SRA_MEMORY

	m_CyclesThisUpdate += 8 ;

	bool isLSBSet = TestBit(reg,0) ;
	bool isMSBSet = TestBit(reg,7) ;

	m_RegisterAF.lo = 0 ;

	reg >>= 1;

	if (isMSBSet)
		reg = BitSet(reg,7) ;
	if (isLSBSet)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C) ;

	if (reg == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;
}

//////////////////////////////////////////////////////////////////////////////////

// shift right. LSB into carry. bit 7 doesn't change
void Emulator::CPU_SRA_MEMORY(WORD address)
{
	// WHEN EDITING THIS FUNCTION ALSO EDIT CPU_SRA

	m_CyclesThisUpdate += 16 ;

	BYTE reg = ReadMemory(address) ;

	bool isLSBSet = TestBit(reg,0) ;
	bool isMSBSet = TestBit(reg,7) ;

	m_RegisterAF.lo = 0 ;

	reg >>= 1;

	if (isMSBSet)
		reg = BitSet(reg,7) ;
	if (isLSBSet)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C) ;

	if (reg == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;

	WriteByte(address, reg) ;
}

//////////////////////////////////////////////////////////////////////////////////

// shift right. bit 0 into carry
void Emulator::CPU_SRL(BYTE& reg)
{
	//WHEN EDITING THIS FUNCTION ALSO EDIT CPU_SRL_MEMORY

	m_CyclesThisUpdate += 8 ;

	bool isLSBSet = TestBit(reg,0) ;

	m_RegisterAF.lo = 0 ;

	reg >>= 1;

	if (isLSBSet)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C) ;

	if (reg == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;

}

//////////////////////////////////////////////////////////////////////////////////

// shift right. bit 0 into carry
void Emulator::CPU_SRL_MEMORY(WORD address)
{
	//WHEN EDITING THIS FUNCTION ALSO EDIT CPU_SRL

	m_CyclesThisUpdate += 8 ;

	BYTE reg = ReadMemory(address) ;

	bool isLSBSet = TestBit(reg,0) ;

	m_RegisterAF.lo = 0 ;

	reg >>= 1;

	if (isLSBSet)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C) ;

	if (reg == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;

	WriteByte(address, reg) ;

}


// rotate left through carry flag
void Emulator::CPU_RL(BYTE& reg)
{
	// WHEN EDITING THIS FUNCTION ALSO EDIT CPU_RL_MEMORY
	m_CyclesThisUpdate += 8 ;

	bool isCarrySet = TestBit(m_RegisterAF.lo, FLAG_C) ;
	bool isMSBSet = TestBit(reg, 7) ;

	m_RegisterAF.lo = 0 ;

	reg <<= 1 ;

	if (isMSBSet)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C) ;

	if (isCarrySet)
		reg = BitSet(reg, 0) ;

	if (reg == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;
}

//////////////////////////////////////////////////////////////////////////////////

// rotate left through carry flag
void Emulator::CPU_RL_MEMORY(WORD address)
{
	// WHEN EDITING THIS FUNCTION ALSO EDIT CPU_RL

	m_CyclesThisUpdate += 16 ;
	BYTE reg = ReadMemory(address) ;

	bool isCarrySet = TestBit(m_RegisterAF.lo, FLAG_C) ;
	bool isMSBSet = TestBit(reg, 7) ;

	m_RegisterAF.lo = 0 ;

	reg <<= 1 ;

	if (isMSBSet)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C) ;

	if (isCarrySet)
		reg = BitSet(reg, 0) ;

	if (reg == 0)
		m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_Z) ;

	WriteByte(address, reg) ;
}

//////////////////////////////////////////////////////////////////////////////////
