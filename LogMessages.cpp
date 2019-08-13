#include "LogMessages.h"
#include <assert.h>
#include <stdio.h>
#include <time.h>

#ifdef WIN32
#include <windows.h>
#endif

////////////////////////////////////////////////////////////////////////////////////////

LogMessage* LogMessage::m_Instance = 0 ;

LogMessage* LogMessage::CreateInstance( )
{
	if (0 == m_Instance)
		m_Instance = new LogMessage( ) ;
	return m_Instance ;
}

////////////////////////////////////////////////////////////////////////////////////////

LogMessage* LogMessage::GetSingleton( )
{
	assert(m_Instance != 0) ;
	return m_Instance ;
}

////////////////////////////////////////////////////////////////////////////////////////

LogMessage::LogMessage(void) :
	m_LogFile(NULL)
{
	m_LogFile = (_iobuf*)fopen("emulator.log", "w") ;
}

////////////////////////////////////////////////////////////////////////////////////////

LogMessage::~LogMessage(void)
{
	if (NULL != m_LogFile)
		fclose((FILE*)m_LogFile) ;
}

////////////////////////////////////////////////////////////////////////////////////////

void LogMessage::DoLogMessage(const char* message, bool logToConsole)
{
	if (NULL != m_LogFile)
	{
		fputs(message, (FILE*)m_LogFile) ;
		fputs("\r\n", (FILE*)m_LogFile) ;
	}

	if (false == logToConsole)
		return ;

#ifdef WIN32
	OutputDebugStr(message) ;
	OutputDebugStr("\n") ;
#else
	printf(message) ;
	printf("\n") ;
#endif


}

////////////////////////////////////////////////////////////////////////////////////////
