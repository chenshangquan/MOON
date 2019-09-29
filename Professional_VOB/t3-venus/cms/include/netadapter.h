#ifndef _ADAPTER_INFO_H____
#define _ADAPTER_INFO_H____
#include <windows.h>
#include <tchar.h>
#include <iphlpapi.h>
#include <ipifcons.h>
#include <vector>
#include "SensAPI.h"
#include "ipinfomanager.h"

using namespace std;

class CNetworkAdapter;

#ifndef tstring
	#ifdef _UNICODE
		#define tstring			std::wstring
	#else
		#define tstring			std::string		
	#endif
#endif

// import the internet protocol helper libarary
// #pragma comment( lib, "iphlpapi.lib" )
// #pragma comment(lib, "SensAPI.Lib")
// #pragma comment(lib, "ws2_32.lib")

#define DEFAULT_GATEWAY_ADDR	0

typedef struct tagIPINFO 
{
	tstring sIp;
	tstring sSubnet;
}TIPINFO;

class CIpInfoArray : public vector< TIPINFO > {};
class StringArray : public vector< tstring > {};



#define IsDhcp  0
#define UnDhcp  1

enum EmNetStatus{
    emNetDisconnnect = 0,
        emNetException,
        emNetOK
};



//IP
typedef struct tagIpConfig
{
    BOOL bIpDhcp;             //是否自动获取IP地址
    u32_ip  dwIP;           //IP
    u32_ip  dwSubMask;         //子网掩码
    u32_ip  dwGateWay;      //网关
    
    BOOL bDnsDhcp;           //是否自动获取Dns服务器
    u32_ip  dwPriorityCns;   //首选dns服务器
    u32_ip  dwBkupCns;       //备用dns服务器
public:
    tagIpConfig(){ memset( this ,0 ,sizeof( tagIpConfig ) );}
}TIpConfig;


//////////////////////////////////////////////////////////////////////////////////////////
//	Desc:
//		Class wrapper for a single network adapter.  A listing of these adapters
//		can be built using the EnumNetworkAdapters(...) function prototyped
//		above.
//////////////////////////////////////////////////////////////////////////////////////////
class CNetworkAdapter 
{
public:
	CNetworkAdapter();
	~CNetworkAdapter();

	//供主程序调用初始化改类
	static BOOL InitIPCfgAPI( /* CNetworkAdapter *pNetParam*/  );
    static CNetworkAdapter * GetIpCfg( ){ return m_ptNetParam ; }

	BOOL SetupAdapterInfo( IP_ADAPTER_INFO* pAdaptInfo );

	tstring GetAdapterName() const; //获取适配器名称
	tstring GetAdapterDescription() const;
	
	// dhcp lease access functions
	time_t	GetLeaseObtained() const;
	time_t	GetLeaseExpired() const;
	
	
	SIZE_T	GetNumIpAddrs() const;		         
	SIZE_T	GetNumDnsAddrs() const;
	tstring	GetIpAddr( int nIp = 0 );	        //获取当前静态ip
	tstring GetSubnetForIpAddr( int nIp = 0 ) const; //获取当前静态掩码地址
	tstring	GetDnsAddr( int nDns = 0 ) const;		//获取当前DNS地址
	tstring GetCurrentIpAddress() const;            //获取当前IP
	
	// dhcp function
	BOOL	IsDhcpUsed() const;		                //DHCP是否在用
    BOOL    IsDnsDhcpUsed() const ;
	tstring	GetDchpAddr() const;                    //得到当前DHCP地址

	// wins function
	BOOL	IsWinsUsed() const;
	tstring GetPrimaryWinsServer() const;
	tstring GetSecondaryWinsServer() const;

	tstring	GetGatewayAddr( int nGateway = DEFAULT_GATEWAY_ADDR ) const; //获取当前网关地址
	SIZE_T	GetNumGatewayAddrs() const;

	static	tstring GetAdapterTypeString( UINT nType );
	UINT	GetAdapterType() const;

	u32	    GetAdapterIndex() const;

	//下面3个函数参数都可以直接将界面IPCtl中GetAddress值作为参数传递
	BOOL    NetIpConflict( u32 chIP ); //ip冲突检测,TRUE为冲突
	EmNetStatus    NetAlive( u32 dw );  //当前网络断链与否,TRUE为正常
	EmNetStatus    GetNetWorkState(); //获取网卡状态

