/*****************************************************************************
ģ����      : CAddrbookExpLogic
�ļ���      : addrbookexplogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: logic��ַ�����뵼��ҳ��
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/12/07     1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_ADDRBOOKEXPLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
#define AFX_ADDRBOOKEXPLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CAddrbookExpLogic :public CWndLogicBase, public ISingleTon<CAddrbookExpLogic> 
{
public:  
    CAddrbookExpLogic();
	virtual ~CAddrbookExpLogic();

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
		/**	 
	* ����:  ��������ַ��
	* @return   
	* @remarks	 
	*/
	bool OnBtnImportAddrbook( const IArgs & arg );
	
		/**	 
	* ����:  ���������ַ��
	* @return   
	* @remarks	 
	*/
	bool OnBtnExportAddrbook( const IArgs & arg );

		 /**	 
	* ����:  ����������
	* @return   
	* @remarks	 
	*/	
	bool OnBtnImportAddrbookScan( const IArgs & arg );
	
		 /**	 
	* ����:  ����������
	* @return   
	* @remarks	 
	*/
	bool OnBtnExportAddrbookScan( const IArgs & arg );
	
		/**	 
	* ����:  ���ļ�Ŀ¼
	* @return   
	* @remarks	 
	*/	
	bool OnBtnExportFolder( const IArgs & arg );

  /**	 
	* ����:  ���´������
	* @return   
	* @remarks	 
	*/
	bool OnTransAddrbookProgress( const IArgs & arg );

		/**	 
	* ����: ����Ŀ¼�����仯
	* @return   bool
	* @remarks  
	*/
	bool OnImpFolderEditChange( const IArgs & arg );

		/**	 
	* ����: ����Ŀ¼�����仯
	* @return   bool
	* @remarks  
	*/
	bool OnExpFolderEditChange( const IArgs & arg );

protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();
	
 
private:
		/**	 
	* ����: FTP��������
	* @return   bool
	* @remarks  
	*/
	void CleanTransfer();

		/**	 
	* ����: ���غ���
	* @param    const String strCheckFileName   [in]     ��������ļ��� 
	* @return   bool
	* @remarks  
	*/
	BOOL DownloadCore(const String& strCheckFileName); 


		/**	 
	* ����: �ϴ�����
	* @param    const String strCheckFileName   [in]     ��������ļ��� 
	* @return   bool
	* @remarks  
	*/
	BOOL UploadCore(const String& strCheckFileName); 

private:
	const String m_strEdtImport;  
	const String m_strProgressImp;  
	const String m_strEdtExport;
	const String m_strProgressExp; 

	Window* m_pWnd;

	CFtpCtrl m_cFtp;
	EM_FTPTRANS_TYPE m_emFtpTransType;  //��ǰLogic�е��뵼������  
	EmFtpStatus m_emFileFtpStatus;      //��ǰFTP����״̬
    u32 m_dwTotalFileSize;				//���뵼���ļ��ܴ�С
	Value_ProgressPos m_valProgress;    //�������

	String m_strCurTransRemoteFileFullPath;     //��ǰ������ļ��ڷ������˵�ȫ·��

};

#define ADDRBOOKEXPLOGICRPTR    CAddrbookExpLogic::GetSingletonPtr()               //��ַ�����뵼��logicָ��

#endif // !defined(AFX_ADDRBOOKEXPLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
