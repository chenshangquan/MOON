// CallFuncManage.h: interface for the CCallFuncManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALLFUNCMANAGE_H__449890B2_C187_4CF4_B88F_E4C3A5A6FF0D__INCLUDED_)
#define AFX_CALLFUNCMANAGE_H__449890B2_C187_4CF4_B88F_E4C3A5A6FF0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* ��	����CFuncManage
* ��    �ܣ�����ȫ�ֺ���ָ���һ���ط�
* ����˵�������ֱ���Ψһ
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/06/02	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
class CFuncManage : public Singleton< CFuncManage >
{
public:
	CFuncManage();
	virtual ~CFuncManage();
/**  ע��ȫ�ֺ���
 *  @param[in] strName ��������Ӧ������ ����Ψһ
 *  @param[in] piFunc ����ָ�룬�����Ǿ�̬�����������ǳ�Ա������
 *  @return �Ƿ�ɹ�
 */
	bool RegFunc( String strName, ICallBackFuncBase* piFunc );

/**  ��ע��ȫ�ֺ���
 *  @param[in] strName ��������Ӧ������
 *  @return �Ƿ�ɹ�
 */
	bool UnRegFunc( String strName );

/**  ��ע������ȫ�ֺ��� 
 *  @return �Ƿ�ɹ�
 *  @mark �����Ƴ�uifactoryʱʹ�ã��ͷ�new���ڴ� 2012.12.3 yjj
 */
	void UnRegAllFunc();

/**  ִ�к���
 *  @param[in] strName ������
 *  @param[in] args ���� ���Ը����Լ���Ҫ�������
 *  @see IArgs
 *  @param[out] 
 *  @return �Ƿ�ɹ�
 */
	bool ExeFunc( String strName, const IArgs& args );
protected:
	typedef std::map< String, ICallBackFuncBase* > FuncMap;
/*
 * ȫ�ֺ���map��\n 
 */
	FuncMap m_mapFuncs;
};

/*
* ע��ȫ�ֺ����������Ա������Ϊ����ָ�� \n
* str ������ʾ func ������ obj ��ָ�� objType ������
*/
#ifndef REG_GOBAL_MEMBER_FUNC
#define REG_GOBAL_MEMBER_FUNC( str, func, obj, objType ) \
CFuncManage::GetSingletonPtr()->RegFunc( str, new CMemberCallBackFunc<objType>( func, obj ) );
#endif

/*
* ע��ȫ�ֺ�������ȫ�ֻ��߾�̬������Ϊ����ָ�� \n
* str ������ʾ func ������
*/
#ifndef REG_GOBAL_STATIC_FUNC 
#define REG_GOBAL_STATIC_FUNC( str, func ) \
CFuncManage::GetSingletonPtr()->RegFunc( str, new CCallBackFunc( func ) );
#endif

/*
* ��ע��ȫ�ֺ��� \n
* str ������ʾ
*/
#ifndef UN_REG_GOBAL_FUNC
#define UN_REG_GOBAL_FUNC( str ) CFuncManage::GetSingletonPtr()->UnRegFunc( str );
#endif
} // namespace AutoUIFactory end
#endif // !defined(AFX_CALLFUNCMANAGE_H__449890B2_C187_4CF4_B88F_E4C3A5A6FF0D__INCLUDED_)

