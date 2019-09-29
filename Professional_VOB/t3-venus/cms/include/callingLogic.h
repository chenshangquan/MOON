// callingLogic.h: interface for the CCallingLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALLINGLOGIC_H__C06F2EE9_FFAE_4FC2_B0C5_E0FB5201A77F__INCLUDED_)
#define AFX_CALLINGLOGIC_H__C06F2EE9_FFAE_4FC2_B0C5_E0FB5201A77F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"



class CCallingLogic : public CWndLogicBase  
{
public: 
    static CCallingLogic* GetLogicPtr(); 
    CCallingLogic();
    virtual ~CCallingLogic(); 
    
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
  

    virtual bool OnBtnHungupConf( const IArgs & arg );

    //更换呼叫图片
    void UpdateCallingImg();

protected:  
    HRESULT OnShowNotify( WPARAM wparam, LPARAM lparam);
    HRESULT OnHideNotify( WPARAM wparam, LPARAM lparam); 
    
  
protected: 
    virtual void RegMsg(); 
    virtual void UnRegMsg();
    
private:
     
    static const String m_strCallImg;
    static const String m_strCallMsg;

    static CCallingLogic *m_pLogic;
    Em_ImgSchm m_emImgSchm;          //当前图片显示方案

    static const String m_stcShowTime;  //呼叫动画显示的时间。若查过改时间，则像mainFrameLogic 发通知

    static const String m_shmImg1;
    static const String m_shmImg2;
    static const String m_shmImg3;
    static const String m_shmImg4;


	EMTimer m_emTimer;

};

#endif // !defined(AFX_CALLINGLOGIC_H__C06F2EE9_FFAE_4FC2_B0C5_E0FB5201A77F__INCLUDED_)
