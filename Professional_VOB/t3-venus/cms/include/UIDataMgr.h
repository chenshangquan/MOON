// UIDataMgr.h: interface for the CUIDataMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UIDATAMGR_H__27046F30_49B2_4F4B_8662_2133B7CC3BCC__INCLUDED_)
#define AFX_UIDATAMGR_H__27046F30_49B2_4F4B_8662_2133B7CC3BCC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

enum EMLocalCnsState 
{   
	emLocalCnsIdle = em_CALL_IDLE , //����״̬ ����EmCALLSTATE ���룬 2012.11.14  by yjj  
        emLocalCnsCalling   = em_CALL_CALLING,      //���ں�����
		emLocalCnsConnected = em_CALL_CONNECTED,
        emLocalCallingTimeOut,  //���ж�������ʾ����5�룬Ӧ���л�������״̬
        emLocalCnsInConf,       //�ڻ�����
        emLocalCnsHungup,       //���鿪����localCns �����ߣ�ִ���˹Ҷϲ���
        
	   
		/*��Ҫ�Ҷ�/�뿪����
         Note:��ʾ��ʱ����ʾ �� �Ƿ�Ҫ�Ҷ�/�뿪����ģ���ʾ��
		 ����ʱ���������;���Ѿ����������ʱ����ʾ��Ӧ�Զ����� 
         Bug00113809
		 2012.11.14 �����*/
		emLocalCnsWillHungup,	

		emLocalCnsLocking,      //���鿪����localCns ������,��ǰ����������״̬
};


enum EmWaitType{
	emWaitRegInfo,		//�ȴ�ע����Ϣ
	emWaitConfInfo,  //�ȴ�������Ϣ
	emWaitLoadAddr   //�ȴ������ַ��
};



enum EMTimer{
	emTimerCalling,  
		emTimerRefreshUI
};


enum EM_NETMNGOPT_TYPE      //���ܲ�������
{
	em_NETMNGOPT_ADD,
	em_NETMNGOPT_MODIFY,
	em_NETMNGOPT_IDLE
};

class CUIDataMgr  
{
public:
	virtual ~CUIDataMgr();

    static CUIDataMgr* GetSingleTon();
private:
	CUIDataMgr();


public:
	bool IsPcVersion();//�Ƿ���PC��
    String GetCurSimulateDlgName(){ return m_strSimulateCnsDlgName; }
    void SetCurSimulateDlgName( String strName ){ m_strSimulateCnsDlgName = strName ; }


    String GetCurMainMenuType(){ return m_strSchmMainMenuShow ;}
    void SetCurMainMenuType( String strType ) { m_strSchmMainMenuShow = strType ;}

 	
	/** ������Ļ������Ϣ
	 *  @param[in]  tInfo  ��Ļ������Ϣ
	 *  @return 
	 */
	void SetLockScreenInfo( TLockScreenInfo tInfo );

	/** ��ȡ��Ļ������Ϣ
	 *  @param[out]  TLockScreenInfo ��Ļ������Ϣ
	 *  @return 
	 */
	TLockScreenInfo& GetLockScreenInfo();
 
   
     /**
	* ����:  ��ȡ����cns״̬
	* @param [out]tConfInfo  ����cns�μӵĻ�����Ϣ
	* @return �ɹ�����TRUE,ʧ�ܷ���FALSE
	* @remarks 
	*/
    EMLocalCnsState GetLocalCnsState( ){ return m_emLocalCnsState ;}


    /**
	* ����:  ��ȡ����cns������Ϣ
	* @param [out]tConfInfo  ����cns�μӵĻ�����Ϣ
	* @return �ɹ�����TRUE,ʧ�ܷ���FALSE
	* @remarks 
	*/
    void setLocalCnsState( EMLocalCnsState emState  ){ m_emLocalCnsState = emState; }


    //���õ�ǰ�����Ļ�����
    void SetCurConfName( s8 *pConfName ){ _snprintf(m_achCurConfName, sizeof(m_achCurConfName),"%s" , pConfName); }

    //��ȡ��ǰ�����Ļ�����
    s8*GetCurConfName(){ return m_achCurConfName; }


	/*
	���ܣ�PinYin�����ж�
	������const CString strTextInput: ���жϵĶ���(�û�����PY��)
	      const CString strTextSrc  : �ж�Դ�ֶ���(������)
	����ֵ:��Գɹ� TRUE, ���ʧ�� FALSE;
	*/
	BOOL  HZPYMatchList( const CString strTextInput,  const CString strTextSrc );


    //��ǰ�Ƿ�����״̬
    BOOL  IsUILockScreen() { return m_bUILockScreen; }
    void  SetUILockScreen( BOOL bLockScreen ) { m_bUILockScreen = bLockScreen; }
 
private:
    static CUIDataMgr *m_pThis;

