/*****************************************************************************
ģ����      : CPreWnd
�ļ���      : PreWnd.h
����ļ�    : 
�ļ�ʵ�ֹ���: Ԥ�����ڣ�����Ԥ������֧�ֵ�ppt pdf xls png jpg txt���ļ���(WS_CHILD)
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/6/03      1.0         ����ӡ      ����
******************************************************************************/
#ifndef PREWND_H
#define PREWND_H

class CBaseWindowWnd;
class UILIB_API CPreWnd : public CBaseWindowWnd
{
public:
	CPreWnd(CPaintManagerUI& paint_manager);
	LPCTSTR GetWindowClassName() const;
	virtual LRESULT OnDestroy( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual void OnFinalMessage(HWND hWnd);
	virtual LRESULT MessageHandler( UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled );
	virtual const TCHAR* GetSkinFile();

	void Init();
	void Notify(TNotifyUI& msg);


	 /*****************************************************************************
	* ����:			��ʾprewnd����
	* @param		[in]	TRUE����ʾ     FALSE������
	* @return		�� 
	* @remarks		��
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2013/5/3       1.0         ����ӡ      ����
    ******************************************************************************/
	void ShowWnd(bool bShow = true);	

	 /*****************************************************************************
	* ����:			�ƶ�prewnd����λ��
	* @param		[in]	Ŀ�괰��λ��POINT
	* @return		�� 
	* @remarks		��
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2013/5/3       1.0         ����ӡ      ����
    ******************************************************************************/
	void MoveWnd(POINT pt);		

	 /*****************************************************************************
	* ����:			��Դ�ļ�����
	* @param		[in]	const tString& strFile:�ļ�·��
	* @return		�� 
	* @remarks		��
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2013/6/5       1.0         ����ӡ      ����
    ******************************************************************************/
	void Draw(const tString& strFile);

	 /*****************************************************************************
	* ����:			��ʾͼƬ
	* @param		[in]	const tString& strFile:�ļ�·��
	* @param		[in]	BOOL bShow: TRUE ��ʾ��FLASE ����
	* @return		�� 
	* @remarks		��
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2013/6/5       1.0         ����ӡ      ����
    ******************************************************************************/
	void ShowImage( const tString& strFile, BOOL bShow = TRUE );

	void SetMainFrameWnd(HWND hWnd);

	void SetScrollContainerUI(CommonScrollContainerUI* pScrollContainerUI);

	void ShowPageDown( const tString& strFile );

protected:
	CPaintManagerUI& m_cPaintMng;

private:
	HWND m_hWndMain;
	CPreviewIF g_clsPreview;	//Ԥ���ӿ�

	CommonScrollContainerUI* m_pScrollContainerUI; 
	
	CLabelUI* m_pShowImgLabelUI;
};

#endif // PREWND_H