// sysTime.h: interface for the CSysTime class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTIME_H__85C8D4FC_8AD1_49AC_B942_1584146C37E9__INCLUDED_)
#define AFX_SYSTIME_H__85C8D4FC_8AD1_49AC_B942_1584146C37E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CSysTime{
public:
	static SYSTEMTIME GetSysTime();
	static CString GetSysHour();
	static CString GetSysMin();
	static CString GetSysSec();
    static CString GetSysDate();

	static void GetSysTime( CString &strHour, CString &strMin, CString &strSec);
	static void GetSysTime( CString &strHourMin ); 
	static void GetSysDate( CString &strDate, CString &strHour, CString &strMin, CString &strSec); 

    
	static BOOL SetLocalTime( const SYSTEMTIME& time ); 
    static BOOL SetLocalTime(const CString strDay, const CString strMon, const CString strYear, const CString  strHour, const CString  strMin, const CString  strSec );
                               
	static BOOL IsDateValid( const CString cstrYear, const CString cstrMon, const CString cstrDay ,CString &strErrDescrip);

	static BOOL IsTiemValid( const CString  strHour, const CString  strMin, const CString  strSec,CString &strErrDescrip  );
 
 };
#endif // !defined(AFX_SYSTIME_H__85C8D4FC_8AD1_49AC_B942_1584146C37E9__INCLUDED_)
