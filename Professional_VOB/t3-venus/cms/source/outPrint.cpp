// outPrint.cpp: implementation of the COutPrint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "outPrint.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

COutPrint::COutPrint()
{

}

COutPrint::~COutPrint()
{

}


void COutPrint::GetAllConfInfo()
{
   TCMSConf tConf;
   BOOL32 bInf =  ComInterface->IsInConf(&tConf);
   if ( !bInf )
   {
       PrtMsg( "\n    Ŀǰ�޻�����Ϣ\n" );
   }
   else
   {  
        
	   PrtMsg("\n    ID:%d, Name:%s, E164:%s, confType:%d , ChairMan:%s(CnsID=%d),speaker:%s(CnsID=%d),DualAlairs:%s(CnsID:%d)\n  ",  
                                    tConf.m_wConfID,tConf.m_achConfName,tConf.m_achConfE164,tConf.m_emConfType, tConf.m_tChairName.m_abyAlias, 
                                    tConf.m_wDefaultChairMan,tConf.GetSpeakerAliars(),tConf.m_wSpeaker,tConf.GetDualAliars(),tConf.m_wDual);

           CTime tmStart( tConf.m_tStartTime ); 
           PrtMsg(  "\n    ���鿪ʼʱ�䣺%.4d-%.2d-%.2d %.2d:%.2d:%.2d\n", 
                         tmStart.GetYear(), tmStart.GetMonth(),tmStart.GetDay(), tmStart.GetHour(),tmStart.GetMinute(),tmStart.GetSecond() );
           
       

       
   }
}


void COutPrint::GetConfInfo( u16 wConfID )
{
//     TCMSConf* p = ComInterface->GetConfByID( wConfID );
//     if ( p == NULL )
//     {
//         PrtMsg( "\n    δ��ȡ�������\n" );
//     }
//     else
//     {
//         PrtMsg("\n    ID:%d, Name:%s, E164:%s, ChairMan:%s(CnsID=%d), speaker:%s(CnsID=%d), DualAlairs:%s(CnsID:%d), ConfType=%d\n  ",  
//                                     p->m_wConfID,p->m_achConfName,p->m_achConfE164,p->GetChairManAliars(), p->m_wDefaultChairMan, p->GetSpeakerAliars(),p->m_wSpeaker,p->GetDualAliars(),p->m_wDual,p->m_emConfType);
// 
//         CTime tmStart( p->m_tStartTime ); 
//         PrtMsg(  "\n    ���鿪ʼʱ�䣺%.4d-%.2d-%.2d %.2d:%.2d:%.2d \n", 
//                          tmStart.GetYear(), tmStart.GetMonth(),tmStart.GetDay(), tmStart.GetHour(),tmStart.GetMinute(),tmStart.GetSecond() );
//     }
}


void COutPrint::GetConfCnsInfo( u16 wConfID , u16 wCnsID)
{
    
    TCMSConf tConf;
    BOOL32 bInfo = ComInterface->IsInConf( &tConf );
    if ( !bInfo )
    {
        PrtMsg( "\n    δ��ȡ��������Ϣ\n" );
    }
    else
    {  
        TCnsInfo* pCns = tConf.GetCnsInfoByID( wCnsID );
        if ( pCns == NULL )
        {
            PrtMsg( "\n    δ��ȡ���᳡��Ϣ\n" );
        }
        else
        {
            PrtMsg("\n    ID:%d, Name:%s, emEpType:%d, bOnline:%d, bMute:%d, bQuiet:%d,  emCallReason:%d \n  ",  
                wCnsID,tConf.m_achConfName,pCns->m_emEpType,pCns->m_bOnline,pCns->m_bMute, pCns->m_bQuiet,pCns->m_emCallReason);
 
        }

       
    }
}


