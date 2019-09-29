/*****************************************************************************
ģ����      : CFrameWnd
�ļ���      : App.h
����ļ�    : 
�ļ�ʵ�ֹ���: ��������
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/6/19      1.0         ����ӡ      ����
******************************************************************************/
#ifndef APP_H
#define APP_H
#include "resource.h"

#define BTN_FILELISTCHILD	_T("btnfilechild")
#define LIST_FILE			_T("listfile")
#define LIST_FILE_RIGHT		_T("listfileright")
#define LIST_CONF			_T("listconf")
#define LIST_DOWNDYNAMIC	_T("listdowndynamic")
#define LIST_BOARD			_T("listboard")
#define LIST_TVWSTYLE		_T("listtvwstyle")
#define BTN_POP_DLG         _T("btnpopdlg")

class CFrameWnd : public CMsgHandler, public ISingleTon<CFrameWnd>
{
public:
	CFrameWnd();
	~CFrameWnd(void);

public:
	virtual void InitWnd();
	virtual LPCTSTR GetClassName(){ return DLG_UIFRAME;};
	LRESULT OnMsgNotify( WPARAM wparam, LPARAM lparam );

protected:
	void OnBtnPopDlg(TNotifyUI& tMsg);
	void OnBtnFileListChildClick(TNotifyUI& tMsg);
	void OnFileListItemClick(TNotifyUI& tMsg);
	void OnRFileListItemClick(TNotifyUI& tMsg);

	DECLARE_MSG_MAP()

protected:
	void InitListUI();

	//�ļ��б�
	void InitFileList();
	void OpenFileListFolderSub();	//˫�������ļ�Ŀ¼����Ŀ¼����  Ŀǰ����  ʵ���л���ʵ�ʵ�vector����
	void InitRightFileList();
	void InitConfList();			//�����б�
	void InitDownLeftDynamicList();
	void InitBoardList();
	void InitTvwStyleList();

public:
	//�ļ��б�����
	CCommonListUI* m_pFileLeftList;
	std::vector<IData*> m_vecFileListInfo;
	std::vector<IData*> m_vecSubFileListInfo;

	//�Ҳ��ļ��б�����
	CCommonListUI* m_pFileRightList;
	std::vector<IData*> m_vecRightFileListInfo;

	//�����б�����
 	CCommonListUI* m_pConfRightList;
 	std::vector<IData*> m_vecConfRightListInfo;

	//��̬�б�
	std::vector<IData*> m_vecDynamicLeftListInfo;

	//�����б�
	std::vector<IData*> m_vecBoardListInfo;

	//����ǽ����б�
	std::vector<IData*> m_vecTvwStyleListInfo;

};

#define  PTR_DLG_UIFRAME  CFrameWnd::GetSingletonPtr()

#endif