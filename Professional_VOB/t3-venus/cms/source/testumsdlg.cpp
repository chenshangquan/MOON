// testumsdlg.cpp : implementation file
//

#include "stdafx.h"
#include "cms.h"
#include "testumsdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestUmsDlg dialog


CTestUmsDlg::CTestUmsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestUmsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestUmsDlg)
	m_edtUserName = _T("");
	m_edtPswd = _T("");
	m_stcOpResult = _T("");
	m_edtName = _T("");
	m_edtTemplateID = _T("");
	//}}AFX_DATA_INIT
}


void CTestUmsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestUmsDlg)
	DDX_Control(pDX, IDC_LST_CONF_CNS, m_lstConfCns);
	DDX_Control(pDX, IDC_LST_CONF, m_lst_conf);
	DDX_Control(pDX, IDC_LST_TEMPLATE, m_lstConfTemp);
	DDX_Control(pDX, IDC_LST_USER, m_lstUser);
	DDX_Control(pDX, IDC_IP_UMS, m_ipCtrlUms);
	DDX_Text(pDX, IDC_EDT_NAME, m_edtUserName);
	DDX_Text(pDX, IDC_EDT_PSWD, m_edtPswd);
	DDX_Text(pDX, IDC_STC_OPERATE_RESULT, m_stcOpResult);
	DDX_Text(pDX, IDC_EDT_USERNAME, m_edtName);
	DDX_Text(pDX, IDC_EDT_TEMPLATEID, m_edtTemplateID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTestUmsDlg, CDialog)
	//{{AFX_MSG_MAP(CTestUmsDlg)
	ON_BN_CLICKED(IDC_BTN_LOGIN, OnBtnLogin)
	ON_MESSAGE( UI_UMS_DISCONNECTED,   OnLinkBreak )
	ON_MESSAGE( UI_UMS_CMD_TIMEOUT,   OnTimeOut )
	ON_MESSAGE( UI_UMS_CONNECTED,   OnConnectUms )
	ON_MESSAGE( UI_UMS_OPERATE_CONFTEMP_RET, OnOpTemplateRsp)
	ON_MESSAGE( UI_UMS_REFRESH_CONFTEMPLATE_LIST, OnResfreshTemplate)
	ON_MESSAGE( UI_UMS_OPERATE_USER_RET, OnOpUserRsp)
	ON_MESSAGE( UI_UMS_REFRESH_USER_LIST, OnResfreshUser)
	ON_MESSAGE( UI_UMS_REFRESH_CONF_LIST, OnResfreshConf)
	ON_MESSAGE( UI_UMS_REFRESH_CONFCNS_LIST, OnResfreshConfCns)
	ON_MESSAGE( UI_UMS_REFRESH_CONFPOLL_LIST, OnResfreshConfPoll)
	ON_MESSAGE( UI_UMS_REFRESH_CONFAUDMIX_LIST, OnResfreshConfAudmix)
	ON_BN_CLICKED(IDC_BTN_ADD_TEMPLATE, OnBtnAddTemplate)
	ON_BN_CLICKED(IDC_BTN_DELETE_TEMPLATE, OnBtnDeleteTemplate)
	ON_BN_CLICKED(IDC_BTN_UPDATE_TEMPLATE, OnBtnUpdateTemplate)
	ON_BN_CLICKED(IDC_BTN_ADD_USER, OnBtnAddUser)
	ON_BN_CLICKED(IDC_BTN_DELETE_USER, OnBtnDeleteUser)
	ON_BN_CLICKED(IDC_BTN_UPDATE_USER, OnBtnUpdateUser)
	ON_BN_CLICKED(IDC_BTN_HANGUP_CNS, OnBtnHangupCns)
	ON_BN_CLICKED(IDC_BTN_HANGUP_CONF, OnBtnHangupConf)
	ON_BN_CLICKED(IDC_BTN_REMOVE_CNS, OnBtnRemoveCns)
	ON_BN_CLICKED(IDC_BTN_START_CONF, OnBtnStartConf)
	ON_BN_CLICKED(IDC_BTN_SHOW_AUDMIX, OnBtnShowAudmix)
	ON_BN_CLICKED(IDC_BTN_SHOW_POLL, OnBtnShowPoll)
	ON_BN_CLICKED(IDC_BTN_SHOW_CNS, OnBtnShowCns)
	ON_BN_CLICKED(IDC_BTN_REG_SIP, OnBtnRegSip)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestUmsDlg message handlers




