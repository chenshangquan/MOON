// TestLog.h: interface for the CTestLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTLOG_H__CBF215F8_28E2_4A92_83D5_FD4DC2E4ED38__INCLUDED_)
#define AFX_TESTLOG_H__CBF215F8_28E2_4A92_83D5_FD4DC2E4ED38__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Logger.h"
class CTestLog : public ILogger
{
public:
	CTestLog();
	virtual ~CTestLog();
	virtual bool LogEvent( String strEvent, LogLevel emLoglv = Standard );
};

#endif // !defined(AFX_TESTLOG_H__CBF215F8_28E2_4A92_83D5_FD4DC2E4ED38__INCLUDED_)
