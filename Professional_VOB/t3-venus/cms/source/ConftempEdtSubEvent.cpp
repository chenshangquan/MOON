// ConftempEdtLogic.cpp: implementation of the CConftempEdtLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "ConftempEdtLogic.h"
#include "TouchListProperty.h"
#include "msgBoxLogic.h"
#include "PropertyHelp.h"
#include "pollLstManage.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
 
//�������ģ����б��ĳ����Ŀ
bool CConftempEdtLogic::OnTempItemClick( const IArgs & arg   )
{    
    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&arg) )
    {
        const IData *pIdata = pClickInfo->m_pClickList->GetItemData()->GetUserData();
        if ( const Data_ConfTemp *pDataTemp = dynamic_cast<const Data_ConfTemp *>(pIdata) )
        {
            m_tConfTempSel = pDataTemp->m_tCmsConfTemp ;

            UIManagePtr->LoadScheme( "SchmDisable", m_pWndTree, m_strBtnEdit );
            SetTempSubList();
            UpdateTempInfoDlg();
        }
    }
    
    return true;
}

//�������ģ����б� ��Ŀ�е�ɾ��ͼ��
bool CConftempEdtLogic::OnTempLstDelIcon( const IArgs & arg  )
{
    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&arg) )
    {
        const IData *pIData = pClickInfo->m_pClickList->GetParentItem()->GetItemData()->GetUserData();
        if ( const Data_ConfTemp *pConfTempData = dynamic_cast<const Data_ConfTemp *>(pIData) )
        {
            m_tConfTempSel = pConfTempData->m_tCmsConfTemp  ; 
            Args_MsgBox arg;
            arg.pOwnerWnd = pClickInfo->m_pSrcWnd; 
            MSG_BOX("�Ƿ�ɾ����ѡ����ģ��",CConftempEdtLogic::DelSelConfTemp,NULL,
                m_pLogic, CConftempEdtLogic ,&arg,TRUE);
        }
    } 
    return true;
}

//ɾ����ѡ����ģ�壬
bool CConftempEdtLogic::DelSelConfTemp( const IArgs & arg  )
{
    u16 wRe = BusinessManagePtr->DeleteConfTemplate( m_tConfTempSel.m_wID );
    if ( wRe != NO_ERROR )
    {
       // HANDLE_ERROR(wRe);
        CString strErr = GET_ERR_STRING( wRe );
        Args_MsgBox argMsg;
        argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr(  m_strDlgConfInfo,m_pWndTree  );
        MSG_BOX_PROMPT( strErr,&argMsg );
    }
    return true;
}



/**	 
* ����: ɾ���ֻ᳡�б��еġ�ɾ��ͼ�ꡱ 
* @return  bool
* @remarks  ɾ����ѡ�ֻ᳡ 
*/
bool CConftempEdtLogic::OnCnsLstDelIcon( const IArgs & arg  )
{    
    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();        
        if ( const Data_CnsAddr *pItemInfo = dynamic_cast<const Data_CnsAddr*>( pBaseItem->GetUserData() )) 
        {   
            u16 wRe = m_tConfTempSel.DeletConfEp(pItemInfo->m_tEpAddr.m_wEpID);
            if ( wRe != NO_ERROR)
            {
               // HANDLE_ERROR(wRe);
                CString strErr = GET_ERR_STRING( wRe );
                Args_MsgBox argMsg;
                argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr(  m_strDlgConfInfo,m_pWndTree  );
                MSG_BOX_PROMPT( strErr,&argMsg );
                return false;
            }
          UpdateTempInfoDlg();
             
        } 
    }
    return true;
}

 

        