void COutPrint::GetConfCnsInfo( u16 wConfID )
{
    TCMSConf tConf;
    BOOL32 bInfo = ComInterface->IsInConf( &tConf );
    if ( !bInfo ) 
    {
        PrtMsg( "\n    δ��ȡ������\n" );
    }
    else
    {    
        for ( int j = 0; j< tConf.m_tplCnsList.Size(); j++ )
        {
            PrtMsg("\n    cnsID:%d, achRoomName:%s, emEpType:%d, bOnLine:%d, wLevel=%d, bMute:%d, bQuiet:%d, emCallReason:%d \n", 
            tConf.m_tplCnsList.GetAt(j).m_wEpID, tConf.m_tplCnsList.GetAt(j).m_achRoomName,
            tConf.m_tplCnsList.GetAt(j).m_emEpType, tConf.m_tplCnsList.GetAt(j).m_bOnline, tConf.m_tplCnsList.GetAt(j).m_wLevel,
            tConf.m_tplCnsList.GetAt(j).m_bMute, tConf.m_tplCnsList.GetAt(j).m_bQuiet, tConf.m_tplCnsList.GetAt(j).m_emCallReason );
        } 
        
    }
}


void COutPrint::GetLocalCnsInfo()
{
    TTPCnsInfo tCnsInfo;
    ComInterface->GetLocalCnsInfo( tCnsInfo );
    in_addr addr;
    CString strIp;
    int nCount = sizeof(tCnsInfo.m_adwIP)/sizeof(u32);
    for ( int i = 0 ; i< nCount ; i++ )
    {  
        CString temp;
        addr.S_un.S_addr = tCnsInfo.m_adwIP[i];
        temp.Format("%s    " , inet_ntoa(addr));
        strIp += temp;
    } 
    

    PrtMsg("\n    Name:%s, E164:%s, DualPos:%d, Level:%d, ScreenNum:%d, IP:%s\n",
              tCnsInfo.m_achRoomName,tCnsInfo.m_achE164,tCnsInfo.m_byDualPos,tCnsInfo.m_emLevel,tCnsInfo.m_wScreenNum,strIp);
}


void COutPrint::IsLocalCnsInConf()
{ 
    TTPCnsConfStatus  confstate = ComInterface->GetLocalCnsConfState() ;
   
    PrtMsg("\n    TConfState: %d ( %d:CALL_IDLE, %d:CALL_CALLING, %d:CALL_CONNECTED), confID:%d, confName:%s, confType:%d, MixMotive:%d\n, ", 
        confstate.emState, em_CALL_IDLE, em_CALL_CALLING, em_CALL_CONNECTED, confstate.wConfID, confstate.achConfName, confstate.m_emCallType, confstate.m_bMixMotive);

    TCMSConf conf;
    BOOL32 bInConf = ComInterface->IsInConf( &conf );
    if ( bInConf )
    {
        PrtMsg("\n    ID:%d, Name:%s, E164:%s, ChairMan:%s(CnsID=%d)\n  ",  
                conf.m_wConfID,conf.m_achConfName,conf.m_achConfE164,conf.GetChairManAliars(), conf.m_wDefaultChairMan);
     
        CTime tmStart( conf.m_tStartTime );
        PrtMsg(  "    ���鿪ʼʱ�䣺%.4d-%.2d-%.2d %.2d:%.2d:%.2d\n", 
                         tmStart.GetYear(), tmStart.GetMonth(),tmStart.GetDay(), tmStart.GetHour(),tmStart.GetMinute(),tmStart.GetSecond() );
    }      
}

void COutPrint::ShowConfTemp( u16 wID )
{
    /*
     if ( wID == INVALID_WORD )  //��ʾ����
     {
         TplArray<TTPConfTemplate> *pLst = ComInterface->GetConfTemplateList();
         if ( pLst == NULL )
         {
             PrtMsg( "\n    ��ȡ����ģ���б�ʧ��\n" );
         }
         else
         {  
             CString msg;
             int nCount = pLst->Size();
			 PrtMsg( "    Num: %d \n", nCount );
             for ( int i = 0 ; i< nCount; i++ )
             {  
                  
                 PrtMsg("\n    ID:%d, Name:%s, E164:%s, ChairMan: %d \n  ",  
                     pLst->GetAt(i).m_wID,pLst->GetAt(i).m_achConfName,pLst->GetAt(i).m_achConfE164, pLst->GetAt(i).m_wDefaultChairMan ); 
                                 
             }           
         }
     }
     else 
     {
         // ��ʾһ��
         TTPConfTemplate* p = ComInterface->GetConfTemplateByID( wID );
         if ( p == NULL )
         {
             PrtMsg( "\n    δ��ȡ������ģ��\n" );
         }
         else
         {
             PrtMsg("\n    ID:%d, Name:%s, E164:%s, ChairMan: %d\n  ",  
                 p->m_wID,p->m_achConfName,p->m_achConfE164, p->m_wDefaultChairMan);
         }
     }
     */
}


