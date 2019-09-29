#include "stdafx.h"
#include "netadapter.h"
//#include "netwinerr.h"
#include "windows.h"
#include "cms.h"


#define ALLOCATE_FROM_PROCESS_HEAP( bytes )		::HeapAlloc( ::GetProcessHeap(), HEAP_ZERO_MEMORY, bytes )
#define DEALLOCATE_FROM_PROCESS_HEAP( ptr )		if( ptr ) ::HeapFree( ::GetProcessHeap(), 0, ptr )
#define REALLOC_FROM_PROCESS_HEAP( ptr, bytes )	::HeapReAlloc( ::GetProcessHeap(), HEAP_ZERO_MEMORY, ptr, bytes )
#define  EXEFILE     "c:\\WINDOWS\\system32\\netsh.exe"
HANDLE	g_hwndNetCheck = NULL;	// ��ȡ�߳����ݵľ��
DWORD	g_dwNetCheckNum = 0;	// ��ȡ�����̱߳��
HANDLE	g_hNetCheckStop = NULL;	// ֹͣ�¼�
u32 WINAPI NetCheckThreadProc(LPVOID pParam);
//void CALLBACK MyTimerProc(HWND hwnd,UINT uMsg,UINT idEvent,u32 dwTime); 

CRITICAL_SECTION    CNetworkAdapter::m_s_tCriticalSection;
BOOL32              CNetworkAdapter::m_bCheckIP = TRUE;
s32                 CNetworkAdapter::m_nNetWorkCnt = 0;
CString             CNetworkAdapter::m_strCurNetWorkName = "";
CIPInfoManager*     CNetworkAdapter::m_pNetWorkAssist = NULL;
CString             CNetworkAdapter::m_cstrCurNetCardName = "��������";

CNetworkAdapter * CNetworkAdapter::m_ptNetParam = NULL;

//////////////////////////////////////////////////////////////////////////
// API ��ʼ��
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
//		��õ�ǰϵͳ�����������б���õ�ǰ��������ip����Ϣ
//		���û���㹻�Ŀռ䣬����ERROR_INSUFFICIENT_BUFFER
//		
//		�ɹ�����bufferʹ�ô�С
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
			m_strCurNetWorkName = strText; //Ŀǰ������ֻ��һ���������

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
		//Ҫ���ж������������Ҫ�ڴ˴����޸�
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
	//��ֹ��vista��û����ֵʱ��ʾ����255.255.255.255
	if ( sStr == _T("") )
	{
		sStr = _T("0.0.0.0");
	}

	return sStr;
}

////////////////////////////////////////////////////////////
//	Desc:
//		����string������������
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

		//��ȡ����MAC��ַ,��ǰipΪ0�����ڶ���ʱ����߻�ȡ����ipʱ��
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
		//MAC ��ַת��
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
		
		//��ȡ����������ȥip��MAC��ַ
		if ( chIP == 0 )
		{
			return TRUE;
		}

		ulLen = 6;
		memset(pulMac, 0xff, sizeof(pulMac));
		hr = SendARP(chIP, 0, pulMac, &ulLen);
		// 
		//ת��MAC��ַ 
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
			//MessageBox( "IP��ͻ" );
			
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

	//��ipʼ�տ�������ȥ��ip��ͻ�ж����߳����ж�
 	if ( TRUE == NetIpConflict( dwIPAddr) )
 	{
 		return FALSE;
 	}	

	CString strExut = "netsh interface ip set address name=\"";
			
	//strExut += "�������� static";
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
        //����DHCP
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
	//strExut += "name=�������� source=dhcp";
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

 //����DNS������ʹ��DHCP
