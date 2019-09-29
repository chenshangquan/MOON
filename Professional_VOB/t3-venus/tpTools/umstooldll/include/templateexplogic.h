/*****************************************************************************
ģ����      : CTemplateExpLogic
�ļ���      : templateexplogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: logic����ģ�嵼�뵼��ҳ��
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/12/07     1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_TEMPLATEEXPLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
#define AFX_TEMPLATEEXPLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CTemplateExpLogic :public CWndLogicBase, public ISingleTon<CTemplateExpLogic> 
{
public:  
    CTemplateExpLogic();
	virtual ~CTemplateExpLogic();

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
	* ����:  ����������ģ��
	* @return   
	* @remarks	 
	*/
	bool OnBtnImportTmp( const IArgs & arg );
	
		/**	 
	* ����:  �����������ģ��
	* @return   
	* @remarks	 
	*/
	bool OnBtnExportTmp( const IArgs & arg );

		 /**	 
	* ����:  ����������
	* @return   
	* @remarks	 
	*/	
	bool OnBtnImportTmpScan( const IArgs & arg );
	
		 /**	 
	* ����:  ����������
	* @return   
	* @remarks	 
	*/
	bool OnBtnExportTmpScan( const IArgs & arg );
	
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
	bool OnTransTmpProgress( const IArgs & arg );

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
	
	HRESULT OnExpTemplateRsp( WPARAM wparam, LPARAM lparam);

 
private:
		/**	 
	* ����: FTP��������
	* @return   bool
	* @remarks  
	*/
	void CleanTransfer();

		/**	 
	* ����: ���غ���
	* @param    void
	* @return   bool
	* @remarks  
	*/
	BOOL DownloadCore(); 


		/**	 
	* ����: �ϴ�����
	* @param    void
	* @return   bool
	* @remarks  
	*/
	BOOL UploadCore(); 

private:
	const String m_strEdtImport;  
	const String m_strProgressImp;  
	const String m_strEdtExport;
	const String m_strProgressExp; 
	const String m_strBtnExportTmp; 
	const String m_strBtnExportScan; 

	Window* m_pWnd;

	CFtpCtrl m_cFtp;
	EM_FTPTRANS_TYPE m_emFtpTransType;  //��ǰLogic�е��뵼������  
	EmFtpStatus m_emFileFtpStatus;      //��ǰFTP����״̬
    u32 m_dwTotalFileSize;				//���뵼���ļ��ܴ�С
	Value_ProgressPos m_valProgress;    //�������
	String m_strImpFileName;            //�������ļ���
	String m_strExpFileName;            //�������ļ���

	String m_strCurTransRemoteFileFullPath;     //��ǰ������ļ��ڷ������˵�ȫ·��

};

#define TEMPLATEEXPLOGICRPTR    CTemplateExpLogic::GetSingletonPtr()               //����ģ�嵼�뵼��logicָ��

#endif // !defined(AFX_TEMPLATEEXPLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
