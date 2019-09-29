// CurtainCfgLogic.h: interface for the CCurtainCfgLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CURTAINCFGLOGIC_H__5D0C4DC0_A18B_461B_B316_B04A49A4173C__INCLUDED_)
#define AFX_CURTAINCFGLOGIC_H__5D0C4DC0_A18B_461B_B316_B04A49A4173C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WndLogicBase.h"

class CCurtainCfgLogic : public CWndLogicBase 
{
public:
	virtual ~CCurtainCfgLogic();

	static CCurtainCfgLogic* GetLogicPtr();

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

    bool OnClickSwitchBtn1( const IArgs& args );
	bool OnClickBtnStop1( const IArgs& args );
	bool OnClickBtnUp1( const IArgs& args );
	bool OnClickBtnDown1( const IArgs& args );
	bool OnClickSwitchBtn2( const IArgs& args );
	bool OnClickBtnStop2( const IArgs& args );
	bool OnClickBtnUp2( const IArgs& args );
	bool OnClickBtnDown2( const IArgs& args );
	bool OnClickSwitchBtn3( const IArgs& args );
	bool OnClickBtnStop3( const IArgs& args );
	bool OnClickBtnUp3( const IArgs& args );
	bool OnClickBtnDown3( const IArgs& args );
	bool OnClickSwitchBtn4( const IArgs& args );
	bool OnClickBtnStop4( const IArgs& args );
	bool OnClickBtnUp4( const IArgs& args );
	bool OnClickBtnDown4( const IArgs& args );
	bool OnClickSwitchBtn5( const IArgs& args );
	bool OnClickBtnStop5( const IArgs& args );
	bool OnClickBtnUp5( const IArgs& args );
	bool OnClickBtnDown5( const IArgs& args );
	bool OnClickSwitchBtn6( const IArgs& args );
	bool OnClickBtnStop6( const IArgs& args );
	bool OnClickBtnUp6( const IArgs& args );
	bool OnClickBtnDown6( const IArgs& args );
	bool OnClickSwitchBtn( const IArgs& args );
	bool OnClickBtnStop( const IArgs& args );
	bool OnClickBtnUp( const IArgs& args );
	bool OnClickBtnDown( const IArgs& args );

protected:

	CCurtainCfgLogic();

	HRESULT OnCurtainStateNty( WPARAM wparam, LPARAM lparam );

    //������ť״̬����
	void BtnStateCtrl();

	//���������������
	void DataClear();

	BOOL m_bCheck;  //�Ƿ���ѡ��

private:

	static CCurtainCfgLogic *m_pLogic;

	static const String m_strSwitchBtn;

	static const String m_strSwitchBtn1;

	static const String m_strSwitchBtn2;

	static const String m_strSwitchBtn3;

	static const String m_strSwitchBtn4;

	static const String m_strSwitchBtn5;

	static const String m_strSwitchBtn6;

	BOOL m_bIsCheck[MAX_CURTAIN_NUM];

    u8 m_nCurNum;    //�ײ㷢������ʵ�ʴ�������

};

#endif // !defined(AFX_CURTAINCFGLOGIC_H__5D0C4DC0_A18B_461B_B316_B04A49A4173C__INCLUDED_)
