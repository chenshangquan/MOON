// ethnetcfglogic.h: interface for the CEthnetCfgLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ETHNETCFGLOGIC_H__5721BFA8_DF16_4A3D_8316_6C4B45CC537F__INCLUDED_)
#define AFX_ETHNETCFGLOGIC_H__5721BFA8_DF16_4A3D_8316_6C4B45CC537F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CEthnetCfgLogic : public CWndLogicBase
{
public:
	CEthnetCfgLogic();
	virtual ~CEthnetCfgLogic();
	
	static CEthnetCfgLogic* GetLogicPtr();
	
public:
	virtual bool RegCBFun();
	virtual bool UnRegFunc();
	virtual void RegMsg();

    /**	 
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

protected:
	bool InitWnd( const IArgs & args );
	/**
	* ����:  �������
	* @return  bool
	* @remarks  
	*/
	bool OnSave( const IArgs& args );
	
	BOOL CheckAllIp();	//�������Ip�仯
	
	/**	 
	* ����:  ���ȡ��
	* @return  bool
	* @remarks  
	*/
	bool OnCancel( const IArgs& args );
	/**	 
	* ����:  ����༭
	* @return  bool
	* @remarks  
	*/
	bool OnEdit( const IArgs& args );

	bool OnSysCfg( const IArgs& args );

	bool SaveEthnetCfg( const IArgs& args );

	bool OnCloseDlg( const IArgs& args );

	LRESULT UpdateEthnetInfo( WPARAM wParam, LPARAM lParam );

	LRESULT UpdateNatInfo( WPARAM wParam, LPARAM lParam );

	bool BtnSwitchNATClick( const IArgs& args );
private:
	static CEthnetCfgLogic *m_pCfgLogic;

	static const String m_strEdtIp;
    static const String m_strEdtSubMask;
    static const String m_strEdtGateWay;

	static const String m_strBtnNATSwitch;	 
	static const String m_strEdtNatIP;

};

#endif // !defined(AFX_ETHNETCFGLOGIC_H__5721BFA8_DF16_4A3D_8316_6C4B45CC537F__INCLUDED_)
