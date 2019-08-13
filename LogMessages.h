#pragma once
#ifndef _LOGMESSAGE_H
#define _LOGMESSAGE_H

struct _iobuf ;

class LogMessage
{
public:
	static	LogMessage*				CreateInstance						( ) ;
	static	LogMessage*				GetSingleton						( ) ;

			void					DoLogMessage						( const char* message, bool logToConsole ) ;

									~LogMessage							(void);
private:
									LogMessage							(void);

	static	LogMessage*				m_Instance	;
			_iobuf*					m_LogFile ;
};

#endif //