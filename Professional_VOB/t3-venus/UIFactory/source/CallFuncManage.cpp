// CallFuncManage.cpp: implementation of the CCallFuncManage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "CallFuncManage.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace AutoUIFactory
{

template<> CFuncManage* Singleton<CFuncManage>::ms_pSingleton = 0;
CFuncManage::CFuncManage()
{

}

CFuncManage::~CFuncManage()
{
	UnRegAllFunc();
}

bool CFuncManage::UnRegFunc( String strName )
{
	FuncMap::iterator itr =	m_mapFuncs.find( strName );
	if ( itr != m_mapFuncs.end() )
	{
		delete itr->second;
		itr->second = 0;
		m_mapFuncs.erase( itr );
		LOGEVENT( "CFuncManage::UnRegFunc �ɹ�ע�������� name = " + strName );
		return true;
	}
	LOGEVENT( "CFuncManage::UnRegFunc δ�ҵ���Ӧ���� name = " + strName );
	return false;
}

bool CFuncManage::RegFunc( String strName, ICallBackFuncBase* piFunc )
{
	FuncMap::iterator itr =	m_mapFuncs.find( strName );
	if ( itr != m_mapFuncs.end() )
	{
		LOGEVENT( "CFuncManage::RegFunc �ô������Ѿ����� name = " + strName );
		return false;
	}
	m_mapFuncs.insert( FuncMap::value_type( strName, piFunc ) );
	LOGEVENT( "CFuncManage::RegFunc �ɹ�ע�ắ�� name = " + strName );
	return true;
}

bool CFuncManage::ExeFunc( String strName, const IArgs& args )
{
	FuncMap::iterator itr = m_mapFuncs.find( strName );
	if ( itr == m_mapFuncs.end() )
	{
		return false;
	}
	(*itr->second)( args );
	return false;
}



void CFuncManage::UnRegAllFunc()
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
} // namespace AutoUIFactory end
