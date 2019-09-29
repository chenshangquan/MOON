// TouchListHelp.cpp: implementation of the CTouchListHelp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TouchListHelp.h"
#include "TouchListProperty.h"
#include <time.h>
#include <algorithm>
#include "AddrList.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
 
const String CTouchListHelp::strItemDefault = "ImageItem";
const String CTouchListHelp::strItemText = "TextItem";

const String CTouchListHelp::strItemAddrList = "AddrListItem";

//------模板系统列表-------
const String CTouchListHelp::strConfTemplate = "TouchListConfTemp";
const String CTouchListHelp::strTempCns = "TouchListTempCns";
const String CTouchListHelp::strItemTempPoll = "TouchListTempPoll";

//
const String CTouchListHelp::strConfLst = "TouchListConf";
const String CTouchListHelp::strConfCns = "TouchListConfInfo";

//地址簿列表
const String CTouchListHelp::strListAddr = "TouchListAddr";
const String CTouchListHelp::strListCnsList = "TouchListCnsList";
const String CTouchListHelp::strListConnectCn = "ListConnectCns";

const String CTouchListHelp::strListUser = "TouchListUser";   //用户列表
const String CTouchListHelp::strListAlarm = "TouchListAlarm"; //告警列表
 
//菜单列表
const String CTouchListHelp::strListMenu = "TouchListMenu";
const String CTouchListHelp::strListTvw = "TouchListTvw";		//电视墙列表
const String CTouchListHelp::strListConfMenu = "HoriListConfMenu";
const String CTouchListHelp::strVerListConfMenu = "VerListConfMenu";
const String CTouchListHelp::strListDualSrc = "ListDualSrc";
const String CTouchListHelp::strListWebManage = "ListWebManage";

CTouchListHelp::CTouchListHelp()
{ 
}

CTouchListHelp::~CTouchListHelp()
{

}

  

//模板列表
bool CTouchListHelp::TransData( IItemList* pList, Value_TouchListConfTemp &val) 
{
    if ( pList == NULL || val.m_pvctConfTemplate == NULL )
    {
        return false;
    }

    IBaseItem* pBaseItem = pList->GetItemData();
    pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert ); 
    pBaseItem->SetMoveStatus(true); 
    
    sort( val.m_pvctConfTemplate->begin(), val.m_pvctConfTemplate->end(), CTransparentAddrList::ConfTempCompare );
    
    Args_MakeItem args;
    args.pList = pList;
    args.bDrag = val.m_bDrag;
    args.strClickItemFunc = val.m_strItemFunc;
    args.pVctSubItem = val.m_pVctSubItem;
    args.strImageItem = "TempListItem";
    args.strTxtItem = "TextItem";
    
    TTPCnsInfo tCnsInfo;
    BusinessManagePtr->GetLocalCnsInfo(  tCnsInfo );
    
    if ( strlen( tCnsInfo.m_achRoomName ) == 0  )
    {
        return false;
    }
    
    s32 count =  val.m_pvctConfTemplate->size(); 
	for ( int j = 0; j < count; j++ )
    {
		Data_ConfTemp UserData( *( &val.m_pvctConfTemplate->at(j) ) );  //会议模板
		UserData.SetDataKey( j );
		
		args.nKey = j;
		args.strTxt = val.m_pvctConfTemplate->at(j).m_abyAlias;
		args.pUserData = &UserData;
		
        MakeItem( args ); 
	}

    /*
    //默认ID为0的会议模板为开启临时会议的模板，在此不显示出来
    for ( int j= 0; j < count; j++ )
    {   
        if ( val.m_pvctConfTemplate->GetAt(j).m_wID == INSTANT_CONFTEMPLATE_ID )
         { //临时会议的会议模板不显示
             continue;
         }
        //只显示当前cns为主席的会议模板
        char*pChairManName = ( *( (TCMSConfTemplate* )&val.m_pAryConfTemplate->GetAt(j)) ).GetChairManAliars();
        if (  val.m_bShowAll || 
             (!val.m_bShowAll &&  pChairManName != NULL && strcmp(pChairManName, tCnsInfo.m_achRoomName ) == 0 ) )
        {
            String txt =  val.m_pAryConfTemplate->GetAt(j).m_achConfName;  
            Data_ConfTemp UserData( *( (TCMSConfTemplate* )&val.m_pAryConfTemplate->GetAt(j)) );  //会议模板
            UserData.SetDataKey(val.m_pAryConfTemplate->GetAt(j).m_wID );
            
            args.nKey = j;
            args.strTxt = txt;
            args.pUserData = &UserData;
            
            MakeItem( args ); 
        } 
    }
	*/
    
	return true;
}
 
//会议模板中的cns列表
bool CTouchListHelp::TransData(  IItemList* pList , Value_TouchListTempCns &val /* TEpAddrList  &tCnsLst  ,  String strClickItemFunc,  ARRAY<String> * pVctSubItem,BOOL32 bDrag*/)
{
    IBaseItem* pBaseItem = pList->GetItemData();
    pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert ); 
    pBaseItem->SetMoveStatus(true);  
   
    TEpAddrList tCnsLst  = val.m_tCnsLst;
    vector<TEpAddr> vctCnsList;
    int count =  tCnsLst.m_wNum;
    for ( int i = 0; i < count; i++ )
    {
        vctCnsList.push_back( tCnsLst.m_tCnsList[i] );
    }
    
    sort( vctCnsList.begin(), vctCnsList.end(), CTransparentAddrList::TempCnsCompare );
    
    Args_MakeItem arg;
    arg.pList = pList;
    arg.bDrag = val.m_bDrag;
    arg.strClickItemFunc = val.m_strClickItemFunc ;
    arg.pVctSubItem = val.m_pVctSubItem ;
    arg.strImageItem =  "TempListItem";
    arg.strTxtItem = "TextItem";

