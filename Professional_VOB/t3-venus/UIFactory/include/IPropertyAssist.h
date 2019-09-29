// IPropertyAssist.h: interface for the IPropertyAssist class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPROPERTYASSIST_H__15CEDED9_6BB9_4167_A3EC_7DBA88E0906E__INCLUDED_)
#define AFX_IPROPERTYASSIST_H__15CEDED9_6BB9_4167_A3EC_7DBA88E0906E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "System.h"
#include "IProperty.h"
#include "PropertySet.h"
namespace AutoUIFactory
{
class CPropertyAssist : public Singleton< CPropertyAssist >
{
public:
	static const String strName;
	static const String strValue;
public:
	CPropertyAssist();
	virtual ~CPropertyAssist();
/**  Ϊһ��������������
 *  @param[in] xmlAttrib �����������xml��Ϣ
 *  @param[in] window ����
 *  @param[in] strWndType ��������
 *  @return �Ƿ����óɹ�
 *  @note �������;����˻ᵽ�ĸ�PropertySet����ȥ��ѯ��Ȼ�����xmlAttrib���������ȥ�ҵ�Property���������window����
 */
	bool SetProperty( const XMLAttributes& xmlAttrib, const Window* window, const String& strWndType );
/**  ͨ��Value�Կؼ���ֵ
 *  @param[in] value �������ֵ
 *  @param[in] window ��Ӧ����
 *  @param[in] strWndType ��������
 *  @return �Ƿ����óɹ�
 */
	bool SetProperty( const IValue& value, const Window* window,  const String& strWndType );

/**  ��ȡһ�������ض���ֵ
 *  @param[out] value ��Ҫ���ص�ֵ
 *  @param[in] �μ���
 *  @param[out] �μ���
 *  @return ����д��ĳ���
 */
	bool GetValue( IValue& value, const Window* window, const String& strWndType );


/** ����������Ժ����Լ� 
 *  @return  
 *  @mark ���Ƴ�uifactoryʱʹ��  2012.12.3 yjj
 */
	void ClearAllProperty();
	void ClearAllPropertySet();

public:
/**  ��ȫ�ֵ�һ�����Ա��������һ������
 *  @param[in] strName ������������ȫ��Ψһ
 *  @param[in] piProperty ����
 *  @return ���������Ƿ�ɹ�
 */
	bool AddProperty( String strName, IProperty* piProperty, bool bCover = false );

/**  ��ȫ�ֵ�һ�����Ա������ȡһ������
 *  @param[in] strName ������
 *  @return ��Ӧ������
 */
	IProperty* GetProperty( String strName );

/**  ��ȫ�ֵ�һ�����Լ��ı��������һ�����Լ�
 *  @param[in] strName ���Լ����� ����Ψһ
 *  @param[in] piPropertySet ���Լ�
 *  @return �Ƿ���ӳɹ�
 */
	bool AddPropertySet( String strName, IPropertySet* piPropertySet, bool bCover = false );

/**  ��ȫ�ֵ�һ�����Լ��ı������ȡһ�����Լ�
 *  @param[in] strName ���Լ����� ����Ψһ
 *  @return ���Լ�
 */
	IPropertySet* GetPropertySet( String strName );

/**  ͨ�����봰�����ͣ���ȡ�����Լ���Ȼ��ͨ�������Լ��������Ҫ������
 *  @param[in] strWndType ��������
 *  @param[in] strName ��������
 *  @return ����
 */
	IProperty* GetPropertyByCommonName( String strWndType, String strName );

/**  ������Ե����Լ���
 *  @param[in] strWndType ��������
 *  @param[in] strProperty ��������value����
 *  @param[in] strValue ��������
 *  @return �Ƿ����óɹ� 
 *  @mark �������������Լ��ж�̬��� -2012.12.14 xcr
          strProperty��IValue���࣬��strValue��IProperty����
 */
    bool AddPropertyToSet( String strWndType, String strProperty, String strValue );

protected:
	typedef std::map< String, IProperty* > PropertyMap;
/*
 * ȫ�ֵ�һ�����Եı�\n 
 * ��������˲�ͬ�ؼ���ͬ�����ԣ������Size��һ�� \n
 * �������ButtonSize,BmpButtonSize,WindowSize��
 */
	PropertyMap m_mapProperties;

	typedef std::map< String, IPropertySet* > PropertySetMap;
/*
 * ȫ�ֵ�һ�����Լ��ı�\n 
 * ���Լ���������һ�ര�ڹ��õ����ԣ�String��String�ģ�\n
 * ǰ���String�ǹ��õ����֣�����һ��String��Ӧ�ľ���ȫ�ֵ����Ա����������
 */
	PropertySetMap m_mapPropertySets;
};

/*
* ע������
* name ���� className���Զ�Ӧ�Ĵ�����
* Ϊ�˱�֤����һ�£�����ע���ʱ����Ҫ����Ҫ����д��
* ���������������������ʽ������д�����꣬����ֱ�ӵ��ö�Ӧ����
*/
#define REG_PROPERTY( name ) \
CPropertyAssist::GetSingletonPtr()->AddProperty( #name, new Property_##name )

/*
* ע�����Լ�
* name ���� className���Լ���
* Ϊ�˱�֤����һ�£�����ע���ʱ����Ҫ����Ҫ����д��
* ���������������������ʽ������д�����꣬����ֱ�ӵ��ö�Ӧ����
*/
#define REG_PROPERTY_SET( name ) \
CPropertyAssist::GetSingletonPtr()->AddPropertySet( #name, new name##PropertySet )

/*
* �����Լ�������������
* wndtype �������� propertyname�������� valuename��������
* �����ڳ��������������Լ���̬�������
* Ϊ�˱�֤����һ�£�����ע���ʱ����Ҫ����Ҫ����д��
*/
#define ADD_PROPERTY_TO_SET( wndtype, propertyname, valuename ) \
CPropertyAssist::GetSingletonPtr()->AddPropertyToSet( #wndtype, propertyname, valuename )


} // namespace AutoUIFactory end
#endif // !defined(AFX_IPROPERTYASSIST_H__15CEDED9_6BB9_4167_A3EC_7DBA88E0906E__INCLUDED_)

