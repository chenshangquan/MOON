// IpCfgLogic.cpp: implementation of the CIpCfgLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IpCfgLogic.h"
#include "msgBoxLogic.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

 

CIpCfgLogic *CIpCfgLogic::m_pLogic = NULL;

 

const String CIpCfgLogic::m_strEdtIp = "IPCtrlIP" ;
const String CIpCfgLogic::m_strEdtSubMask = "IPCtrlSubMask";
const String CIpCfgLogic::m_strEdtGateWay = "IPCtrlGateway";
const String CIpCfgLogic::m_strEdtPriorityDns = "IPCtrlPriorityDNS" ;
const String CIpCfgLogic::m_strEdtBkupDns = "IPCtrlBkupDNS";

const String CIpCfgLogic::m_strSwBtnDhcp = "BtnAutoGetIP";
const String CIpCfgLogic::m_strSwBtnAutoDns ="BtnAutoGetDNS";


const String CIpCfgLogic::m_strSchmUseIPDhcp = "schmUseIpDhcp" ;
const String CIpCfgLogic::m_strSchmNotUseIPDhcp = "schmNotUseIpDhcp" ;
const String CIpCfgLogic::m_strSchmUseDnsDhcp = "schmUseDnsDhcp" ;
const String CIpCfgLogic::m_strSchmNotUseDnsDhcp = "schmNotUseDnsDhcp" ;



UINT ThreadSetIP(LPVOID lpParam)
{    
    u16 re= NO_ERROR;
    TIpConfig *ipCfg = ( TIpConfig * )lpParam  ;
    if ( ipCfg != NULL )
    {
        //BusinessManagePtr->GetIPCfg()->SetIPToPC( *ipCfg );
        CIpCfgLogic::GetLogicPtr()->SetPc(*ipCfg );
        
    }

    MSG_BOX_NOBTN("设置IP成功。" , NULL );
   
    //设置到文件
    CIpCfgLogic::GetLogicPtr()->ReFreshIpCfg();  
    CIpCfgLogic::GetLogicPtr()->m_tLocalIp.bDnsDhcp = ipCfg->bDnsDhcp;
    
    UIManagePtr->SaveToFile( g_stcStrIpCfgDlg, "", "WindowCaption" ,TRUE );
    UIManagePtr->SaveToFile( g_stcStrIpCfgDlg, "", "SwitchState"  ,TRUE  ); 
     
    
    HIDE_MSG_BOX
        
    UIManagePtr->ShowWindow( g_stcStrIpCfgDlg, false );
    UIManagePtr->LoadScheme( "shcmShowLoginFrm", NULL,g_stcStrLoginDlg ); 

    return re;
} 


CIpCfgLogic::CIpCfgLogic():m_tLocalIp(),m_tAUiIpCfg()
{ 
//    const_cast<String&>(m_strEdtIp) = g_stcStrIpCfgDlg + "/" + m_strEdtIp;
//    const_cast<String&>(m_strEdtSubMask) = g_stcStrIpCfgDlg + "/" + m_strEdtSubMask; 
//    const_cast<String&>(m_strEdtGateWay) = g_stcStrIpCfgDlg + "/" + m_strEdtGateWay; 
//    const_cast<String&>(m_strEdtPriorityDns) = g_stcStrIpCfgDlg + "/" + m_strEdtPriorityDns; 
//    const_cast<String&>(m_strEdtBkupDns) = g_stcStrIpCfgDlg + "/" + m_strEdtBkupDns; 
//    const_cast<String&>(m_strSwBtnDhcp) = g_stcStrIpCfgDlg + "/" + m_strSwBtnDhcp; 
//    const_cast<String&>(m_strSwBtnAutoDns) = g_stcStrIpCfgDlg + "/" + m_strSwBtnAutoDns; 
}

CIpCfgLogic::~CIpCfgLogic()
{
    if ( m_pLogic != NULL )
    {   
        UnRegMsg();
        UnRegFunc();
        delete m_pLogic;
        m_pLogic = NULL; 
    }
}


CIpCfgLogic* CIpCfgLogic::GetLogicPtr()
{
    if ( m_pLogic == NULL )
    {  
        m_pLogic = new CIpCfgLogic();   
    }
    
    return m_pLogic;
}

