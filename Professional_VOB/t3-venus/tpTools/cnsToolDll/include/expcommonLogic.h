/*****************************************************************************
ģ����      : CExpCommonDlgLogic
�ļ���      : expcommonlogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: ���أ�������ͨ�õ�������  �磺�������á�������־����  ���������ͬͨ����������(��ֲumstool������cnstool)
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/01/28     1.0         ����ӡ      ����
2013/03/21				   ������      �޸���ֲ 
******************************************************************************/
#if !defined(AFX_EXPCOMMONLOGIC_H__CF8FB18A_BC99_46F4_B98F_21441701BA58__INCLUDED_)
#define AFX_EXPCOMMONLOGIC_H__CF8FB18A_BC99_46F4_B98F_21441701BA58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"


class CExpCommonDlgLogic : public CLogicBase, public ISingleTon<CExpCommonDlgLogic>    
{
public:
	CExpCommonDlgLogic();
	virtual ~CExpCommonDlgLogic();

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

protected:
	bool OnBtnClose( const IArgs & arg );

	/**	 
	* ����: ������־
	* @return   bool
	* @remarks  
	*/
	bool OnBtnDownloadLogWork( const IArgs & arg );
	
	/**	 
	* ����: ����cns����
	* @return   bool
	* @remarks  
	*/
	bool OnBtnExportConfigWork( const IArgs & arg );	
	
	/**	 
	* ����: �������������
	* @return   bool
	* @remarks  
	*/
	bool OnBtnExportCameraCfg( const IArgs & arg );	

protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();
	
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

	u32 m_nCount;
	vector<String> m_vctDownFile;
};

#define EXPCOMMONLOGICRPTR    CExpCommonDlgLogic::GetSingletonPtr()               //���أ�������ͨ�õ�������logicָ��

#endif // !defined(AFX_EXPCOMMONLOGIC_H__CF8FB18A_BC99_46F4_B98F_21441701BA58__INCLUDED_)
