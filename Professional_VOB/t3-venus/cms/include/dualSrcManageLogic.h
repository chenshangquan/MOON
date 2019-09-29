// dualSrcManageLogic.h: interface for the CDualSrcManageLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DUALSRCMANAGELOGIC_H__22C6B2D7_E5B2_46BF_85F6_C9F98D04792B__INCLUDED_)
#define AFX_DUALSRCMANAGELOGIC_H__22C6B2D7_E5B2_46BF_85F6_C9F98D04792B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "wndLogicBase.h"
class CDualSrcManageLogic : public CWndLogicBase   
{
public:
	CDualSrcManageLogic();
	virtual ~CDualSrcManageLogic(); 
 
	static CDualSrcManageLogic* GetLogicPtr();

public:
	virtual bool RegCBFun();
	virtual bool UnRegFunc();
	virtual void RegMsg();
	virtual void UnRegMsg();
	
    /**	 
	* ����:  �������״̬������
	* @return    
	*/
    virtual void Clear();

	bool InitWnd( const IArgs & args );

	bool BtnToSysCfg( const IArgs & args );

	bool BtnToDualConfig( const IArgs & args );

    bool OnClickDualSrcItem( const IArgs & args );

    bool OnEdit( const IArgs & args );

    bool OnSave( const IArgs & args );

    bool OnCancel( const IArgs & args );
 
protected:

    LRESULT OnVgaInfoNotify( WPARAM wParam, LPARAM lParam );
 
private:	
    static CDualSrcManageLogic *m_pLogic;

    TDualSrcInfo   m_tDualSrcInfo;
    TVgaInfo       m_tVgaInfo;         //��ǰ��ʾԴ��Ϣ
    BOOL           m_bDefault;         //��ǰ��ʾԴ�Ƿ�Ĭ��
    int            m_nCurSelInfoIndex;    //��ǰ��ʾԴ��m_tDualSrcInfo�е���ţ��Ա����ʱͬ�����µ�ǰ�༭����Ϣ 2012.10.8 by yujinjin
    static const String m_strBtnDefDualSwitch;
    static const String m_strEdtDualName;
};

#endif // !defined(AFX_DUALSRCMANAGELOGIC_H__22C6B2D7_E5B2_46BF_85F6_C9F98D04792B__INCLUDED_)