bool CIpCfgLogic::InitWnd( const IArgs & arg )
{   
    CWndLogicBase::InitWnd( arg ); 
    ReFreshIpCfg(); 
    //开机重启，把文件中存放的ip 信息设置到Pc上
    TIpConfig  tIpCfg;
    bool bRe = GetIpCfgFrmUI( tIpCfg );
    
    if ( bRe )
    {   
        //如果未使用dhcp且IP为0 则显示当前pc IP，否则把文件中的IP设置到PC
        if ( !tIpCfg.bIpDhcp && tIpCfg.dwIP == 0 )
        {
           ; //UpdateUI( m_tLocalIp );
        }
        else
        {
            SetPc( tIpCfg ); 
            ReFreshIpCfg(); 
            m_tLocalIp.bDnsDhcp = tIpCfg.bDnsDhcp;

        }

        

        UpdateUI( m_tLocalIp );
    }

    return true;

}


void CIpCfgLogic::RegMsg()
{   
    //会议的cns列表更新 
    //REG_MSG_HANDLER( UI_UMS_REFRESH_CONFCNS_LIST,CTvwLogic::OnRefreshCnsLstNotify , m_pLogic, CTvwLogic  );
}


 
bool CIpCfgLogic::RegCBFun()
{   
    REG_GOBAL_MEMBER_FUNC( "CIpCfgLogic::InitWnd", CIpCfgLogic::InitWnd, m_pLogic, CIpCfgLogic);	 
    REG_GOBAL_MEMBER_FUNC( "CIpCfgLogic::BtnSaveClick", CIpCfgLogic::BtnSaveClick, m_pLogic, CIpCfgLogic);
    REG_GOBAL_MEMBER_FUNC( "CIpCfgLogic::BtnCancleClick", CIpCfgLogic::BtnCancleClick, m_pLogic, CIpCfgLogic);
    REG_GOBAL_MEMBER_FUNC( "CIpCfgLogic::BtnAutoGetIP", CIpCfgLogic::BtnAutoGetIP, m_pLogic, CIpCfgLogic);
    REG_GOBAL_MEMBER_FUNC( "CIpCfgLogic::BtnAutoGetDNS", CIpCfgLogic::BtnAutoGetDNS, m_pLogic, CIpCfgLogic);
 
    return true;
}


void CIpCfgLogic::UnRegMsg()
{

}

void CIpCfgLogic::Clear()
{

}


bool CIpCfgLogic::BtnSaveClick( const IArgs & arg )
{  
   // ReFreshIpCfg();

    TIpConfig  tIpCfg;
    bool bRe = GetIpCfgFrmUI( tIpCfg );
     
    Args_MsgBox msgArg;
    msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
    //检测IP 
    if ( !tIpCfg.bIpDhcp  )
    {   
        
        CString cstrErrStr;
	    if ( !CCallAddr::IsValidDevIP( tIpCfg.dwIP, tIpCfg.dwSubMask, cstrErrStr, 0 ) ) 
        {
            UIManagePtr->SetFocus( m_strEdtIp, m_pWndTree );
            MSG_BOX_PROMPT( cstrErrStr, &msgArg );
            return false;
        } 
        
        if ( !CCallAddr::IsValidIpMask(tIpCfg.dwSubMask) )
        {  
            UIManagePtr->SetFocus( m_strEdtSubMask, m_pWndTree );
            MSG_BOX_PROMPT( "掩码IP地址非法", &msgArg );
            return false;
        }
        
        CString cstrErrStr;
        if ( tIpCfg.dwGateWay != 0 && !CCallAddr::IsValidCallIP(tIpCfg.dwGateWay, cstrErrStr, 0) )
        {   
            UIManagePtr->SetFocus( m_strEdtGateWay, m_pWndTree );
            MSG_BOX_PROMPT( cstrErrStr, &msgArg );
            return false;
        } 
        
        if ( tIpCfg.dwPriorityCns != 0 && tIpCfg.dwPriorityCns == tIpCfg.dwBkupCns )
        {   
            UIManagePtr->SetFocus( m_strEdtPriorityDns, m_pWndTree );
            MSG_BOX_PROMPT( "首选DNS服务器和备用DNS服务器IP地址不可以重复", &msgArg );
            return false; 
        }


//         if ( !CCallAddr::IsValidIpV4(tIpCfg.dwPriorityCns) )
//         {
//             MSG_BOX_PROMPT( "首选DNS服务器IP地址非法", &msgArg );
//             return false;
//         }
//        
//         
//         if ( !CCallAddr::IsValidIpV4(tIpCfg.dwBkupCns) )
//         {
//             MSG_BOX_PROMPT( "备用DNS服务器IP地址非法", &msgArg );
//             return false;
//         } 
    }
    else
    {
        if ( !tIpCfg.bDnsDhcp)
        {
            if ( tIpCfg.dwPriorityCns != 0 && tIpCfg.dwPriorityCns == tIpCfg.dwBkupCns )
            {   
                UIManagePtr->SetFocus( m_strEdtPriorityDns, m_pWndTree );
                MSG_BOX_PROMPT( "首选DNS服务器和备用DNS服务器的IP地址不可以重复", &msgArg );
                return false; 
            }
        }
    }

    MSG_BOX_NOBTN("正在设置IP,请耐心等待......", &msgArg);
    m_tAUiIpCfg = tIpCfg;

    ReFreshIpCfg();
    AfxBeginThread( ThreadSetIP, &m_tAUiIpCfg );  
 
    
    
    return true;
}

 

