// IXmlHanlde.h: interface for the IXmlHanlde class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IXMLHANLDE_H__2C7B1485_9344_4DCD_8F6C_C166364C71D4__INCLUDED_)
#define AFX_IXMLHANLDE_H__2C7B1485_9344_4DCD_8F6C_C166364C71D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace AutoUIFactory
{
#include "uifactorydef.h"
#include "XmlAttrib.h"

/*---------------------------------------------------------------------
* ��	����IXmlHanlde
* ��    �ܣ�xml�ļ���������
* ����˵����xmlÿ���ڵ�Ľ���ֻ������ģʽ��һ�־��ǽ�ȥ��һ�־��ǳ���
*			��ȥ��ʱ���������ԣ�������ʱ���ͷ���Դ�����õ�ǰ״̬
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/06/02	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
Interface IXmlHanlde  
{
public:
	IXmlHanlde();
	virtual ~IXmlHanlde();
/**  ��������һ����ǩ��ʱ������
 *  @param[in] strElement ��ǩ��
 *  @param[in] xmlAttributes ����ȡ��������
 *  @return �Ƿ�ɹ�
 */
	virtual bool ElementStart( String strElement, const XMLAttributes& xmlAttributes ) = 0;

/**  ������һ����ǩ��ʱ������
 *  @param[in] strElement ��ǩ��
 *  @node һ����˵��������ǰѵ�ǰ��״̬�л�������Ǵ��ڶ�ȡ������Ҫ���õ�ǰ����Ϊǰһ��
 *  @return �Ƿ�ɹ�
 */
	virtual bool ElementEnd( String strElement ) = 0;
};

} // namespace AutoUIFactory end

#endif // !defined(AFX_IXMLHANLDE_H__2C7B1485_9344_4DCD_8F6C_C166364C71D4__INCLUDED_)
