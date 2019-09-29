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
    AddErr(NO_ERROR,"�����ɹ�"); 

    //��¼��� 
    AddErr(ERR_UMC_LOGIN_FAIL,"��¼ʧ��");
    AddErr(ERR_UMC_LOGIN_UMS_USER_ERR,"��¼ʧ��: �û�������");
    AddErr(ERR_UMC_LOGIN_UMS_PSWD_ERR,"��¼ʧ��: �������");
    AddErr(ERR_UMC_LOGIN_UMS_MAX_LOGIN,"��¼ʧ��: �ﵽ�û���¼����");
    AddErr(ERR_UMC_LOGIN_UMS_LOGED,"��¼ʧ��: �û��Ѿ���¼");
    AddErr(ERR_UMC_LOGIN_UMS_SYSINITING,"��¼ʧ��: ϵͳ����׼��");
       
    AddErr(ERR_CMS_UI_UMS_LOGIN,"��¼������ʧ��(UMS)");
    AddErr(ERR_CMS_UI_CNS_LOGIN,"��¼������ʧ��(CNS)");

    AddErr(ERR_CNC_TCPCONNECT,"��¼ʧ��: ��������ʧ��");
    AddErr(ERR_UMC_CREATE_TCP_FAIL,"��¼������ʧ��: ��������ʧ��(UMS)");
    
    AddErr(ERR_CNC_ACTIVE_CONNECT,"��¼������ʧ��: �Ѿ���¼(CNS)");
    AddErr(ERR_UMC_ACTIVE_CONNECTION,"��¼������ʧ��: �Ѿ���¼(ums)");  

    //����
    AddErr(ERR_UMC_STARTCONF_CONFTEMP_UNKNOW_ERR,"��������ʧ��"); //2012-8-7 SEʯ�ľ�ȷ��δ֪��������ʾ by yjj
    AddErr(ERR_UMC_STARTCONF_CONFTEMP_UNEXIST,"��������ʧ��: ����ģ�岻����");
    AddErr(ERR_UMC_STARTCONF_CONF_FULL,"��������ʧ��: ��������");
    AddErr(ERR_UMC_STARTCONF_CONF_EXIST,"��������ʧ��: �����Ѵ���");
    AddErr(ERR_UMC_CALLCNS_HUNGUP,"���عҶ�");
    AddErr(ERR_CMS_CALLCNS_UNREACHABLE,"�Զ˲��ɴ�");
    AddErr(ERR_UMC_CALLCNS_RESOURCE_FULL,"�Ѵﵽ�᳡��������");
    AddErr(ERR_UMC_CALLCNS_DST_NOT_FOUND,"�Զ˲�����");
    AddErr(ERR_UMC_CALLCNS_BUSY,"�Զ�æ");
    AddErr(ERR_CMS_CALLCNS_NO_CONF,"���鲻����");
    AddErr(ERR_UMC_CALLCNS_CNS_EXIST,"�Զ����ڱ�������");
    AddErr(ERR_UMC_CALLCNS_LOCAL,"����ԭ��");
	AddErr(ERR_UMC_CALLCNS_CNS_REJECTED,"�Զ˾ܾ�");
	AddErr(ERR_UMC_CALLCNS_CNS_PEERHUNGUP,"�Զ˹Ҷ�");
	AddErr(ERR_UMC_CALLCNS_CNS_ABNORMAL,"���ص��߹Ҷ�");
	AddErr(ERR_UMC_CALLCNS_CNS_PEERABNORMAL,"�Զ˵��߹Ҷ�");
	AddErr(ERR_UMC_CALLCNS_CNS_CONFOVER,"�������");
	AddErr(ERR_UMC_CALLCNS_CNS_CALLEXCEPTION,"����ģ�����");
	AddErr(ERR_UMC_CALLCNS_CNS_CONFEXIST,"�����Ѵ���");
	AddErr(ERR_UMC_CALLCNS_CNS_UNKNOWN,"δ֪ԭ��");
	
    AddErr(ERR_UMC_HUNGUP_CONF_UNEXIST,"��������ʧ��: ���鲻����");

    //��ӻ���ģ���� ���
    AddErr(ERR_CMS_CONFTEMP_E164_REPEAT,"����ʧ��: �����E164�����ظ�");
    AddErr(ERR_CMS_CONFTEMP_ALIARS_REPEAT,"����ʧ��: �������Ʋ����ظ�");
    AddErr(ERR_CMS_CONFTEMP_ALIARS_EMPTY,"����ʧ��: �������Ʋ���Ϊ��");
    AddErr(ERR_CMS_CNS_ALIARS_EMPTY,"����ʧ��: �᳡��������Ϊ��");
    AddErr(ERR_CMS_CNS_MAX_NUM,"����ʧ��: ��ģ���еĻ᳡�б�����");
    AddErr(ERR_CMS_CNS_ALIAS_EXIST,"����ʧ��: ����ģ�����Ѵ��ڸû᳡");
    AddErr(ERR_CMS_CNSID_INVALID,"����ʧ�ܣ��᳡ID�Ƿ�"); //,ERR_CMS_CNSID_INVALID); 
    AddErr(ERR_CMS_CNS_UNKNOW,"����ʧ�ܣ� δ֪�᳡"); //,ERR_CMS_CNS_UNKNOW); 
    AddErr(ERR_CMS_CNS_UNEXIST,"����ʧ�ܣ� �û᳡������"); 
   
   //����ģ�忪����� 
    AddErr(ERR_CMS_CONFTEMP_UNEXIST,"����ʧ�ܣ� ����ģ�岻����"); 
    AddErr(ERR_CMS_TEMPLATE_CHAIRMAN_NOT_LOCAL_CNS,"����ʧ�ܣ� ����ģ���е���ϯ���Ǳ��ػ᳡"); 
   
    AddErr(ERR_CMS_UI_NAME_REPEAT,"����ʧ�ܣ� �û��������ظ�"); 
    AddErr(ERR_CMS_UI_E164_REPEAT,"����ʧ�ܣ� E164�Ų��ɴ���");
    
    //�û����
    AddErr(ERR_CMS_OPERATE_USER_FAIL,"�����û�ʧ��");

}

CString CErrCodeManage::GetErrString( DWORD dwErrId )
{
    MapErrtInfo::iterator it =  m_mapErrInfo.find(dwErrId);
    if ( it != m_mapErrInfo.end() )
    {
        return it->second;
    }
    
    return "";//"δ֪����";2012-8-7 SEʯ�ľ�ȷ��δ֪��������ʾ by yjj
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
