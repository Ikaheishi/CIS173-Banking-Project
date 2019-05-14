#pragma once
#include "macros.h"

// Check for C++ support
#ifndef __cplusplus
	#error APPNAME " REQUIRES SUPPORT FOR C++11 OR LATER"
#endif

// If compiling for Windows, check if the target platform is for
// a version of Windows that has comparable enough support for
// the standardised features we use.
#ifdef _WIN32
	#if _MSC_VER < 1916
		#error APPNAME " REQUIRES WINDOWS 10 REDSTONE (1607) OR LATER"
	#endif
#endif
