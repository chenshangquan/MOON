/*****************************************************************************
�ļ�ʵ�ֹ���: �ַ�����������Ϣ��lib��ҵ������Ϣ
�ļ���      : msgHandler.h 
����ļ�    : LogicMap.h
��ע		: ͨ��logicMap����ע�ᵽdlg��paintManager��Notifier�����У�����Ӧ��Ӧ��dlg��Ϣ 
����        : �����
�汾        : V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/4/10      1.0         �����      ����
******************************************************************************/

#pragma once
namespace DuiLib {

#define MAX_MSG_NAME_LEN      100
#define MAX_CTRL_NAME_LEN  255
 
class CMsgHandler;

typedef LRESULT (CMsgHandler::*BUSI_MSG_HDL_FUNC)(WPARAM , LPARAM);
typedef void (CMsgHandler::*CTRL_MSG_HDL_FUNC)(TNotifyUI& msg);

//UI��ص���Ϣ
typedef struct tagCtrlMsg{

	TCHAR	tcCtrlMsgType[MAX_MSG_NAME_LEN];			  //��Ϣ��
	TCHAR   tcCtrlName[MAX_CTRL_NAME_LEN];  //�ؼ���
	CTRL_MSG_HDL_FUNC pMsgHdlFun;			  //��Ӧ�Ĵ�����ָ��
} TCtrlMsg,*PTCtrlMsg;


//lib����ص�ҵ������Ϣ
typedef struct tagBusiMsg{
	unsigned int	uiMsgID; //��Ϣ��
	BUSI_MSG_HDL_FUNC pMsgHdlFun; //��Ӧ�Ĵ�����ָ��
}TBusiMsg,*PTBusiMsg;




/*****************************************************************************
ģ����      : CMsgHandler 
�����      : CDUIDialog �� UIģ�����߼�������ĸ���
ģ��ʵ�ֹ���: �ַ�����������Ϣ��lib��ҵ������Ϣ
��ע        : CDUIDialog����ͨ��AddNotifier�ӿڰѸö�����ӵ�Notifier����������Ӧ֪ͨ
�汾        : V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/4/10      1.0         �����      ����
******************************************************************************/
class   UILIB_API CMsgHandler: public INotifyUI
{
public:
	//CMsgHandler(void);
	CMsgHandler( /* LPCTSTR  strDlgName = NULL */);
	~CMsgHandler(void);

	virtual void InitWnd();  //by xhx

	//UI����Ϣ�ַ�����
	virtual void Notify(TNotifyUI& msg);

	virtual LPCTSTR GetClassName() = 0;

	//ҵ������Ϣ�ַ�����
	void  BusiMsgNotify( UINT uiMsgID, WPARAM wparam, LPARAM lparam );

protected:

	//UI����Ϣӳ�����
	virtual const TCtrlMsg* GetCtrlMessageMap() const;

	//ҵ������Ϣӳ�����
	virtual const TBusiMsg* GetBusiMessageMap() const;
private:
  //static	const TCtrlMsg m_ctlMsgMap[]; //�ؼ�����Ϣӳ�����
  //static	const TBusiMsg m_busiMsgMap[];//ҵ������Ϣӳ�����
  
   /*CStdString  m_strDlgName;*/
	/*CDUIDialog  *m_pRoot;  */   
};


//����
#define DECLARE_MSG_MAP() \
	private: \
	static const TCtrlMsg m_ctlMsgMap[]; \
	static const TBusiMsg m_busiMsgMap[]; \
	protected: \
	virtual const TCtrlMsg* GetCtrlMessageMap() const; \
	virtual const TBusiMsg* GetBusiMessageMap() const; \

 

// UI��Ϣ�����ʼ�� ͬ END_CONTROL_MSG_MAP����ʹ�� 
#define BEGIN_CONTROL_MSG_MAP(theClass) \
	const TCtrlMsg* theClass::GetCtrlMessageMap() const \
	{ \
		return m_ctlMsgMap; \
	} \
	const TCtrlMsg theClass::m_ctlMsgMap[] = \
	{ \

//UI��Ϣ�ڴ˽���ӳ������
//CTRL_MSG()
//UI��Ϣ����ӳ����������	
#define END_CONTROL_MSG_MAP() \
	{ \
		_T(""), _T(""), NULL } \
	}; \
 
#define CTRL_MSG(tcCtrlMsgType, tcCtrlName, handlerFunc) \
	{ tcCtrlMsgType,tcCtrlName,(CTRL_MSG_HDL_FUNC)(void (CMsgHandler::*)(TNotifyUI&))&handlerFunc },







// ҵ������Ϣ�����ʼ�� ͬ END_BUSINESS_MSG_MAP����ʹ��  
#define BEGIN_BUSINESS_MSG_MAP(theClass) \
	const TBusiMsg* theClass::GetBusiMessageMap() const \
	{ \
		return m_busiMsgMap; \
	} \
	const TBusiMsg theClass::m_busiMsgMap[] = \
   { \

//ҵ������Ϣ�ڴ˽���ӳ������
//BUSI_MSG()
//ҵ������Ϣ����ӳ����������
#define END_BUSINESS_MSG_MAP() \
	{ \
		0, NULL } \
	};

#define BUSI_MSG( uiMsgID, handlerFunc) \
	{ uiMsgID,(BUSI_MSG_HDL_FUNC)(HRESULT (CMsgHandler::*)(WPARAM,LPARAM))&handlerFunc },








}