//     TTPCnsInfo  tCnsInfo;
//     BusinessManagePtr->GetLocalCnsInfo( tCnsInfo );
    for ( int j = 0; j< count ; j++ )
    {   
        
        String txt = vctCnsList[j].m_tAlias.m_abyAlias;  

       // if ( strcmp( txt.c_str(),tCnsInfo.m_achRoomName) == 0 )
        if ( val.m_wChairManID == vctCnsList[j].m_wEpID ) 
        { //主cns不在列表中显示
            continue;
        }

        Data_CnsAddr userData( vctCnsList[j] ); //TEpAddr
        userData.SetDataKey( vctCnsList[j].m_wEpID ); 
       
        arg.strTxt = txt;
        arg.nKey = j;
        arg.pUserData = &userData; 
        MakeItem( arg ); 
    }
    return true;
}
 
//会议模板中轮询列表
bool CTouchListHelp::TransData( IItemList* pList,  TCMSConfTemplate &tConfTemp,  String strClickItemFunc,  ARRAY<String> * pVctSubItem,BOOL32 bDrag)
{     
    IBaseItem* pBaseItem = pList->GetItemData();
	pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert );
    pBaseItem->SetMoveStatus(true);


    Args_MakeItem arg;
    arg.pList = pList;
    arg.bDrag = bDrag;
    arg.strClickItemFunc = strClickItemFunc;
    arg.pVctSubItem = pVctSubItem;
    arg.strImageItem =  "TempListItem";
    arg.strTxtItem = "TextItem";

    for ( int i = 0; i < tConfTemp.m_tTurnList.m_wNum; i++ )
    {  
        String txt = "";
        u16 wCnsID = tConfTemp.m_tTurnList.m_awList[i];
        TEpAddr *p = tConfTemp.GetCnsAddrByID( wCnsID ) ;//BusinessManagePtr->GetCnsInfoFromTemplateByID(tConfTemp.m_wID, wCnsID);
        if ( p != NULL )
        {
            txt = p->m_tAlias.m_abyAlias;
        }
        
        Data_CnsID userData( wCnsID ); //cnsID
        userData.SetDataKey(wCnsID); 
        
        arg.nKey = i;
        arg.strTxt = txt;
        arg.pUserData = &userData; 
        MakeItem( arg );
    }
    return true;
}


//会议中cns列表
bool CTouchListHelp::TransData( IItemList* pList, Value_TouchListConfInfo &val )
{ 
    IBaseItem* pBaseItem = pList->GetItemData();
    pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert );
    pBaseItem->SetMoveStatus(true);
    s32 count = val.m_tConf.m_tplCnsList.Size();

	vector<TCnsInfo> vctCnsList;
	for ( int i = 0; i < count; i++ )
	{
		vctCnsList.push_back( val.m_tConf.m_tplCnsList.GetAt(i) );
	}

	sort( vctCnsList.begin(), vctCnsList.end(), CTransparentAddrList::CnsInfoCompare );

    Args_MakeItem args;
    args.pList = pList;
    args.bDrag = val.m_bDrag;
    args.strClickItemFunc = val.m_strClickItemFunc;
    

    for ( i = 0; i < count; i++ )
    {  
		EmTPEndpointType emType = vctCnsList.at(i).m_emEpType;
        if ( emTPEndpointTypeCNS != emType &&  emTPEndpointH323MT != emType && emTPEndpointH323SingleMCU != emType )
        {  //如果类型不是cns则过滤掉，不显示
            continue;
        }

        String txt = vctCnsList[i].m_achRoomName; 
        u16 wCnsID = vctCnsList[i].m_wEpID;
        Data_ConfCns userData( vctCnsList[i] );  
        userData.SetDataKey(vctCnsList[i].m_wEpID);
        
        String strImageItem = strItemAddrList;
        if ( BusinessManagePtr->IsCnsChairMan(wCnsID)) ///*BusinessManagePtr->IsLocalCns( txt )*/ dyy 2013年8月8日 显示主会场为绿色
        {
            strImageItem = "MainCnsItem";
        }

        ARRAY<String> vct; 
        
        args.strTxt = txt; 
        args.nKey = i;
        args.pUserData = &userData;
        args.strImageItem = strImageItem;
		args.strTxtItem = strItemText;
     
		switch ( val.m_lstType )
		{
        case  em_ConfLstTypeCns :
            {
                if ( !vctCnsList[i].m_bOnline )
                {
                    //vct.push_back("ImageItemCnsOffline");
					args.strTxtItem = "TextItemOfflineCns";
                }
                else
                {
                    //按照如下顺序判断状态：哑音 静音 双流  发言人 
                    //哑音
                    if ( vctCnsList[i].m_bMute )
                    {
                        vct.push_back("ImageItemCnsMute");
                    }
                    
                    //静音
                    if (vctCnsList[i].m_bQuiet )
                    {
                        vct.push_back("ImageItemCnsSilence");
                    }

					//双流
                    if ( val.m_tConf.m_wDual != INVALID_WORD && 
                        vctCnsList[i].m_wEpID == val.m_tConf.m_wDual )
                    {
                        vct.push_back("ImageItemCnsDual");
                    } 
                    
                    //发言人
                    if ( val.m_tConf.m_wSpeaker != INVALID_WORD && 
                        vctCnsList[i].m_wEpID == val.m_tConf.m_wSpeaker )
                    {
                        vct.push_back("ImageItemCnsSpeaker");
                    }                   
                }
                               
                args.pVctSubItem = &vct; 
		    	MakeItem( args ); 
            }
            break;
        case em_ConfLstTypeAudmix:
            {
				if ( !vctCnsList[i].m_bOnline )
                {
                    continue;
                }
              
                TCMSConf tConf = val.m_tConf;
                BOOL bCanDrag = val.m_bDrag;
                u16 wCnsId = vctCnsList[i].m_wEpID;
				
// 				if ( tConf.IsStartAudMix() )
// 				{
					if ( -1 != tConf.GetCnsIndexFrmAuxLst( wCnsId ) )
					{
						vct.push_back("ImageMixItemSelected");
						bCanDrag = FALSE;
					}
					else
					{
						vct.push_back("ImageItemAudMixCheck");
					}

					//隐藏讨论发言人设置，列表中不显示发言人图标
// 					u16 wSpeakerId = val.m_tConf.m_tAudmixList.GetSpeakerEpID();
// 					if ( wSpeakerId != TP_INVALID_INDEX && wSpeakerId == wCnsId )
// 					{
// 						vct.push_back("ImageItemCnsSpeaker");
// 					}
/*				}*/
                
                args.bDrag = bCanDrag;
                args.pVctSubItem = &vct; 
		    	MakeItem( args ); 
            }
            break;
        case em_ConfLstTypeTvw:
            {
				if ( !vctCnsList[i].m_bOnline )
                {
                    continue;
                }
              
                TCMSConf tConf = val.m_tConf;
                BOOL bCanDrag = val.m_bDrag;
                vct.push_back("ImageItemCnsToTvw");
//                 s8* pAliars = vctCnsList[i].m_achRoomName;
//                 if ( BusinessManagePtr->IsCnsInTvw( pAliars ) )
//                 {
//                     vct.push_back("ImageItemSelected");
//                     bCanDrag = FALSE;
//                 }
//                 else
//                 {
//                     vct.push_back("ImageItemCnsToTvw");
//                 } 
                
                args.bDrag = bCanDrag;
                args.pVctSubItem = &vct; 
		    	MakeItem( args ); 
            }
             break;
        case  em_ConfLstTypwSelView:
            {
                if ( !vctCnsList[i].m_bOnline )
                {
                    continue;
                }

                
                if ( strcmp(val.m_tConf.m_tChairName.m_abyAlias, vctCnsList[i].m_achRoomName) == 0 )                 
                {
                    continue; //主席不显示在选看列表中
                }
                
                TCMSConf tConf = val.m_tConf;
                BOOL bCanDrag = val.m_bDrag; 
                s8* pAliars = vctCnsList[i].m_achRoomName;
                //vct.push_back( "ImageItemCnsToView" ); 
                args.bDrag = bCanDrag;
                args.pVctSubItem = &vct; 
		    	MakeItem( args ); 
            }
            break;
        }
    }
    return true;

}


