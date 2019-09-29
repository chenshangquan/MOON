// PropertyHelp.h: interface for the CPropertyHelp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROPERTYHELP_H__367F886B_837E_4680_8867_1BA68DBF1481__INCLUDED_)
#define AFX_PROPERTYHELP_H__367F886B_837E_4680_8867_1BA68DBF1481__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "uifactorydef.h"

 
#include "list.h"
#include "IValue.h"
namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* ��	����CPropertyHelp
* ��    �ܣ��ṩһЩ���õ�����ת��
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/06/02	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
class CPropertyHelp  
{
public:
	CPropertyHelp();
	virtual ~CPropertyHelp();
public:
	static	float		stringToFloat(const String& str);
	static	String		floatToString(float val);

	static	int			stringToInt(const String& str);
	static	String		intToString(int val);

	static	bool		stringToBool(const String& str);
	static	String		boolToString(bool val);

	static	POINT		stringToPoint(const String& str);
	static	String		pointToString(const POINT& val);

	static	SIZE		stringToSize(const String& str);
	static	String		sizeToString(const SIZE& val);

	static  COLORREF	stringToColor(const String& str); 
	static	String		colorToString(const COLORREF& col);
	
	static	RECT		stringToRect(const String& str);
	static	String		rectToString(const RECT& rc);

	static DWORD		StringToDWORD(const String& str);
	static String       DWORDToString(const DWORD&val);

    static void         StringToRange( const String& str, int &nMin, int &nMax);
    static String       RangeToString(int nMin, int nMax);

	static StringAlignment stringToAlignment(const String& str);
	static String		alignmentToString(const StringAlignment& align);

    static FontStyle    stringToFontStyle(const String& str);
	static String		fontStyleToString(const FontStyle& align);

    //��ǰ�ֱ��ʺ�ԭ�ֱ��ʵı�ֵ
    static void CPropertyHelp::GetResolutionScale( float &fx, float &fy);

    //�ֱ�������Ӧ
    static void ResolutionAdp( long &nx, long  &ny);

    //�����С����Ӧ
    static void  FontSizeAdp( int &nFontSize );
   
};

 
}// namespace AutoUIFactory end

#endif // !defined(AFX_PROPERTYHELP_H__367F886B_837E_4680_8867_1BA68DBF1481__INCLUDED_)
