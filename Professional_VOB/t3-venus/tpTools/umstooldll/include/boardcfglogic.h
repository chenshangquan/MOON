/*****************************************************************************
ģ����      : CBoardCfgLogic
�ļ���      : boardcfglogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: logic��������ҳ��
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/12/17     1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_BOARDCFGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
#define AFX_BOARDCFGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"
#include "touchlistdataproperty.h"

class CBoardCfgLogic :public CWndLogicBase, public ISingleTon<CBoardCfgLogic> 
{
public:  
    CBoardCfgLogic();
	virtual ~CBoardCfgLogic();

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

	/**	 
	* ����: �жϵ�ǰ���޻��飬���¿ؼ�״̬
	* @return   bool
	* @remarks  
	*/
	void UpdateBtnState();

public:
		/**	 
	* ����: ����л�ҳ������  �б仯����
	* @return   BOOL:TRUE�����л�    FALSE��ֹ�л�
	* @remarks  
	*/
	BOOL CheckPageDataChangeToSave();

protected:
		/**	 
	* ����: ����㵥���б�
	* @return   bool
	* @remarks  
	*/
	bool OnBoardLstFloorItem( const IArgs & arg );

	/**	 
	* ����: ����ɾ��
	* @return   bool
	* @remarks  
	*/
	bool OnBtnBoardDel( const IArgs & arg );

	/**	 
	* ����: �����޸�
	* @return   bool
	* @remarks  
	*/
	bool OnBtnBoardModify( const IArgs & arg );

	/**	 
	* ����: �������
	* @return   bool
	* @remarks  
	*/
	bool OnBtnBoardAdd( const IArgs & arg );

	/**	 
	* ����: ��������
	* @return   bool
	* @remarks  
	*/
	bool OnBtnBoardReboot( const IArgs & arg );

	/**	 
	* ����: ��������
	* @return   bool
	* @remarks  
	*/
	bool OnBtnBoardUpgrade( const IArgs & arg );

	/**	 
	* ����: ����ģʽɾ��
	* @return   bool
	* @remarks  
	*/
	bool OnBtnBoardModeDel( const IArgs & arg );

	/**	 
	* ����: ����ģʽ�޸�(����Ϊ ��� �޸ĺϲ�Ϊ����)
	* @return   bool
	* @remarks  
	*/
	bool OnBtnBoardModeSave( const IArgs & arg );

	/**	 
	* ����: ����ģʽ���ơ��������ݸı�
	* @return   bool
	* @remarks  
	*/
	bool OnBoardMdlEditChange( const IArgs & arg );

	/**	 
	* ����: apu��������������ı�
	* @return   bool
	* @remarks  
	*/
	bool OnBoardAudioMixNameEditChange( const IArgs & arg );

	/**	 
	* ����: apu���������������·��1�ı�
	* @return   bool
	* @remarks  
	*/
	bool OnBoardAudioMixNum1EditChange( const IArgs & arg );

	/**	 
	* ����: apu���������������·��2�ı�
	* @return   bool
	* @remarks  
	*/
	bool OnBoardAudioMixNum2EditChange( const IArgs & arg );

	/**	 
	* ����: ��������б�հ״�
	* @return   bool
	* @remarks  
	*/
	bool OnClickBoardLstBlack( const IArgs & arg );

	/**	 
	* ����: ����ģʽ�����Ƿ�ı�
	* @return   bool
	* @remarks  
	*/
	BOOL GetMdlDataChange(){ return m_bMdlDataChange;};


protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();

	HRESULT OnRefreshBoardInfoNotify( WPARAM wparam, LPARAM lparam);
	HRESULT OnOptBoardNotify( WPARAM wparam, LPARAM lparam);
	HRESULT OnOptBoardRsp( WPARAM wparam, LPARAM lparam);
	HRESULT OnDelBoardNotify( WPARAM wparam, LPARAM lparam);
	HRESULT OnOptBoardModeNotify( WPARAM wparam, LPARAM lparam);
	HRESULT OnOptBoardModeRsp( WPARAM wparam, LPARAM lparam);
	HRESULT OnBoardUpgradeRsp( WPARAM wparam, LPARAM lparam);
	HRESULT OnBoardBeginUpgrade( WPARAM wparam, LPARAM lparam);
	HRESULT OnConfCount( WPARAM wparam, LPARAM lparam);

