// WndMsgEventManage.h: interface for the CWndMsgEventManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WNDMSGEVENTMANAGE_H__049E4C6D_E3A9_4B99_841E_FAB9EEAF8ACE__INCLUDED_)
#define AFX_WNDMSGEVENTMANAGE_H__049E4C6D_E3A9_4B99_841E_FAB9EEAF8ACE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "uifactorydef.h"
/*---------------------------------------------------------------------
* ��	����CWndMsgEventManage
* ��    �ܣ�������Ϣ�¼������࣬ͨ��xml�ļ���ȡ������Ϣ��Ӧ
* ����˵����������Ϣ��Ӧ��������
*			����ID���ҵ���Ӧ���¼��������¼��������ҵ��¼���
*			ͨ���¼�������ȫ�ֺ���������ȥ�Ҷ�Ӧ���¼�����ִ��
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/05/13	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
namespace AutoUIFactory
{
class CWndMsgEventManage : public Singleton<CWndMsgEventManage>
{
public:
	const static String strFunc;
	const static String strScript;
public:
	CWndMsgEventManage();
	virtual ~CWndMsgEventManage();
/**  ����Windows��Ϣ
 *  @param[in] pMsg window��Ϣ
 *  @return �Ƿ�ɹ�
 */
	virtual bool TransMsg( WindowMsg* pMsg );

/**  Ϊĳһ������ע���¼�
 *  @param[in] wWndId ����ID
 *  @param[in] strEvent �¼�����
 *  @param[in] strFunc �¼�����
 *	@param[in] bCover ����Ѿ�ע�����Ƿ񸲸�
 *  @return �Ƿ�ɹ�
 */
	bool RegEvent( HWND hWnd, String strEvent, String strFunc, String strType = CWndMsgEventManage::strFunc, bool bCover = false );

/**  ��ע���¼�
 *  @param[in] wWndId ����ID
 *  @param[in] strEvent �¼�����
 *  @return �Ƿ�ɹ�
 */
	bool UnRegEvent( HWND hWnd, String strEvent );

/**  UnRegAllEvent
 *   mark  2012.12.3 yjj
 */
	void UnRegAllEvent();

protected:
	typedef pair<String,String>	FuncInfo;
	typedef std::map<String, FuncInfo > EventSet;
	typedef std::map<HWND, EventSet* > EventMap;
/*
 * �¼�����������һ��ؼ���Ӧ��һ���¼�\n 
 */
	EventMap m_mapEvents;

/*
 * ͨ������ID��ȡ�������¼���\n 
 */
	const std::map<String, FuncInfo >* GetFuncMap( HWND hWnd );
};


/*
 * ע���¼� id= ����ID event=�¼��� func=����\n
 * һ����������ṩ��EventTag���õ�
 */
#ifndef REG_WND_MSG_EVENT
#define REG_WND_MSG_EVENT( id, event, func, type ) CWndMsgEventManage::GetSingletonPtr()->RegEvent( id, event, func, type );
#endif

/*---------------------------------------------------------------------
* ��	����CWindowDefaultMsgMap
* ��    �ܣ��ṩһ����ID���ַ�����ת��������LButtonDown��һ���꣬��Ҫת��Ϊ�ַ�
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/06/02	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
class CWindowDefaultMsgMap
{
public:
	static bool MsgToString( unsigned int wMsg, String& str );
	static bool RegMsg( unsigned int wMsg, String str );
protected:
	typedef std::map< unsigned int, String > DefaultMsgMap;
	static DefaultMsgMap m_mapMsgs;
};

/*
 * ע���һ��ID��һ���ַ�����ӳ��\n 
 */
#ifndef REG_DEFAULT_WINDOW_MSG
#define REG_DEFAULT_WINDOW_MSG( id ) CWindowDefaultMsgMap::RegMsg( id, #id );
#endif
} // namespace AutoUIFactory end
#endif // !defined(AFX_WNDMSGEVENTMANAGE_H__049E4C6D_E3A9_4B99_841E_FAB9EEAF8ACE__INCLUDED_)
