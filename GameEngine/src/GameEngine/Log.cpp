#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace GameEngine {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;


	void Log::Init()
	{
		//Costumize the logging
		spdlog::set_pattern("%^[%T] %n: %v%$");  // %T = is the Time stamp: %n = the name of the logger: %v%$ = the message: %^ and %$ = color the log


		// create color multi threaded logger
		s_CoreLogger = spdlog::stdout_color_mt("GameEngine");	
		s_CoreLogger->set_level(spdlog::level::trace);		
		s_ClientLogger = spdlog::stdout_color_mt("Game");
		s_ClientLogger->set_level(spdlog::level::trace);
	}		

}
