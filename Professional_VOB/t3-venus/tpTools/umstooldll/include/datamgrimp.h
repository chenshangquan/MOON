/*****************************************************************************
ģ����      : CDataMgrImp
�ļ���      : datamgrimp.h
����ļ�    : 
�ļ�ʵ�ֹ���: umstool ���ݹ���ģ��
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/11/21     1.0         ����ӡ      ����
******************************************************************************/

#if !defined(AFX_COMMONMGRIF_H__25AF60AB_76A1_4E49_B81C_E81E55B0A801__INCLUDED_)
#define AFX_COMMONMGRIF_H__25AF60AB_76A1_4E49_B81C_E81E55B0A801__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "umclib.h" 

class CDataMgrImp : public CWnd, public ISingleTon<CDataMgrImp>
{
public:
	CDataMgrImp();
	virtual ~CDataMgrImp();

	/*=============================================================================
    �� �� ��:CreateDataMgr
    ��    ��:�õ����ݹ���ָ��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:CDataMgrImp*
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/11/21  1.0     ����ӡ    ����
    =============================================================================*/
	BOOL CreateDataMgr();

	/*=============================================================================
    �� �� ��:DestroyDataMrg
    ��    ��:�������ݹ���ָ��
    ��    ��:��
    ע    ��:��
    �� �� ֵ:��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/11/21  1.0     ����ӡ    ����
    =============================================================================*/
    void DestroyDataMrg();

	HWND GetRecvWnd();

	
	//---------------CUmsConfigCtrlҵ������------------------
	TTPEthnetInfo		GetEthnetCfgData();
	TTPSipRegistrarCfg  GetSipCfgData();
	TTPGKCfg			GetGkCfgData();
	TTPTime				GetUmsSystimeData();

	//---------------CUmsSysInfoCtrlҵ������----------------
	TUmsVersion			GetUmsVerData();
	TToolSysInfo		GetUmsSysInfoData();
	std::pair<int,int>  GetAuthCountData();
	u32				    GetConfCountData();

	//---------------CUmsBoardCtrlҵ������----------------
	TTPBrdUsedInfo		GetUmsBoardUsedData();
	TTPBrdUsedInfo		GetUmsTvwUsedData();

	//---------------CUmsTvwBoardCtrlҵ������----------------
	std::multimap<u8,THduCfg> GetUmsTvwBoardData();
	THduStyleData GetUmsTvwStyleData();

	//---------------CUmsNetMngCtrlҵ������----------------
	u16 GetUmsNetMngData( vector<TTPNMServerCfg> &vecTTPNMServerCfg );

	//---------------CUmsVTRCtrlҵ������----------------
	u16 GetUmsVTRData( vector<TVcrCfg> &vecTVcrCfg );

protected:
    virtual BOOL PreCreateWindow( CREATESTRUCT& cs );
    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam); 

	// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CDataMgrImp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:

};

#define DATAMGRPTR    CDataMgrImp::GetSingletonPtr()               //����ָ��

#endif // !defined(AFX_COMMONMGRIF_H__25AF60AB_76A1_4E49_B81C_E81E55B0A801__INCLUDED_)
