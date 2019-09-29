/*****************************************************************************
ģ����      : CTvwStyleCfgLogic
�ļ���      : templateexplogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: logic����ǽ�������ҳ��
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/01/16     1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_TVWSTYLECFGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
#define AFX_TVWSTYLECFGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CTvwStyleCfgLogic :public CWndLogicBase,public ISingleTon<CTvwStyleCfgLogic> 
{
public:  
    CTvwStyleCfgLogic();
	virtual ~CTvwStyleCfgLogic();

public:
		/**	 
	* ����: ������ǽ��������Ƿ�ı�
	* @return   bool
	* @remarks  
	*/
	BOOL CheckPageDataChangeToSave();

		/**	 
	* ����: �õ���ǰ������ĵ���ǽ������
	* @return   void
	* @remarks  
	*/
	THduStyleData GetStyleDataMatrix(){return m_tHduStyleDataMatrix;}; 


			/**	 
	* ����: ���µ���ǽ����б�
	* @return   void
	* @remarks  
	*/
	void UpdateTvwStyleList();

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
	* ����: ��ʼ����������
	* @return   void
	* @remarks  
	*/
	virtual void InitLogicData();

	/**	 
	* ����:  ��ȡ�㡢��ͨ���豸����Ӧ��Ϣ
	* @return   
	* @remarks	 
	*/
	String GetDeviceByLayorAndSlot(const std::pair<s32,s32>& pairLayorSlot);

protected:
		/**	 
	* ����: �������ǽ����б�
	* @return   bool
	* @remarks  
	*/
	bool OnTvwStyleItem( const IArgs & arg );

			/**	 
	* ����: �������õĵ���ǽ���
	* @return   bool
	* @remarks  
	*/
	bool OnBtnTvwStyleSave( const IArgs & arg );

		/**	 
	* ����: ����˵����õ���ǽ���
	* @return   bool
	* @remarks  
	*/
	bool OnBtnTvwStyleMenu( const IArgs & arg );

	/**	 
	* ����: ����˵�ɾ������ǽ���
	* @return   bool
	* @remarks  
	*/
	bool OnBtnTvwStyleMenuDel( const IArgs & arg );
	
protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();

		/**	 
	* ����: ˢ�µ���ǽ�������֪ͨ
	* @return   bool
	* @remarks  
	*/
	HRESULT OnRefreshTvwStyleInfoNotify( WPARAM wparam, LPARAM lparam);
	
		/**	 
	* ����: �������ǽ�����
	* @return   bool
	* @remarks  
	*/
	HRESULT OnTvwStyleSaveRsp( WPARAM wparam, LPARAM lparam);

	/**	 
	* ����: ���µ���ǽ�����
	* @return   bool
	* @remarks  
	*/
	HRESULT OnTvwStyleUpdateRsp( WPARAM wparam, LPARAM lparam);

		/**	 
	* ����: ����ǽ���������Edit�ı�(��̬����������ʾ����)
	* @return   bool
	* @remarks  
	*/
	bool OnTvwStyleRowEditChange( const IArgs & arg );

		/**	 
	* ����: �ֶ��������ǽ���������(��̬����������ʾ����)
	* @return   bool
	* @remarks  
	*/
	bool OnTvwStyleRowEditOnChar( const IArgs & arg );
	
		/**	 
	* ����: ����ǽ���������Edit�ı�(��̬���Ƶ���ǽ����б���ж�����ʾ���)
	* @return   bool
	* @remarks  
	*/
	bool OnTvwStyleColEditChange( const IArgs & arg );


		/**	 
	* ����: �ֶ��������ǽ���������(��̬���Ƶ���ǽ����б���ж�����ʾ���)
	* @return   bool
	* @remarks  
	*/
	bool OnTvwStyleColEditOnChar( const IArgs & arg );

		/**	 
	* ����: ���combo���б�����
	* @return   bool
	* @remarks  
	*/
	bool OnTvwStyleColClick( const IArgs & arg );


		/**	 
	* ����: ���combo���б�����
	* @return   bool
	* @remarks  
	*/
	bool OnTvwStyleRowClick( const IArgs & arg );


		/**	 
	* ����: ˢ�µ���ǽ�������֪ͨ
	* @param    wparam:TTvwStyleInfo m_tSelTvwStyleInfo
	* @return   bool
	* @remarks  
	*/
	HRESULT OnTvwStyleSave( WPARAM wparam, LPARAM lparam);
	
private:
		/**	 
	* ����: �������пؼ���̬����������   Ĭ����ʾ��һ������
	* @return   void
	* @remarks  
	*/
	void SetStyleColData();

		/**	 
	* ����: ��̬���Ƶ���ǽ����б���ж�����ʾ���
	* @return   void
	* @remarks  
	*/
	void SetDynamicStyleList();


		/**	 
	* ����: �������ǽ���Ԥ��
	* @return   void
	* @remarks  
	*/
	BOOL TvwStyleSave( const TTvwStyleInfo& m_tSelTvwStyleInfo );

		/**	 
	* ����: ���µ���ǽ��������Ϣ
	* @return   void
	* @remarks  
	*/
	void RefreshTvwStyleInfo();

		/**	 
	* ����: ����ǽ�����������Ƿ�仯���
	* @return   void
	* @remarks  
	*/
	BOOL CompareStyleDataMatrixChange();

	/**	 
	* ����: �����ĳ��Ԥ�����ã����ݵ�ǰ�㡢�ۡ�ͨ���ţ��õ�Ӧ��ʾ��ͨ����  ��ͨ����0   0��0������ʾ1    ��ͨ����1   0��1������ʾ4   
	* @return   String �豸��  u8 ͨ����
	* @remarks
	*/
//	u8 GetShowChanNo( u8 byLayer, u8 bySlot, u8 byChanNo );

private:
	const String m_strComboboxTvwStyleCol;
	const String m_strComboboxTvwStyleRow;
	const String m_strLstTvwStyle;
	const String m_strBtnTvwStyleSave;

	TTvwStyleInfo m_tSelTvwStyleInfo;		//��ǰѡ�ж�Ӧ�ĵ���ǽͨ�����ݣ����������б�ʹ�� 
	THduStyleData m_tHduStyleDataMatrix;    //���շ������������ĵ���ǽ������ݣ�������������л�������� ������� ��������ʹ�� 
											//����THduStyleUnitֻ������ˢ�º����ñ���ʱ�����������������

	BOOL m_bStyleDataChange;
	CTransparentViewList* m_pListWnd;
};

#define TVWSTYLELOGICRPTR    CTvwStyleCfgLogic::GetSingletonPtr()               //����ǽ���logicָ��

#endif // !defined(AFX_TVWSTYLECFGLOGIC_H__AE177678_C26D_4119_9634_55EB6A4DB4C3__INCLUDED_)
