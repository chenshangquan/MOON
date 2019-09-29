// SchemeTag.h: interface for the CSchemeTag class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCHEMETAG_H__4E849144_0685_462D_8537_968273470C02__INCLUDED_)
#define AFX_SCHEMETAG_H__4E849144_0685_462D_8537_968273470C02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ITag.h"
namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* ��	����CSchemeTag
* ��    �ܣ�������tag����Ҫ�洢��ͬ״̬��UI�ı仯
* ����˵�����ڲ�ͬ״̬�£�button���԰󶨲�ͬ���¼�
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/07/01	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
class CSchemeTag : public IXmlTag
{
public:
	const static String strName;
public:
	CSchemeTag();
	virtual ~CSchemeTag();
	virtual bool ElementStart( String strElement, const XMLAttributes& xmlAttributes, void* pContext = 0 );
	virtual bool ElementEnd( String strElement,  void* pContext = 0 );
};

} // namespace AutoUIFactory end
#endif // !defined(AFX_SCHEMETAG_H__4E849144_0685_462D_8537_968273470C02__INCLUDED_)
