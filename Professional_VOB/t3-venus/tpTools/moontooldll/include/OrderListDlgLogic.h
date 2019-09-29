// OrderListDlgLogic.h: interface for the COrderListDlgLogic class.
//
//////////////////////////////////////////////////////////////////////
/*****************************************************************************
�ļ���      : COrderListDlgLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: ϵͳ���ý���
����        : ���`�`
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2014/12/22     1.0         ���`�`      ����
******************************************************************************/
#if !defined(AFX_ORDERLISTDLGLOGIC_H__B06B345C_CF30_42B5_9B64_5F72C61D6269__INCLUDED_)
#define AFX_ORDERLISTDLGLOGIC_H__B06B345C_CF30_42B5_9B64_5F72C61D6269__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class COrderListDlgLogic : public CLogicBase, public ISingleTon<COrderListDlgLogic> 
{
public:
	COrderListDlgLogic();
	virtual ~COrderListDlgLogic();
	
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

	bool OnBtnImport( const IArgs& args );

	bool OnBtnExport( const IArgs& args );

	bool OnBtnModify( const IArgs& args );

	bool OnBtnInvoke( const IArgs& args );

	bool OnBtnDelete( const IArgs& args );

	bool OnBtnBack( const IArgs& args );

	bool OnClickOrderPosItem( const IArgs& args );

	bool OnClickOrderLstDlgBlack( const IArgs& args );
protected:
	
	HRESULT OnCamPreSetNty( WPARAM wparam, LPARAM lparam );

	HRESULT OnCamPreDelInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnCamPreModifyInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnCamPreSetInd( WPARAM wparam, LPARAM lparam );

	LRESULT OnSnapShotNty( WPARAM wparam, LPARAM lparam );
private:
	/** ����: ��Ϊռ��ͼƬ���ܱ�ʹ�ã����Բ����м�ͼƬ�����н���
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	void SwapImage( );
	/** ����: ����ͼƬ
	*  @param[in] bIsSwaped False  �����غ��ͼƬ����Ϊ326*256��С  True ����ʱ�м�ͼƬ�������������ͬ���Ŀ���������
	*  @return 
	*  @remarks  
	*/
	bool CopySnapShotImage( bool bIsSwaped );
	/** ����: �ͷ�ͼƬ��Դ
	*  @param[in] bIsRelOriPic  True ���������ͬ���Ŀ���ͼƬ�ͷ� False �ͷ�Temp���м����ͼƬ
	*  @return 
	*  @remarks  
	*/
	void ReleaseSnapShotImage( bool bIsRelOriPic );
	/** ����: ɾ������ͼƬ��Դ�󣬲������м����ͼƬ
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	void DeleteFile();
	/** ����: �����ļ�
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	void DownLoadFile( vector<TTPCamPreOption> &VecTCamPreInfo );
	BOOL DownloadCore(const String & strFileName );
	bool OnDownloadProgress( const IArgs & arg );
	/** ����: ���ͷ�����Download�ļ����¿���ͼƬ��Դ 
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	void ReleaseAllImage( vector<TTPCamPreOption> &VecTCamPreInfo );
	/** ����: ʹ��GDI����ͼƬʱ����ȡ��ͬͼƬ��clsidʹ�� 
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
	/** ����: ��1920*1080ͼƬ����Ϊ326*256ͼƬ
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool PictureChange(string strSrcName, string strDestName );
private:
	
	string							m_strLstOrderPos;
	std::vector<TTPCamPreOption>	m_vecTPCamPreInfo;

	TTPCamPre						m_tCamPreSel;
	BOOL							m_bIsSelect;
	CTransparentViewList*			m_pListWnd;	
	std::vector<string>				m_vecDownLoadfile;							//�������ؿ����ļ�
	std::vector<string>				m_vecWaitDownLoad;							//����ȴ����صĿ����ļ�
	EmFtpStatus m_emFileFtpStatus;
private:
	CFtpCtrl m_cFtp;
};


#endif // !defined(AFX_ORDERLISTDLGLOGIC_H__B06B345C_CF30_42B5_9B64_5F72C61D6269__INCLUDED_)
