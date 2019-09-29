// ConftempEdtLogic.cpp: implementation of the CConftempEdtLogic class.
//���ļ�ֻ���� ģ��༭����� ������ʾ �� bnt����Ȼ������������������list�¼�����
//conftempEdtSub.cpp�д���
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "ConftempEdtLogic.h" 
#include "pollLstManage.h"
#include "msgBoxLogic.h" 

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CConftempEdtLogic *CConftempEdtLogic::m_pLogic = NULL;

// g_stcStrConftempEdtDlg
//
const String  CConftempEdtLogic::m_strDlgLst = "DlgLst";                      //�����б�Ľ���
                 
const String  CConftempEdtLogic::m_strLstTemp ="LstConftemp";                //ģ���б�
const String  CConftempEdtLogic::m_strLstCns = "LstCns";                     //cns�б�
const String  CConftempEdtLogic::m_strBtnCreateTemp = "BtnCreateTemp";       //btn  �½�����ģ��
const String  CConftempEdtLogic::m_strBtnShwConfInfo = "BtnShowConfInfo";     //btn  ��ʾ������Ϣ
const String  CConftempEdtLogic::m_strBtnShwPollInfo = "BtnShowPollInfo";      //btn  ��ʾ��ѯ��Ϣ
const String  CConftempEdtLogic::m_strBtnEdit = "BtnEdit";                    //btn  �༭
const String  CConftempEdtLogic::m_strBtnSave = "BtnSave";                     //btn  ����
const String  CConftempEdtLogic::m_strBtnCancle = "BtnCancle";                 //btn  ȡ��

  
const String  CConftempEdtLogic::m_strDlgInfo = "DlgInfo";                   //������Ϣ�ĸ�����

//m_strDlgConfInfo = "DlgConfInfo" 
const String  CConftempEdtLogic::m_strDlgConfInfo = "DlgConfInfo";            //Dlg ������Ϣ
const String  CConftempEdtLogic::m_strEdtConfName = "EdtConfName";           //������
const String  CConftempEdtLogic::m_strEdtConfE164 = "EdtConfE164";            //E164
const String  CConftempEdtLogic::m_strEdtPrimaCnsName = "EdtPrimaCnsName";   //���᳡��
const String  CConftempEdtLogic::m_strLstSecondaryCns = "LstSecondaryCns";            //cns�ֻ᳡�б�
 
//m_strDlgPollInfo = "DlgPollInfo" 
const String  CConftempEdtLogic::m_strDlgPollInfo = "DlgPollInfo";              //Dlg ��ѯ��Ϣ 
const String  CConftempEdtLogic::m_strEdtPollIntv = "EdtPollInterval";        //��ѯ���
const String  CConftempEdtLogic::m_strLstPollCns = "LstPollCns";               //cns ��ѯ�б�


//������ര��
const String  CConftempEdtLogic::m_strLstAddr ="LstAddr" ;                     //��ַ��
const String  CConftempEdtLogic::m_strLstAddrGrp ="LstAddrGrp";                  //��ַ������
const String  CConftempEdtLogic::m_strBtnShowAddrGrp ="BtnShowAddr";                  //��ʾ��ַ������
const String  CConftempEdtLogic::m_strBtnShowAddr ="BtnShowAddrGrp";                      //��ʾ��ַ��


const String CConftempEdtLogic::m_strDlgPollManageMenu = "PollLstManageMenu";
const String CConftempEdtLogic::m_strLstPollManage = "PollLstManageMenu/LstManageMenu";

CConftempEdtLogic::CConftempEdtLogic():m_tConfTempSel(),
                                       m_bEdtState(FALSE),
                                       m_emShowInfo( emDlgShowConfInfo )
{ 

    const_cast<String &> (m_strLstTemp) = m_strDlgLst + "/" + m_strLstTemp;
    const_cast<String &> (m_strLstCns) = m_strDlgLst + "/" + m_strLstCns;
    const_cast<String &> (m_strLstAddr) = m_strDlgLst + "/" + m_strLstAddr;
    const_cast<String &> (m_strLstAddrGrp) = m_strDlgLst + "/" + m_strLstAddrGrp;
 
         
    
    const_cast<String &> (m_strBtnEdit) = m_strDlgInfo + "/" + m_strBtnEdit;

    const_cast<String &> (m_strDlgConfInfo) = m_strDlgInfo + "/" + m_strDlgConfInfo;
   // m_strDlgConfInfo = "DlgConfInfo"
    const_cast<String &> (m_strEdtConfName) = m_strDlgConfInfo + "/" + m_strEdtConfName;
    const_cast<String &> (m_strEdtConfE164) = m_strDlgConfInfo + "/" + m_strEdtConfE164;
    const_cast<String &> (m_strEdtPrimaCnsName) = m_strDlgConfInfo + "/" + m_strEdtPrimaCnsName;
    const_cast<String &> (m_strLstSecondaryCns) = m_strDlgConfInfo + "/" + m_strLstSecondaryCns;
  
    
    const_cast<String &> (m_strDlgPollInfo) = m_strDlgInfo + "/" + m_strDlgPollInfo;
    //m_strDlgPollInfo = "DlgPollInfo" 
    const_cast<String &> (m_strEdtPollIntv) = m_strDlgPollInfo + "/" + m_strEdtPollIntv;
    const_cast<String &> (m_strLstPollCns) = m_strDlgPollInfo + "/" + m_strLstPollCns; 
    
    m_tConfTempSel.InvalidConfTemp();
}

