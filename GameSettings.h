#pragma once
#ifndef _GAME_SETTINGS_H
#define _GAME_SETTINGS_H

#include <map>
#include <string>

class GameSettings
{
public:
	static	GameSettings*	CreateInstance					( ) ;
	static	GameSettings*	GetSingleton					( ) ;

			bool			LoadSettings					( ) ;
			std::string		GetSetting						( const std::string setting) const ;

							~GameSettings					(void);
private:
							GameSettings					(void);

	static	GameSettings*	m_Instance ;

	typedef std::map<std::string, std::string> GAMESETTINGS ;
	GAMESETTINGS m_Settings ;

};

#endif