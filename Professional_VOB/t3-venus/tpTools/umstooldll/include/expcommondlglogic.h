/*****************************************************************************
ģ����      : CExpCommonDlgLogic
�ļ���      : Expcommondlglogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: logic���أ�������ͨ�õ�������  �磺��Ȩ������������־����  ���������ͬ  ͨ����������
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/01/28     1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_EXPCOMMONDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
#define AFX_EXPCOMMONDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CExpCommonDlgLogic :public CWndLogicBase, public ISingleTon<CExpCommonDlgLogic>  
{
public:  
    CExpCommonDlgLogic();
	virtual ~CExpCommonDlgLogic();

public:  
	virtual bool RegCBFun();
	virtual bool UnRegFunc( );
    virtual bool InitWnd( const IArgs & arg );

   /**	 
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

protected:
	bool OnBtnClose( const IArgs & arg );

	/**	 
	* ����: ������־
	* @return   bool
	* @remarks  
	*/
	bool OnBtnDownloadLogWork( const IArgs & arg );
	
	/**	 
	* ����: ������Ȩ
	* @return   bool
	* @remarks  
	*/
	bool OnBtnExportAuthWork( const IArgs & arg );	

	/**	 
	* ����: ����ums����
	* @return   bool
	* @remarks  
	*/
	bool OnBtnExportConfigWork( const IArgs & arg );	

protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();

	HRESULT OnExpAuthRsp( WPARAM wparam, LPARAM lparam);
	
	/**	 
	* ����: �������ؽ���
	* @return   bool
	* @remarks  
	*/
	bool OnDownloadProgress( const IArgs & arg );

	/**	 
	* ����: ������
	* @return   bool
	* @remarks  
	*/
	bool OnBtnExportScan( const IArgs & arg );

	/**	 
	* ����: ������ļ�Ŀ¼
	* @return   bool
	* @remarks  
	*/
	bool OnBtnOpenFolder( const IArgs & arg );

		/**	 
	* ����: Ŀ¼�����仯
	* @return   bool
	* @remarks  
	*/
	bool OnFolderEditChange( const IArgs & arg );

private:
		/**	 
	* ����: FTP��������
	* @return   bool
	* @remarks  
	*/
	void CleanTransfer();

		/**	 
	* ����: ���غ���
	* @param    const String strFilePath        [in]     ��������ļ�·��
	* @param    const String strCheckFileName   [in]     ��������ļ��� 
	* @return   bool
	* @remarks  
	*/
	BOOL DownloadCore(const String& strFilePath, const String& strCheckFileName); 

private:
	const String m_strEdtSaveFolder;
	const String m_strProgressExp;

	CFtpCtrl m_cFtp;
	EmFtpStatus m_emFileFtpStatus;
    u32 m_dwTotalFileSize;				//�����ļ��ܴ�С
	Window* m_pWnd;
	Value_ProgressPos m_valProgress;    //�������

};

#define EXPCOMMONLOGICRPTR    CExpCommonDlgLogic::GetSingletonPtr()               //���أ�������ͨ�õ�������logicָ��

#endif // !defined(AFX_EXPCOMMONDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
