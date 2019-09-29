 /*****************************************************************************
ģ����      : CMS����̨
�ļ���      : MainWndLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: �������߼���Ԫ 
˵��       �� ���Ӧ��xml�а��������dlg�����˵�dlg ����ַ��������ģ���б��������ۣ�����ǽ���� �������䣬������
����        : �����
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2011/5/24  1.0          �����      ����
******************************************************************************/

#if !defined(AFX_MAINWNDLOGIC_H__336C3B31_4484_4F36_9B80_1BA09DB004FA__INCLUDED_)
#define AFX_MAINWNDLOGIC_H__336C3B31_4484_4F36_9B80_1BA09DB004FA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"


class CMainFrameLogic :public CWndLogicBase//, public CProcessMsgBase<CMainFrameLogic>// ,public Singleton<CMainFrameLogic>
{
public:   
	 static CMainFrameLogic*  GetLogicPtr();
     CMainFrameLogic();
	 virtual ~CMainFrameLogic();  
public:  
   
	virtual bool RegCBFun();

	virtual bool UnRegFunc( );
 
    virtual bool InitWnd( const IArgs & arg );
   
 
    /**	 
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear() ;

/**	 
  * ����:  ���������
  * @return  bool
  * @remarks  
  */
    bool BtnToolMenuClick( const IArgs & arg );
   
  /**	 
  * ����:  �������
  * @return   bool
  * @remarks  
  */
    bool BtnLockScreenClick( const IArgs & arg );

   
    /**	 
  * ����:  �����ַ��
  * @return   bool
  * @remarks  
  */
	bool BtnCnsManageClick( const IArgs & arg );


/**	 
  * ����:  �����ַ��
  * @return   bool
  * @remarks  
  */
	bool BtnAddrbookClick( const IArgs & arg );
 
   
 /**	 
  * ����:  �������ģ��
  * @return   bool
  * @remarks  
  */
	bool BtnConftempClick( const IArgs & arg );
 
   
	/**	 
  * ����:  ����᳡�б�
  * @return   bool
  * @remarks  
  */
	bool BtnCnsListClick( const IArgs & arg );


	/**	 
  * ����:  �����������
  * @return   bool
  * @remarks  
  */
	bool BtnMixAudClick( const IArgs & arg );

/**	 
  * ����:  �������ǽ
  * @return   bool
  * @remarks  
  */
	bool BtnTvwClick( const IArgs & arg );


 /**	 
  * ����:  ��������ַ��
  * @return   bool
  * @remarks  
  */
	bool BtnAddrbookManageClick( const IArgs & arg );


  /**	 
  * ����:  �������ģ��༭but
  * @return   bool
  * @remarks  
  */
	bool BtnConftempManageClick( const IArgs & arg );


 /**	 
  * ����:  ���������Ϣbut
  * @return   bool
  * @remarks  
  */
    bool BtnConfInfoClick( const IArgs & arg );


	bool BtnSysCfgClick( const IArgs & arg );

    /**	 
  * ����:  ����û�����button
  * @return   bool
  * @remarks  
  */
    bool BtnUserManageClick( const IArgs & arg );


	/**	 
	* ����:  ����Զ���button
	* @return   bool
	* @remarks  
	*/
    bool BtnUserDefineClick( const IArgs & arg );

	/**	 
	* ����:  ����澯button
	* @return   bool
	* @remarks  
	*/
	bool BtnAlarmClick( const IArgs & arg );

	/**	 
	* ����:  ��wnd���Ե��޸ı��浽�ļ�
	* @return   bool
	* @remarks  
	*/
    bool BtnSaveToFileClick( const IArgs & arg );


    //��ʾ����ͼ�����
    bool BtnVideoClick( const IArgs & args );

	/**	 
	* ����:  �������˵�����
	* @return   
	* @remarks ��������Ҫ�ѡ�����ģ���б�ť��ת��Ϊ���᳡�б�ť����
			   ͬʱ"  ����ǽ����"�͡������顱����button��Ϊ���ã�
			   �����ڻ��������������button�ûҽ���
	*/
	void UpdateMainMenuDlg();


    //ˢ�º���״̬
    void  RefreshCallState();

