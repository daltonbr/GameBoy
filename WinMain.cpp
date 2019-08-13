#include "Config.h"
#include "GameBoy.h"
#include "GameSettings.h"


int main(int argc, char *argv[])
{
	LogMessage* log = LogMessage::CreateInstance() ;
	GameSettings* settings = GameSettings::CreateInstance();

	GameBoy* gb = GameBoy::CreateInstance( ) ;

	gb->StartEmulation( ) ;

	delete gb ;
	delete settings ;
	delete log ;

	return 0;
}
