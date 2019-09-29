// System.h: interface for the CSystem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEM_H__0A0675EB_2D2B_4BCD_9310_F9D9A7038FDB__INCLUDED_)
#define AFX_SYSTEM_H__0A0675EB_2D2B_4BCD_9310_F9D9A7038FDB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*
 * @defgroup System ϵͳ�࣬ͳ�����д�������
 * @author  Ĳ��ï
 * @version 1.0
 * @date  2011/05/31
 * @{
 */
 
#include "uifactorydef.h"
#include "Logger.h"
#include "templateClass.h"
#include "WindowFacotryManage.h"
#include "XmlAttrib.h"
#include "IScript.h"
#include "WindowManage.h"
namespace AutoUIFactory
{

class IXmlParser;
class IScript;

typedef std::multimap<String, XMLAttributes> SystemInfoMultiMap;
class Args_SystemObserver : public IArgs
{
public:
	Args_SystemObserver( SystemInfoMultiMap& mapSystemInfo ) : IArgs( "SystemObserver" ), m_mapSystemInfos( mapSystemInfo ){}
	SystemInfoMultiMap&		m_mapSystemInfos;
};
/*---------------------------------------------------------------------
* ��	����CSystem
* ��    �ܣ���ΪUIFactory���ܹ�
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/06/02	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
class CSystem : public Singleton<CSystem>
{
public:
	friend class CWindowManage;
	friend class CSystemXmlHandle;
	friend class XmlSaveDocument;
	static const String strWndParent;
	static const String strName;
	static const String strValue;
public:
	/**  
	 *  @param[in] strMainXml ��xml·��(����һЩϵͳ����Ϣ)
	 *  @param[in] piScript �ű�ִ��ģ��
	 *  @param[in] IXmlParser xml������
	 *  @deprecated ����һ�������ֻ࣬��Ҫ���������õĳ�������newһ�ξͿ���
	 */
	CSystem( String strMainXml = "", IScript* piScript = 0, IXmlParser* pXmlParser = 0 );
	virtual ~CSystem();

	void AddObserver( IObserver* piObserver );
	
	void Launch();
public:
	
	void SetImagePath( String strPath );
	String GetImagePath();

	/**  ����ϵͳ�����ļ�·��
	 *  @param[in] strPath ·��
	 *  @return 
	 */
	void SetLayoutPath( String strPath );
	String GetLayoutPath();

	/**  ����ItemInfo�ļ�·��
	 *  @param[in] strPath ·��
	 *  @return 
	 */
	void SetItemInfoPath( String strPath );
	String GetItemInfoPath();

    /**  ��ȡEditĬ��������Ϣ
	 *  @return 
	 */
    TFontInfo GetEditFontInfo();

    /**  ��ȡStaticĬ��������Ϣ
	 *  @return 
	 */
    TFontInfo GetStaticFontInfo();

public:
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

    /**  ��ȡһ�����ڶ�Ӧ��xml·��
	 *  @param[in] strName ��������
	 *  @param[out] strXml ·��
	 *  @return �Ƿ��ȡ�ɹ�
	 */
	String GetWindowXml( String strName );
	
	/**  ���һ���ļ�·�����б���
	 *  @param[in] strName �ļ���
	 *  @param[in] strPath �ļ�·��
	 *  @return �Ƿ���ӳɹ�
	 */
	bool AddWindowXml( String strName, const XMLAttributes& attrib );
protected:
	/**  ��д��xml�ļ�
	 *  @param[in] strMainXml �ļ�·��
	 *  @return ��ȡ�Ƿ�ɹ�
	 *  @deprecated �����ȡ����ϵͳ���޷�ʹ��
	 */
	bool ReadMainXml( String strMainXml );

	bool AddSystemInfo( String strElement, const XMLAttributes& attrib );

	void Update();

protected:
	/*
	 * �ű�����ģ��  
	 */
	IScript* m_pScript;
	
	/*
	 * xml����ģ��  
	 */
	IXmlParser* m_pXmlParser;	

	/*
	 * ��¼���д����Ӧ��xml�ļ�  
	 */
	SystemInfoMultiMap		m_mapSystemInfos;

	/*
	 * ϵͳ��ʼ������Ҫ֪ͨ�Ķ���\n 
	 */
	typedef std::vector<IObserver*> ObserverVec;
	ObserverVec				m_vecObservers;

	String m_strMainXml;
};
} // namespace AutoUIFactory end

/** @} */ 
#endif // !defined(AFX_SYSTEM_H__0A0675EB_2D2B_4BCD_9310_F9D9A7038FDB__INCLUDED_)
