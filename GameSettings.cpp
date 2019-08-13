#include "GameSettings.h"
#include "LogMessages.h"
#include "useful_utils.h"
#include <assert.h>
#include <fstream>

///////////////////////////////////////////////////////////////////////////////////////////

GameSettings* GameSettings::m_Instance = 0 ;

GameSettings* GameSettings::CreateInstance( )
{
	if (0 == m_Instance)
		m_Instance = new GameSettings( ) ;
	return m_Instance ;
}

///////////////////////////////////////////////////////////////////////////////////////////

GameSettings* GameSettings::GetSingleton( )
{
	if (0 == m_Instance)
	{
		LogMessage::GetSingleton()->DoLogMessage("Attempting to get the singleton of GameSettings when m_Instance is 0", true) ;
		assert(false) ;
	}
	return m_Instance ;
}

///////////////////////////////////////////////////////////////////////////////////////////

GameSettings::GameSettings(void)
{
	m_Settings.clear( ) ;
}

///////////////////////////////////////////////////////////////////////////////////////////

GameSettings::~GameSettings(void)
{
}

///////////////////////////////////////////////////////////////////////////////////////////

bool GameSettings::LoadSettings( )
{
	m_Settings.clear( ) ;

	std::fstream file ;
	file.open("settings.ini", std::ios::in) ;

	// test if the file exists
	if (false == file.is_open())
	{
		// if in visual studio then it will be in the parent directory
		file.open("../settings.ini", std::ios::in) ;
		if (false == file.is_open())
		{
			LogMessage::GetSingleton()->DoLogMessage("Cannot find file settings.ini",true) ;
			return false ;
		}
	}

	char buffer[256] ;
	std::string settingname ;
	std::string settingvalue ;

	// load in all the settings a line at a time
	while (false == file.eof())
	{
		memset(buffer, 0, sizeof(buffer)) ;
		file.getline(buffer,256) ;
		
		char ch = buffer[0] ;

		// ignore blank lines, comments etc
		if ('\0' == ch || '*' == ch || '\r' == ch || '\n' == ch)
			continue ;

		char* tokens = NULL;
		tokens = strtok(buffer, ":") ;
		
		settingname = tokens ;
		
		tokens = strtok(NULL, "*") ;
		settingvalue = tokens ;

		if (settingname.empty() || settingvalue.empty())
		{
			LogMessage::GetSingleton()->DoLogMessage("Settings.ini appears to be malformed",true) ;
			file.close() ;
			return false ;
		}

		m_Settings.insert(std::make_pair(settingname,settingvalue));
	}


	file.close() ;

	return true ;

}

///////////////////////////////////////////////////////////////////////////////////////////

std::string GameSettings::GetSetting(const std::string setting) const
{
	std::string res = "" ;
	GAMESETTINGS::const_iterator it = m_Settings.find(setting) ;

	if (m_Settings.end() == it)
	{
		std::string message = "Could Not Find Setting " ;
		message += setting ;
		LogMessage::GetSingleton()->DoLogMessage(message.c_str(), true) ;
		return "" ;
	}

	return (*it).second ;
}

///////////////////////////////////////////////////////////////////////////////////////////