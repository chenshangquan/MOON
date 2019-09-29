// addrbookExpLogic.h: interface for the AddrbookExpLogic class.
//
//////////////////////////////////////////////////////////////////////
/*****************************************************************************
ģ����      : CAddrbookExpLogic
�ļ���      : addrbookExpLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: ��ַ����Ϣ����
����        : ������
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/02/04     1.0         ������      ����
******************************************************************************/

#if !defined(AFX_ADDRBOOKEXPLOGIC_H__07ADDBF0_47EB_4983_B5EA_7E3B34DCDF78__INCLUDED_)
#define AFX_ADDRBOOKEXPLOGIC_H__07ADDBF0_47EB_4983_B5EA_7E3B34DCDF78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

enum EM_FTPTRANS_TYPE      //�ļ�����򵼳�����
{
	em_FTPTRANS_IMPORT,
	em_FTPTRANS_EXPORT,
};

class CAddrbookExpLogic : public CLogicBase, public ISingleTon<CAddrbookExpLogic>  
{
public:
	CAddrbookExpLogic();
	virtual ~CAddrbookExpLogic();

//CLogicBase
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
	virtual void UnRegFunc( );
	
	/** ����:  ��ʼ������
	*  @param[in] 
	*  @return 
	*  @remarks  �ڶ�ȡxml�ļ�ʱ�����,������������ݳ�ʼ������
	*/	
    virtual bool InitWnd( const IArgs & arg ); 
	
	/** ����:  ������
	*  @param[in] 
	*  @return 
	*  @remarks  �ڴ��ڹرյ�ʱ�����,��մ�������
	*/		
    virtual void Clear() ;
protected:
		
	/** ����: ע����Ϣ,��������lib���з���������Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	virtual void RegMsg(); 
		
	/** ����: ��ע����Ϣ,�����溯���෴,ע��ע�����Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	virtual void UnRegMsg();

	/** ����:  ���շ������Ļ᳡��Ϣ�����½���
	*  @param[in] 
	*  @return �ɹ�����true,ʧ�ܷ���false
	*  @remarks 
	*/
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

};

#define ADDRBOOKEXPLOGICRPTR    CAddrbookExpLogic::GetSingletonPtr()               //��ַ�����뵼��logicָ��

#endif // !defined(AFX_ADDRBOOKEXPLOGIC_H__07ADDBF0_47EB_4983_B5EA_7E3B34DCDF78__INCLUDED_)
