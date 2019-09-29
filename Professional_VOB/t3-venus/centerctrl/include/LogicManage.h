// LogicManage.h: interface for the CLogicManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGICMANAGE_H__7B8208EC_67CD_4E16_AE8F_C630FB8BCE23__INCLUDED_)
#define AFX_LOGICMANAGE_H__7B8208EC_67CD_4E16_AE8F_C630FB8BCE23__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "WndLogicBase.h"

class CLogicManage : public ISingleTon< CLogicManage >
{
public:
    CLogicManage();
	virtual ~CLogicManage();

    /**	 
    * 功能:  创建所有logic 
    * @return   
    * @remarks	   
    */ 
    void CreateLogic();

    /**	 
    * 功能:  销毁所有logic 
    * @return   
    * @remarks	   
    */ 
    void DestroyLogic();

protected:
    HRESULT OnDisConnect( WPARAM wparam, LPARAM lparam );
    
};

#define LogicManagePtr  CLogicManage::GetSingletonPtr()

#endif // !defined(AFX_LOGICMANAGE_H__7B8208EC_67CD_4E16_AE8F_C630FB8BCE23__INCLUDED_)
