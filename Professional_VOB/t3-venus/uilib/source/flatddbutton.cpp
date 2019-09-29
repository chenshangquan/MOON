/********************************************************************
	ģ����:      UILib
	�ļ���:      FlatDDButton.cpp
	����ļ�:    UILibHead.h
	�ļ�ʵ�ֹ��� ��ť��������
    ���ߣ�       ������
	�汾��       1.0
---------------------------------------------------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��		�汾		�޸���		�߶���    �޸�����
	7/20/2004	1.0         ������               ------------

*********************************************************************/

#include "stdafx.h"
#include "UIlibHead.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFlatDDButton::CFlatDDButton()
{
    m_pcDropTarget = new CDDTarget;
}

CFlatDDButton::~CFlatDDButton()
{
    delete m_pcDropTarget;
}

BEGIN_MESSAGE_MAP(CFlatDDButton, CFlatButton)
	//{{AFX_MSG_MAP(CFlatDDButton)
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
2004/07/20	1.0			������                  ����
====================================================================*/
void CFlatDDButton::PreSubclassWindow() 
{
    CFlatButton::PreSubclassWindow();
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
2004/07/20	1.0			������                  ����
====================================================================*/
LRESULT CFlatDDButton::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
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
	
	return CFlatButton::DefWindowProc(message, wParam, lParam);
}



/*====================================================================
������	��    OnDrop
����		���յ�������Ϣ�����õ���Ϣ����ת�����趨�Ĵ��ڡ�
�㷨ʵ��	������ѡ�
����ȫ�ֱ�������
�������˵����
����ֵ˵����  ��
----------------------------------------------------------------------
�޸ļ�¼:
��  ��		�汾		�޸���		�߶���    �޸�����
2004/07/20	1.0			������                  ����
====================================================================*/
BOOL CFlatDDButton::OnDrop(WPARAM pDropInfo, LPARAM lParam)
{
    CDropInfo *pInfo = (CDropInfo *)pDropInfo;
	ASSERT(pInfo->IsKindOf(RUNTIME_CLASS(CDropInfo)));

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
        GlobalUnlock(hMem);
        ::PostMessage(m_hRevMsgWnd, 
            CDragDropMsg::GetDDMsgID(MSG_DROP), (WPARAM)m_hWnd, nDragItem);
    }
	return FALSE;
}

DROPEFFECT CFlatDDButton::OnDropOver(WPARAM pDropInfo, LPARAM lParam)
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

DROPEFFECT CFlatDDButton::OnDropEx(WPARAM pDropInfo, LPARAM lParam)
{
	return (DROPEFFECT)-1;
}

/*====================================================================
������	��    Register
����		��ע�ᴰ�ڡ�
�㷨ʵ��	������ѡ�
����ȫ�ֱ�������
�������˵����
����ֵ˵����  ��
----------------------------------------------------------------------
�޸ļ�¼:
��  ��		�汾		�޸���		�߶���    �޸�����
2004/07/20	1.0			������                  ����
====================================================================*/
void CFlatDDButton::Register()
{
    m_pcDropTarget->Register(this);
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
2004/07/20	1.0			������                  ����
====================================================================*/
void CFlatDDButton::SetReceiveMsgWnd(HWND hRevMsgWnd)
{
    if (hRevMsgWnd == NULL) 
    {
        m_hRevMsgWnd = GetParent()->GetSafeHwnd();
    }
}