//会议列表
bool CTouchListHelp::TransData( IItemList* pList,Value_TouchListConf &val)
{
    if ( val.m_pTplAryConf == NULL )
    {   
        TRACE("\n[CTouchListHelp::TransData] 会议列表中数据为空\n");
        return false;
    }

    IBaseItem* pBaseItem = pList->GetItemData();
    pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert );
    pBaseItem->SetSortAlgorithm( IAlgorithm::strCharacter );
    pBaseItem->SetMoveStatus(true);
     
    
    
 
    for ( int i = 0; i < val.m_pTplAryConf->size(); i++ )
    {  
        IBaseItem* pItem = CItemFactory::GetSingletonPtr()->CreateItem( "AddrListItem" ) ;
        if ( CListItem* pListItem = dynamic_cast<CListItem*>(pItem) )
        {
            pItem->SetLayoutAlgorithm( IAlgorithm::strHoriConfLst ); 
            pItem->SetDragStatus(false);
            pItem->SetFunc( val.m_strItemFunc );
            Data_Conf userData( val.m_pTplAryConf->at(i));  
            userData.SetDataKey( val.m_pTplAryConf->at(i).m_wConfID ); 
            pItem->SetUserData( &userData ); 
        }	
        
        IItemList *pNew = pList->AddItem( i, pItem, emGroup );
        delete pItem;
		pItem = 0;
        
        IBaseItem *pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "TextItemConfLst" );
        if ( CExTextItem* pTextItem = dynamic_cast<CExTextItem*>(pSubItem) )
        {   
             CTime startTm ( val.m_pTplAryConf->at(i).m_tStartTime );
             CString date = startTm.Format ("%Y.%m.%d");
             CString time = startTm.Format("%H:%M");
              
             pTextItem->SetText( (LPCSTR)date );
             pTextItem->SetSecondText( (LPCSTR)time  ); 
        }  
        pNew->ModifyItem( 0, pSubItem ); 
        delete pSubItem; 
        pSubItem = 0;

        pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "TextItemConfLst" );
        if ( CExTextItem* pTextItem = dynamic_cast<CExTextItem*>(pSubItem) )
        {    
            pTextItem->SetText( "会议名称"  ); 
            pTextItem->SetSecondText( "主会场" ); 
        } 
        pNew->ModifyItem( 1, pSubItem ); 
        delete pSubItem; 
        pSubItem = 0;


        pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "TextItemConfLst" );
        if ( CExTextItem* pTextItem = dynamic_cast<CExTextItem*>(pSubItem) )
        {     
            
            pTextItem->SetText(val.m_pTplAryConf->at(i).m_achConfName ); 
           // u16 csnID = val.m_pTplAryConf->at(i).m_wDefaultChairMan;
           // TCnsInfo *p = val.m_pTplAryConf->at(i).GetCnsInfoFrmCnsLst( csnID );
           // if( p != NULL )
//             {    
//                  pTextItem->SetSecondText(p->m_achRoomName );  
//             } 

            if ( strlen( val.m_pTplAryConf->at(i).m_tChairName.m_abyAlias) > 0 ) 
            {
                pTextItem->SetSecondText(val.m_pTplAryConf->at(i).m_tChairName.m_abyAlias );  
            }
            
        } 
        pNew->ModifyItem( 2, pSubItem ); 
        delete pSubItem; 
        pSubItem = 0;
   
        
        // 添加 图标
        ARRAY<String> *pVctSubItem = val.m_pVctSubItem;
        if ( pVctSubItem == NULL )
        { 
            continue;
        }

        ARRAY<String>::iterator it = pVctSubItem->begin();
        int i = 3;
        while ( it != pVctSubItem->end() )
        {   
            pSubItem= CItemFactory::GetSingletonPtr()->CreateItem( *it ) ; 
            pNew->ModifyItem(i++,pSubItem );  
            delete pSubItem; 
            pSubItem = 0;
            it++;
        }

    }

    return true;
}


