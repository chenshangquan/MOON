// EventTag.h: interface for the CEventTag class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTTAG_H__95194AC1_C546_4698_B1F2_9FB61F33E919__INCLUDED_)
#define AFX_EVENTTAG_H__95194AC1_C546_4698_B1F2_9FB61F33E919__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ITag.h"

namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* ��	����CEventTag
* ��    �ܣ��¼���ǩ�����ڷ���ʱ���ǩ�������Ͼ���ע���¼�
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/06/02	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
class CEventTag : public IXmlTag
{
public:
	const static String strEventID;
	const static String strFuncType;
	const static String strFunc;
public:
	CEventTag();
	virtual ~CEventTag();
	virtual bool ElementStart( String strElement, const XMLAttributes& xmlAttributes, void* pContext = 0 );
	virtual bool ElementEnd( String strElement,  void* pContext = 0 );
};

} // namespace AutoUIFactory end
#endif // !defined(AFX_EVENTTAG_H__95194AC1_C546_4698_B1F2_9FB61F33E919__INCLUDED_)
