#include "stdafx.h"
#include "System.h"
#include "PropertySet.h"
#include "PropertyHelp.h"

namespace AutoUIFactory
{
bool IPropertySet::AddProperty( String strProperty, String strValue )
{
	CtrlPropertyMap::iterator itr = m_mapCtrlProperties.find( strProperty );
	if ( itr != m_mapCtrlProperties.end() )
	{
		itr->second = strValue;
		LOGEVENT( "IPropertySet::AddProperty �滻��һ������ name= " + strProperty );
		return true;
	}
	m_mapCtrlProperties.insert( CtrlPropertyMap::value_type( strProperty, strValue ) );
//	LOGEVENT( "IPropertySet::AddProperty �����һ������ name= " + strProperty );
	return true;
}

bool IPropertySet::RemoveProperty( String strProperty )
{
	CtrlPropertyMap::iterator itr = m_mapCtrlProperties.find( strProperty );
	if ( itr != m_mapCtrlProperties.end() )
	{
		m_mapCtrlProperties.erase( itr );
	//	LOGEVENT( "IPropertySet::RemoveProperty ɾ����һ������ name= " + strProperty );
		return true;
	}
	LOGEVENT( "IPropertySet::RemoveProperty û���ҵ�Ҫɾ�������� name= " + strProperty );
	return true;
}

bool IPropertySet::GetProperty( const String& strType, String& strProperty )
{
	CtrlPropertyMap::iterator itr = m_mapCtrlProperties.find( strType );
	if ( itr != m_mapCtrlProperties.end() )
	{
		strProperty = itr->second;
		return true;
	}
	LOGEVENT( "IPropertySet::GetProperty û���ҵ����� name= " + strType );
	return false;
}
} // namespace AutoUIFactory end