    String  m_strSimulateCnsDlgName;  //��ǰʹ�õ�ģ��᳡�Ľ����������ڽ����л���ʱ�������غ���ʾ
    String  m_strSchmMainMenuShow;    //��ǰ���˵���ʾ��ĳ�ֲ˵��ķ�������

    TLockScreenInfo    m_tLockScreenInfo;

    EMLocalCnsState m_emLocalCnsState;         ///<����cns�ĵ�ǰ״̬
    s8  m_achCurConfName[TP_MAX_ALIAS_LEN];	         ///<��ǰ�����Ļ�������
    
    BOOL    m_bUILockScreen;          //��ǰ�����Ƿ�����
};



//���д���������
extern const String g_stcStrLoginDlg;
extern const String g_stcStrMsgBox;
extern const String g_stcStrMainFrameDlg;
extern  const String g_stcStrMainMenuDlg;
extern  const String g_stcStrToolMenuDlg;
extern  const String g_stcStrSimulateCns1Dlg;			///<һ��ģ��᳡
extern  const String g_stcStrSimulateCns3Dlg;			///<����ģ��᳡
extern  const String g_stcStrSimulateCns5Dlg;			///<����ģ��᳡  
extern  const String g_stcStrLockScreenDlg;			     ///<��������
extern  const String g_stcStrAddrbookDlg;				 ///<��ַ��
extern  const String g_stcStrAddrEditDlg;
extern  const String g_stcStrConftempDlg;				 ///<����ģ���б�
extern  const String g_stcStrCnsLstDlg;                     ///<�᳡�б�
extern  const String g_stcStrCallDlg;                         ///<����
extern  const String g_stcStrConfCnsCtrlDlg;            ///������cns�Ŀ��ƽ���
extern  const String g_stcStrVolumCtrlDlg;
extern  const String g_stcStrAudMixDlg;                   ///<��������
extern  const String g_stcStrTvwDlg;                         ///<����ǽ����
extern  const String g_stcStrConftempEdtDlg ;          ///<����ģ��༭����
extern  const String g_stcStrConfInfoDlg ;                ///<������Ϣ����
extern  const String g_stcStrTitleBarDlg ;                ///<������
extern  const String g_stcStrUserManageDlg ;                ///<�û��������
extern  const String g_stcStrUserdefinedDlg ;                ///<�û��Զ������
extern  const String g_stcStrHungupConfPopDlg ;      //�����б��йҶϻ��鵯����
extern  const String g_stcStrAlarmInfoDlg;
extern  const String g_stcStrIpCfgDlg;
extern  const String g_stcStrConnectCnsDlg;
extern  const String g_stcStrLoginFrame;
extern  const String g_stcStrVideoDlg;
extern  const String g_stcStrFuncLstManageMenu;            //�˵��б����Ĳ˵�
extern  const String g_stcStrScrnDisplayMenu;            //��ѡ���˵�
extern  const String g_strSaveLogDlg;                    //Log download ����
extern  const String g_strWaitingRefreshDlg;
extern  const String g_strDualSrcDlg;

//scheme
extern  const String g_schmMainMenuConfManage;            //mainMenu �Ļ�������Ӧ�Ĳ˵��� 
extern  const String g_schmMainMenuCnsManageInconfBase ;     //mainMenu �Ļ����л᳡�Ļ�������
extern  const String g_schmMainMenuCnsManageInconf;          //mainMenu �Ļ����л᳡�����л�ز���
extern  const string g_schmSimScrPtpConf;                   //ģ������Ե���鷽��
extern  const string g_schmSimScrMiltConf;                   //ģ���������鷽��
extern  const String g_schmMainMenuSysManage ;                //mainMenu ��ϵͳ�����Ӧ�Ĳ˵���
extern  const String g_schmMainMenuCnsManage ;                //mainMenu �Ļ᳡����˵�

extern  const String g_schmMainMenuDisableVideoBtn ;                //mainMenu  ����videobutton
extern  const String g_schmMainMenuEnableVideoBtn ;                //mainMenu ��videobutton

extern  const String g_stcStrCallingBox ;                   //���й����еĶ���dlg

extern  const String g_schmMainFrameCnsBkg;                           //ģ��᳡����
extern  const String g_schmMainFrameBlankBkg ;                          //�հױ���

extern  const String g_strMainFrameSimulateBkg;
extern  const String g_strMainFrameSysCfgBkg;                        //ϵͳ���õı���
extern  const String g_strMainFrameConfManageBkg;                    //�������ı���
extern  const String g_strMainFrameLoginBkg;    

extern const String g_strFuncLstData;                      //�����б��Ӧ������ xml

#define  CNSCONF_FILE_PATH		"/usr/conf/"				//̨����λ��

#define UIDATAMGR CUIDataMgr::GetSingleTon()   
#endif // !defined(AFX_UIDATAMGR_H__27046F30_49B2_4F4B_8662_2133B7CC3BCC__INCLUDED_)
