// listfuncmanage.cpp: implementation of the CListFuncManage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "listfuncmanage.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CListFuncManage::CListFuncManage()
{

}

CListFuncManage::~CListFuncManage()
{
    UnRegAllFunc();
}

bool CListFuncManage::UnRegFunc( String strName )
{
    FuncMap::iterator itr =	m_mapFuncs.find( strName );
    if ( itr != m_mapFuncs.end() )
    {
        delete itr->second;
        itr->second = 0;
        m_mapFuncs.erase( itr );
        //LOGEVENT( "CFuncManage::UnRegFunc �ɹ�ע�������� name = " + strName );
        return true;
    }
    //LOGEVENT( "CFuncManage::UnRegFunc δ�ҵ���Ӧ���� name = " + strName );
    return false;
}

bool CListFuncManage::RegFunc( String strName, ICallBackFuncBase* piFunc )
{
    FuncMap::iterator itr =	m_mapFuncs.find( strName );
    if ( itr != m_mapFuncs.end() )
    {
        //LOGEVENT( "CFuncManage::RegFunc �ô������Ѿ����� name = " + strName );
        return false;
    }
    m_mapFuncs.insert( FuncMap::value_type( strName, piFunc ) );
    //LOGEVENT( "CFuncManage::RegFunc �ɹ�ע�ắ�� name = " + strName );
    return true;
}

bool CListFuncManage::ExeFunc( String strName, const IArgs& args )
{
    FuncMap::iterator itr = m_mapFuncs.find( strName );
    if ( itr == m_mapFuncs.end() )
    {
        return false;
    }
    (*itr->second)( args );
    return false;
}



void CListFuncManage::UnRegAllFunc()
{
    FuncMap::iterator itr = m_mapFuncs.begin();
    while( itr != m_mapFuncs.end() )
    {
        delete itr->second;
        itr->second = 0;
        m_mapFuncs.erase( itr );
        itr = m_mapFuncs.begin();
    }
    
}