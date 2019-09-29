/*****************************************************************************
ģ����      : CBackupCfgLogic
�ļ���      : backupcfglogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: 1+1��������ҳ��
����        : �컪��
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/7/29      1.0         �컪��		����
******************************************************************************/
#if !defined(AFX_BACKUPCFGLOGIC_H__5F7CF890_69C3_4BC3_A76E_382BB893ADED__INCLUDED_)
#define AFX_BACKUPCFGLOGIC_H__5F7CF890_69C3_4BC3_A76E_382BB893ADED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CBackupCfgLogic : public CWndLogicBase, public ISingleTon<CBackupCfgLogic>  
{
public:
	CBackupCfgLogic();
	virtual ~CBackupCfgLogic();

public:  
	/**	 
	* ����:  ע���logic�����еĻص�����
	* @return  void
	* @remarks	�ڴ�ע��Ļص�������Ҫ�ǿؼ�����Ӧ�¼�����Ϊ��Ա�ص�����,Ҳ��ע�������Ļص�����
	                    ע��ʱ��Ӧע��ص�������Ӧ���ӵ��������򣺡�����::��������
	*/
	virtual bool RegCBFun();

	/**	 
	* ����:  ע��Ҫ�������Ϣ
	* @return  void
	* @remarks	 ע������Ϣ���ܷ��͵����߼�ģ�飬���򣬽��ղ�������Ϣ
	*/
	virtual void RegMsg(); 

	/**	 
	* ����:  ע���ص�����
	* @return  void
	* @remarks	 
	*/
	virtual bool UnRegFunc( );

	/**	 
	* ����:  ע��Ҫ�������Ϣ
	* @return  void
	* @remarks	 
	*/
	virtual void UnRegMsg();

	/**	 
	* ����:  ��ʼ����������,
	* @return  void
	* @remarks	���ڸù��ܱ��������ؼ����Բ���xml����ؼ��󶨣�
	                    ��Ҫ��RegCBFun������ע�ᵽ�ص���������ģ�� 
	*/
    virtual bool InitWnd( const IArgs & arg );

    /**	 
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

	/**	 
	* ����: ��ʼ����������
	* @return   void
	* @remarks  
	*/
	virtual void InitLogicData();
	
protected: 
	/**	 
	* ����: �����Ϊ���û�
	* @return   bool
	* @remarks  
	*/
	bool OnBtnRadioIsAsHost( const IArgs & arg );

	/**	 
	* ����: �����Ϊ���û�
	* @return   bool
	* @remarks  
	*/
	bool OnBtnRadioIsAsBackup( const IArgs & arg );

	/**	 
	* ����: ������ö��������ʱ��
	* @return   bool
	* @remarks  
	*/
	bool OnBtnRadioTime( const IArgs & arg );

	/**	 
	* ����: ������ö���������
	* @return   bool
	* @remarks  
	*/
	bool OnBtnRadioCount( const IArgs & arg );

	/**	 
	* ����: �Ƿ���1+1���ݹ���
	* @return   bool
	* @remarks  
	*/
	bool OnBtnSwitchBackupClick( const IArgs & arg );

private:
// 	u8 m_abyBackupInfo[4];                 //��¼ѡ���radiobtn��״̬
// 	u8 m_abyOldBackupInfo[4];              //��¼ԭradiobtn��״̬

	//���߼���Ԫ��Ӧ�����пؼ���  
	const String m_strDlgAsHost;           //��Ϊ���û��Ի���
	const String m_strDlgAsBackup;         //��Ϊ���û��Ի���
	const String m_strBtnRadioAsHost;      //��Ϊ���û�
	const String m_strBtnRadioAsBackup;    //��Ϊ���û�
	const String m_strBtnRadioTime1;       //���������ʱ�� 1��
	const String m_strBtnRadioTime2;       //���������ʱ�� 2��
	const String m_strBtnRadioTime3;       //���������ʱ�� 3��
	const String m_strBtnRadioCount1;      //���������� 1��
	const String m_strBtnRadioCount2;      //���������� 2��
	const String m_strBtnRadioCount3;      //���������� 3��
	const String m_strIPBackupIP;          //���û�IP��ַ
};

#define BACKUPCFGLOGICRPTR    CBackupCfgLogic::GetSingletonPtr()           //BackupCfgLogicָ��

#endif // !defined(AFX_BACKUPCFGLOGIC_H__5F7CF890_69C3_4BC3_A76E_382BB893ADED__INCLUDED_)
