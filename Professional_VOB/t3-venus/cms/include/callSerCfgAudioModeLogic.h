// callSerCfgAudioModeLogic.h: interface for the CCallSerCfgAudioModeLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALLSERCFGAUDIOMODELOGIC_H__CCB97C3B_C8C0_46A0_90EB_7FF08A1A6090__INCLUDED_)
#define AFX_CALLSERCFGAUDIOMODELOGIC_H__CCB97C3B_C8C0_46A0_90EB_7FF08A1A6090__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CCallSerCfgAudioModeLogic : public CWndLogicBase 
{
public:
	CCallSerCfgAudioModeLogic();
	virtual ~CCallSerCfgAudioModeLogic();
	static CCallSerCfgAudioModeLogic* GetLogicPtr();
	
public:
	virtual bool RegCBFun();
	virtual bool UnRegFunc();
	virtual void RegMsg();

    /**	 
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear();
	
protected:
	bool InitWnd( const IArgs & args );
	
	bool OnBtnBack( const IArgs & args );
	
	LRESULT OnCallSer2AudioModeNty( WPARAM wParam, LPARAM lParam );
	
	
private:
	static CCallSerCfgAudioModeLogic *m_pLogic;
	EmTpAudioFormat m_emAudioFormat;
};

#endif // !defined(AFX_CALLSERCFGAUDIOMODELOGIC_H__CCB97C3B_C8C0_46A0_90EB_7FF08A1A6090__INCLUDED_)
