#include "stdafx.h"
#include "netadapter.h"
//#include "netwinerr.h"
#include "windows.h"
#include "cms.h"


#define ALLOCATE_FROM_PROCESS_HEAP( bytes )		::HeapAlloc( ::GetProcessHeap(), HEAP_ZERO_MEMORY, bytes )
#define DEALLOCATE_FROM_PROCESS_HEAP( ptr )		if( ptr ) ::HeapFree( ::GetProcessHeap(), 0, ptr )
#define REALLOC_FROM_PROCESS_HEAP( ptr, bytes )	::HeapReAlloc( ::GetProcessHeap(), HEAP_ZERO_MEMORY, ptr, bytes )
#define  EXEFILE     "c:\\WINDOWS\\system32\\netsh.exe"
HANDLE	g_hwndNetCheck = NULL;	// 读取线程内容的句柄
DWORD	g_dwNetCheckNum = 0;	// 读取内容线程编号
HANDLE	g_hNetCheckStop = NULL;	// 停止事件
u32 WINAPI NetCheckThreadProc(LPVOID pParam);
//void CALLBACK MyTimerProc(HWND hwnd,UINT uMsg,UINT idEvent,u32 dwTime); 

CRITICAL_SECTION    CNetworkAdapter::m_s_tCriticalSection;
BOOL32              CNetworkAdapter::m_bCheckIP = TRUE;
s32                 CNetworkAdapter::m_nNetWorkCnt = 0;
CString             CNetworkAdapter::m_strCurNetWorkName = "";
CIPInfoManager*     CNetworkAdapter::m_pNetWorkAssist = NULL;
CString             CNetworkAdapter::m_cstrCurNetCardName = "本地连接";

CNetworkAdapter * CNetworkAdapter::m_ptNetParam = NULL;

//////////////////////////////////////////////////////////////////////////
// API 初始化
//////////////////////////////////////////////////////////////////////////
BOOL CNetworkAdapter::InitIPCfgAPI( /*CNetworkAdapter *ptNetParam*/ )
{
	DWORD	dwErr		= 0;
	ULONG	ulNeeded	= 0;
    
    
    EnterCriticalSection( &m_s_tCriticalSection );
    /*
    dwErr = EnumNetworkAdapters( BusinessManagePtr->m_pNetCfg , 0, &ulNeeded );
	if( dwErr == ERROR_INSUFFICIENT_BUFFER ) 
	{		
        if ( BusinessManagePtr->m_pNetCfg!= NULL )
        {
            delete[] BusinessManagePtr->m_pNetCfg ;
			BusinessManagePtr->m_pNetCfg  = NULL;
        }
		BusinessManagePtr->m_pNetCfg = new CNetworkAdapter[ ulNeeded / sizeof( CNetworkAdapter ) ];		
		dwErr = EnumNetworkAdapters( BusinessManagePtr->m_pNetCfg, ulNeeded, &ulNeeded );		
		if( NULL == BusinessManagePtr->m_pNetCfg ) 
		{
            LeaveCriticalSection( &m_s_tCriticalSection );
			return FALSE;
		}		
	}
	else
    {
        LeaveCriticalSection( &m_s_tCriticalSection );
		return FALSE;
    }
    */
    LeaveCriticalSection( &m_s_tCriticalSection );
    //m_ptNetParam = BusinessManagePtr->m_pNetCfg;
	return TRUE;
}


////////////////////////////////////////////////////////////
//	Desc:
//		获得当前系统中适配器的列表，获得当前适配器的ip等信息
//		如果没有足够的空间，返回ERROR_INSUFFICIENT_BUFFER
//		
//		成功返回buffer使用大小
//		
////////////////////////////////////////////////////////////
DWORD CNetworkAdapter::EnumNetworkAdapters( CNetworkAdapter* pAdapters, ULONG ulSzBuf, LPDWORD lpdwOutSzBuf ) 
{	
	IP_ADAPTER_INFO* pAdptInfo	= NULL;
	IP_ADAPTER_INFO* pNextAd	= NULL;	
	ULONG ulLen					= 0;
	int nCnt					= 0;
	DWORD  erradapt;
	
	erradapt = ::GetAdaptersInfo( pAdptInfo, &ulLen );
	if( erradapt == ERROR_BUFFER_OVERFLOW ) 
	{
		pAdptInfo = ( IP_ADAPTER_INFO* )ALLOCATE_FROM_PROCESS_HEAP( ulLen );
		erradapt = ::GetAdaptersInfo( pAdptInfo, &ulLen );		
	}

	pNextAd = pAdptInfo;
    while( NULL != pNextAd ) 
    {
        nCnt++;
        pNextAd = pNextAd->Next;
    }

	*lpdwOutSzBuf = nCnt * sizeof( CNetworkAdapter );
	if( ulSzBuf < *lpdwOutSzBuf ) 
	{		
		DEALLOCATE_FROM_PROCESS_HEAP( pAdptInfo );
		return ERROR_INSUFFICIENT_BUFFER;
	}

	nCnt = 0;

	if( erradapt == ERROR_SUCCESS ) 
	{
		pNextAd = pAdptInfo;

		while( NULL != pNextAd ) 
		{
			pAdapters[ nCnt ].SetupAdapterInfo( pNextAd );	

			CString strText = "";
			strText =  pNextAd->Description;
			m_strCurNetWorkName = strText; //目前仅考虑只有一个网卡情况

			pNextAd = pNextAd->Next;
			nCnt++;
		}
	}

	m_nNetWorkCnt = nCnt;	
	DEALLOCATE_FROM_PROCESS_HEAP( pAdptInfo );		

	return ERROR_SUCCESS;
}

