// WindowFacotryManage.h: interface for the CWindowFacotryManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDOWFACOTRYMANAGE_H__5220EE0A_4FC2_4C36_90F8_A46CEDEE8F20__INCLUDED_)
#define AFX_WINDOWFACOTRYMANAGE_H__5220EE0A_4FC2_4C36_90F8_A46CEDEE8F20__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "uifactorydef.h"
#include "templateClass.h"
#include "windowfactory.h"

namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* ��	����CWindowFacotryManage
* ��    �ܣ�����������
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/06/02	v1.0		Ĳ��ï		����
-----s-----------------------------------------------------------------*/
class CWindowFacotryManage : public Singleton< CWindowFacotryManage >
{
public:
	CWindowFacotryManage();
	virtual ~CWindowFacotryManage();
public:
/**  ���һ������
 *  @param[in] strType��������
 *  @param[in] pWindowFactory
 *  @return �Ƿ�ɹ�
 */
	bool AddFactory( String strType, IWindowFactory* pWindowFactory, bool bCover = false );
/**  ���һ������
 *  @param[in] strType��������
 *  @return ����ָ��
 */
	const IWindowFactory* GetFactory( String strType );

/**  �������й�������  
 *  @mark 2012.12.3 yjj
 */
	void ClearFactory( );



protected:
	typedef std::map<std::string, IWindowFactory* > FactoryMap;
/*
 * ����map��\n 
 */
	FactoryMap m_mapFactories;
};

/*
 * ע��һ������ name=���� class=����\n 
 * Ϊ�˱�֤����һ�£�����ע���ʱ����Ҫ����Ҫ����д��
 * ���������������������ʽ������д�����꣬����ֱ�ӵ��ö�Ӧ����
 */
#define REG_WINDOW_FACTORY( name ) \
	CWindowFacotryManage::GetSingletonPtr()->AddFactory( #name, new name##Factory )
} // namespace AutoUIFactory end
#endif // !defined(AFX_WINDOWFACOTRYMANAGE_H__5220EE0A_4FC2_4C36_90F8_A46CEDEE8F20__INCLUDED_)