/**	 
* ����: ����˵�ַ���еġ����ͼ�ꡱ
* @return  bool
* @remarks  �ѵ�ַ����ѡ�����Ŀ��ӵ��᳡�б���
*/
bool CConftempEdtLogic::OnAddrAddIcon( const IArgs & arg  )
{   
    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();
        
        if ( const Data_AddrItemInfo *pItemInfo = dynamic_cast<const Data_AddrItemInfo*>( pBaseItem->GetUserData() )) 
        {
           TAddrItem tAddrItem = pItemInfo->m_tAddrItem;
           if ( tAddrItem.emItemType != emEntryItem )
           {
               return false;
           }
           TAddrInfo tAddrInfo = tAddrItem.tAddrInfo;
           u16 wRe = m_tConfTempSel.AddConfEp(tp_Alias_h323,tAddrInfo.achEntryName);
           if ( wRe != NO_ERROR) 
           {
               if (  wRe == ERR_CMS_CNS_MAX_NUM )  
               {
                   //HANDLE_ERROR( wRe );
                   CString strErr = GET_ERR_STRING( wRe );
                   Args_MsgBox argMsg;
                   argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr(  m_strDlgConfInfo,m_pWndTree  );
                   MSG_BOX_PROMPT( strErr,&argMsg ); 
               }
               
               return false;
           }
           UpdateTempInfoDlg(); 

           //�� ��ǰ���������Ϊѡ����
           Value_TransparentBaseListSelItem val;
           int nIndex = m_tConfTempSel.m_atEpList.m_wNum - 1;
           val.dwDataKey = m_tConfTempSel.m_atEpList.m_tCnsList[nIndex].m_wEpID;
           UIManagePtr->SetPropertyValue( val, m_strLstSecondaryCns, m_pWndTree );
        }

    } 
    return true;
}


/**	 
* ����: ����˵�ַ�������еġ����ͼ�ꡱ
* @return  bool
* @remarks  �ѵ�ַ���з�����ѡ��ķ�����ӵ��᳡�б���
*/
bool CConftempEdtLogic::OnAddGrpAddIcon( const IArgs & arg  )
{
    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();
        
        if ( const Data_AddrItemInfo *pItemInfo = dynamic_cast<const Data_AddrItemInfo*>( pBaseItem->GetUserData() )) 
        {
            TAddrItem tAddrItem = pItemInfo->m_tAddrItem;
            if ( tAddrItem.emItemType != emGroupItem )
            {
                return false;
            }
            //�ѵ�ַ�������е���Ŀ����ӵ��б���
            AddAddrToConfTempEpLst( &tAddrItem ); 
            UpdateTempInfoDlg(); 
        }
    }
    return true;
}


/**	 
* ����: �����cns�ġ����ͼ�ꡱ
* @return  bool
* @remarks  ��cns�б���ѡ���cns��ӵ���ѯ�б���
*/
bool CConftempEdtLogic::OnCnsLstAddICon( const IArgs & arg  )
{
    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast< const Args_ClickItemInfo*>(&arg))
    {
        u16 wSelCnsId = -1;
        IBaseItem* pBaseItem = pClickInfo->m_pClickList->GetParentItem()->GetItemData();        
        if ( const Data_CnsAddr *pData = dynamic_cast<const Data_CnsAddr*>( pBaseItem->GetUserData() )) 
        {  
           wSelCnsId = pData->m_tEpAddr.m_wEpID;
           u16 wRe = m_tConfTempSel.AddPollCns( wSelCnsId );
           if ( wRe != NO_ERROR )
           {
              // HANDLE_ERROR(wRe);
               CString strErr = GET_ERR_STRING( wRe );
               Args_MsgBox argMsg;
               argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr(  m_strDlgConfInfo,m_pWndTree  );
               MSG_BOX_PROMPT( strErr,&argMsg );
               return false;
           }
            
            UpdateTempInfoDlg();

           //�� ��ǰ���������Ϊѡ����
            Value_TransparentBaseListSelItem val;
            val.dwDataKey = wSelCnsId;
            UIManagePtr->SetPropertyValue( val, m_strLstPollCns, m_pWndTree );
 

            
        }
    }
    return true;
}


 


 

