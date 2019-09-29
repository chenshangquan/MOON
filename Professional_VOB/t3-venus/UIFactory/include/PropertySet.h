#ifndef _PROPERTYSET_H_
#define _PROPERTYSET_H_
#include "IProperty.h"

#include "uifactorydef.h"

namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* ��	����IPropertySet
* ��    �ܣ��ṩһ��ӳ���ϵ�����Խ�ĳһ��ռ������ӳ�䵽ȫ�ֵ�һ�����Ա�����ȥ
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/06/02	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
class IPropertySet
{
public:
	IPropertySet(){}
	virtual ~IPropertySet(){}
	bool GetProperty( const String& strType, String& strProperty );
	bool AddProperty( String strProperty, String strValue );
	bool RemoveProperty( String strProperty );
protected:
	typedef std::map< String, String > CtrlPropertyMap;
	CtrlPropertyMap m_mapCtrlProperties;
};

/*
 *  ���ڶ������Լ���Ĭ�����д�����ռ䶼������CWndPropertySet \n
 *	�����Ҫ����µ����ԣ������������м���AddProerty���������\n 
 */
#define DECLARE_PROPERTYSET_BEGIN( classname,baseclass ) \
	class classname ## PropertySet : public baseclass \
{ \
public: \
classname ## PropertySet(){ \

#define DECLARE_PROPERTYSET_END } \
}; \

} // namespace AutoUIFactory end
#endif