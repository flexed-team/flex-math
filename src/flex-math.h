#pragma once

#include <cmath>
#include <iostream>
#include <vector>
#include <cassert>
#include <iterator>
#include <iomanip>      // std::setw
#include <xmmintrin.h>
#include <functional>

#ifdef FE_PLATFORM_WINDOWS
#	ifdef FE_BUILD_DLL
#		define FE_API _declspec(dllexport)
#	else 
#		define FE_API _declspec(dllimport)
#	endif
#else 
#	error Flex engine supports only Widnows
#endif



#include "decl.h"
#include "utils.h"
#include "matrix.h"
#include "vector.h"
