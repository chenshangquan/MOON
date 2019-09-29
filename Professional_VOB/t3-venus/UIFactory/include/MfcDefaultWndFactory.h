// MfcDefaultWndFactory.h: interface for the MfcDefaultWndFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCDEFAULTWNDFACTORY_H__FCEDB118_DADA_4E2C_9DCF_1DA08B576D1B__INCLUDED_)
#define AFX_MFCDEFAULTWNDFACTORY_H__FCEDB118_DADA_4E2C_9DCF_1DA08B576D1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*
 * @defgroup MfcDefaultWndFactory mfcĬ�ϵ�һЩ�ؼ����� \n
 * ��������ؼ�����������IWindowFactory��Ȼ��CRegDefaultData����ע��
 * @author  Ĳ��ï
 * @version 1.0
 * @date  2011/05/31
 * @{
 */
#include "uifactorydef.h"
#include "windowfactory.h"

namespace AutoUIFactory
{

class CTransparentDlgFactory : public IWindowFactory
{
public:
	virtual Window* Create( IArgs& iAgrs );
};

class CButtonFactory : public IWindowFactory
{
public:
	virtual Window* Create( IArgs& iAgrs );
};

class CListFactory : public IWindowFactory
{
public:
	virtual Window* Create( IArgs& iAgrs );
};

class CEditFactory : public IWindowFactory
{
public:
	virtual Window* Create( IArgs& iAgrs );
};

class CStaticFactory : public IWindowFactory
{
public:
	virtual Window* Create( IArgs& iAgrs );
};


class CIPAddressCtrlFactory : public IWindowFactory
{
public:
	virtual Window* Create( IArgs& iAgrs );
};


class CSliderCtrlFactory: public IWindowFactory
{
public:
    virtual Window* Create( IArgs& iAgrs );
};

} // namespace AutoUIFactory end

/** @} */ 
#endif // !defined(AFX_MFCDEFAULTWNDFACTORY_H__FCEDB118_DADA_4E2C_9DCF_1DA08B576D1B__INCLUDED_)
