
/*-----------This is set up to init the loging system for the program----------------
-
-
-
*/

#pragma once

#include <memory>

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "spdlog/sinks/stdout_color_sinks.h"




namespace GameEngine {
	class Log
	{
	public: 
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;


	};
}
// Core Log Macros
#define GE_CORE_TRACE(...) ::GameEngine::Log::GetCoreLogger()->trace(_VA_ARGS_)
#define GE_CORE_INFO(...)   = GameEngine::Log::GetCoreLogger()->info(_VA_ARGS_)
#define GE_CORE_WARN(...)  ::GameEngine::Log::GetCoreLogger()->warn(_VA_ARGS_)
#define GE_CORE_ERROR(...) ::GameEngine::Log::GetCoreLogger()->error(_VA_ARGS_)
//#define GE_CORE_FATAL(...) ::GameEngine::Log::GetCoreLogger()->fatal(_VA_ARGS_)

// Client Log Macros
#define GE_CLIENT_TRACE(...) ::GameEngine::Log::GetClientLogger()->trace(_VA_ARGS_)
#define GE_CLIENT_INFO(...)  ::GameEngine::Log::GetClientLogger()->info(_VA_ARGS_)
#define GE_CLIENT_WARN(...)  ::GameEngine::Log::GetClientLogger()->warn(_VA_ARGS_)
#define GE_CLIENT_ERROR(...) ::GameEngine::Log::GetClientLogger()->error(_VA_ARGS_)
//#define GE_CLIENT_FATAL(...) ::GameEngine::Log::GetClientLogger()->fatal(_VA_ARGS_)