bool CIpCfgLogic::BtnCancleClick( const IArgs & arg )
{     

    UIManagePtr->ShowWindow( g_stcStrIpCfgDlg, false );
    UIManagePtr->LoadScheme( "shcmShowLoginFrm", NULL,g_stcStrLoginDlg ); 

    UpdateUI( m_tLocalIp );
    
    return true;
}

bool CIpCfgLogic::BtnAutoGetIP( const IArgs & arg )
{  
    //禁用设置IP相关控件
    bool bUseDchp = false;
    UIManagePtr->GetSwitchState(m_strSwBtnDhcp, bUseDchp, m_pWndTree); 
    if ( !bUseDchp )
    {
       // UIManagePtr->LoadScheme( m_strSchmUseIPDhcp, NULL, g_stcStrIpCfgDlg );
       UseIpDhcp(TRUE);
    }
    else
    {
       // UIManagePtr->LoadScheme( m_strSchmNotUseIPDhcp, NULL, g_stcStrIpCfgDlg );
        UseIpDhcp(FALSE);
        
    }
    return true;
}

bool CIpCfgLogic::BtnAutoGetDNS( const IArgs & arg )
{
    //禁用设置dns相关控件
    bool bAutoGetDns = false;
    UIManagePtr->GetSwitchState(m_strSwBtnAutoDns, bAutoGetDns, m_pWndTree);   
    if ( !bAutoGetDns )
    {
      //  UIManagePtr->LoadScheme( m_strSchmUseDnsDhcp, NULL, g_stcStrIpCfgDlg );
        UseDnsDhcp(TRUE);
    }
    else
    {
       // UIManagePtr->LoadScheme( m_strSchmNotUseDnsDhcp, NULL, g_stcStrIpCfgDlg );
        UseDnsDhcp(FALSE);
        
    }
    return true;
}

