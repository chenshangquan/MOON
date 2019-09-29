// funcLstMenu.h: interface for the CFuncLstMenu class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FUNCLSTMENU_H__AF82C9D5_235C_4A2E_AD4E_7432F9EFED03__INCLUDED_)
#define AFX_FUNCLSTMENU_H__AF82C9D5_235C_4A2E_AD4E_7432F9EFED03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "userDefinedLogic.h"
 
class CFuncLstMenu  
{
public:
	
	virtual ~CFuncLstMenu();
 
    static CFuncLstMenu*Instance();
    
public: 
    void Init(  CUserDefinedLogic *pLogic , vector <TConfMenuInfo> *pVctMenuLst);
     
    void SetCusSelItem( TConfMenuInfo tTemp);
    //œ‘ æ
    bool ShowItem( const IArgs &args );

    //“˛≤ÿ
    bool HideItem( const IArgs &args );
    
    // ÷√∂•
    bool SetFuncTop( const IArgs &args );
    
    //cns ÷√µ◊
    bool SetFuncBottom( const IArgs &args );
    
    //cns…œ“∆
    bool SetFuncUp( const IArgs &args );
    
    //œ¬“∆
    bool SetFuncDown(const IArgs &args );
    
    void UpdateMenu();
    
    
   void ShowWindow( BOOL bShow = TRUE  );

protected:
    CFuncLstMenu(); 
    TConfMenuInfo * GetMenuByName( CString strName );
private:
   
    static CFuncLstMenu* m_stcPThis;
    CUserDefinedLogic *m_pUserDefinedLogic;
    TConfMenuInfo m_tSelItem;
    vector <TConfMenuInfo> *m_pVctMenuLst;
     
};


#endif // !defined(AFX_FUNCLSTMENU_H__AF82C9D5_235C_4A2E_AD4E_7432F9EFED03__INCLUDED_)
