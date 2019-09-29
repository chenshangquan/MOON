// LogicTest.h: interface for the LogicTest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGICTEST_H__8514A3DB_4E04_4726_91C5_03AC721116FD__INCLUDED_)
#define AFX_LOGICTEST_H__8514A3DB_4E04_4726_91C5_03AC721116FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class LogicTest  
{
public:
	LogicTest();
	virtual ~LogicTest();
	bool Test( const IArgs& args );

};

#endif // !defined(AFX_LOGICTEST_H__8514A3DB_4E04_4726_91C5_03AC721116FD__INCLUDED_)
