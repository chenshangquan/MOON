/*****************************************************************************
ģ����      : CMS����̨
�ļ���      : cncaddrbook.cpp
����ļ�    : commoninterface.h
�ļ�ʵ�ֹ���: ��װ��umclib��cnclib�ӿڣ����ļ���Ҫ��װ��ַ����ؽӿ�
����        : Ф��Ȼ
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
  ��  ��      �汾        �޸���      �޸�����
2011/05/10    1.0         Ф��Ȼ        ����
******************************************************************************/

#include "stdafx.h"
#include "cms.h"
#include "commoninterface.h"
#include "AddrList.h"
#include <algorithm>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CAddrBook& CCommonInterface::GetAddrBook()
{
	return m_pAddrBookCtrl->GetAddrBook();
}

BOOL CCommonInterface::GetAddrLoadingState()
{
	return m_pAddrBookCtrl->GetAddrLoadingState();
}

void CCommonInterface::SetAddrLoadingState(BOOL bAddrLoading)
{
	m_pAddrBookCtrl->SetAddrLoadingState( bAddrLoading );
	return;
}

u16 CCommonInterface::AddEntry( const CAddrEntry& entry )  
{
	if ( NULL == m_pAddrBookCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = NO_ERROR;
	
	wRe = m_pAddrBookCtrl->AddEntry( entry );
	
	return wRe;	
}


u16 CCommonInterface::ModifyEntry( const CAddrEntry& entry )
{
	if ( NULL == m_pAddrBookCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pAddrBookCtrl->ModifyEntry( entry );
	
	return wRe;	
}


u16 CCommonInterface::DeleteEntry( u32 dwIndex )
{
	if ( NULL == m_pAddrBookCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pAddrBookCtrl->DeleteEntry( dwIndex );
	
	return wRe;	
}


u16 CCommonInterface::DeleteMultiEntry( vector<u32>& vctEntry )
{
	if ( NULL == m_pAddrBookCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pAddrBookCtrl->DeleteMultiEntry( vctEntry );

	return wRe;
}



u16 CCommonInterface::AddGroup( const CAddrMultiSetEntry& group )
{
	if ( NULL == m_pAddrBookCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pAddrBookCtrl->AddGroup( group );
	
	return wRe;	
}

u16 CCommonInterface::ModifyGroup( const CAddrMultiSetEntry& group )
{
	if ( NULL == m_pAddrBookCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pAddrBookCtrl->ModifyGroup( group );
	
	return wRe;	
}

u16 CCommonInterface::DeleteGroup( u32 dwIndex )
{
	if ( NULL == m_pAddrBookCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pAddrBookCtrl->DeleteGroup( dwIndex );
	
	return wRe;	
}

u16 CCommonInterface::DeleteMultiGroup( vector<u32>& vctGroup )
{
    if ( NULL == m_pAddrBookCtrl ) 
    {
        return ERR_CMS;
    }
    
    u16 wRe = m_pAddrBookCtrl->DeleteMultiGroup( vctGroup );
    
	return wRe;	
}


u16 CCommonInterface::AddEntryToGroup( const TADDRMULTISETENTRY& tGroupEntry )
{
	if ( NULL == m_pAddrBookCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pAddrBookCtrl->AddEntryToGroup( tGroupEntry );
	
	return wRe;	
}

u16 CCommonInterface::DelEntryFromGroup( const TADDRMULTISETENTRY& tGroupEntry )
{
	if ( NULL == m_pAddrBookCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pAddrBookCtrl->DelEntryFromGroup( tGroupEntry );
	
	return wRe;	
}

u16 CCommonInterface::AddGroupToGroup( u32 dwGroupIndex, u32 dwUpGroupIndex )
{
	if ( NULL == m_pAddrBookCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pAddrBookCtrl->AddGroupToGroup( dwGroupIndex, dwUpGroupIndex );
	
	return wRe;	
}

u16 CCommonInterface::DelGroupFromGroup( u32 dwGroupIndex, u32 dwUpGroupIndex )
{
	if ( NULL == m_pAddrBookCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pAddrBookCtrl->DelGroupFromGroup( dwGroupIndex, dwUpGroupIndex );
	
	return wRe;	
}

const vector<TAddrItem>* CCommonInterface::GetLocalAddrList()
{
	return &m_vctLocalAddrList;
}

const vector<TAddrItem>* CCommonInterface::GetAddrGroupList()
{
	return &m_vctGroupList;
}

const vector<TAddrItem>* CCommonInterface::GetAddrEntryList()
{
    return &m_vctEntryList;
}


LRESULT CCommonInterface::UpdateAddrBook(WPARAM wParam, LPARAM lParam)
{
	if ( NULL == m_pAddrBookCtrl ) 
	{
		return ERR_CMS;
	}

	UpdateAddrList();

	CMsgDispatch::SendMessage( UI_CNS_ADDRBOOK_CHANGED, wParam, lParam );
	return 0;
}

void CCommonInterface::UpdateAddrList()
{
	UpdateAddrEntryList();
	//UpdateAddrGroupList();
	//ֻ��ʾ��һ����ַ����
	UpdateLevelOneGroup();
}



void CCommonInterface::UpdateAddrEntryList()
{
	m_vctLocalAddrList.clear();
    m_vctEntryList.clear();
	CAddrBook cAddrBook = m_pAddrBookCtrl->GetAddrBook();
	
	CString strLetter;
	TAddrItem tAddrItem;
	tAddrItem.emItemType = emEntryItem;

    vector<TAddrInfo> vctCnsRegInfo;
	vctCnsRegInfo = m_pSipInfoCtrl->GetCnsRegInfo();

	
	//��ȡ������Ŀ����
	u32 dwUsedSize = cAddrBook.GetAddrEntryUsedSize();
	
	u32 dwIndex = 0;
	s32 nIndex = 0;
	CAddrEntry cAddrEntry;
	dwIndex = cAddrBook.GetFirstAddrEntry( &cAddrEntry );
	while ( nIndex < dwUsedSize )
	{
		if ( dwIndex != INVALID_INDEX )
		{	
			TAddrInfo tAddrInfo;
			SetAddrItemInfo( tAddrInfo, cAddrEntry );

            //TTPAlias tAlias;

			//��ȡ��Ŀ������ĸ��������ֻ�л᳡����ʱ�Ժ�����������Ϊ�ո�+�������ʽ����֤����������ǰ�� -2012.11.7 xcr
            //ֻ�к���ʱ������ʾ������Ҫ������ǰ�ӿո� -2013.7.17
            if ( strcmp( tAddrInfo.achEntryName, "" ) == 0 )
			{
                strLetter.Format( "%s", tAddrInfo.achE164 );

                //tAlias.SetAlias( tp_Alias_e164, tAddrInfo.achE164 );
            }
            else
            {
			    CTransparentAddrList::GetFirstLetter( tAddrInfo.achEntryName, strLetter );

               // tAlias.SetAlias( tp_Alias_h323, tAddrInfo.achEntryName );
            }
			
            //�����Ŀ��ע����Ϣ�У���ʾ���� 
            vector<TAddrInfo>::iterator itfind = vctCnsRegInfo.begin();
            for ( ; itfind != vctCnsRegInfo.end(); itfind++ )
            {
                if ( 0 == strcmp( tAddrInfo.achEntryName, "" ) )
                {
                    if ( 0 == strcmp( tAddrInfo.achE164, itfind->achE164 ) )
                    {
                        break;
                    }
                }
                else
                {
                    if ( 0 == strcmp( tAddrInfo.achE164, "" ) )
                    {
                        if ( 0 == strcmp( tAddrInfo.achEntryName, itfind->achEntryName ) )
                        {
                            break;
                        }
                    }
                    else
                    {
                        if ( 0 == strcmp( tAddrInfo.achEntryName, itfind->achEntryName ) &&
                            0 == strcmp( tAddrInfo.achE164, itfind->achE164 ) )
                        {
                            break;
                        }
                    }
                } 
            }
            if ( itfind == vctCnsRegInfo.end() )
            {
                tAddrInfo.bOnLine = FALSE;
            }
            else
            {
                tAddrInfo.bOnLine = TRUE;
                tAddrInfo.m_emEndpointType = itfind->m_emEndpointType;
            }

            tAddrItem.tAddrInfo = tAddrInfo;
            tAddrItem.strNameLetter = strLetter;

			m_vctLocalAddrList.push_back(tAddrItem);
			
			nIndex++;
			
			u32 dwEntryNum = cAddrBook.GetNextAddrEntry( dwIndex, &cAddrEntry );
			if ( dwEntryNum == 0 )
			{
				break;
			}
			else
			{
				dwIndex = cAddrEntry.GetEntryIndex();
			}			
		}
		else
		{
			break;
		}
	}

    m_vctEntryList = m_vctLocalAddrList;
}

void CCommonInterface::UpdateLevelOneGroup()
{
	CAddrBook cAddrBook = m_pAddrBookCtrl->GetAddrBook();

	s8 aszGroupName[MAX_NAME_LEN + 1] = _T("");     //������

	CString strLetter;
	TAddrItem tAddrItem;
	tAddrItem.emItemType = emGroupItem;

	u32 *pdwGroup = new u32[MAX_ADDRGROUP];
	u32 dwNum = cAddrBook.FindLevelOneGroup( pdwGroup );

	CAddrMultiSetEntry cAddrGroup;
	for ( int i = 0; i < dwNum; i++ )
	{
		u32 dwGroupIndex = *(pdwGroup + i);
		cAddrBook.GetAddrMultiSetEntry( &cAddrGroup, dwGroupIndex );

		cAddrGroup.GetGroupName( aszGroupName, cAddrGroup.GetGroupNameLen() + 1 );

		TGroupInfo tGroupInfo;
		tGroupInfo.dwGroupIdx = cAddrGroup.GetGroupIndex(); 
		strncpy( tGroupInfo.achGroupName, aszGroupName, TP_MAX_ALIAS_LEN_CNC+1 ); 
		tGroupInfo.nEntryNum = cAddrGroup.GetEntryCount();
		u32* pEntryTable = cAddrGroup.GetEntryTable();
		for ( s32 i = 0; i < tGroupInfo.nEntryNum; i++ )
		{
			tGroupInfo.adwEntryIdx[i] = *(pEntryTable + i);
		}
		u32 adwDownGroup[MAX_ADDRGROUP] = {0};
		tGroupInfo.nDownGroupNum = cAddrBook.FindLowGroupOfGroupByIndex( tGroupInfo.dwGroupIdx, adwDownGroup );

		tAddrItem.tGroupInfo = tGroupInfo;

		CTransparentAddrList::GetFirstLetter( tGroupInfo.achGroupName, strLetter );
        //�������ǰ��2���ո񣬱�֤������Ŀǰ�� -2013.3.19 xcr
        CString strGroupLetter;
        strGroupLetter.Format( "  %s", (LPCTSTR)strLetter );
		tAddrItem.strNameLetter = strGroupLetter;

		m_vctLocalAddrList.push_back(tAddrItem);
	}
	if ( pdwGroup != NULL )
	{
		delete []pdwGroup;
		pdwGroup = NULL;
	}
	
}


void CCommonInterface::UpdateAddrGroupList()
{
	CAddrBook cAddrBook = m_pAddrBookCtrl->GetAddrBook();
	
	s8 aszGroupName[MAX_NAME_LEN + 1] = _T("");     //��Ŀ����
	
	TAddrItem tAddrItem;
	tAddrItem.emItemType = emGroupItem;
	
	//��ȡ����Ŀ����
	u32 dwUsedSize = cAddrBook.GetAddrGroupUsedSize();
	
	u32 dwIndex = 0;
	s32 nIndex = 0;
	CAddrMultiSetEntry cAddrGroup;
	dwIndex = cAddrBook.GetFirstAddrMultiSetEntry( &cAddrGroup );
	while ( nIndex < dwUsedSize )
	{
		if ( dwIndex != INVALID_INDEX )
		{	
			cAddrGroup.GetGroupName( aszGroupName, cAddrGroup.GetGroupNameLen() + 1 );
			
			TGroupInfo tGroupInfo;
			tGroupInfo.dwGroupIdx = cAddrGroup.GetGroupIndex(); 
			strncpy( tGroupInfo.achGroupName, aszGroupName, TP_MAX_ALIAS_LEN_CNC+1 ); 
			tGroupInfo.nEntryNum = cAddrGroup.GetEntryCount();
			u32* pEntryTable = cAddrGroup.GetEntryTable();
			for ( s32 i = 0; i < tGroupInfo.nEntryNum; i++ )
			{
				tGroupInfo.adwEntryIdx[i] = *(pEntryTable + i);
			}
			tAddrItem.tGroupInfo = tGroupInfo;
			m_vctGroupList.push_back(tAddrItem);
			
			nIndex++;
			
			u32 dwEntryNum = cAddrBook.GetNextAddrMultiSetEntry( dwIndex, &cAddrGroup );
			if ( dwEntryNum == 0 )
			{
				break;
			}
			else
			{
				dwIndex = cAddrGroup.GetGroupIndex();
			}			
		}
		else
		{
			break;
		}
	}
}

void CCommonInterface::SetAddrItemInfo( TAddrInfo& tAddrInfo, CAddrEntry& cAddrEntry )
{
	s8 aszEntryName[MAX_NAME_LEN + 1] = _T("");     //��Ŀ����
	s8 aszE164[MAX_E164NUM_LEN + 1] = _T("");       //E164��
	
	cAddrEntry.GetEntryName( aszEntryName, cAddrEntry.GetEntryNameLen() + 1 );
	cAddrEntry.GetMtNumber( aszE164, cAddrEntry.GetMtNumberLen() + 1 );
	
	tAddrInfo.dwEntryIdx = cAddrEntry.GetEntryIndex();
	strncpy( tAddrInfo.achEntryName, aszEntryName, TP_MAX_ALIAS_LEN_CNC+1 );
	strncpy( tAddrInfo.achE164, aszE164, MAX_E164NUM_LEN + 1 );
}

void CCommonInterface::GetGroupAddrInfo( const TGroupInfo& tGroupInfo, vector<TAddrInfo>& vctAddrInfo )
{
	if ( m_pAddrBookCtrl == NULL )
	{
		return;
	}
	CAddrBook cAddrBook = m_pAddrBookCtrl->GetAddrBook();

	vctAddrInfo.clear();
		
	u32 adwEntrySet[MAX_ADDRENTRY] = {0};
	u32 nNum = cAddrBook.GetGroupAllEntrySet( tGroupInfo.dwGroupIdx, adwEntrySet );
	for ( int i = 0; i < nNum; i++ )
	{
		bool bValid = cAddrBook.IsAddrEntryValid( adwEntrySet[i] );
		if ( !bValid )
		{
			continue;
		}
		CAddrEntry cEntry;
		cAddrBook.GetAddrEntry( &cEntry, adwEntrySet[i] );

		TAddrInfo tAddrInfo;
		SetAddrItemInfo( tAddrInfo, cEntry );
		 
 		vctAddrInfo.push_back(tAddrInfo); 
	}

//int nNum = tGroupInfo.nEntryNum;
// 	for ( int i = 0; i < nNum; i++ )
// 	{
// 		bool bValid = cAddrBook.IsAddrEntryValid( tGroupInfo.adwEntryIdx[i] );
// 		if ( !bValid )
// 		{
// 			continue;
// 		}
// 		CAddrEntry cEntry;
// 		cAddrBook.GetAddrEntry( &cEntry, tGroupInfo.adwEntryIdx[i] );
// 		
// 		TAddrInfo tAddrInfo;
// 		SetAddrItemInfo( tAddrInfo, cEntry );
// 
// 		vctAddrInfo.push_back(tAddrInfo); 
// 	}
}

//��ȡ�����Ա�б�
void CCommonInterface::GetAddrGroupMember( u32 dwGroupIndex, vector<TAddrItem>& vctGroupMemberList )
{
	vctGroupMemberList.clear();

	CAddrBook cAddrBook = ComInterface->GetAddrBook();	
	bool bValid = cAddrBook.IsAddrMultiSetEntryValid( dwGroupIndex );
	if ( !bValid )
	{
		return;
	}

    vector<TAddrInfo> vctCnsRegInfo;
	vctCnsRegInfo = m_pSipInfoCtrl->GetCnsRegInfo();

	CString strLetter;
	CAddrMultiSetEntry cGroup;
	cAddrBook.GetAddrMultiSetEntry( &cGroup, dwGroupIndex );	
	
	int nNum = cGroup.GetEntryCount();
	u32* pEntryTable = cGroup.GetEntryTable();	

	for ( int i = 0; i < nNum; i++ )
	{
		bool bValid = cAddrBook.IsAddrEntryValid( *pEntryTable );
		if ( !bValid )
		{
			pEntryTable++;
			continue;
		}
		CAddrEntry cEntry;
		cAddrBook.GetAddrEntry( &cEntry, *pEntryTable );
		
		TAddrItem tAddrItem;
		TAddrInfo tAddrInfo;
		SetAddrItemInfo( tAddrInfo, cEntry );

		tAddrInfo.dwInGroupIdx = dwGroupIndex;
		
        if ( strcmp( tAddrInfo.achEntryName, "" ) == 0 )
        {
            strLetter.Format( "%s", tAddrInfo.achE164 );
        }
        else
        {
		    CTransparentAddrList::GetFirstLetter( tAddrInfo.achEntryName, strLetter );
        }
		
        //�����Ŀ��ע����Ϣ�У���ʾ���� 
        vector<TAddrInfo>::iterator itfind = vctCnsRegInfo.begin();
        for ( ; itfind != vctCnsRegInfo.end(); itfind++ )
        {
            if ( 0 == strcmp( tAddrInfo.achEntryName, "" ) )
            {
                if ( 0 == strcmp( tAddrInfo.achE164, itfind->achE164 ) )
                {
                    break;
                }
            }
            else
            {
                if ( 0 == strcmp( tAddrInfo.achE164, "" ) )
                {
                    if ( 0 == strcmp( tAddrInfo.achEntryName, itfind->achEntryName ) )
                    {
                        break;
                    }
                }
                else
                {
                    if ( 0 == strcmp( tAddrInfo.achEntryName, itfind->achEntryName ) &&
                         0 == strcmp( tAddrInfo.achE164, itfind->achE164 ) )
                    {
                        break;
                    }
                }
            }            
        }
        if ( itfind == vctCnsRegInfo.end() )
        {
            tAddrInfo.bOnLine = FALSE;
        }
        else
        {
            tAddrInfo.bOnLine = TRUE;
            tAddrInfo.m_emEndpointType = itfind->m_emEndpointType;
        }

        tAddrItem.tAddrInfo = tAddrInfo;
        tAddrItem.strNameLetter = strLetter;

		vctGroupMemberList.push_back(tAddrItem);
		
		pEntryTable++;
	}
	
	//�¼�����
	u32 *pdwGroup = new u32[MAX_ADDRGROUP];
	u32 dwNum = cAddrBook.FindLowGroupOfGroupByIndex( dwGroupIndex, pdwGroup );
	
	s8 aszGroupName[MAX_NAME_LEN + 1] = _T(""); 
	TAddrItem tAddrItem;
	tAddrItem.emItemType = emGroupItem;

	CAddrMultiSetEntry cAddrGroup;
	for ( i = 0; i < dwNum; i++ )
	{
		u32 dwDownGroupIndex = *(pdwGroup + i);
		cAddrBook.GetAddrMultiSetEntry( &cAddrGroup, dwDownGroupIndex );
		
		cAddrGroup.GetGroupName( aszGroupName, cAddrGroup.GetGroupNameLen() + 1 );
		
		TGroupInfo tGroupInfo;
		tGroupInfo.dwGroupIdx = cAddrGroup.GetGroupIndex(); 
		strncpy( tGroupInfo.achGroupName, aszGroupName, TP_MAX_ALIAS_LEN_CNC+1 ); 
		tGroupInfo.nEntryNum = cAddrGroup.GetEntryCount();
		u32* pEntryTable = cAddrGroup.GetEntryTable();
		for ( s32 i = 0; i < tGroupInfo.nEntryNum; i++ )
		{
			tGroupInfo.adwEntryIdx[i] = *(pEntryTable + i);
		}
		tGroupInfo.dwInGroupIdx = dwGroupIndex;
		u32 adwDownGroup[MAX_ADDRGROUP] = {0};
		tGroupInfo.nDownGroupNum = cAddrBook.FindLowGroupOfGroupByIndex( tGroupInfo.dwGroupIdx, adwDownGroup );
		tAddrItem.tGroupInfo = tGroupInfo;

		CTransparentAddrList::GetFirstLetter( tGroupInfo.achGroupName, strLetter );
        //�������ǰ��2���ո񣬱�֤������Ŀǰ�� -2013.3.19 xcr
        CString strGroupLetter;
        strGroupLetter.Format( "  %s", (LPCTSTR)strLetter );
		tAddrItem.strNameLetter = strGroupLetter;
        
        vctGroupMemberList.push_back(tAddrItem);
	}
	if ( pdwGroup != NULL )
	{
		delete []pdwGroup;
		pdwGroup = NULL;
	}

}


void CCommonInterface::GetAddrGroupInfo( u32 dwGroupIndex, TGroupInfo& tGroupInfo )
{
	CAddrBook cAddrBook = ComInterface->GetAddrBook();

	s8 aszGroupName[MAX_NAME_LEN + 1] = _T(""); 

	CAddrMultiSetEntry cAddrGroup;
	cAddrBook.GetAddrMultiSetEntry( &cAddrGroup, dwGroupIndex );

	cAddrGroup.GetGroupName( aszGroupName, cAddrGroup.GetGroupNameLen() + 1 );
	
	tGroupInfo.SetNull();
	tGroupInfo.dwGroupIdx = cAddrGroup.GetGroupIndex(); 
	strncpy( tGroupInfo.achGroupName, aszGroupName, TP_MAX_ALIAS_LEN_CNC+1 ); 
	tGroupInfo.nEntryNum = cAddrGroup.GetEntryCount();
	u32* pEntryTable = cAddrGroup.GetEntryTable();
	for ( s32 i = 0; i < tGroupInfo.nEntryNum; i++ )
	{
		tGroupInfo.adwEntryIdx[i] = *(pEntryTable + i);
	}
	tGroupInfo.dwInGroupIdx = cAddrBook.FindUpGroupOfGroupByIndex( dwGroupIndex );
	u32 adwDownGroup[MAX_ADDRGROUP] = {0};
	tGroupInfo.nDownGroupNum = cAddrBook.FindLowGroupOfGroupByIndex( tGroupInfo.dwGroupIdx, adwDownGroup );
}


CString CCommonInterface::GetAddrGroupPath( u32 dwGroupIndex )
{
	CString strPath = _T("");
	CString strName;

	CAddrBook cAddrBook = ComInterface->GetAddrBook();

	s8 aszGroupName[MAX_NAME_LEN + 1] = _T(""); 
	CAddrMultiSetEntry cAddrGroup;
	
	u32 dwIndex = dwGroupIndex;
	while( dwIndex != INVALID_INDEX )
	{		
		cAddrBook.GetAddrMultiSetEntry( &cAddrGroup, dwIndex );

		cAddrGroup.GetGroupName( aszGroupName, cAddrGroup.GetGroupNameLen() + 1 );

		strName.Format( "\\%s", aszGroupName );
		strPath = strName + strPath;

		dwIndex = cAddrBook.FindUpGroupOfGroupByIndex( dwIndex );
	}
	return strPath;
}


//ȫ�ֵ�ַ��
const vector<TAddrItem>* CCommonInterface::GetGlobalAddrList()
{
	return &m_vctGlobalAddrList;
}

void CCommonInterface::GetCnsRegInfo( vector<TAddrInfo>* pvctCnsRegInfo )
{
	if ( NULL != m_pSipInfoCtrl ) 
	{
		*pvctCnsRegInfo = m_pSipInfoCtrl->GetCnsRegInfo();
	}
}

u16 CCommonInterface::UpdateGlobalAddrbook()
{
	if ( NULL == m_pSipInfoCtrl ) 
	{
		return ERR_CMS;
	}
	
	u16 wRe = m_pSipInfoCtrl->ReqSipRegInfo( emGetRegInfoType_CNS );
	
	return wRe;	
}


LRESULT CCommonInterface::OnRefreshGlobalAddrBook( WPARAM wParam, LPARAM lParam )
{
	if ( NULL == m_pSipInfoCtrl ) 
	{
		return ERR_CMS;
	}
	
	vector<TAddrInfo> vctCnsRegInfo;
	vctCnsRegInfo = m_pSipInfoCtrl->GetCnsRegInfo();

    CString strLetter;
	TAddrItem tAddrItem;
	tAddrItem.emItemType = emEntryItem;
	m_vctGlobalAddrList.clear();

	for( int i = 0; i < vctCnsRegInfo.size(); i++ )
	{
		TAddrInfo tAddrInfo = vctCnsRegInfo.at(i);
		tAddrInfo.dwEntryIdx = i;
        if ( 0 == strcmp( tAddrInfo.achEntryName, "" ) )
        {
            strLetter.Format( "%s", tAddrInfo.achE164 );
        }
        else
        {
            CTransparentAddrList::GetFirstLetter( tAddrInfo.achEntryName, strLetter );
        }		

		tAddrItem.tAddrInfo = tAddrInfo;
      
		tAddrItem.strNameLetter = strLetter;

		m_vctGlobalAddrList.push_back( tAddrItem );
	}

	CMsgDispatch::SendMessage( UI_CNS_REFRESH_GLOBAL_ADDRBOOK, wParam, lParam );

    //ͬʱ���±��ص�ַ������״̬
    UpdateAddrBook( wParam, lParam );
	return NO_ERROR;
}