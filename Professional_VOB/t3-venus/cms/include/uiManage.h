 
/*****************************************************************************
ģ����      : CMS����̨
�ļ���      : uiManage.h
����ļ�    : 
�ļ�ʵ�ֹ���: UIģ��Ĺ������з�װ��cms����Ҫ��UIFactoryLib�Ľӿڣ�ͬʱҲ�����cms����Ҫ�õĿؼ�
����        : �����
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2011/5/24  1.0          �����      ����
******************************************************************************/

#if !defined(AFX_UIMANAGE_H__A30C96E8_214E_4915_83D0_C0AF9B2BFF8A__INCLUDED_)
#define AFX_UIMANAGE_H__A30C96E8_214E_4915_83D0_C0AF9B2BFF8A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#pragma warning (disable: 4786) 
#pragma warning (disable: 4503) 


//----uifactoryLib------ 

#include "valueSet.h"

#include "MfcDefaultWndProperty.h"


 
 
#define HANDLE_ERROR ( CUiManage::HandleErr )  

#define HANDLE_ERROR_NOW(p)\
{\
	CUiManage::HandleErr(p, "", TRUE);\
}

 

class CUiManage  
{
 
public:
/** @defgroup  CUiManage  (UIģ��Ĺ������з�װ��cms����Ҫ��UIFactoryLib�Ľӿڣ�ͬʱҲ�����cms����Ҫ�õĿؼ�)
 *  @{
 */ 

    static CUiManage* GetUiManagePtr();

/** @defgroup   �������Բ���
 *  @{
 */
    void UpdateUI(   IWndTree* pWndTree );
  
    void UpdateUI( String strWndName,   IWndTree* pWndTree = NULL);
  /**	 
	* ����:  ��ʾ/����ĳ������
	* @param [in]  strWndName  ������
	* @param [in]  bShow  �Ƿ�Ҫ��ʾ 
	* @param [in]  bReDraw  �Ƿ��ػ�
	* @return  u16 �ɹ�����0;ʧ�ܷ��ط�0������
	* @remarks	 
	*/
	u16 ShowWindow( String strWndName, bool bShow = true,const IWndTree* pWndTree = NULL, BOOL bReDraw = TRUE );

   /**	 
	* ����:  ��ȡdomodal�Ĵ���
	* @param [in]  strWndName  ������ 
	* @return   �ɹ�����Windowָ��;ʧ�ܷ���NULL
	* @remarks	 
	*/
	Window* GetModalWnd( String strWndName );
	
 


	/**  ��ȡ�ؼ���Ϣ 
	 *  @param[in] strName �ؼ�����
	 *  @param[in] pWndTree �ؼ��� 
	 *  @return �ؼ���Ϣ
	 *  @remarks ���ؼ��к��С�/�� ��ᰴ�շָ�������
	 */ 
   const IWndTree* GetWindow( String strName, const IWndTree* pWndTree = NULL )  ;
	

   	/**  ��ȡ�ؼ���Ϣ
	 *  @param[in] pWnd ����ָ��
	 *  @param[in] pWndTree ��Ҫ��������
	 *  @return �����������Ĵ���
	 */
    const IWndTree* GetWindow( Window* pWnd, const IWndTree* pWndTree );


	/**  ��ȡ�ؼ�ָ�� 
	 *  @param[in] strName �ؼ�����
	 *  @param[in] pWndTree �ؼ��� 
	 *  @return �ؼ���Ϣ
	 *  @remarks ���ؼ��к��С�/�� ��ᰴ�շָ�������
	 */ 
	Window* GetWindowPtr( String strName, const IWndTree* pWndTree = NULL );

     /**	 
	* ����:  �����÷���
	* @param [in] strSchemeName ������
    * @param [in] String strWndName ���ø÷����Ĵ�����
    * @param[in] pWndTree �������ڵĿؼ��� 
	* @return   
	* @remarks	   
	*/
   bool LoadScheme( String strSchemeName, IWndTree* pWndTree = NULL , String strWndName = "", bool bInvalidate = true );

	 /**	 
	* ����:  ����ĳ�ؼ�����ֵ
	* @param [in]  strWndName  ������
	* @param [in]  value Ҫ���õ�������Ϣ 
	* @param[in] pWndTree �ؼ����ڵ���
	* @return  bool �ɹ�����true;ʧ�ܷ���false
	* @remarks	 ���ؼ��к��С�/�� ��ᰴ�շָ�������
	*/
 	bool SetPropertyValue( const IValue& value,   String strWndName, const IWndTree* pWndTree = NULL );

