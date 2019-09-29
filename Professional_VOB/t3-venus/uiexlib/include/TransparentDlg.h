// TransparentDlg.h: interface for the CTransparentDlg class.
//
//////////////////////////////////////////////////////////////////////

/*****************************************************************************
ģ����      : ͸��dialog 
�ļ���      : TransparentDlg.h
����ļ�    : TransparentBaseDlg.h  
�ļ�ʵ�ֹ���:  ʵ����ģ����Դ�������ֱ�Ӵ���dlg 
����        : �����
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/11/25     1.0         �����      ����
******************************************************************************/

#if !defined(AFX_TRANSPARENTDLG_H__491179F1_B1F3_4F9A_B7F1_F3E639BFE850__INCLUDED_)
#define AFX_TRANSPARENTDLG_H__491179F1_B1F3_4F9A_B7F1_F3E639BFE850__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "TransparentDlgBase.h"
class CTransparentDlg: public CTransparentDlgBase  
{
public: 
	CTransparentDlg();
	~CTransparentDlg(); 
    
	/*****************************************************************************
	* ����: �����Ի���
	* @param [in]  strDlgName  ������
	* @param [in]  rc  ����λ�ô�С
	* @param [in]  dwStyle  ����style�� dwExtendedStyle ��չstyle
	* @param [in]  pParent ���ڵĸ�����
	* @param [in]  bModal  �Ƿ�Ϊģ̬����
	* @return  BOOL �ɹ�����TRUE;ʧ�ܷ���FALSE
	* @remarks	 
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2012/11/25     1.0         �����      ����
    ******************************************************************************/
	BOOL Create( CString strDlgName, CRect rc,DWORD dwStyle, DWORD dwExtendedStyle, CWnd* pParent = NULL,BOOL bModal = FALSE );  


	/*****************************************************************************
	* ����: domodal�Ի��� 
	* @return  int  
	* @remarks ���øýӿ�ǰ��Ҫ�ȵ���Create������ ����bModal������Ϊtrue�� 
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2012/11/25     1.0         �����      ����
    ******************************************************************************/
	int  DoModal();


	/*****************************************************************************
	* ����: domodal�Ի���	
	* @param [in]  strDlgName  ������
	* @param [in]  rc  ����λ�ô�С
	* @param [in]  dwStyle  ����style�� dwExtendedStyle ��չstyle
	* @return  int  
	* @remarks �����ȵ���Create����ֱ�ӵ���
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2012/11/25     1.0         �����      ����
    ******************************************************************************/
	int  DoModal(CString strDlgName, CRect rc,DWORD dwStyle, DWORD dwExtendedStyle, CWnd* pParent = NULL);



	/*****************************************************************************
	* ����: ��ʼ����modal��Ϣѭ��������ʼ���ڵ�domodal״̬
	* @return  int  
	* @remarks �����Ѿ��Է�ģ̬����ʽ�������ڴ�ת��Ϊģ̬��ʽ;
	           ��Ҫ�������ڵ�domodal״̬ʱ����StopModalLoop( int nResult ),
			   �����������nResult��ΪStartModalLoop�ķ���ֵ
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2012/12/30     1.0         �����      ����
    ******************************************************************************/
	int StartModalLoop();
    

	/*****************************************************************************
	* ����: �Ƿ��Ѿ���modalѭ������StartModalLoopǰ�����жϣ�
	        �����ǰ�Ѿ���domal״̬�����ٴε���StartModalLoop��domodal��ʧ��
	* @return  int  
	* @remarks �����Ѿ��Է�ģ̬����ʽ�������ڴ�ת��Ϊģ̬��ʽ;
	           ��Ҫ�������ڵ�domodal״̬ʱ����StopModalLoop( int nResult ),
			   �����������nResult��ΪStartModalLoop�ķ���ֵ
	-----------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��         �汾        �޸���      �޸�����
	2013/2/28     1.0         �����      ����
    ******************************************************************************/
	BOOL IsInModalLoop();
    
	void StopModalLoop( int nResult );
protected:

	virtual BOOL PreTranslateMessage(MSG* pMsg);       //����domodal���ں�child���ڵ���   ����س���������
private:
    
	//����dlgģ��
	DLGTEMPLATE* ConstructDlgTemp( CRect rc,DWORD dwStyle, DWORD dwExtendedStyle );
	
	//���dlgģ��buffer 
	void ClearDlgTempBuff();

	//��ӡ����
	void PrtError( CString strErrFun,CString strErr );

	//����Dlg�����Ƿ�Ϸ�
    BOOL CheckParam( DWORD& dStyle, CWnd* pParent = NULL, BOOL bModalDlg = FALSE );


 

private: 
	CString m_strTxt;            //dlg ����
    DLGTEMPLATE *m_pDlgTemp;    //�洢dlgģ��,��Ҫ����modal���ʹ���
    
};

#endif // !defined(AFX_TRANSPARENTDLG_H__491179F1_B1F3_4F9A_B7F1_F3E639BFE850__INCLUDED_)
