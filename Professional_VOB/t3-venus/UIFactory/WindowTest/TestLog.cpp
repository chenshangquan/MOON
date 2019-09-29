// TestLog.cpp: implementation of the CTestLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WindowTest.h"
#include "TestLog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTestLog::CTestLog()
{

}

CTestLog::~CTestLog()
{

}

bool CTestLog::LogEvent( String strEvent, LogLevel emLoglv /* = Standard */ )
{
	TRACE( strEvent.c_str() );
	return true;
}