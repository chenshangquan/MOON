/*=======================================================================
ģ����      : UILibHead.h
�ļ���      : SkinDDListCtrl.cpp
����ļ�    : 
�ļ�ʵ�ֹ���: 
����        : ���ǿ
�汾        : V1.0  Copyright(C) 2003-2005 KDC, All rights reserved.
-------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾  �޸���  �޸�����
2004/07/16  1.0   ���ǿ  ����
=======================================================================*/

#include "stdafx.h"
#include "UILibHead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CSkinDDListCtrl::CSkinDDListCtrl()
{
    m_hRevMsgWnd = NULL;
    m_pcDropTarget = new CDDTarget;
}

CSkinDDListCtrl::~CSkinDDListCtrl()
{
    delete m_pcDropTarget;
}

BEGIN_MESSAGE_MAP(CSkinDDListCtrl, CSkinListCtrl)
	//{{AFX_MSG_MAP(CSkinDDListCtrl)
	ON_NOTIFY_REFLECT(LVN_BEGINDRAG, OnBegindrag)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSkinDDListCtrl message handlers

/*====================================================================
������	��    PreSubclassWindow
����		��Ԥ����ע�ἰ���ý�����Ϣ���ڡ�
�㷨ʵ��	������ѡ�
����ȫ�ֱ�������
�������˵����
����ֵ˵����  ��
----------------------------------------------------------------------
�޸ļ�¼:
��  ��		�汾		�޸���		�߶���    �޸�����
2004/07/16	1.0			���ǿ                  ����
2004/07/20	1.0			������                  ע��
====================================================================*/
void CSkinDDListCtrl::PreSubclassWindow() 
{
    CSkinListCtrl::PreSubclassWindow();
    m_pcDropTarget->Register(this);
    SetReceiveMsgWnd();
}

/*====================================================================
������	��    DefWindowProc
����		��������Ϣ�����Ӵ����Զ����������Ϣ��
�㷨ʵ��	������ѡ�
����ȫ�ֱ�������
�������˵����
����ֵ˵����  ��
----------------------------------------------------------------------
�޸ļ�¼:
��  ��		�汾		�޸���		�߶���    �޸�����
2004/07/16	1.0			���ǿ                  ����
2004/07/20	1.0			������                  ע��
====================================================================*/
LRESULT CSkinDDListCtrl::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
    if (CDragDropMsg::HasSetMsgID()) 
    {
        UINT nMsgId = message - CDragDropMsg::GetStartMsgID();
        switch(nMsgId) 
        {
        case MSG_DRAGOVER:
            {
                OnDropOver(wParam, lParam);
            }
            break;
        case MSG_DROP:
            {
                OnDrop(wParam, lParam);
            }
            break;
        case MSG_DROPEX:
            {
                OnDropEx(wParam, lParam);
            }
            break;
        default:
            break;
        }
    }
	
	return CSkinListCtrl::DefWindowProc(message, wParam, lParam);
}

void CSkinDDListCtrl::OnBegindrag(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
    if(pNMListView)
	{
        //������������
        CString strData;
        strData.Format(_T("%d"), pNMListView->iItem);
        HGLOBAL hData = GlobalAlloc(GHND | GMEM_SHARE, strData.GetLength() + 1);
        char *pbyData = (char *)GlobalLock(hData);
        memcpy(pbyData, (LPCTSTR)strData, strData.GetLength());
        pbyData[strData.GetLength()] = 0;
        GlobalUnlock(hData);

        
        COleDataSource cDataSrc;
        cDataSrc.CacheGlobalData(CF_TEXT, hData);
        DROPEFFECT ret = cDataSrc.DoDragDrop(DROPEFFECT_COPY);
        GlobalFree(hData);
        ::PostMessage(m_hRevMsgWnd, 
            CDragDropMsg::GetDDMsgID(MSG_BEGINDRAG), (WPARAM)m_hWnd, pNMListView->iItem);
    }
	
	*pResult = 0;
}