////////////////////////////////////////////////////////////
//	Construction.  
//		
////////////////////////////////////////////////////////////
CNetworkAdapter::CNetworkAdapter() 
{
	m_bDhcpUsed		= FALSE;
	m_bWinsUsed		= FALSE;
	m_dwIndex		= 0;
	m_nAdapterType	= 0;
	m_dwIP          = 0;

	m_nIndexNet     = -1;

	::memset( &m_ucAddress.ucAddress, 0, MAX_ADAPTER_ADDRESS_LENGTH );
	m_ucAddress.nLen = 0;
	
	m_pIfTable = NULL;
	m_nNetWorkCnt = 0; 
	m_strCurNetWorkName = "";
	m_dwCurIfRowIndex = 0;

	m_DnsAddresses.clear();
	m_IpAddresses.clear();
	m_GatewayList.clear();

    
	return;
}

////////////////////////////////////////////////////////////
//	Desc:
//		Deconstruction.
////////////////////////////////////////////////////////////
CNetworkAdapter::~CNetworkAdapter() 
{
#ifdef _DEBUG
	::memset( &m_ucAddress.ucAddress, 0, MAX_ADAPTER_ADDRESS_LENGTH );
	m_ucAddress.nLen = 0;
	m_bDhcpUsed		= FALSE;
	m_bWinsUsed		= FALSE;
	m_dwIndex		= 0;
	m_nAdapterType	= 0;
#endif
	
	m_DnsAddresses.clear();
	m_IpAddresses.clear();
	m_GatewayList.clear();

	m_nIndexNet     = -1;

	if ( NULL != m_pIfTable )
	{
		DEALLOCATE_FROM_PROCESS_HEAP(m_pIfTable);
		m_pIfTable = NULL;	
	}

// 	if ( NULL != CNetworkAdapter::m_pNetWorkAssist )
// 	{
// 		delete CNetworkAdapter::m_pNetWorkAssist;
// 		CNetworkAdapter::m_pNetWorkAssist = NULL;
// 	}

	return;
}

////////////////////////////////////////////////////////////
//	Desc:
//
////////////////////////////////////////////////////////////
BOOL CNetworkAdapter::SetupAdapterInfo( IP_ADAPTER_INFO* pAdaptInfo ) 
{
	BOOL bSetupPassed				= FALSE;
	IP_ADDR_STRING* pNext			= NULL;
	IP_PER_ADAPTER_INFO* pPerAdapt	= NULL;
	ULONG ulLen						= 0;
	DWORD  err;

	TIPINFO iphold;
	
	if( pAdaptInfo ) 
	{
		if ( m_nIndexNet >= 0 )
		{
			m_nIndexNet ++;
		}
		
#ifndef _UNICODE 
		m_sName			= pAdaptInfo->AdapterName;		
		m_sDesc			= pAdaptInfo->Description;
#else
		USES_CONVERSION;
		m_sName			= A2W( pAdaptInfo->AdapterName );
		m_sDesc			= A2W( pAdaptInfo->Description );
#endif
		//要是有多个适配器开启要在此处作修改
// 		if ( m_sDesc.c_str() != "Realtek RTL8168/811 Family PCI-E GBE Ethernet NIC" )
// 		{
// 			return FALSE;
// 		}

		s32 nI = -1;
		nI ++;
		if ( m_nIndexNet < 0 )
		{
			m_nIndexNet = nI;
		}
		

		m_sPriWins		= pAdaptInfo->PrimaryWinsServer.IpAddress.Str;
		m_sSecWins		= pAdaptInfo->SecondaryWinsServer.IpAddress.Str;
		m_dwIndex		= pAdaptInfo->Index;		
		m_nAdapterType	= pAdaptInfo->Type;	
		m_bDhcpUsed		= pAdaptInfo->DhcpEnabled;
		m_bWinsUsed		= pAdaptInfo->HaveWins;	
		m_tLeaseObtained= pAdaptInfo->LeaseObtained;
		m_tLeaseExpires	= pAdaptInfo->LeaseExpires;
		m_sDhcpAddr		= pAdaptInfo->DhcpServer.IpAddress.Str;
		
		if( pAdaptInfo->CurrentIpAddress ) 
		{
			m_sCurIpAddr.sIp		= pAdaptInfo->CurrentIpAddress->IpAddress.Str;
			m_sCurIpAddr.sSubnet	= pAdaptInfo->CurrentIpAddress->IpMask.Str;
		}
		else
		{
			m_sCurIpAddr.sIp		= _T("0.0.0.0");
			m_sCurIpAddr.sSubnet	= _T("0.0.0.0");
		}

		pNext = &( pAdaptInfo->IpAddressList );
		while( NULL != pNext ) 
		{
			iphold.sIp		= pNext->IpAddress.Str;
			iphold.sSubnet	= pNext->IpMask.Str;
			m_IpAddresses.push_back( iphold );
			pNext = pNext->Next;
		}

		pNext = &( pAdaptInfo->GatewayList );
		while( NULL != pNext ) 
		{
			m_GatewayList.push_back( pNext->IpAddress.Str );
			pNext = pNext->Next;
		}	

		err = ::GetPerAdapterInfo( m_dwIndex, pPerAdapt, &ulLen );
		if( err == ERROR_BUFFER_OVERFLOW ) 
		{
			pPerAdapt = ( IP_PER_ADAPTER_INFO* ) ALLOCATE_FROM_PROCESS_HEAP( ulLen );
			err = ::GetPerAdapterInfo( m_dwIndex, pPerAdapt, &ulLen );
			
			if( err == ERROR_SUCCESS ) 
			{
				pNext = &( pPerAdapt->DnsServerList );
				while( NULL != pNext ) 
				{
					m_DnsAddresses.push_back( pNext->IpAddress.Str );
					pNext = pNext->Next;
				}				
				bSetupPassed = TRUE;
			}

			DEALLOCATE_FROM_PROCESS_HEAP( pPerAdapt );
		}		
	}
	
	return bSetupPassed;
}

