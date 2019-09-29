// WndLogicBase.h: interface for the CWndLogicBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WNDLOGICBASE_H__C7EF446E_24BE_46AF_9307_4206EE6A8EAA__INCLUDED_)
#define AFX_WNDLOGICBASE_H__C7EF446E_24BE_46AF_9307_4206EE6A8EAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

const String g_stcStrCenterCtrlDlg = "CenterCtrlDlg";
const String g_stcStrMainMenuDlg = "MainMenuDlg"; 
const String g_stcStrAirConditionDlg = "AirConditionDlg";
const String g_stcStrCameraDlg = "CameraDlg"; 
const String g_stcStrMonitorDlg = "MonitorDlg";
const String g_stcStrTouchPadDlg = "TouchPadDlg"; 
const String g_stcStrWaitingDlg = "WaitingDlg";
const String g_stcStrCurtainCfgDlg = "CurtainCfgDlg";
const String g_stcStrBtnCurtainCfg = "MainMenuDlg/BtnCurtainCfg";

class CWndLogicBase  
{
public:
    CWndLogicBase();   
	virtual ~CWndLogicBase();

	/**	 
	* ����:  ��ʼ��
	* @return   
	* @remarks	 
	*/
	void InitLogic()
	{    
		RegCBFun();
        RegMsg();
	};

    /**	 
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear() = 0;

	/**	 
	* ����:  ע���logic�����еĻص�����
	* @return  void
	* @remarks	�ڴ�ע��Ļص�������Ҫ�ǿؼ�����Ӧ�¼�����Ϊ��Ա�ص�����,Ҳ��ע�������Ļص�����
	                    ע��ʱ��Ӧע��ص�������Ӧ���ӵ��������򣺡�����::��������
	*/
	virtual bool RegCBFun(){ return true; }

    /**	 
	* ����:  ע��ĳ�ص�����
	* @return  void
	* @remarks	 
	*/
	virtual bool UnRegFunc(){ return true; }

    	/**	 
	* ����:  ��ʼ����������,
	* @return  void
	* @remarks	���ڸù��ܱ��������ؼ����Բ���xml����ؼ��󶨣�
	                    ��Ҫ��RegCBFun������ע�ᵽ�ص���������ģ�� 
	*/
	 virtual bool InitWnd(  const IArgs  & arg ) 
     { 
		 Args_WindowTree argTree = *dynamic_cast< Args_WindowTree *>( const_cast<IArgs*>( &arg ));
		 m_pWndTree = argTree.m_piTree; 
		 return true;
	 }
    
     IWndTree * GetWndTree(){ return m_pWndTree; }

protected: 
   /**	 
	* ����:  ע��Ҫ�������Ϣ
	* @return  void
	* @remarks	 ע������Ϣ���ܷ��͵����߼�ģ�飬���򣬽��ղ�������Ϣ
	*/
    virtual void RegMsg(){};

	virtual void UnRegMsg(){};

protected:
	IWndTree * m_pWndTree; 
};

#endif // !defined(AFX_WNDLOGICBASE_H__C7EF446E_24BE_46AF_9307_4206EE6A8EAA__INCLUDED_)
