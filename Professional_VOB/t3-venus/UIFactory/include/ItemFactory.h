// ItemFactory.h: interface for the CItemFactory class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEMFACTORY_H__CEDBB4B6_E51C_4067_A953_6A354F57216D__INCLUDED_)
#define AFX_ITEMFACTORY_H__CEDBB4B6_E51C_4067_A953_6A354F57216D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "uifactorydef.h"
#include "XmlAttrib.h"
namespace AutoUIFactory
{
class CItemFactory : public Singleton<CItemFactory>
{
public:
	static const String strType;
	static const String strImage;
	static const String strText;
	static const String strSize;

	static const String strTextItem;	
	static const String strImageItem;
	static const String strMidImageItem;
	static const String strFunc;
	static const String strFontColor;
	static const String strFontName;
	static const String strFontSize;
	static const String strSelColor;
	static const String strAlignment;
	static const String strLineAlignment;
	static const String strLayoutAlgorithm;
	static const String strSortAlgorithm;

	static const String strExTextItem;
	static const String strSecondText;
	static const String strSecondFontColor;
	static const String strSecondFontName;
	static const String strSecondFontSize;
	static const String strSecondAlignment;

	static const String strCanMove;
	static const String strCanDrag;
	static const String strAlwaysShow;
	static const String strListItem;
	static const String strCheckItem;
	static const String strButtonItem;
public:
/**  ������Ŀ
 *  @param[in] xmlAttrib xml��Ϣ 
 *  @return ����Ŀ
 */
	IBaseItem* CreateItem( XMLAttributes& xmlAttrib );

/**  ������Ŀ
 *  @param[in] strType ��Ŀ����
 *  @return ����Ŀ
 */
	IBaseItem* CreateItem( String strType );

	bool AddItemInfo( String strType, XMLAttributes xmlAttribs );
	bool GetItemInfo( String strType, XMLAttributes& xmlAttribs );
protected:
	/*
	 * ��¼����item��Ϣ  
	 */
	typedef std::map<String, XMLAttributes> ItemInfoMap;
	ItemInfoMap    m_mapItemInfos;
};

}


#endif // !defined(AFX_ITEMFACTORY_H__CEDBB4B6_E51C_4067_A953_6A354F57216D__INCLUDED_)
