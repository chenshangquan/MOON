/*****************************************************************************
ģ����      : globaldef
�ļ���      : globaldef.h
����ļ�    : 
�ļ�ʵ�ֹ���: umstoolȫ�������ļ�
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/10/30     1.0         ����ӡ      ����
******************************************************************************/
#ifndef GLOBALDEF_H 
#define GLOBALDEF_H

#pragma warning( disable : 4786 )	// ��ʶ�����Ƴ���255�ֽ�
#pragma warning( disable : 4067 )
#pragma warning( disable : 4129 )
#pragma warning( disable : 4503 )
#pragma warning( disable : 4800 )


#include "uiexhead.h"
#include "UifactoryHeader.h"
//10-common
#include "kdvType.h"		// ��������
#include "evCmsLib.h"

#pragma warning( disable : 4786 )
#include <afxtempl.h>
#include <afxole.h>
#include <afxdtctl.h>
#include <map>
#include <vector>

#include "msgIddispatch.h"
#define iterator _iterator

#include <string>
using namespace std;
//typedef string String;
#include "templateClass.h"
using namespace AutoUIFactory;

#ifndef   ULONG_PTR   
#define   ULONG_PTR   unsigned   long*   
#endif

//#include <gdiplus.h>   //���������error C2955: 'map' : use of class template requires template argument list
#ifdef _MFC_VER
#include <afx.h>
#endif
#undef iterator

//70-common

#include "cmsConst.h"
#include "tperrno.h"
#include "umclib.h"
#include "tpmsginit.h"
#include "ftpctrl.h"       //ftp����ģ��   ��NmsCommon����lib���а���

#include <algorithm>
#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <set>
using namespace std;

//windows ��
#include "Shlwapi.h"
#pragma comment(lib, "Shlwapi.lib")
#pragma comment(lib, "wininet.lib")

enum EM_FTPTRANS_TYPE      //�ļ�����򵼳�����
{
	em_FTPTRANS_IMPORT,
	em_FTPTRANS_EXPORT,
};

enum EM_BOARDOPT_TYPE      //���Ӳ�������
{
	em_BOARDOPT_ADD,
	em_BOARDOPT_MODIFY,
	em_TVWBOARDOPT_ADD,
	em_TVWBOARDOPT_MODIFY,
};

enum UMSTOOLMSG
{
	em_UMSTOOL_LOGINRESULT = UMSTOOL_MSG_BEGIN + 0x01,
#define WM_UMSTOOL_FTPLOGPROGRESS em_TPTOOL_LOGINRESULT      //��־���ؽ������� wparam:����ֵ
		
		em_UMSTOOL_FTPTEMPLATEPROGRESS,
#define WM_UMSTOOL_FTPTEMPLATEPROGRESS em_UMSTOOL_FTPTEMPLATEPROGRESS      //����ģ�嵼�뵼���������� wparam:����ֵ
		
		em_UMSTOOL_FTPADDRBOOKPROGRESS,
#define WM_UMSTOOL_FTPADDRBOOKPROGRESS em_UMSTOOL_FTPADDRBOOKPROGRESS      //��ַ�����뵼���������� wparam:����ֵ


};

enum EM_NETMNGOPT_TYPE      //���ܲ�������
{
	em_NETMNGOPT_ADD,
	em_NETMNGOPT_MODIFY,
};

#define  UMSLOG_FILE_NAME			"umslog.ini"
#define  AUTH_FILE_NAME_EXP			"license.ini"
#define  AUTH_FILE_NAME_IMP			"kedalicense.key"
#define  UMSCONFIG_FILE_NAME		"umscfg.ini"
#define  TEMPLATE_FILE_NAME			"template_down.conf"
#define  ADDRBOOK_FILE_NAME		    "kdvaddrbook.kdv"
#define  BOARDUPGRADE_FILE_NAME		"boardupgrade.ini"

