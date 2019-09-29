/*****************************************************************************
模块名      : CFrameWnd
文件名      : App.h
相关文件    : 
文件实现功能: 主控制类
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/6/19      1.0         刘德印      创建
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

	//文件列表
	void InitFileList();
	void OpenFileListFolderSub();	//双击进入文件目录的子目录数据  目前测试  实际中会有实际的vector数据
	void InitRightFileList();
	void InitConfList();			//会议列表
	void InitDownLeftDynamicList();
	void InitBoardList();
	void InitTvwStyleList();

public:
	//文件列表数据
	CCommonListUI* m_pFileLeftList;
	std::vector<IData*> m_vecFileListInfo;
	std::vector<IData*> m_vecSubFileListInfo;

	//右侧文件列表数据
	CCommonListUI* m_pFileRightList;
	std::vector<IData*> m_vecRightFileListInfo;

	//会议列表数据
 	CCommonListUI* m_pConfRightList;
 	std::vector<IData*> m_vecConfRightListInfo;

	//动态列表
	std::vector<IData*> m_vecDynamicLeftListInfo;

	//单板列表
	std::vector<IData*> m_vecBoardListInfo;

	//电视墙风格列表
	std::vector<IData*> m_vecTvwStyleListInfo;

};

#define  PTR_DLG_UIFRAME  CFrameWnd::GetSingletonPtr()

#endif