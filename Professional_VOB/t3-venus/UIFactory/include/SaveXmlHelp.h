// SaveXmlHelp.h: interface for the CSaveXmlHelp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SAVEXMLHELP_H__9D9CD1F7_4740_46CB_9C75_E962E2116EDD__INCLUDED_)
#define AFX_SAVEXMLHELP_H__9D9CD1F7_4740_46CB_9C75_E962E2116EDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "templateClass.h"
#include "uifactorydef.h"
namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* ��	����CSaveXmlHelp
* ��    �ܣ����ڱ���UI����Ϣ���ļ�
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/06/02	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
class CSaveXmlHelp  
{
public:
	CSaveXmlHelp();
	virtual ~CSaveXmlHelp();
/**  ����һ��UI����Ϣ��һ��xml�ļ�
 *  @param[in] strWindow ������
 *  @param[in] strSavePropertyName Ҫ�����������
 *  @param[in] bForceSave ���Ҫ��������Բ��ڵ�ǰ�����У��Ƿ�ǿ�Ʊ���
 *  @return �Ƿ�ɹ�
 */
	static bool SaveXml( String strWindow,string strWndName = "" , string strSavePerpertyName = "" ,BOOL bForceSave = FALSE );
 

};

} // namespace AutoUIFactory end
#endif // !defined(AFX_SAVEXMLHELP_H__9D9CD1F7_4740_46CB_9C75_E962E2116EDD__INCLUDED_)
