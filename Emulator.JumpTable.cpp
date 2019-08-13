#include "Config.h"
#include "Emulator.h"
#include <stdio.h>

void Emulator::ExecuteOpcode(BYTE opcode)
{
	switch(opcode)
	{
		//no-op
		case 0x00: m_CyclesThisUpdate+=4 ; break ;

		// 8-Bit Loads
		case 0x06: CPU_8BIT_LOAD(m_RegisterBC.hi) ; break ;
		case 0x0E: CPU_8BIT_LOAD(m_RegisterBC.lo) ; break ;
		case 0x16: CPU_8BIT_LOAD(m_RegisterDE.hi) ; break ;
		case 0x1E: CPU_8BIT_LOAD(m_RegisterDE.lo) ; break ;
		case 0x26: CPU_8BIT_LOAD(m_RegisterHL.hi) ; break ;
		case 0x2E: CPU_8BIT_LOAD(m_RegisterHL.lo) ; break ;

		// load reg
		case 0x7F: CPU_REG_LOAD(m_RegisterAF.hi, m_RegisterAF.hi, 4) ; break ;
		case 0x78: CPU_REG_LOAD(m_RegisterAF.hi, m_RegisterBC.hi, 4) ; break ;
		case 0x79: CPU_REG_LOAD(m_RegisterAF.hi, m_RegisterBC.lo, 4) ; break ;
		case 0x7A: CPU_REG_LOAD(m_RegisterAF.hi, m_RegisterDE.hi, 4) ; break ;
		case 0x7B: CPU_REG_LOAD(m_RegisterAF.hi, m_RegisterDE.lo, 4) ; break ;
		case 0x7C: CPU_REG_LOAD(m_RegisterAF.hi, m_RegisterHL.hi, 4) ; break ;
		case 0x7D: CPU_REG_LOAD(m_RegisterAF.hi, m_RegisterHL.lo, 4) ; break ;
		case 0x40: CPU_REG_LOAD(m_RegisterBC.hi, m_RegisterBC.hi, 4) ; break ;
		case 0x41: CPU_REG_LOAD(m_RegisterBC.hi, m_RegisterBC.lo, 4) ; break ;
		case 0x42: CPU_REG_LOAD(m_RegisterBC.hi, m_RegisterDE.hi, 4) ; break ;
		case 0x43: CPU_REG_LOAD(m_RegisterBC.hi, m_RegisterDE.lo, 4) ; break ;
		case 0x44: CPU_REG_LOAD(m_RegisterBC.hi, m_RegisterHL.hi, 4) ; break ;
		case 0x45: CPU_REG_LOAD(m_RegisterBC.hi, m_RegisterHL.lo, 4) ; break ;
		case 0x48: CPU_REG_LOAD(m_RegisterBC.lo, m_RegisterBC.hi, 4) ; break ;
		case 0x49: CPU_REG_LOAD(m_RegisterBC.lo, m_RegisterBC.lo, 4) ; break ;
		case 0x4A: CPU_REG_LOAD(m_RegisterBC.lo, m_RegisterDE.hi, 4) ; break ;
		case 0x4B: CPU_REG_LOAD(m_RegisterBC.lo, m_RegisterDE.lo, 4) ; break ;
		case 0x4C: CPU_REG_LOAD(m_RegisterBC.lo, m_RegisterHL.hi, 4) ; break ;
		case 0x4D: CPU_REG_LOAD(m_RegisterBC.lo, m_RegisterHL.lo, 4) ; break ;
		case 0x50: CPU_REG_LOAD(m_RegisterDE.hi, m_RegisterBC.hi, 4) ; break ;
		case 0x51: CPU_REG_LOAD(m_RegisterDE.hi, m_RegisterBC.lo, 4) ; break ;
		case 0x52: CPU_REG_LOAD(m_RegisterDE.hi, m_RegisterDE.hi, 4) ; break ;
		case 0x53: CPU_REG_LOAD(m_RegisterDE.hi, m_RegisterDE.lo, 4) ; break ;
		case 0x54: CPU_REG_LOAD(m_RegisterDE.hi, m_RegisterHL.hi, 4) ; break ;
		case 0x55: CPU_REG_LOAD(m_RegisterDE.hi, m_RegisterHL.lo, 4) ; break ;
		case 0x58: CPU_REG_LOAD(m_RegisterDE.lo, m_RegisterBC.hi, 4) ; break ;
		case 0x59: CPU_REG_LOAD(m_RegisterDE.lo, m_RegisterBC.lo, 4) ; break ;
		case 0x5A: CPU_REG_LOAD(m_RegisterDE.lo, m_RegisterDE.hi, 4) ; break ;
		case 0x5B: CPU_REG_LOAD(m_RegisterDE.lo, m_RegisterDE.lo, 4) ; break ;
		case 0x5C: CPU_REG_LOAD(m_RegisterDE.lo, m_RegisterHL.hi, 4) ; break ;
		case 0x5D: CPU_REG_LOAD(m_RegisterDE.lo, m_RegisterHL.lo, 4) ; break ;
		case 0x60: CPU_REG_LOAD(m_RegisterHL.hi, m_RegisterBC.hi, 4) ; break ;
		case 0x61: CPU_REG_LOAD(m_RegisterHL.hi, m_RegisterBC.lo, 4) ; break ;
		case 0x62: CPU_REG_LOAD(m_RegisterHL.hi, m_RegisterDE.hi, 4) ; break ;
		case 0x63: CPU_REG_LOAD(m_RegisterHL.hi, m_RegisterDE.lo, 4) ; break ;
		case 0x64: CPU_REG_LOAD(m_RegisterHL.hi, m_RegisterHL.hi, 4) ; break ;
		case 0x65: CPU_REG_LOAD(m_RegisterHL.hi, m_RegisterHL.lo, 4) ; break ;
		case 0x68: CPU_REG_LOAD(m_RegisterHL.lo, m_RegisterBC.hi, 4) ; break ;
		case 0x69: CPU_REG_LOAD(m_RegisterHL.lo, m_RegisterBC.lo, 4) ; break ;
		case 0x6A: CPU_REG_LOAD(m_RegisterHL.lo, m_RegisterDE.hi, 4) ; break ;
		case 0x6B: CPU_REG_LOAD(m_RegisterHL.lo, m_RegisterDE.lo, 4) ; break ;
		case 0x6C: CPU_REG_LOAD(m_RegisterHL.lo, m_RegisterHL.hi, 4) ; break ;
		case 0x6D: CPU_REG_LOAD(m_RegisterHL.lo, m_RegisterHL.lo, 4) ; break ;

		// write reg to memory
		case 0x70: WriteByte(m_RegisterHL.reg, m_RegisterBC.hi) ; m_CyclesThisUpdate+=8; break ;
		case 0x71: WriteByte(m_RegisterHL.reg, m_RegisterBC.lo) ; m_CyclesThisUpdate+=8;break ;
		case 0x72: WriteByte(m_RegisterHL.reg, m_RegisterDE.hi) ; m_CyclesThisUpdate+=8;break ;
		case 0x73: WriteByte(m_RegisterHL.reg, m_RegisterDE.lo) ; m_CyclesThisUpdate+=8;break ;
		case 0x74: WriteByte(m_RegisterHL.reg, m_RegisterHL.hi) ; m_CyclesThisUpdate+=8;break ;
		case 0x75: WriteByte(m_RegisterHL.reg, m_RegisterHL.lo) ; m_CyclesThisUpdate+=8;break ;

		// write memory to reg
		case 0x7E: CPU_REG_LOAD_ROM(m_RegisterAF.hi, m_RegisterHL.reg) ; break ;
		case 0x46: CPU_REG_LOAD_ROM(m_RegisterBC.hi, m_RegisterHL.reg) ; break ;
		case 0x4E: CPU_REG_LOAD_ROM(m_RegisterBC.lo, m_RegisterHL.reg) ; break ;
		case 0x56: CPU_REG_LOAD_ROM(m_RegisterDE.hi, m_RegisterHL.reg) ; break ;
		case 0x5E: CPU_REG_LOAD_ROM(m_RegisterDE.lo, m_RegisterHL.reg) ; break ;
		case 0x66: CPU_REG_LOAD_ROM(m_RegisterHL.hi, m_RegisterHL.reg) ; break ;
		case 0x6E: CPU_REG_LOAD_ROM(m_RegisterHL.lo, m_RegisterHL.reg) ; break ;
		case 0x0A: CPU_REG_LOAD_ROM(m_RegisterAF.hi, m_RegisterBC.reg) ; break ;
		case 0x1A: CPU_REG_LOAD_ROM(m_RegisterAF.hi, m_RegisterDE.reg) ; break ;
		case 0xF2: CPU_REG_LOAD_ROM(m_RegisterAF.hi, (0xFF00+m_RegisterBC.lo)) ; break ;



		// put a into register
		case 0x47 : CPU_REG_LOAD(m_RegisterBC.hi, m_RegisterAF.hi, 4) ; break ;
		case 0x4F : CPU_REG_LOAD(m_RegisterBC.lo, m_RegisterAF.hi, 4) ; break ;
		case 0x57 : CPU_REG_LOAD(m_RegisterDE.hi, m_RegisterAF.hi, 4) ; break ;
		case 0x5F : CPU_REG_LOAD(m_RegisterDE.lo, m_RegisterAF.hi, 4) ; break ;
		case 0x67 : CPU_REG_LOAD(m_RegisterHL.hi, m_RegisterAF.hi, 4) ; break ;
		case 0x6F : CPU_REG_LOAD(m_RegisterHL.lo, m_RegisterAF.hi, 4) ; break ;

		// put a into memory address
		case 0x02: WriteByte(m_RegisterBC.reg, m_RegisterAF.hi) ; m_CyclesThisUpdate+=8; break ;
		case 0x12: WriteByte(m_RegisterDE.reg, m_RegisterAF.hi) ; m_CyclesThisUpdate+=8; break ;
		case 0x77: WriteByte(m_RegisterHL.reg, m_RegisterAF.hi) ; m_CyclesThisUpdate+=8; break ;
		case 0xE2: WriteByte((0xFF00+m_RegisterBC.lo), m_RegisterAF.hi) ; m_CyclesThisUpdate+=8; break ;

		// put memory into a, decrement/increment memory
		case 0x3A: CPU_REG_LOAD_ROM(m_RegisterAF.hi,m_RegisterHL.reg ) ; CPU_16BIT_DEC(m_RegisterHL.reg,0) ;break ;
		case 0x2A: CPU_REG_LOAD_ROM(m_RegisterAF.hi,m_RegisterHL.reg ) ; CPU_16BIT_INC(m_RegisterHL.reg,0) ;break ;

		// put a into memory, decrement/increment reg
		case 0x32: WriteByte(m_RegisterHL.reg, m_RegisterAF.hi); CPU_16BIT_DEC(m_RegisterHL.reg,0) ; m_CyclesThisUpdate += 8; break;
		case 0x22: WriteByte(m_RegisterHL.reg, m_RegisterAF.hi); CPU_16BIT_INC(m_RegisterHL.reg,0) ; m_CyclesThisUpdate += 8;break;

		// 16 bit loads
		case 0x01: CPU_16BIT_LOAD( m_RegisterBC.reg ); break ;
		case 0x11: CPU_16BIT_LOAD( m_RegisterDE.reg );break ;
		case 0x21: CPU_16BIT_LOAD( m_RegisterHL.reg );break ;
		case 0x31: CPU_16BIT_LOAD( m_StackPointer.reg );break ;
		case 0xF9: m_StackPointer.reg = m_RegisterHL.reg ; m_CyclesThisUpdate+=8; break ;

		// push word onto stack
		case 0xF5: PushWordOntoStack( m_RegisterAF.reg ) ; m_CyclesThisUpdate+=16 ;break;
		case 0xC5: PushWordOntoStack( m_RegisterBC.reg ) ; m_CyclesThisUpdate+=16 ;break;
		case 0xD5: PushWordOntoStack( m_RegisterDE.reg ) ; m_CyclesThisUpdate+=16 ;break;
		case 0xE5: PushWordOntoStack( m_RegisterHL.reg ) ; m_CyclesThisUpdate+=16 ; break;

		// pop word from stack into reg
		case 0xF1: m_RegisterAF.reg = PopWordOffStack( ) ; m_CyclesThisUpdate+=12 ;break;
		case 0xC1: m_RegisterBC.reg = PopWordOffStack( ) ; m_CyclesThisUpdate+=12 ;break;
		case 0xD1: m_RegisterDE.reg = PopWordOffStack( ) ; m_CyclesThisUpdate+=12 ;break;
		case 0xE1: m_RegisterHL.reg = PopWordOffStack( ) ; m_CyclesThisUpdate+=12 ; break;

		// 8-bit add
		case 0x87: CPU_8BIT_ADD(m_RegisterAF.hi, m_RegisterAF.hi,4,false,false) ; break ;
		case 0x80: CPU_8BIT_ADD(m_RegisterAF.hi, m_RegisterBC.hi,4,false,false) ; break ;
		case 0x81: CPU_8BIT_ADD(m_RegisterAF.hi, m_RegisterBC.lo,4,false,false) ; break ;
		case 0x82: CPU_8BIT_ADD(m_RegisterAF.hi, m_RegisterDE.hi,4,false,false) ; break ;
		case 0x83: CPU_8BIT_ADD(m_RegisterAF.hi, m_RegisterDE.lo,4,false,false) ; break ;
		case 0x84: CPU_8BIT_ADD(m_RegisterAF.hi, m_RegisterHL.hi,4,false,false) ; break ;
		case 0x85: CPU_8BIT_ADD(m_RegisterAF.hi, m_RegisterHL.lo,4,false,false) ; break ;
		case 0x86: CPU_8BIT_ADD(m_RegisterAF.hi, ReadMemory(m_RegisterHL.reg),8,false,false) ; break ;
		case 0xC6: CPU_8BIT_ADD(m_RegisterAF.hi, 0,8,true,false) ; break ;

		// 8-bit add + carry
		case 0x8F: CPU_8BIT_ADD(m_RegisterAF.hi, m_RegisterAF.hi,4,false,true) ; break ;
		case 0x88: CPU_8BIT_ADD(m_RegisterAF.hi, m_RegisterBC.hi,4,false,true) ; break ;
		case 0x89: CPU_8BIT_ADD(m_RegisterAF.hi, m_RegisterBC.lo,4,false,true) ; break ;
		case 0x8A: CPU_8BIT_ADD(m_RegisterAF.hi, m_RegisterDE.hi,4,false,true) ; break ;
		case 0x8B: CPU_8BIT_ADD(m_RegisterAF.hi, m_RegisterDE.lo,4,false,true) ; break ;
		case 0x8C: CPU_8BIT_ADD(m_RegisterAF.hi, m_RegisterHL.hi,4,false,true) ; break ;
		case 0x8D: CPU_8BIT_ADD(m_RegisterAF.hi, m_RegisterHL.lo,4,false,true) ; break ;
		case 0x8E: CPU_8BIT_ADD(m_RegisterAF.hi, ReadMemory(m_RegisterHL.reg),8,false,true) ; break ;
		case 0xCE: CPU_8BIT_ADD(m_RegisterAF.hi, 0,8,true,true) ; break ;

		// 8-bit subtract
		case 0x97: CPU_8BIT_SUB(m_RegisterAF.hi, m_RegisterAF.hi,4,false,false) ; break ;
		case 0x90: CPU_8BIT_SUB(m_RegisterAF.hi, m_RegisterBC.hi,4,false,false) ; break ;
		case 0x91: CPU_8BIT_SUB(m_RegisterAF.hi, m_RegisterBC.lo,4,false,false) ; break ;
		case 0x92: CPU_8BIT_SUB(m_RegisterAF.hi, m_RegisterDE.hi,4,false,false) ; break ;
		case 0x93: CPU_8BIT_SUB(m_RegisterAF.hi, m_RegisterDE.lo,4,false,false) ; break ;
		case 0x94: CPU_8BIT_SUB(m_RegisterAF.hi, m_RegisterHL.hi,4,false,false) ; break ;
		case 0x95: CPU_8BIT_SUB(m_RegisterAF.hi, m_RegisterHL.lo,4,false,false) ; break ;
		case 0x96: CPU_8BIT_SUB(m_RegisterAF.hi, ReadMemory(m_RegisterHL.reg),8,false,false) ; break ;
		case 0xD6: CPU_8BIT_SUB(m_RegisterAF.hi, 0,8,true,false) ; break ;

		// 8-bit subtract + carry
		case 0x9F: CPU_8BIT_SUB(m_RegisterAF.hi, m_RegisterAF.hi,4,false,true) ; break ;
		case 0x98: CPU_8BIT_SUB(m_RegisterAF.hi, m_RegisterBC.hi,4,false,true) ; break ;
		case 0x99: CPU_8BIT_SUB(m_RegisterAF.hi, m_RegisterBC.lo,4,false,true) ; break ;
		case 0x9A: CPU_8BIT_SUB(m_RegisterAF.hi, m_RegisterDE.hi,4,false,true) ; break ;
		case 0x9B: CPU_8BIT_SUB(m_RegisterAF.hi, m_RegisterDE.lo,4,false,true) ; break ;
		case 0x9C: CPU_8BIT_SUB(m_RegisterAF.hi, m_RegisterHL.hi,4,false,true) ; break ;
		case 0x9D: CPU_8BIT_SUB(m_RegisterAF.hi, m_RegisterHL.lo,4,false,true) ; break ;
		case 0x9E: CPU_8BIT_SUB(m_RegisterAF.hi, ReadMemory(m_RegisterHL.reg),8,false,true) ; break ;
		case 0xDE: CPU_8BIT_SUB(m_RegisterAF.hi, 0,8,true,true) ; break ;

		// 8-bit AND reg with reg
		case 0xA7: CPU_8BIT_AND(m_RegisterAF.hi, m_RegisterAF.hi,4, false) ; break ;
		case 0xA0: CPU_8BIT_AND(m_RegisterAF.hi, m_RegisterBC.hi,4, false) ; break ;
		case 0xA1: CPU_8BIT_AND(m_RegisterAF.hi, m_RegisterBC.lo,4, false) ; break ;
		case 0xA2: CPU_8BIT_AND(m_RegisterAF.hi, m_RegisterDE.hi,4, false) ; break ;
		case 0xA3: CPU_8BIT_AND(m_RegisterAF.hi, m_RegisterDE.lo,4, false) ; break ;
		case 0xA4: CPU_8BIT_AND(m_RegisterAF.hi, m_RegisterHL.hi,4, false) ; break ;
		case 0xA5: CPU_8BIT_AND(m_RegisterAF.hi, m_RegisterHL.lo,4, false) ; break ;
		case 0xA6: CPU_8BIT_AND(m_RegisterAF.hi, ReadMemory(m_RegisterHL.reg),8, false) ; break ;
		case 0xE6: CPU_8BIT_AND(m_RegisterAF.hi, 0,8, true) ; break ;

		// 8-bit OR reg with reg
		case 0xB7: CPU_8BIT_OR(m_RegisterAF.hi, m_RegisterAF.hi,4, false) ; break ;
		case 0xB0: CPU_8BIT_OR(m_RegisterAF.hi, m_RegisterBC.hi,4, false) ; break ;
		case 0xB1: CPU_8BIT_OR(m_RegisterAF.hi, m_RegisterBC.lo,4, false) ; break ;
		case 0xB2: CPU_8BIT_OR(m_RegisterAF.hi, m_RegisterDE.hi,4, false) ; break ;
		case 0xB3: CPU_8BIT_OR(m_RegisterAF.hi, m_RegisterDE.lo,4, false) ; break ;
		case 0xB4: CPU_8BIT_OR(m_RegisterAF.hi, m_RegisterHL.hi,4, false) ; break ;
		case 0xB5: CPU_8BIT_OR(m_RegisterAF.hi, m_RegisterHL.lo,4, false) ; break ;
		case 0xB6: CPU_8BIT_OR(m_RegisterAF.hi, ReadMemory(m_RegisterHL.reg),8, false) ; break ;
		case 0xF6: CPU_8BIT_OR(m_RegisterAF.hi, 0,8, true) ; break ;

		// 8-bit XOR reg with reg
		case 0xAF: CPU_8BIT_XOR(m_RegisterAF.hi, m_RegisterAF.hi,4, false) ; break ;
		case 0xA8: CPU_8BIT_XOR(m_RegisterAF.hi, m_RegisterBC.hi,4, false) ; break ;
		case 0xA9: CPU_8BIT_XOR(m_RegisterAF.hi, m_RegisterBC.lo,4, false) ; break ;
		case 0xAA: CPU_8BIT_XOR(m_RegisterAF.hi, m_RegisterDE.hi,4, false) ; break ;
		case 0xAB: CPU_8BIT_XOR(m_RegisterAF.hi, m_RegisterDE.lo,4, false) ; break ;
		case 0xAC: CPU_8BIT_XOR(m_RegisterAF.hi, m_RegisterHL.hi,4, false) ; break ;
		case 0xAD: CPU_8BIT_XOR(m_RegisterAF.hi, m_RegisterHL.lo,4, false) ; break ;
		case 0xAE: CPU_8BIT_XOR(m_RegisterAF.hi, ReadMemory(m_RegisterHL.reg),8, false) ; break ;
		case 0xEE: CPU_8BIT_XOR(m_RegisterAF.hi, 0,8, true) ; break ;

		// 8-Bit compare
		case 0xBF: CPU_8BIT_COMPARE(m_RegisterAF.hi, m_RegisterAF.hi,4, false) ; break ;
		case 0xB8: CPU_8BIT_COMPARE(m_RegisterAF.hi, m_RegisterBC.hi,4, false) ; break ;
		case 0xB9: CPU_8BIT_COMPARE(m_RegisterAF.hi, m_RegisterBC.lo,4, false) ; break ;
		case 0xBA: CPU_8BIT_COMPARE(m_RegisterAF.hi, m_RegisterDE.hi,4, false) ; break ;
		case 0xBB: CPU_8BIT_COMPARE(m_RegisterAF.hi, m_RegisterDE.lo,4, false) ; break ;
		case 0xBC: CPU_8BIT_COMPARE(m_RegisterAF.hi, m_RegisterHL.hi,4, false) ; break ;
		case 0xBD: CPU_8BIT_COMPARE(m_RegisterAF.hi, m_RegisterHL.lo,4, false) ; break ;
		case 0xBE: CPU_8BIT_COMPARE(m_RegisterAF.hi, ReadMemory(m_RegisterHL.reg),8, false) ; break ;
		case 0xFE: CPU_8BIT_COMPARE(m_RegisterAF.hi, 0,8, true) ; break ;

		// 8-bit inc
		case 0x3C: CPU_8BIT_INC(m_RegisterAF.hi,4); break ;
		case 0x04: CPU_8BIT_INC(m_RegisterBC.hi,4); break ;
		case 0x0C: CPU_8BIT_INC(m_RegisterBC.lo,4); break ;
		case 0x14: CPU_8BIT_INC(m_RegisterDE.hi,4); break ;
		case 0x1C: CPU_8BIT_INC(m_RegisterDE.lo,4); break ;
		case 0x24: CPU_8BIT_INC(m_RegisterHL.hi,4); break ;
		case 0x2C: CPU_8BIT_INC(m_RegisterHL.lo,4); break ;
		case 0x34: CPU_8BIT_MEMORY_INC(m_RegisterHL.reg,12); break ;

		// 8-bit dec
		case 0x3D: CPU_8BIT_DEC(m_RegisterAF.hi,4); break ;
		case 0x05: CPU_8BIT_DEC(m_RegisterBC.hi,4); break ;
		case 0x0D: CPU_8BIT_DEC(m_RegisterBC.lo,4); break ;
		case 0x15: CPU_8BIT_DEC(m_RegisterDE.hi,4); break ;
		case 0x1D: CPU_8BIT_DEC(m_RegisterDE.lo,4); break ;
		case 0x25: CPU_8BIT_DEC(m_RegisterHL.hi,4); break ;
		case 0x2D: CPU_8BIT_DEC(m_RegisterHL.lo,4); break ;
		case 0x35: CPU_8BIT_MEMORY_DEC(m_RegisterHL.reg,12); break ;

		// 16-bit add
		case 0x09: CPU_16BIT_ADD(m_RegisterHL.reg,m_RegisterBC.reg,8) ; break ;
		case 0x19: CPU_16BIT_ADD(m_RegisterHL.reg,m_RegisterDE.reg,8) ; break ;
		case 0x29: CPU_16BIT_ADD(m_RegisterHL.reg,m_RegisterHL.reg,8) ; break ;
		case 0x39: CPU_16BIT_ADD(m_RegisterHL.reg,m_StackPointer.reg,8) ; break ;

		// inc 16-bit register
		case 0x03: CPU_16BIT_INC( m_RegisterBC.reg, 8) ; break ;
		case 0x13: CPU_16BIT_INC( m_RegisterDE.reg, 8) ; break ;
		case 0x23: CPU_16BIT_INC( m_RegisterHL.reg, 8) ; break ;
		case 0x33: CPU_16BIT_INC( m_StackPointer.reg, 8) ; break ;

		// dec 16-bit register
		case 0x0B: CPU_16BIT_DEC( m_RegisterBC.reg, 8) ; break ;
		case 0x1B: CPU_16BIT_DEC( m_RegisterDE.reg, 8) ; break ;
		case 0x2B: CPU_16BIT_DEC( m_RegisterHL.reg, 8) ; break ;
		case 0x3B: CPU_16BIT_DEC( m_StackPointer.reg, 8) ; break ;

		// jumps
		case 0xE9: m_CyclesThisUpdate+=4 ; m_ProgramCounter = m_RegisterHL.reg ; break ;
		case 0xC3: CPU_JUMP(false, 0, false) ; break ;
		case 0xC2: CPU_JUMP(true, FLAG_Z, false) ; break ;
		case 0xCA: CPU_JUMP(true, FLAG_Z, true) ; break ;
		case 0xD2: CPU_JUMP(true, FLAG_C, false) ; break ;
		case 0xDA: CPU_JUMP(true, FLAG_C, true) ; break ;

		// jump with immediate data
		case 0x18 : CPU_JUMP_IMMEDIATE( false, 0, false ) ; break ;
		case 0x20 : CPU_JUMP_IMMEDIATE( true, FLAG_Z, false ) ;break ;
		case 0x28 : CPU_JUMP_IMMEDIATE( true, FLAG_Z, true ) ;break ;
		case 0x30 : CPU_JUMP_IMMEDIATE( true, FLAG_C, false) ;break ;
		case 0x38 : CPU_JUMP_IMMEDIATE( true, FLAG_C, true ) ;break ;

		// calls
		case 0xCD : CPU_CALL( false, 0, false) ; break ;
		case 0xC4 : CPU_CALL( true, FLAG_Z, false) ;break ;
		case 0xCC : CPU_CALL( true, FLAG_Z, true) ;break ;
		case 0xD4 : CPU_CALL( true, FLAG_C, false) ;break ;
		case 0xDC : CPU_CALL( true, FLAG_C, true) ; break ;

		// returns
		case 0xC9: CPU_RETURN( false, 0, false ) ; break ;
		case 0xC0: CPU_RETURN( true, FLAG_Z, false ) ; break ;
		case 0xC8: CPU_RETURN( true, FLAG_Z, true ) ; break ;
		case 0xD0: CPU_RETURN( true, FLAG_C, false ) ; break ;
		case 0xD8: CPU_RETURN( true, FLAG_C, true ) ; break ;


		// restarts
		case 0xC7: CPU_RESTARTS( 0x00 ) ; break ;
		case 0xCF: CPU_RESTARTS( 0x08 ) ; break ;
		case 0xD7: CPU_RESTARTS( 0x10 ) ; break ;
		case 0xDF: CPU_RESTARTS( 0x18 ) ; break ;
		case 0xE7: CPU_RESTARTS( 0x20 ) ; break ;
		case 0xEF: CPU_RESTARTS( 0x28 ) ; break ;
		case 0xF7: CPU_RESTARTS( 0x30 ) ; break ;
		case 0xFF: CPU_RESTARTS( 0x38 ) ; break ;

		case 0x27: CPU_DAA( ) ; break ;

		// handle the extended opcodes
		case 0xCB: ExecuteExtendedOpcode( ) ; break ;

		// unique instructions
		case 0x07:CPU_RLC(m_RegisterAF.hi); break ;
		case 0x0F:CPU_RRC(m_RegisterAF.hi) ;	break ;
		case 0x17:CPU_RL(m_RegisterAF.hi) ; break ;
		case 0x1F:CPU_RR(m_RegisterAF.hi) ;	break ;

		case 0xD9:
		{
			//LOGMESSAGE(Logging::MSG_INFO, "Returning from iterupt") ;
			m_ProgramCounter = PopWordOffStack( ) ;
			m_EnableInterupts = true ;
			m_CyclesThisUpdate+=8 ;
			LogMessage::GetSingleton()->DoLogMessage("Returning from interupt", false) ;
		}break ;

		case 0x08:
		{
			WORD nn = ReadWord( ) ;
			m_ProgramCounter+=2 ;
			WriteByte(nn, m_StackPointer.lo) ;
			nn++ ;
			WriteByte(nn, m_StackPointer.hi) ;
			m_CyclesThisUpdate += 20 ;
		}break ;

		case 0x36:
		{
			m_CyclesThisUpdate+=12 ;
			BYTE n = ReadMemory(m_ProgramCounter) ;
			m_ProgramCounter++;
			WriteByte(m_RegisterHL.reg, n) ;
		}break ;

		case 0xFA:
		{
			m_CyclesThisUpdate+=16 ;
			WORD nn = ReadWord( ) ;
			m_ProgramCounter+=2 ;
			BYTE n = ReadMemory(nn) ;
			m_RegisterAF.hi = n ;
		}break ;

		case 0x3E:
		{
			m_CyclesThisUpdate+=8;
			BYTE n = ReadMemory(m_ProgramCounter) ;
			m_ProgramCounter++ ;
			m_RegisterAF.hi = n;
		}break ;
		case 0xEA:
		{
			m_CyclesThisUpdate+=16 ;
			WORD nn = ReadWord( ) ;
			m_ProgramCounter+=2 ;
			WriteByte(nn, m_RegisterAF.hi) ;
		}break ;

		case 0xF3:
		{
			m_PendingInteruptDisabled = true ;
			m_CyclesThisUpdate+=4 ;
		}break ;

		case 0xFB:
		{
			m_PendingInteruptEnabled = true ;
			m_CyclesThisUpdate+=4 ;
		}break ;

		case 0xE0:
		{
			BYTE n = ReadMemory(m_ProgramCounter) ;
			m_ProgramCounter++ ;
			WORD address = 0xFF00 + n ;
			WriteByte(address, m_RegisterAF.hi) ;
			m_CyclesThisUpdate += 12 ;
		}break ;

		case 0xF0:
		{
			BYTE n = ReadMemory(m_ProgramCounter) ;
			m_ProgramCounter++ ;
			WORD address = 0xFF00 + n ;
			m_RegisterAF.hi = ReadMemory( address ) ;
			m_CyclesThisUpdate+=12 ;
		}break ;

		case 0x2F:
		{
			m_CyclesThisUpdate += 4;
			m_RegisterAF.hi ^= 0xFF;

			m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_N) ;
			m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_H) ;
		}break ;

		case 0x76:
		{
			//LOGMESSAGE(Logging::MSG_INFO, "Halting cpu") ;
			m_CyclesThisUpdate += 4 ;
			m_Halted = true ;
		}break ;

		case 0x3F:
		{
			m_CyclesThisUpdate += 4 ;
			if (TestBit(m_RegisterAF.lo, FLAG_C))
				m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_C) ;
			else
				m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C) ;

			m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_H) ;
			m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_N) ;
		}break ;

		case 0x37:
		{
			m_CyclesThisUpdate += 4;
			m_RegisterAF.lo = BitSet(m_RegisterAF.lo, FLAG_C);
			m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_H);
			m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_N);
		} break ;

		case 0xF8:
		{
			SIGNED_BYTE n = ReadMemory(m_ProgramCounter) ;
			m_ProgramCounter++ ;
			m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_Z);
			m_RegisterAF.lo = BitReset(m_RegisterAF.lo, FLAG_N);


			WORD value = (m_StackPointer.reg + n) & 0xFFFF;

			m_RegisterHL.reg = value ;
			unsigned int v = m_StackPointer.reg + n ;

			if( n > 0xFFFF )
				m_RegisterAF.lo = BitSet(m_RegisterAF.lo,FLAG_C) ;
			else
				m_RegisterAF.lo = BitReset(m_RegisterAF.lo,FLAG_C) ;

			if( (m_StackPointer.reg & 0xF) + (n & 0xF) > 0xF )
				m_RegisterAF.lo = BitSet(m_RegisterAF.lo,FLAG_H) ;
			else
				m_RegisterAF.lo = BitReset(m_RegisterAF.lo,FLAG_H) ;

		}break ;

		case 0x10:
		{
			m_ProgramCounter++ ;
			m_CyclesThisUpdate+= 4 ;
		}break ;

		default:
		{
		    char mybuf[200] ;
		    sprintf(mybuf, "Unhandled Opcode %x", opcode) ;
		    LogMessage::GetSingleton()->DoLogMessage(mybuf,true) ;
			assert(false) ;
		} break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////

