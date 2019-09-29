// DefaultLogger.h: interface for the CDefaultLogger class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEFAULTLOGGER_H__D26DFC6F_AA2E_4055_8F28_D4FBB700469E__INCLUDED_)
#define AFX_DEFAULTLOGGER_H__D26DFC6F_AA2E_4055_8F28_D4FBB700469E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Logger.h"
namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* ��	����CDefaultLogger
* ��    �ܣ�Ĭ�ϵ�һ����ӡ��
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/06/02	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
class CDefaultLogger : public ILogger
{
public:
	CDefaultLogger();
	virtual ~CDefaultLogger();
	virtual bool LogEvent( String strEvent, LogLevel emLoglv = Standard );
	//virtual bool LogEvent( LogLevel emLoglv , char* format,...  );
	CFile m_file;
};
} // namespace AutoUIFactory end
#endif // !defined(AFX_DEFAULTLOGGER_H__D26DFC6F_AA2E_4055_8F28_D4FBB700469E__INCLUDED_)
