// errCodeManage.cpp: implementation of the CErrCodeManage class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "errCodeManage.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
MapErrtInfo CErrCodeManage::m_mapErrInfo ;
CErrCodeManage* CErrCodeManage::m_pErrManager = NULL;
CErrCodeManage::CErrCodeManage()
{
    Instance();
}

CErrCodeManage::~CErrCodeManage()
{

}

CErrCodeManage*CErrCodeManage::GetErrCodeManage()
{
    if ( m_pErrManager == NULL )
    {
        m_pErrManager = new CErrCodeManage;
	}

    return m_pErrManager;
}

void CErrCodeManage::Instance()
{    
    AddErr(NO_ERROR,"操作成功"); 

    //登录相关 
    AddErr(ERR_UMC_LOGIN_FAIL,"登录失败");
    AddErr(ERR_UMC_LOGIN_UMS_USER_ERR,"登录失败: 用户名错误");
    AddErr(ERR_UMC_LOGIN_UMS_PSWD_ERR,"登录失败: 密码错误");
    AddErr(ERR_UMC_LOGIN_UMS_MAX_LOGIN,"登录失败: 达到用户登录上限");
    AddErr(ERR_UMC_LOGIN_UMS_LOGED,"登录失败: 用户已经登录");
    AddErr(ERR_UMC_LOGIN_UMS_SYSINITING,"登录失败: 系统正在准备");
       
    AddErr(ERR_CMS_UI_UMS_LOGIN,"登录服务器失败(UMS)");
    AddErr(ERR_CMS_UI_CNS_LOGIN,"登录服务器失败(CNS)");

    AddErr(ERR_CNC_TCPCONNECT,"登录失败: 网络连接失败");
    AddErr(ERR_UMC_CREATE_TCP_FAIL,"登录服务器失败: 建立连接失败(UMS)");
    
    AddErr(ERR_CNC_ACTIVE_CONNECT,"登录服务器失败: 已经登录(CNS)");
    AddErr(ERR_UMC_ACTIVE_CONNECTION,"登录服务器失败: 已经登录(ums)");  

    //开会
    AddErr(ERR_UMC_STARTCONF_CONFTEMP_UNKNOW_ERR,"开启会议失败"); //2012-8-7 SE石文娟确认未知错误不做提示 by yjj
    AddErr(ERR_UMC_STARTCONF_CONFTEMP_UNEXIST,"开启会议失败: 会议模板不存在");
    AddErr(ERR_UMC_STARTCONF_CONF_FULL,"开启会议失败: 会议已满");
    AddErr(ERR_UMC_STARTCONF_CONF_EXIST,"开启会议失败: 会议已存在");
    AddErr(ERR_UMC_CALLCNS_HUNGUP,"本地挂断");
    AddErr(ERR_CMS_CALLCNS_UNREACHABLE,"对端不可达");
    AddErr(ERR_UMC_CALLCNS_RESOURCE_FULL,"已达到会场最大接入数");
    AddErr(ERR_UMC_CALLCNS_DST_NOT_FOUND,"对端不存在");
    AddErr(ERR_UMC_CALLCNS_BUSY,"对端忙");
    AddErr(ERR_CMS_CALLCNS_NO_CONF,"会议不存在");
    AddErr(ERR_UMC_CALLCNS_CNS_EXIST,"对端已在本会议中");
    AddErr(ERR_UMC_CALLCNS_LOCAL,"本地原因");
	AddErr(ERR_UMC_CALLCNS_CNS_REJECTED,"对端拒绝");
	AddErr(ERR_UMC_CALLCNS_CNS_PEERHUNGUP,"对端挂断");
	AddErr(ERR_UMC_CALLCNS_CNS_ABNORMAL,"本地掉线挂断");
	AddErr(ERR_UMC_CALLCNS_CNS_PEERABNORMAL,"对端掉线挂断");
	AddErr(ERR_UMC_CALLCNS_CNS_CONFOVER,"会议结束");
	AddErr(ERR_UMC_CALLCNS_CNS_CALLEXCEPTION,"接入模块掉线");
	AddErr(ERR_UMC_CALLCNS_CNS_CONFEXIST,"会议已存在");
	AddErr(ERR_UMC_CALLCNS_CNS_UNKNOWN,"未知原因");
	
    AddErr(ERR_UMC_HUNGUP_CONF_UNEXIST,"结束会议失败: 会议不存在");

    //添加会议模板中 相关
    AddErr(ERR_CMS_CONFTEMP_E164_REPEAT,"操作失败: 会议的E164不可重复");
    AddErr(ERR_CMS_CONFTEMP_ALIARS_REPEAT,"操作失败: 会议名称不可重复");
    AddErr(ERR_CMS_CONFTEMP_ALIARS_EMPTY,"操作失败: 会议名称不可为空");
    AddErr(ERR_CMS_CNS_ALIARS_EMPTY,"操作失败: 会场别名不可为空");
    AddErr(ERR_CMS_CNS_MAX_NUM,"操作失败: 该模板中的会场列表已满");
    AddErr(ERR_CMS_CNS_ALIAS_EXIST,"操作失败: 会议模板中已存在该会场");
    AddErr(ERR_CMS_CNSID_INVALID,"操作失败：会场ID非法"); //,ERR_CMS_CNSID_INVALID); 
    AddErr(ERR_CMS_CNS_UNKNOW,"操作失败： 未知会场"); //,ERR_CMS_CNS_UNKNOW); 
    AddErr(ERR_CMS_CNS_UNEXIST,"操作失败： 该会场不存在"); 
   
   //会议模板开会相关 
    AddErr(ERR_CMS_CONFTEMP_UNEXIST,"操作失败： 会议模板不存在"); 
    AddErr(ERR_CMS_TEMPLATE_CHAIRMAN_NOT_LOCAL_CNS,"操作失败： 会议模板中的主席不是本地会场"); 
   
    AddErr(ERR_CMS_UI_NAME_REPEAT,"操作失败： 用户名不可重复"); 
    AddErr(ERR_CMS_UI_E164_REPEAT,"操作失败： E164号不可存在");
    
    //用户相关
    AddErr(ERR_CMS_OPERATE_USER_FAIL,"操作用户失败");

}

CString CErrCodeManage::GetErrString( DWORD dwErrId )
{
    MapErrtInfo::iterator it =  m_mapErrInfo.find(dwErrId);
    if ( it != m_mapErrInfo.end() )
    {
        return it->second;
    }
    
    return "";//"未知错误";2012-8-7 SE石文娟确认未知错误不做提示 by yjj
}


void CErrCodeManage::AddErr( DWORD dwErrId, char * format,... )
{  
    va_list arg_ptr;  
    char szBuffer[300] = { 0 };
    
    va_start(arg_ptr, format);  
    _vsntprintf ( szBuffer, sizeof (szBuffer) / sizeof (TCHAR),format, arg_ptr) ;  
    va_end(arg_ptr);  
    
    int n = strlen(szBuffer);
    szBuffer[n] = '\0';  
    CString strErr;
    strErr.Format("%s",szBuffer);
   // TRACE("\n[ CErrCodeManage::AddErr] errCode = %ld, string = %s\n",dwErrId,szBuffer);
    m_mapErrInfo.insert(MapErrtInfo::value_type(dwErrId,strErr));
}
