/*****************************************************************************
ģ����      : CExpCommonDlgLogic
�ļ���      : impcommonlogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: logic�ϴ������룩ͨ�õ�������  �磺���������������ؽ���  ���������ͬͨ����������(��ֲumstool������cnstool)
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/01/28     1.0         ����ӡ      ����
2013/03/21				   ������      �޸���ֲ 
******************************************************************************/
#if !defined(AFX_IMPCOMMONLOGIC_H__31BC88EC_E3B5_47B4_998A_A726B272AD12__INCLUDED_)
#define AFX_IMPCOMMONLOGIC_H__31BC88EC_E3B5_47B4_998A_A726B272AD12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CImpCommonDlgLogic : public CLogicBase, public ISingleTon<CImpCommonDlgLogic>    
{
public:
	CImpCommonDlgLogic();
	virtual ~CImpCommonDlgLogic();

public:  
	/** ����:  ע��ص�����
	*  @param[in] 
	*  @return 
	*  @remarks  �ڶ�ȡxml�ļ�ʱ��,���������ע��ĺ���
	*/
	virtual void RegCBFun();
	/** ����:  ��ע��ص�����
	*  @param[in] 
	*  @return 
	*  @remarks  �����溯���෴,ע��ע��ĺ���
	*/
	virtual void UnRegFunc();
	/** ����:  ��ʼ������
	*  @param[in] 
	*  @return 
	*  @remarks  �ڶ�ȡxml�ļ�ʱ�����,������������ݳ�ʼ������
	*/	
    virtual bool InitWnd( const IArgs & arg ); 

   /**	 
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear();
	
public:
	void SetSevrIpAddr(u32 dwCurSevr){ m_dwCurSevr = dwCurSevr;};	//���õ�ǰ������������ַ	
	u32 GetSevrIpAddr(){return m_dwCurSevr;};						//�õ���ǰ������������ַ

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
	* ����: �������������
	* @return   bool
	* @remarks  
	*/
	bool OnBtnImportCamCfg( const IArgs & arg );

	/**	 
	* ����: cns����
	* @return   bool
	* @remarks  
	*/
	bool OnBtnUpgradeCns( const IArgs & arg );

	EmFtpStatus GetFtpStatus() { return m_emFileFtpStatus; }

	//ftp��ʱ��Է������ļ��Ĵ���
	void ClearTransFile();
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
//	void UpdateUpgradeFileList();

private:
	const String m_strEdtSaveFolder;
	const String m_strProgressImp;
	const String m_strLstUpgradeFile;

	CFtpCtrl m_cFtp;
	EmFtpStatus m_emFileFtpStatus;
    u32 m_dwTotalFileSize;				//�����ļ��ܴ�С
	Window* m_pWnd;
	Value_ProgressPos m_valProgress;    //�������

	String m_strImpFileName;			//����T300���ļ�����
	String m_strCurTransRemoteFileFullPath;     //��ǰ������ļ��ڷ������˵�ȫ·��

	CString m_strCurTransFile;	    	//��ǰ����������ļ���
	u32 m_dwCurSevr;                    //��ǰ����������
};

#define IMPCOMMONLOGICRPTR    CImpCommonDlgLogic::GetSingletonPtr()               //�ϴ������룩ͨ�õ�������logicָ��

#endif // !defined(AFX_IMPCOMMONLOGIC_H__31BC88EC_E3B5_47B4_998A_A726B272AD12__INCLUDED_)
