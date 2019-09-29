// WindowManage.h: interface for the CWindowManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDOWMANAGE_H__D64B4440_822E_4154_A06C_BD2CB1DFDC20__INCLUDED_)
#define AFX_WINDOWMANAGE_H__D64B4440_822E_4154_A06C_BD2CB1DFDC20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "uifactorydef.h"
#include "windowfactory.h"
/*---------------------------------------------------------------------
* ��	����CWindowManage
* ��    �ܣ����ڹ���ʹ�������
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/05/11	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
namespace AutoUIFactory
{
	class CTagInfo
	{
	public:
		CTagInfo( String strTag, XMLAttributes xmlAttribs ) : m_strTag( strTag ), m_xmlAttribs( xmlAttribs ){}
		String m_strTag;
		XMLAttributes m_xmlAttribs;
		CTagInfo* Clone()
		{
			CTagInfo* pTagInfo = new CTagInfo( m_strTag, m_xmlAttribs );
			return pTagInfo;
		}
	};
typedef IItem<CTagInfo,int> SchemeMap;
class WndInfo
{
public:
	static const String strDefaultScheme;
public:
	WndInfo();
	~WndInfo();
	
	String strType;
	Window* pWnd;
	
	void AddScheme( String strName, XMLAttributes xmlAttributes );
	void AddAttribs( String strName, XMLAttributes xmlAttributes );

	WndInfo* Clone();
	SchemeMap* GetSchemeMap( String strName );

	void SetCurUseScheme( String str ){ m_strCurUseScheme = str; }
	String GetCurUseScheme(){ return m_strCurUseScheme; }

    void EndScheme();//ִ����һ��Scheme
private:
	int m_nIndex;
	SchemeMap* m_pCurScheme;
	SchemeMap* m_schemeMap;
	String m_strCurUseScheme;
};

typedef IItem< WndInfo, String > IWndTree;

class CWindowManage : public Singleton<CWindowManage>
{
public:
	CWindowManage();
	virtual ~CWindowManage();
/**  
 *  @param[in] strType �������ͣ��磺Window��Button
 *  @param[in] strName ��������
 *  @param[in] pParent ������
 *  @return ����ָ��
 */
	Window* Create( IArgs& iArgs );
public:
/**  ͨ�����ֻ�ø��ڵ�����Ĵ������������Ҫ��ȡ����������������ؼ�����ο�CWndTreeHelp
 *  @param[in] strName ��������
 *  @return ������ָ��
 */
	const IWndTree* GetWindowTree( String strName );
/**  ��ȡ���ڵ�
 *  @return ���ظ��ڵ�
 */
	IWndTree*	GetRoot() const { return m_pRoot; }
/**  ���ٴ��ڣ���������CWnd��Destory
 *  @param[in] pWnd ����ָ��
 *  @return �Ƿ����ٳɹ�
 */
	bool DestoryWnd( Window* pWnd );
/**  ���ٴ��ڣ���������CWnd��Destory
 *  @param[in] pWndTree ������
 *  @return �Ƿ����ٳɹ�
 */
	bool DestoryWnd( IWndTree* pWndTree );

	/**  �������д��ڴ��ڣ���������CWnd��Destory
 *  @param[in] pWndTree ������
 *  @return �Ƿ����ٳɹ�
 *  @auth yjj 2011.11.30
 */
	bool DestoryAllWnd();
protected:
/*
 * ���ڵ�\n
 */
	IWndTree* m_pRoot;
};


} // namespace AutoUIFactory end
#endif // !defined(AFX_WINDOWMANAGE_H__D64B4440_822E_4154_A06C_BD2CB1DFDC20__INCLUDED_)
