// WndTreeHelp.h: interface for the CWndTreeHelp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WNDTREEHELP_H__6FAD23DF_D071_4754_8FF7_59E9654DE4E7__INCLUDED_)
#define AFX_WNDTREEHELP_H__6FAD23DF_D071_4754_8FF7_59E9654DE4E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "templateClass.h"
#include "WindowManage.h"
namespace AutoUIFactory
{

class CWndTreeHelp  
{
public:
/*
 * �ָ���Ŷ���\n
 */
	static const char chPartitionChar;
public:
	CWndTreeHelp();
	virtual ~CWndTreeHelp();
	
	/**  ��ȡ�ؼ���Ϣ
	 *  @param[in] nLevel ��һ��
	 *  @param[in] strName �ؼ�����
	 *  @param[in] pWndTree �ؼ���
	 *  @param[in] bPartitionString �Ƿ��ַ�����Ҫ�ָ�
	 *  @return �ؼ���Ϣ
	 */
	static const IWndTree* GetWindow( String strName, const IWndTree* pWndTree );

	/**  ��ȡ�ؼ���Ϣ
	 *  @param[in] pWnd ����ָ��
	 *  @param[in] pWndTree ��Ҫ��������
	 *  @return �����������Ĵ���
	 */
	static const IWndTree* GetWindow( Window* pWnd, const IWndTree* pWndTree );
protected:
	/**  ������������������Ҫ�и����ַ���
	 *  @param[in] strName �ؼ�����
	 *  @param[in] pWndTree �ؼ���
	 *  @return �ؼ���Ϣ
	 */
	static const IWndTree* GetWindowByPartitionString( const String& strName, const IWndTree* pWndTree );
};

} // namespace AutoUIFactory end

#endif // !defined(AFX_WNDTREEHELP_H__6FAD23DF_D071_4754_8FF7_59E9654DE4E7__INCLUDED_)
