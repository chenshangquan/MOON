/*****************************************************************************
ģ����      : CSessionIns
�ļ���      : sessionins.h
����ļ�    : 
�ļ�ʵ�ֹ���: umstool ȫ��Sessionģ��
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/11/21     1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_SESSIONINS_H__B1C93EC9_9BDD_40C7_BA07_694169421352__INCLUDED_)
#define AFX_SESSIONINS_H__B1C93EC9_9BDD_40C7_BA07_694169421352__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSessionIns : public ISingleTon<CSessionIns>
{
public:
	CSessionIns();
	virtual ~CSessionIns();

public:

	/*=============================================================================
    �� �� ��:CreateSession
    ��    ��:������Umsͨ�ŻỰ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:return BOOL �ɹ�����TRUE;ʧ�ܷ���FALSE
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/11/21  1.0     ����ӡ    ����
    =============================================================================*/
	BOOL  CreateSession( u16 wAppId = AID_UMSTOOL2UMS_APP );


	/*=============================================================================
    �� �� ��:DisConnectUms
    ��    ��:������Umsͨ�ŻỰ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:return BOOL �ɹ�����TRUE;ʧ�ܷ���FALSE
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/11/21  1.0     ����ӡ    ����
    =============================================================================*/
	BOOL  DisConnectUms();

	/*=============================================================================
    �� �� ��:DesdroySession
    ��    ��:������Umsͨ�ŻỰ
    ��    ��:��
    ע    ��:��
    �� �� ֵ:return BOOL �ɹ�����TRUE;ʧ�ܷ���FALSE
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/11/21  1.0     ����ӡ    ����
    =============================================================================*/
	void DesdroySession();

	CUmsSessionCtrlIF* GetSessionCtrlPtr(){ return m_pUmsSessCtrlIF;};
	CUserCtrlIF* GetUserCtrlPtr(){ return m_pUserCtrlIF;};
	CUmsSysInfoCtrlIF* GetSysInfoCtrlPtr(){ return m_pSysInfoCtrlIF;};
	CUmsTvwBoardCtrlIF* GetTvwBoardCtrlPtr(){ return m_pTvwBoardCtrlIF;};
	CUmsBoardCtrlIF* GetBoardCtrlPtr(){ return m_pBoardCtrlIFIF;};
	CUmsExportCtrlIF* GetExportCtrPtr(){ return m_pExportCtrlIF;};
	CUmsConfigCtrlIF* GetConfigCtrlPtr(){ return m_pConfigCtrlIF;};
	CUmsNetMngCtrlIF* GetNetMngCtrlPtr(){ return m_pNetMngCtrlIF;};
	CUmsVTRCtrlIF* GetVTRCtrlPtr(){ return m_pVTRCtrlIF;};

private:
	CUmsSessionCtrlIF*    m_pUmsSessCtrlIF;		    //ums�ĻỰ�˽ӿ�
    CUserCtrlIF*	      m_pUserCtrlIF;			//ums�û����ƽӿ�
	CUmsSysInfoCtrlIF*    m_pSysInfoCtrlIF;         //umsϵͳ��Ϣ�ӿ�
	CUmsTvwBoardCtrlIF*   m_pTvwBoardCtrlIF;        //ums����ǽ�忨�ӿ�
	CUmsBoardCtrlIF*      m_pBoardCtrlIFIF;         //ums����ӿ�
	CUmsExportCtrlIF*     m_pExportCtrlIF;          //ums���뵼���ӿ�
	CUmsConfigCtrlIF*     m_pConfigCtrlIF;          //ums���ýӿ�
	CUmsNetMngCtrlIF*     m_pNetMngCtrlIF;			//ums���ܽӿ�
	CUmsVTRCtrlIF*		  m_pVTRCtrlIF;				//ums¼����ӿ�


};

#define SESSIONPTR    CSessionIns::GetSingletonPtr()     //Sessionָ��

#endif // !defined(AFX_SESSIONINS_H__B1C93EC9_9BDD_40C7_BA07_694169421352__INCLUDED_)
