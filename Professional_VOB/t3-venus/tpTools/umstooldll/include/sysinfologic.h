/*****************************************************************************
ģ����      : CSysInfoLogic
�ļ���      : sysinfologic.h
����ļ�    : 
�ļ�ʵ�ֹ���: logic������Ϣҳ��
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/12/05     1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_SYSINFOLOGIC_H__A4F911AB_BD71_4AF5_9E24_9D1D82DC07E8__INCLUDED_)
#define AFX_SYSINFOLOGIC_H__A4F911AB_BD71_4AF5_9E24_9D1D82DC07E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CSysInfoLogic  : public CWndLogicBase, public ISingleTon<CSysInfoLogic>  
{
public:  
    CSysInfoLogic();
	virtual ~CSysInfoLogic();
public:  
	void UpdateServerTime();

public:
	virtual bool RegCBFun();
	virtual bool UnRegFunc( );
    virtual bool InitWnd( const IArgs & arg );

	/**	 
	* ����:  ��ʼ������ע����½������ʼ��
	* @return   
	* @remarks	 
	*/
	 virtual void InitLogicData();

   /**	 
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

protected:
	bool OnBtnRealTimeRefresh( const IArgs & arg );
	bool OnBtnImportAuth( const IArgs & arg );
	bool OnBtnExportAuth( const IArgs & arg );
	bool OnBtnSyncSevr( const IArgs & arg );

protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();

	HRESULT OnUmsVerNotify( WPARAM wparam, LPARAM lparam);
	HRESULT OnUmsSipNotify( WPARAM wparam, LPARAM lparam);
	HRESULT OnUmsGkNotify( WPARAM wparam, LPARAM lparam);
	HRESULT OnUmsAuthCountNotify( WPARAM wparam, LPARAM lparam);
	HRESULT OnUmsConfCountNotify( WPARAM wparam, LPARAM lparam);
	HRESULT OnUmsSysInfoNotify( WPARAM wparam, LPARAM lparam);
	HRESULT OnUmsSysTimeNotify( WPARAM wparam, LPARAM lparam);
	HRESULT OnTvwUsedNotify( WPARAM wparam, LPARAM lparam);
	HRESULT OnBoardUsedNotify( WPARAM wparam, LPARAM lparam);

	HRESULT OnRegInfoNty( WPARAM wparam, LPARAM lparam);
	HRESULT OnRegGkNty( WPARAM wparam, LPARAM lparam);
	

private:
	void SyncTimeToSevr();


private:
	const String m_strStcHardWareVer;  
	const String m_strStcSoftWareVer;  
	const String m_strStcSipSevr;  
	const String m_strStcGkSevr;  
	const String m_strStcAuthCount;  
	const String m_strStcSysTimeValue;  
	const String m_strStcCpuRate;  
	const String m_strStcMemeryRate;  
	const String m_strStcCoufCount;  
	const String m_strStcMixAudioPer;  
	const String m_strStcImageCompondPer;  
	const String m_strStcTvwPer;  
	const String m_strStcSteamAdaptePer;     
	const String m_strBtnImportAuth;  
	const String m_strBtnExportAuth;  
	const String m_strBtnSyncSevr;  
	const String m_strBtnRealTimeRefresh;   

	BOOL m_bSetTimer;

};

#define SYSINFOLOGICRPTR    CSysInfoLogic::GetSingletonPtr()               //ums������Ϣlogicָ��

#endif // !defined(AFX_SYSINFOLOGIC_H__A4F911AB_BD71_4AF5_9E24_9D1D82DC07E8__INCLUDED_)
