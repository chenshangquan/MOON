// msgBoxLogic.h: interface for the CMsgBoxLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGBOXLOGIC_H__9735A1A4_9A2E_41D8_B252_7402A0588B61__INCLUDED_)
#define AFX_MSGBOXLOGIC_H__9735A1A4_9A2E_41D8_B252_7402A0588B61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"
#include "valueStorage.h"
class CMsgBoxLogic : public CWndLogicBase  
{
public:
 
    static CMsgBoxLogic* GetLogicPtr(); 
    CMsgBoxLogic();
    virtual ~CMsgBoxLogic(); 
    
public:  
    /**	 
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear(){} 

    void HideWindow();

    //�Ƿ��Ƕ���ʱ����ʾ����
    void SetDisCntMsgBoxFlag( BOOL32 bDIsConnectMsgBox );
    BOOL32 IsDisCntMsgBoxShow();

 

   /**	 
  * ����: ��ʼ��������Ϣ
  * @param[in] strMsg  ��ʾ����Ϣ
  * @param[in] bShowCancleBtn �Ƿ���ʾȡ����ť
  * @return  ���ȷ��/ȡ����ťʱ �ķ���ֵ
  * @remarks ������domodal����    2013.1.29 yjj
  */
   int InitInfo(CString strMsg, BOOL32 bShowCancleBtn ,IArgs *pArgs );

    /**	 
    * ����: ��ʼ��������Ϣ
    * @remarks PostMessage֮�󵯳�domoal��  xcr
    */
   void InitPostInfo(CString strMsg, BOOL32 bShowCancleBtn ,IArgs *pArgs );
    
  /**	 
  * ����: ���ok
  * @return  bool
  * @remarks 
  */
    bool OnBtnOkClick( const IArgs & arg  );

  /**	 
  * ����: ���cancle
  * @return  bool
  * @remarks  
  */
    bool OnBtnCancleClick( const IArgs & arg  );
    

    virtual bool RegCBFun();
    
    virtual bool UnRegFunc( );
    
    virtual bool InitWnd( const IArgs & arg );
    
    bool BtnSaveToFileClick( const IArgs & arg );

    bool OnPostDomodal( const IArgs & arg );
protected: 
    
    //afx_msg HRESULT OnConnectRep( WPARAM wparam, LPARAM lparam);*/
    
    
protected: 
    virtual void RegMsg(); 
    virtual void UnRegMsg();
    
private:
    ICallBackFuncBase* m_pOkFunc;
    ICallBackFuncBase* m_pCancleFunc;
    static CMsgBoxLogic *m_pLogic; 
    static const String m_strEdtMsg;
    IArgs *m_pArgs;
	Window* m_pOwnerWnd;

    BOOL32 m_IsDisConnectBoxShow; //�Ƿ��Ƕ�������ʾ����
};

#ifndef HIDE_MSG_BOX
#define HIDE_MSG_BOX CMsgBoxLogic::GetLogicPtr()->HideWindow();
#endif

 

#ifndef MSG_BOX
#define MSG_BOX( strMsg,bShowCancleBtn,pArgs) \
	CMsgBoxLogic::GetLogicPtr()->InitInfo(strMsg,bShowCancleBtn,pArgs);  
#endif 

//POST��Ϣ֮�󵯳�MSGBOX
#ifndef MSG_BOX_POST
#define MSG_BOX_POST( strMsg,bShowCancleBtn,pArgs) \
CMsgBoxLogic::GetLogicPtr()->InitPostInfo(strMsg,bShowCancleBtn,pArgs);  
#endif 
 
 
#endif // !defined(AFX_MSGBOXLOGIC_H__9735A1A4_9A2E_41D8_B252_7402A0588B61__INCLUDED_)
