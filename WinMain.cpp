#include "Config.h"
#include "GameBoy.h"
#include "GameSettings.h"

int main(int argc, char* argv[])
{
	LogMessage* log = LogMessage::CreateInstance();
	GameSettings* settings = GameSettings::CreateInstance();

	GameBoy* gameboy = GameBoy::CreateInstance();

	gameboy->StartEmulation();

	delete gameboy;
	delete settings;
	delete log;

	return 0;
}
