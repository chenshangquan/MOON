/*****************************************************************************
ģ����      : MainFrame
�ļ���      : MainFrm.h
����ļ�    : 
�ļ�ʵ�ֹ���: ��������
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/5/3      1.0         ����ӡ      ����
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
	void InitChildDialog();						//��ʼ������MainFrame�ϵ������ӶԻ���


	void InitListUI();							//������ǰ�������е��б�ָ��
	void UpdateFileList();						//�����ļ��б�

	void EnumerateFolder(const tString& strPath);

private:
	CTextUI* m_pTxFilePath;

private: 
 	std::vector<IData*> m_vecFiles;

	//�б�
	CCommonListUI* m_pFileList;

	CPreWnd* m_pPreWnd;
	CommonScrollContainerUI* m_pScrollContainerUI; 

	tString m_strFolderPath;
	int m_nCurFileIndex;
};

#endif // MAINFRM_H

