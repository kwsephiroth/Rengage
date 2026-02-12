#include "../inc/game_manager.h"
#include "../inc/rengage.lib/services/service_locator.h"

using namespace rengage::services;
int main()
{
	ServiceLocator::provide_service<logging::ILogger>(std::make_unique<logging::FileLogger>());
	forest_escape::GameManager gm;
	gm.start_game_loop();
	return 0;
}