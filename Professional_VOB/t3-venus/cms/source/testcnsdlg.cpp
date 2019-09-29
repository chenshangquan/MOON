// testcnsdlg.cpp : implementation file
//

#include "stdafx.h"
#include "cms.h"
#include "testcnsdlg.h"
#include "tpsys.h"
#include "testdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestCnsDlg dialog


CTestCnsDlg::CTestCnsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestCnsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestCnsDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CTestCnsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestCnsDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_SIP_IPADDRESS, m_cSipIP);
	DDX_Control(pDX, IDC_LISTADDR, m_listAddr);
	DDX_Text(pDX, IDC_STATIC_RESULT, m_strResult);
	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestCnsDlg, CDialog)
	//{{AFX_MSG_MAP(CTestCnsDlg)
	ON_BN_CLICKED(IDC_LOGIN, OnLogin)
	ON_BN_CLICKED(IDC_SIP_CFG, OnSipCfg)	
	ON_MESSAGE( UI_CNS_CONNECTED, OnConnectCns )
	ON_BN_CLICKED(IDC_SETCNSIP, OnSetCnsIp)
	ON_BN_CLICKED(IDC_BTN_ADDENTRY, OnAddEntry)
	ON_BN_CLICKED(IDC_BTN_MODIFYENTRY, OnModifyEntry)
	ON_BN_CLICKED(IDC_BTN_DELENTRY, OnDeleteEntry)
	ON_MESSAGE( UI_CNS_ADDRBOOK_CHANGED, UpdateAddrBook )
	ON_BN_CLICKED(IDC_UITEST, OnUiTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestCnsDlg message handlers

BOOL CTestCnsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
//	REG_MSGHANDLER( UI_CNS_CONNECTED );
//	REG_MSGHANDLER( UI_CNS_ADDRBOOK_CHANGED );

	//m_pcComInterface = CCommonInterface::GetCommIF();

	m_cSipIP.SetAddress( ntohl( inet_addr("172.16.160.104") ) );


	m_listAddr.SetExtendedStyle(m_listAddr.GetExtendedStyle()|LVS_EX_SUBITEMIMAGES|LVS_EX_FULLROWSELECT);
	m_listAddr.InsertColumn(0, "条目名称", LVCFMT_LEFT, 100);
	m_listAddr.InsertColumn(1, "别名", LVCFMT_LEFT, 100);
	m_listAddr.InsertColumn(2, "IP", LVCFMT_LEFT, 100);
	m_listAddr.InsertColumn(3, "E164 号", LVCFMT_LEFT, 80);


	//UIFactory
	//new CSystem( "System.xml" );
//	LogicTest* pTest = new LogicTest();
//	REG_GOBAL_MEMBER_FUNC( "Login::Click", LogicTest::Test, pTest, LogicTest );
	//REG_WINDOW_FACTORY( "Window", CWndFactory );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CTestCnsDlg::OnLogin()
{
	u32 dwAddress = 0;
	dwAddress = ntohl( inet_addr("172.16.160.104") );
	//u16 wRe = ComInterface->ConnectCns( dwAddress, 60002, "ha", "" );		
}

void CTestCnsDlg::OnSipCfg() 
{
	// TODO: Add your control notification handler code here
	u32 dwAddress = 0;
	m_cSipIP.GetAddress(dwAddress);
	TTPSipRegistrarCfg tSipReg;
	tSipReg.dwRegIP = htonl(dwAddress);
	u16 wRe = ComInterface->CnsRegSipService( tSipReg );	
}

void CTestCnsDlg::OnCancel() 
{
	// TODO: Add extra cleanup here	
	u16 wRe = ComInterface->DisConnect( emEqCns );	

	CDialog::OnCancel();
}



LRESULT CTestCnsDlg::OnConnectCns(WPARAM wParam, LPARAM lParam)
{
	m_strResult = "Login OK";
	UpdateData(FALSE);
	return 0;
}

void CTestCnsDlg::OnSetCnsIp() 
{
	// TODO: Add your control notification handler code here
	u32 dwAddress = 0;
	m_cSipIP.GetAddress(dwAddress);
	u32 dwIp = htonl(dwAddress);
//	u16 wRe = ComInterface->SetCnsIp( dwIp );
}

void CTestCnsDlg::OnAddEntry() 
{
	// TODO: Add your control notification handler code here
	CAddrEntry cEntry;
	TADDRENTRYINFO tEntryInfo;
    ZeroMemory(&tEntryInfo, sizeof(TADDRENTRYINFO));
	u32 dwAddress = 0;
	m_cSipIP.GetAddress(dwAddress);
	tEntryInfo.dwMtIpAddr = htonl(dwAddress);
	strcpy(tEntryInfo.achEntryName, "160.104");
	cEntry.SetEntryInfo( tEntryInfo );
	u16 wRe = ComInterface->AddEntry( cEntry );
}

void CTestCnsDlg::OnModifyEntry() 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listAddr.GetFirstSelectedItemPosition();
	
    if (pos != NULL) 
    {
        s32 nItem = m_listAddr.GetNextSelectedItem(pos);
        u32 dwIndex = m_listAddr.GetItemData(nItem);
				
		CAddrBook cAddrBook = ComInterface->GetAddrBook();
		CAddrEntry cAddrEntry;
		u32 dwRet = cAddrBook.GetAddrEntry(&cAddrEntry, dwIndex);
		if (dwRet != INVALID_INDEX) 
        {
			cAddrEntry.SetEntryName( "hahaha" );
			int nRet = ComInterface->ModifyEntry(cAddrEntry);
		}
    }
}