BOOL CTestUmsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	RegMsg();
	
	m_ipCtrlUms.SetAddress(172,16,160,102);
    m_edtUserName = "admin";
	m_edtPswd = "admin";
    
	LVCOLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH | LVCF_ORDER;
	lvc.fmt = LVCFMT_LEFT; //左对齐
	CString szColUmn[2] = {"templateID","templateName"};
	for (int i = 0; i < 2; i++)
	{
		lvc.pszText = szColUmn[i].GetBuffer(szColUmn[i].GetLength());
		lvc.iSubItem = i;
		lvc.iOrder = i;
		lvc.cx = 200;
		m_lstConfTemp.InsertColumn(i, &lvc);
	}



	CString szUserColUmn[2] = {"UserName","Pswd"};
	for ( i = 0; i < 2; i++)
	{
		lvc.pszText = szUserColUmn[i].GetBuffer(szUserColUmn[i].GetLength());
		lvc.iSubItem = i;
		lvc.iOrder = i;
		lvc.cx = 200;
		m_lstUser.InsertColumn(i, &lvc);
	}
	
	CString szConf[2] ={ "confID","confName" };
	for ( i=0; i<2;i++)
	{
		lvc.pszText = const_cast<char*>((LPCSTR)szConf[i]);
		lvc.iSubItem = i;
		lvc.iOrder = i;
		lvc.cx = 100;
		m_lst_conf.InsertColumn(i, &lvc);
	}
	

	CString szList[2] ={ "ID","Name" };
	for ( i=0; i<2;i++)
	{
		lvc.pszText = const_cast<char*>((LPCSTR)szList[i]);
		lvc.iSubItem = i;
		lvc.iOrder = i;
		lvc.cx = 100;
		m_lstConfCns.InsertColumn(i, &lvc);
	}
	
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CTestUmsDlg::RegMsg()
{   
// 	REG_MSGHANDLER(	UI_UMS_DISCONNECTED); 
// 
// 	REG_MSGHANDLER( UI_UMS_CMD_TIMEOUT);
// 
// 	REG_MSGHANDLER( UI_UMS_CONNECTED);
// 
// 	REG_MSGHANDLER( UI_UMS_OPERATE_CONFTEMP_RET);
// 	REG_MSGHANDLER( UI_UMS_REFRESH_CONFTEMPLATE_LIST);
// 
// 	REG_MSGHANDLER( UI_UMS_OPERATE_USER_RET);
// 	REG_MSGHANDLER( UI_UMS_REFRESH_USER_LIST);
// 
// 	REG_MSGHANDLER( UI_UMS_REFRESH_CONF_LIST);
// 	REG_MSGHANDLER( UI_UMS_REFRESH_CONFCNS_LIST);
// 	REG_MSGHANDLER( UI_UMS_REFRESH_CONFAUDMIX_LIST);
// 	REG_MSGHANDLER( UI_UMS_REFRESH_CONFPOLL_LIST);
	
	 
}


void CTestUmsDlg::OnBtnLogin() 
{
	UpdateData();
	u32 dwAddress = 0;
	m_ipCtrlUms.GetAddress( dwAddress );
	u16 re = ComInterface->Connect( dwAddress,  60001, m_edtUserName, m_edtPswd);
	
	if ( re == NO_ERROR ) 
	{
		m_stcOpResult = "connecting ums  !" ;  
	}
	else
	{
		m_stcOpResult = "connecting ums error !" ;  
	}
	
	UpdateData(FALSE);
}


