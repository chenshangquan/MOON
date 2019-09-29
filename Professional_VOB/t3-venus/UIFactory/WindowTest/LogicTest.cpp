// LogicTest.cpp: implementation of the LogicTest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WindowTest.h"
#include "LogicTest.h"
#include "SaveXmlHelp.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

LogicTest::LogicTest()
{

}

LogicTest::~LogicTest()
{

}

bool LogicTest::Test( const IArgs& args )
{
	CWndTreeHelp::GetWindow( "mainmenu", CWindowManage::GetSingletonPtr()->GetRoot() );
	CUILayoutHelp::LayoutUI( "TPDlg" );
//	bool result = CSaveXmlHelp::SaveXml( "mainmenu" );
	return true;
}