/*

  enum EMPosPic
  {
  emPic_Invalid = 0,
		emPic_Local,
        emPic_Static,
        emPic_Speaker,
        emPic_Dual,
        emPic_Poll,
        emPic_SelView,              //ѡ��Զ�� 
        emPic_SelDual,              //ѡ��˫��
        emPic_SelLocal,             //ѡ������
};
*/
void COutPrint::ShowScrnInfo()
{
    vector<TScreenInfo> vctScreenInfo;
    u16 re = ComInterface->GetCnsScreenInfo( vctScreenInfo );
    if ( re != NO_ERROR )
    {
       PrtMsg( "\n    ��ȡ����Ϣʧ��\n" );  
    }

    vector<TScreenInfo>::iterator it = vctScreenInfo.begin();
    while ( it != vctScreenInfo.end() )
    {
        PrtMsg("\n    ID:%d, Name:%s, emPic:%d  \n ( emPic_Invalid:%d, emPic_Local:%d, emPic_Static:%d, emPic_Speaker:%d, \
 emPic_Dual:%d, emPic_Poll:%d, emPic_SelView:%d, emPic_SelDual:%d,emPic_SelLocal:%d )\n", 
            it->byScreenID, it->achCnsName,it->emPosPic, emPic_Invalid, emPic_Local, emPic_Static,emPic_Speaker, emPic_Dual,
            emPic_Poll, emPic_SelView,emPic_SelDual,emPic_SelLocal);
        it ++;
    }
}

void COutPrint::ShowCnsList()
{
	TTPCnList  tCnList;
	ComInterface->GetConnectCnsList( tCnList );

	PrtMsg( "    Num: %d \n", tCnList.wNum );
	for ( int i = 0; i< tCnList.wNum; i++ )
	{
		TTPCn tCn = tCnList.tCn[i];
		PrtMsg("    Inst: %d,  Name: %s\n", tCn.byInsId, tCn.achName );  
	}
}

void COutPrint::ShowAllUseInfo()
{
     
    TplArray<CUserFullInfo>* pUserLst = ComInterface->GetUserList();
    if ( pUserLst == NULL )
    {
        PrtMsg("    δ��ȡ���û���Ϣ\n" );  
        return;
    }

    int nSize = pUserLst->Size();
    for( int i = 0; i< nSize ; i++ )
    {
        PrtMsg("    Name: %s\n", pUserLst->GetAt(i).GetName() );  
    }


}

void COutPrint::ShowLocalIP()
{
   u32 IP;
   BusinessManagePtr->GetLocalIP( IP );
   in_addr t;
   t.S_un.S_addr = htonl(IP); 
   PrtMsg("    LocalIP: %s\n", inet_ntoa( t ) );  
}

#include "VideoLogic.h" 
void COutPrint::SetDecVol( u8 abyVol )
{
    CVideoLogic::GetLogicPtr()->SetDecVol( abyVol );
}

void COutPrint::ShowDecVol()
{
    PrtMsg("    vol: %d\n", CVideoLogic::GetLogicPtr()->GetDecVol() );   
}


#include "alarminfologic.h"
void COutPrint::ShowAlarmInfoLst()
{
    vector<String> alarmLst = CAlarmInfoLogic::GetLogicPtr()->GetAlarmMsgLst();
    vector<String>::iterator it = alarmLst.begin();
    while( it != alarmLst.end() )
    {
        PrtMsg("    alarm: %s\n", it->c_str() );  
        it++;
    }
}