//菜单栏
bool CTouchListHelp::TransData( IItemList* pList, ARRAY<TMenuItemInfo> *pvctMenuLst, BOOL32 bDrag )
{
    IBaseItem* pBaseItem = pList->GetItemData();
    pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert );

    Args_MakeItem arg;
    arg.pList = pList;
    arg.bDrag = bDrag;  


    ARRAY<TMenuItemInfo>::iterator it = pvctMenuLst->begin();
    int i = 0;
    while ( it != pvctMenuLst->end() )
    {  
        String txt = it->strTxt;  


        String strClickItemFunc = it->strItemFunc; 
        Data_Menu data(*it); 
        
        arg.strImageItem = it->strImageItem;
        arg.strTxtItem = it->strTxtItem;  
        arg.nKey = i++;
        arg.strTxt = txt;
        data.SetDataKey( arg.nKey );
        arg.pUserData = &data; 
        arg.strClickItemFunc = strClickItemFunc;
        arg.pVctSubItem = it->m_pVctSubItem;
        MakeItem(arg);
        it++;
    }
	return true;
}

//地址簿
bool CTouchListHelp::TransData( IItemList* pList, Value_TouchListAddr& valAddr )
{
	IBaseItem* pBaseItem = pList->GetItemData();
	pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert );
    pBaseItem->SetMoveStatus(true);

    ARRAY<TAddrItem>* pArray = valAddr.m_pAddrList;
	//排序
	if ( valAddr.m_bSort )
	{
		sort( pArray->begin(), pArray->end(), CTransparentAddrList::AddrItemCompare );
	}
	
	for ( int i = 0; i < pArray->size(); i++ )
	{
		TAddrItem tAddrItem = pArray->at(i); 
		Data_AddrItemInfo itemInfo(tAddrItem);
		if ( tAddrItem.emItemType == emEntryItem )
		{
			itemInfo.SetDataKey( tAddrItem.tAddrInfo.dwEntryIdx );		
		}
		else
		{
			itemInfo.SetDataKey( tAddrItem.tGroupInfo.dwGroupIdx + MAX_ADDRENTRY ); //防止跟EntryItem一样
		}
		
		IBaseItem* pItem = CItemFactory::GetSingletonPtr()->CreateItem( strItemAddrList ) ;
		if ( CListItem* pImageItem = dynamic_cast<CListItem*>(pItem) )
		{
			if ( tAddrItem.emItemType == emEntryItem )
			{
				pItem->SetLayoutAlgorithm( IAlgorithm::strNormalItem );
			}
			else
			{
				pItem->SetLayoutAlgorithm( IAlgorithm::strAddrGroupItem );
			}
		
			pItem->SetDragStatus(true);
			pItem->SetFunc( valAddr.m_strItemFunc );
			pItem->SetUserData( &itemInfo );
		}	
		
		IItemList *pNew = pList->AddItem( i, pItem, emGroup );
		delete pItem;
		pItem = NULL;

		int nIndex = 0;
		if ( tAddrItem.emItemType == emEntryItem )
		{
			IBaseItem *pSubItem = NULL;
            if ( strcmp( tAddrItem.tAddrInfo.achEntryName, "" ) != 0 && strcmp( tAddrItem.tAddrInfo.achE164, "" ) != 0  )
            {
                pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "ExTextItem" );
                if ( CExTextItem* pTextItem = dynamic_cast<CExTextItem*>(pSubItem) )
                {
                    pTextItem->SetText( tAddrItem.tAddrInfo.achEntryName );
                    pTextItem->SetSecondText( tAddrItem.tAddrInfo.achE164 );
                    
                    //Sip会场蓝色显示
                    if ( tAddrItem.tAddrInfo.m_emEndpointType == emTPEndpointTypeCNS )
                    {
                        pTextItem->SetFontColor( Color(14, 125, 239) );
                        pTextItem->SetSelColor( Color(255, 255, 255) );
                    }
			    }
            }
            else
            {
                pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "TextItem" );
                if ( CTextItem* pTextItem = dynamic_cast<CTextItem*>(pSubItem) )
                {
                    if ( strcmp( tAddrItem.tAddrInfo.achEntryName, "" ) != 0 )
                    {
                        pTextItem->SetText( tAddrItem.tAddrInfo.achEntryName );
                    }
                    else
                    {
                        pTextItem->SetText( tAddrItem.tAddrInfo.achE164 );

                        pTextItem->SetFontColor( Color(108, 124, 148) );
                        pTextItem->SetSelColor( Color(255, 255, 255) );
                    }
                    
                    //Sip会场蓝色显示
                    if ( tAddrItem.tAddrInfo.m_emEndpointType == emTPEndpointTypeCNS )
                    {
                        pTextItem->SetFontColor( Color(14, 125, 239) );
                        pTextItem->SetSelColor( Color(255, 255, 255) );
                    }   
			    }
            }    
            		
			pNew->AddItem( 0, pSubItem, emGroup );
			nIndex = 1;
            if( pSubItem != NULL )
            {
			    delete pSubItem;
			    pSubItem = NULL;
            }
		}
		else
		{
			IBaseItem * pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "GroupNameItem" );
			if ( CTextItem* pNameItem = dynamic_cast<CTextItem*>(pSubItem) )
			{
				pNameItem->SetText( tAddrItem.tGroupInfo.achGroupName );
			}
			pNew->AddItem( 0, pSubItem, emGroup );
			delete pSubItem;
			pSubItem = NULL;

			pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "GroupNumItem" );
			if ( CTextItem* pNumItem = dynamic_cast<CTextItem*>(pSubItem) )
			{
				CString strNum;
				strNum.Format( "(%d)", tAddrItem.tGroupInfo.nEntryNum + tAddrItem.tGroupInfo.nDownGroupNum );
				pNumItem->SetText( (LPCTSTR)(strNum) );
			}			
			pNew->AddItem( 1, pSubItem, emGroup );
			delete pSubItem;
			pSubItem = NULL;

			pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "ImageItemAddrGroup" );
			pNew->AddItem( 2, pSubItem, emGroup );
            nIndex = 3;
			delete pSubItem;
			pSubItem = NULL;
		}

		if ( !tAddrItem.strImg.IsEmpty() )
		{
			IBaseItem *pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( (LPCTSTR)tAddrItem.strImg );
			if ( pSubItem != NULL )
			{
				pNew->AddItem( nIndex++, pSubItem, emGroup );
				delete pSubItem;
				pSubItem = NULL;
			}	
		}		
		
		if ( valAddr.m_pSubItem != NULL )
		{
			ARRAY<String>::iterator it = valAddr.m_pSubItem->begin();

			while ( it != valAddr.m_pSubItem->end() )
			{   
				IBaseItem *pSubItem= CItemFactory::GetSingletonPtr()->CreateItem( *it ); 
				if ( pSubItem != NULL )
				{
					pNew->AddItem( nIndex++, pSubItem, emGroup );
					delete pSubItem;
					pSubItem = NULL;
				}				
				it++;
			}
		}

        if ( !valAddr.m_bGlobalAddr && (tAddrItem.emItemType == emEntryItem) )
        {
            if ( tAddrItem.tAddrInfo.bOnLine )
            {
                IBaseItem *pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "AddrOnlineItem" );
                if ( pSubItem != NULL )
                {
                    pNew->AddItem( nIndex++, pSubItem, emGroup );
                    delete pSubItem;
                    pSubItem = NULL;
			    }
            }
            else
            {
                IBaseItem *pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "AddrOfflineItem" );
                if ( pSubItem != NULL )
                {
                    pNew->AddItem( nIndex++, pSubItem, emGroup );
                    delete pSubItem;
                    pSubItem = NULL;
			    }
            }
        }
	}
	return true;
}