BOOL CSkinDDListCtrl::OnDrop(WPARAM pDropInfo, LPARAM lParam)
{
    CDropInfo *pInfo = (CDropInfo *)pDropInfo;
	ASSERT(pInfo->IsKindOf(RUNTIME_CLASS(CDropInfo)));

	//ģ��᳡
	if(pInfo->m_pDataObject->IsDataAvailable(CF_TEXT))
	{
		//�õ���������
		HGLOBAL hMem = pInfo->m_pDataObject->GetGlobalData(CF_TEXT);
        char *pMem = (char *)GlobalLock(hMem);

        if(pMem == NULL)
		{
			GlobalUnlock(hMem);
			return FALSE;
		}

		int nDragItem = (DWORD)atoi(pMem);
		UINT uFlags = 0;
		int nDropItem = HitTest(pInfo->m_point, &uFlags);
        GlobalUnlock(hMem);
        UINT dwItem = MAKELONG(nDragItem, nDropItem);
        ::PostMessage(m_hRevMsgWnd, 
            CDragDropMsg::GetDDMsgID(MSG_DROP), (WPARAM)m_hWnd, dwItem);
    }
	return FALSE;
}

DROPEFFECT CSkinDDListCtrl::OnDropOver(WPARAM pDropInfo, LPARAM lParam)
{
    CDropInfo *pInfo = (CDropInfo *)pDropInfo;
	ASSERT(pInfo->IsKindOf(RUNTIME_CLASS(CDropInfo)));
	
	if(pInfo->m_pDataObject->IsDataAvailable(CF_TEXT))
	{
		return DROPEFFECT_COPY;
	}
	else
	{
		return DROPEFFECT_NONE;
	}
}

DROPEFFECT CSkinDDListCtrl::OnDropEx(WPARAM pDropInfo, LPARAM lParam)
{
	return (DROPEFFECT)-1;
}

/*====================================================================
������	��    SetReceiveMsgWnd
����		�����ý�����Ϣ���ڡ�
�㷨ʵ��	������ѡ�
����ȫ�ֱ�������
�������˵����
����ֵ˵����  ��
----------------------------------------------------------------------
�޸ļ�¼:
��  ��		�汾		�޸���		�߶���    �޸�����
2004/07/16	1.0			���ǿ                  ����
2004/07/20	1.0			������                  ע��
====================================================================*/
void CSkinDDListCtrl::SetReceiveMsgWnd(HWND hRevMsgWnd)
{
    if (hRevMsgWnd == NULL) 
    {
        m_hRevMsgWnd = GetParent()->GetSafeHwnd();
    }
    else
    {
        m_hRevMsgWnd = hRevMsgWnd;
    }
}

//////////////////////////////////////////////////////////////////////////
//������Ϣ��                                                            //
//////////////////////////////////////////////////////////////////////////

UINT CDragDropMsg::m_nStartMsgID = 0;

//������Ϣ�Ļ��㡣
void CDragDropMsg::SetStartMsgID(UINT nStartMsgID)
{
    m_nStartMsgID = nStartMsgID;
}

//�õ���Ϣ�Ļ��㡣
UINT CDragDropMsg::GetStartMsgID()
{
    return m_nStartMsgID;
}

//�Ƿ���������Ϣ
BOOL CDragDropMsg::HasSetMsgID()
{
    return m_nStartMsgID != 0;
}

//����ƫ�Ƽ���ʵ�ʵ���ϢID
UINT CDragDropMsg::GetDDMsgID(UINT nMsgType)
{
    return m_nStartMsgID + nMsgType;
}


//////////////////////////////////////////////////////////////////////////
//
//    CDropInfo  ���ڴ���������Ϣ����
//////////////////////////////////////////////////////////////////////////

IMPLEMENT_DYNAMIC( CDropInfo, CObject );

CDropInfo::CDropInfo()
{
	m_pDataObject = NULL;
	m_dwKeyState = 0;
	m_dropEffect = (DROPEFFECT)-1;
	m_dropEffectList = DROPEFFECT_NONE;
}

CDropInfo::CDropInfo(COleDataObject* pDataObject,DWORD dwKeyState,
				DROPEFFECT dropEffect,DROPEFFECT dropEffectList,CPoint point )
{
	m_pDataObject = pDataObject;
	m_dwKeyState = dwKeyState;
	m_dropEffect = dropEffect;
	m_dropEffectList = dropEffectList;
	m_point = point;
}

CDropInfo::~CDropInfo()
{
	m_pDataObject = NULL;
}

//////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
//
// CDDTarget �̳�����Ŀ�����
//////////////////////////////////////////////////////////////////////////


CDDTarget::CDDTarget()
{

}

CDDTarget::~CDDTarget()
{
    Revoke();
}

