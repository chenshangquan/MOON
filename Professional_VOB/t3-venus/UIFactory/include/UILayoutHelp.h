// UILayoutHelp.h: interface for the CUILayoutHelp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UILAYOUTHELP_H__A9262EDB_ED17_4A47_9455_E0DA12A70182__INCLUDED_)
#define AFX_UILAYOUTHELP_H__A9262EDB_ED17_4A47_9455_E0DA12A70182__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "uifactorydef.h"
#include "templateClass.h"
namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* ��	����CUILayoutHelp
* ��    �ܣ����ڶ�̬����UI���ֵ��࣬��Ҫ��xml������Ӧ�����òſ���
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/06/09	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
class CUILayoutHelp  
{
public:
	const static String strLeft;
	const static String strRight;
	const static String strTop;
	const static String strBottom;
	const static String strCenter;
	const static char chPartitionChar;
public:
	CUILayoutHelp();
	virtual ~CUILayoutHelp();
/**  ����UI����
 *  @param[in] strWndName		��Ҫ���ִ��ڵ�����
 *	@param[in] bRecurrence		�Ƿ�Ҫ�����ô��������д���
 *  @return �Ƿ�ɹ�
 */
	static bool LayoutUI( const String& strWndName, bool bRecurrence = true );

/**  ����UI����
 *  @param[in] pWnd				����ָ��
 *	@param[in] bRecurrence		�Ƿ�Ҫ�����ô��������д���
 *  @return �Ƿ�ɹ�
 */
	static bool LayoutUI( const Window* pWnd, bool bRecurrence = true );

/**  ����UI����
 *  @param[in] pWndTree			�ؼ���
 *	@param[in] bRecurrence		�Ƿ�Ҫ�����ô��������д���
 *  @return �Ƿ�ɹ�
 */
	static bool LayoutUI( const IWndTree* pWndTree, bool bRecurrence = true );

protected:
/**  Layout
 *  @param[in] 
 *  @param[in] 
 *  @param[out] 
 *  @return �Ƿ�ɹ�
 */
	static bool Layout( WndInfo* pWndInfo );
};

} // namespace AutoUIFactory end
#endif // !defined(AFX_UILAYOUTHELP_H__A9262EDB_ED17_4A47_9455_E0DA12A70182__INCLUDED_)
