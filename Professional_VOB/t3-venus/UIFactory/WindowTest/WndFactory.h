// WndFactory.h: interface for the CWndFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WNDFACTORY_H__71040829_7277_43CE_8552_750A8600013B__INCLUDED_)
#define AFX_WNDFACTORY_H__71040829_7277_43CE_8552_750A8600013B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#endif // !defined(AFX_WNDFACTORY_H__71040829_7277_43CE_8552_750A8600013B__INCLUDED_)
#include "MfcDefaultWndPropertySet.h"
class CWindowFactory : public IWindowFactory
{
public:
	CWindowFactory(){}
	virtual ~CWindowFactory(){}
	virtual Window* Create( IArgs& iAgrs );
};

DECLARE_PROPERTYSET_BEGIN( CWindow, CWndPropertySet )
// 如果有新增属性请到这里添加
DECLARE_PROPERTYSET_END
