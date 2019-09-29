// LayoutXmlHandle.h: interface for the CLayoutXmlHandle class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LAYOUTXMLHANDLE_H__C9E3A152_E2BA_450F_9551_195E9AE54A2A__INCLUDED_)
#define AFX_LAYOUTXMLHANDLE_H__C9E3A152_E2BA_450F_9551_195E9AE54A2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "uifactorydef.h"
#include "IXmlHanlde.h"
#include "ITag.h"

#include "WindowManage.h"

namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* ��	����CLayoutHandle
* ��    �ܣ�ר�����ڽ�������xml�ļ�����
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/06/02	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
class CLayoutHandle : public IXmlHanlde
{
public:
	const static String strCreateWindow;
	const static String strProperty;
	const static String strEvent;
	const static String strCallBackFunc;
	const static String strLayout;
	const static String strScheme;
public:
	CLayoutHandle();
	~CLayoutHandle();
/*---------------------------------------------------------------------
* �� �� ����ElementStart
* ��    �ܣ���д���ֱ�ǩ
* ����˵����
* �� �� ֵ��
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/05/11	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
	bool ElementStart( String strElement, const XMLAttributes& xmlAttributes );
	bool ElementEnd( String strElement );

/*---------------------------------------------------------------------
* �� �� ����ClearTags
* ��    �ܣ��������tag���ͷ��ڴ� 
* ����˵����
* �� �� ֵ��
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2012/12/3  	v1.0		�����		����
----------------------------------------------------------------------*/
	void ClearTags();

public:
/*---------------------------------------------------------------------
* �� �� ����AppendWindow
* ��    �ܣ���Ӵ���
* ����˵����
* �� �� ֵ��
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/05/12	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
	bool AppendWindow( Window* pWnd, String strName, XMLAttributes xmlAttribs );
	bool PopWindow();
	const Window* GetCurWindow();
	
	void SetCurWnd( Window* pWnd )
	{
		m_pCurWindow = pWnd;
		m_stackWnd.push_back( pWnd );
	}

	void SetCurWndTree( IWndTree* pWndTree );

	const IWndTree* GetCurWindowTree();

	bool AddXmlTag( String strElement, IXmlTag* pXmlTag );
protected:
	bool AppendWindowInTree( Window* pWnd, String strName, XMLAttributes xmlAttribs );
	bool PopWindowFromTree();
/*---------------------------------------------------------------------
* �� �� ����IniTags
* ��    �ܣ����Ĭ�ϱ�ǩ����
* ����˵����
* �� �� ֵ��
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/05/12	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
	bool IniDefaultTags();

	
protected:

	typedef std::map<String, IXmlTag*> TagMap;
	TagMap	m_mapTags;

/*
 * ���ڵ�һ����ջ������xml�Ľ�������Զ����֪���ö��ĸ����ڽ�������\n 
 */
	typedef std::vector<Window*> WindowStack;
	WindowStack m_stackWnd;
	Window* m_pCurWindow;

/*
 * ��ǰ��һ��IWndTree�Ķ�ջ������start��ӣ�����end��ջ\n 
 */
	typedef std::vector<IWndTree*> WndTreeStack;
	WndTreeStack m_stackWndTree;
	IWndTree* m_pCurWndTree;

public:
	bool m_bInScheme;
};

} // namespace AutoUIFactory end

#endif // !defined(AFX_LAYOUTXMLHANDLE_H__C9E3A152_E2BA_450F_9551_195E9AE54A2A__INCLUDED_)
