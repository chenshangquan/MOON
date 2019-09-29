// confCnsLstLogic.cpp: implementation of the CConfCnsLstLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "confCnsLstLogic.h" 
#include "confCtrlLogic.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

bool CConfCnsLstLogic::OnShowAllConfCnsClick( const IArgs & arg )
{   
    if ( m_emCnsShowState == emShowAll )
    {
        return true ;
    }

    m_emCnsShowState = emShowAll;
    UpdateCnsLst( TRUE );
    UpdateShowOption();
    return true;
}

bool CConfCnsLstLogic::OnShowOfflineCnsClick( const IArgs & arg )
{ 
    if ( m_emCnsShowState == emShowOffLine )
    {
        return true ;
    }
    

    m_emCnsShowState = emShowOffLine;
    UpdateCnsLst( TRUE );
    UpdateShowOption();
    return true;
}



bool CConfCnsLstLogic::OnShowSpokesCnsClick( const IArgs & arg )
{ 
    if ( m_emCnsShowState == emShowSpeaker )
    {
        return true ;
    }
    m_emCnsShowState = emShowSpeaker;
    UpdateCnsLst( TRUE );
    UpdateShowOption();
    return true;
}


bool  CConfCnsLstLogic::OnShowMuteCnsClick( const IArgs & arg )
{ 
    if ( m_emCnsShowState == emShowMute )
    {
        return true ;
    }
    m_emCnsShowState = emShowMute;
    UpdateCnsLst( TRUE );
    UpdateShowOption();
    return true;
}

bool CConfCnsLstLogic::OnShowSlienceCnsClick( const IArgs & arg )
{ 
    if ( m_emCnsShowState == emShowQuiet )
    {
        return true ;
    }
    m_emCnsShowState = emShowQuiet;
    UpdateCnsLst( TRUE );
    UpdateShowOption();
    return true;
}

bool CConfCnsLstLogic::OnShowDbflowCnsClick( const IArgs & arg )
{ 
    if ( m_emCnsShowState == emShowDual )
    {
        return true ;
    }
    m_emCnsShowState = emShowDual;
    UpdateCnsLst( TRUE );
    UpdateShowOption();
    return true;
}
