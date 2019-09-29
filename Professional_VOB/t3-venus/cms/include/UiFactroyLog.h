// UiFactroyLog.h: interface for the UiFactroyLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UIFACTROYLOG_H__3C2EA599_8D97_4FD2_83D8_8B4B832C5853__INCLUDED_)
#define AFX_UIFACTROYLOG_H__3C2EA599_8D97_4FD2_83D8_8B4B832C5853__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Logger.h"
using namespace AutoUIFactory;
class CUiFactroyLog : public ILogger 
{
public:
	CUiFactroyLog();
	virtual ~CUiFactroyLog();
	
    String GetLogFile();

    void  WriteWrongInfo( String str ); 

	virtual bool LogEvent( String strEvent, LogLevel emLoglv = Standard );
};

#endif // !defined(AFX_UIFACTROYLOG_H__3C2EA599_8D97_4FD2_83D8_8B4B832C5853__INCLUDED_)
