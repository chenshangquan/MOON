/*****************************************************************************
ģ����      : CTvwStyleOptDlgLogic
�ļ���      : tvwstyleoptdlglogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: logic����ǽ�������ҳ��
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/01/21     1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_TVWSTYLEOPTDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
#define AFX_TVWSTYLEOPTDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CTvwStyleOptDlgLogic :public CWndLogicBase, public ISingleTon<CTvwStyleOptDlgLogic>  
{
public:  
    CTvwStyleOptDlgLogic();
	virtual ~CTvwStyleOptDlgLogic();

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

	bool OnBtnTvwStyleOptCancel( const IArgs & arg );

protected:
   /**	 
	* ����:  ���͵�ǰѡ�е����ݵ��������ҳ��
	* @return   
	* @remarks	 
	*/
	HRESULT OnTvwStyleSelData( WPARAM wparam, LPARAM lparam );



protected:
	virtual void RegMsg(); 
	virtual void UnRegMsg();

	bool OnBtnTvwStyleOptOk( const IArgs & arg );
	
		/**	 
	* ����: ͨ�����༭�����ı�
	* @return   bool
	* @remarks  
	*/
	bool OnChanNameEditChange( const IArgs & arg );

private:
	   /**	 
	* ����:  ��ȡ�豸����Ӧ�㡢����Ϣ
	* @return   
	* @remarks	 
	*/
	std::pair<s32,s32> GetLayorAndSlotByDevice(const String& strDeviceName);

		/**	 
	* ����: �������ӵ�ͨ����Ϣ���Ƿ������ͬ��   ���������ʧ��    
	* @return   BOOL
	* @remarks  
	*/
	BOOL CheckExistChanInfo(const THduStyleUnit& tStyleUnits);

	/**	 
	* ����: �����豸�����б�
	* @return
	* @remarks
	*/
	bool RevertComboboxDeviceName();

		/**	 
	* ����: ת��ͨ����   ת������   0��0�� Ϊ1 2�� 0��1��Ϊ3 4   �Դ�����     ��ʵ�ʷ���   ֻ��0 1
	* @return   bool
	* @remarks  RevertBrdPosToChanNo Ϊ1 2������ʾ      RevertChanNoToBrdPos 0��0 1
	*/
	bool RevertBrdPosToChanNo( u8 byLayer, u8 bySlot );
	bool RevertChanNoToBrdPos();

		/**	 
	* ����: �����ĳ��Ԥ������   ���ݵ�ǰͨ����   ������Ӧ����ʾ����  ��ͨ����0   0��0������ʾ1    ��ͨ����1   0��1������ʾ4   
	* @return   void
	* @remarks
	*/
	void ShowChanNo(u8 byChanNo);

private:
	const String  m_strComboboxTvwStyleOptDeviceName;
	const String  m_strComboboxTvwStyleOptChanNo;
	const String  m_strBtnTvwStyleOptOk;

	TTvwStyleInfo m_tTvwStyleInfo;

};

#define TVWSTYLEOPTLOGICRPTR    CTvwStyleOptDlgLogic::GetSingletonPtr()               //����ǽ�������logicָ��

#endif // !defined(AFX_TVWSTYLEOPTDLGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
