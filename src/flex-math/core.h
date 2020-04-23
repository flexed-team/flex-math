#pragma once

#ifdef FM_PLATFORM_WINDOWS
#	ifdef FM_BUILD_DLL
#		define FM_API _declspec(dllexport)
#	else 
#		define FM_API _declspec(dllimport)
#	endif
#else 
#	error Flex engine supports only Widnows
#endif