bool CIpCfgLogic::GetIpCfgFrmUI( TIpConfig& tIpCfg )
{ 
    if ( m_pWndTree == NULL )
    {
        return false ;
    }

    ZeroMemory(&tIpCfg,sizeof(TIpConfig) );

    bool bUseDchp = false;
    UIManagePtr->GetSwitchState(m_strSwBtnDhcp, bUseDchp, m_pWndTree); 
    tIpCfg.bIpDhcp = bUseDchp;
    
    bool bAutoGetDns = false;
    UIManagePtr->GetSwitchState(m_strSwBtnAutoDns, bAutoGetDns, m_pWndTree);   
    tIpCfg.bDnsDhcp = bAutoGetDns;
    
   
    
    if ( !tIpCfg.bIpDhcp  )
    {
        Value_IpEditData valIp;
        UIManagePtr->GetPropertyValue(valIp, m_strEdtIp, m_pWndTree);  
        
        Value_IpEditData valSubMask;
        UIManagePtr->GetPropertyValue(valSubMask, m_strEdtSubMask, m_pWndTree); 
        
      
        
        Value_IpEditData valGateway;
        UIManagePtr->GetPropertyValue(valGateway, m_strEdtGateWay, m_pWndTree); 
        
      
        Value_IpEditData valPriDns;
        UIManagePtr->GetPropertyValue(valPriDns, m_strEdtPriorityDns, m_pWndTree); 
        
        
        
        Value_IpEditData valBkupDns;
        UIManagePtr->GetPropertyValue(valBkupDns, m_strEdtBkupDns, m_pWndTree); 
       
        
        tIpCfg.dwIP = valIp.dwIP;
        tIpCfg.dwSubMask = valSubMask.dwIP;
        tIpCfg.dwGateWay = valGateway.dwIP;
        tIpCfg.dwPriorityCns = valPriDns.dwIP;
        tIpCfg.dwBkupCns = valBkupDns.dwIP;
        
    } 
    else
    {
        if ( !bAutoGetDns )
        {
            Value_IpEditData valPriDns;
            UIManagePtr->GetPropertyValue(valPriDns, m_strEdtPriorityDns, m_pWndTree); 
            
            //DNS地址不做校验
            //             if ( !CCallAddr::IsValidIpV4(valPriDns.dwIP) )
            //             {
            //                 MSG_BOX_PROMPT( "首选DNS服务器IP地址非法", &msgArg );
            //                 return false;
            //             }
            
            Value_IpEditData valBkupDns;
            UIManagePtr->GetPropertyValue(valBkupDns, m_strEdtBkupDns, m_pWndTree); 
            
            //             if ( !CCallAddr::IsValidIpV4(valBkupDns.dwIP) )
            //             {
            //                 MSG_BOX_PROMPT( "备用DNS服务器IP地址非法", &msgArg );
            //                 return false;
            //             } 
            
            tIpCfg.dwPriorityCns = valPriDns.dwIP;
            tIpCfg.dwBkupCns = valBkupDns.dwIP;
        }
    }

    return true;

}
//根据UI上的IP来设置PC
bool CIpCfgLogic::SetPc( TIpConfig& tIpCfg )
{  

    bool bNeedSetIp = false ;
    if ( tIpCfg.bIpDhcp != m_tLocalIp.bIpDhcp )
    {   
        bNeedSetIp = true;
    } 
    else if( !tIpCfg.bIpDhcp  )  //如果dhcp状态相同
    {
        if ( tIpCfg.dwIP != m_tLocalIp.dwIP || tIpCfg.dwSubMask != m_tLocalIp.dwSubMask
            || tIpCfg.dwGateWay != m_tLocalIp.dwGateWay )
        {
            bNeedSetIp = true;
            
        } 
        
    }

    if ( bNeedSetIp )
    {
        //设置IP
        // BusinessManagePtr->GetIPCfg()->SetIPToPC( tIpCfg );
        if ( tIpCfg.bIpDhcp  )
        {
            BusinessManagePtr->GetIPCfg()->SetDHCPToPC(TRUE);
        }
        else 
        {
            BusinessManagePtr->GetIPCfg()->SetIPToPC( tIpCfg.dwIP,tIpCfg.dwSubMask,tIpCfg.dwGateWay,TRUE);
        }
        
    }  


    bool bNeedSetDNS = true ;

    
    if( tIpCfg.bDnsDhcp  && tIpCfg.bDnsDhcp == m_tLocalIp.bDnsDhcp  ) // 不需要设置dns信息
    {
        bNeedSetDNS = false;
    }
    
    if ( bNeedSetDNS )
    {
        if ( tIpCfg.bDnsDhcp )
        {
            BusinessManagePtr->GetIPCfg()->SetDnsDhcpToPc();
            
        }
        else
        {
            if (tIpCfg.dwPriorityCns != m_tLocalIp.dwPriorityCns )
            {
                BusinessManagePtr->GetIPCfg()->SetDnsAddr( tIpCfg.dwPriorityCns );
            }
            
            if ( tIpCfg.dwBkupCns != m_tLocalIp.dwBkupCns )
            {
                BusinessManagePtr->GetIPCfg()->SetBackupDnsAddr( tIpCfg.dwBkupCns );
                
            }
        }
       
    } 
   
    
	return true;
}

//根据pc的IP来设置UI
void CIpCfgLogic::UpdateUI( TIpConfig& tIpCfg )
{
     
    bool bUseDchp = tIpCfg.bIpDhcp;
    UIManagePtr->SetSwitchState(m_strSwBtnDhcp, bUseDchp, m_pWndTree); 
 
    
    bool bAutoGetDns = tIpCfg.bDnsDhcp; 
    UIManagePtr->SetSwitchState(m_strSwBtnAutoDns, bAutoGetDns, m_pWndTree);   
     
 
    Value_IpEditData valIp;
    valIp.dwIP =  tIpCfg.dwIP ;
    UIManagePtr->SetPropertyValue(valIp, m_strEdtIp, m_pWndTree);  
    
    Value_IpEditData valSubMask ;
    valSubMask.dwIP = tIpCfg.dwSubMask;
    UIManagePtr->SetPropertyValue(valSubMask, m_strEdtSubMask, m_pWndTree); 
  
    Value_IpEditData valGateway ;
    valGateway.dwIP = tIpCfg.dwGateWay;
    UIManagePtr->SetPropertyValue(valGateway, m_strEdtGateWay, m_pWndTree); 
 
    Value_IpEditData valPriDns ;
    valPriDns.dwIP = tIpCfg.dwPriorityCns;
    UIManagePtr->SetPropertyValue(valPriDns, m_strEdtPriorityDns, m_pWndTree); 


    Value_IpEditData valBkupDns;
    valBkupDns.dwIP = tIpCfg.dwBkupCns;
    UIManagePtr->SetPropertyValue(valBkupDns, m_strEdtBkupDns, m_pWndTree); 
          
    if ( bUseDchp )
    {   
        UseIpDhcp(TRUE);
        
    }
    else
    {  
        UseIpDhcp(FALSE);
    }


    if ( bUseDchp )
    { 
        if ( bAutoGetDns )
        {
           // UIManagePtr->LoadScheme( m_strSchmUseDnsDhcp, NULL, g_stcStrIpCfgDlg );
            UseDnsDhcp(TRUE);
        }
        else
        {
           // UIManagePtr->LoadScheme( m_strSchmNotUseDnsDhcp, NULL, g_stcStrIpCfgDlg );
            UseDnsDhcp(FALSE);
        }
    }
    
}