LRESULT CTestUmsDlg::OnConnectUms(  WPARAM wParam, LPARAM lParam ) 
{
	CString msg;
	msg.Format("login Error Code:%d", wParam);
	m_stcOpResult = msg;
	UpdateData(FALSE);
	return 0;
}


 
void CTestUmsDlg::OnBtnAddTemplate() 
{  
   UpdateData();

   TTPConfTemplate  tConfTem;
 
   sprintf(tConfTem.m_achConfName,"%s_%s" , "add", m_edtTemplateID );
   sprintf(tConfTem.m_achConfE164,"%s" , m_edtTemplateID );
   
   
   tConfTem.m_atEpList.Add(tp_Alias_h323,"cns1");
   tConfTem.m_atEpList.Add(tp_Alias_h323,"cns2");
   tConfTem.m_tTurnList.m_wNum=1;
   tConfTem.m_tTurnList.m_awList[0]=0;
 
   u16 re = ComInterface->AddConfTemplate(tConfTem);
   TRACE("\nAdd confTemplate result:%d\n",re);
}

void CTestUmsDlg::OnBtnDeleteTemplate() 
{
	// TODO: Add your control notification handler code here
   
    POSITION pos = m_lstConfTemp.GetFirstSelectedItemPosition();
    int nIndex = m_lstConfTemp.GetNextSelectedItem(pos) ;
    char pID[50] = {0};
	m_lstConfTemp.GetItemText(nIndex,0,pID,50);
    int id = atoi(pID);
	u16 re = ComInterface->DeleteConfTemplate(id);
   TRACE("\nDelete confTemplate result:%d\n",re);
}

void CTestUmsDlg::OnBtnUpdateTemplate() 
{  
	TTPConfTemplate  tConfTem;

	POSITION pos = m_lstConfTemp.GetFirstSelectedItemPosition();
    int nIndex = m_lstConfTemp.GetNextSelectedItem(pos) ;
    char pID[50] = {0};
	m_lstConfTemp.GetItemText(nIndex,0,pID,50);
    tConfTem.m_wID  = atoi(pID);
	 
	sprintf(tConfTem.m_achConfName,"%s_%d" , "Update",tConfTem.m_wID);
  
   u16 re = ComInterface->UpdateConfTemplate(tConfTem);
   TRACE("\nModify confTemplate result:%d\n",re);
	
}



void CTestUmsDlg::OnBtnAddUser()
{  
	UpdateData();
	CUserFullInfo tUser;
	tUser.SetName( const_cast<s8*>((LPCTSTR) m_edtName ));
	tUser.SetPassword(tUser.GetName());
	//tUser.SetEncryptedPassword(tUser.GetName());
	u16 re = ComInterface->AddUser(tUser);
 
    TRACE("\nAdd  User result:%d\n",re);
    
} 


void CTestUmsDlg::OnBtnDeleteUser()
{
	POSITION pos = m_lstUser.GetFirstSelectedItemPosition();
    int nIndex = m_lstUser.GetNextSelectedItem(pos) ;
    char pName[32] = {0};
	m_lstUser.GetItemText(nIndex,0,pName,32);

	CUserFullInfo tUser;
	tUser.SetName( pName );
	tUser.SetPassword(pName);
    //tUser.SetEncryptedPassword(pName);
	u16 re = ComInterface->DeleteUser(tUser);
    TRACE("\nDelete User result:%d\n",re);
	
    
}

