// diagTestFrameLogic.cpp: implementation of the DiagTestFrameLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "diagTestFrameLogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDiagTestFrameLogic::CDiagTestFrameLogic()		
{

}

CDiagTestFrameLogic::~CDiagTestFrameLogic()
{

}

bool CDiagTestFrameLogic::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );
	UIFACTORYMGR_PTR->ShowWindow( g_strDiagInTestInfo);
    UIFACTORYMGR_PTR->ShowWindow( g_strDiagOutTestInfo, false );
	return true;
}

void CDiagTestFrameLogic::RegMsg()
{
	CDiagTestFrameLogic *pThis =  GetSingletonPtr(); 		
}

void CDiagTestFrameLogic::UnRegMsg()
{
	
}

void CDiagTestFrameLogic::RegCBFun()
{
	CDiagTestFrameLogic *pThis =  GetSingletonPtr();	
    REG_GOBAL_MEMBER_FUNC( "CDiagTestFrameLogic::InitWnd", CDiagTestFrameLogic::InitWnd, pThis, CDiagTestFrameLogic );

}

void CDiagTestFrameLogic::UnRegFunc()
{
	UN_REG_GOBAL_FUNC( "CDiagTestInfoLogic::InitWnd" );	
}

void CDiagTestFrameLogic::Clear()
{
	s32 nResult = 0;
	UIFACTORYMGR_PTR->Endmodal(nResult, g_strDiagTestFrame );
}