void CIpCfgLogic::ReFreshIpCfg()
{
    CNetworkAdapter *pcAdt = NULL;
    u32 dwIP = 0;
    u32 dwMask = 0;
    u32 dwDns = 0;
    u32 dwGateWay= 0;
    u8 byUseDHCP = 0;
    
    CNetworkAdapter::InitIPCfgAPI();
    pcAdt = BusinessManagePtr->GetIPCfg();
    if ( pcAdt == NULL  )
    {
        return ;
    }
 
    m_tLocalIp.dwIP = inet_addr( pcAdt->GetIpAddr(0).c_str() );
    m_tLocalIp.dwSubMask = inet_addr( pcAdt->GetSubnetForIpAddr(0).c_str() );
    m_tLocalIp.dwGateWay = inet_addr( pcAdt->GetGatewayAddr(DEFAULT_GATEWAY_ADDR).c_str() );
    m_tLocalIp.dwPriorityCns = inet_addr( pcAdt->GetDnsAddr(0).c_str() );
    m_tLocalIp.dwBkupCns = inet_addr( pcAdt->GetDnsAddr(1).c_str() );
	m_tLocalIp.bIpDhcp = pcAdt->IsDhcpUsed();
    //m_tLocalIp.bDnsDhcp = pcAdt->IsDnsDhcpUsed();
    //PrtMsg("\nbDnsDhcp=%d\n",m_tLocalIp.bDnsDhcp);
    m_tLocalIp.bDnsDhcp = TRUE;
    if ( m_tLocalIp.dwPriorityCns != 0 )
    {
        m_tLocalIp.bDnsDhcp = FALSE;
    }
    
    m_tLocalIp.dwIP = ntohl( m_tLocalIp.dwIP );
    m_tLocalIp.dwSubMask = ntohl( m_tLocalIp.dwSubMask ); 
    m_tLocalIp.dwGateWay = ntohl( m_tLocalIp.dwGateWay ); 
    m_tLocalIp.dwPriorityCns = ntohl( m_tLocalIp.dwPriorityCns ); 
    m_tLocalIp.dwBkupCns = ntohl( m_tLocalIp.dwBkupCns ); 
     
    

}


void CIpCfgLogic::UseIpDhcp( BOOL bUse )
{
    if ( bUse )
    {
        UIManagePtr->LoadScheme( m_strSchmUseIPDhcp , NULL ,g_stcStrIpCfgDlg );
        // 把IP置空
        UIManagePtr->SetCaption( m_strEdtIp, "",m_pWndTree );
        UIManagePtr->SetCaption( m_strEdtSubMask, "", m_pWndTree );
        UIManagePtr->SetCaption( m_strEdtGateWay, "", m_pWndTree ); 
        
    }
    else
    {
        UIManagePtr->SetSwitchState( m_strSwBtnAutoDns, false, m_pWndTree );
        UIManagePtr->LoadScheme( m_strSchmNotUseIPDhcp , NULL ,g_stcStrIpCfgDlg );  
    }

}
void CIpCfgLogic::UseDnsDhcp( BOOL bUse )
{
    if ( bUse )
    {
        UIManagePtr->LoadScheme( m_strSchmUseDnsDhcp, NULL, g_stcStrIpCfgDlg );
        
        UIManagePtr->SetCaption( m_strEdtPriorityDns, "", m_pWndTree );
        UIManagePtr->SetCaption( m_strEdtBkupDns, "", m_pWndTree );
    }
    else
    {
        UIManagePtr->LoadScheme( m_strSchmNotUseDnsDhcp, NULL, g_stcStrIpCfgDlg );
        

    }
}
