///*****************************************************************************
//模块名      : CPopDlg
//文件名      : popdlg.h
//相关文件    : 
//文件实现功能: 列表
//作者        : 
//版本        : 
//-----------------------------------------------------------------------------
//修改记录:
//日  期         版本        修改人      修改内容
//                           徐华秀        创建
//******************************************************************************/
#ifndef POPDLG_H
#define POPDLG_H

#pragma once
#include "resource.h"

class CPopDlg : public CMsgHandler, public ISingleTon<CPopDlg>
{
public:
	CPopDlg();
	~CPopDlg(void);
	virtual void InitWnd();
	virtual LPCTSTR GetClassName(){  return DLG_POPTEST; };

protected:
	void OnBtnClose(TNotifyUI& tMsg);
	void OnBtnTest(TNotifyUI& tMsg);
	void OnAddrListItemClick(TNotifyUI& tMsg);
	void OnAddrListItemClickIcon(TNotifyUI& tMsg);
	void OnDragEnd(TNotifyUI& tMsg);

	LRESULT OnMsgNotify( WPARAM wparam, LPARAM lparam );

	DECLARE_MSG_MAP()

protected:
	 void UpdateAddrList();

private:
	CCommonListUI* m_pAddrList;
	CCommonListUI* m_pSelAddrList;

	int m_nSelAddr;
};

#define  PTR_DLG_POPTEST  CPopDlg::GetSingletonPtr()

#endif
