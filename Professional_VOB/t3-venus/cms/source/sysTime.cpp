// sysTime.cpp: implementation of the CSysTime class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "sysTime.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SYSTEMTIME CSysTime::GetSysTime()
{
	SYSTEMTIME sysTime;
	::GetLocalTime( &sysTime );
	return sysTime;
}

CString CSysTime::GetSysHour()
{
	SYSTEMTIME sysTime = GetSysTime();
	CString strHour;
    strHour.Format("%d", sysTime.wHour ); 
	return strHour;	
}

CString CSysTime::GetSysMin()
{
	SYSTEMTIME sysTime = GetSysTime();
	CString strMin;
	 
	strMin.Format("%.2d", sysTime.wMinute);
	 
	return strMin;	
}

CString CSysTime::GetSysSec()
{
	SYSTEMTIME sysTime = GetSysTime();
	CString strSec;
    strSec.Format("%.2d", sysTime.wSecond);
	 
	
	return strSec;	
}

void CSysTime::GetSysTime( CString &strHour, CString &strMin, CString &strSec)
{
	SYSTEMTIME sysTime = GetSysTime();
 
	strHour.Format("%.2d", sysTime.wHour);
    strMin.Format("%.2d", sysTime.wMinute ); 
	strSec.Format("%.2d", sysTime.wSecond );
 

}
void CSysTime::GetSysTime( CString &strHorMin )
{   
    
	SYSTEMTIME sysTime = GetSysTime();
 
	strHorMin.Format("%.2d", sysTime.wHour );
 
	
	CString strMin;
    strMin.Format("%.2d", sysTime.wMinute );
 
	
// 	CString  strSec; 
// 	strSec.Format("%.2d", sysTime.wSecond );
 
  
	strHorMin = strHorMin + ":" + strMin ; //+  ":" + strSec;
 
}

void CSysTime::GetSysDate( CString &strDate, CString &strHour, CString &strMin, CString &strSec)
{
   SYSTEMTIME sysTime = GetSysTime();
   strDate.Format( "%.4d-%.2d-%.2d", sysTime.wYear, sysTime.wMonth, sysTime.wDay );
   strHour.Format("%.2d", sysTime.wHour);
   strMin.Format("%.2d", sysTime.wMinute);
   strSec.Format("%.2d", sysTime.wSecond);
 
}

CString CSysTime::GetSysDate()
{
	SYSTEMTIME sysTime = GetSysTime();
	CString strDate;
    strDate.Format( "%.4d.%.2d.%.2d", sysTime.wYear, sysTime.wMonth, sysTime.wDay );
	return strDate;
}

BOOL CSysTime::SetLocalTime( const SYSTEMTIME& time )
{
    BOOL bRet =  ::SetLocalTime(&time);
	return bRet;
}

BOOL CSysTime::SetLocalTime( const CString strDay, const CString strMon, const CString strYear, const CString  strHour, const CString  strMin, const CString  strSec )
{  
    CString strErr;
	if ( !IsDateValid( strYear, strMon,strDay ,strErr ) ) 
	{
		return FALSE;
	}
 
	if (  !IsTiemValid( strHour, strMin, strSec ,strErr) ) 
	{
		return FALSE;
	}

	SYSTEMTIME  time;
	memset( &time, 0 ,sizeof(time) ); 
	time.wMinute = atoi( strMin );  
	time.wHour= atoi( strHour );
 
	time.wDay= atoi( strDay );  
	time.wMonth= atoi( strMon ); 
	time.wYear= atoi( strYear );
	
    BOOL bRet = SetLocalTime(  time );
   return bRet; 
}

BOOL CSysTime::IsDateValid( const CString cstrYear, const CString cstrMon, const CString cstrDay,CString &strErrDescrip )
{  
    strErrDescrip.Empty();
	BOOL bRes = TRUE;
    //1.先判断当前年是不是闰年，非闰年二月左右28天，闰年29天  
	WORD wYear = 0;
	BOOL bLeap = FALSE;
 
	wYear = atoi( cstrYear );
	
	bLeap = ((( wYear % 4 == 0 ) && (wYear % 100 != 0)) || ( wYear % 400 == 0 ) );
	
	
	//2.判断月是不是二月
	 
	WORD wMonth = 1; 
	wMonth = atoi( cstrMon );
	
	if ( 2 == wMonth )
	{
		CString cstrErrMsg = ""; 
		WORD wDay = 1; 
		wDay = atoi( cstrDay );
		
		if ( bLeap )
		{
			//3.1 年份为闰年,29天
			if ( wDay > 29 )
			{
				
			    strErrDescrip.Format("%d年2月份的日期范围为1-29", wYear);
             //   TRACE(strErrDescrip);
				return FALSE;
			}
		}
		else
		{
			//3.2 年份非闰年,28天
			if ( wDay > 28 )
            {  
                strErrDescrip.Format("%d年2月份的日期范围为1-28", wYear); 
		//		TRACE(strErrDescrip); 
				return FALSE;
			}
		}
	}

	return TRUE;

}

 

BOOL CSysTime::IsTiemValid( const CString  strHour, const CString  strMin, const CString  strSec,CString &strErrDescrip )
{
    strErrDescrip.Empty();
    BOOL bRes = TRUE;
   
	WORD wTime = 1;
   
	wTime = atoi(strHour);
	if ( wTime <= 0  || wTime > 59 ) 
    {   
        strErrDescrip = "小时为0--59的整数";
		return FALSE;
	}

	wTime = atoi(strMin);
	if ( wTime < 0  || wTime > 59 ) 
    {  
        strErrDescrip = "分钟为0--59的整数";
		return FALSE;
	}

	wTime = atoi(strSec);
	if ( wTime < 0  || wTime > 59 ) 
	{
        strErrDescrip = "秒为0--59的整数";
		return FALSE;
	}

   return TRUE;
}