	 /**	 
	* ����:  ��ȡĳ�ؼ�����ֵ
	* @param [in&out]  IValue  Ҫ��ȡ��������Ϣ
	* @param [in]  window  Ҫ��ȡ�����ԵĴ���ָ��
	* @param [in]  strWndType  Ҫ��ȡ�����ԵĴ�������
	* @return  bool �ɹ�����true;ʧ�ܷ���false
	* @remarks	 
	*/
    bool SetPropertyValue( const IValue& value, const Window* window,  const String& strWndType );


   	 /**	 
	* ����:  ��ȡĳ�ؼ�����ֵ
	* @param [in&out]  IValue  Ҫ��ȡ��������Ϣ
	* @param [in]  strWndName  ������ 
	* @param[in] pWndTree �ؼ����ڵ���
	* @return  bool �ɹ�����true;ʧ�ܷ���false
	* @remarks	 ���ؼ��к��С�/�� ��ᰴ�շָ�������
	*/
	bool GetPropertyValue( IValue& value, String strWndName, const IWndTree* pWndTree = NULL);

	 /**	 
	* ����:  ��ȡĳ�ؼ�����ֵ
	* @param [in&out]  IValue  Ҫ��ȡ��������Ϣ
	* @param [in]  window  Ҫ��ȡ�����ԵĴ���ָ��
	* @param [in]  strWndType  Ҫ��ȡ�����ԵĴ�������
	* @return  bool �ɹ�����true;ʧ�ܷ���false
	* @remarks	 
	*/
 	bool GetPropertyValue( IValue& value, const Window* window,  const String& strWndType );

	/**	 
	* ����:  ���ÿؼ��Ƿ����
	* @param [in]  strWndName  �ؼ���
	* @param [in]  bEnable  ״̬
	* @param [in]  pWndTree �ؼ��� 
	* @return  bool �ɹ�����true;ʧ�ܷ���false
	* @remarks	 
	*/
	bool EnableWindow( String strWndName, bool bEnable = true, const IWndTree* pWndTree = NULL );

	/**	 
	* ����:  ���ÿؼ�����
	* @param [in]  strWndName  �ؼ���
	* @param [in]  strCaption  ����
	* @param [in]  pWndTree �ؼ��� 
	* @param [in]  bReDraw  �Ƿ��ػ� 
	* @return  bool �ɹ�����true;ʧ�ܷ���false
	* @remarks	 
	*/
	bool SetCaption( String strWndName, String strCaption, const IWndTree* pWndTree = NULL, BOOL bReDraw = FALSE );

	/**	 
	* ����:  ��ȡ�ؼ�����
	* @param [in]  strWndName  �ؼ���
	* @param [out] strCaption  ����
	* @param [in]  pWndTree �ؼ��� 
	* @return  bool �ɹ�����true;ʧ�ܷ���false
	* @remarks	 
	*/
	bool GetCaption( String strWndName, String& strCaption, const IWndTree* pWndTree = NULL );

	/**	 
	* ����:  ���ý���
	* @param [in]  strWndName  �ؼ���
	* @param [in]  pWndTree �ؼ��� 
	* @return  bool �ɹ�����true;ʧ�ܷ���false
	* @remarks	 
	*/
	bool SetFocus( String strWndName, const IWndTree* pWndTree = NULL );

	/**	 
	* ����:  ����Button Check״̬
	* @param [in]  strWndName  �ؼ���
	* @param [in] nCheckState  ״̬
	* @param [in]  pWndTree �ؼ��� 
	* @return  bool �ɹ�����true;ʧ�ܷ���false
	* @remarks	 
	*/
	bool SetCheckState( String strWndName, int nCheckState, const IWndTree* pWndTree = NULL );

	/**	 
	* ����:  ����SwitchButton Check״̬
	* @param [in]  strWndName  �ؼ���
	* @param [in]  bState  ״̬
	* @param [in]  pWndTree �ؼ��� 
	* @return  bool �ɹ�����true;ʧ�ܷ���false
	* @remarks	 
	*/
	bool SetSwitchState( String strWndName, bool bState, const IWndTree* pWndTree = NULL );

	/**	 
	* ����:  ��ȡSwitchButton Check״̬
	* @param [in]  strWndName  �ؼ���
	* @param [out] bState  ״̬
	* @param [in]  pWndTree �ؼ��� 
	* @return  bool �ɹ�����true;ʧ�ܷ���false
	* @remarks	 
	*/
	bool GetSwitchState( String strWndName, bool& bState, const IWndTree* pWndTree = NULL );

   	/**	 
	* ����:  �鿴�ؼ��Ƿ���ʾ
	* @param [in]  strWndName  �ؼ��� 
	* @param [in]  pWndTree �ؼ��� 
	* @return  bool ��ʾ����true;δ��ʾ����false
	* @remarks	 
	*/
	bool IsVisible( String strWndName, const IWndTree* pWndTree = NULL );