void COutPrint::ShowAddrbook()
{
    CAddrBook cAddrBook = ComInterface->GetAddrBook();	

	//��ȡ������Ŀ����
    u32 dwEntrySize = cAddrBook.GetAddrEntryUsedSize();
    u32 dwGroupSize = cAddrBook.GetAddrGroupUsedSize();

    vector<TAddrItem> vctLocalList; 
    vctLocalList = *ComInterface->GetLocalAddrList();
    
    PrtMsg("    ��ַ�� �᳡����: %d, �����: %d, LocalAddrList.size: %d\n", dwEntrySize, dwGroupSize, vctLocalList.size() ); 

	s32 nIndex = 0;

    CAddrEntry cAddrEntry;
    u32 dwFirstIndex = cAddrBook.GetFirstAddrEntry( &cAddrEntry );

	while ( nIndex < dwEntrySize )
	{
		if ( dwFirstIndex != INVALID_INDEX )
		{	
			TAddrInfo tAddrInfo;
			ComInterface->SetAddrItemInfo( tAddrInfo, cAddrEntry );

			PrtMsg("    EntryIndex: %d, Name: %s, E164: %s\n", 
				tAddrInfo.dwEntryIdx, tAddrInfo.achEntryName, tAddrInfo.achE164 );
  	
			nIndex++;
			
			u32 dwEntryNum = cAddrBook.GetNextAddrEntry( dwFirstIndex, &cAddrEntry );
			if ( dwEntryNum == 0 )
			{
				break;
			}
			else
			{
				dwFirstIndex = cAddrEntry.GetEntryIndex();
			}			
		}
		else
		{
			break;
		}
	}

    //PrtMsg("    FirstIndex: %d, EntryIndex: %d, Name: %s, E164: %s\n", dwFirstIndex, tAddrInfo.dwEntryIdx, tAddrInfo.achEntryName, tAddrInfo.achE164 );
}

void COutPrint::ShowOnlineAddr()
{
	vector<TAddrInfo> vctCnsRegInfo;
	ComInterface->GetCnsRegInfo(&vctCnsRegInfo);

	for( int i = 0; i < vctCnsRegInfo.size(); i++ )
	{
		TAddrInfo tAddrInfo = vctCnsRegInfo.at(i);
		tAddrInfo.dwEntryIdx = i;
		
		PrtMsg("    EntryIndex: %d, Name: %s, E164: %s\n", 
			tAddrInfo.dwEntryIdx, tAddrInfo.achEntryName, tAddrInfo.achE164 );	
	}
	
    vector<TAddrItem> vctGlobalList; 
    vctGlobalList = *ComInterface->GetGlobalAddrList();

    PrtMsg("    ���ߵ�ַ�� �᳡����: %d, GlobalList.size: %d\n", vctCnsRegInfo.size(), vctGlobalList.size() ); 
}

void COutPrint::ShowAddrEntry( u32 dwEntryIndex )
{
    CAddrBook cAddrBook = ComInterface->GetAddrBook();
    bool bValid = cAddrBook.IsAddrEntryValid( dwEntryIndex );
    if ( !bValid )
    {
        PrtMsg("    ��ַ�������ڴ˻᳡"); 
        return;
    }

    CAddrEntry cEntry;
    cAddrBook.GetAddrEntry( &cEntry, dwEntryIndex );

    TAddrInfo tAddrInfo;
	ComInterface->SetAddrItemInfo( tAddrInfo, cEntry );

    PrtMsg("    �᳡Index: %d, Name: %s, E164: %s\n", tAddrInfo.dwEntryIdx, tAddrInfo.achEntryName, tAddrInfo.achE164 );
}

void COutPrint::ShowDlgName( char* pchDlgName )
{
    if ( pchDlgName == NULL )
    {
        PrtMsg(" �����봰������! ");
    }
    else
    {
        HWND hwnd = UIManagePtr->GetWindowPtr( pchDlgName )->GetSafeHwnd();
        
        if ( hwnd == NULL)
        {
            PrtMsg(" ����������! ");
            return;
        }

        RECT rect;
        GetWindowRect( hwnd, &rect );      
        PrtMsg("    ����%s:���Ͻ����꣺%d��%d ���½����꣺%d��%d\n", pchDlgName, (int)rect.left, (int)rect.top, (int)rect.right, (int)rect.bottom );
    }

}

