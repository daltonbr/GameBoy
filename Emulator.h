#pragma once
#ifndef _EMULATOR_H
#define _EMULATOR_H

typedef unsigned char BYTE ;
typedef char SIGNED_BYTE ;
typedef unsigned short WORD ;
typedef signed short SIGNED_WORD ;

#define FLAG_MASK_Z 128
#define FLAG_MASK_N 64
#define FLAG_MASK_H 32
#define FLAG_MASK_C 16
#define FLAG_Z 7
#define FLAG_N 6
#define FLAG_H 5
#define FLAG_C 4

typedef bool (*PauseFunc)() ;
typedef void (*RenderFunc)() ;

class Emulator
{
public:
							Emulator			(void);
							~Emulator			(void);

		bool				LoadRom				(const std::string& romName) ;
		bool				InitGame			( RenderFunc func ) ;
		void				Update				( ) ;
		void				StopGame			( ) ;
		std::string			GetCurrentOpcode	( ) const ;
		std::string			GetImmediateData1	( ) const ;
		std::string			GetImmediateData2	( ) const ;
		WORD				GetRegisterAF		( ) const { return m_RegisterAF.reg; }
		WORD				GetRegisterBC		( ) const { return m_RegisterBC.reg; }
		WORD				GetRegisterDE		( ) const { return m_RegisterDE.reg; }
		WORD				GetRegisterHL		( ) const { return m_RegisterHL.reg; }
		int					GetProgramCounter	( ) const { return m_ProgramCounter; }
		bool				IsGameLoaded		( ) const { return m_GameLoaded ; }
		BYTE				ExecuteNextOpcode	( ) ;
		int					GetZeroFlag			( )  const;
		int					GetSubtractFlag		( )  const ;
		int					GetCarryFlag		( )  const ;
		int					GetHalfCarryFlag	( )  const ;
		WORD				GetStackPointer		( ) const { return m_StackPointer.reg; }
		void				KeyPressed			( int key ) ;
		void				KeyReleased			( int key ) ;
		void				SetPauseFunction	( PauseFunc func ) { m_TimeToPause = func ; }
		unsigned long long	GetTotalOpcodes		( ) const { return m_TotalOpcodes; }
		void				SetPausePending		( bool pending ) { m_DebugPause = false ;m_DebugPausePending = pending ; }
		void				SetPause			( bool pause ) { m_DebugPause = pause; }


		BYTE				m_ScreenData[144][160][3] ;

private:
		enum COLOUR
		{
			WHITE,
			LIGHT_GRAY,
			DARK_GRAY,
			BLACK
		};

		BYTE				GetLCDMode			( ) const ;
		void				SetLCDStatus		( ) ;
		BYTE				GetJoypadState		( ) const ;
		void				CreateRamBanks		( int numBanks ) ;

		BYTE				ReadMemory			( WORD memory ) const;
		bool				ResetCPU			( ) ;
		void				ResetScreen			( ) ;
		void				DoInterupts			( ) ;
		void				DoGraphics			( int cycles ) ;
		void				ServiceInterrupt	( int num) ;
		void				DrawScanLine		( ) ;
		COLOUR				GetColour			( BYTE colourNumber, WORD address ) const ;
		void				DoTimers			( int cycles ) ;
		void				DoInput				( ) ;

		void				RenderBackground	( BYTE lcdControl ) ;
		void				RenderSprites		( BYTE lcdControl ) ;

		void				ExecuteOpcode		( BYTE opcode ) ;
		void				ExecuteExtendedOpcode( ) ;

		void				CPU_8BIT_LOAD		( BYTE& reg ) ;
		void				CPU_16BIT_LOAD		( WORD& reg ) ;
		void				CPU_REG_LOAD		( BYTE& reg, BYTE load, int cycles) ;
		void				CPU_REG_LOAD_ROM	( BYTE& reg, WORD address ) ;
		void				CPU_8BIT_ADD		( BYTE& reg, BYTE toAdd, int cycles, bool useImmediate, bool addCarry ) ;
		void				CPU_8BIT_SUB		( BYTE& reg, BYTE toSubtract, int cycles, bool useImmediate, bool subCarry ) ;
		void				CPU_8BIT_AND		( BYTE& reg, BYTE toAnd, int cycles, bool useImmediate ) ;
		void				CPU_8BIT_OR			( BYTE& reg, BYTE toOr, int cycles, bool useImmediate ) ;
		void				CPU_8BIT_XOR		( BYTE& reg, BYTE toXOr, int cycles, bool useImmediate ) ;
		void				CPU_8BIT_COMPARE	( BYTE reg, BYTE toSubtract, int cycles, bool useImmediate) ; //dont pass a reference
		void				CPU_8BIT_INC		( BYTE& reg, int cycles ) ;
		void				CPU_8BIT_DEC		( BYTE& reg, int cycles ) ;
		void				CPU_8BIT_MEMORY_INC	( WORD address, int cycles ) ;
		void				CPU_8BIT_MEMORY_DEC	( WORD address, int cycles ) ;
		void				CPU_RESTARTS		( BYTE n ) ;

