// waringLogic.cpp: implementation of the CWaringLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "warningLogic.h"

#ifdef _DEBUG						//���������_DEBUG��Ҳ���ǵ��԰������ִ���������� 
#undef THIS_FILE					//ȡ����ǰ��THIS_FILE�Ķ��� 
static char THIS_FILE[]=__FILE__;   //��������ʼ��THIS_FILEO���飬���ݵĳ�ʼ����Ϊ���ļ����ļ���   __FILE__���ǵ�ǰԴ�ļ�������
#define new DEBUG_NEW				//����newΪDEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWarningLogic::CWarningLogic()
: m_stcWarning( "WaringDlg/StcWarning" )
, m_btnWarningPre( "BtnWarningPre" )
, m_btnWarningNext( "BtnWarningNext" )
, m_nIndex(-1)
{

}

CWarningLogic::~CWarningLogic()
{
	UnRegMsg();
	UnRegFunc();
}

void CWarningLogic::RegMsg()
{
	
}

void CWarningLogic::RegCBFun()
{
	REG_GOBAL_MEMBER_FUNC( "CWarningLogic::InitWnd", CWarningLogic::InitWnd, WARNINGLOGICRPTR, CWarningLogic);
	REG_GOBAL_MEMBER_FUNC( "CWarningLogic::OnBtnWarningPre", CWarningLogic::OnBtnWarningPre, WARNINGLOGICRPTR, CWarningLogic ); 
	REG_GOBAL_MEMBER_FUNC( "CWarningLogic::OnBtnWarningNext", CWarningLogic::OnBtnWarningNext, WARNINGLOGICRPTR, CWarningLogic ); 
}

void CWarningLogic::UnRegFunc()
{

}

void CWarningLogic::UnRegMsg()
{

}

bool CWarningLogic::InitWnd( const IArgs & arg )
{
	CLogicBase::InitWnd( arg );
	return true;
}

void CWarningLogic::Clear()
{
	m_vecWarning.clear();
	m_nIndex = -1;
	m_vecIsShow.clear();
	
	UIFACTORYMGR_PTR->LoadScheme( "SchmClean", m_pWndTree );
}

#define MAX_MESSAGE_LEN 70		//�����ʾ��Ϣ����
void CWarningLogic::MessageBoxWnd( const CString& strWaringText )
{
	if ( strWaringText.IsEmpty() )
	{
		return;
	}
	
	CString strTmpWaringText;
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	char chBuf[20];
	sprintf( chBuf, "%.2d:%.2d:%.2d ",sysTime.wHour, sysTime.wMinute, sysTime.wSecond );
	
	char chWaringText[MAX_MESSAGE_LEN+1] = {0};
	strncpy( chWaringText, strWaringText, MAX_MESSAGE_LEN);
	strTmpWaringText = chBuf;
	strTmpWaringText += chWaringText;
	
	ASSERT( m_vecWarning.size() <= 5 );
	
	//��ǰ��ʾ��ϢΪ���һ����ֱ����ʾ������Ϣ����ť����˸
	if ( m_nIndex == m_vecWarning.size()-1 )
	{
		if ( m_vecWarning.size() == 5 )
		{
			m_vecWarning.erase(m_vecWarning.begin());
			m_vecIsShow.erase(m_vecIsShow.begin());
		}
		
		if ( 0 <= m_vecWarning.size() && m_vecWarning.size() < 5 )
		{
			m_vecWarning.push_back(strTmpWaringText);
			m_nIndex = m_vecWarning.size()-1;
			m_vecIsShow.push_back(FALSE);
		}
		else
		{
			return;
		}
	}
	else			//��ǰ��ʾ��Ϣ��Ϊ���һ������ʾ��ǰ��Ϣ�����°�ť��˸
	{
		if ( m_vecWarning.size() == 5 )
		{
			m_vecWarning.erase(m_vecWarning.begin());
			m_vecIsShow.erase(m_vecIsShow.begin());
		}
		
		if ( 0 <= m_vecWarning.size() && m_vecWarning.size() < 5 )
		{
			m_vecWarning.push_back(strTmpWaringText);
			m_nIndex = m_nIndex-1;
			m_vecIsShow.push_back(FALSE);
			if ( m_nIndex <= 0 )
			{
				m_nIndex = 0;
			}
		}
		else
		{
			return;
		}
	}
	
	UpdateItem();
}

bool CWarningLogic::OnBtnWarningPre( const IArgs & arg )
{
	WarningChage(TRUE);
	return true;
}

bool CWarningLogic::OnBtnWarningNext( const IArgs & arg )
{
	WarningChage(FALSE);
	return true;
}

void CWarningLogic::UpdateItem()
{
	int nSize = m_vecWarning.size();
	if ( nSize == 0 )
	{
		return;
	}
	
	UIFACTORYMGR_PTR->SetCaption( m_stcWarning, (LPCTSTR)(m_vecWarning[m_nIndex]), m_pWndTree );
	
	int n = m_vecIsShow.size();
	ASSERT( n >= (m_nIndex+1) );
	
	m_vecIsShow[m_nIndex] = TRUE;
	
	Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_stcWarning, m_pWndTree );
	if ( pWnd != NULL )
	{
		pWnd->Invalidate(FALSE);
	}
	
	UpdateBtn();
}

void CWarningLogic::UpdateBtn()
{
	UIFACTORYMGR_PTR->LoadScheme( "SchmNextUnShine", m_pWndTree );
	std::vector<BOOL>::iterator it = m_vecIsShow.begin();
	for( ; it != m_vecIsShow.end(); it++ )
	{
		if ( *it == FALSE )
		{
			UIFACTORYMGR_PTR->LoadScheme( "SchmNextShine", m_pWndTree );
			break;
		}
	}
	
	UIFACTORYMGR_PTR->LoadScheme( "SchmHasPre", m_pWndTree );
	if ( m_nIndex <= 0 )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmNoPre", m_pWndTree );
	}
	
	UIFACTORYMGR_PTR->LoadScheme( "SchmHasNext", m_pWndTree );
	int n = m_vecWarning.size();
	if ( m_nIndex >= (m_vecWarning.size()-1) || m_vecWarning.size() <= 1 )
	{
		UIFACTORYMGR_PTR->LoadScheme( "SchmNoNext", m_pWndTree );
	}

}

void CWarningLogic::WarningChage( BOOL bPre )
{
	if ( bPre == TRUE )
	{
		m_nIndex = m_nIndex - 1;
		if ( m_nIndex <= 0 )
		{
			m_nIndex = 0;
		}
	}
	else
	{
		m_nIndex = m_nIndex + 1;
		if ( (m_nIndex+1) >= m_vecWarning.size() )
		{
			m_nIndex = m_vecWarning.size() - 1;
		}
	}
	
	UpdateItem();
}
