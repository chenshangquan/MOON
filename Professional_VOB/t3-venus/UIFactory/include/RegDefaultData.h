// RegDefaultData.h: interface for the CRegDefaultData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REGDEFAULTDATA_H__46668158_5ACE_4AC5_8DBA_7C562AF7320F__INCLUDED_)
#define AFX_REGDEFAULTDATA_H__46668158_5ACE_4AC5_8DBA_7C562AF7320F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "uifactorydef.h"

namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* ��	����CRegDefaultData
* ��    �ܣ�ע��һЩĬ������
* ����˵����һ��ֻ��System��
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/06/02	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
/*
���һ���¿ؼ�������
1����ӹ����������Ŀռ���ΪCXXX�����ú�DECLARE_WINDOW_FACTORY(CXXX)
2������˹�������Ҫ��CRegDefaultData�����RegDefaultWindowFactory��������ע��
	��ʹ�ú�REG_WINDOW_FACTORY(CXXX)
3���ؼ�д�ú���ҪΪ��������Լ�����ʹ�ú� DECLARE_PROPERTYSET_BEGIN( CXXX, IPropertySet ) �� DECLARE_PROPERTYSET_END
	�����Ҫ����һЩĬ�ϵ����ԣ��뽫IPropertySet�޸�ΪCWndPropertySet
4��д�ÿؼ���������Ҫ��CRegDefaultData�����RegDefaultWindowPropertySet��������ע��
	Ҳ��ʹ�ú�REG_PROPERTY_SET(CXXX)
5������ؼ�������ӵ����ԣ���ʹ�ú�DECLARE_VALUE_BEGIN(CXXXImage) DECLARE_VALUE_END ��������
	����ע��������ο���
6�������������Ҫ�滻�����ԣ�����CXXXImage��Ҫ�滻WindowPos������ԣ�ֱ���ڵ�3���ĺ��м����
	AddProperty( "WindowPos", "CXXXImage" );
7����������Ժ���Ҫ��CRegDefaultData�����RegDefaultWindowProperty��������ע��
	ʹ�ú�REG_PROPERTY(CXXXImage)
*/
class CRegDefaultData  
{
public:
	CRegDefaultData();
	virtual ~CRegDefaultData();
/*
*  ע��ȫ������
*/
	static void RegAllDefaultData();
/*
 * ע��Ĭ�ϵĹ���\n 
 */
	static void RegDefaultWindowFactory();
/*
 * ע��Ĭ�ϵ�����\n 
 */
	static void RegDefaultWindowProperty();
/*
 * ע��Ĭ�����Լ�\n 
 */
	static void RegDefaultWindowPropertySet();
/*
 * ע��Ĭ���¼�\n 
 */
	static void RegDefaultWindowEvent();
	
/*
 * ע��uilib�Ĺ���\n
 */
	static void RegUILibWindowFactory();

/*
 * ע��uilib�ؼ������Լ�\n 
 */
	static void RegUILibPropertySet();

/*
 * ע��Ĭ�ϵķ��\n 
 */
	static void RegDefaultStyle();

/*
 * ע��Ĭ�ϵ��㷨\n
 */
	static void RegDefaultAlgorithm();
};

} // namespace AutoUIFactory end

#endif // !defined(AFX_REGDEFAULTDATA_H__46668158_5ACE_4AC5_8DBA_7C562AF7320F__INCLUDED_)
