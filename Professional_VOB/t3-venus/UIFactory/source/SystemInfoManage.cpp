// SystemInfoManage.cpp: implementation of the CSystemInfoManage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "System.h"
#include "SystemInfoManage.h"
#include "PropertyHelp.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
namespace AutoUIFactory
{
const String CSystemInfoManage::strSystemInfo = "SystemInfo";
const String CSystemInfoManage::strVersion = "Version";
const String CSystemInfoManage::strName = "Name";
const String CSystemInfoManage::strValue = "Value";
const String CSystemInfoManage::strImagePath = "ImagePath";
const String CSystemInfoManage::strLayoutPath = "LayoutPath";
const String CSystemInfoManage::strItemInfo = "ItemInfo";
const String CSystemInfoManage::strResolution = "DefaultResolution";//Ĭ�Ϸֱ���
const String CSystemInfoManage::strBeSelAdpResolution = "IsSelAdpResolution"; //�Ƿ�����Ӧ�ֱ���
const String CSystemInfoManage::strEditInfo = "EditInfo";
const String CSystemInfoManage::strStaticInfo = "StaticInfo";

template<> CSystemInfoManage* Singleton<CSystemInfoManage>::ms_pSingleton  = 0;
CSystemInfoManage::CSystemInfoManage():m_strMainXml(),
                                       m_strImagePath(),
                                       m_strLayoutPath(),
                                       m_strItemInfo(),
                                       m_strResolution(),
                                       m_bBeSelAdpResolution( TRUE ),
									   m_strVersion()

{

}

CSystemInfoManage::~CSystemInfoManage()
{

}

void CSystemInfoManage::Update( IArgs* pArgs )
{
	if (  Args_SystemObserver* pObser = dynamic_cast<Args_SystemObserver*>(pArgs) )
	{
		SystemInfoMultiMap::iterator itr = pObser->m_mapSystemInfos.begin();
		while ( itr != pObser->m_mapSystemInfos.end() )
		{
			if ( itr->first == CSystemInfoManage::strSystemInfo )
			{
				UpdateSystemInfo( itr->second );
			}
			itr++;
		}
	}
}

void CSystemInfoManage::UpdateSystemInfo( XMLAttributes& xmlAttribs )
{   
	if ( !xmlAttribs.exists( CSystemInfoManage::strName ) || !xmlAttribs.exists( CSystemInfoManage::strValue ) )
    {   
        LOGEVENT("[CSystemInfoManage::UpdateSystemInfo] return �������� " + CSystemInfoManage::strName + "���߲�����"+CSystemInfoManage::strValue );
		return;
	}
	String strName = xmlAttribs.getValue( CSystemInfoManage::strName );
	String strValue = xmlAttribs.getValue( CSystemInfoManage::strValue );
	
	if ( strName == CSystemInfoManage::strImagePath)
	{		
		SetImagePath( strValue );
	}	
	else if ( strName == CSystemInfoManage::strLayoutPath )
	{
		SetLayoutPath( strValue );
	}
	else if ( strName == CSystemInfoManage::strItemInfo )
	{
		SetItemInfoPath( strValue );
 	}
    else if ( strName == CSystemInfoManage::strResolution)
    {
        SetResolution( strValue );
    }
    else if ( strName == CSystemInfoManage::strBeSelAdpResolution )
    {
        SetBeSelAdpResolution(strValue);
    }
    else if ( strName == CSystemInfoManage::strEditInfo )
    {
        SetFontInfo( m_tEditFontInfo, xmlAttribs );
    }
    else if ( strName == CSystemInfoManage::strStaticInfo )
    {
        SetFontInfo( m_tStaticFontInfo, xmlAttribs );
    }
	else if ( strName == CSystemInfoManage::strVersion )
    {
        SetVersion( strValue );
    }

}

/**  ����ϵͳͼƬ��Դ·��
 *  @param[in] strPath ·��
 *  @return 
 */
void CSystemInfoManage::SetImagePath( String strPath )
{ 
    m_strImagePath = strPath ;
#ifndef _DEBUG
    MakeFullPath( m_strImagePath );
#endif
    
}


/**  ����ϵͳ�����ļ�·��
*  @param[in] strPath ·��
*  @return 
*/
void CSystemInfoManage::SetLayoutPath( String strPath )
{ 
    m_strLayoutPath = strPath ; 
#ifndef _DEBUG
    MakeFullPath(m_strLayoutPath); 
#endif
    
}


/**  ����ItemInfo�ļ�·��
 *  @param[in] strPath ·��
 *  @return 
 */
void CSystemInfoManage::SetItemInfoPath( String strPath )
{  
    m_strItemInfo =  strPath ;
#ifndef _DEBUG
    MakeFullPath(m_strItemInfo );
#endif
    
    LOGEVENT("[etItemInfoPath( String strPath )]" + m_strItemInfo );
}

//��ĳ���ļ������·������Ϊ����·��
void CSystemInfoManage::MakeFullPath( String& strFileSubPath )
{
    TCHAR achDllName[MAX_PATH] = _T(""); 
    GetModuleFileName(AfxGetInstanceHandle(), achDllName, sizeof (achDllName));
    String str( achDllName ); 
    
    int pos = str.find_last_of('\\'); 
    String strSub = str.substr( 0,pos+1 );
    char strFullPath[MAX_PATH] = _T(""); 
   
    _snprintf(strFullPath , sizeof(strFullPath), "%s%s",strSub.c_str(),strFileSubPath.c_str() );
   
    strFileSubPath = strFullPath ;
  
}


void CSystemInfoManage::SetResolution( String strValue )
{  
    m_strResolution = strValue; 
}


void CSystemInfoManage::GetResolution( int &cx, int &cy )
{ 
    SIZE  sz ;
	//Ĭ�Ϸֱ���1366*768
    sz.cx = 1366;
    sz.cy = 768;
    if ( !m_strResolution.empty() )
    {
         sz = CPropertyHelp::stringToSize( m_strResolution );
    }
   
    cx = sz.cx;
    cy = sz.cy;
}


//�Ƿ�����Ӧ�ֱ���
void CSystemInfoManage::SetBeSelAdpResolution( String strValue )
{
    m_bBeSelAdpResolution = CPropertyHelp::stringToBool( strValue );
}


BOOL CSystemInfoManage::IsSelAdpResolution() 
{
    return m_bBeSelAdpResolution;
}


void CSystemInfoManage::SetFontInfo( TFontInfo &tFontInfo, XMLAttributes& xmlAttribs )
{
    if ( !xmlAttribs.exists( CSystemInfoManage::strName ) )
    {   
        LOGEVENT("[CSystemInfoManage::SetEditFontInfo] return�������� " + CSystemInfoManage::strName );
        return;
    }
    String strName = xmlAttribs.getValue( CSystemInfoManage::strName );
	String strValue = xmlAttribs.getValue( CSystemInfoManage::strValue );

    if ( xmlAttribs.exists( CItemFactory::strFontName ) )
    {
        tFontInfo.strFontName = xmlAttribs.getValue( CItemFactory::strFontName );            
	}
    if ( xmlAttribs.exists( CItemFactory::strFontSize ) )
    {
        tFontInfo.nFontSize = xmlAttribs.getValueAsInteger( CItemFactory::strFontSize );
    }
    if ( xmlAttribs.exists( CItemFactory::strFontColor ) )
    {
        tFontInfo.strNormalColor = xmlAttribs.getValue( CItemFactory::strFontColor );
    }
    if ( xmlAttribs.exists( "FocusColor" ) )
    {
        tFontInfo.strFocusColor = xmlAttribs.getValue( "FocusColor" );
    }
    if ( xmlAttribs.exists( "DisableColor" ) )
    {
        tFontInfo.strDisableColor = xmlAttribs.getValue( "DisableColor" );
    }
    if ( xmlAttribs.exists( "DisableImg" ) )
    {
        tFontInfo.strDisableImg = xmlAttribs.getValue( "DisableImg" );
    }

}
 

void  CSystemInfoManage::SetVersion( string strVer )
{
	m_strVersion =  strVer ; 
   
}


}
