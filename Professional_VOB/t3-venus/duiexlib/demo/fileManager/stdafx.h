// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h> 
// TODO: reference additional headers your program requires here


#include <objbase.h>
#include<vector>
#include<map>
#include<string>


#include "UIlib.h" 

// namespace DuiLib { 
//   typedef std::basic_string<TCHAR> TString;
// }

#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string tstring;
#endif


#ifndef NO_USING_DUILIB_NAMESPACE
	using namespace DuiLib;
	using namespace std;
#endif


#  pragma comment(lib, "duiexlib.lib")
// #ifdef _DEBUG
// #   ifdef _UNICODE
// #       pragma comment(lib, "..\\..\\bin\\DuiLib_ud.lib")
// #   else
// #       pragma comment(lib, "..\\..\\bin\\DuiLib_d.lib")
// #   endif
// #else
// #   ifdef _UNICODE
// #       pragma comment(lib, "..\\..\\bin\\DuiLib_u.lib")
// #   else
// #       pragma comment(lib, "..\\..\\bin\\DuiLib.lib")
// #   endif
// #endif