//�ӵ�ַ��/��ַ��������ק����
bool CConftempEdtLogic::OnEndDragSecdryCns( const IArgs & arg  )
{
    Args_WindowMsg WinMsg = *dynamic_cast<const Args_WindowMsg*>(&arg);
    WindowMsg msg = WinMsg.m_Msg; 
    Window* pWnd = UIManagePtr->GetWindowPtr( m_strLstSecondaryCns, m_pWndTree );
    if ( !pWnd->IsWindowVisible()|| !pWnd->IsWindowEnabled() )
    {
        return false;
    }

    if ( Data_AddrItemInfo *pItemInfo =  dynamic_cast<Data_AddrItemInfo*>( (IData*)msg.wParam ))
    {
        TAddrItem tAddrItem = pItemInfo->m_tAddrItem;
        bool re = AddAddrToConfTempEpLst(&tAddrItem);
        if ( re )
        {
            //ˢ��cns�ֻ᳡�б� 
            UpdateTempInfoDlg();
        } 
    } 
	 
   return true;
}

//����ѯ�б� ��ק��Ŀ����
bool CConftempEdtLogic::OnEndDragPollLst( const IArgs & arg  )
{
    Args_WindowMsg WinMsg = *dynamic_cast<const Args_WindowMsg*>(&arg);
    WindowMsg msg = WinMsg.m_Msg; 
    Window* pWnd = UIManagePtr->GetWindowPtr( m_strLstPollCns, m_pWndTree );
    if ( !pWnd->IsWindowVisible()|| !pWnd->IsWindowEnabled() )
    {
        return false;
    }
    
    if ( Data_CnsAddr *pData =  dynamic_cast<Data_CnsAddr*>( (IData*) msg.wParam ))
    {
        if ( pData->m_tEpAddr.m_wEpID == INVALID_WORD )
        {
            return false;
        }
        
        u16 wNum = m_tConfTempSel.m_tTurnList.m_wNum  ;
        m_tConfTempSel.m_tTurnList.m_wNum++;
        m_tConfTempSel.m_tTurnList.m_awList[wNum] = pData->m_tEpAddr.m_wEpID;
        
        UpdateTempInfoDlg();
    }
    return true;
}
 
//�� ��ѯ�б� ��ק��Ŀ����
bool CConftempEdtLogic::OnEndDragFrmPollLst( const IArgs & arg  )
{
    Args_WindowMsg WinMsg = *dynamic_cast<const Args_WindowMsg*>(&arg);
    WindowMsg msg = WinMsg.m_Msg; 
   
    s32 x = LOWORD(msg.lParam);
    s32 y = HIWORD(msg.lParam);
	CPoint point(x, y);
    
   	Window* pWnd = UIManagePtr->GetWindowPtr( m_strLstPollCns, m_pWndTree );
    if ( pWnd->IsWindowVisible()  )
    {
        CRect rect;
        pWnd->GetWindowRect(&rect);
        if ( !rect.PtInRect(point) )
		{ 

            if ( const Data_CnsID *pData = dynamic_cast<const Data_CnsID *>((IData*)msg.wParam ) )
            { 
                u16 re = m_tConfTempSel.DeletePollCns( pData->m_wData );
                if ( re!= NO_ERROR )
                {
                    HANDLE_ERROR(re);
                    return false;
                }
                UpdateTempInfoDlg(); 
            }

        }
    } 
  
    
    return true;
}
//��������ѯ�б����Ŀ�е�ͼ��
bool CConftempEdtLogic::OnPollItemClick(const IArgs &args )
{   

    if ( !m_bEdtState )
    {
        return false;
    }

    PrtMsg( 0, emEventTypeCmsWindow, "====[CConftempEdtLogic::OnPollItemClick] show pollLstManageMenu");

    if ( const Args_ClickItemInfo *pClickInfo =  dynamic_cast<const Args_ClickItemInfo*>(&args) )
    {
        const IData *pIData = pClickInfo->m_pClickList->GetItemData()->GetUserData();
        if ( const Data_CnsID *pData = dynamic_cast<const Data_CnsID *>(pIData) )
        {
            //m_wCnsID = pData->m_wData;
            CPollLstManage::GetPollLstManage()->SetCurCns(pData->m_wData);
            CRect rect = const_cast<CRect&>(pClickInfo->m_rcFrame);
            
            //�ڴ�rect�����½���ʾ�����˵� 
            Value_WindowPos val; 
            val.nX = rect.right;
            val.nY = rect.top; 
            
            Value_WindowSize valSize;
            UIManagePtr->GetPropertyValue( valSize, m_strDlgPollManageMenu );
            
            Value_WindowPos valLargerBottom;
            UIManagePtr->GetPropertyValue( valLargerBottom, g_stcStrMainMenuDlg  );
            
            if ( val.nY + valSize.nHeight >= valLargerBottom.nY )
            {   
                val.nY = rect.bottom -  valSize.nHeight;
                UIManagePtr->LoadScheme( "SchmImgEx", NULL, m_strDlgPollManageMenu, false ); 
            }
            else
            {
                UIManagePtr->LoadScheme( "SchmImgNormal", NULL, m_strDlgPollManageMenu, false );
            }


            UIManagePtr->SetPropertyValue(val,m_strDlgPollManageMenu);
            CPollLstManage::GetPollLstManage()->ShowPollLstManage(TRUE);
            UIManagePtr->ShowWindow(m_strDlgPollManageMenu);
        }
    }
    return true;
}
 

 
 