void CTestUmsDlg::OnBtnUpdateUser()
{   
	UpdateData();

	POSITION pos = m_lstUser.GetFirstSelectedItemPosition();
    int nIndex = m_lstUser.GetNextSelectedItem(pos) ;
    char pName[200] = {0};
	m_lstUser.GetItemText(nIndex,0,pName,sizeof(pName));
 
	CUserFullInfo tUser;
	tUser.SetName(pName);
	tUser.SetPassword( const_cast<s8*>((LPCTSTR) m_edtName ));
	//tUser.SetEncryptedPassword(const_cast<s8*>((LPCTSTR) m_edtName ));
	u16 re = ComInterface->UpdateUser(tUser);
    TRACE("\nupdate User result:%d\n",re);
}
 


 

void CTestUmsDlg::OnBtnHangupCns() 
{
	UpdateData();
	
	POSITION pos = m_lst_conf.GetFirstSelectedItemPosition();
    int nIndex = m_lst_conf.GetNextSelectedItem(pos) ;
    char pConfID[32] = {0};
	m_lst_conf.GetItemText(nIndex,0,pConfID,sizeof(pConfID));
    u16 wConfID = 0;
	wConfID = atoi(pConfID);
	
	TConfEpID t;
	t.m_wConfID = wConfID;
	
	pos = m_lstConfCns.GetFirstSelectedItemPosition();
    nIndex = m_lstConfCns.GetNextSelectedItem(pos) ;
	char pCnsID[32] = {0};
	m_lstConfCns.GetItemText(nIndex,0, pCnsID,sizeof(pCnsID)); 
	u16 wCnsID = 0;
	wCnsID = atoi(pCnsID);
    t.m_wEpID =wCnsID; 

	u16 wRe = ComInterface->HangupCNS(t);
}

void CTestUmsDlg::OnBtnHangupConf() 
{
	UpdateData(); 
	POSITION pos = m_lst_conf.GetFirstSelectedItemPosition();
    int nIndex = m_lst_conf.GetNextSelectedItem(pos) ;
    char pConfID[32] = {0};
	m_lst_conf.GetItemText(nIndex,0,pConfID,sizeof(pConfID));
    u16 wConfID = 0;
	wConfID = atoi(pConfID);  
     
	u16 wRe = ComInterface->HangupConf(wConfID);
	
}

void CTestUmsDlg::OnBtnRemoveCns() 
{
	UpdateData();
	
	POSITION pos = m_lst_conf.GetFirstSelectedItemPosition();
    int nIndex = m_lst_conf.GetNextSelectedItem(pos) ;
    char pConfID[32] = {0};
	m_lst_conf.GetItemText(nIndex,0,pConfID,sizeof(pConfID));
    u16 wConfID = 0;
	wConfID = atoi(pConfID);
	
	TConfEpID t;
	t.m_wConfID = wConfID;
	
	pos = m_lstConfCns.GetFirstSelectedItemPosition();
    nIndex = m_lstConfCns.GetNextSelectedItem(pos) ;
	char pCnsID[32] = {0};
	m_lstConfCns.GetItemText(nIndex,0, pCnsID,sizeof(pCnsID)); 
	u16 wCnsID = 0;
	wCnsID = atoi(pCnsID);
    t.m_wEpID =wCnsID;
	u16 wRe = ComInterface->RemoveCNS(t);
}

void CTestUmsDlg::OnBtnStartConf() 
{
	POSITION pos = m_lstConfTemp.GetFirstSelectedItemPosition();
    int nIndex = m_lstConfTemp.GetNextSelectedItem(pos) ;
    char pID[50] = {0};
	m_lstConfTemp.GetItemText(nIndex,0,pID,50);
    u16 wConfID =  atoi(pID);	
	ComInterface->StartTemplateConf(wConfID );
}



LRESULT CTestUmsDlg::OnLinkBreak(  WPARAM wParam, LPARAM lParam )
{ 
	m_stcOpResult = "连接断开";
	UpdateData(FALSE);
	return NO_ERROR;
}

LRESULT CTestUmsDlg::OnTimeOut(  WPARAM wParam, LPARAM lParam ) 
{
	m_stcOpResult = "处理超时";
	UpdateData(FALSE);
	return NO_ERROR;
}

