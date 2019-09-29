// IXmlParser.h: interface for the IXmlParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IXMLPARSER_H__6ED0A159_76CD_41B6_9049_EEAA15B70723__INCLUDED_)
#define AFX_IXMLPARSER_H__6ED0A159_76CD_41B6_9049_EEAA15B70723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace AutoUIFactory
{

class IXmlHanlde;
/*---------------------------------------------------------------------
* ��	����IXmlParser
* ��    �ܣ�xml��һ���������࣬ĿǰĬ�ϵĽ��������õ�tinyxml
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/06/02	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
Interface IXmlParser : public Singleton<IXmlParser>
{
public:
	IXmlParser();
	virtual ~IXmlParser();
/**  ����xml�ļ�
 *  @param[in] piXmlHandle ������
 *  @param[in] strFileName �ļ���
 *  @return �Ƿ�ɹ�
 */
	virtual bool ParserXml( IXmlHanlde* piXmlHandle, String strFileName ) = 0;
};

} // namespace AutoUIFactory end

#endif // !defined(AFX_IXMLPARSER_H__6ED0A159_76CD_41B6_9049_EEAA15B70723__INCLUDED_)