//登录时的cns会场列表
bool CTouchListHelp::TransData( IItemList* pList, TTPCnList* ptCnList, String strItemFunc )
{
	IBaseItem* pBaseItem = pList->GetItemData();
	pBaseItem->SetLayoutAlgorithm( IAlgorithm::strHori );
    pBaseItem->SetMoveStatus( false );
	
	int nNum = ptCnList->wNum;
	int nPage = 0;
	if ( nNum > 0 )
	{
		nPage = ( nNum - 1 ) / MAX_PAGE_COUNT + 1;
	}
	if ( nPage > 1 )
	{
		pBaseItem->SetMoveStatus( true );
	}
	for ( int nCount = 0; nCount < nPage; nCount++ )
	{
		IBaseItem* pItem = CItemFactory::GetSingletonPtr()->CreateItem( "BlankPageItem" ) ;
		if ( CImageItem* pImageItem = dynamic_cast<CImageItem*>(pItem) )
		{
			pItem->SetLayoutAlgorithm( IAlgorithm::strDoubleColumn );
		}		
		IItemList *pFirst = pList->AddItem( nCount, pItem, emGroup );
		delete pItem;
		pItem = 0;

		for ( int i = 0; i < MAX_PAGE_COUNT; i++ )
		{
			int nRealNum = nCount * MAX_PAGE_COUNT + i;
			if ( nRealNum >= nNum )
			{
				break;
			}
			TTPCn tCn = ptCnList->tCn[nRealNum];
			
			Data_TPCnInfo CnInfo(tCn);
			CnInfo.SetDataKey( tCn.byInsId );

			IBaseItem *pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "ConnectCnsItem" );
			if ( CImageItem* pTextItem = dynamic_cast<CImageItem*>(pSubItem) )
			{
				pSubItem->SetLayoutAlgorithm( IAlgorithm::strTextOnly );
				pSubItem->SetFunc( strItemFunc );
				pSubItem->SetUserData( &CnInfo );
			}
			
			IItemList* pSecond = pFirst->AddItem( i, pSubItem, emGroup );
			delete pSubItem;
			pSubItem = 0;

			IBaseItem* pSubSubItem= CItemFactory::GetSingletonPtr()->CreateItem( "TextItemSuperWhite" ) ;
			if ( CTextItem * pTextItem = dynamic_cast<CTextItem*>(pSubSubItem)  )
			{
				pTextItem->SetText( tCn.achName ); 
			}   
			pSecond->AddItem( 0, pSubSubItem, emGroup );
			
			delete pSubSubItem;
			pSubSubItem = 0; 
		}
	}
	
	return true;
}


//CNS连接的会场列表
bool CTouchListHelp::TransData( IItemList* pList, ARRAY<TTPCnsInfo>* pArray, String strItemFunc, ARRAY<String>* pSubItem )
{
	IBaseItem* pBaseItem = pList->GetItemData();
	pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert );
    pBaseItem->SetMoveStatus(true);

	sort( pArray->begin(), pArray->end(), CTransparentAddrList::TPCnsInfoCompare );

    Args_MakeItem arg;
    arg.pList = pList;
    arg.bDrag = FALSE; 
    arg.strClickItemFunc = strItemFunc;
    arg.pVctSubItem = pSubItem;
    arg.strImageItem = "TempListItem";

	ARRAY<TTPCnsInfo>::iterator it = pArray->begin();
    int i = 0;
    while ( it != pArray->end() )
    {  
		TTPCnsInfo* pCnsInfo = it; 
		Data_TPCnsInfo CnsInfo(pCnsInfo);
        String txt = pCnsInfo->m_achRoomName; 

        arg.nKey = i++;
        arg.strTxt = txt;
        arg.pUserData = &CnsInfo;
        MakeItem(arg);
        it++;
    }
	return true;
}


//用户列表 
bool CTouchListHelp::TransData( IItemList* pList,Value_TouchListUser &val)
{
    if ( pList == NULL || val.m_pTplArryUser == NULL )
    {
        return false;
    }

    IBaseItem* pBaseItem = pList->GetItemData();
    pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert );
    pBaseItem->SetMoveStatus(true);  
     
    Args_MakeItem arg;
    arg.pList = pList;
    arg.bDrag = FALSE;
    arg.strClickItemFunc = val.m_strClickItemFunc; 
    arg.pVctSubItem = val.m_pVctSubItem ;
    arg.strImageItem = "TempListItem";
    arg.strTxtItem = "TextItem";
    
    int count =  val.m_pTplArryUser->Size();
    vector<CUserFullInfo> vctList;
    for ( int i = 0; i < count; i++ )
    {
        vctList.push_back( val.m_pTplArryUser->GetAt(i) );
    }
    
	sort( vctList.begin(), vctList.end(), CTransparentAddrList::UserItemCompare );


    
    for ( int k = 0; k< count; k++ )
    {
        CUserFullInfo user = vctList[k];
        Data_User data(  user );
         
        String txt = user.GetName();  

        if ( txt == "admin")
        {//管理员不显示在列表中
            continue;
        }

        arg.strTxt = txt;
        arg.nKey = k; 
        arg.pUserData = &data;  
        MakeItem( arg );
    }
 
	return true;
}



