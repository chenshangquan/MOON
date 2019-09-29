/*****************************************************************************
模块名      : MainFrame
文件名      : MainFrm.h
相关文件    : 
文件实现功能: 主控制类
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2013/5/3      1.0         刘德印      创建
******************************************************************************/
#ifndef MAINFRM_H
#define MAINFRM_H

class CBaseWindowWnd;
class MainFrame : public CBaseWindowWnd
{
public:
	MainFrame();
	~MainFrame();

public:
	LPCTSTR GetWindowClassName() const;	
	virtual void OnFinalMessage(HWND hWnd);
	virtual void Init();
	virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);
	virtual const TCHAR* GetSkinFile();
	virtual const TCHAR* GetSkinFolder();
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	DWORD GetBkColor();
	void SetBkColor(DWORD dwBackColor);

protected:	
	void Notify(TNotifyUI& msg);
	void OnPrepare(TNotifyUI& msg);
	void OnExit(TNotifyUI& msg);
	void OnTimer(TNotifyUI& msg);

	void OnBtnNextPage();
	void OnBtnReturn();

	void OnListItemClick(TNotifyUI& msg);
	void OnListItemDbClick(TNotifyUI& msg);

private:
	void InitChildDialog();						//初始化创建MainFrame上的所有子对话框


	void InitListUI();							//创建当前窗口所有的列表指针
	void UpdateFileList();						//更新文件列表

	void EnumerateFolder(const tString& strPath);

private:
	CTextUI* m_pTxFilePath;

private: 
 	std::vector<IData*> m_vecFiles;

	//列表
	CCommonListUI* m_pFileList;

	CPreWnd* m_pPreWnd;
	CommonScrollContainerUI* m_pScrollContainerUI; 

	tString m_strFolderPath;
	int m_nCurFileIndex;
};

#endif // MAINFRM_H