	bool OnGrabLogin( const IArgs & arg );

	void UpdateAlarmImg();

    //�Ҷϻ���������Ҷ��Լ�ums�������������Բ�������
    void HideAllDlg();
  

   
protected:

	virtual void RegMsg(); 
	virtual void UnRegMsg();
  
    void ShowVideo( BOOL32 bFullScreen );
private:
  
  
 /**	 
  * ����:  ����ģ��᳡����
  * @return   
  * @remarks  ����cns��������ѡ����Ӧ��xml������
  */
   void CreateSimulateCnsDlg();

   void UpdateSimulateCnsDlg();

   /**	 
 arks  ���δ���ӣ��򷵻ص���½����
  */
   BOOL32 CheckLinkState();

   void  CreateWnd();

   void  InitConfMenu();

   void  UpdateConfMenu( EM_ConfType emConfType );
 
protected: 

	HRESULT OnStratConftempRsp( WPARAM wparam, LPARAM lparam);
	HRESULT OnInvitCnsRsp( WPARAM wparam, LPARAM lparam);
 
	HRESULT OnConfStateNotify( WPARAM wparam, LPARAM lparam );
    HRESULT OnHungupP2pConfNotify( WPARAM wparam, LPARAM lparam );
	HRESULT	OnCnsInfoNotify( WPARAM wparam, LPARAM lparam );
	HRESULT OnCnsOfflineNotify( WPARAM wparam, LPARAM lparam );
     
    HRESULT	OnRefreshConfLst( WPARAM wparam, LPARAM lparam );
    HRESULT	OnRefreshConfCnsLst( WPARAM wparam, LPARAM lparam );
    HRESULT OnHungupConf( WPARAM wparam, LPARAM lparam );
  
    //���˻��Ѿ�����һ���ط���¼
    HRESULT GrabLoginNotify( WPARAM wparam, LPARAM lparam );

    //���ж�����ʾ �Ѵﵽ5���ӣ����᳡��δ����
    HRESULT CallingTimeOut( WPARAM wparam, LPARAM lparam );
    
    HRESULT OnShowAlarmNotify( WPARAM wparam, LPARAM lparam ); 
	
    HRESULT OnDualRecvStateNotify( WPARAM wparam, LPARAM lparam );

	HRESULT OnDualOffLineNotify( WPARAM wparam, LPARAM lparam );

    HRESULT OnDualRcvInterruptNotify( WPARAM wparam, LPARAM lparam );

	HRESULT OnCnsLeaveConfNotify( WPARAM wparam, LPARAM lparam );

    HRESULT OnCentreSleepNotify( WPARAM wparam, LPARAM lparam );

    //UMS�������Ĵ�����Ϣ��ʾ
    HRESULT OnUmsReasonInd( WPARAM wparam, LPARAM lparam );

    //TPad Home����Ӧ
    HRESULT OnTPadHomeKeyNotify( WPARAM wparam, LPARAM lparam );

private:
	//���߼���Ԫ��Ӧ�����д����� 
	static const String  m_strBtnConftempLst ;  ///<����ģ���б�
	static const String  m_strBtnCnsLst ;           ///<����Ļ᳡�б�
	static const String  m_strBtnAddrbook ;      ///< ��ַ��
    static const String  m_strBtnAddrbookMng ;      ///< ��ַ������
	static const String  m_strBtnLockScreen;     ///< ����
    static const String  m_strBtnToolMenu;        ///<���ð�ť�˵��� �����ڵ��������������öԻ���
    static const String  m_strBtnMixaud  ;
    static const String  m_strBtnTvw ;
	static const String  m_strBtnAlarm;
	static const String  m_strDlgConfManageMenu;
	static const String  m_strBtnPrePage;
	static const String  m_strBtnNextPage;
	static const String  m_strConfManageList;
    static const String  m_strBtnVideo;
    static CMainFrameLogic *m_pLogic;
    
	BOOL32               m_bAlarmOn; 	
	EM_ConfType          m_emConfType;    

};



#endif // !defined(AFX_MAINWNDLOGIC_H__336C3B31_4484_4F36_9B80_1BA09DB004FA__INCLUDED_)