//告警
bool CTouchListHelp::TransData( IItemList* pList, ARRAY<String>* pArray )
{
	IBaseItem* pBaseItem = pList->GetItemData();
	pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert );
    pBaseItem->SetMoveStatus(true);

	for ( int i = 0; i < pArray->size(); i++ )
	{
		String strStr = pArray->at(i);
		String strItemType;
		strItemType = "AutoHeightItem";

		int nSize = strStr.size();		
		
		IBaseItem* pItem = CItemFactory::GetSingletonPtr()->CreateItem( strItemType );
		if ( CListItem* pListItem = dynamic_cast<CListItem*>(pItem) )
		{
			pItem->SetLayoutAlgorithm( IAlgorithm::strTextOnly );		
			pItem->SetDragStatus(false);

			if ( nSize <= 36 )
			{
				pListItem->SetItemHeight( 44 );
			}
			else if ( nSize > 72 )
			{
				pListItem->SetItemHeight( 90 );
			}
			else
			{
				pListItem->SetItemHeight( 60 );
			}		
		}	
		
		IItemList *pNew = pList->AddItem( i, pItem, emGroup );
		delete pItem;
		pItem = NULL;

		IBaseItem *pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "TextItemNoSel" );
		if ( CTextItem* pTextItem = dynamic_cast<CTextItem*>(pSubItem) )
		{
			pTextItem->SetText( strStr );
		}
		
		pNew->AddItem( 0, pSubItem, emGroup );
		delete pSubItem;
		pSubItem = NULL;
	}
	return true;
}


bool CTouchListHelp::TransData( IItemList* pList, ARRAY<TConfMenuInfo>* pArray )
{   
    IBaseItem* pBaseItem = pList->GetItemData();
    pBaseItem->SetLayoutAlgorithm( IAlgorithm::strHori );
    pBaseItem->SetMoveStatus(true);

	vector<TConfMenuInfo> vctMenu;
    for ( int j = 0; j < pArray->size(); j++ )
    {
		TConfMenuInfo tInfo = pArray->at(j);
		if ( !tInfo.bShow || !tInfo.bSetShow )
		{
			continue;
		}
        vctMenu.push_back( tInfo );
    }
    
    sort( vctMenu.begin(), vctMenu.end(), CTransparentAddrList::ConfMenuCompare ); 

    int nNum = vctMenu.size();
    int nPage = 0;
    if ( nNum > 0 )
    {
        nPage = ( nNum - 1 ) / 6 + 1;
    }
    
    for ( int nCount = 0; nCount < nPage; nCount++ )
    {
        IBaseItem* pItem = CItemFactory::GetSingletonPtr()->CreateItem( "ConfMenuPageItem" );
        if ( CImageItem* pImageItem = dynamic_cast<CImageItem*>(pItem) )
        {
            pItem->SetLayoutAlgorithm( IAlgorithm::strHori );
        }		
        IItemList *pFirst = pList->AddItem( nCount, pItem, emGroup );
        delete pItem;
        pItem = 0;
        
        for ( int i = 0; i < 6; i++ )
        {
            int nRealNum = nCount * 6 + i;
            if ( nRealNum >= nNum )
            {
                break;
            }
            TConfMenuInfo tInfo = vctMenu.at(nRealNum);

			if ( !tInfo.bShow || !tInfo.bSetShow )
			{
				continue;
			}
            
            IBaseItem *pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( (LPCTSTR)tInfo.strItemType );
			if ( pSubItem != NULL )
			{
				pSubItem->SetImageFolder( (LPCTSTR)tInfo.strImgFolder );
				pSubItem->SetFunc( (LPCTSTR)tInfo.strItemFunc );

				Data_ConfMenu data( tInfo );
				data.SetDataKey( tInfo.nIndex );
				pSubItem->SetUserData( &data );

				pFirst->AddItem( i, pSubItem, emGroup );
				delete pSubItem;
				pSubItem = 0;
			}
        }
    }
    
	return true;
  
}

bool CTouchListHelp::TransData( IItemList* pList, Value_VerListConfMenu &val) 
{
    if ( pList == NULL || val.m_pConfMenuLst == NULL )
    {
        return false;
    }
    
    IBaseItem* pBaseItem = pList->GetItemData();
    pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert );
    pBaseItem->SetMoveStatus(true);  
    
    Args_MakeItem arg;
    arg.pList = pList;
    arg.bDrag = FALSE;
    arg.strClickItemFunc = val.m_strClickItemFunc; 
    arg.pVctSubItem = val.m_pVctSubItem ;
    arg.strImageItem = "TempListItem";
    arg.strTxtItem = "TextItem";
    
    int count =  val.m_pConfMenuLst->size(); 
    
    sort( val.m_pConfMenuLst->begin(), val.m_pConfMenuLst->end(), CTransparentAddrList::ConfMenuCompare ); 
    
    vector<TConfMenuInfo>::iterator it  = val.m_pConfMenuLst->begin();
    int i = 0;
    while( it != val.m_pConfMenuLst->end() )
    {
        TConfMenuInfo menu = *it;
        Data_ConfMenu data(  menu );
        data.SetDataKey(menu.nIndex );
        
        String txt = menu.strName;  
        
        arg.strTxt = txt;
        arg.nKey = i++; 
        arg.pUserData = &data; 

        vector<String> vct;
        String img;
        vct.clear();
        if ( !menu.bSetShow )
        {   
            img = "ImageItemHide";
            vct.push_back(img);

            arg.pVctSubItem = &vct;
        }
        else
        {
            arg.pVctSubItem = NULL;
        }
        MakeItem( arg );
        it++;
        
    }
    
	return true;
}