LRESULT CTestUmsDlg::OnOpTemplateRsp(  WPARAM wParam, LPARAM lParam )
{
	CString msg;
	msg.Format("OpTemplate Error Code:%d, templateID:%d", wParam,lParam);
	m_stcOpResult = msg;
	UpdateData(FALSE);
	return NO_ERROR;
}



LRESULT CTestUmsDlg::OnResfreshTemplate(  WPARAM wParam, LPARAM lParam )
{ 
	m_lstConfTemp.DeleteAllItems();  
	const TplArray<TTPConfTemplate>* pList = ComInterface->GetConfTemplateList();
	if ( NULL == pList )
	{  
		return FALSE;
	}
	
	int nCnt = pList->Size();
	for ( int i=0; i<nCnt; i++) 
	{
		int nIndex = m_lstConfTemp.GetItemCount();
		char id[2] = {0};
		_itoa(pList->GetAt(i).m_wID,id,10);
		m_lstConfTemp.InsertItem(nIndex, id  );  
		m_lstConfTemp.SetItemText(nIndex, 1,  pList->GetAt(i).m_achConfName); 
		
	}
	
	return NO_ERROR;
}



LRESULT CTestUmsDlg::OnOpUserRsp(  WPARAM wParam, LPARAM lParam )
{
	CString msg;
	msg.Format("User Error Code:%d, templateID:%d", wParam,lParam);
	m_stcOpResult = msg;
	UpdateData(FALSE);
	return NO_ERROR;
}


LRESULT CTestUmsDlg::OnResfreshUser(  WPARAM wParam, LPARAM lParam )
{
	m_lstUser.DeleteAllItems();  
	const TplArray<CUserFullInfo>* pList = ComInterface->GetUserList();
	if ( NULL == pList )
	{  
		return FALSE;
	}
	
	int nCnt = pList->Size();
	for ( int i=0; i<nCnt; i++) 
	{
		int nIndex = m_lstUser.GetItemCount();
		char* Name = pList->GetAt(i).GetName() ;
		m_lstUser.InsertItem(nIndex, Name  );  
		m_lstUser.SetItemText(nIndex, 1,  pList->GetAt(i).GetPassword()); 
		
	}
	
	return NO_ERROR;
}

LRESULT CTestUmsDlg::OnResfreshConf(  WPARAM wParam, LPARAM lParam )
{
    m_lst_conf.DeleteAllItems(); 
	const TplArray<TCMSConf >* pList;// = ComInterface->GetConfList();
	if ( NULL == pList )
	{  
		return FALSE;
	}
	
	int nCnt = pList->Size();
	for ( int i=0; i<nCnt; i++) 
	{
		int nIndex = m_lst_conf.GetItemCount();
		char cID[32] = {0};
		 printf(cID,"%d", pList->GetAt(i).m_wConfID);
		m_lst_conf.InsertItem(nIndex, cID  );  
		m_lst_conf.SetItemText(nIndex, 1, pList->GetAt(i).m_achConfName); 
		 
	}
	return NO_ERROR;
	
}
LRESULT CTestUmsDlg::OnResfreshConfCns(  WPARAM wParam, LPARAM lParam ) 
{  
	u16 wID = (u16)wParam;
	CString msg;
	msg.Format("refresh cns List, templateID:%d", wID);
	m_stcOpResult = msg;
	UpdateData(FALSE);
	return NO_ERROR;
}


LRESULT CTestUmsDlg::OnResfreshConfPoll(  WPARAM wParam, LPARAM lParam ) 
{
	u16 wID = (u16)wParam;
	CString msg;
	msg.Format("refresh poll List, templateID:%d", wID);
	m_stcOpResult = msg;
	UpdateData(FALSE);
	return NO_ERROR;
}
LRESULT CTestUmsDlg::OnResfreshConfAudmix(  WPARAM wParam, LPARAM lParam )
{
	u16 wID = (u16)wParam;
	CString msg;
	msg.Format("refresh Audmix list, templateID:%d", wID);
	m_stcOpResult = msg;
	UpdateData(FALSE);
	return NO_ERROR;
}