	/**	 
	* ����:  ����DlgͼƬ
	* @param [in]  strWndName  �ؼ���
	* @param [in]  strPath  ͼƬ·��
	* @param [in]  pWndTree �ؼ��� 
	* @return  bool �ɹ�����true;ʧ�ܷ���false
	* @remarks	 
	*/
	bool SetTransparentDlgImage( String strWndName, String strPath, const IWndTree* pWndTree = NULL );

	/**	 
	* ����:  ����DragButton Sel״̬
	* @param [in]  strWndName  �ؼ���
	* @param [out] bState  ״̬
	* @param [in]  pWndTree �ؼ��� 
	* @return  bool �ɹ�����true;ʧ�ܷ���false
	*/
	bool SetSelState( String strWndName, bool bState, const IWndTree* pWndTree = NULL );

	/**	 
	* ����:  ��ȡDragButton Sel״̬
	* @param [in]  strWndName  �ؼ���
	* @param [out] bState  ״̬
	* @param [in]  pWndTree �ؼ��� 
	* @return  bool �ɹ�����true;ʧ�ܷ���false
	*/
	bool GetSelState( String strWndName, bool& bState, const IWndTree* pWndTree = NULL );

	/**	 
	* ����:  ����DragButton Online״̬
	* @param [in]  strWndName  �ؼ���
	* @param [out] bOnline  ״̬
	* @param [in]  pWndTree �ؼ��� 
	* @return  bool �ɹ�����true;ʧ�ܷ���false
	*/
	bool SetDragBtnOnline( String strWndName, bool bOnline, const IWndTree* pWndTree = NULL );   
/**@} */  //�������Դ�����

  
  /**	 
	* ����:  ����windows��Ϣ
	* @param [in]  pMsg Ҫ�������Ϣ��Ϣ
	* @return  bool �ɹ�����true;ʧ�ܷ���false
	* @remarks	��uifactroy�ڲ�����ע�������Ϣ�Ĵ����� �Ը���Ϣ������Ӧ
	*/
	bool HandleMsg( WindowMsg* pMsg );

 

     /**  �������д���
 *  @param[in]  
 *  @return �Ƿ����سɹ�
 */
    bool HideAllWindow();
   

   	/**	 
	* ����:  ���ٴ���	 
	* @param [in]  strWndName Ҫ���ٵĴ�����
	* @return  u16 �ɹ�����0��ʧ�ܷ��ش���
	* @remarks	   
	*/ 
	u16 DestroyWindow( String strWndName );


	/**  ���ٴ��ڣ���������CWnd��Destory
   *  @param[in] pWnd ����ָ��
   *  @return �Ƿ����ٳɹ�
  */
	bool DestoryWnd( Window* pWnd );


  /**  ���ٴ��ڣ���������CWnd��Destory
  *  @param[in] pWndTree ������
  *  @return �Ƿ����ٳɹ�
 */
	bool DestoryWnd( IWndTree* pWndTree );


 
/**@} */  //wnd������
   
   	/**	 
	* ����:  �Ѵ��ڷ��ĸı��¼���ļ��� 
	* @param [in]   String strWndName������
    *  @param[in] strSavePropertyName Ҫ�����������
    *  @param[in] bForceSave ���Ҫ��������Բ��ڵ�ǰ�����У��Ƿ�ǿ�Ʊ���
	* @return   
	* @remarks	   
	*/
   bool  SaveToFile( String strWndName, string strSaveWndName = "" ,string strSavePropertyName = "" , BOOL bForceSave = FALSE );
 
   String GetImagePath();

   static void HandleErr( DWORD dwErrID, CString strMsp = "", BOOL bShowNow = FALSE );


   vector<TConfMenuInfo> *GetConfMenu(){ return &m_vctConfMenu ; }
   
   BOOL SaveConfMenu( vector<TConfMenuInfo> & lst ); 
 
   BOOL UpdateConfMenuAccordFile( );
private:
   IWndTree * m_pRoot;

/** @}*/ 

public:   
	virtual ~CUiManage();
private:
	CUiManage();
	static void InitWndName();

private:
    static CUiManage* m_pStMySelf;
    vector<TConfMenuInfo> m_vctConfMenu;

};


#define UIManagePtr CUiManage::GetUiManagePtr()

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
extern  const String g_strSysStandBy;
extern  const String g_strNetManageCfg;
extern  const String g_strAddrShowOptnDlg;

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

              
 
#endif // !defined(AFX_UIMANAGE_H__A30C96E8_214E_4915_83D0_C0AF9B2BFF8A__INCLUDED_)