bool CTouchListHelp::TransData( IItemList* pList, Value_ListDualSrc &val )
{
    IBaseItem* pBaseItem = pList->GetItemData();
    pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert );
    pBaseItem->SetMoveStatus(true);

    for ( int i = 0; i < val.m_tSrcInfo.vctVgaInfo.size(); i++ )
    {
        TVgaInfo tVgaInfo = val.m_tSrcInfo.vctVgaInfo.at(i); 
        Data_DualSrc itemInfo(tVgaInfo);
        itemInfo.SetDataKey( tVgaInfo.m_emVgaType );

        IBaseItem* pItem = CItemFactory::GetSingletonPtr()->CreateItem( "TempListItem" ) ;
        if ( CListItem* pImageItem = dynamic_cast<CListItem*>(pItem) )
		{
            pItem->SetLayoutAlgorithm( IAlgorithm::strNormalItem );        
            pItem->SetFunc( val.m_strClickItemFunc );
			pItem->SetUserData( &itemInfo );
        }

        IItemList *pNew = pList->AddItem( i, pItem, emGroup );
		delete pItem;
		pItem = NULL;

        //条目中添加一个字符串 
        IBaseItem* pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "TextItem" );
        if ( CTextItem * pTextItem = dynamic_cast<CTextItem*>(pSubItem)  )
        {
            pTextItem->SetText( tVgaInfo.m_achAlias );          
        }   
        pNew->AddItem( 0, pSubItem, emGroup );
        delete pSubItem;
        pSubItem = NULL; 

        if ( val.m_bConfig )
        {
            pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "ImageItemSysCfg" );
            if ( pSubItem != NULL )
            {
                pNew->AddItem( 1, pSubItem, emGroup );
                delete pSubItem;
                pSubItem = NULL;
            }

            //默认视频源
            if ( tVgaInfo.m_emVgaType == val.m_tSrcInfo.emDefaultType )
            {
                pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "GrayTextItem" );
                if ( CTextItem * pTextItem = dynamic_cast<CTextItem*>(pSubItem)  )
                {
                    pTextItem->SetText( "已设为默认" );
                    pNew->AddItem( 2, pSubItem, emGroup );
                    delete pSubItem;
                    pSubItem = NULL;
                }
            }
        }
        else
        {
            if ( tVgaInfo.m_emVgaType == val.m_tSrcInfo.emCurrentType )
            {
                pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "ImageItemSelected" );
                if ( pSubItem != NULL )
                {
                    pNew->AddItem( 1, pSubItem, emGroup );
                    delete pSubItem;
                    pSubItem = NULL;
                }
            }
        }

    }

    return true;
}


bool Value_ListNetManage::SetData( IItemList* pList )
{
    IBaseItem* pBaseItem = pList->GetItemData();
    pBaseItem->SetLayoutAlgorithm( IAlgorithm::strVert );
    pBaseItem->SetMoveStatus(true);
	
    for ( int i = 0; i < m_pvctNetList->size(); i++ )
    {
        TTPNMServerCfg tNMServerCfg = m_pvctNetList->at(i); 
        Data_NetManage itemInfo( tNMServerCfg );
        itemInfo.SetDataKey( i );
		
        IBaseItem* pItem = CItemFactory::GetSingletonPtr()->CreateItem( "TempListItem" ) ;
        if ( CListItem* pImageItem = dynamic_cast<CListItem*>(pItem) )
		{
            pItem->SetLayoutAlgorithm( IAlgorithm::strNormalItem );        
            pItem->SetFunc( m_strClickItemFunc );
			pItem->SetUserData( &itemInfo );
        }
		
        IItemList *pNew = pList->AddItem( i, pItem, emGroup );
		delete pItem;
		pItem = NULL;
		
        //条目中添加一个字符串
		IBaseItem* pSubItem =  CItemFactory::GetSingletonPtr()->CreateItem( "TextItem" );
		if ( CTextItem * pTextItem = dynamic_cast<CTextItem*>(pSubItem)  )
        {	
			CString strSerName;
			strSerName.Format("网管服务器0%d",tNMServerCfg.wNMServerNO+1);
            pTextItem->SetText((String)strSerName);          
        } 
		pNew->AddItem( 0, pSubItem, emGroup );
        delete pSubItem;
        pSubItem = NULL; 
		pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "ImageItemSysCfg" );
		if ( pSubItem != NULL )
		{
			pNew->AddItem( 1, pSubItem, emGroup );
			delete pSubItem;
			pSubItem = NULL;
        }	
    }
	
    return true;
}
 
