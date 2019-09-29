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
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear(){} 

    void HideWindow();

    //是否是断链时的提示窗口
    void SetDisCntMsgBoxFlag( BOOL32 bDIsConnectMsgBox );
    BOOL32 IsDisCntMsgBoxShow();

 

   /**	 
  * 功能: 初始化界面信息
  * @param[in] strMsg  显示的消息
  * @param[in] bShowCancleBtn 是否显示取消按钮
  * @return  点击确认/取消按钮时 的返回值
  * @remarks 真正的domodal窗口    2013.1.29 yjj
  */
   int InitInfo(CString strMsg, BOOL32 bShowCancleBtn ,IArgs *pArgs );

    /**	 
    * 功能: 初始化界面信息
    * @remarks PostMessage之后弹出domoal框  xcr
    */
   void InitPostInfo(CString strMsg, BOOL32 bShowCancleBtn ,IArgs *pArgs );
    
  /**	 
  * 功能: 点击ok
  * @return  bool
  * @remarks 
  */
    bool OnBtnOkClick( const IArgs & arg  );

  /**	 
  * 功能: 点击cancle
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

    BOOL32 m_IsDisConnectBoxShow; //是否是断链的提示窗口
};

#ifndef HIDE_MSG_BOX
#define HIDE_MSG_BOX CMsgBoxLogic::GetLogicPtr()->HideWindow();
#endif

 

#ifndef MSG_BOX
#define MSG_BOX( strMsg,bShowCancleBtn,pArgs) \
	CMsgBoxLogic::GetLogicPtr()->InitInfo(strMsg,bShowCancleBtn,pArgs);  
#endif 

//POST消息之后弹出MSGBOX
#ifndef MSG_BOX_POST
#define MSG_BOX_POST( strMsg,bShowCancleBtn,pArgs) \
CMsgBoxLogic::GetLogicPtr()->InitPostInfo(strMsg,bShowCancleBtn,pArgs);  
#endif 
 
 
#endif // !defined(AFX_MSGBOXLOGIC_H__9735A1A4_9A2E_41D8_B252_7402A0588B61__INCLUDED_)