		void				CPU_16BIT_DEC		( WORD& word, int cycles ) ;
		void				CPU_16BIT_INC		( WORD& word, int cycles ) ;
		void				CPU_16BIT_ADD		( WORD& reg, WORD toAdd, int cycles ) ;

		void				CPU_JUMP			( bool useCondition, int flag, bool condition ) ;
		void				CPU_JUMP_IMMEDIATE	( bool useCondition, int flag, bool condition ) ;
		void				CPU_CALL			( bool useCondition, int flag, bool condition ) ;
		void				CPU_RETURN			( bool useCondition, int flag, bool condition ) ;

		void				CPU_SWAP_NIBBLES	( BYTE& reg ) ;
		void				CPU_SWAP_NIB_MEM	( WORD address ) ;
		void				CPU_SHIFT_LEFT_CARRY( BYTE& reg ) ;
		void				CPU_SHIFT_LEFT_CARRY_MEMORY( WORD address ) ;
		void				CPU_SHIFT_RIGHT_CARRY( BYTE& reg, bool resetMSB ) ;
		void				CPU_SHIFT_RIGHT_CARRY_MEMORY( WORD address, bool resetMSB  ) ;

		void				CPU_RESET_BIT		( BYTE& reg, int bit ) ;
		void				CPU_RESET_BIT_MEMORY( WORD address, int bit ) ;
		void				CPU_TEST_BIT		( BYTE reg, int bit, int cycles ) ;
		void				CPU_SET_BIT			( BYTE& reg, int bit ) ;
		void				CPU_SET_BIT_MEMORY	( WORD address, int bit ) ;

		void				CPU_DAA				( ) ;

		void				CPU_RLC				( BYTE& reg ) ;
		void				CPU_RLC_MEMORY		( WORD address ) ;
		void				CPU_RRC				( BYTE& reg ) ;
		void				CPU_RRC_MEMORY		( WORD address ) ;
		void				CPU_RL				( BYTE& reg ) ;
		void				CPU_RL_MEMORY		( WORD address ) ;
		void				CPU_RR				( BYTE& reg ) ;
		void				CPU_RR_MEMORY		( WORD address ) ;

		void				CPU_SLA				( BYTE& reg );
		void				CPU_SLA_MEMORY		( WORD address ) ;
		void				CPU_SRA				( BYTE& reg );
		void				CPU_SRA_MEMORY		( WORD address ) ;
		void				CPU_SRL				( BYTE& reg );
		void				CPU_SRL_MEMORY		( WORD address ) ;

		PauseFunc			m_TimeToPause ;
		unsigned long long	m_TotalOpcodes ;

		bool				m_DoLogging ;

		RenderFunc			m_RenderFunc ;


	union Register
	{
		WORD reg ;
		struct
		{
			BYTE lo ;
			BYTE hi ;
		};
	};

		BYTE				m_JoypadState ;

		bool				m_GameLoaded ;
		BYTE				m_Rom[0x10000] ;
		BYTE				m_GameBank[0x200000] ;
		std::vector<BYTE*>	m_RamBank ;
		WORD				m_ProgramCounter ;
		bool				m_EnableRamBank ;

		Register			m_RegisterAF ;
		Register			m_RegisterBC ;
		Register			m_RegisterDE ;
		Register			m_RegisterHL ;
		int					m_CyclesThisUpdate ;

		Register			m_StackPointer ;
		int					m_CurrentRomBank ;
		bool				m_UsingMemoryModel16_8 ;
		bool				m_EnableInterupts ;
		bool				m_PendingInteruptDisabled ;
		bool				m_PendingInteruptEnabled ;
		int					m_CurrentRamBank ;
		int					m_RetraceLY ;
		bool				m_DebugPause ;
		bool				m_DebugPausePending ;

		void				RequestInterupt( int bit ) ;

		WORD				ReadWord			( ) const ;
		WORD				ReadLSWord			( ) const ;
		void				WriteByte			(WORD address, BYTE data) ;
		void				IssueVerticalBlank	( ) ;
		void				DrawCurrentLine		( ) ;
		void				PushWordOntoStack	( WORD word ) ;
		WORD				PopWordOffStack		( ) ;

		BYTE				m_DebugValue ;




		bool				m_UsingMBC1	 ;
		bool                m_UsingMBC2 ;
		bool				m_Halted ;
		int					m_TimerVariable ;
		int					m_DividerVariable ;
		int					m_CurrentClockSpeed ;


};

#endif
