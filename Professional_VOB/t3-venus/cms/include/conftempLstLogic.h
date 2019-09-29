// conftempLstLogic.h: interface for the CConftempLstLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFTEMPLSTLOGIC_H__47B4E665_6A0A_4258_A7A4_B0BFB66FBBEB__INCLUDED_)
#define AFX_CONFTEMPLSTLOGIC_H__47B4E665_6A0A_4258_A7A4_B0BFB66FBBEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "wndLogicBase.h"
class CConftempLstLogic :public CWndLogicBase 
{ 
public:  
	static CConftempLstLogic* GetLogicPtr(); 
	CConftempLstLogic(); 
	virtual ~CConftempLstLogic();
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
  * ����:  ��wnd���Ե��޸ı��浽�ļ�
  * @return   bool
  * @remarks  
  */
   bool BtnSaveToFileClick( const IArgs & arg );

	/**	 
  * ����:  ���ת������ģ���б�
  * @return  bool
  * @remarks  
  */
    bool BtnToTemplstClick( const IArgs & arg );


	/**	 
  * ����:  �ӻ���ģ���б�ת��ģ����ϸ��Ϣ����
  * @return  bool
  * @remarks  
  */
    bool BtnToTempInfoClick( const IArgs & arg );
  

 /**	 
  * ����: �������ģ����б��ĳ����Ŀ
  * @return  bool
  * @remarks �ѻ���ģ��ID��䵽����ģ����Ϣ���棬���������в˵�
  */
    bool OnClickTempItem( const IArgs & arg  );

	/**	 
  * ����:  �����������
  * @return  bool
  * @remarks  
  */
   bool BtnStartConfClick( const IArgs & arg );
   bool BtnHangupConfClick( const IArgs & arg );

	//ˢ��
	bool BtnRefreshTemp( const IArgs & arg );

   bool  CloseDlg( const IArgs & arg  );

  
protected:   
	afx_msg HRESULT OnRefreshConftempLstNotify( WPARAM wparam, LPARAM lparam);
	afx_msg HRESULT OnStartConfRsp( WPARAM wparam, LPARAM lparam);
			
	afx_msg LRESULT OnWaitRefreshOverTime( WPARAM wParam, LPARAM lParam );
 
protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();
	
private:
    //���»���ģ����Ϣ����
    void UpdateTempInfoDlg( );

private:
	
    static CConftempLstLogic *m_pLogic;   

    vector<TTPAlias>     m_vctConfTempList;             //����ģ���б� 

    TTPConfTemplate      m_tConfTempIDSel;              //����ģ���б��е�ǰѡ�е�ģ����Ϣ
 
	static const String  m_strStcTitle;				    //����ģ��������
	static const String  m_strBtnToTemplst;			    //ת������ģ���б�

    static const String  m_strDlgTempList;				//ģ���б����   
	static const String  m_strLstTemp;

	static const String  m_strDlgTempInfo;              //ģ����ϸ��Ϣ����
	static const String  m_strStcTempName;              //ģ����
	static const String  m_strStcTempID ;				//ģ��ID
	static const String  m_strStcConfType;				 //��������
	static const String  m_strStcPrimaCnsName;	//���᳡��   
	static const String  m_strBtnStartConf;               //��������
	static const String  m_strLstSencondaryCns;
    
    static const String m_strPollInterval;
    static const String m_strLstPollCns;
	static const String m_strBtnRefresh;
    
};

#endif // !defined(AFX_CONFTEMPLSTLOGIC_H__47B4E665_6A0A_4258_A7A4_B0BFB66FBBEB__INCLUDED_)
