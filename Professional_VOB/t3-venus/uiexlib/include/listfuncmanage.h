/*---------------------------------------------------------------------
* ��	����CListFuncManage
* ��    �ܣ��б�ص�����������
* ����˵��������ע���б���Ӧ����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2012/12/05	v1.0		Ф��Ȼ		����
----------------------------------------------------------------------*/

#if !defined(AFX_LISTFUNCMANAGE_H__6CD44751_8882_4EE4_89D2_C7367CB5C255__INCLUDED_)
#define AFX_LISTFUNCMANAGE_H__6CD44751_8882_4EE4_89D2_C7367CB5C255__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "uiexBaseData.h"

class CListFuncManage : public ISingleTon< CListFuncManage > 
{
public:
	CListFuncManage();
	virtual ~CListFuncManage();

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
    *  @mark �����Ƴ�uifactoryʱʹ�ã��ͷ�new���ڴ�  yjj
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
* ע���б�ص������������Ա������Ϊ����ָ�� \n
* str ������ʾ func ������ obj ��ָ�� objType ������
*/
#ifndef REG_LIST_CALLFUNC
#define REG_LIST_CALLFUNC( str, func, obj, objType ) \
CListFuncManage::GetSingletonPtr()->RegFunc( str, new CMemberCallBackFunc<objType>( func, obj ) );
#endif

/*
* ��ע���б�ص����� \n
* str ������ʾ
*/
#ifndef UN_REG_LIST_CALLFUNC
#define UN_REG_LIST_CALLFUNC( str ) CListFuncManage::GetSingletonPtr()->UnRegFunc( str );
#endif

#endif // !defined(AFX_LISTFUNCMANAGE_H__6CD44751_8882_4EE4_89D2_C7367CB5C255__INCLUDED_)