void Emulator::ExecuteExtendedOpcode( )
{
	BYTE opcode = m_Rom[m_ProgramCounter] ;

	if ((m_ProgramCounter >= 0x4000 && m_ProgramCounter <= 0x7FFF) || (m_ProgramCounter >= 0xA000 && m_ProgramCounter <= 0xBFFF))
		opcode = ReadMemory(m_ProgramCounter) ;

	if (false)
	{
		char buffer[200] ;
		sprintf(buffer, "EXTENDEDOP = %x PC = %x\n", opcode, m_ProgramCounter) ;
		LogMessage::GetSingleton()->DoLogMessage(buffer,false) ;
	}

	m_ProgramCounter++ ;

	//LOGMESSAGE(Logging::MSG_INFO, STR::Format("Processing Extended Opcode %x, Program Counter: %x", opcode, m_ProgramCounter).ConstCharPtr()) ;

	switch(opcode)
	{
		// rotate left through carry
  		case 0x0 : CPU_RLC(m_RegisterBC.hi) ; break ;
  		case 0x1 : CPU_RLC(m_RegisterBC.lo) ; break ;
  		case 0x2 : CPU_RLC(m_RegisterDE.hi) ; break ;
  		case 0x3 : CPU_RLC(m_RegisterDE.lo) ; break ;
  		case 0x4 : CPU_RLC(m_RegisterHL.hi) ; break ;
  		case 0x5 : CPU_RLC(m_RegisterHL.lo) ; break ;
  		case 0x6 : CPU_RLC_MEMORY(m_RegisterHL.reg) ; break ;
  		case 0x7 : CPU_RLC(m_RegisterAF.hi) ; break ;

  		// rotate right through carry
  		case 0x8 : CPU_RRC(m_RegisterBC.hi) ; break ;
  		case 0x9 : CPU_RRC(m_RegisterBC.lo) ; break ;
  		case 0xA : CPU_RRC(m_RegisterDE.hi) ; break ;
  		case 0xB : CPU_RRC(m_RegisterDE.lo) ; break ;
  		case 0xC : CPU_RRC(m_RegisterHL.hi) ; break ;
  		case 0xD : CPU_RRC(m_RegisterHL.lo) ; break ;
  		case 0xE : CPU_RRC_MEMORY(m_RegisterHL.reg) ; break ;
  		case 0xF : CPU_RRC(m_RegisterAF.hi) ; break ;

  		// rotate left
  		case 0x10: CPU_RL(m_RegisterBC.hi); break;
  		case 0x11: CPU_RL(m_RegisterBC.lo); break;
	  	case 0x12: CPU_RL(m_RegisterDE.hi); break;
  		case 0x13: CPU_RL(m_RegisterDE.lo); break;
  		case 0x14: CPU_RL(m_RegisterHL.hi); break;
  		case 0x15: CPU_RL(m_RegisterHL.lo); break;
  		case 0x16: CPU_RL_MEMORY(m_RegisterHL.reg); break;
  		case 0x17: CPU_RL(m_RegisterAF.hi); break;

  		// rotate right
  		case 0x18: CPU_RR(m_RegisterBC.hi); break;
  		case 0x19: CPU_RR(m_RegisterBC.lo); break;
  		case 0x1A: CPU_RR(m_RegisterDE.hi); break;
  		case 0x1B: CPU_RR(m_RegisterDE.lo); break;
  		case 0x1C: CPU_RR(m_RegisterHL.hi); break;
  		case 0x1D: CPU_RR(m_RegisterHL.lo); break;
  		case 0x1E: CPU_RR_MEMORY(m_RegisterHL.reg); break;
  		case 0x1F: CPU_RR(m_RegisterAF.hi); break;

  		case 0x20 : CPU_SLA( m_RegisterBC.hi ) ;break ;
  		case 0x21 : CPU_SLA( m_RegisterBC.lo ) ;break ;
  		case 0x22 : CPU_SLA( m_RegisterDE.hi ) ;break ;
	  	case 0x23 : CPU_SLA( m_RegisterDE.lo ) ;break ;
  		case 0x24 : CPU_SLA( m_RegisterHL.hi ) ;break ;
  		case 0x25 : CPU_SLA( m_RegisterHL.lo ) ;break ;
  		case 0x26 : CPU_SLA_MEMORY( m_RegisterHL.reg ) ;break ;
		case 0x27 : CPU_SLA( m_RegisterAF.hi ) ;break ;

  		case 0x28 : CPU_SRA( m_RegisterBC.hi ) ; break ;
  		case 0x29 : CPU_SRA( m_RegisterBC.lo ) ; break ;
  		case 0x2A : CPU_SRA( m_RegisterDE.hi ) ; break ;
  		case 0x2B : CPU_SRA( m_RegisterDE.lo ) ; break ;
  		case 0x2C : CPU_SRA( m_RegisterHL.hi ) ; break ;
  		case 0x2D : CPU_SRA( m_RegisterHL.lo ) ; break ;
  		case 0x2E : CPU_SRA_MEMORY( m_RegisterHL.reg ) ; break ;
  		case 0x2F : CPU_SRA( m_RegisterAF.hi ) ; break ;

  		case 0x38 : CPU_SRL( m_RegisterBC.hi ) ; break ;
  		case 0x39 : CPU_SRL( m_RegisterBC.lo ) ; break ;
  		case 0x3A : CPU_SRL( m_RegisterDE.hi ) ; break ;
  		case 0x3B : CPU_SRL( m_RegisterDE.lo ) ; break ;
  		case 0x3C : CPU_SRL( m_RegisterHL.hi ) ; break ;
  		case 0x3D : CPU_SRL( m_RegisterHL.lo ) ; break ;
  		case 0x3E : CPU_SRL_MEMORY( m_RegisterHL.reg ) ; break ;
	  	case 0x3F : CPU_SRL( m_RegisterAF.hi ) ; break ;

			// swap nibbles
		case 0x37 : CPU_SWAP_NIBBLES( m_RegisterAF.hi ) ;break ;
		case 0x30 : CPU_SWAP_NIBBLES( m_RegisterBC.hi ) ;break ;
		case 0x31 : CPU_SWAP_NIBBLES( m_RegisterBC.lo ) ;break ;
		case 0x32 : CPU_SWAP_NIBBLES( m_RegisterDE.hi ) ;break ;
		case 0x33 : CPU_SWAP_NIBBLES( m_RegisterDE.lo ) ;break ;
		case 0x34 : CPU_SWAP_NIBBLES( m_RegisterHL.hi ) ;break ;
		case 0x35 : CPU_SWAP_NIBBLES( m_RegisterHL.lo ) ;break ;
		case 0x36 : CPU_SWAP_NIB_MEM( m_RegisterHL.reg ) ;break ;

		// test bit
		case 0x40 : CPU_TEST_BIT( m_RegisterBC.hi, 0 , 8 ) ; break ;
		case 0x41 : CPU_TEST_BIT( m_RegisterBC.lo, 0 , 8 ) ; break ;
		case 0x42 : CPU_TEST_BIT( m_RegisterDE.hi, 0 , 8 ) ; break ;
		case 0x43 : CPU_TEST_BIT( m_RegisterDE.lo, 0 , 8 ) ; break ;
		case 0x44 : CPU_TEST_BIT( m_RegisterHL.hi, 0 , 8 ) ; break ;
		case 0x45 : CPU_TEST_BIT( m_RegisterHL.lo, 0 , 8 ) ; break ;
		case 0x46 : CPU_TEST_BIT( ReadMemory(m_RegisterHL.reg), 0 , 16 ) ; break ;
		case 0x47 : CPU_TEST_BIT( m_RegisterAF.hi, 0 , 8 ) ; break ;
		case 0x48 : CPU_TEST_BIT( m_RegisterBC.hi, 1 , 8 ) ; break ;
		case 0x49 : CPU_TEST_BIT( m_RegisterBC.lo, 1 , 8 ) ; break ;
		case 0x4A : CPU_TEST_BIT( m_RegisterDE.hi, 1 , 8 ) ; break ;
		case 0x4B : CPU_TEST_BIT( m_RegisterDE.lo, 1 , 8 ) ; break ;
		case 0x4C : CPU_TEST_BIT( m_RegisterHL.hi, 1 , 8 ) ; break ;
		case 0x4D : CPU_TEST_BIT( m_RegisterHL.lo, 1 , 8 ) ; break ;
		case 0x4E : CPU_TEST_BIT( ReadMemory(m_RegisterHL.reg), 1 , 16 ) ; break ;
		case 0x4F : CPU_TEST_BIT( m_RegisterAF.hi, 1 , 8 ) ; break ;
		case 0x50 : CPU_TEST_BIT( m_RegisterBC.hi, 2 , 8 ) ; break ;
		case 0x51 : CPU_TEST_BIT( m_RegisterBC.lo, 2 , 8 ) ; break ;
		case 0x52 : CPU_TEST_BIT( m_RegisterDE.hi, 2 , 8 ) ; break ;
		case 0x53 : CPU_TEST_BIT( m_RegisterDE.lo, 2 , 8 ) ; break ;
		case 0x54 : CPU_TEST_BIT( m_RegisterHL.hi, 2 , 8 ) ; break ;
		case 0x55 : CPU_TEST_BIT( m_RegisterHL.lo, 2 , 8 ) ; break ;
		case 0x56 : CPU_TEST_BIT( ReadMemory(m_RegisterHL.reg), 2 , 16 ) ; break ;
		case 0x57 : CPU_TEST_BIT( m_RegisterAF.hi, 2 , 8 ) ; break ;
		case 0x58 : CPU_TEST_BIT( m_RegisterBC.hi, 3 , 8 ) ; break ;
		case 0x59 : CPU_TEST_BIT( m_RegisterBC.lo, 3 , 8 ) ; break ;
		case 0x5A : CPU_TEST_BIT( m_RegisterDE.hi, 3 , 8 ) ; break ;
		case 0x5B : CPU_TEST_BIT( m_RegisterDE.lo, 3 , 8 ) ; break ;
		case 0x5C : CPU_TEST_BIT( m_RegisterHL.hi, 3 , 8 ) ; break ;
		case 0x5D : CPU_TEST_BIT( m_RegisterHL.lo, 3 , 8 ) ; break ;
		case 0x5E : CPU_TEST_BIT( ReadMemory(m_RegisterHL.reg), 3 , 16 ) ; break ;
		case 0x5F : CPU_TEST_BIT( m_RegisterAF.hi, 3 , 8 ) ; break ;
		case 0x60 : CPU_TEST_BIT( m_RegisterBC.hi, 4 , 8 ) ; break ;
		case 0x61 : CPU_TEST_BIT( m_RegisterBC.lo, 4 , 8 ) ; break ;
		case 0x62 : CPU_TEST_BIT( m_RegisterDE.hi, 4 , 8 ) ; break ;
		case 0x63 : CPU_TEST_BIT( m_RegisterDE.lo, 4 , 8 ) ; break ;
		case 0x64 : CPU_TEST_BIT( m_RegisterHL.hi, 4 , 8 ) ; break ;
		case 0x65 : CPU_TEST_BIT( m_RegisterHL.lo, 4 , 8 ) ; break ;
		case 0x66 : CPU_TEST_BIT( ReadMemory(m_RegisterHL.reg), 4 , 16 ) ; break ;
		case 0x67 : CPU_TEST_BIT( m_RegisterAF.hi, 4 , 8 ) ; break ;
		case 0x68 : CPU_TEST_BIT( m_RegisterBC.hi, 5 , 8 ) ; break ;
		case 0x69 : CPU_TEST_BIT( m_RegisterBC.lo, 5 , 8 ) ; break ;
		case 0x6A : CPU_TEST_BIT( m_RegisterDE.hi, 5 , 8 ) ; break ;
		case 0x6B : CPU_TEST_BIT( m_RegisterDE.lo, 5 , 8 ) ; break ;
		case 0x6C : CPU_TEST_BIT( m_RegisterHL.hi, 5 , 8 ) ; break ;
		case 0x6D : CPU_TEST_BIT( m_RegisterHL.lo, 5 , 8 ) ; break ;
		case 0x6E : CPU_TEST_BIT( ReadMemory(m_RegisterHL.reg), 5 , 16 ) ; break ;
		case 0x6F : CPU_TEST_BIT( m_RegisterAF.hi, 5 , 8 ) ; break ;
		case 0x70 : CPU_TEST_BIT( m_RegisterBC.hi, 6 , 8 ) ; break ;
		case 0x71 : CPU_TEST_BIT( m_RegisterBC.lo, 6 , 8 ) ; break ;
		case 0x72 : CPU_TEST_BIT( m_RegisterDE.hi, 6 , 8 ) ; break ;
		case 0x73 : CPU_TEST_BIT( m_RegisterDE.lo, 6 , 8 ) ; break ;
		case 0x74 : CPU_TEST_BIT( m_RegisterHL.hi, 6 , 8 ) ; break ;
		case 0x75 : CPU_TEST_BIT( m_RegisterHL.lo, 6 , 8 ) ; break ;
		case 0x76 : CPU_TEST_BIT( ReadMemory(m_RegisterHL.reg), 6 , 16 ) ; break ;
		case 0x77 : CPU_TEST_BIT( m_RegisterAF.hi, 6 , 8 ) ; break ;
		case 0x78 : CPU_TEST_BIT( m_RegisterBC.hi, 7 , 8 ) ; break ;
		case 0x79 : CPU_TEST_BIT( m_RegisterBC.lo, 7 , 8 ) ; break ;
		case 0x7A : CPU_TEST_BIT( m_RegisterDE.hi, 7 , 8 ) ; break ;
		case 0x7B : CPU_TEST_BIT( m_RegisterDE.lo, 7 , 8 ) ; break ;
		case 0x7C : CPU_TEST_BIT( m_RegisterHL.hi, 7 , 8 ) ; break ;
		case 0x7D : CPU_TEST_BIT( m_RegisterHL.lo, 7 , 8 ) ; break ;
		case 0x7E : CPU_TEST_BIT( ReadMemory(m_RegisterHL.reg), 7 , 16 ) ; break ;
		case 0x7F : CPU_TEST_BIT( m_RegisterAF.hi, 7 , 8 ) ; break ;

		// reset bit
		case 0x80 : CPU_RESET_BIT( m_RegisterBC.hi, 0 ) ; break ;
		case 0x81 : CPU_RESET_BIT( m_RegisterBC.lo, 0 ) ; break ;
		case 0x82 : CPU_RESET_BIT( m_RegisterDE.hi, 0 ) ; break ;
		case 0x83 : CPU_RESET_BIT( m_RegisterDE.lo, 0 ) ; break ;
		case 0x84 : CPU_RESET_BIT( m_RegisterHL.hi, 0 ) ; break ;
		case 0x85 : CPU_RESET_BIT( m_RegisterHL.lo, 0 ) ; break ;
		case 0x86 : CPU_RESET_BIT_MEMORY( m_RegisterHL.reg, 0 ) ; break ;
		case 0x87 : CPU_RESET_BIT( m_RegisterAF.hi, 0 ) ; break ;
		case 0x88 : CPU_RESET_BIT( m_RegisterBC.hi, 1  ) ; break ;
		case 0x89 : CPU_RESET_BIT( m_RegisterBC.lo, 1 ) ; break ;
		case 0x8A : CPU_RESET_BIT( m_RegisterDE.hi, 1 ) ; break ;
		case 0x8B : CPU_RESET_BIT( m_RegisterDE.lo, 1 ) ; break ;
		case 0x8C : CPU_RESET_BIT( m_RegisterHL.hi, 1 ) ; break ;
		case 0x8D : CPU_RESET_BIT( m_RegisterHL.lo, 1 ) ; break ;
		case 0x8E : CPU_RESET_BIT_MEMORY( m_RegisterHL.reg, 1 ) ; break ;
		case 0x8F : CPU_RESET_BIT( m_RegisterAF.hi, 1  ) ; break ;
		case 0x90 : CPU_RESET_BIT( m_RegisterBC.hi, 2  ) ; break ;
		case 0x91 : CPU_RESET_BIT( m_RegisterBC.lo, 2  ) ; break ;
		case 0x92 : CPU_RESET_BIT( m_RegisterDE.hi, 2  ) ; break ;
		case 0x93 : CPU_RESET_BIT( m_RegisterDE.lo, 2  ) ; break ;
		case 0x94 : CPU_RESET_BIT( m_RegisterHL.hi, 2  ) ; break ;
		case 0x95 : CPU_RESET_BIT( m_RegisterHL.lo, 2  ) ; break ;
		case 0x96 : CPU_RESET_BIT_MEMORY( m_RegisterHL.reg, 2 ) ; break ;
		case 0x97 : CPU_RESET_BIT( m_RegisterAF.hi, 2  ) ; break ;
		case 0x98 : CPU_RESET_BIT( m_RegisterBC.hi, 3  ) ; break ;
		case 0x99 : CPU_RESET_BIT( m_RegisterBC.lo, 3  ) ; break ;
		case 0x9A : CPU_RESET_BIT( m_RegisterDE.hi, 3  ) ; break ;
		case 0x9B : CPU_RESET_BIT( m_RegisterDE.lo, 3  ) ; break ;
		case 0x9C : CPU_RESET_BIT( m_RegisterHL.hi, 3  ) ; break ;
		case 0x9D : CPU_RESET_BIT( m_RegisterHL.lo, 3  ) ; break ;
		case 0x9E : CPU_RESET_BIT_MEMORY( m_RegisterHL.reg, 3  ) ; break ;
		case 0x9F : CPU_RESET_BIT( m_RegisterAF.hi, 3  ) ; break ;
		case 0xA0 : CPU_RESET_BIT( m_RegisterBC.hi, 4  ) ; break ;
		case 0xA1 : CPU_RESET_BIT( m_RegisterBC.lo, 4  ) ; break ;
		case 0xA2 : CPU_RESET_BIT( m_RegisterDE.hi, 4  ) ; break ;
		case 0xA3 : CPU_RESET_BIT( m_RegisterDE.lo, 4  ) ; break ;
		case 0xA4 : CPU_RESET_BIT( m_RegisterHL.hi, 4  ) ; break ;
		case 0xA5 : CPU_RESET_BIT( m_RegisterHL.lo, 4  ) ; break ;
		case 0xA6 : CPU_RESET_BIT_MEMORY( m_RegisterHL.reg, 4) ; break ;
		case 0xA7 : CPU_RESET_BIT( m_RegisterAF.hi, 4 ) ; break ;
		case 0xA8 : CPU_RESET_BIT( m_RegisterBC.hi, 5 ) ; break ;
		case 0xA9 : CPU_RESET_BIT( m_RegisterBC.lo, 5 ) ; break ;
		case 0xAA : CPU_RESET_BIT( m_RegisterDE.hi, 5 ) ; break ;
		case 0xAB : CPU_RESET_BIT( m_RegisterDE.lo, 5 ) ; break ;
		case 0xAC : CPU_RESET_BIT( m_RegisterHL.hi, 5 ) ; break ;
		case 0xAD : CPU_RESET_BIT( m_RegisterHL.lo, 5 ) ; break ;
		case 0xAE : CPU_RESET_BIT_MEMORY( m_RegisterHL.reg, 5 ) ; break ;
		case 0xAF : CPU_RESET_BIT( m_RegisterAF.hi, 5  ) ; break ;
		case 0xB0 : CPU_RESET_BIT( m_RegisterBC.hi, 6  ) ; break ;
		case 0xB1 : CPU_RESET_BIT( m_RegisterBC.lo, 6  ) ; break ;
		case 0xB2 : CPU_RESET_BIT( m_RegisterDE.hi, 6  ) ; break ;
		case 0xB3 : CPU_RESET_BIT( m_RegisterDE.lo, 6  ) ; break ;
		case 0xB4 : CPU_RESET_BIT( m_RegisterHL.hi, 6  ) ; break ;
		case 0xB5 : CPU_RESET_BIT( m_RegisterHL.lo, 6  ) ; break ;
		case 0xB6 : CPU_RESET_BIT_MEMORY( m_RegisterHL.reg, 6 ) ; break ;
		case 0xB7 : CPU_RESET_BIT( m_RegisterAF.hi, 6  ) ; break ;
		case 0xB8 : CPU_RESET_BIT( m_RegisterBC.hi, 7  ) ; break ;
		case 0xB9 : CPU_RESET_BIT( m_RegisterBC.lo, 7  ) ; break ;
		case 0xBA : CPU_RESET_BIT( m_RegisterDE.hi, 7  ) ; break ;
		case 0xBB : CPU_RESET_BIT( m_RegisterDE.lo, 7  ) ; break ;
		case 0xBC : CPU_RESET_BIT( m_RegisterHL.hi, 7  ) ; break ;
		case 0xBD : CPU_RESET_BIT( m_RegisterHL.lo, 7  ) ; break ;
		case 0xBE : CPU_RESET_BIT_MEMORY( m_RegisterHL.reg, 7 ) ; break ;
		case 0xBF : CPU_RESET_BIT( m_RegisterAF.hi, 7 ) ; break ;


		// set bit
		case 0xC0 : CPU_SET_BIT( m_RegisterBC.hi, 0 ) ; break ;
		case 0xC1 : CPU_SET_BIT( m_RegisterBC.lo, 0 ) ; break ;
		case 0xC2 : CPU_SET_BIT( m_RegisterDE.hi, 0 ) ; break ;
		case 0xC3 : CPU_SET_BIT( m_RegisterDE.lo, 0 ) ; break ;
		case 0xC4 : CPU_SET_BIT( m_RegisterHL.hi, 0 ) ; break ;
		case 0xC5 : CPU_SET_BIT( m_RegisterHL.lo, 0 ) ; break ;
		case 0xC6 : CPU_SET_BIT_MEMORY( m_RegisterHL.reg, 0 ) ; break ;
		case 0xC7 : CPU_SET_BIT( m_RegisterAF.hi, 0 ) ; break ;
		case 0xC8 : CPU_SET_BIT( m_RegisterBC.hi, 1  ) ; break ;
		case 0xC9 : CPU_SET_BIT( m_RegisterBC.lo, 1 ) ; break ;
		case 0xCA : CPU_SET_BIT( m_RegisterDE.hi, 1 ) ; break ;
		case 0xCB : CPU_SET_BIT( m_RegisterDE.lo, 1 ) ; break ;
		case 0xCC : CPU_SET_BIT( m_RegisterHL.hi, 1 ) ; break ;
		case 0xCD : CPU_SET_BIT( m_RegisterHL.lo, 1 ) ; break ;
		case 0xCE : CPU_SET_BIT_MEMORY( m_RegisterHL.reg, 1 ) ; break ;
		case 0xCF : CPU_SET_BIT( m_RegisterAF.hi, 1  ) ; break ;
		case 0xD0 : CPU_SET_BIT( m_RegisterBC.hi, 2  ) ; break ;
		case 0xD1 : CPU_SET_BIT( m_RegisterBC.lo, 2  ) ; break ;
		case 0xD2 : CPU_SET_BIT( m_RegisterDE.hi, 2  ) ; break ;
		case 0xD3 : CPU_SET_BIT( m_RegisterDE.lo, 2  ) ; break ;
		case 0xD4 : CPU_SET_BIT( m_RegisterHL.hi, 2  ) ; break ;
		case 0xD5 : CPU_SET_BIT( m_RegisterHL.lo, 2  ) ; break ;
		case 0xD6 : CPU_SET_BIT_MEMORY( m_RegisterHL.reg, 2 ) ; break ;
		case 0xD7 : CPU_SET_BIT( m_RegisterAF.hi, 2  ) ; break ;
		case 0xD8 : CPU_SET_BIT( m_RegisterBC.hi, 3  ) ; break ;
		case 0xD9 : CPU_SET_BIT( m_RegisterBC.lo, 3  ) ; break ;
		case 0xDA : CPU_SET_BIT( m_RegisterDE.hi, 3  ) ; break ;
		case 0xDB : CPU_SET_BIT( m_RegisterDE.lo, 3  ) ; break ;
		case 0xDC : CPU_SET_BIT( m_RegisterHL.hi, 3  ) ; break ;
		case 0xDD : CPU_SET_BIT( m_RegisterHL.lo, 3  ) ; break ;
		case 0xDE : CPU_SET_BIT_MEMORY( m_RegisterHL.reg, 3  ) ; break ;
		case 0xDF : CPU_SET_BIT( m_RegisterAF.hi, 3  ) ; break ;
		case 0xE0 : CPU_SET_BIT( m_RegisterBC.hi, 4  ) ; break ;
		case 0xE1 : CPU_SET_BIT( m_RegisterBC.lo, 4  ) ; break ;
		case 0xE2 : CPU_SET_BIT( m_RegisterDE.hi, 4  ) ; break ;
		case 0xE3 : CPU_SET_BIT( m_RegisterDE.lo, 4  ) ; break ;
		case 0xE4 : CPU_SET_BIT( m_RegisterHL.hi, 4  ) ; break ;
		case 0xE5 : CPU_SET_BIT( m_RegisterHL.lo, 4  ) ; break ;
		case 0xE6 : CPU_SET_BIT_MEMORY( m_RegisterHL.reg, 4) ; break ;
		case 0xE7 : CPU_SET_BIT( m_RegisterAF.hi, 4 ) ; break ;
		case 0xE8 : CPU_SET_BIT( m_RegisterBC.hi, 5 ) ; break ;
		case 0xE9 : CPU_SET_BIT( m_RegisterBC.lo, 5 ) ; break ;
		case 0xEA : CPU_SET_BIT( m_RegisterDE.hi, 5 ) ; break ;
		case 0xEB : CPU_SET_BIT( m_RegisterDE.lo, 5 ) ; break ;
		case 0xEC : CPU_SET_BIT( m_RegisterHL.hi, 5 ) ; break ;
		case 0xED : CPU_SET_BIT( m_RegisterHL.lo, 5 ) ; break ;
		case 0xEE : CPU_SET_BIT_MEMORY( m_RegisterHL.reg, 5 ) ; break ;
		case 0xEF : CPU_SET_BIT( m_RegisterAF.hi, 5  ) ; break ;
		case 0xF0 : CPU_SET_BIT( m_RegisterBC.hi, 6  ) ; break ;
		case 0xF1 : CPU_SET_BIT( m_RegisterBC.lo, 6  ) ; break ;
		case 0xF2 : CPU_SET_BIT( m_RegisterDE.hi, 6  ) ; break ;
		case 0xF3 : CPU_SET_BIT( m_RegisterDE.lo, 6  ) ; break ;
		case 0xF4 : CPU_SET_BIT( m_RegisterHL.hi, 6  ) ; break ;
		case 0xF5 : CPU_SET_BIT( m_RegisterHL.lo, 6  ) ; break ;
		case 0xF6 : CPU_SET_BIT_MEMORY( m_RegisterHL.reg, 6 ) ; break ;
		case 0xF7 : CPU_SET_BIT( m_RegisterAF.hi, 6 ) ; break ;
		case 0xF8 : CPU_SET_BIT( m_RegisterBC.hi, 7  ) ; break ;
		case 0xF9 : CPU_SET_BIT( m_RegisterBC.lo, 7  ) ; break ;
		case 0xFA : CPU_SET_BIT( m_RegisterDE.hi, 7  ) ; break ;
		case 0xFB : CPU_SET_BIT( m_RegisterDE.lo, 7  ) ; break ;
		case 0xFC : CPU_SET_BIT( m_RegisterHL.hi, 7  ) ; break ;
		case 0xFD : CPU_SET_BIT( m_RegisterHL.lo, 7  ) ; break ;
		case 0xFE : CPU_SET_BIT_MEMORY( m_RegisterHL.reg, 7 ) ; break ;
		case 0xFF : CPU_SET_BIT( m_RegisterAF.hi, 7 ) ; break ;


		default:
		{
		    char buffer[256];
		    sprintf(buffer, "Unhandled Extended Opcode %x", opcode) ;
		    LogMessage::GetSingleton()->DoLogMessage(buffer,true) ;
			assert(false) ;
		} break;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////