void CTestCnsDlg::OnDeleteEntry() 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listAddr.GetFirstSelectedItemPosition();
	
    while (pos) 
    {
        s32 nItem = m_listAddr.GetNextSelectedItem(pos);
        u32 dwIndex = m_listAddr.GetItemData(nItem);
		int nRet = ComInterface->DeleteEntry(dwIndex);
    }
}


LRESULT CTestCnsDlg::UpdateAddrBook(WPARAM wParam, LPARAM lParam)
{
	CAddrBook  cAddrBook = ComInterface->GetAddrBook();
	m_listAddr.DeleteAllItems(); 

	s8 aszEntryName[MAX_NAME_LEN + 1] = _T("");     //条目名称
	s8 aszMTAlias[MAX_H323ALIAS_LEN + 1] = _T("");  //H323名称
	s8 aszMTNumber[MAX_E164NUM_LEN + 1] = _T("");   //E164号码
	s8 aszMTIP[MAX_IPADDR_LEN + 1] = _T("");        //IP

	//获取基本条目个数
	u32 dwUsedSize = cAddrBook.GetAddrEntryUsedSize();
	
	u32 dwIndex = 0;
	s32 nIndex = 0;
	CAddrEntry cAddrEntry;
	dwIndex = cAddrBook.GetFirstAddrEntry( &cAddrEntry );
	while ( nIndex < dwUsedSize )
	{
		if ( dwIndex != INVALID_INDEX )
		{	
			cAddrEntry.GetEntryName( aszEntryName, cAddrEntry.GetEntryNameLen() + 1 );
			cAddrEntry.GetMtAlias( aszMTAlias, cAddrEntry.GetMtAliasLen() + 1 );
			cAddrEntry.GetMtNumber( aszMTNumber, cAddrEntry.GetMtNumberLen() + 1 );
			cAddrEntry.GetMtIpAddr( aszMTIP, MAX_IPADDR_LEN + 1 );
			
			m_listAddr.InsertItem(nIndex, aszEntryName); 
			//m_listAddr.SetItemText(nIndex, 0, aszEntryName);
			m_listAddr.SetItemText(nIndex, 1, aszMTAlias);
			m_listAddr.SetItemText(nIndex, 2, aszMTIP);
			m_listAddr.SetItemText(nIndex, 3, aszMTNumber);
			m_listAddr.SetItemData(nIndex, dwIndex );
			
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
	UpdateData(TRUE);

	m_strResult = "地址簿已更新";
	UpdateData(FALSE);
	return 0;
}

void CTestCnsDlg::OnOK() 
{
	// TODO: Add extra validation here
	CDialog::OnOK();
}

void CTestCnsDlg::OnUiTest() 
{
	// TODO: Add your control notification handler code here
	IWndTree* pTree2 = const_cast<IWndTree*>(CWindowManage::GetSingletonPtr()->GetWindowTree( "AddrBookDlg" ));
	
	//IWndTree* pTree  = const_cast<IWndTree*>(UIManagePtr->GetWindow( "AddrBookDlg"));
}
