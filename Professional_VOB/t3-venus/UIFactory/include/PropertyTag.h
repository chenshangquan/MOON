// PropertyTag.h: interface for the CPropertyTag class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROPERTYTAG_H__2968D01A_503A_42BE_ABE5_8E586D11C40A__INCLUDED_)
#define AFX_PROPERTYTAG_H__2968D01A_503A_42BE_ABE5_8E586D11C40A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ITag.h"
namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* ��	����CPropertyTag
* ��    �ܣ�ר�Ŵ������Ա�ǩ
* ����˵������ǩ���ֱ���һ��
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/06/02	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
class CPropertyTag : public IXmlTag
{
public:
	CPropertyTag();
	virtual ~CPropertyTag();
	virtual bool ElementStart( String strElement, const XMLAttributes& xmlAttributes, void* pContext = 0 );
	virtual bool ElementEnd( String strElement,  void* pContext = 0 );
};

} // namespace AutoUIFactory end

#endif // !defined(AFX_PROPERTYTAG_H__2968D01A_503A_42BE_ABE5_8E586D11C40A__INCLUDED_)
