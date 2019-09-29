// listDataAssist.h: interface for the CListDataAssist class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LISTDATAASSIST_H__C473B406_CF28_47D8_B69D_FF5D0AC33FAE__INCLUDED_)
#define AFX_LISTDATAASSIST_H__C473B406_CF28_47D8_B69D_FF5D0AC33FAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

 
#include "uifactorydef.h"
 
class TiXmlElement;
class TiXmlDocument;
namespace AutoUIFactory
{
//typedef std::string String;
 

typedef struct tagListItem 
{   
    String strItemName; 
    bool   bVisible;
    int    nIndex;
} TListItem, *PTListItem;



class CListDataAssist  
{
public:
	CListDataAssist();
	virtual ~CListDataAssist();
public:
    BOOL GetListData( const String strFileName, const String strListName, OUT vector<TListItem>& LstData );

    BOOL SetListData( const String strFileName, const String strListName, vector<TListItem>& LstData );
    BOOL SetItemData( const String strFileName, const String strListName, const TListItem &LstData );
  
private:
    const TiXmlElement*  GetElement( const String strFileName, const String lstName );
    const TiXmlElement*  FindElement( const TiXmlElement* element, const String strListName );

    void GetAttribData(const TiXmlElement* element, OUT vector<TListItem>& LstData );
    BOOL SetAttribData( const TiXmlElement* element , const TListItem &tItem  );

    
private:

    std::vector<TListItem> m_LstData;
    String m_strElementName;

    const String m_strRootTag;  //list
    const String m_strName;  //list Name  

    const String m_strItem;  //item������
    const String m_strIndex; 
    const String m_strImg;
    const String m_strClickFun;
    const String m_strVisible;

    TiXmlDocument *m_pDocument;
    
};
}
#endif // !defined(AFX_LISTDATAASSIST_H__C473B406_CF28_47D8_B69D_FF5D0AC33FAE__INCLUDED_)
