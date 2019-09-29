// simulateCnsLogic.h: interface for the CSimulateCnsLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMULATECNSLOGIC_H__1CEC2AB2_3CCB_4983_9535_B9657B1395F9__INCLUDED_)
#define AFX_SIMULATECNSLOGIC_H__1CEC2AB2_3CCB_4983_9535_B9657B1395F9__INCLUDED_

#include "wndLogicBase.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//屏扩展信息
typedef struct tagScreenInfoEx{
	String strCtlScreen;                    //控件名：屏 
	String strCtlScreenState;          //控件名：屏状态 
    String strCtlCnsName;              //控件名：当前屏正在播放的cns名  
 
} TScreenInfoEx,*PTScreenInfoEx;


typedef struct tagSeatInfoEx{
	String strCtrlSeat;            //控件名：坐席
	String strCtrlSpoksBtn;    //控件名：button，指定发言人 
 
}TSeatInfoEx, *PTSeatInfoEx;

#define  MAX_SCREEN_COUNT    5
#define  MAX_SEAT_COUNT      3

class CSimulateCnsLogic: public CWndLogicBase
{ 
public:  
	static CSimulateCnsLogic* GetLogicPtr(); 
	CSimulateCnsLogic();
	virtual ~CSimulateCnsLogic();
public:  
	
	virtual bool RegCBFun();
	
	virtual bool UnRegFunc( );
	
    virtual bool InitWnd( const IArgs & arg );
   
    /**	 
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear();


	bool BtnSetSpokesman1Click( const IArgs & arg );

	bool BtnSetSpokesman2Click( const IArgs & arg );

	bool BtnSetSpokesman3Click( const IArgs & arg );

    /**	 
        * 功能:  点击屏幕
        * @return  bool
        * @remarks  
	*/
    bool BtnSrcn1Click( const IArgs & arg );
    bool BtnSrcn2Click( const IArgs & arg );
    bool BtnSrcn3Click( const IArgs & arg );
   
 
 
   
protected:   
	//会议状态通知
	afx_msg HRESULT OnConfStateNotify( WPARAM wparam, LPARAM lparam );

	//屏名更改通知
	afx_msg HRESULT OnScreenNameNotify( WPARAM wparam, LPARAM lparam );

	//屏状态更改通知
	afx_msg HRESULT OnScreenStateNotify( WPARAM wparam, LPARAM lparam );
	
	//发言人更改通知
	afx_msg HRESULT OnSpokesManNotify( WPARAM wparam, LPARAM lparam );
    
 

protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();

    bool GetPosFrmArg( const IArgs & arg , CPoint &pos);
	
   
private: 

	//更改屏状态
	void UpdateScreenState( TScreenInfo tInfo );

	//刷新会场屏
    void RefreshCnsScreen();
	
	//刷新坐席
	void RefreshSpeakSeat();

 
private:

    static CSimulateCnsLogic *m_pLogic;    
	static const String   m_strConfTitle;
    static TScreenInfoEx  m_screenInfoArry[MAX_SCREEN_COUNT];       //屏信息     
	static TSeatInfoEx    m_seatInfoArry[MAX_SEAT_COUNT];		    //坐席信息  

    
    const  static String         m_strSchmActive;                   //激活方案
    const  static String         m_strSchmUnActive;                 //未激活
    const static String          m_strSchnCancleView;               //取消选看

	static String                m_BtnScreenArry[MAX_SEAT_COUNT];   //三个可激活屏
    const static String          m_strSwitchBtnScrn1;               //
    const static String          m_strSwitchBtnScrn2;
    const static String          m_strSwitchBtnScrn3;

    u8     m_bySelScreenID;                                         //当前选中的屏号 

    u8    m_byCurSpokesSeatID;						                //当前发言人ID
	BOOL  m_bInConf;
    
};

#endif // !defined(AFX_SIMULATECNSLOGIC_H__1CEC2AB2_3CCB_4983_9535_B9657B1395F9__INCLUDED_)



    
