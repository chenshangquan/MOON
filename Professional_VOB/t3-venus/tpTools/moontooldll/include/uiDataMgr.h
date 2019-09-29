// uiDataMgr.h: interface for the CUIDataMgr class.

/*****************************************************************************
ģ����      : ������صĹ������ݹ���ģ��
�ļ���      : uiDataMgr.h
����ļ�    : ���д�����ص�ȫ������Ӧ����ڴ˴�
�ļ�ʵ�ֹ���: ������������
����        : ���`�`
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2014/11/28     1.0         ���`�`      ����
******************************************************************************/


#if !defined(AFX_UIDATAMGR_H__C2E44322_FA60_408C_972F_0701D85D461C__INCLUDED_)
#define AFX_UIDATAMGR_H__C2E44322_FA60_408C_972F_0701D85D461C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "templateClass.h"
class CUIDataMgr:public ISingleTon<CUIDataMgr> 
{
public:
	CUIDataMgr();
	virtual ~CUIDataMgr();

	/*---------------------------------------------------------------------
	* ��    �ܣ����ⲿ���ڷ���֪ͨ
	* ���������
	* ���������
	* �� �� ֵ������FALSE����ʧ��
	* ��    ע��  
	* ����			�汾		�޸���		�޸ļ�¼
	* 2012.12.13    1.0         �����        ����
	----------------------------------------------------------------------*/
	 BOOL NotifyOuterWnd( UINT nMsg , WPARAM wparam, LPARAM lparam );
	/*=============================================================================
    �� �� ��:IsFileExist
    ��    ��:����ļ��Ƿ����
    ��    ��:const CString& strFileFullPath    [in]     �ļ�ȫ·������
    ע    ��:��
    �� �� ֵ:TRUE: �ɹ�   FALSE:ʧ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/12/14  1.0     ����ӡ    ����
    =============================================================================*/
	 BOOL IsFileExist(const CString& strFileFullPath);

	/*=============================================================================
    �� �� ��:IsFolderExist
    ��    ��:���Ŀ¼�Ƿ����
    ��    ��:const CString& strFolderFullPath    [in]     Ŀ¼ȫ·������
    ע    ��:��
    �� �� ֵ:TRUE: �ɹ�   FALSE:ʧ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/12/14  1.0     ����ӡ    ����
    =============================================================================*/
	 BOOL IsFolderExist(const CString& strFolderFullPath);

	/*=============================================================================
    �� �� ��:IsIniFile
    ��    ��:����Ƿ���ini�ļ����ڻ���ģ��͵�ַ�ļ����
    ��    ��:const String& strFileName    [in]     �ļ�ȫ·������
    ע    ��:��
    �� �� ֵ:TRUE: �ɹ�   FALSE:ʧ��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/12/14  1.0     ����ӡ    ����
    =============================================================================*/
	 BOOL IsIniFile(const String& strFileName);

	/*=============================================================================
    �� �� ��:GetIpStr
    ��    ��:����ͨ����ת��ΪIP��
    ��    ��:unsigned int dwIPAddr    [in]     IP�����ͱ�ʾ��ʽ
    ע    ��:��
    �� �� ֵ:���ơ�127.0.0.1����ʽ
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���    �޸�����
    2012/12/14  1.0     ����ӡ    ����
    =============================================================================*/
	 CString GetIpStr(unsigned int dwIPAddr);

	/*=============================================================================
    �� �� ��: GetFileFolderPath
    ��    ��: �õ��ļ������ļ���·����
    ��    ��: const String& strFilePath        [in]    �ļ�ȫ·����
    ע    ��:��
    �� �� ֵ:String     �ļ������ļ���·����
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2013/01/28  1.0     ����ӡ    ����
    =============================================================================*/
	 String GetFileFolderPath(const String& strFilePath);

	/*=============================================================================
    �� �� ��: OpenBrowseForFolder
    ��    ��: ������ļ�Ŀ¼��Ӧ�����ļ����桢���ء������ȣ�
    ��    ��: const String& strFileName        [in]    �ļ���
	��    ��: HWND hWnd                        [in]    ��Ϊģ̬�Ի���hWndΪ�����ھ��   by xhx
    ��    ��: BOOL bIsAddFileName              [in]    �Ƿ񸽼��ļ���   FALSE��ֱ�ӵõ�Ŀ¼��
    ע    ��:��
    �� �� ֵ:String     �ļ�ȫ·��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2013/01/28  1.0     ����ӡ    ����
    =============================================================================*/
	 String OpenBrowseForFolder(const String& strFileName, HWND hWnd = NULL, BOOL bIsAddFileName = TRUE );

	/*=============================================================================
    �� �� ��: OpenFileDialog
    ��    ��: ���ļ�Ŀ¼��Ӧ�����ļ�����Ϊ�����롢�򿪵ȣ�
    ��    ��: const String& strFilter			  [in]    �����ļ�
    ��    ��: const String& strDefFileName        [in]    Ĭ����ʾ�ļ���
    ��    ��: const String& strFilePathName       [out]    �ļ�ȫ·��
    ��    ��: String strFileName				  [out]    �ļ���
    ��    ��: BOOL bOpenStyle					  [in]    ������������Ǳ���
    ע    ��:��
    �� �� ֵ:String     �ļ�ȫ·��
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2013/01/28  1.0     ����ӡ    ����
    =============================================================================*/
	 BOOL OpenFileDialog( const String& strFilter, const String& strDefFileName, String& strFilePathName,
		 String& strFileName, BOOL bOpenStyle = TRUE );

