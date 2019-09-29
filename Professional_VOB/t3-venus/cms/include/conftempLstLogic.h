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
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear() ;

	/**	 
  * 功能:  把wnd属性的修改保存到文件
  * @return   bool
  * @remarks  
  */
   bool BtnSaveToFileClick( const IArgs & arg );

	/**	 
  * 功能:  点击转到会议模板列表
  * @return  bool
  * @remarks  
  */
    bool BtnToTemplstClick( const IArgs & arg );


	/**	 
  * 功能:  从会议模板列表转到模板详细信息界面
  * @return  bool
  * @remarks  
  */
    bool BtnToTempInfoClick( const IArgs & arg );
  

 /**	 
  * 功能: 点击会议模板的列表的某个条目
  * @return  bool
  * @remarks 把会议模板ID填充到会议模板信息界面，并弹出呼叫菜单
  */
    bool OnClickTempItem( const IArgs & arg  );

	/**	 
  * 功能:  点击开启会议
  * @return  bool
  * @remarks  
  */
   bool BtnStartConfClick( const IArgs & arg );
   bool BtnHangupConfClick( const IArgs & arg );

	//刷新
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
    //更新会议模板信息界面
    void UpdateTempInfoDlg( );

private:
	
    static CConftempLstLogic *m_pLogic;   

    vector<TTPAlias>     m_vctConfTempList;             //会议模板列表 

    TTPConfTemplate      m_tConfTempIDSel;              //会议模板列表中当前选中的模板信息
 
	static const String  m_strStcTitle;				    //会议模板界面标题
	static const String  m_strBtnToTemplst;			    //转到会议模板列表

    static const String  m_strDlgTempList;				//模板列表界面   
	static const String  m_strLstTemp;

	static const String  m_strDlgTempInfo;              //模板详细信息界面
	static const String  m_strStcTempName;              //模板名
	static const String  m_strStcTempID ;				//模板ID
	static const String  m_strStcConfType;				 //会议类型
	static const String  m_strStcPrimaCnsName;	//主会场名   
	static const String  m_strBtnStartConf;               //开启会议
	static const String  m_strLstSencondaryCns;
    
    static const String m_strPollInterval;
    static const String m_strLstPollCns;
	static const String m_strBtnRefresh;
    
};

#endif // !defined(AFX_CONFTEMPLSTLOGIC_H__47B4E665_6A0A_4258_A7A4_B0BFB66FBBEB__INCLUDED_)