#define BOARD_IS22_NAME				"ums-tp.bin"
#define BOARD_EAPU_NAME				"kdvapu2.bin"
#define BOARD_MPC2_NAME				"mpc-tp.bin"
#define BOARD_CRI2_SIP_NAME			"sip-tp.bin"
#define BOARD_CRI2_DSU_NAME			"dsu-tp.bin"
#define BOARD_MPU2_VMP_NAME			"kdvmpu2.bin"
#define BOARD_MPU2_BAS_NAME			"kdvmpu2.bin"
#define BOARD_TVW_NAME				"kdvhdu2.bin"

#define  UMSLOG_FILE_PATH			"/usr/conf/"
#define  AUTH_FILE_PATH				"/usr/conf/"
#define  UMSCONFIG_FILE_PATH		"/usr/conf/"
#define  TEMPLATE_FILE_PATH			"/ramdisk/"
#define  ADDRBOOK_FILE_PATH			"/usr/conf/"
#define  BOARDUPGRADE_FILE_PATH		"/ramdisk/"

#define UMSTOOLEXCEPTION_FILE _T("umsToolExcep.log")

//////////////////////////////ui logic///////////////////////////////////////////
#define  SYSTEM_UMSTOOL_XML "resumstool\\umstoolsystem.xml"
const String g_stcStrMainFrmDlg				= "TPMainDlg";				//popup����
const String g_stcStrSysinfoDlg				= "SysInfoDlg";				//ϵͳ������Ϣ����
const String g_stcStrCorrelativeCfgDlg		= "CorrelativeCfgDlg";      //������ý���
const String g_stcStrAddrbookExpDlg			= "AddrbookExpDlg";			//������ַ������
const String g_stcStrTemplateExpDlg			= "TemplateExpDlg";			//��������ģ�����
const String g_stcStrBoardCfgDlg			= "BoardCfgDlg";			//�������ý���
const String g_stcStrUmsCfgDlg				= "UmsCfgDlg";				//Ums���ý���
const String g_stcStrBoardOptDlg			= "BoardOptDlg";			//Ums��������޸Ľ���
const String g_stcMsgboxDlg					= "MsgboxDlg";				//msgbox��Ϣ��ʾ��
const String g_stcStrTvwBoardCfgDlg			= "TvwBoardCfgDlg";			//����ǽ�������ý���
const String g_stcStrNetMngCfgDlg			= "NetMngCfgDlg";			//�������ý���
const String g_stcStrNetMngOptDlg			= "NetMngOptDlg";			//��������޸Ľ���
const String g_stcStrTvwStyleCfgDlg			= "TvwStyleCfgDlg";			//����ǽԤ������
const String g_stcStrTvwStyleListMenuDlg    = "TvwStyleCfgDlg/TvwStyleListMenuDlg";		//����ǽԤ���˵�WS_POPUP
const String g_stcStrTvwStyleOptDlg			= "TvwStyleOptDlg";			//����ǽԤ�����ý���
const String g_stcStrImpCommonDlg			= "ImpCommonDlg";			//�ϴ������룩ͨ�õ�������  �磺��Ȩ���롢������ؽ���   ���������ͬ  ͨ����������
const String g_stcStrExpCommonDlg			= "ExpCommonDlg";			//���أ�������ͨ�õ�������  �磺��Ȩ������������־����  ���������ͬ  ͨ����������
const String g_stcStrVTRCfgDlg				= "VTRCfgDlg";				//¼������ý���
const String g_stcStrVTROptDlg				= "VTROptDlg";				//¼�������޸Ľ���
const String g_stcWaringDlg					= "WarningDlg";				//��Ϣ��ʾ����
const String g_stcStrBackupCfgDlg			= "BackupCfgDlg";			//1+1�������ý���

//umstoollib����
#include "exceptioncatch.h"

#include "MsgDispatch.h"
#include "msghandle.h"
#include "commonmgrif.h"
#include "datamgrimp.h"
#include "sessionins.h"
#include "umstoolcommon.h"

#include "logicmanage.h"
#include "uifactorylib.h"
#include "touchlistdataproperty.h"


#endif