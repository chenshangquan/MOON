/*****************************************************************************
�ļ�ʵ�ֹ���: ����dlgName�����Ӧ�Ĳ���xml��logic���ӳ���ϵ�� ���Ѿ���������dlgָ��
�ļ���      : dlgMap.h 
����ļ�    : UIlib.h DUIDialog.h 
��ע		: ��ȡdlgMap.xml
����        : �����
�汾        : V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/4/18      1.0         �����      ����
******************************************************************************/

#pragma once
#include "DUIDialog.h"
#include<map>
namespace DuiLib {

#define PARENT_NAME_LEN 40

class UILIB_API CDlgManager:public ISingleTon<CDlgManager>
{
public:
	/*****************************************************************************
	* ����: ����szDlgMapXml�ļ������Ѷ�Ӧ�����Զ��洢��m_dlgMap
	* @param [in]  szDlgMapXml  ��Ӧ��dlgMap�ļ�
	* @return    
	* @remarks	 
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2013/4/18       1.0         �����      ����
    ******************************************************************************/  
	BOOL InitDlgMap( const LPCTSTR szDlgMapXml );


	/*****************************************************************************
	* ����: ����dlg�����Ҷ�Ӧ��dlg
	* @param [in]  szDlgName  dlg��
	* @return   �ɹ����� szDlgName��Ӧ��CDUIDialog*;ʧ�ܷ��� NULL
	* @remarks	��δ�������򴴽�����
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2013/4/18       1.0         �����      ����
    ******************************************************************************/
	CDUIDialog* FindDlgByName( const LPCTSTR szDlgName );



	/*****************************************************************************
	* ����: domodalĳ��dlg
	* @param [in]  szDlgMapXml  ��Ӧ��dlgMap�ļ�
	* @return    
	* @remarks	 
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2013/4/18       1.0         �����      ����
    ******************************************************************************/  
	int DoModal( const LPCTSTR szDlgMapXml );


	/*****************************************************************************
	* ����:����ĳ��dlg��ģʽ״̬
	* @param [in]  szDlgMapXml  ��Ӧ��dlgMap�ļ�
	* @param [in]  nResult   DoModal  �ķ���ֵ
	* @return    
	* @remarks	 
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2013/4/18       1.0         �����      ����
    ******************************************************************************/  
	void EndModal( const LPCTSTR szDlgMapXml, int nResult );


	/*****************************************************************************
	* ����: �ر�dlg
	* @param [in]  szDlgName ��Ӧ��dlg��
	* @return   �ɹ�����  TRUE��ʧ�ܷ���FALSE
	* @remarks	 
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2013/5/2       1.0         �����      ����
    ******************************************************************************/ 
	BOOL CloseDlg( const LPCTSTR szDlgName);


	/*****************************************************************************
	* ����: ���÷���
	* @param [in]  szCaseName  ��������szDlgName ��Ӧ��dlg��
	* @return   �ɹ�����  TRUE��ʧ�ܷ���FALSE
	* @remarks	��δ�������򴴽�����
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2013/5/2       1.0         �����      ����
    ******************************************************************************/
	BOOL DoCase( const LPCTSTR szCaseName, const LPCTSTR szDlgName );


public:
	CDlgManager();
	~CDlgManager(void);
private:
	 

	typedef struct
	{
		DWORD dwStyle  ;
		DWORD dwExStyle ;
		TCHAR tcParent[PARENT_NAME_LEN];
		BOOL bAuotHide ;
		TCHAR tcLayoutFile[MAX_PATH];
	}TDlgAttrib;
	 

	

	//����dlgName����dlg
	CDUIDialog* CreateDlgByName(  const LPCTSTR szDlgName  ); 

	//����dlgName ���Ҷ�Ӧ��dlg����
	TDlgAttrib* FindElementByDlgName( const LPCTSTR szDlgName );

private:
	 
	typedef std::map<tString/*CStdString*/,TDlgAttrib> DLGMAP;       
	typedef std::map<tString/*CStdString*/,CDUIDialog*> LIVEDLGMAP;
	  

	DLGMAP m_dlgMap;				//��Ӧ�ڴ洢dlg map ��xml�ļ�
	LIVEDLGMAP m_liveDlgMap;		//�Ѿ������˵�dlg
 

};
#define DLG_MNG_PTR CDlgManager::GetSingletonPtr()

/*****************************************************************************
ģ��ʵ�ֹ���: ���ô������Թ��������ַ���ת��Ϊ��Ӧ������ֵ
��ע		:  
����        : �����
�汾        : V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/4/19      1.0         �����      ����
******************************************************************************/
class CWindowStyleMap
{
public:
	static const TCHAR m_chPartitionChar;
public:
	/**  ͨ��һ���ַ���ת��Ϊһ�����
	 *  @param[in] str �ַ���
	 *  @param[out] dwStyle ���
	 *  @return �Ƿ�ɹ�
	 */
	static DWORD StringToStyle( LPCTSTR str );


    static bool StringToStyle( LPCTSTR str, DWORD& dwStyle, DWORD& dwStyleEx );

	/**  ע��һ������Ӧ��ϵ Ĭ��ע�����CRegDefaultData����
	 *  @param[in] dwStyle	���
	 *  @param[in] str		�ַ���
	 *  @return �Ƿ�ɹ�
	 */
	static bool RegStyle( DWORD dwStyle, LPCTSTR str );
protected:
	typedef std::map< CStdString, DWORD > DefaultStyleMap;
	static DefaultStyleMap m_mapStyles;
};

/*
* ע���һ��ID��һ���ַ�����ӳ��\n 
*/
#ifndef REG_WINDOW_STYLE
#define REG_WINDOW_STYLE( strKey ) CWindowStyleMap::RegStyle( strKey, _T(#strKey) );
#endif

}