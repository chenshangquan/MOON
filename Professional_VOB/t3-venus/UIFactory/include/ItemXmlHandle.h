// ItemXmlHandle.h: interface for the CItemXmlHandle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEMXMLHANDLE_H__0D89A944_118D_4FEA_94ED_3204EB689851__INCLUDED_)
#define AFX_ITEMXMLHANDLE_H__0D89A944_118D_4FEA_94ED_3204EB689851__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IXmlHanlde.h"

namespace AutoUIFactory
{

class CItemXmlHandle : public IXmlHanlde
{
public:
	static const String strName;
	static const String strType;
public:
	CItemXmlHandle();
	virtual ~CItemXmlHandle();
/**  ��������һ����ǩ��ʱ������
 *  @param[in] strElement ��ǩ��
 *  @param[in] xmlAttributes ����ȡ��������
 *  @return �Ƿ�ɹ�
 */
	bool ElementStart( String strElement, const XMLAttributes& xmlAttributes );

/**  ������һ����ǩ��ʱ������
 *  @param[in] strElement ��ǩ��
 *  @node һ����˵��������ǰѵ�ǰ��״̬�л�������Ǵ��ڶ�ȡ������Ҫ���õ�ǰ����Ϊǰһ��
 *  @return �Ƿ�ɹ�
 */
	bool ElementEnd( String strElement );
};

}

#endif // !defined(AFX_ITEMXMLHANDLE_H__0D89A944_118D_4FEA_94ED_3204EB689851__INCLUDED_)
