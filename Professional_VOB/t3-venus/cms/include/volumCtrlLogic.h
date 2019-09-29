// volumCtrlLogic.h: interface for the CVolumCtrlLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VOLUMCTRLLOGIC_H__6DB062EE_4BC2_4FC3_9DFD_82B57B6E788F__INCLUDED_)
#define AFX_VOLUMCTRLLOGIC_H__6DB062EE_4BC2_4FC3_9DFD_82B57B6E788F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"
enum EM_VolumType{
    emVolumSpeaker,
    emVolumMic,
};

class CVolumCtrlLogic : public CWndLogicBase  
{ 
public:
    
    static CVolumCtrlLogic* GetLogicPtr(); 
    CVolumCtrlLogic();
    virtual ~CVolumCtrlLogic(); 
    
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

    bool BtnSaveToFileClick( const IArgs & arg );
    bool BtnCloseClick( const IArgs & arg );

    void ShowVolum( EM_VolumType emVolum = emVolumSpeaker, Window *pOwner = NULL );

     /**	 
  * 功能:  点击显示静音
  * @return  bool
  * @remarks  
  */
   bool OnBntQuietClick( const IArgs & arg );


  /**	 
  * 功能:  点击显示哑音
  * @return  bool
  * @remarks  
  */
  bool OnBntMuteClick( const IArgs & arg );


  //设置 音量
  bool OnReleasedcaptureVolumn( const IArgs & arg ) ;
    
  
  //设置 音量
  bool BtnMinusVolClick( const IArgs & arg ) ;

  //设置 音量
  bool BtnAddVolClick( const IArgs & arg ) ;

private:
    void CVolumCtrlLogic::BeforeUpdateVol( EM_VolumType emVol = emVolumSpeaker ); 

protected:   
    
    HRESULT OnMuteInd( WPARAM wparam, LPARAM lparam );
    HRESULT OnInputInd( WPARAM wparam, LPARAM lparam );
    HRESULT OnOutputInd( WPARAM wparam, LPARAM lparam );

    

    HRESULT OnMouseMoveVolumn( WPARAM wparam, LPARAM lparam );
 
    
protected: 
    virtual void RegMsg(); 
    virtual void UnRegMsg();
    
    void InitDlg();
    void UpdateVolum(s32 nPos );
private: 
    static CVolumCtrlLogic *m_pLogic;
    static const String m_strBtnMute;       //哑音按钮    
    static const String m_strSliderVolum;   //音量控制
    
    static EM_VolumType m_emVolumType;             //音量类型
};

#endif // !defined(AFX_VOLUMCTRLLOGIC_H__6DB062EE_4BC2_4FC3_9DFD_82B57B6E788F__INCLUDED_)