//�ѵ�ַ����Ŀ�������ӵ�����ģ���cns�б�
bool CConftempEdtLogic::AddAddrToConfTempEpLst(TAddrItem* pAddrItem)
{
    if ( pAddrItem == NULL )
    {
        return false;
    }
   
    //�����һ����Ŀ����Ѹ���Ŀ��ӵ� cns�б�
    if ( pAddrItem->emItemType == emEntryItem )
    {
        TAddrInfo tAddrInfo = pAddrItem->tAddrInfo;
        u16 wRe = m_tConfTempSel.AddConfEp(tp_Alias_h323,tAddrInfo.achEntryName);
        if ( wRe != NO_ERROR) 
        {
            if (  wRe == ERR_CMS_CNS_MAX_NUM )  
            {
                //HANDLE_ERROR( wRe );
                CString strErr = GET_ERR_STRING( wRe );
                Args_MsgBox argMsg;
                argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr(  m_strDlgConfInfo,m_pWndTree  );
                MSG_BOX_PROMPT( strErr,&argMsg ); 
            }
            
            return false;
        }
 
    }

   //�����һ�����飬�������������Ŀ����ӵ�cns�б���ȥ
    if ( pAddrItem->emItemType == emGroupItem )
    {   
        TGroupInfo tGroupInfo = pAddrItem->tGroupInfo;
        CAddrBook addrBook  = BusinessManagePtr->GetAddrBook();
        for ( int i = 0; i< pAddrItem->tGroupInfo.nEntryNum; i++ ) 
        {
            CAddrEntry  cAddrEntry ;
            u32 dwRe = addrBook.GetAddrEntry(&cAddrEntry, tGroupInfo.adwEntryIdx[i] );
            char pchEntryName[TP_MAX_ALIAS_LEN];
            cAddrEntry.GetEntryName(pchEntryName,TP_MAX_ALIAS_LEN);
            u16 wRe = m_tConfTempSel.AddConfEp(tp_Alias_h323,pchEntryName );
            if ( wRe != NO_ERROR) 
            {
                if (  wRe == ERR_CMS_CNS_MAX_NUM )  
                {
                    //HANDLE_ERROR( wRe );
                    CString strErr = GET_ERR_STRING( wRe );
                    Args_MsgBox argMsg;
                    argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr(  m_strDlgConfInfo,m_pWndTree  );
                    MSG_BOX_PROMPT( strErr,&argMsg ); 
                }
                
              //  return false;
           }
        }  
    }

   return true;  
}