bool CTouchListHelp::SetData( IItemList* pList, const IValue* pValue )
{
	if ( pList == 0 || pValue == 0 )
	{
		return false;
    } 

 //	return CTouchListHelp::TransData( pList, pValue);
    
    pList->DeleteAllItem(); 
    String strType = pValue->GetType(); 
   
    //会议模板列表
	if ( strType == CTouchListHelp::strConfTemplate )
    {     
		if ( Value_TouchListConfTemp* pConfTempValue = dynamic_cast<Value_TouchListConfTemp*>(const_cast<IValue*>(pValue) ) )
		{
			if ( pConfTempValue != 0 )
            {                
				return CTouchListHelp::TransData( pList, *pConfTempValue );
			}
		}
	}

    /*//模板中的cns列表
    if ( strType == CTouchListHelp::strTempCns)
    {
        if ( Value_TouchListTempCns* pConfTempValue = dynamic_cast<Value_TouchListTempCns*>(const_cast<IValue*>(pValue) ) ) 
        {
            if ( pConfTempValue != 0 )
            {
                  return CTouchListHelp::TransData( pList, *pConfTempValue  ); 
            }
		}
    }

    //模板中轮询列
    if ( strType == CTouchListHelp::strItemTempPoll )
    {
        if ( Value_TouchListTempPoll* pTempPollValue = dynamic_cast<Value_TouchListTempPoll*>(const_cast<IValue*>(pValue) ) )
        {
            if ( pTempPollValue != NULL )
            {
                return CTouchListHelp::TransData( pList, pTempPollValue->m_tTemp, pTempPollValue->m_strClickItemFunc,
                    pTempPollValue->m_pVctSubItem, pTempPollValue->m_bDrag );
            }
        }
    }*/

    //地址簿
	if ( strType == CTouchListHelp::strListAddr )
	{
		if ( Value_TouchListAddr* pAddrValue = dynamic_cast<Value_TouchListAddr*>( const_cast<IValue*>(pValue) ) )
		{
			if ( pAddrValue != NULL )
			{
				return CTouchListHelp::TransData( pList, *pAddrValue );
			}
		}
	}

    //strListMenu
    if ( strType == CTouchListHelp::strListMenu )
    {
        if ( const Value_TouchListMenu* pVa = dynamic_cast<const Value_TouchListMenu*>( pValue ) )
        {
            if ( pVa != NULL )
            {
                return CTouchListHelp::TransData( pList, pVa->m_pMenuLst, pVa->m_bDrag );
            }
        }
    }

    //会议中cns列
    if ( strType == CTouchListHelp::strConfCns )
    {
        if ( const Value_TouchListConfInfo* pVa = dynamic_cast<const Value_TouchListConfInfo*>( pValue ) )
        {
            if ( pVa != NULL )
            {   
                Value_TouchListConfInfo cnsLst = *const_cast<Value_TouchListConfInfo*>(pVa);
                return CTouchListHelp::TransData( pList, cnsLst );
            }
        }
    }

    // 会议列表
    if ( strType == CTouchListHelp::strConfLst )
    {
        if ( const Value_TouchListConf* pVa = dynamic_cast<const Value_TouchListConf*>( pValue ) )
        {
            if ( pVa != NULL )
            {   
                Value_TouchListConf  Lst = *const_cast<Value_TouchListConf*>(pVa);
                return CTouchListHelp::TransData( pList, Lst);
            }
        }
    }
    
	if ( strType == CTouchListHelp::strListCnsList )
	{
		if ( Value_TouchListCnsList* pVa = dynamic_cast<Value_TouchListCnsList*>( const_cast<IValue*>(pValue) ) )
        {
            if ( pVa != NULL )
            {   
				return CTouchListHelp::TransData( pList, pVa->m_pCnsList, pVa->m_strItemFunc, pVa->m_pSubItem );
            }
        }
	}
 
    // 用户列表
    if ( strType == CTouchListHelp::strListUser )
    {
        if ( const Value_TouchListUser* pVa = dynamic_cast<const Value_TouchListUser*>( pValue ) )
        {
            if ( pVa != NULL )
            {   
                Value_TouchListUser  Lst = *const_cast<Value_TouchListUser*>(pVa);
                return CTouchListHelp::TransData( pList, Lst);
            }
        }
    }
    
	//告警信息
	if( strType == CTouchListHelp::strListAlarm )
	{
		if ( const Value_TouchListAlarm* pVa = dynamic_cast<const Value_TouchListAlarm*>( pValue ) )
		{
			if ( pVa != NULL )
			{
				return CTouchListHelp::TransData( pList, pVa->m_pAlarmList );
			}
		}
	}

	if ( strType == CTouchListHelp::strListConnectCn )
	{
		if ( const Value_ListConnectCns* pVa = dynamic_cast<const Value_ListConnectCns*>( pValue ) )
		{
			if ( pVa != NULL )
			{
				return CTouchListHelp::TransData( pList, pVa->m_ptCnList, pVa->m_strItemFunc );
			}
		}
	}

    //会议中操作菜单栏
	if ( strType == CTouchListHelp::strListConfMenu )
	{
		if ( const Value_HoriListConfMenu* pVa = dynamic_cast<const Value_HoriListConfMenu*>( pValue ) )
		{
			if ( pVa != NULL )
			{
				return CTouchListHelp::TransData( pList, pVa->m_pMenuList );
			}
		}
	}

    if ( strType == CTouchListHelp::strVerListConfMenu  )
    {
        if ( const Value_VerListConfMenu* pVa = dynamic_cast<const Value_VerListConfMenu*>( pValue ) )
        {
            if ( pVa != NULL )
            {
                Value_VerListConfMenu  Lst = *const_cast<Value_VerListConfMenu*>(pVa);
                return CTouchListHelp::TransData( pList, Lst );
            }
		}
    }

    if ( strType == CTouchListHelp::strListDualSrc )
    {
        if ( const Value_ListDualSrc* pVa = dynamic_cast<const Value_ListDualSrc*>( pValue ) )
        {
            if ( pVa != NULL )
            {
                Value_ListDualSrc vLst = *const_cast<Value_ListDualSrc*>(pVa);
                return CTouchListHelp::TransData( pList, vLst );
            }
		}
    }
    
	return true;
}


bool CTouchListHelp::MakeItem(  Args_MakeItem &agrs )
{    
    
    IBaseItem* pItem = CItemFactory::GetSingletonPtr()->CreateItem( agrs.strImageItem ) ;
    //if ( CListItem* pImageItem = dynamic_cast<CListItem*>(pItem) )
    //{
        pItem->SetLayoutAlgorithm( agrs.strLayoutAlgorithm ); 
		pItem->SetDragStatus(agrs.bDrag); 
        pItem->SetUserData(agrs.pUserData); 
        //点击条目后 
        if ( ! agrs.strClickItemFunc.empty() )
        {
            pItem->SetFunc( agrs.strClickItemFunc );
        } 
        

        pItem->SetItemStatus( agrs.emItemStatus );
        IItemList *pNew  = agrs.pList->ModifyItem( agrs.nKey, pItem );  //添加 一个条目
    //}	  
    delete pItem;
    pItem = 0;
    
    //条目中添加一个字符串 
    IBaseItem* pSubItem= CItemFactory::GetSingletonPtr()->CreateItem( agrs.strTxtItem ) ;
    if ( CTextItem * pTextItem = dynamic_cast<CTextItem*>(pSubItem)  )
    {
        pTextItem->SetText( agrs.strTxt ); 
        pNew->ModifyItem(0,pSubItem );
    }   
    delete pSubItem;
    pSubItem = 0; 
    
    // 添加 图标
    if ( agrs.pVctSubItem == NULL || agrs.strTxt.empty())
    { 
        return true;
    }

    ARRAY<String>::iterator it = agrs.pVctSubItem->begin();
    int i = 1;
    while ( it != agrs.pVctSubItem->end() )
    {   
        pSubItem= CItemFactory::GetSingletonPtr()->CreateItem( *it ) ; 
        pNew->ModifyItem(i++,pSubItem ); 
        delete pSubItem;
        pSubItem = 0;
        it++;
    }
    
    return true;
}