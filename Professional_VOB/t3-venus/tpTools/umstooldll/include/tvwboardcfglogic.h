/*****************************************************************************
ģ����      : CTvwBoardCfgLogic
�ļ���      : TvwBoardcfglogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: logic����ǽ��������ҳ��
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/01/04     1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_TVWBoardCFGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
#define AFX_TVWBoardCFGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

#include "touchlistdataproperty.h"

class CTvwBoardCfgLogic :public CWndLogicBase, public ISingleTon<CTvwBoardCfgLogic> 
{
public:  
    CTvwBoardCfgLogic();
	virtual ~CTvwBoardCfgLogic();

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

public:
		/**	 
	* ����: ����л�ҳ������  �б仯����
	* @return   BOOL:TRUE�����л�    FALSE��ֹ�л�
	* @remarks  
	*/
	BOOL CheckPageDataChangeToSave();

protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();

	HRESULT OnRefreshTvwBoardInfoNotify( WPARAM wparam, LPARAM lparam);
	HRESULT OnOptTvwBoardNotify( WPARAM wparam, LPARAM lparam);
	HRESULT OnOptTvwBoardRsp( WPARAM wparam, LPARAM lparam);
	HRESULT OnDelTvwBoardNotify( WPARAM wparam, LPARAM lparam);
	HRESULT OnOptTvwBoardModeNotify( WPARAM wparam, LPARAM lparam);
	HRESULT OnOptTvwBoardModeRsp( WPARAM wparam, LPARAM lparam);
	HRESULT OnDelTvwBoardModeNotify( WPARAM wparam, LPARAM lparam);
	HRESULT OnTvwBoardUpgradeRsp( WPARAM wparam, LPARAM lparam);
	HRESULT OnTvwBoardBeginUpgrade( WPARAM wparam, LPARAM lparam);

protected:
		/**	 
	* ����: ���������л��˵��б�
	* @return   bool
	* @remarks  
	*/
	bool OnMenuLstItem( const IArgs & arg );
	
		/**	 
	* ����: ����㵥���б�
	* @return   bool
	* @remarks  
	*/
	bool OnTvwBoardLstFloorItem( const IArgs & arg );

	/**	 
	* ����: �����л������б�ҳ��ؼ�״̬
	* @return   bool
	* @remarks  
	*/
	void ResetTvwBoardPageControl();

	/**	 
	* ����: ����ɾ��
	* @return   bool
	* @remarks  
	*/
	bool OnBtnTvwBoardDel( const IArgs & arg );

	/**	 
	* ����: �����޸�
	* @return   bool
	* @remarks  
	*/
	bool OnBtnTvwBoardModify( const IArgs & arg );

	/**	 
	* ����: �������
	* @return   bool
	* @remarks  
	*/
	bool OnBtnTvwBoardAdd( const IArgs & arg );

	/**	 
	* ����: ��������
	* @return   bool
	* @remarks  
	*/
	bool OnBtnTvwBoardReboot( const IArgs & arg );

	/**	 
	* ����: ��������
	* @return   bool
	* @remarks  
	*/
	bool OnBtnTvwBoardUpgrade( const IArgs & arg );

	/**	 
	* ����: ����ģʽɾ��
	* @return   bool
	* @remarks  
	*/
	bool OnBtnTvwBoardModeDel( const IArgs & arg );

	/**	 
	* ����: ����ģʽ�޸�
	* @return   bool
	* @remarks  
	*/
	bool OnBtnTvwBoardModeSave( const IArgs & arg );

		/**	 
	* ����: ����ǽ����ģʽ����ӿڸı�   ��Ϊֻ������ӿ�1�ı�   ��Ӧ��ʽ�ӿ����ݲŸı�   ���Ե�����ȡ
	* @return   bool
	* @remarks  
	*/
	bool OnTvwBoardMdlEditInputPortOneChange( const IArgs & arg );

		/**	 
	* ����: ����ǽ����ģʽ����ӿڸı�   ��Ϊֻ������ӿ�2�ı�   ��Ӧ��ʽ�ӿ����ݲŸı�   ���Ե�����ȡ
	* @return   bool
	* @remarks  
	*/
	bool OnTvwBoardMdlEditInputPortTwoChange( const IArgs & arg );

		/**	 
	* ����: ����ǽ����ģʽ��ʽ1�ı�
	* @return   bool
	* @remarks  
	*/
	bool OnTvwBoardMdlEditInputNTFSOneChange( const IArgs & arg );

		/**	 
	* ����: ����ǽ����ģʽ��ʽ2�ı�
	* @return   bool
	* @remarks  
	*/
	bool OnTvwBoardMdlEditInputNTFSTwoChange( const IArgs & arg );

		/**	 
	* ����: �������ǽ��������ӿ�1
	* @return   bool
	* @remarks  
	*/
	bool OnTvwBoardMdlEditInputPortOneClick( const IArgs & arg );

		/**	 
	* ����: �������ǽ��������ӿ�2
	* @return   bool
	* @remarks  
	*/
	bool OnTvwBoardMdlEditInputPortTwoClick( const IArgs & arg );

		/**	 
	* ����: �������ǽ�����б�հ״�
	* @return   bool
	* @remarks  
	*/
	bool OnClickTvwBoardLstBlack( const IArgs & arg );

