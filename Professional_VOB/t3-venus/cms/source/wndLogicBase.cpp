#include "stdafx.h" 
#include "wndLogicBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
 


bool CWndLogicBase::IsAllE164Number( String strText )
{
	LPCTSTR  lpstr  =  (LPCTSTR)strText.c_str(); 

    s32 nLen = _tcslen( lpstr );
    if ( nLen == 0 )
    {
        return false;
    }
	
    s32 nIndex = _tcsspn( lpstr, _T("0123456789*,#") );
	
	if ( nLen == nIndex )
	{
		return true;
	}
	return false;
}

//  ; /   ?   : @ & = + $ , % ¡­¡­ & ^ ¿Õ¸ñ tab
bool CWndLogicBase::IsValidTPStr( String strText )
{
	CString strError = INVALID_ALIAS_FOR_CODE;
	CString str(strText.c_str());
	CString strRe = str.SpanExcluding( strError );
	if ( strRe != str )
	{
		return false;
	} 
    return true;
}

 