/*****************************************************************************
ģ����      : CImpCommonDlgLogic
�ļ���      : impcommondlglogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: logic�ϴ������룩ͨ�õ�������  �磺��Ȩ���롢������ؽ���   ���������ͬ  ͨ����������
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/01/28     1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_IMPCOMMONDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
#define AFX_IMPCOMMONDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CImpCommonDlgLogic :public CWndLogicBase, public ISingleTon<CImpCommonDlgLogic>  
{
public:  
    CImpCommonDlgLogic();
	virtual ~CImpCommonDlgLogic();

public:
	void SerSevrIpAddr(u32 dwCurSevr){ m_dwCurSevr = dwCurSevr;};	//���õ�ǰ������������ַ	
	u32 GetSevrIpAddr(){return m_dwCurSevr;};						//�õ���ǰ������������ַ
	
	void SetEMEqpType(EMEqpType emEqpTy){m_emEqpTy = emEqpTy;};
	EMEqpType GetEMEqpType(){ return m_emEqpTy;};

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

public:
	bool OnBtnClose( const IArgs & arg );
	
	/**	 
	* ����: �����ϴ�����
	* @return   bool
	* @remarks  
	*/
	bool OnUploadProgress( const IArgs & arg );

	/**	 
	* ����: ������
	* @return   bool
	* @remarks  
	*/
	bool OnBtnImportScan( const IArgs & arg );

		/**	 
	* ����: Ŀ¼�����仯
	* @return   bool
	* @remarks  
	*/
	bool OnFolderEditChange( const IArgs & arg );

	/**	 
	* ����: ������Ȩ
	* @return   bool
	* @remarks  
	*/
	bool OnBtnImportAuthWork( const IArgs & arg );

	/**	 
	* ����: ��������
	* @return   bool
	* @remarks  
	*/
	bool OnBtnUpgradeBoardWork( const IArgs & arg );

protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();
	
private:
		/**	 
	* ����: �ϴ�����
	* @param    const String strRemotePath      [in]     linux�˴��洢·��
	* @param    const String strLocalFile       [in]     ��������ļ�ȫ·�� 
	* @param    const String strCheckFileName   [in]     ��������ļ��� 
	* @return   bool
	* @remarks  
	*/
	BOOL UploadCore( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName, BOOL bIsDefServ = TRUE ); 

		/**	 
	* ����: FTP��������
	* @return   bool
	* @remarks  
	*/
	void CleanTransfer();

	/**	 
	* ����: ˢ�������ļ��б�
	* @return   ��
	* @remarks  
	*/
	void UpdateUpgradeFileList();

private:
	const String m_strEdtSaveFolder;
	const String m_strProgressImp;
	const String m_strLstUpgradeFile;

	CFtpCtrl m_cFtp;
	EmFtpStatus m_emFileFtpStatus;
    u32 m_dwTotalFileSize;				//�����ļ��ܴ�С
	Window* m_pWnd;
	Value_ProgressPos m_valProgress;    //�������

	std::vector<TUmsToolFile> m_vecUpgradeFile;

	String m_strCurTransRemoteFileFullPath;     //��ǰ������ļ��ڷ������˵�ȫ·��

	EMEqpType m_emEqpTy;				//���õ�ǰ��������������
	CString m_strCurTransFile;	    	//��ǰ����������ļ���
	u32 m_dwCurSevr;                    //��ǰ����������
	BOOL m_bReUploadCore;               //����һ������ʧ��,�Ƿ��Ѿ�����  xhx
};

#define IMPCOMMONLOGICRPTR    CImpCommonDlgLogic::GetSingletonPtr()               //�ϴ������룩ͨ�õ�������logicָ��

#endif // !defined(AFX_IMPCOMMONDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