	/*=============================================================================
    �� �� ��: CheckTransferFile
    ��    ��: ��⴫��ȫ·�����ļ����ĺϷ���
    ��    ��: const String strFileFullPath    [in]     �������ļ�ȫ·��
    ��    ��: const String strCheckFileName   [in]     �������ļ��� 
    ע    ��:��
    �� �� ֵ:BOOL
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2013/01/28  1.0     ����ӡ    ����
    =============================================================================*/
	 BOOL CheckTransferFile( const String& strFileFullPath, const String& strCheckFileName );

	/*=============================================================================
    �� �� ��: GetFileSize
    ��    ��: �õ��ļ���С
    ��    ��: const String strFilePath    [in]     �ļ�ȫ·��
    ע    ��:��
    �� �� ֵ:u64 �ֽ���
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2013/02/01  1.0     ����ӡ    ����
    =============================================================================*/
	 u64 GetFileSize( const String& strFilePath );
 
	/*=============================================================================
    �� �� ��: RecusionMkDir
    ��    ��: �ݹ鴴��Ŀ¼�� ���Ŀ¼�Ѿ����ڻ��ߴ����ɹ�����TRUE
    ��    ��: CString strFolder        [in]    �������ļ���·��
    ע    ��:��
    �� �� ֵ:BOOL
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2013/01/28  1.0     ����ӡ    ����
    =============================================================================*/
	 BOOL RecusionMkDir(CString strFolder);

	/*=============================================================================
    �� �� ��:SetLstSelItem
    ��    ��: �����б��ؼ���ѡ���У�Ĭ��ȥ��ѡ���
    ��    ��: const String& strLstWnd        [in]    �б���
	��    ��: IWndTree* pWndTree		     [in]    ��������
	��    ��: s32 nItemNo					 [in]    ѡ���к�
    ע    ��:��
    �� �� ֵ:BOOL
    -------------------------------------------------------------------------------
    �޸ļ�¼:
    ��      ��  �汾    �޸���  �޸�����
    2013/01/17  1.0     ����ӡ    ����
    =============================================================================*/
	 void SetLstSelItem( const String& strLstWnd, IWndTree* pWndTree = NULL, s32 nItemNo = -1 );

private:
	

};

#define  UIDATAMGR_PTR CUIDataMgr::GetSingletonPtr()

//��Ҫ������Ϣ
extern const  string g_stcMsgboxDlg;		//��ʾ������
extern const  string g_strMoonMainFrame;	//moonTool ������		
extern const  string g_strCamCtrlDlg;		//������Ϣ����
extern const  string g_strMoonAdjustDlg; //ƴ�ӵ�������
extern const  string g_strSysCfgDlg;        //ϵͳ�����ý���	
extern const  string g_strOrderListDlg;	
extern const  string g_strCfgFrame;			//���ÿ��
extern const  string g_strCfgCnsDlg;		//���ÿ���е�cns����
extern const  string g_strCfgAudioPort;		//���ÿ���е���Ƶ���ý���
extern const  string g_strCfgMixDlg;		//���ÿ���еĻ������ý���
extern const  string g_strDiagInfoDlg;		//��Ͻ���
extern const  string g_strWarningDlg;
extern const  string g_stcStrExpCommonDlg;
extern const  string g_stcStrImpCommonDlg;
extern const  string g_stcStrOrderPosInfoDlg;
extern const  string g_stcStrSetContrastAreaDlg;
extern const  string g_stcStrCorrectParamDlg;
//��Ҫ����
extern const  string g_strShmShow ; //��ʾ����, ���е��ø÷����Ĵ�����Ҫ��xml�ķ���������Ϊ "SchmShow" 
extern const  string g_strShmHide ; //���ط���, ���е��ø÷����Ĵ�����Ҫ��xml�ķ���������Ϊ "SchmHide"

#define  ADDRBOOK_FILE_PATH         "/usr/conf/"
#define  ADDRBOOK_FILE_NAME		    "kdvaddrbook.kdv"
#define  CNSLOG_FILE_PATH			"/usr/kdvlog/log/"
#define  CNSLOG_FILE_NAME			"cnlog.ini"
#define  CNSCONFIG_FILE_PATH		"/usr/conf/"
#define  CNSCONFIG_FILE_NAME		"cncfg.ini"
#define  CNSCONF_FILE_PATH			"/usr/bin/"				
#define  CNSUPGRADE_FILE_NAME		"tpcns.bin"
#define  MOONCAMERA_FILE_PATH		"/usr/conf/"
#define  MOONCAMERA_FILE_NAME		"mooncfg.ini"
#define	 MoonTool_SNAPSHOT_PATH         "/usr/snapshot/"
#define  MOONSNAPSHOT_FILE_PATH		     "download"
#define  MOONSNAPSHOT_FILE_NAME1		"snapshot0.jpg"
#define  MOONSNAPSHOT_FILE_NAME2		"snapshot1.jpg"
#define  MOONSNAPSHOT_FILE_NAME3		"snapshot2.jpg"
#define  MOONPRESET_SNAPSHOT            "cam%d_%d.jpg"
#define  MOONPRESET_SNAPSHOT1           "tempcam%d_%d.jpg"

#endif // !defined(AFX_UIDATAMGR_H__C2E44322_FA60_408C_972F_0701D85D461C__INCLUDED_)