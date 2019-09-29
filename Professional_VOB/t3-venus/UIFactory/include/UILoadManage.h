// UILoadManage.h: interface for the CUILoadManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UILOADMANAGE_H__F943A576_E87E_4418_97C6_4AEDD36944AB__INCLUDED_)
#define AFX_UILOADMANAGE_H__F943A576_E87E_4418_97C6_4AEDD36944AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace AutoUIFactory
{

class CUILoadManage : public IObserver, public Singleton<CUILoadManage>
{
public:
	static const String strName;	
	static const String strValue;
	static const String strType;
public:
	CUILoadManage();
	virtual ~CUILoadManage();

	/**  ��ȡui�����ļ�
	 *  @param[in] strLayout 
	 *  @return �Ƿ��ȡ�ɹ�
	 *  @deprecated 
	 */
	bool ReadLayoutXml( String strLayout );

	/**  ��ȡһ�����ڶ�Ӧ��xml·��
	 *  @param[in] strName ��������
	 *  @param[out] strXml ·��
	 *  @return �Ƿ��ȡ�ɹ�
	 */
	bool GetWindowXml( String strName, XMLAttributes& attrib );

    String GetWindowXml( String strName ); //2011-11-16 by yjj
	
	/**  ���һ���ļ�·�����б���
	 *  @param[in] strName �ļ���
	 *  @param[in] strPath �ļ�·��
	 *  @return �Ƿ���ӳɹ�
	 */
	bool AddWindowXml( String strName, const XMLAttributes& attrib );

	/**  ���ϵͳ��Ϣ
	 *  @param[in] strElement ��Ϣ��
	 *  @param[in] attrib ��Ϣ����
	 *  @return �Ƿ���ӳɹ�
	 */

	void Update( IArgs* pArgs );
protected:
	void Update( XMLAttributes& xmlAttribs );

	typedef std::map< String, XMLAttributes > WindowAttribMap;
	WindowAttribMap m_mapWindowAttribs;
};

}
#endif // !defined(AFX_UILOADMANAGE_H__F943A576_E87E_4418_97C6_4AEDD36944AB__INCLUDED_)
