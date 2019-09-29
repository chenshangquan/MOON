 
/*****************************************************************************
ģ����      : CMS����̨
�ļ���      : toolMenuLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���:  �����ò˵�dlg
˵��       ���������������ϵͳ���ã��ǳ����رջ����ҵ�Դ�͹ػ� 5��������
����        : �����
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2011/5/24  1.0          �����      ����
******************************************************************************/

#if !defined(AFX_TOOLMENULOGIC_H__58E085DD_3999_4E94_9521_DE2D3B5B49AC__INCLUDED_)
#define AFX_TOOLMENULOGIC_H__58E085DD_3999_4E94_9521_DE2D3B5B49AC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "wndLogicBase.h"
class CToolMenuLogic :public CWndLogicBase 
{

public:  
	static CToolMenuLogic* GetLogicPtr(); 
	CToolMenuLogic();
	virtual ~CToolMenuLogic();
public:  
	
	virtual bool RegCBFun();
	
	virtual bool UnRegFunc( );
	
    virtual bool InitWnd( const IArgs & arg );
  
    /**	 
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

    /**	 
  * ����:  �������
  * @return   bool
  * @remarks  
  */
	bool BtnMeetingManageClick( const IArgs & arg );
	
    /**	 
    * ����:  �᳡����button
    * @return   bool
    * @remarks  
    */
    bool BtnCnsManageClick( const IArgs & arg );
  

    bool BtnSystemSetClick( const IArgs & arg );
  
    /**	 
    * ����: �ػ�button
    * @return   bool
    * @remarks  
    */
    bool BtnShutDownClick( const IArgs & arg );
    
    bool ShutDown( const IArgs & arg );

   /**	 
    * ����: �ǳ�button
    * @return   bool
    * @remarks  
    */
    bool BtnLogoutClick( const IArgs & arg );

    
    bool DisConnect( const IArgs & arg );


    bool BtnHideToolBarClick( const IArgs & arg );
    
    /**	 
    * ����:  �رս���
    * @return   bool
    * @remarks  
    */ 
    bool CloseDlg( const IArgs & arg  );
 

    bool BtnSaveToFileClick( const IArgs & arg );


    bool BtnMinmizeClick( const IArgs & arg );


    bool OnBtnExitClick( const IArgs & arg );
  
    bool ExitCmc( const IArgs & arg );


    bool OnBtnCenterCtrl( const IArgs & arg );

    bool OnWndHide( const IArgs & arg );


    /**	 
    * ����:  �������ò˵�����
    * @return   
    * @remarks ����Ա�û���Ҫ��ʾ���������ϵͳ���� ��ť	  
    */
    void UpdateDlg();
protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();

	HRESULT OnDisConnect( WPARAM wparam, LPARAM lparam );
    HRESULT OnMainMenuClickToolBtn( WPARAM wparam, LPARAM lparam );
     
private:
	BOOL  m_bFirstShow;  //����ǵ�һ����ʾ������Ҫʹ�� UpdateDlg
    static CToolMenuLogic *m_pLogic;  


	static const String  m_strBtnConfManage ;  ///<�������
	static const String  m_strBtnSysSet ;           ///<ϵͳ����
	static const String  m_strBtnLogoff  ;          ///<�ǳ�
	static const String  m_strBtnPowerdown  ;  ///<�رջ����ҵ�Դ
	static const String  m_strBtnShutdown ;     ///<�ػ�
};

#endif // !defined(AFX_TOOLMENULOGIC_H__58E085DD_3999_4E94_9521_DE2D3B5B49AC__INCLUDED_)
