// Logger.h: interface for the CLogger class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGGER_H__92014A36_F08C_449C_B1BA_06B0ECCFF45D__INCLUDED_)
#define AFX_LOGGER_H__92014A36_F08C_449C_B1BA_06B0ECCFF45D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "templateClass.h"
namespace AutoUIFactory
{

enum LogLevel
{
	Errors,
		Warnings,
		Standard,
		Informative,
		Insane			
};




/*---------------------------------------------------------------------
* ��	����CLogger
* ��    �ܣ���ӡ��
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/05/11	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
class ILogger : public Singleton<ILogger>
{
 
public:
	virtual bool LogEvent( String strEvent, LogLevel emLoglv = Standard ) = 0;
	
	
	bool LogEvent(  LogLevel emLoglv , char* format,... ) 
	{    
		//��ӡ��Ϣ��
		va_list arg_ptr;  
		char szBuffer[300] = { 0 };
		
		va_start(arg_ptr, format);  
		_vsntprintf ( szBuffer, sizeof (szBuffer) / sizeof (TCHAR),format, arg_ptr) ; 
		
		va_end(arg_ptr);  
		
		size_t n = strlen(szBuffer);
		szBuffer[n] = '\0';
 
		TRACE( szBuffer );
 

		return true;
	}

	ILogger(){ }
	virtual ~ILogger()
	{
 
 
		
	}
	
    
};

 

#define LOGEVENT( message ) \
	String strMsg = message; \
	String strCodeInfo; \
    char buff[128] = {0 }; \
	_snprintf(buff, sizeof (buff), "\n filepath=%s line=%d \n",__FILE__,__LINE__); \
	strMsg += buff; \
    ILogger::GetSingletonPtr()->LogEvent(strMsg,Insane); 
} // namespace AutoUIFactory end
#endif // !defined(AFX_LOGGER_H__92014A36_F08C_449C_B1BA_06B0ECCFF45D__INCLUDED_)
