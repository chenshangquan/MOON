// Logger.cpp: implementation of the CLogger class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "System.h"
#include "Logger.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace AutoUIFactory
{
template<> ILogger* Singleton<ILogger>::ms_pSingleton  = 0;
} // namespace AutoUIFactory end
