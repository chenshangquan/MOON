// CameraLogic.h: interface for the CCameraLogic class.
//
//////////////////////////////////////////////////////////////////////

/*****************************************************************************
ģ����      : CCameraLogic
�ļ���      : CameraLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: �ĵ������ҳ��
����        : ���`�`
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/1/7       1.0         ���`�`			����
******************************************************************************/
#if !defined(AFX_CAMERALOGIC_H__8B953119_C5EB_4FA6_908B_99481064F20A__INCLUDED_)
#define AFX_CAMERALOGIC_H__8B953119_C5EB_4FA6_908B_99481064F20A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WndLogicBase.h"

class CCameraLogic : public CWndLogicBase   
{
public:
	virtual ~CCameraLogic();

	static CCameraLogic* GetLogicPtr();

public: 
	/**	 
	* ����:  ע���logic�����еĻص�����
	* @return  void
	* @remarks	�ڴ�ע��Ļص�������Ҫ�ǿؼ�����Ӧ�¼�����Ϊ��Ա�ص�����,Ҳ��ע�������Ļص�����
	                    ע��ʱ��Ӧע��ص�������Ӧ���ӵ��������򣺡�����::��������
	*/
    virtual bool RegCBFun();

	/**	 
	* ����:  ע��ĳ�ص�����
	* @return  void
	* @remarks	 
	*/
	virtual bool UnRegFunc();

	/**	 
	* ����:  ע��Ҫ�������Ϣ
	* @return  void
	* @remarks	 ע������Ϣ���ܷ��͵����߼�ģ�飬���򣬽��ղ�������Ϣ
	*/
    virtual void RegMsg();

	/**	 
	* ����:  ע��ĳ�ص�����
	* @return  void
	* @remarks	 
	*/
	virtual void UnRegMsg();
	
    /**	 
	* ����:  ��ʼ����������,
	* @return  void
	* @remarks	���ڸù��ܱ��������ؼ����Բ���xml����ؼ��󶨣�
	                    ��Ҫ��RegCBFun()��ע�ᵽ�ص���������ģ�� 
	*/
    virtual bool InitWnd( const IArgs& args );
    
	/**	 
	* ����:  �������״̬������
	* @return    
	*/
    virtual void Clear(); 
	
protected:

    bool OnBtnOpenCameraSwitch( const IArgs& args );

	/**	 
	* ����:  ���Ԥ��λ1����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnClickOrderPosition1( const IArgs& args );

	/**	 
	* ����:  ���Ԥ��λ2����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnClickOrderPosition2( const IArgs& args );

	/**	 
	* ����:  ���Ԥ��λ3����Ӧ����
	* @return   bool
	* @remarks	 
	*/
	bool OnClickOrderPosition3( const IArgs& args );


    bool OnBeginReduce( const IArgs& args );
    bool OnBeginEnlarge( const IArgs& args );

    bool OnBtnReduce( const IArgs& args );

    bool OnBtnEnlarge( const IArgs& args );

    bool OnBtnFocus( const IArgs& args );

    bool OnBtnWhiteBalance( const IArgs& args );

    bool OnBtnSave( const IArgs& args );
	
	
protected:
    CCameraLogic();
	
	HRESULT OnDCamStateNty( WPARAM wparam, LPARAM lparam );
    HRESULT OnDCamPowerInd( WPARAM wparam, LPARAM lparam );

private:
	static CCameraLogic *m_pLogic;

    EmDCamRecallNum     m_emRecallNum;  //��ǰԤ��λ


	static const String m_strBtnOpenCameraSwitch;
    static const String m_strBtnReduce;
    static const String m_strBtnEnlarge;
};

#endif // !defined(AFX_CAMERALOGIC_H__8B953119_C5EB_4FA6_908B_99481064F20A__INCLUDED_)
