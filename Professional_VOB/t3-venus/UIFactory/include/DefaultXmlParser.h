// DefaultXmlParser.h: interface for the DefaultXmlParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEFAULTXMLPARSER_H__9DE688AD_807B_4988_BC2D_1D4596501AE2__INCLUDED_)
#define AFX_DEFAULTXMLPARSER_H__9DE688AD_807B_4988_BC2D_1D4596501AE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "IXmlParser.h"

namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* ��	����DefaultXmlParser
* ��    �ܣ�Ĭ��xml�����࣬����tinyxml
* ����˵���������Ҫ�������ģ��뽫xml�ļ�����ı�����gb2312
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/06/02	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
class DefaultXmlParser : public IXmlParser
{
public:
	DefaultXmlParser(void){}
	~DefaultXmlParser(void){}
	
/**  ����xml�ļ�
 *  @param[in] piXmlHandle ������
 *  @param[in] strFileName �ļ�·��
 *  @return �Ƿ�ɹ�
 */
	bool ParserXml( IXmlHanlde* piXmlHandle, String strFileName );
	
protected:
	// Implementation of abstract interface.
	bool initialiseImpl(void);
	void cleanupImpl(void);
};

}
#endif // !defined(AFX_DEFAULTXMLPARSER_H__9DE688AD_807B_4988_BC2D_1D4596501AE2__INCLUDED_)
