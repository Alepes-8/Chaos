#pragma once

#ifdef HZ_PLATFORM_WINDOWS
	#ifdef GE_BUILD_DLL
		#define GE_API _declspec(dllexport)
	#else
		#define GE_API _declspec(dllimport)
	#endif // DEBUG
#else
	#error We only suport Windows
#endif // HZ_PLATFORM_WINDOWS

#define BIT(x) (1<<x)