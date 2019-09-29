// MsgDispatch.h: interface for the CMsgDispatch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGHANDLE_H__88B55A09_8C28_4EA6_B12B_C8DBFEBFE51E__INCLUDED_)
#define AFX_MSGHANDLE_H__88B55A09_8C28_4EA6_B12B_C8DBFEBFE51E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMsgHandle : public CWnd
{
public:
	CMsgHandle();
	virtual ~CMsgHandle();

public:
    static void Init();
    static void Destroy();

    static HWND GetMsgReceiveHandle();

    static void RegMsgHandler( u32 nMsgId, HWND hHandleWnd );
	
	static void DetachMsgHandler( u32 nMsgId, HWND hHandleWnd );

	static LRESULT SendMessage( u32 dwMessage, WPARAM wParam = 0 , LPARAM lParam = 0 );

protected:
    virtual BOOL PreCreateWindow( CREATESTRUCT& cs );
    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
 
private:
    DECLARE_MESSAGE_MAP()

private:
    void DisPatchMsg();

private:
    static CMsgHandle *m_pMySelf;
    static map< u32, vector<HWND> > m_mapDispatch;
};


/*
* ע��ȫ�ֺ����������Ա������Ϊ����ָ�� \n
* str ������ʾ func ������ obj ��ָ�� objType ������
*/ 
#ifndef REG_MSG
#define REG_MSG(dwMsgDI,hNotifyWnd)  CMsgHandle::RegMsgHandler( dwMsgDI, hNotifyWnd );
#endif


/*
* ��ע��ȫ�ֺ��� \n
* str ������ʾ
*/
#ifndef UN_REG_MSG
#define UN_REG_MSG( dwMsgDI,hNotifyWnd ) CMsgHandle::DetachMsgHandler( dwMsgDI,hNotifyWnd );
#endif
#endif // !defined(AFX_MSGDISPATCH_H__88B55A09_8C28_4EA6_B12B_C8DBFEBFE51E__INCLUDED_)
