// SystemXmlHandle.h: interface for the CSystemXmlHandle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMXMLHANDLE_H__763DFA04_BC85_425C_AF11_484E6D6B2834__INCLUDED_)
#define AFX_SYSTEMXMLHANDLE_H__763DFA04_BC85_425C_AF11_484E6D6B2834__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "IXmlHanlde.h"
#include "ITag.h"

namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* ��	����CSystemXmlHandle
* ��    �ܣ�ר�����ڽ���ϵͳxml�ļ���һ����
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/06/02	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
class CSystemXmlHandle : public IXmlHanlde 
{
public:
	static const String strSystemInfo;
	static const String strWindowInfo;
	static const String strWindowInfoName;
	static const String strWindowInfoValue;
	static const String strImagePath;
	static const String strLayoutPath;
	static const String strItemInfo;
    static const String strResolution;//�ֱ���
public:
	CSystemXmlHandle();
	virtual ~CSystemXmlHandle();
/*---------------------------------------------------------------------
* �� �� ����ElementStart
* ��    �ܣ������ض��ı�ǩȥ����صĴ�����
* ����˵����
* �� �� ֵ��
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/05/11	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
	virtual bool ElementStart( String strElement, const XMLAttributes& xmlAttributes );
/*---------------------------------------------------------------------
* �� �� ����
* ��    �ܣ�
* ����˵����
* �� �� ֵ��
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/05/11	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
	virtual bool ElementEnd( String strElement );
protected:
// /*---------------------------------------------------------------------
// * �� �� ����WindowInfoStart
// * ��    �ܣ���дWindowInfo
// * ����˵����
// * �� �� ֵ��
// * �޸ļ�¼��
// * ����			�汾		�޸���		�޸ļ�¼
// * 2011/05/11	v1.0		Ĳ��ï		����
// ----------------------------------------------------------------------*/
// 	bool WindowInfoStart( const XMLAttributes& xmlAttributes );
// 	bool WindowInfoEnd();
// /*---------------------------------------------------------------------
// * �� �� ����SystemInfoStart
// * ��    �ܣ���ȡSystemInfo
// * ����˵����
// * �� �� ֵ��
// * �޸ļ�¼��
// * ����			�汾		�޸���		�޸ļ�¼
// * 2011/05/11	v1.0		Ĳ��ï		����
// ----------------------------------------------------------------------*/
// 	bool SystemInfoStart( const XMLAttributes& xmlAttributes );
// 	bool SystemInfoEnd();
// 
// 	/*---------------------------------------------------------------------
// 	* �� �� ����ItemInfoStart
// 	* ��    �ܣ���ȡItemInfo
// 	* ����˵����
// 	* �� �� ֵ��
// 	* �޸ļ�¼��
// 	* ����			�汾		�޸���		�޸ļ�¼
// 	* 2011/05/11	v1.0		Ĳ��ï		����
// 	----------------------------------------------------------------------*/
// 	bool ItemInfoStart( const XMLAttributes& xmlAttributes );
// 	bool ItemInfoEnd();
protected:
	typedef std::map<String, IXmlTag*> XmlTagMap;
	XmlTagMap    m_mapXmlTag;
};

} // namespace AutoUIFactory end

#endif // !defined(AFX_SYSTEMXMLHANDLE_H__763DFA04_BC85_425C_AF11_484E6D6B2834__INCLUDED_)