//////////////////////////////////////////////////////////////////////
DROPEFFECT CDDTarget::OnDragEnter(CWnd* pWnd, COleDataObject* pDataObject,
			DWORD dwKeyState, CPoint point)
{
	ASSERT_VALID(this);
	ASSERT(::IsWindow(pWnd->m_hWnd));

	if (pWnd->IsKindOf(RUNTIME_CLASS(CView)))
		return COleDropTarget::OnDragEnter(pWnd,pDataObject, dwKeyState, point);

	CDropInfo DropInfo( pDataObject, dwKeyState, 0, 0, point );
	 ::SendMessage( pWnd->GetSafeHwnd(), CDragDropMsg::GetDDMsgID(MSG_DRAGENTER), (WPARAM)&DropInfo, 0 );
    return DROPEFFECT_COPY;
}

DROPEFFECT CDDTarget::OnDragOver(CWnd* pWnd, COleDataObject* pDataObject,
			DWORD dwKeyState, CPoint point)
{
	ASSERT_VALID(this);
	ASSERT(::IsWindow(pWnd->m_hWnd));

	if (pWnd->IsKindOf(RUNTIME_CLASS(CView)))//if CView,Call base class
		return COleDropTarget::OnDragOver(pWnd,pDataObject, dwKeyState, point);
	
	CDropInfo DropInfo(pDataObject, dwKeyState, 0, 0, point);
    ::SendMessage(pWnd->GetSafeHwnd(), CDragDropMsg::GetDDMsgID(MSG_DRAGOVER), (WPARAM)&DropInfo, 0);
    return DROPEFFECT_COPY;
}

BOOL CDDTarget::OnDrop(CWnd* pWnd, COleDataObject* pDataObject,
        DROPEFFECT dropEffect, CPoint point)
{
	ASSERT_VALID(this);
	ASSERT(::IsWindow(pWnd->m_hWnd));

	if (pWnd->IsKindOf(RUNTIME_CLASS(CView)))//if CView,Call base class
		return COleDropTarget::OnDrop(pWnd, pDataObject,dropEffect,point);

	CDropInfo DropInfo(pDataObject, 0, dropEffect, 0, point);
    ::SendMessage(pWnd->GetSafeHwnd(), CDragDropMsg::GetDDMsgID(MSG_DROP), (WPARAM)&DropInfo, 0);

    return TRUE;
}

DROPEFFECT CDDTarget::OnDropEx(CWnd* pWnd, COleDataObject* pDataObject,
			DROPEFFECT dropEffect, DROPEFFECT dropEffectList, CPoint point)
{
	ASSERT_VALID(this);
	ASSERT(::IsWindow(pWnd->m_hWnd));

	if (pWnd->IsKindOf(RUNTIME_CLASS(CView)))//if CView,Call base class
		return COleDropTarget::OnDropEx( pWnd, pDataObject, dropEffect, dropEffectList, point) ;

	CDropInfo DropInfo(pDataObject, 0, dropEffect, dropEffectList, point);
    ::SendMessage(pWnd->GetSafeHwnd(), CDragDropMsg::GetDDMsgID(MSG_DROPEX), (WPARAM)&DropInfo, 0);
    return (DROPEFFECT)-1;
}

void CDDTarget::OnDragLeave(CWnd* pWnd)
{
	ASSERT_VALID(this);
	ASSERT(::IsWindow(pWnd->m_hWnd));

	if (pWnd->IsKindOf(RUNTIME_CLASS(CView)))//if CView,Call base class
	{
		COleDropTarget::OnDragLeave(pWnd);
		return;
	}

    ::SendMessage(pWnd->GetSafeHwnd(), CDragDropMsg::GetDDMsgID(MSG_DRAGLEAVE), 0, 0);
	return;
}


BOOL CDDTarget::MyRegist(CWnd *pWnd)
{
	ASSERT_VALID(this);
	ASSERT(m_hWnd == NULL);     // registering drop target twice?
	ASSERT_VALID(pWnd);

	LPUNKNOWN lpUnknown = (LPUNKNOWN)GetInterface(&IID_IUnknown);
	ASSERT(lpUnknown != NULL);

	// the object must be locked externally to keep LRPC connections alive
    
    HRESULT re = CoLockObjectExternal(lpUnknown, TRUE, FALSE);
	if (re != S_OK)
		return FALSE;

	// connect the HWND to the IDropTarget implementation
	if (RegisterDragDrop(pWnd->m_hWnd,
		(LPDROPTARGET)GetInterface(&IID_IDropTarget)) != S_OK)
	{
		CoLockObjectExternal(lpUnknown, FALSE, FALSE);
		return FALSE;
	}

	// connect internal data
	m_hWnd = pWnd->m_hWnd;


	return TRUE;

}
