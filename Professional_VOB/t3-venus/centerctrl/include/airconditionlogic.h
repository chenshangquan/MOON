// airconditionlogic.h: interface for the CAirConditionLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AIRCONDITIONLOGIC_H__B10C58CA_286B_42A7_9392_927D1B3CC39B__INCLUDED_)
#define AFX_AIRCONDITIONLOGIC_H__B10C58CA_286B_42A7_9392_927D1B3CC39B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WndLogicBase.h"

class CAirConditionLogic : public CWndLogicBase 
{
public:	
    virtual ~CAirConditionLogic();
    
    static CAirConditionLogic* GetLogicPtr();
    
public:  
    virtual bool RegCBFun();
    virtual void RegMsg(); 
    
    virtual bool InitWnd( const IArgs& args );
    
    virtual void Clear();  

    bool OnBtnMinusTemp( const IArgs& args );

    bool OnBtnAddTemp( const IArgs& args );

	bool OnBtnAirScreen1( const IArgs& args );

    bool OnBtnAirScreen2( const IArgs& args );

	bool OnBtnAirScreen3( const IArgs& args );

	bool OnBtnSwitch1( const IArgs& args );

	bool OnBtnSwitch2( const IArgs& args );

	bool OnBtnSwitch3( const IArgs& args );

    bool OnBtnCold( const IArgs& args );

    bool OnBtnWarm( const IArgs& args );

	bool OnBtnWind( const IArgs& args );

    bool OnBtnWet( const IArgs& args );

    bool OnBtnAuto( const IArgs& args );

    bool OnBtnMinusVolume( const IArgs& args );

    bool OnBtnAddVolume( const IArgs& args );

	bool OnBtnApplyToAll( const IArgs& args );

	//void TransIntEm( EmCentreACAirVol emAirVol, u8 byAirVol );
    
protected:
    CAirConditionLogic();

    void UpdateTempImg( u16 wTemp, String strTempDlg );
    void UpdateAirVol( u8 byVol, String strTempDlg );
	void UpdateModePic( EmCentreACMode emACMode, String strTempDlg );
	bool OnDragEnd( const IArgs& args );
	//	bool OnDragItemOut( const IArgs& args );
	
	//  HRESULT OnSchStateNty( WPARAM wparam, LPARAM lparam );
	//  HRESULT OnSchTempNty( WPARAM wparam, LPARAM lparam );
    HRESULT OnACStateNty( WPARAM wparam, LPARAM lparam );
    HRESULT OnAirPowerInd( WPARAM wparam, LPARAM lparam );
	HRESULT OnSelectAirInd( WPARAM wparam, LPARAM lparam );
	HRESULT OnApplyToAllInd( WPARAM wparam, LPARAM lparam );
private:
	static CAirConditionLogic *m_pLogic;
	
	//  static const String m_strDlgLocalTemp;
    static const String m_strDlgAirTemp1;
    static const String m_strDlgAirTemp2;
	static const String m_strDlgAirTemp3;
	static const String m_strBtnAirSwitch1;
	static const String m_strBtnAirSwitch2;
	static const String m_strBtnAirSwitch3;
    static const String m_strDlgAirVolume;
    static const String m_strStcAirCtrlTitle;

    u16    m_wLocalTemp;    //当前温度
    u16    m_wAirTemp;      //空调温度
	u16    m_wAirTemp1;
	u16    m_wAirTemp2;     
	u16    m_wAirTemp3;		//选中的空调温度
	u16    m_wCurTemp;      //当地温度
    u8     m_byAirVol;      //新风风量
	u8     m_byAirVol1;
	u8     m_byAirVol2;
	u8     m_byAirVol3;     //选中的新风风量
	u8     m_byIndex;       //单个或者两个空调时首个空调的序列号
	u8     m_byIndex1;      //双空调时，末位空调的序列号
	u8     m_byIndex2;      //被选中的空调序号回复到界面，界面记录的Index
	u8     m_byNum;
}; 

#endif // !defined(AFX_AIRCONDITIONLOGIC_H__B10C58CA_286B_42A7_9392_927D1B3CC39B__INCLUDED_)

