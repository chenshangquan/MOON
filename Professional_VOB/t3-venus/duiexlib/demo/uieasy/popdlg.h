///*****************************************************************************
//ģ����      : CPopDlg
//�ļ���      : popdlg.h
//����ļ�    : 
//�ļ�ʵ�ֹ���: �б�
//����        : 
//�汾        : 
//-----------------------------------------------------------------------------
//�޸ļ�¼:
//��  ��         �汾        �޸���      �޸�����
//                           �컪��        ����
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
