// ProperyTest.h: interface for the ProperyTest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROPERYTEST_H__E299D7D1_96EB_42F7_956E_525F6083AE1D__INCLUDED_)
#define AFX_PROPERYTEST_H__E299D7D1_96EB_42F7_956E_525F6083AE1D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TestWnd.h"
class ProperyTest 
{
public:
	ProperyTest();
	virtual ~ProperyTest();
	virtual bool SetProperty( const XMLAttributes& xmlAttrib, const Window* window );
};

#endif // !defined(AFX_PROPERYTEST_H__E299D7D1_96EB_42F7_956E_525F6083AE1D__INCLUDED_)
