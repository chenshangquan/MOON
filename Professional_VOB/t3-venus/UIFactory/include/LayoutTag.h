// LayoutTag.h: interface for the LayoutTag class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LAYOUTTAG_H__F9942780_C46F_4E15_84D7_98A41692162E__INCLUDED_)
#define AFX_LAYOUTTAG_H__F9942780_C46F_4E15_84D7_98A41692162E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ITag.h"
namespace AutoUIFactory
{

/*---------------------------------------------------------------------
* ��	����CLayoutTag
* ��    �ܣ����ڲ��ֵı�ǩ
* ����˵���������ʾ�˵�ǰ�����Ƿ���Ҫ���ж�̬����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/06/10	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
class CLayoutTag : public IXmlTag
{
public:
	CLayoutTag();
	virtual ~CLayoutTag();
	virtual bool ElementStart( String strElement, const XMLAttributes& xmlAttributes, void* pContext = 0 );
	virtual bool ElementEnd( String strElement,  void* pContext = 0 );
};

}

#endif // !defined(AFX_LAYOUTTAG_H__F9942780_C46F_4E15_84D7_98A41692162E__INCLUDED_)
