// MainFrameLogic.h: interface for the CMainFrameLogic class.
 /*****************************************************************************
 ģ����      : cnsTool�������߼�����ģ��
 �ļ���      : MainFrameLogic.h
 ����ļ�    : 
 �ļ�ʵ�ֹ���: �������߼���Ԫ 
 ˵��       �� ��ӦmainFrame.xml,���а��������dlg 
 ����        : �����
 �汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
 -----------------------------------------------------------------------------
 �޸ļ�¼:
 ��  ��         �汾        �޸���      �޸�����
 2012/11/23    1.0          �����      ����
******************************************************************************/

#if !defined(AFX_MAINFRAMELOGIC_H__7A9522E4_68BE_4C94_83CB_71ECEEC91F9E__INCLUDED_)
#define AFX_MAINFRAMELOGIC_H__7A9522E4_68BE_4C94_83CB_71ECEEC91F9E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CMainFrameLogic : public CLogicBase, public ISingleTon<CMainFrameLogic>
{
public: 
	virtual ~CMainFrameLogic();  
    CMainFrameLogic();

public:	 	
	/** ����:  ע��ص�����
	*  @param[in] 
	*  @return 
	*  @remarks  �ڶ�ȡxml�ļ�ʱ��,���������ע��ĺ���
	*/
	virtual void RegCBFun();

	/** ����:  ��ע��ص�����
	*  @param[in] 
	*  @return 
	*  @remarks  �����溯���෴,ע��ע��ĺ���
	*/
	virtual void UnRegFunc( );

	/** ����:  ��ʼ������
	*  @param[in] 
	*  @return 
	*  @remarks  �ڶ�ȡxml�ļ�ʱ�����,������������ݳ�ʼ������
	*/	
    virtual bool InitWnd( const IArgs & arg ); 
 
	/** ����:  ������
	*  @param[in] 
	*  @return 
	*  @remarks  �ڴ��ڹرյ�ʱ�����,��մ�������
	*/
    virtual void Clear() ;
protected:	
	/** ����: ע����Ϣ,��������lib���з���������Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	virtual void RegMsg(); 
		
	/** ����: ��ע����Ϣ,�����溯���෴,ע��ע�����Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	virtual void UnRegMsg();

	/** ����:  ������Ϣ��Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	HRESULT OnDisConnect( WPARAM wparam, LPARAM lparam );

	/** ����:  ��¼��Ϣ��Ӧ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	HRESULT OnConnectRsp( WPARAM wparam, LPARAM lparam );	

	/** ����:  ���ϵ�¼֪ͨ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	HRESULT OnGrabLoginNty( WPARAM wparam, LPARAM lparam );  

	/** ����:  ��½��ʱ��ʾ��Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	HRESULT OnLoginTimeOut( WPARAM wparam, LPARAM lparam );		
	
private: 
	/** ����:  ע������,�ص���¼����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnLogoff( const IArgs& args );		

	/** ����:  	������С��
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnMinmize( const IArgs& args );	

	/** ����:  	���ڹر�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool OnBtnTerminalCnstool( const IArgs& args );	

	/** ����:  ������־
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	bool OnBtnDowloadLog( const IArgs& args );		

	/** ����:  	����������
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	bool OnBtnResetSrv( const IArgs& args );		
	
	//�����ܲ˵�����¼�
    bool OnClickCfg( const IArgs& args );
    bool OnClickBaSic( const IArgs& args );
	bool OnClickDiag( const IArgs& args );
	bool OnClickCentCtrl( const IArgs& args );
	bool OnClickCamera( const IArgs& args );
	bool OnClickAddrBook( const IArgs& args );

	/** ����:  	��ʼ�������б�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/		
	void InitFunMenu();

	/** ����:  	��IP��ַת��Ϊ���ʽ
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
    String TransformIp(u32 dwIp);	

	/** ����:  Tableҳ�л�����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void SwitchCfgTabWnd( string strWnd );

	/** ����:  �������д���
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	void HideAllWnd();		

	/** ����:  �ж����ý���������Ƿ�Ķ�
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/
	s32 IsCfgChange();		

private:
    string m_strLstFunMenu;			//�����б� 
    const String m_stcStrCnsIp;		//���������Ͻ�CNS��IP��ַ
};

#endif // !defined(AFX_MAINFRAMELOGIC_H__7A9522E4_68BE_4C94_83CB_71ECEEC91F9E__INCLUDED_)