CConftempEdtLogic::~CConftempEdtLogic()
{
    if ( m_pLogic != NULL )
    {   
        UnRegMsg();
        UnRegFunc();
        delete m_pLogic;
        m_pLogic = NULL; 
	}
}


CConftempEdtLogic* CConftempEdtLogic::GetLogicPtr()
{
    if ( m_pLogic == NULL )
    {  
        m_pLogic = new CConftempEdtLogic(); 
        
    }
    
    return m_pLogic;
}

void CConftempEdtLogic::RegMsg()
{    
    
    REG_MSG_HANDLER(  UI_UMS_REFRESH_CONFTEMPLATE_LIST,CConftempEdtLogic::OnRefreshConftempLstNotify, m_pLogic, CConftempEdtLogic);
    REG_MSG_HANDLER( UI_UMS_OPERATE_CONFTEMP_RET, CConftempEdtLogic::OnOperateTempRet, m_pLogic, CConftempEdtLogic );

    REG_MSG_HANDLER( UI_CNS_ADDRBOOK_CHANGED, CConftempEdtLogic::OnUpdateAddrBook, m_pLogic, CConftempEdtLogic );
    
}

void CConftempEdtLogic::UnRegMsg()
{
    
}

bool CConftempEdtLogic::RegCBFun()
{   	 
    REG_GOBAL_MEMBER_FUNC( "CConftempEdtLogic::InitWnd", CConftempEdtLogic::InitWnd, m_pLogic, CConftempEdtLogic);
   
    //���itemͼ��
    REG_GOBAL_MEMBER_FUNC( "CConftempEdtLogic::OnTempLstDelIcon", CConftempEdtLogic::OnTempLstDelIcon, m_pLogic, CConftempEdtLogic);
    REG_GOBAL_MEMBER_FUNC( "CConftempEdtLogic::OnTempItemClick", CConftempEdtLogic::OnTempItemClick, m_pLogic, CConftempEdtLogic);    
    REG_GOBAL_MEMBER_FUNC( "CConftempEdtLogic::OnCnsLstDelIcon", CConftempEdtLogic::OnCnsLstDelIcon, m_pLogic, CConftempEdtLogic);
    REG_GOBAL_MEMBER_FUNC( "CConftempEdtLogic::OnCnsLstAddICon", CConftempEdtLogic::OnCnsLstAddICon, m_pLogic, CConftempEdtLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CConftempEdtLogic::OnAddrAddIcon", CConftempEdtLogic::OnAddrAddIcon, m_pLogic, CConftempEdtLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CConftempEdtLogic::OnAddGrpAddIcon", CConftempEdtLogic::OnAddGrpAddIcon, m_pLogic, CConftempEdtLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CConftempEdtLogic::OnPollItemClick", CConftempEdtLogic::OnPollItemClick, m_pLogic, CConftempEdtLogic ) ; 
   
    REG_GOBAL_MEMBER_FUNC( "CConftempEdtLogic::DelSelConfTemp", CConftempEdtLogic::DelSelConfTemp, m_pLogic, CConftempEdtLogic);

    //δѡ�л���ģ���֪ͨ
    REG_GOBAL_MEMBER_FUNC( "CConftempEdtLogic::UnSelConfTemp", CConftempEdtLogic::UnSelConfTemp, m_pLogic, CConftempEdtLogic ) ; 
 
    //���button
    REG_GOBAL_MEMBER_FUNC( "CConftempEdtLogic::OnBtnNewClick", CConftempEdtLogic::OnBtnNewClick, m_pLogic, CConftempEdtLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CConftempEdtLogic::OnBtnEdtClick", CConftempEdtLogic::OnBtnEdtClick, m_pLogic, CConftempEdtLogic);
    REG_GOBAL_MEMBER_FUNC( "CConftempEdtLogic::OnBtnSaveClick", CConftempEdtLogic::OnBtnSaveClick, m_pLogic, CConftempEdtLogic);
    REG_GOBAL_MEMBER_FUNC( "CConftempEdtLogic::OnBtnCancleClick", CConftempEdtLogic::OnBtnCancleClick, m_pLogic, CConftempEdtLogic);
    REG_GOBAL_MEMBER_FUNC( "CConftempEdtLogic::OnBtnAddAllCnsToPollClick", CConftempEdtLogic::OnBtnAddAllCnsToPollClick, m_pLogic, CConftempEdtLogic);
    REG_GOBAL_MEMBER_FUNC( "CConftempEdtLogic::OnBtnClearPollClick", CConftempEdtLogic::OnBtnClearPollClick, m_pLogic, CConftempEdtLogic);

    

    REG_GOBAL_MEMBER_FUNC( "CConftempEdtLogic::OnBtnShowAddrClick", CConftempEdtLogic::OnBtnShowAddrClick, m_pLogic, CConftempEdtLogic);
    REG_GOBAL_MEMBER_FUNC( "CConftempEdtLogic::OnBtnShowAddrGrpClick", CConftempEdtLogic::OnBtnShowAddrGrpClick, m_pLogic, CConftempEdtLogic);
    
    REG_GOBAL_MEMBER_FUNC( "CConftempEdtLogic::OnBtnShowConfinfoClick", CConftempEdtLogic::OnBtnShowConfinfoClick, m_pLogic, CConftempEdtLogic);
    REG_GOBAL_MEMBER_FUNC( "CConftempEdtLogic::OnBtnShowPollClick", CConftempEdtLogic::OnBtnShowPollClick, m_pLogic, CConftempEdtLogic);
    
    REG_GOBAL_MEMBER_FUNC( "CConftempEdtLogic::BtnSavePollMenueToFileClick", CConftempEdtLogic::BtnSavePollMenueToFileClick, m_pLogic, CConftempEdtLogic ) ;
    REG_GOBAL_MEMBER_FUNC( "CConftempEdtLogic::BtnSaveToFileClick", CConftempEdtLogic::BtnSaveToFileClick, m_pLogic, CConftempEdtLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CConftempEdtLogic::CloseDlg", CConftempEdtLogic::CloseDlg, m_pLogic, CConftempEdtLogic ) ; 

     
    //drag end
    REG_GOBAL_MEMBER_FUNC( "CConftempEdtLogic::OnEndDragPollLst", CConftempEdtLogic::OnEndDragPollLst, m_pLogic, CConftempEdtLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CConftempEdtLogic::OnEndDragFrmPollLst", CConftempEdtLogic::OnEndDragFrmPollLst, m_pLogic, CConftempEdtLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CConftempEdtLogic::OnEndDragSecdryCns", CConftempEdtLogic::OnEndDragSecdryCns, m_pLogic, CConftempEdtLogic ) ; 
    


    return true;
}

bool CConftempEdtLogic::UnRegFunc()
{
    //	UN_REG_GOBAL_FUNC( "CConftempEdtLogic::InitWnd" );
    return true;
}


bool CConftempEdtLogic::InitWnd(  const IArgs & arg )
{   
    CWndLogicBase::InitWnd( arg );

    CPollLstManage::GetPollLstManage()->Init(&m_tConfTempSel,m_pLogic);

    UIManagePtr->LoadScheme("SchmDisable",m_pWndTree );
    UIManagePtr->LoadScheme("SchmHideAllLst",m_pWndTree );
    UIManagePtr->LoadScheme("SchmShowTempLst",m_pWndTree );
 
    
    UpdateAddrList();
    UpdateAddrGrpList();

    //ע�����ק���� 
    CDragWindow* p = CDragWindow::GetDragWindow();
    Window* pPollLst = UIManagePtr->GetWindowPtr( m_strLstPollCns, m_pWndTree );
    Window* pCnsLst = UIManagePtr->GetWindowPtr( m_strLstSecondaryCns, m_pWndTree );
    if ( p != NULL )
    {   
        
        p->RegisterDropWindow( pPollLst );  
        p->RegisterDropWindow( pCnsLst ); 

    } 
 
//     CBmpDragWindow* pBmp = CBmpDragWindow::GetDragWindow();
//     if ( pBmp != NULL )
//     {   
//         pBmp->RegisterDropWindow( pPollLst );  
//         pBmp->RegisterDropWindow( pCnsLst ); 
// 
//     }

    OnRefreshConftempLstNotify( 0,0 ); 
    UpdateTempInfoDlg();

    UIManagePtr->LoadScheme( "SchmHideEditBtn", m_pWndTree, m_strBtnEdit );
    return true;
}

void CConftempEdtLogic::Clear() 
{
    m_tConfTempSel.Clear();
	m_vctAddrList.clear();
	m_vctGroupList.clear();
    m_bEdtState = FALSE;
    m_emShowInfo = emDlgShowConfInfo;
    
    //�����б�ƫ����Ϊ0
    Value_TransparentBaseListOffset val;
    val.nOffset = 0;
    UIManagePtr->SetPropertyValue( val, m_strLstTemp, m_pWndTree );
    SetTempSubList();
 
    //���õ�ǰû��ѡ����  
	Value_TransparentBaseListSelItem valSel;
	valSel.dwDataKey =  -1;
	UIManagePtr->SetPropertyValue( valSel, m_strLstTemp, m_pWndTree);
	UIManagePtr->SetPropertyValue( valSel, m_strLstAddrGrp, m_pWndTree);
	UIManagePtr->SetPropertyValue( valSel, m_strLstAddr, m_pWndTree);

	UIManagePtr->LoadScheme("SchmDisable",m_pWndTree,   "", false  );
	UIManagePtr->LoadScheme("SchmHideAllLst",m_pWndTree ,  "", false  );
	UIManagePtr->LoadScheme("SchmShowTempLst",m_pWndTree ,  "", false  );
   
    UpdateTempInfoDlg();
    UIManagePtr->LoadScheme( "SchmHideEditBtn", m_pWndTree, m_strBtnEdit );

    UIManagePtr->LoadScheme( "", m_pWndTree );

	UIManagePtr->ShowWindow( g_stcStrConftempEdtDlg, false );
}

void CConftempEdtLogic::SetTempSubList()
{
    //�����б�ƫ����Ϊ0
    Value_TransparentBaseListOffset val;
    val.nOffset = 0; 
    UIManagePtr->SetPropertyValue( val, m_strLstAddrGrp, m_pWndTree );
    UIManagePtr->SetPropertyValue( val, m_strLstAddr, m_pWndTree );
    UIManagePtr->SetPropertyValue( val, m_strLstPollCns, m_pWndTree );
    UIManagePtr->SetPropertyValue( val, m_strLstCns, m_pWndTree );
    UIManagePtr->SetPropertyValue( val, m_strLstSecondaryCns, m_pWndTree );

    //�����б���ѡ����
    Value_TransparentBaseListSelItem valSel;
    valSel.dwDataKey = -1;
    UIManagePtr->SetPropertyValue( valSel, m_strLstAddrGrp, m_pWndTree );
    UIManagePtr->SetPropertyValue( valSel, m_strLstAddr, m_pWndTree );
    UIManagePtr->SetPropertyValue( valSel, m_strLstPollCns, m_pWndTree );
    UIManagePtr->SetPropertyValue( valSel, m_strLstCns, m_pWndTree );
    UIManagePtr->SetPropertyValue( valSel, m_strLstSecondaryCns, m_pWndTree );
}

bool CConftempEdtLogic::BtnSaveToFileClick( const IArgs & arg )
{
    return  UIManagePtr->SaveToFile( g_stcStrConftempEdtDlg  );   
}

bool CConftempEdtLogic::BtnSavePollMenueToFileClick( const IArgs & arg )
{
   return  UIManagePtr->SaveToFile( m_strDlgPollManageMenu );   
}

bool CConftempEdtLogic::CloseDlg( const IArgs & arg  )
{
    return UIManagePtr->ShowWindow( g_stcStrConftempEdtDlg, false);
}


// ����: ����½� 
bool CConftempEdtLogic::OnBtnNewClick( const IArgs & arg  )
{   
    TplArray<TTPConfTemplate>* pLsit = BusinessManagePtr->GetConfTemplateList();
    if ( pLsit != NULL )
    {
        if ( pLsit->Size() >= CONFTEMPLATE_MAX_COUNT )
        {  
            Args_MsgBox msgArg;
	        msgArg.pOwnerWnd = m_pWndTree->GetItemData()->pWnd;
            CString str;
            str.Format("��ǰ����ģ������Ѵﵽ���ֵ%d������ɾ������ģ�������ӡ�",CONFTEMPLATE_MAX_COUNT);

            MSG_BOX_PROMPT( str , &msgArg);
            return false;
        }

    }

    bool re = CheckLocalCnsInLst();
    if ( !re )
    {
        return false;
    }


    m_tConfTempSel.InvalidConfTemp(); 
    m_tConfTempSel.m_wDefaultChairMan = 0 ;
    m_tConfTempSel.m_tTurnList.m_wInterval = 20;
     
    ShowConfinfo();
    IArgs *p = NULL; 

    UPdateTempInfoEdtWnd();
    OnBtnEdtClick(*p); 
    return true;
}

//����༭��ť
bool CConftempEdtLogic::OnBtnEdtClick( const IArgs & arg  )
{   
  
  bool re =  CheckLocalCnsInLst();
  if ( !re )
  {
      return false;
  }

   UIManagePtr->LoadScheme("SchmEnable",m_pWndTree); 
   UPdateTempInfoEdtWnd(); 

   m_bEdtState = TRUE; 
   UPdateTempInfoLst(); 

   //���µ�ǰ��ʾ���б�
   UpDateShowInfo();
   return true;
}


//������水ť
bool CConftempEdtLogic::OnBtnSaveClick( const IArgs & arg  )
{     
    Args_MsgBox argMsg;
    argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr(  m_strDlgConfInfo,m_pWndTree  ); 

    String str;
    //conf name
    UIManagePtr->GetCaption( m_strEdtConfName,str,m_pWndTree);
    if ( str.empty() )
    {
        //HANDLE_ERROR( ERR_CMS_CONFTEMP_ALIARS_EMPTY );
        CString strErr = GET_ERR_STRING( ERR_CMS_CONFTEMP_ALIARS_EMPTY );
        
        MSG_BOX_PROMPT( strErr,&argMsg );
        return false;
    } 
    else if ( IsAllNumber( str ) )
    {
        MSG_BOX_PROMPT( "������������ȫ��Ϊ����",&argMsg ); 
        return false;
    }
    else if ( !IsValidTPStr( str ) )
    {
		CString str; 
		str.Format("�����������԰����ո������е������ַ� [ %s ]",INVALID_ALIAS_FOR_SHOW)  ;
		MSG_BOX_PROMPT( str ,&argMsg ); 
        
        return false;
    }
   

    _snprintf( m_tConfTempSel.m_achConfName,sizeof(m_tConfTempSel.m_achConfName),"%s" , str.c_str() );
    
    
    //conf E164
    UIManagePtr->GetCaption( m_strEdtConfE164,str,m_pWndTree);
    if (!str.empty())
    { 
        _snprintf( m_tConfTempSel.m_achConfE164,sizeof(m_tConfTempSel.m_achConfE164),"%s" , str.c_str() );
    }
    else
    {
        _snprintf( m_tConfTempSel.m_achConfE164,sizeof(m_tConfTempSel.m_achConfE164),"" ); 
    }
    

    //���᳡������Ϊ��
    UIManagePtr->GetCaption( m_strEdtPrimaCnsName, str, m_pWndTree );
    if ( str.empty() )
    {
       MSG_BOX_PROMPT( "�������ģ��ʧ�ܣ�δ��ȡ�����᳡",&argMsg ); 
       return false;
    }

    u16 re = BusinessManagePtr->CheckConfTemplateValidate(m_tConfTempSel);
    if ( re != NO_ERROR )
    { 
        //HANDLE_ERROR(  re );
        CString strErr = GET_ERR_STRING( re ); 
        
        MSG_BOX_PROMPT( strErr,&argMsg );
        return false; 
    }
    
    if ( m_tConfTempSel.m_wDefaultChairMan == INVALID_WORD )
    {
        m_tConfTempSel.m_wDefaultChairMan = 0; 
    }
    
   
 
    UIManagePtr->GetCaption( m_strEdtPollIntv,str,m_pWndTree); 
    int nInterval = atol(str.c_str());
    if ( nInterval < 5  || nInterval>3600 )
    {
        CString strErr = "��ѯ���Ӧ�� 5 ~ 3600 ֮������� ";
        Args_MsgBox argMsg;
        argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr( m_strDlgConfInfo,m_pWndTree );
        
        MSG_BOX_PROMPT( strErr,&argMsg );
        return false; 

    }
    m_tConfTempSel.m_tTurnList.m_wInterval = nInterval;
    

    u16 wRe = BusinessManagePtr->ModifyConfTemplate( m_tConfTempSel );
    if ( wRe != NO_ERROR )
    {
        //HandleErr( wRe );
        CString strErr = GET_ERR_STRING( re );
        Args_MsgBox argMsg;
        argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr(  m_strDlgConfInfo,m_pWndTree  ); 
        MSG_BOX_PROMPT( strErr,&argMsg );
        return false;
    }

    m_bEdtState = FALSE; 
    UIManagePtr->LoadScheme("SchmDisable",m_pWndTree );
    UpDateShowInfo();
    return true;
}


//���ȡ����ť
bool CConftempEdtLogic::OnBtnCancleClick( const IArgs & arg )
{  
    
    m_bEdtState = FALSE; 
    SetTempSubList();
    UIManagePtr->LoadScheme("SchmDisable",m_pWndTree );
    if ( m_tConfTempSel.m_wID != INVALID_WORD )
    {
        m_tConfTempSel = *((TCMSConfTemplate*)(BusinessManagePtr->GetConfTemplateByID( m_tConfTempSel.m_wID )));
    }
    else
    {
         BusinessManagePtr->InvalidConfTemp(m_tConfTempSel);
         m_tConfTempSel.m_tTurnList.m_wInterval = 20;

         //��ȡ��ǰѡ����
         Value_TransparentBaseListSelItem val; 
         UIManagePtr->GetPropertyValue( val, m_strLstTemp, m_pWndTree );
         if ( val.pSelItem != NULL )
         {
             const IData* userData  = val.pSelItem ->GetUserData();
             try
             {
                 if ( const  Data_ConfTemp *pData = dynamic_cast<const Data_ConfTemp*>(userData) )
                 {
                     m_tConfTempSel = pData->m_tCmsConfTemp;
                 }
             }
             catch (...)
             {
             	
             }
             
         }
         else
         {//���ر༭��ť
            UIManagePtr->LoadScheme( "SchmHideEditBtn", m_pWndTree, m_strBtnEdit );
         }
    }  
    
    UpDateShowInfo();
    UpdateTempInfoDlg();
    return true;
}




/**	 
* ����: �������ʾ������Ϣbtn
* @return  bool
* @remarks ȡ������ģ����޸�
*/
bool CConftempEdtLogic::OnBtnShowConfinfoClick( const IArgs & arg  )
{   
   if ( m_emShowInfo!= emDlgShowConfInfo )
   {
       UIManagePtr->LoadScheme("SchmShowConfInfoDlg",m_pWndTree);
       m_emShowInfo = emDlgShowConfInfo;
       UpDateShowInfo();
   } 
   else
   {
       UIManagePtr->LoadScheme("SchmShowPollDlg",m_pWndTree);
       m_emShowInfo = emDlgShowPollInfo;
       UpDateShowInfo();
   }
   
   return true;
}


void  CConftempEdtLogic::ShowConfinfo()
{   
    if ( m_emShowInfo!= emDlgShowConfInfo )
    {
        UIManagePtr->LoadScheme("SchmShowConfInfoDlg",m_pWndTree);
        m_emShowInfo = emDlgShowConfInfo; 
   } 
}

/**	 
* ����: �������ʾ��ѯ��Ϣbut
* @return  bool
* @remarks ȡ������ģ����޸�
*/
bool CConftempEdtLogic::OnBtnShowPollClick( const IArgs & arg  )
{
    if ( m_emShowInfo != emDlgShowPollInfo )
    {
        UIManagePtr->LoadScheme("SchmShowPollDlg",m_pWndTree);
        m_emShowInfo = emDlgShowPollInfo;
        UpDateShowInfo();
    }
    else
    {
        UIManagePtr->LoadScheme("SchmShowConfInfoDlg",m_pWndTree);
        m_emShowInfo = emDlgShowConfInfo;
        UpDateShowInfo();
    }
    
    return true;
}


//�����ʾ��ַ����ť
bool CConftempEdtLogic::OnBtnShowAddrClick( const IArgs & arg  )
{   
    Value_WindowVisible val;
    UIManagePtr->GetPropertyValue( val, m_strLstAddr,m_pWndTree);
    if ( !val.bVisible )
    {
        UIManagePtr->LoadScheme("SchmHideAllLst",m_pWndTree);
        UIManagePtr->LoadScheme("SchmShowAddr",m_pWndTree);
    }
 return true;   
}

//�����ʾ��ַ�����鰴ť
bool CConftempEdtLogic::OnBtnShowAddrGrpClick( const IArgs & arg  )
{
    Value_WindowVisible val;
    UIManagePtr->GetPropertyValue( val, m_strLstAddrGrp,m_pWndTree);
    if ( !val.bVisible )
    {
        UIManagePtr->LoadScheme("SchmHideAllLst",m_pWndTree);
        UIManagePtr->LoadScheme("SchmShowAddrGrp",m_pWndTree);
    }
  return true;
}


bool CConftempEdtLogic::OnBtnAddAllCnsToPollClick( const IArgs & arg  )
{
    
    m_tConfTempSel.ClearPollLst();
    m_tConfTempSel.AddPollAllCns();

    //ƫ������0
    //�����б�ƫ����Ϊ0
    Value_TransparentBaseListOffset val;
    val.nOffset = 0;
    UIManagePtr->SetPropertyValue( val, m_strLstCns, m_pWndTree );

    UpdateTempInfoDlg();
    return true;
}



 
bool CConftempEdtLogic::OnBtnClearPollClick( const IArgs & arg  )
{
    m_tConfTempSel.ClearPollLst(); 

    //�����б�ƫ����Ϊ0
    Value_TransparentBaseListOffset val;
    val.nOffset = 0;
    UIManagePtr->SetPropertyValue( val, m_strLstPollCns, m_pWndTree );

    UpdateTempInfoDlg();
    return true;
}
 


//ˢ�»���ģ���б�֪ͨ
HRESULT CConftempEdtLogic::OnRefreshConftempLstNotify( WPARAM wparam, LPARAM lparam)
{  
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }

    TplArray<TTPConfTemplate>* pTplConftempLst = BusinessManagePtr->GetConfTemplateList();
    if (  pTplConftempLst != NULL )
    {
        //ˢ�»���ģ���б�
        vector<string> vcIconitem;
        vcIconitem.push_back("ImageItemConftempDelete");
        Value_TouchListConfTemp touchListConfTemp( pTplConftempLst, "CConftempEdtLogic::OnTempItemClick",&vcIconitem ,FALSE);
        touchListConfTemp.m_pAryConfTemplate = BusinessManagePtr->GetConfTemplateList();
        touchListConfTemp.m_bShowAll = TRUE;
        UIManagePtr->SetPropertyValue( touchListConfTemp , m_strLstTemp ,m_pWndTree );  
        
        TTPConfTemplate* p = BusinessManagePtr->GetConfTemplateByID( (u16)wparam );
        
        if ( !m_bEdtState && strlen(m_tConfTempSel.m_achConfName) > 0  )
        {    
            if ( p == NULL && m_tConfTempSel.m_wID != INVALID_WORD && m_tConfTempSel.m_wID == (u16)wparam)
            {//��ǰѡ�е�ģ�屻ɾ��
                m_tConfTempSel.InvalidConfTemp();
             
                IArgs *arg = NULL;
                UnSelConfTemp( *arg );
            }
            else if ( p != NULL && m_tConfTempSel.m_wID == INVALID_WORD && strcmp( m_tConfTempSel.m_achConfName, p->m_achConfName ) == 0 )
            {// �½�ģ��
                m_tConfTempSel = *p ; 

                Value_TransparentBaseListSelItem val;
                val.dwDataKey = m_tConfTempSel.m_wID;
                UIManagePtr->SetPropertyValue( val, m_strLstTemp, m_pWndTree);

            }
           
            UpdateTempInfoDlg();  
        }
    } 
    return NO_ERROR;
}
 
/*
//����ģ��������
enum EmTpConfTemplateRet
{
TP_ConfTemplate_UnKonw,
TP_ConfTemplate_AddSuccess,
TP_ConfTemplate_DelSuccess,
TP_ConfTemplate_UpdateSuccess,
TP_ConfTemplate_MaxNum,				//ģ��������������
TP_ConfTemplate_E164Repeat,			//e164�����ظ�
TP_ConfTemplate_UnFindConf,			//δ�ҵ���Ŀ
TP_ConfTemplate_ParamInValid,		//��������
};
*/
HRESULT CConftempEdtLogic::OnOperateTempRet( WPARAM wparam, LPARAM lparam)
{
    EmTpConfTemplateRet re =  (EmTpConfTemplateRet )wparam;
    u16 wTempID = (u16)lparam;

    bool bNeedUpdateSelItem = false;
    switch ( re )
    {
    case TP_ConfTemplate_AddSuccess:
    case TP_ConfTemplate_UpdateSuccess:
        
        break;
    case TP_ConfTemplate_DelSuccess:
        if ( m_tConfTempSel.m_wID == wTempID && !m_bEdtState)
        {
            m_tConfTempSel.Clear();
            UpdateTempInfoDlg();
        }
        break;
    case TP_ConfTemplate_MaxNum:
        ShowPopMsg( "�޸Ļ���ģ��ʧ�ܣ��ѵ���������"); 
        break;
    case TP_ConfTemplate_E164Repeat:
        ShowPopMsg( "�޸Ļ���ģ��ʧ�ܣ�E164���ظ�"); 
        
        break;
    case TP_ConfTemplate_UnFindConf:
        ShowPopMsg( "�޸Ļ���ģ��ʧ�ܣ�δ�ҵ�����Ŀ");  
        break;
    case TP_ConfTemplate_ParamInValid:
        ShowPopMsg( "�޸Ļ���ģ��ʧ�ܣ���������");  
        break;
    case TP_ConfTemplate_UnKonw:
        ShowPopMsg( "�޸Ļ���ģ��ʧ�ܣ�δ֪����");  
        break;
    default:
        break;
    }
    
    
    return NO_ERROR; 
   
}
//����ģ����Ϣ����
void CConftempEdtLogic::UpdateTempInfoDlg()
{
    
    UPdateTempInfoEdtWnd();
   
    UPdateTempInfoLst(); 
}


//���»���ģ����Ϣ������б�
void CConftempEdtLogic::UPdateTempInfoLst()
{
    //ˢ�»᳡�б�,�����ڱ༭״̬������ʾ�Ҳ���ʾ�Ľ���Ϊ��ѯ��Ϣ�����ʱ�������,������ = cns�б� - ���᳡cns - ��ѯ�б���cns  
    if ( m_bEdtState )
    { 
        TEpAddrList tCnsLst = GetCnsLstExceptPoll(); 
        ARRAY<String> vctSubItem; 
        vctSubItem.push_back("ImageItemConftempCnsAddToPoll");
        Value_TouchListTempCns touchListCns( tCnsLst, "",&vctSubItem,TRUE ); 
        touchListCns.m_wChairManID =  m_tConfTempSel.m_wDefaultChairMan;
        UIManagePtr->SetPropertyValue( touchListCns ,m_strLstCns ,m_pWndTree );
    } 
    
    //----------������Ϣ����  
    //ˢ��cns�ֻ᳡�б�  
    Value_TouchListTempCns touchListConfCns( m_tConfTempSel.m_atEpList, "",NULL,FALSE ); 
    ARRAY<String> vctSubItem;    
    if ( m_bEdtState )
    {    
        vctSubItem.push_back("ImageItemConftempCnsDelete");
    }
    touchListConfCns.m_pVctSubItem = &vctSubItem;
    touchListConfCns.m_wChairManID = m_tConfTempSel.m_wDefaultChairMan;
    UIManagePtr->SetPropertyValue( touchListConfCns ,m_strLstSecondaryCns ,m_pWndTree );
    
    //------ˢ����ѯ��Ϣ����  
    //��ѯ�б� 
    ARRAY<String> arryItemName;
    String strClickItem = "";
    if ( m_bEdtState )
    {   
//         arryItemName.push_back("ImageItemConftempPollDrag"); 
//         strClickItem = "CConftempEdtLogic::OnPollItemClick"; 
    } 
    
    BOOL32 bDrag = m_bEdtState; 
    Value_TouchListTempPoll val( m_tConfTempSel , strClickItem,&arryItemName,bDrag); 

    if ( m_bEdtState )
    {    
        val.m_strClickItemFunc = "CConftempEdtLogic::OnPollItemClick";
    } 

    UIManagePtr->SetPropertyValue(val,m_strLstPollCns,m_pWndTree);  
}


bool CConftempEdtLogic::UnSelConfTemp( const IArgs & arg  )
{
    m_tConfTempSel.InvalidConfTemp(); 
    UpdateTempInfoDlg();
    UIManagePtr->LoadScheme( "SchmHideEditBtn", m_pWndTree, m_strBtnEdit );
    return true;
}

//���»���ģ����Ϣ����ı༭��
void CConftempEdtLogic::UPdateTempInfoEdtWnd()
{  
    
    if ( m_bEdtState )
    {
        return ;
    }
    //----------������Ϣ���� 
    //������       
    Value_WindowCaption captVal;
    captVal.strCaption = m_tConfTempSel.m_achConfName;
    UIManagePtr->SetPropertyValue( captVal, m_strEdtConfName ,m_pWndTree);
    
    captVal.strCaption = m_tConfTempSel.m_achConfE164;
    UIManagePtr->SetPropertyValue( captVal,m_strEdtConfE164, m_pWndTree);  
    
    //���᳡��
    captVal.strCaption = "";
    TEpAddr * pEp = m_tConfTempSel.GetCnsAddrByID( m_tConfTempSel.m_wDefaultChairMan );
    if ( pEp != NULL )
    {
         captVal.strCaption = pEp->m_tAlias.m_abyAlias;  
    } 
    UIManagePtr->SetPropertyValue( captVal, m_strEdtPrimaCnsName,m_pWndTree );
    
    
    //------ˢ����ѯ��Ϣ����  
    //��ѯ���  
    captVal.strCaption = CPropertyHelp::DWORDToString(m_tConfTempSel.m_tTurnList.m_wInterval);
    UIManagePtr->SetPropertyValue( captVal, m_strEdtPollIntv, m_pWndTree);
    
}
 
//������ര����ʾ������
void CConftempEdtLogic::UpDateShowInfo()
{
    UIManagePtr->LoadScheme("SchmHideAllLst",m_pWndTree);
    if ( !m_bEdtState )
    {
        //����������ʾ����ģ���б�  
        UIManagePtr->LoadScheme("SchmShowTempLst",m_pWndTree);
        return;
    }

    //���������ʾ��ַ��
   if ( m_emShowInfo == emDlgShowConfInfo )
   { 
       //��ʾ��ַ���б�
       UIManagePtr->LoadScheme("SchmShowAddr",m_pWndTree);
       
   }
   else
   {//���������ʾ�᳡�б� 
       UIManagePtr->LoadScheme( "SchmShowCnsLst",m_pWndTree ); 
   } 
 
}


//��ȡcns�᳡�б����б��в��������ػ᳡������ѯcns
TEpAddrList CConftempEdtLogic::GetCnsLstExceptPoll( )
{    
    TEpAddrList  tAddr;
    TTPCnsInfo tCnsInfo;
    BusinessManagePtr->GetLocalCnsInfo( tCnsInfo);
    for ( u16 i = 0 ; i< m_tConfTempSel.m_atEpList.m_wNum; i++ )
    {   
        bool bAdd = true;

       if ( !strcmp( m_tConfTempSel.m_atEpList.m_tCnsList[i].m_tAlias.m_abyAlias,tCnsInfo.m_achRoomName ) )
       {
           continue;
       } 

        for ( u16 j = 0; j < m_tConfTempSel.m_tTurnList.m_wNum; j++ )
        {    
            if( m_tConfTempSel.m_atEpList.m_tCnsList[i].m_wEpID == m_tConfTempSel.m_tTurnList.m_awList[j] )
            {  
                bAdd = false;
                break;
            }
            
        }
       
        if ( bAdd )
        {
            tAddr.Add( m_tConfTempSel.m_atEpList.m_tCnsList[i].m_tAlias.m_byType,
                m_tConfTempSel.m_atEpList.m_tCnsList[i].m_tAlias.m_abyAlias);
             tAddr.m_tCnsList[tAddr.m_wNum-1].m_wEpID = m_tConfTempSel.m_atEpList.m_tCnsList[i].m_wEpID;
        }
        
    }

    return tAddr;
}

HRESULT CConftempEdtLogic::OnUpdateAddrBook( WPARAM wparam, LPARAM lparam)
{
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }
   UpdateAddrList();
   UpdateAddrGrpList();
   return NO_ERROR;
}

void CConftempEdtLogic::UpdateAddrList()
{   
	m_vctAddrList.clear();	
	m_vctAddrList = *ComInterface->GetLocalAddrList();

    ARRAY<String> vctSubItem;
    vctSubItem.push_back("ImageItemConftempAddrToCns");
    Value_TouchListAddr touchListAddr( &m_vctAddrList, &vctSubItem );
    UIManagePtr->SetPropertyValue( touchListAddr , m_strLstAddr, m_pWndTree ); 
}


void CConftempEdtLogic::UpdateAddrGrpList()
{  
	m_vctGroupList.clear();	
	m_vctGroupList = *ComInterface->GetAddrGroupList();

    ARRAY<String> vctSubItem;
    vctSubItem.push_back("ImageItemConftempAddrGrpToCns");
    Value_TouchListAddr touchListAddr( &m_vctGroupList, &vctSubItem );
    UIManagePtr->SetPropertyValue( touchListAddr ,m_strLstAddrGrp, m_pWndTree ); 
    
}

 