	BOOL    SetIPToPC( u32 dwIPAddr, u32 dwMaskAddr, u32 dwGateAddr, u32 dwDNSAddr );//正确返回TRUE 主机序
  
    BOOL    SetIPToPC( u32 dwIPAddr, u32 dwMaskAddr, u32 dwGateAddr, BOOL bRefreshIPCfg = TRUE );

    BOOL    SetIPToPC( TIpConfig &tEthnet );
	
	BOOL    SetDHCPToPC( BOOL bRefreshIPCfg = TRUE ); //正确返回TRUE，设置IP使用DHCP
    
    BOOL    SetDnsDhcpToPc(  BOOL bRefreshIPCfg = TRUE );   //设置DNS服务器使用DHCP
    
    BOOL    SetDnsAddr( u32 dwDNSAddr , BOOL bRefreshIPCfg = TRUE );      //设置DNS地址
    BOOL    SetBackupDnsAddr( u32 dwDNSAddr , BOOL bRefreshIPCfg = TRUE ); //设置备用DNS地址


	void    StartCheckNet( );//启动定时器，每500毫秒检测一下断链和ip冲突

	s32     GetIndex();
	
    static void InitCriticalSection()
    {
        InitializeCriticalSection( &m_s_tCriticalSection );
    }

	static void DelCriticalSection()
    {
        DeleteCriticalSection( &m_s_tCriticalSection );
    }

	static void CreateCurNetCardName( ) ;
	
	// 获取WiFi的IP地址
	static tstring	GetWiFiIpAddr();      // 获取无线ip
    static tstring	GetWiFiGatewayAddr(); // 获取无线网关
    static tstring	GetWiFiMaskAddr();    // 获取无线子网掩码

protected:
	tstring	GetStringFromArray( const StringArray* pPtr, int nIndex ) const;
	
	/////////////////////////////////////////////
	// Function Prototypes
	//获取当前适配器相关信息
	static DWORD EnumNetworkAdapters( CNetworkAdapter* lpBuffer, ULONG ulSzBuf, LPDWORD lpdwOutSzBuf );

	CString GetCurNetCardName(){ return m_cstrCurNetCardName; }

    BOOL  WinExecAndWait(LPSTR lpExeName, LPSTR lpCmdLine);
public:
    static CRITICAL_SECTION    m_s_tCriticalSection;
    static BOOL32  m_bCheckIP;  // 是否要检查IP冲突和断链检测

private:		
	tstring			m_sName;		// adapter name with the computer.  For human readable name use m_sDesc.
	tstring			m_sDesc;
	tstring			m_sPriWins;
	tstring			m_sSecWins;
	tstring			m_sDefGateway;
	tstring			m_sDhcpAddr;
	TIPINFO			m_sCurIpAddr;	// ip列表中当前使用的ip
	DWORD			m_dwIndex;		// 适配器索引号
	UINT			m_nAdapterType;	
	BOOL			m_bDhcpUsed;
    BOOL            m_bDnsDhcpUsed;
	BOOL			m_bWinsUsed;		
	StringArray		m_DnsAddresses;
	CIpInfoArray	m_IpAddresses;
	StringArray		m_GatewayList;
	time_t			m_tLeaseObtained;
	time_t			m_tLeaseExpires;
	tstring         m_strMAC;
	u32             m_dwIP;        //开始给界面的ip

	s32             m_nIndexNet;

	struct UNNAMED 
	{
        BYTE	ucAddress[ MAX_ADAPTER_ADDRESS_LENGTH ];
		UINT	nLen;
	} m_ucAddress;


    static CNetworkAdapter *m_ptNetParam ;

private:

	PMIB_IFROW   m_pIfRow;  
	PMIB_IFTABLE m_pIfTable;
	static s32          m_nNetWorkCnt;       //网卡数量
	static CString      m_strCurNetWorkName; //当前使用的网卡名称
	u32          m_dwCurIfRowIndex;   //当前使用的IFROW索引
 	static CIPInfoManager* m_pNetWorkAssist;  //用于获取网卡接口信息 
	static CString      m_cstrCurNetCardName; //当前使用的网卡名称[本地连接xxx]，用于netsh使用
public:
	void UpdateUI();
	BOOL GetIfData();

};

#endif //_ADAPTER_INFO_H____