// tpadlib.cpp: implementation of the CTpadLib class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "tpadlib.h"
#include "tpadsession.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTPadLib::CTPadLib()
{

}

CTPadLib::~CTPadLib()
{

}


u16 CTPadLib::CreateSession(CTPadSessionIF **ppIf)
{
	CTPadSession *pSession = new CTPadSession();
	if(pSession == NULL)
	{
		*ppIf = NULL;
		return ERR_TPAD_INTERFACE;
	}
	else
	{
		*ppIf = pSession;
		return NO_ERROR;
	}
}

u16 CTPadLib::DestroySession(CTPadSessionIF **ppIf)
{
	CTPadSession *pSession = dynamic_cast<CTPadSession*>(*ppIf);
	if(pSession == NULL)
    {
        return ERR_TPAD_INTERFACE;
    }
	delete pSession;
	*ppIf = NULL;
	return NO_ERROR;
}
