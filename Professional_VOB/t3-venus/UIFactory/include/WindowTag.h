// WindowTag.h: interface for the CWindowTag class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDOWTAG_H__8D2CCF46_1DD6_45D4_8914_F75C8423D7BA__INCLUDED_)
#define AFX_WINDOWTAG_H__8D2CCF46_1DD6_45D4_8914_F75C8423D7BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ITag.h"
/*---------------------------------------------------------------------
* ��	����CWindowTag
* ��    �ܣ�ר�Ž���Window��ǩ
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/05/12	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
namespace AutoUIFactory
{

class CWindowTag : public IXmlTag
{
public:
	const static String strName;
	const static String strValue;
	const static String strType;
	const static String strArgs;
	const static String strStyle;
	const static String strExStyle;
	const static String strModal; //�Ƿ�Ϊģ̬���� 2012.12.3 yjj
	enum emWndCreateArg
	{
		CreateByFactory = 0,
		CreateByXml,
	};
public:
	CWindowTag();
	virtual ~CWindowTag();
	virtual bool ElementStart( String strElement, const XMLAttributes& xmlAttributes, void* pContext = 0 );
	virtual bool ElementEnd( String strElement,  void* pContext = 0 );
};

} // namespace AutoUIFactory end
#endif // !defined(AFX_WINDOWTAG_H__8D2CCF46_1DD6_45D4_8914_F75C8423D7BA__INCLUDED_)
