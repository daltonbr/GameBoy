#include "LogMessages.h"
#include <cassert>
#include <cstdio>
#include <ctime>

#ifdef WIN32
#include <windows.h>
#endif

LogMessage* LogMessage::m_Instance = nullptr;

LogMessage* LogMessage::CreateInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new LogMessage();
	}
	return m_Instance;
}

LogMessage* LogMessage::GetSingleton()
{
	assert(m_Instance != nullptr);
	return m_Instance;
}

LogMessage::LogMessage(void) :
	m_LogFile(nullptr)
{
	m_LogFile = static_cast<_iobuf*>(fopen("emulator.log", "w"));
}

LogMessage::~LogMessage(void)
{
	if (m_LogFile != nullptr)
		fclose(static_cast<FILE*>(m_LogFile));
}

void LogMessage::DoLogMessage(const char* message, bool logToConsole) const
{
	if (m_LogFile != nullptr)
	{
		fputs(message, static_cast<FILE*>(m_LogFile));
		fputs("\r\n", static_cast<FILE*>(m_LogFile));
	}

	if (false == logToConsole)
		return;

#ifdef WIN32
	OutputDebugString(message);
	OutputDebugString("\n");
#else
	printf(message);
	printf("\n");
#endif

}