private:
		/**	 
	* ����: ��ʼ��������л��˵��б�
	* @return   bool
	* @remarks  
	*/
	void InitFunMenu();

		/**	 
	* ����: ��ʼ��ģʽ�б���������   �հ���������   �ǿհ���������Ӧ����
	* @return   bool
	* @remarks  
	*/
	void InitMdlComboList();

		/**	 
	* ����: ��ʼ�������б�����
	* @return   bool
	* @remarks  
	*/
	void InitTvwBoardListData();

	/**	 
	* ����: ˢ�µڼ����б���ʾ
	* @return   ��
	* @remarks  
	*/
	void UpdateTvwBoardLayarList(s32 nLayar);
	void UpdateLayarList( s32 nLayar, BOOL bIsReset = FALSE );

	/**	 
	* ����: ���õ���ǽ����ģʽ�ؼ����ݵ�������
	* @return   ��
	* @remarks  
	*/
	bool SetTvwModeControlInfoToSevr();

	/**	 
	* ����: ��յ���ǽģʽҳ��������ʾ
	* @return   ��
	* @remarks  
	*/
	void CleanTvwMdlControlShow();

	/**	 
	* ����: ���õ���ǽģʽ�ؼ�����
	* @return   ��
	* @remarks  
	*/
	BOOL SetTvwModeDataToControl(const THduCfg& tHduCfgSel);

		/**	 
	* ����: ���ģʽ�����Ƿ����    �����򱣴�ʧ��
	* @return   BOOL:TRUE����    TRUE������
	* @remarks  
	*/
	BOOL IsExistMdlName();

		/**	 
	* ����: ������ǽ����ģʽ���ݵĺϷ���
	* @return   BOOL
	* @remarks  
	*/
	BOOL CheckPageTvwBoardMdlData();

		/**	 
	* ����: ���Ƶ������   ���ֻ����4��������
	* @return   BOOL
	* @remarks  
	*/
	BOOL ControlNotNullBoradLayorCount();

	/**	 
	* ����: ����ǽ����ģʽ�����Ƿ�ı�
	* @return   bool
	* @remarks  
	*/
	BOOL GetMdlDataChange(){ return m_bMdlDataChange;};

	/**	 
	* ����: �ȽϽ������ݱ仯
	* @return   bool
	* @remarks  
	*/
	void CompareDataChange();

	/**	 
	* ����: ���ü���combox�ؼ���Ĭ����ʾֵ
	* @return   ��
	* @remarks  
	*/
	void InitHduOutPortValue();	
	void InitHduOutModeValue();	
	void InitHduZoomRateValue();	
	void InitHduShowModeValue();	

	String EmHduOutPortToString(EmHduOutPort emValue);		//�ӿ�����ת��
	EmHduOutPort StringToEmHduOutPort(String strValue);
	String EmHduOutModeToString(EmHduOutMode emValue);		//�����ʽת��
	EmHduOutMode StringToEmHduOutMode(String strValue);
	String EmHduZoomRateToString(EmHduZoomRate emValue);	//���ű���ת��
	EmHduZoomRate StringToEmHduZoomRate(String strValue);
	String EmHduShowModeToString(EmHduShowMode emValue);	//�������ת��
	EmHduShowMode StringToEmHduShowMode(String strValue);

	void SetMdlDataChange(BOOL bMdlDataChange){ m_bMdlDataChange = bMdlDataChange;};

	/**	 
	* ����: ���ÿؼ�1ģʽ��
	* @return   ��
	* @remarks  
	*/
	void SetModePortOneDataToCtrl( BOOL bIsEditDataChange = TRUE );	

	/**	 
	* ����: ���ÿؼ�2ģʽ��
	* @return   ��
	* @remarks  
	*/
	void SetModePortTwoDataToCtrl( BOOL bIsEditDataChange = TRUE );

	/**	 
	* ����: ���õ�ǰѡ�е�ģʽ��Ϣ
	* @return   ��
	* @remarks  
	*/
	void SetSelMdlDataToCtrl();

private:
	const String m_strLstTvwBoardFloor;
	const String m_strLstTvwFloorMenu;
	const String m_strBtnTvwBoardDel;
	const String m_strBtnTvwBoardModify;
	const String m_strBtnTvwBoardAdd;
	const String m_strBtnTvwBoardReboot;
	const String m_strBtnTvwBoardUpgrade;
	const String m_strBtnTvwBoardModeDel;
	const String m_strBtnTvwBoardModeSave;

	const String m_strEdtTvwBoardModeName;
	const String m_strComboxTvwBoardInputPortOne;
	const String m_strComboxTvwBoardInputPortTwo;
	const String m_strComboxTvwBoardInputPortOneNTSC;
	const String m_strComboxTvwBoardInputPortTwoNTSC;
	const String m_strComboxTvwBoardInputPortOnePer;
	const String m_strComboxTvwBoardInputPortTwoPer;
	const String m_strComboxTvwBoardInputPortOnePerPloy;
	const String m_strComboxTvwBoardInputPortTwoPerPloy;


	std::vector<THduCfg> m_vecTPTvwBrdInfo;
	THduCfg m_tHduCfgSel;

	std::vector<CString> m_vecHduOutPort;
	std::vector<CString> m_vecHduOutModeCommon;     //�ӿ�����ΪDVI��Ĭ�ϣ�/HDMI/YPbPrʱ�������ʽ֧��
	std::vector<CString> m_vecHduOutModeVGA;        //�ӿ�����ΪVGAʱ�������ʽ֧��
	std::vector<CString> m_vecHduZoomRate;
	std::vector<CString> m_vecHduShowMode;

	BOOL m_bMdlDataChange;

	s32 m_nCurFloorNo;
};

#define TVWBOARDLOGICRPTR    CTvwBoardCfgLogic::GetSingletonPtr()               //����ǽ����logicָ��

#endif // !defined(AFX_TVWBoardCFGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
