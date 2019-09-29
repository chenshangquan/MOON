// WaitingRefreshLogic.h: interface for the CWaitingRefreshLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WAITINGREFRESHLOGIC_H__5C20464F_BD5B_45AB_A68A_19B17B97637E__INCLUDED_)
#define AFX_WAITINGREFRESHLOGIC_H__5C20464F_BD5B_45AB_A68A_19B17B97637E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CWaitingRefreshLogic : public CWndLogicBase
{
public:
	CWaitingRefreshLogic();
	virtual ~CWaitingRefreshLogic();

	static CWaitingRefreshLogic* GetLogicPtr();

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

	void UpdateWaitingImg();

protected:
	bool InitWnd( const IArgs & args );

	LRESULT OnBeginWaitingRefresh(WPARAM wParam, LPARAM lParam);

	LRESULT OnEndWaitingRefresh(WPARAM wParam, LPARAM lParam);

	LRESULT OnLoadAddrNumNty(WPARAM wParam, LPARAM lParam);

private:
	static CWaitingRefreshLogic *m_pLogic;

	int                 m_nUpdateTime;
	EmGetRegInfoType    m_emGetType;

	Em_ImgSchm          m_emImgSchm; 

	static const String m_stcUpdateImg;
	static const String m_shmImg1;
	static const String m_shmImg2;
	static const String m_shmImg3;
	static const String m_shmImg4;
	EmWaitType       m_emWaitType; //等待刷新的 类型  2013.1.16 yjj
};

#endif // !defined(AFX_WAITINGREFRESHLOGIC_H__5C20464F_BD5B_45AB_A68A_19B17B97637E__INCLUDED_)
