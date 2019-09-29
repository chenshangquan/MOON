// userManageLogic.h: interface for the CUserManageLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERMANAGELOGIC_H__0720ED96_4DB3_48DD_8F13_8753E6FDA4D4__INCLUDED_)
#define AFX_USERMANAGELOGIC_H__0720ED96_4DB3_48DD_8F13_8753E6FDA4D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

/*
1.SchmShowUserLst :��ʾ�û��б���棬ͬʱ title�л�Ϊ���û�������btn "�û�����"��ʾ�����½��û�����ʾ��������������
2.SchmShowUserInfo :��ʾ�û���Ϣ����, ͬʱ title�л�Ϊ���û���Ϣ����btn "�û�����"��ʾ�����༭����ʾ 
3.SchmEdtUser: �û���Ϣ������ʾΪ �ɱ༭�ģ� ͬʱ title�л�Ϊ���༭�û���Ϣ����btn "����"��ʾ����ȡ������ʾ  
*/

enum EmModifyUserType{
    emModifyTpCheck,                  //�鿴
    emModifyTpNew,                  //�½��û�
    emModifyTpUpdate,               //�༭�����û�
    emModifyManager,
};

class CUserManageLogic : public CWndLogicBase  
{ 
public:  
    static CUserManageLogic* GetLogicPtr(); 
    CUserManageLogic();
    virtual ~CUserManageLogic();
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
    * ����:  �����ת���û����ý����button
    * @return   bool
    * @remarks  
    */  
    bool BtnToUserConfigClick( const IArgs & arg );



    /**	 
    * ����:  ������½��û���button
    * @return   bool
    * @remarks  
    */  
    bool BtnToNewUserClick( const IArgs & arg );



     /**	 
    * ����:  ����˱༭�û���button
    * @return   bool
    * @remarks  
    */  
    bool BtnToEdtClick( const IArgs & arg );


     /**	 
    * ����:  ����˱����û���Ϣ��btn
    * @return   bool
    * @remarks  
    */  
    bool BtnToSaveClick( const IArgs & arg );



     /**	 
    * ����:  �����ȡ���༭�û���Ϣ��btn
    * @return   bool
    * @remarks  
    */  
    bool BtnToCancleClick( const IArgs & arg );




     /**	 
    * ����:  �����ɾ���û���Ϣ��btn
    * @return   bool
    * @remarks  
    */  
    bool BtnToDeleteClick( const IArgs & arg );



    /**	 
    * ����:  ������û�����item
    * @return   bool
    * @remarks  
    */  
    bool OnUserConfigItemIcon( const IArgs & arg );

    bool OnUserConfigItem( const IArgs & arg );

     /**	 
    * ����:  ������û�list item�ϵ�ͼ��
    * @return   bool
    * @remarks  
    */  
    bool OnUserLstItemIcon( const IArgs & arg );

    bool OnUserLstItem( const IArgs & arg );


    /**	 
    * ����:  �������ʾ�û��б��ͼ��
    * @return   bool
    * @remarks  
    */  
    bool ToUserLstIconClick( const IArgs & arg );




    /**	 
    * ����:  �������ʾ�û���Ϣ��ͼ��
    * @return   bool
    * @remarks  
    */  
    bool ToUserInfoIconClick( const IArgs & arg );


     /**	 
    * ����:  ���������Ϣ
    * @return   bool
    * @remarks  
    */  
    bool BtnSaveToFileClick( const IArgs & arg );

    bool  OnPswdEdtSetFocus( const IArgs & arg );
protected: 
    virtual void RegMsg(); 
    virtual void UnRegMsg();
    
    HRESULT OnUserRefreshNotify( WPARAM wparam, LPARAM lparam );
    HRESULT OnUserModifyRsp( WPARAM wparam, LPARAM lparam );
   
    void  InitConfigLst();
    void  UpdateUserInfo();
    void  UpdateUserLst();
    void  UpdateDlg();
    void  UpdateManageDlg();
   
    void  ShowSubDlg( String strSubDlgName );

private:
    
    static CUserManageLogic *m_pLogic;
    
    CUserFullInfo       m_selUser;                 //��ǰѡ����û�

    EmModifyUserType    m_emModifyType;            //���޸��û�  ���� �½��û�
   
    static const String m_strUserManage;           //
    static const String m_strManagerModify;

    //controls 
    static const String m_dlgUserConfig;
    static const String m_dlgUserInfo; 
    static const String m_dlgUserLst;               //�û��б����
    static const String m_strEdtUserName;           //�û���
    static const String m_strEdtPswd;               //����
    static const String m_strEdtNote;               //��ע
   
    static const String m_strLstUser;               //�û��б�
   
    static const String m_strLstConfig;             //�����б�


    //����Ա����
    static const String CUserManageLogic::m_dlgManagerInfo ;     //����Ա����
    static const String CUserManageLogic::m_strEdtManagerName ;    //�û���
    static const String CUserManageLogic::m_strEdtOriPswd ;         //ԭ����
    static const String CUserManageLogic::m_strEdtNewPswd ;         //������
    static const String CUserManageLogic::m_strEdtReNewPswd ;     //�ظ����� 

    //shceme
    static const String  m_schmShowUserLst;
    static const String  m_schmShowUserInfo;
    static const String  m_schmShowUserConfig;
    static const String  m_schmShowManagerModify;  //����Ա�����޸�
    static const String  m_schmNewUser;            //�½��û�
    static const String  m_schmShowEdtState;
};

#endif // !defined(AFX_USERMANAGELOGIC_H__0720ED96_4DB3_48DD_8F13_8753E6FDA4D4__INCLUDED_)