void CTestUmsDlg::OnBtnShowAudmix() 
{
	m_lstConfCns.DeleteAllItems();  
	UpdateData();
	
	POSITION pos = m_lst_conf.GetFirstSelectedItemPosition();
    int nIndex = m_lst_conf.GetNextSelectedItem(pos) ;
    char pID[200] = {0};
	m_lst_conf.GetItemText(nIndex,0,pID,sizeof(pID));
    int nConfID = atoi(pID);
	
	
	TCMSConf* pTConf = ComInterface->GetConfByID( nConfID );
    if ( pTConf == NULL ) 
	{
		return;
    }
	
	
// 	int nCnt = pTConf->m_tplAudmixList.Size();
// 	for ( int i=0; i<nCnt; i++) 
// 	{
// 		int nIndex = m_lstConfCns.GetItemCount();
// 		u16  wCnsID =  pTConf->m_tplAudmixList.GetAt(i);
// 		char pID[32] = {0};
// 		sprintf( pID,"%d",wCnsID );
// 	 
// 		m_lstConfCns.InsertItem(nIndex, pID  );   
// 	}
	 
	
}

void CTestUmsDlg::OnBtnShowPoll() 
{
	m_lstConfCns.DeleteAllItems();  
	UpdateData();
	
	POSITION pos = m_lst_conf.GetFirstSelectedItemPosition();
    int nIndex = m_lst_conf.GetNextSelectedItem(pos) ;
    char pID[200] = {0};
	m_lst_conf.GetItemText(nIndex,0,pID,sizeof(pID));
    int nConfID = atoi(pID);
	
	
	TCMSConf* pTConf = ComInterface->GetConfByID( nConfID );
    if ( pTConf == NULL ) 
	{
		return;
    }
	
	
	int nCnt = pTConf->m_tplPollList.Size();
	for ( int i=0; i<nCnt; i++) 
	{
		int nIndex = m_lstConfCns.GetItemCount();
		u16  wCnsID =  pTConf->m_tplPollList.GetAt(i);
		char pID[32] = {0};
		sprintf( pID,"%d",wCnsID );
		
		m_lstConfCns.InsertItem(nIndex, pID  );   
	}
	 
}

void CTestUmsDlg::OnBtnShowCns() 
{  
	m_lstConfCns.DeleteAllItems();  
	UpdateData();
	
	POSITION pos = m_lst_conf.GetFirstSelectedItemPosition();
    int nIndex = m_lst_conf.GetNextSelectedItem(pos) ;
    char pID[200] = {0};
	m_lst_conf.GetItemText(nIndex,0,pID,sizeof(pID));
    int nConfID = atoi(pID);

	
	TCMSConf* pTConf = ComInterface->GetConfByID( nConfID );
    if ( pTConf == NULL ) 
	{
		return;
    }
    
	int nCnt = pTConf->m_tplCnsList.Size();
	for ( int i=0; i<nCnt; i++) 
	{
		int nIndex = m_lstConfCns.GetItemCount();
		u16  wCnsID =  pTConf->m_tplCnsList.GetAt(i).m_wEpID;
		char pID[32] = {0};
		sprintf( pID,"%d",wCnsID );
		char* Name = pTConf->m_tplCnsList.GetAt(i).m_achRoomName ;
		m_lstConfCns.InsertItem(nIndex, pID  );  
		m_lstConfCns.SetItemText(nIndex, 1, Name ); 
		
	}
	
 
}

 
void CTestUmsDlg::OnBtnRegSip() 
{ 
 	TTPSipRegistrarCfg t;
   
 	 u16 wRe = ComInterface->UmsRegSipService( t );
 
}

 

LRESULT CTestUmsDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::DefWindowProc(message, wParam, lParam);
}