////////////////////////////////////////////////////////////
//	Desc:
//		Generic function to grab a string from an array.
//		purpose of this function is just to add error 
//		checking.
////////////////////////////////////////////////////////////
tstring	CNetworkAdapter::GetStringFromArray( const StringArray* pPtr, int nIndex ) const 
{
	tstring sStr = _T("");
	if( pPtr && ( ( SIZE_T )nIndex < pPtr->size() ) ) 
	{
		sStr = ( *pPtr )[ nIndex ];
	}
	//防止在vista上没有设值时显示的是255.255.255.255
	if ( sStr == _T("") )
	{
		sStr = _T("0.0.0.0");
	}

	return sStr;
}

////////////////////////////////////////////////////////////
//	Desc:
//		返回string的适配器类型
//		
////////////////////////////////////////////////////////////
tstring CNetworkAdapter::GetAdapterTypeString( UINT nType ) 
{
	tstring sType = _T("");
	switch( nType ) 
	{
		case MIB_IF_TYPE_OTHER:		sType = _T("Other");		break;
		case MIB_IF_TYPE_ETHERNET:	sType = _T("Ethernet");		break; 
		case MIB_IF_TYPE_TOKENRING:	sType = _T("Token Ring");	break; 
		case MIB_IF_TYPE_FDDI:		sType = _T("FDDI");			break; 
		case MIB_IF_TYPE_PPP:		sType = _T("PPP");			break; 
		case MIB_IF_TYPE_LOOPBACK:	sType = _T("Loopback");		break; 
		case MIB_IF_TYPE_SLIP:		sType = _T("SLIP");			break; 	
		default: sType = _T("Invalid Adapter Type");			break;
	};

	return sType;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//																									//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

tstring CNetworkAdapter::GetAdapterName()				const {	return m_sName; }
tstring CNetworkAdapter::GetAdapterDescription()		const { return m_sDesc; }
time_t CNetworkAdapter::GetLeaseObtained()				const {	return m_tLeaseObtained; }
time_t CNetworkAdapter::GetLeaseExpired()				const {	return m_tLeaseExpires; }
SIZE_T	CNetworkAdapter::GetNumIpAddrs()				const {	return m_IpAddresses.size(); }
SIZE_T	CNetworkAdapter::GetNumDnsAddrs()				const { return m_DnsAddresses.size(); }
tstring	CNetworkAdapter::GetDnsAddr( int nDns )			const { return GetStringFromArray( &m_DnsAddresses, nDns ); }
tstring CNetworkAdapter::GetCurrentIpAddress()			const { return m_sCurIpAddr.sIp; }
BOOL CNetworkAdapter::IsDhcpUsed()						const { return m_bDhcpUsed; }
BOOL CNetworkAdapter::IsDnsDhcpUsed()                   const { return m_bDnsDhcpUsed; }
tstring	CNetworkAdapter::GetDchpAddr()					const {	return m_sDhcpAddr; }
BOOL CNetworkAdapter::IsWinsUsed()						const { return m_bWinsUsed; }
tstring CNetworkAdapter::GetPrimaryWinsServer()			const { return m_sPriWins; }
tstring CNetworkAdapter::GetSecondaryWinsServer()		const { return m_sSecWins; }
tstring	CNetworkAdapter::GetGatewayAddr( int nGateway ) const { return GetStringFromArray( &m_GatewayList, nGateway ); }
SIZE_T	CNetworkAdapter::GetNumGatewayAddrs()			const { return m_GatewayList.size(); }
u32 CNetworkAdapter::GetAdapterIndex()				const {	return m_dwIndex; }
UINT CNetworkAdapter::GetAdapterType()					const { return m_nAdapterType; }

s32 CNetworkAdapter::GetIndex()
{
	return m_nIndexNet;
}


tstring	CNetworkAdapter::GetIpAddr( int nIp ) 
{	
	tstring sAddr = _T("");
	if( ( SIZE_T )nIp < m_IpAddresses.size() ) 
	{
        sAddr = m_IpAddresses[ nIp ].sIp;
	}

	m_dwIP = inet_addr( sAddr.c_str() );

	return sAddr;
}

tstring CNetworkAdapter::GetSubnetForIpAddr( int nIp ) const 
{ 
	tstring sAddr = _T("");
	if( ( SIZE_T )nIp < m_IpAddresses.size() ) 
	{
        sAddr = m_IpAddresses[ nIp ].sSubnet;
	}
	return sAddr;
}

BOOL CNetworkAdapter::NetIpConflict( DWORD chIP )
{
	try
	{

		HRESULT hr; 
		ULONG  pulMac[6];
		ULONG ulLen; 

		//获取本机MAC地址,当前ip为0出现在断链时候或者获取不了ip时候
		if ( m_dwIP == 0 )
		{
			return FALSE;
		}

		ulLen = 6;
		hr = SendARP(m_dwIP, 0, pulMac, &ulLen);
		
		s8 achIP[16];
		u8 *pIP;
		pIP = (u8*)&m_dwIP;
		sprintf(achIP, "%u.%u.%u.%u", *(pIP+3), *(pIP+2), *(pIP+1), *pIP);
		// 
		//MAC 地址转换
		// 
		size_t i, j; 
		char* szMac = NULL;
		szMac = new char[30]; 
		if ( NULL == szMac )
		{
			return FALSE;
		}
		memset(szMac, 0, 30 );
		PBYTE pbHexMac = (PBYTE) pulMac;
		tstring strMACRem;
		ulLen = 6;
		for( i = 0, j = 0; i < ulLen - 1; ++ i )   
		{ 
			j += sprintf( szMac + j, "%02X: ", pbHexMac[i] );
		} 
		
		sprintf(szMac + j, "%02X ", pbHexMac[i]); 
	//	printf("MAC address %s\n ", szMac);
		m_strMAC = szMac;
		
		//获取网络上设下去ip的MAC地址
		if ( chIP == 0 )
		{
			return TRUE;
		}

		ulLen = 6;
		memset(pulMac, 0xff, sizeof(pulMac));
		hr = SendARP(chIP, 0, pulMac, &ulLen);
		// 
		//转换MAC地址 
		//
		ulLen = 6;
		pbHexMac = (PBYTE) pulMac;
		for( i = 0, j = 0; i < ulLen - 1; ++ i )   
		{ 
			j += sprintf( szMac + j, "%02X: ", pbHexMac[i] );
		} 
		
		sprintf(szMac + j, "%02X ", pbHexMac[i]); 
		strMACRem = szMac;
		
		if( strMACRem != m_strMAC  && strMACRem != "FF: FF: FF: FF: FF: FF " )
		{
			//MessageBox( "IP冲突" );
			
			delete []szMac;
			szMac = NULL;
			
			return TRUE;
		}
		else if ( m_strMAC == "CC: CC: CC: CC: CC: CC " )
		{
			delete []szMac;
			szMac = NULL;
			
			return FALSE;
		}	
		
		delete []szMac;
		szMac = NULL;
	}
	catch ( ... )
	{
		return FALSE;
	}
	return FALSE;
}

EmNetStatus CNetworkAdapter::NetAlive( u32 dw )
{
	if ( !IsNetworkAlive( &dw ) )
	{
		DWORD dwRst = GetLastError();
		if ( dwRst == ERROR_SUCCESS )
		{
			return emNetDisconnnect;
		}
		else
		{
			return emNetException;
		}
	}
	else
	{
		return emNetOK;
	}
}

EmNetStatus CNetworkAdapter::GetNetWorkState()
{
	if ( m_nNetWorkCnt == 0) 
	{	
		return emNetDisconnnect;
	}

	BOOL32 bRet = GetIfData();

	if ( !bRet )
	{
		return emNetException;
	}

	m_pIfRow = (MIB_IFROW *)&m_pIfTable->table[m_dwCurIfRowIndex];
	
	if (GetIfEntry(m_pIfRow) != NO_ERROR)
	{
		return emNetException;
	}

	DWORD dwOperStatusMy = 0;
	dwOperStatusMy = m_pIfRow->dwOperStatus;
	
	CString strText = "";
	switch ( dwOperStatusMy )
	{
	case MIB_IF_OPER_STATUS_NON_OPERATIONAL:
	case MIB_IF_OPER_STATUS_UNREACHABLE:
	case MIB_IF_OPER_STATUS_DISCONNECTED:
	case MIB_IF_OPER_STATUS_CONNECTING:
	case MIB_IF_OPER_STATUS_CONNECTED:
		return emNetDisconnnect;
	case MIB_IF_OPER_STATUS_OPERATIONAL:
		return emNetOK;
	default:
		break;
	}
	
	return emNetOK;
}




BOOL CNetworkAdapter::SetIPToPC( u32 dwIPAddr, u32 dwMaskAddr, u32 dwGateAddr, BOOL bRefreshIPCfg /*= TRUE */)
{
    s8 achIP[16];
	s8 achMask[16];
	s8 achGate[16]; 
	u8 *pIP, *pMask, *pGate ;

	pIP = (u8*)&dwIPAddr;
	pMask = (u8*)&dwMaskAddr;
	pGate = (u8*)&dwGateAddr;
   

	sprintf(achIP, "%u.%u.%u.%u", *(pIP+3), *(pIP+2), *(pIP+1), *pIP);
	sprintf(achMask, "%u.%u.%u.%u", *(pMask+3), *(pMask+2), *(pMask+1), *pMask);
	sprintf(achGate, "%u.%u.%u.%u", *(pGate+3), *(pGate+2), *(pGate+1), *pGate);
 
	dwIPAddr = inet_addr( achIP );

	//让ip始终可以设下去，ip冲突判断在线程里判断
 	if ( TRUE == NetIpConflict( dwIPAddr) )
 	{
 		return FALSE;
 	}	

	CString strExut = "netsh interface ip set address name=\"";
			
	//strExut += "本地连接 static";
	strExut += m_cstrCurNetCardName;
	strExut += "\" static";
	strExut += " ";
	strExut += achIP;
	strExut += " ";
	strExut += achMask;
	strExut += " ";
	strExut += achGate;
	strExut += " ";
	strExut += "1";
	OspPrintf( 1, 0, "\n====setip :%s\n", strExut);
	//WinExec( strExut, SW_HIDE );
    WinExecAndWait(EXEFILE, (LPSTR)(LPCTSTR)strExut);
    
    if( bRefreshIPCfg )
    {    
	   InitIPCfgAPI( /*m_ptNetParam*/ );
    }

    return TRUE;
}

BOOL CNetworkAdapter::SetIPToPC( u32 dwIPAddr, u32 dwMaskAddr, u32 dwGateAddr, u32 dwDNSAddr )
{
    SetIPToPC( dwIPAddr, dwMaskAddr, dwGateAddr, FALSE );
		
    SetDnsAddr( dwDNSAddr, FALSE );

	InitIPCfgAPI( /*m_ptNetParam*/ );
	
	return TRUE;
}

BOOL CNetworkAdapter::SetIPToPC( TIpConfig &tEthnet )
{ 
    if ( tEthnet.bIpDhcp )
    {
        //设置DHCP
        SetDHCPToPC( FALSE );
        
        if ( tEthnet.bDnsDhcp )
        {
             SetDnsDhcpToPc( FALSE );
        }
        else
        { 
             SetDnsAddr( tEthnet.dwPriorityCns, FALSE ); 
             SetBackupDnsAddr( tEthnet.dwBkupCns, FALSE );
        } 
        
    }
    else
    {
        SetIPToPC( tEthnet.dwIP, tEthnet.dwSubMask, tEthnet.dwGateWay , FALSE );
        SetDnsAddr( tEthnet.dwPriorityCns, FALSE ); 
        SetBackupDnsAddr( tEthnet.dwBkupCns, FALSE ); 
    } 
    
    InitIPCfgAPI( /*m_ptNetParam*/ );
    
	return TRUE;

}



BOOL CNetworkAdapter::SetDHCPToPC( BOOL bRefreshIPCfg /*= TRUE*/ )
{
	m_bDhcpUsed = TRUE;

	CString strExut = "netsh interface ip set address ";
	//strExut += "name=本地连接 source=dhcp";
	strExut += "name=\"";
	strExut += m_cstrCurNetCardName;
	strExut += "\" source=dhcp";
    OspPrintf( 1, 0, "\n====SetDHCPToPC :%s\n", strExut);
	
	//WinExec( strExut, SW_HIDE );
    WinExecAndWait(EXEFILE, (LPSTR)(LPCTSTR)strExut);
   
    if( bRefreshIPCfg )
    {
         
	   InitIPCfgAPI( /*m_ptNetParam*/ );
    }

	return TRUE;
}

 //设置DNS服务器使用DHCP
BOOL CNetworkAdapter::SetDnsDhcpToPc( BOOL bRefreshIPCfg /*= TRUE*/ )
{
    m_bDnsDhcpUsed = TRUE;
    CString strExu =  "netsh interface ip set dns ";	
    //strExut += "name=本地连接 source=dhcp";
    //set dns name="Local Area Connection" source=dhcp
    strExu += "name=\"";
    strExu += m_cstrCurNetCardName;
    strExu += "\" source=dhcp";
    OspPrintf( 1, 0, "\n====SetDnsDhcpToPc :%s\n", strExu);
    //WinExec( strExu, SW_HIDE );
    WinExecAndWait(EXEFILE, (LPSTR)(LPCTSTR)strExu);
    if( bRefreshIPCfg )
    {
         
	   InitIPCfgAPI( /*m_ptNetParam*/ );
    }
 
    return TRUE;
} 

//设置DNS地址
BOOL CNetworkAdapter::SetDnsAddr( u32 dwDNSAddr , BOOL bRefreshIPCfg /*= TRUE*/ )
{   
    s8 achDNSAddr[16];
    u8  *pDNS; 
    pDNS = (u8*)&dwDNSAddr;
    sprintf(achDNSAddr, "%u.%u.%u.%u", *(pDNS+3), *(pDNS+2), *(pDNS+1), *pDNS);
    
    CString strDNS = "";
    strDNS.Format("netsh interface ip set dns name=\"%s\" source=static addr=", m_cstrCurNetCardName );
    if ( dwDNSAddr == 0 )
    {
    }
    else
    {
        strDNS += achDNSAddr;
        strDNS += " primary ";
    }
    OspPrintf( 1, 0, "\n====SetDnsAddr :%s\n", strDNS);
   // WinExec( strDNS, SW_HIDE );
    WinExecAndWait(EXEFILE, (LPSTR)(LPCTSTR)strDNS);
    if( bRefreshIPCfg )
    {
         
	   InitIPCfgAPI( /*m_ptNetParam*/ );
    }
 
    return TRUE;
}

 //设置备用DNS地址
BOOL CNetworkAdapter::SetBackupDnsAddr( u32 dwDNSAddr , BOOL bRefreshIPCfg /*= TRUE */)
{
    s8 achDNSAddr[16];
    u8  *pDNS; 
    pDNS = (u8*)&dwDNSAddr;
    sprintf(achDNSAddr, "%u.%u.%u.%u", *(pDNS+3), *(pDNS+2), *(pDNS+1), *pDNS);
    
    CString strDNS = "";
    //netsh interface ip add dns "本地连接 " 202.193.160.33  
    strDNS.Format("netsh interface ip add dns name=\"%s\" ", m_cstrCurNetCardName );
    if ( dwDNSAddr == 0 )
    {
    }
    else
    {
        strDNS += achDNSAddr;
        strDNS += "  index=2 ";
    }

    OspPrintf( 1, 0, "\n====SetBackupDnsAddr :%s\n", strDNS);
    
    //WinExec( strDNS, SW_HIDE );
     WinExecAndWait(EXEFILE, (LPSTR)(LPCTSTR)strDNS);
   
    if( bRefreshIPCfg )
    {
         
	   InitIPCfgAPI( /*m_ptNetParam*/ );
    }

    return TRUE;
 
} 



void CNetworkAdapter::StartCheckNet( )
{
	g_hwndNetCheck = CreateThread( NULL,
		                           0,
								   NetCheckThreadProc,
								   0,
								   0,
								   &g_dwNetCheckNum );

	if ( g_hwndNetCheck == NULL )
	{
		CloseHandle(g_hNetCheckStop);
		g_hNetCheckStop = NULL;
		return;
	}
}

u32 WINAPI NetCheckThreadProc(LPVOID pParam)
{
//WND hWnd = reinterpret_cast<HWND>(pParam);

	while(true)
	{
        u32 dwMsgId = 0;
        WPARAM wParam = 0;
        LPARAM lParam = 0;

        EnterCriticalSection( &CNetworkAdapter::m_s_tCriticalSection );

        if ( NULL !=  CNetworkAdapter::GetIpCfg() && TRUE == CNetworkAdapter::m_bCheckIP )
        {
            u32 dwTempip = inet_addr(CNetworkAdapter::GetIpCfg()->GetIpAddr(0).c_str());
			
			//EmNetStatus emNetStatus = theApp.m_pNetParam->NetAlive(dwTempip);
			EmNetStatus emNetStatus = CNetworkAdapter::GetIpCfg()->GetNetWorkState();

			switch ( emNetStatus )
			{
			case emNetOK:
				{
					if ( TRUE == CNetworkAdapter::GetIpCfg()->NetIpConflict( dwTempip ) && FALSE == CNetworkAdapter::GetIpCfg()->IsDhcpUsed() )
					{
						dwMsgId = WM_NET_IPCONFLICT;
						wParam = 0;
						lParam = 0;
					}
					else
					{
						dwMsgId = WM_NET_IPCONFLICT;
						wParam = 1;
						lParam = 0;
					}
				}
				break;
			case emNetDisconnnect:
				{
					dwMsgId = WM_NET_DISCONNECT;
					wParam = emNetDisconnnect;
					lParam = 0;
				}
				break;
			case emNetException:
				{
					dwMsgId = WM_NET_DISCONNECT;
					wParam = emNetException;
					lParam = 0;
				}
				break;
			default:
				{
					dwMsgId = WM_NET_DISCONNECT;
					wParam = emNetDisconnnect;
					lParam = 0;
				}
				break;
			}
        }

        LeaveCriticalSection( &CNetworkAdapter::m_s_tCriticalSection );

        // 避免死锁，将发送消息放在后面
        if ( dwMsgId != 0 )
        {
            CMsgDispatch::SendMessage( dwMsgId, wParam, lParam );
        }

		Sleep( 500 );
	}

	return 0;
}

BOOL CNetworkAdapter::GetIfData()
{	
	DWORD dwSize = 0;
	
	if ( NULL == m_pIfTable ) 
	{
		m_pIfTable = (MIB_IFTABLE *)ALLOCATE_FROM_PROCESS_HEAP(sizeof (MIB_IFTABLE));
		
		if ( NULL == m_pIfTable)
		{
			return FALSE;
		}
	}
	
	dwSize = sizeof (MIB_IFTABLE);
	
	if ( GetIfTable( m_pIfTable, &dwSize, FALSE ) == ERROR_INSUFFICIENT_BUFFER ) 
	{
		DEALLOCATE_FROM_PROCESS_HEAP(m_pIfTable);
		m_pIfTable = NULL;		

		if ( NULL == m_pIfTable ) 
		{
			m_pIfTable = (MIB_IFTABLE *) ALLOCATE_FROM_PROCESS_HEAP( dwSize );

			if ( NULL == m_pIfTable)
			{
				return FALSE;
			}
		}
	}
	
    char temp[256]={0};
	
	if ( GetIfTable(m_pIfTable, &dwSize, FALSE) == NO_ERROR ) 
	{
		for (int i = 0; i < (int) m_pIfTable->dwNumEntries; i++) 
		{
			m_pIfRow = (MIB_IFROW *) & m_pIfTable->table[i];
			
			if ( m_pIfRow->dwType   == MIB_IF_TYPE_ETHERNET) //只处理ethernet
			{	
				CString strTemp = m_pIfRow->bDescr;

				/*
				DWORD	dwPhysAddrLen = 0;
				dwPhysAddrLen = m_pIfRow->dwPhysAddrLen;
				CString strPhy = "";
				CString strPhyText = "";
				CString strTemp = m_pIfRow->bDescr;
				if( dwPhysAddrLen > 0 )
				{
					for(DWORD wIndex=0; wIndex < dwPhysAddrLen-1; ++wIndex)
					{
						strPhyText.Format("%02X-" , m_pIfRow->bPhysAddr[wIndex]);
						strPhy += strPhyText;
					}
					strPhyText.Format("%02X" , m_pIfRow->bPhysAddr[wIndex]);
					strPhy += strPhyText;
				}
				sprintf(temp,"名称:%s 物理地址:%s  数量:%d\n", strTemp, strPhy, m_nNetCnt);
				*/
				//目前没有更好方法去区分当前正在使用的网卡，所以用名称去区别
				if ( 0 == m_strCurNetWorkName.CompareNoCase(strTemp)) 
				{
					//记住索引，根据此索引去判断当前网卡的网络状态
					//在win7上面，会存在很多个网络适配器，即使禁用了全部的，为了使用适配器状态来判断
					//网络状态 所以需要做这样的处理
					m_dwCurIfRowIndex = i; 
				}
			}
		}
		
	}
	return TRUE;
}


void CNetworkAdapter::CreateCurNetCardName()
{
 
	if ( NULL == CNetworkAdapter::m_pNetWorkAssist )
	{
		CNetworkAdapter::m_pNetWorkAssist = new CIPInfoManager();
	}
    
    m_cstrCurNetCardName = CNetworkAdapter::m_pNetWorkAssist->GetCurNetWorkName();
	OspPrintf( 1, 0, "=======netcard:%s\n",m_cstrCurNetCardName ) ;
 
}

BOOL CNetworkAdapter::WinExecAndWait(LPSTR lpExeName, LPSTR lpCmdLine)
{  
    BOOL bRe = FALSE;
    PROCESS_INFORMATION pi;
    
    STARTUPINFO si;
    
    memset(&si,0,sizeof(si));
    
    si.cb=sizeof(si);
    
    si.wShowWindow=SW_HIDE;
    
    si.dwFlags=STARTF_USESHOWWINDOW;	
    
    bRe = CreateProcess( lpExeName, lpCmdLine,NULL, FALSE,NULL,NULL,NULL,NULL,&si,&pi);
    
    if (bRe != FALSE)
    {
        WaitForSingleObject(pi.hProcess,INFINITE);
    }
    //Sleep(100);//解决：设置IP后退出然后5s内再启动软件获取不到网络接口问题 2010-12-17
    return bRe;
} 



#ifndef tstring
#ifdef _UNICODE
#define tstring			std::wstring
#else
#define tstring			std::string		
#endif
#endif

//////////////////////////////////////////////////////////
//	Desc:
//		Class wrapper for windows errors.  This class
//		allows easy translation of error codes into
//		readable strings however, in order for it to
//		work proper it must be given a correct
//		module handle if the error code is not
//		direct from system.
//////////////////////////////////////////////////////////
class CWinErr {
public:
	CWinErr() {
		m_dwErr = 0;
		return;
	}
	
	CWinErr& operator = ( DWORD dwCode ) {
		m_dwErr = dwCode;
		return *this;
	}
	
	void SetCode( DWORD dwCode ) {
		m_dwErr = dwCode;
		return;
	}
	
	DWORD GetCode() {
		return m_dwErr;
	}
	
	operator DWORD(){
		return m_dwErr;
	}
	
	tstring GetFormattedMsg( LPCTSTR lpszModule = NULL ) 
	{
		DWORD	dwFmtRt		= 0;
		DWORD	dwFlags		= FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_FROM_SYSTEM;
		LPVOID	lpMsgBuf	= NULL;
		HMODULE hLookupMod	= NULL;
		tstring	sMsg		= _T("");
		
		if( lpszModule != NULL ) {
			hLookupMod	= ::LoadLibraryEx( lpszModule, NULL, LOAD_LIBRARY_AS_DATAFILE );
			if( hLookupMod ) {
				dwFlags	|=  FORMAT_MESSAGE_FROM_HMODULE;
			}				
		}
		
		dwFmtRt = ::FormatMessage( 
			dwFlags,
			( LPCVOID ) hLookupMod,
			m_dwErr,
			MAKELANGID( LANG_NEUTRAL, SUBLANG_DEFAULT ),
			(LPTSTR)&lpMsgBuf, 
			0,
			NULL );					
		
		
		if( dwFmtRt != 0 )	sMsg = ( TCHAR* ) lpMsgBuf;
		if( lpMsgBuf )		::LocalFree( lpMsgBuf );
		if( hLookupMod )	::FreeLibrary( hLookupMod );			
		
		return sMsg;
	}
	
protected:
	DWORD m_dwErr;
};



tstring CNetworkAdapter::GetWiFiIpAddr()
{
    IP_ADAPTER_INFO* pAdptInfo	= NULL;
    IP_ADAPTER_INFO* pNextAd	= NULL;	
    ULONG ulLen					= 0;
    CWinErr erradapt;
    tstring strIp = "0.0.0.0";
	
    erradapt = ::GetAdaptersInfo( pAdptInfo, &ulLen );
    if( erradapt == ERROR_BUFFER_OVERFLOW ) 
    {
        pAdptInfo = ( IP_ADAPTER_INFO* )ALLOCATE_FROM_PROCESS_HEAP( ulLen );
        erradapt = ::GetAdaptersInfo( pAdptInfo, &ulLen );		
    }
	
    pNextAd = pAdptInfo;
    while( pNextAd ) 
    {
        if ( strcmp( pNextAd->Description, "802.11n Wireless LAN Card" ) == 0 )
        {
            strIp = pNextAd->IpAddressList.IpAddress.Str;
			
            break;
        }
		
        pNextAd = pNextAd->Next;
    }
	
    DEALLOCATE_FROM_PROCESS_HEAP( pAdptInfo );
	
	return strIp;
}

tstring CNetworkAdapter::GetWiFiMaskAddr()
{
    IP_ADAPTER_INFO* pAdptInfo	= NULL;
    IP_ADAPTER_INFO* pNextAd	= NULL;	
    ULONG ulLen					= 0;
    CWinErr erradapt;
    tstring strMaskIp = "0.0.0.0";
	
    erradapt = ::GetAdaptersInfo( pAdptInfo, &ulLen );
    if( erradapt == ERROR_BUFFER_OVERFLOW ) 
    {
        pAdptInfo = ( IP_ADAPTER_INFO* )ALLOCATE_FROM_PROCESS_HEAP( ulLen );
        erradapt = ::GetAdaptersInfo( pAdptInfo, &ulLen );		
    }
	
    pNextAd = pAdptInfo;
    while( pNextAd ) 
    {
        if ( strcmp( pNextAd->Description, "802.11n Wireless LAN Card" ) == 0 )
        {
            strMaskIp = pNextAd->IpAddressList.IpMask.Str;
			
            break;
        }
		
        pNextAd = pNextAd->Next;
    }
	
    DEALLOCATE_FROM_PROCESS_HEAP( pAdptInfo );
	
    return strMaskIp;
}

tstring CNetworkAdapter::GetWiFiGatewayAddr()
{
    IP_ADAPTER_INFO* pAdptInfo	= NULL;
    IP_ADAPTER_INFO* pNextAd	= NULL;	
    ULONG ulLen					= 0;
    CWinErr erradapt;
    tstring strGatewayIp = "0.0.0.0";
	
    erradapt = ::GetAdaptersInfo( pAdptInfo, &ulLen );
    if( erradapt == ERROR_BUFFER_OVERFLOW ) 
    {
        pAdptInfo = ( IP_ADAPTER_INFO* )ALLOCATE_FROM_PROCESS_HEAP( ulLen );
        erradapt = ::GetAdaptersInfo( pAdptInfo, &ulLen );		
    }
	
    pNextAd = pAdptInfo;
    while( pNextAd ) 
    {
        if ( strcmp( pNextAd->Description, "802.11n Wireless LAN Card" ) == 0 )
        {
            strGatewayIp = pNextAd->GatewayList.IpAddress.Str;
			
            break;
        }
		
        pNextAd = pNextAd->Next;
    }
	
    DEALLOCATE_FROM_PROCESS_HEAP( pAdptInfo );
	
	return strGatewayIp;
}


//////////////////////////////////////////// End Accessor Functions ////////////////////////////////////////////





/* ////////相关命令帮助文件///////////////////////////////
C:\Documents and Settings\yujinjin>netsh interface help
   此上下文中的命令:
   ?              - 显示命令列表。
   add            - 向表中添加一个配置项目。
   delete         - 从表中删除一个配置项目。
   dump           - 显示一个配置脚本。
   help           - 显示命令列表。
   ip             - 更改到 `netsh interface ip' 上下文。
   ipv6           - 更改到 `netsh interface ipv6' 上下文。
   portproxy      - 更改到 `netsh interface portproxy' 上下文。
   reset          - 复位信息。
   set            - 设置配置信息。
   show           - 显示信息。
   
下列的子上下文可用:
 ip ipv6 portproxy

C:\Documents and Settings\yujinjin>netsh interface ip set ?

  下列指令有效:
  
    此上下文中的命令:
    set address    - 设置指定的接口的 IP 地址或默认网关。
    set dns        - 设置 DNS 服务器模式和地址。
    set wins       - 设置 WINS 服务器模式和地址。
 
   C:\Documents and Settings\yujinjin>netsh interface ip set ?
   
     下列指令有效:
     
       此上下文中的命令:
       set address    - 设置指定的接口的 IP 地址或默认网关。
       set dns        - 设置 DNS 服务器模式和地址。
       set wins       - 设置 WINS 服务器模式和地址。
       
         C:\Documents and Settings\yujinjin>netsh interface ip set address ?
         
           用法: set address [name=]<string>
           [[source=]dhcp |
           [source=] static [addr=]IP address [mask=]IP subnet mask]
           [[gateway=]<IP address>|none [gwmetric=]integer]
           
            参数:

            标记           值
            name         - 接口名称。
            source       - 下列值之一:
            dhcp: 对于指定接口，设置用 DHCP 配置 IP
            地址。
            static: 设置使用本地静态配置设置 IP
            地址。

            gateway      - 下列值之一:
            <IP address>: 您设置的 IP 地址的指定默认
            网关。
            none: 不设置默认网关。
            gwmetric     - 默认网关的跃点数。如果网关设置为 'none'，则
            不应设置此字段。
            只有在 'source' 为 'static' 时才设置下列选项:

            addr         - 指定接口的 IP 地址。
            mask         - 指定 IP 地址的子网掩码。

            注释   : 用来将 IP 地址配置模式从 DHCP 模式改为 static，或从 static
            模式改为 DHCP。用静态 IP 地址在接口上添加 IP 地址，或添加
            默认网关。
            示例   :

            set address name="Local Area Connection" source=dhcp
            set address local static 10.0.0.9 255.0.0.0 10.0.0.1 1



C:\Documents and Settings\yujinjin>netsh interface ip set dns ? 
       

用法: set dns [name=]<string> [source=]dhcp|static [addr=]<IP address>|none
[[register=]none|primary|both]

  参数:
  
    标志           值
    name         - 界面的名称。
    source       - 下面的值之一:
    dhcp: 设置 DHCP 作为为某一个界面配置 DNS 服务器的源。
    
    静态: 设置配置 DNS 服务器的源为本地静态配置。

    addr         - 下面的值之一:
    <IP 地址>: DNS 服务器的一个 IP。
    none: 清除 DNS 服务器列表。
    register     - 下面的值之一:
    none: 禁用动态 DNS 注册。
    primary: 只在主 DNS 后缀下注册。
    both: 在主 DNS 后缀下注册，也在特定连接后缀下注册。

    说明:    设置 DNS 服务器配置为 DHCP 或静态模式。只有在源是“static”，
    并且“addr” 选项也可用以为此特定的界面配置 DNS 服务器的 IP
    地址的一个静态列表的情况下。

    示例:

      set dns name="Local Area Connection" source=dhcp
     set dns "Local Area Connection" static 10.0.0.1 primary  
   

    //设置备用DNS服务器
     netsh interface ip add dns "本地连接 " 202.193.160.33  
*/