private:
		/**	 
	* ����: ��ʼ��������л��˵��б�
	* @return   bool
	* @remarks  
	*/
	void InitFunMenu();

		/**	 
	* ����: ��ʼ�������б�����
	* @return   bool
	* @remarks  
	*/
	void InitBoardListData();

		/**	 
	* ����: ���������л��˵��б�
	* @return   bool
	* @remarks  
	*/
	bool OnMenuLstItem( const IArgs & arg );

		/**	 
	* ����: �л������˵�
	* @return   bool
	* @remarks  
	*/
	void SwitchTabWnd(CString strItemName);


	/**	 
	* ����: �����л������б�ҳ��ؼ�״̬
	* @return   bool
	* @remarks  
	*/
	void ResetBoardPageControl();
	
		/**	 
	* ����: ��ⵥ��ģʽ���ݵĺϷ���
	* @return   BOOL
	* @remarks  
	*/
	BOOL CheckPageBoardMdlData();

	String EmTpBoardRetToString(EmTpBoardRet emValue);				//�������Ӵ���ֵת��
	std::vector<CString> EMBrdTypeToVector(EMBrdType emBrdType);	//��������ת��
	String EMEqpTypeToString(EMEqpType emValue);					//��������ת��
	EMEqpType StringToEMEqpType(String strType);

	void SetMdlDataChange(BOOL bMdlDataChange){ m_bMdlDataChange = bMdlDataChange;};
	void SetLstNoSelItem(s32 nExceptLayarNo);						//����б��   �л���  �����б������в�������ѡ����

	void ShowBoardMdlCfg();				                    		//���õ���ģ����Ϣ������ʾ
	void EnableApuBoardMdlEdit(BOOL bEnable = TRUE);

	void ResetBoardMdlData(BOOL bDefault = TRUE);					//���õ���ģ����Ϣ

private:
	const String m_strLstBoardZeroFloor;
	const String m_strLstBoardFirstFloor;
	const String m_strLstBoardSecondFloor;
	const String m_strLstBoardThirdFloor;
	const String m_strLstMenuFloor;
	const String m_strEdtBoardModeName;
	const String m_strComboboxModeType;
	const String m_strBtnBoardDel;
	const String m_strBtnBoardModify;
	const String m_strBtnBoardAdd;
	const String m_strBtnBoardReboot;
	const String m_strBtnBoardUpgrade;
	const String m_strBtnBoardModeDel;
	const String m_strBtnBoardModeSave;
	const String m_strStBoardModeName;
	const String m_strStBoardModeType;
	const String m_strStAudioMixName1;
	const String m_strStAudioMixName2;
	const String m_strEdtAudioMixName1;
	const String m_strEdtAudioMixName2;
	const String m_strStAudioMixNum1;
	const String m_strStAudioMixNum2;
	const String m_strEdtAudioMixNum1;
	const String m_strEdtAudioMixNum2;

	std::vector<TTPBrdInfo> m_vecTPBrdInfoZero;
	std::vector<TTPBrdInfo> m_vecTPBrdInfoFirst;
	std::vector<TTPBrdInfo> m_vecTPBrdInfoSecond;
	std::vector<TTPBrdInfo> m_vecTPBrdInfoThird;

	TTPBrdInfo m_tTBoardInfoSel;

	BOOL m_bMdlDataChange;
	BOOL m_bApuMdlNameChange;
	BOOL m_bApuMdlNum1Change;
	BOOL m_bApuMdlNum2Change;

	BOOL m_bSelItem;
};

#define BOARDLOGICRPTR    CBoardCfgLogic::GetSingletonPtr()               //����logicָ��

#endif // !defined(AFX_BOARDCFGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