//j��鱾��cns�Ƿ��Ѿ���ӵ�cn���б��У����û�У�����ӽ�ȥ 
bool CConftempEdtLogic::CheckLocalCnsInLst()
{
    TTPCnsInfo cns;
    BusinessManagePtr->GetLocalCnsInfo(cns); 

    if ( strlen( cns.m_achRoomName) == 0  )
    {   
        Args_MsgBox argMsg;
        argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr(  m_strDlgConfInfo,m_pWndTree  );
        MSG_BOX_PROMPT( "��ȡ���᳡ʧ�ܣ����ɸ��Ļ���ģ��",&argMsg );
        return false;
    }

    if ( m_tConfTempSel.m_atEpList.m_wNum > 0  )
    {   
        TEpAddr * pChairMan = m_tConfTempSel.GetCnsAddrByID(m_tConfTempSel.m_wDefaultChairMan);
        if ( strlen( cns.m_achRoomName) == 0 )
        {   
            PrtMsg(0,emEventTypeCmsWindow,"[CConftempEdtLogic::CheckLocalCnsInLst]У�����᳡ʧ�ܣ� ����cns��roomName Ϊ��");

            Args_MsgBox argMsg;
            argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr(  m_strDlgConfInfo,m_pWndTree  );
            MSG_BOX_PROMPT( "��ȡ���᳡ʧ��",&argMsg ); 

            return false;
        }
        else if ( pChairMan!= NULL && strcmp(pChairMan->m_tAlias.m_abyAlias ,cns.m_achRoomName) == 0 )
        {
            return true;
        }
        else
        {   
            //�ж��б����Ƿ��Ѵ��ڸ�cns
            int nChairID = -1 ;
            int nSize = m_tConfTempSel.m_atEpList.m_wNum;
            for ( int i = 0 ; i< nSize; i++ )
            {
                if ( strcmp(m_tConfTempSel.m_atEpList.m_tCnsList[i].m_tAlias.m_abyAlias ,cns.m_achRoomName) == 0 )
                {
                   nChairID = m_tConfTempSel.m_atEpList.m_tCnsList[i].m_wEpID;
                   break;
                }
            }

 
            //�����ڣ������ø�cns����ϯ
            if ( nChairID >= 0 )
            {
                m_tConfTempSel.m_wDefaultChairMan = nChairID;
            }
            else  ////�������ڣ���Ѹ�cns��ӵ��б��У�������Ϊ��ϯ
            {   
                //�����ǰ�����Ѵﵽ�����ֱ���滻ԭ�е���ϯ
                if ( nSize == TP_CONF_MAX_EPNUM )
                { 
                    ZeroMemory(pChairMan->m_tAlias.m_abyAlias ,sizeof(pChairMan->m_tAlias.m_abyAlias));
                    pChairMan->m_tAlias.m_byType = tp_Alias_h323; 
                    strcpy(pChairMan->m_tAlias.m_abyAlias,cns.m_achRoomName);
                }
                else
                { // �ѵ�ǰ���᳡��ӽ�ȥ
                    u16 wRe = m_tConfTempSel.AddConfEp( tp_Alias_h323,cns.m_achRoomName );
                    if ( wRe != NO_ERROR )
                    {   
                       
                        CString strErr = GET_ERR_STRING( wRe );
                        Args_MsgBox argMsg;
                        argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr(  m_strDlgConfInfo,m_pWndTree  );
                        MSG_BOX_PROMPT( strErr,&argMsg );
                        return false;
                    }

                     int nIndex = m_tConfTempSel.m_atEpList.m_wNum; 
                     m_tConfTempSel.m_wDefaultChairMan = m_tConfTempSel.m_atEpList.m_tCnsList[ nIndex -1 ].m_wEpID;
                }
                
            } 
 
        }

    }
    else
    {
       m_tConfTempSel.AddConfEp(tp_Alias_h323,cns.m_achRoomName);
    }
         
    return true;     
}