BOOL CNetworkAdapter::SetDnsDhcpToPc( BOOL bRefreshIPCfg /*= TRUE*/ )
{
    m_bDnsDhcpUsed = TRUE;
    CString strExu =  "netsh interface ip set dns ";	
    //strExut += "name=�������� source=dhcp";
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

//����DNS��ַ
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

 //���ñ���DNS��ַ
BOOL CNetworkAdapter::SetBackupDnsAddr( u32 dwDNSAddr , BOOL bRefreshIPCfg /*= TRUE */)
{
    s8 achDNSAddr[16];
    u8  *pDNS; 
    pDNS = (u8*)&dwDNSAddr;
    sprintf(achDNSAddr, "%u.%u.%u.%u", *(pDNS+3), *(pDNS+2), *(pDNS+1), *pDNS);
    
    CString strDNS = "";
    //netsh interface ip add dns "�������� " 202.193.160.33  
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

        // ������������������Ϣ���ں���
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
			
			if ( m_pIfRow->dwType   == MIB_IF_TYPE_ETHERNET) //ֻ����ethernet
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
				sprintf(temp,"����:%s �����ַ:%s  ����:%d\n", strTemp, strPhy, m_nNetCnt);
				*/
				//Ŀǰû�и��÷���ȥ���ֵ�ǰ����ʹ�õ�����������������ȥ����
				if ( 0 == m_strCurNetWorkName.CompareNoCase(strTemp)) 
				{
					//��ס���������ݴ�����ȥ�жϵ�ǰ����������״̬
					//��win7���棬����ںܶ����������������ʹ������ȫ���ģ�Ϊ��ʹ��������״̬���ж�
					//����״̬ ������Ҫ�������Ĵ���
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
    //Sleep(100);//���������IP���˳�Ȼ��5s�������������ȡ��������ӿ����� 2010-12-17
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





/* ////////�����������ļ�///////////////////////////////
C:\Documents and Settings\yujinjin>netsh interface help
   ���������е�����:
   ?              - ��ʾ�����б�
   add            - ��������һ��������Ŀ��
   delete         - �ӱ���ɾ��һ��������Ŀ��
   dump           - ��ʾһ�����ýű���
   help           - ��ʾ�����б�
   ip             - ���ĵ� `netsh interface ip' �����ġ�
   ipv6           - ���ĵ� `netsh interface ipv6' �����ġ�
   portproxy      - ���ĵ� `netsh interface portproxy' �����ġ�
   reset          - ��λ��Ϣ��
   set            - ����������Ϣ��
   show           - ��ʾ��Ϣ��
   
���е��������Ŀ���:
 ip ipv6 portproxy

C:\Documents and Settings\yujinjin>netsh interface ip set ?

  ����ָ����Ч:
  
    ���������е�����:
    set address    - ����ָ���Ľӿڵ� IP ��ַ��Ĭ�����ء�
    set dns        - ���� DNS ������ģʽ�͵�ַ��
    set wins       - ���� WINS ������ģʽ�͵�ַ��
 
   C:\Documents and Settings\yujinjin>netsh interface ip set ?
   
     ����ָ����Ч:
     
       ���������е�����:
       set address    - ����ָ���Ľӿڵ� IP ��ַ��Ĭ�����ء�
       set dns        - ���� DNS ������ģʽ�͵�ַ��
       set wins       - ���� WINS ������ģʽ�͵�ַ��
       
         C:\Documents and Settings\yujinjin>netsh interface ip set address ?
         
           �÷�: set address [name=]<string>
           [[source=]dhcp |
           [source=] static [addr=]IP address [mask=]IP subnet mask]
           [[gateway=]<IP address>|none [gwmetric=]integer]
           
            ����:

            ���           ֵ
            name         - �ӿ����ơ�
            source       - ����ֵ֮һ:
            dhcp: ����ָ���ӿڣ������� DHCP ���� IP
            ��ַ��
            static: ����ʹ�ñ��ؾ�̬�������� IP
            ��ַ��

            gateway      - ����ֵ֮һ:
            <IP address>: �����õ� IP ��ַ��ָ��Ĭ��
            ���ء�
            none: ������Ĭ�����ء�
            gwmetric     - Ĭ�����ص�Ծ�����������������Ϊ 'none'����
            ��Ӧ���ô��ֶΡ�
            ֻ���� 'source' Ϊ 'static' ʱ����������ѡ��:

            addr         - ָ���ӿڵ� IP ��ַ��
            mask         - ָ�� IP ��ַ���������롣

            ע��   : ������ IP ��ַ����ģʽ�� DHCP ģʽ��Ϊ static����� static
            ģʽ��Ϊ DHCP���þ�̬ IP ��ַ�ڽӿ������ IP ��ַ�������
            Ĭ�����ء�
            ʾ��   :

            set address name="Local Area Connection" source=dhcp
            set address local static 10.0.0.9 255.0.0.0 10.0.0.1 1



C:\Documents and Settings\yujinjin>netsh interface ip set dns ? 
       

�÷�: set dns [name=]<string> [source=]dhcp|static [addr=]<IP address>|none
[[register=]none|primary|both]

  ����:
  
    ��־           ֵ
    name         - ��������ơ�
    source       - �����ֵ֮һ:
    dhcp: ���� DHCP ��ΪΪĳһ���������� DNS ��������Դ��
    
    ��̬: �������� DNS ��������ԴΪ���ؾ�̬���á�

    addr         - �����ֵ֮һ:
    <IP ��ַ>: DNS ��������һ�� IP��
    none: ��� DNS �������б�
    register     - �����ֵ֮һ:
    none: ���ö�̬ DNS ע�ᡣ
    primary: ֻ���� DNS ��׺��ע�ᡣ
    both: ���� DNS ��׺��ע�ᣬҲ���ض����Ӻ�׺��ע�ᡣ

    ˵��:    ���� DNS ����������Ϊ DHCP ��̬ģʽ��ֻ����Դ�ǡ�static����
    ���ҡ�addr�� ѡ��Ҳ������Ϊ���ض��Ľ������� DNS �������� IP
    ��ַ��һ����̬�б������¡�

    ʾ��:

      set dns name="Local Area Connection" source=dhcp
     set dns "Local Area Connection" static 10.0.0.1 primary  
   

    //���ñ���DNS������
     netsh interface ip add dns "�������� " 202.193.160.33  
*/


