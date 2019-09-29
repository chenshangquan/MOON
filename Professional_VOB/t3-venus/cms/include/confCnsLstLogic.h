// confCnsLstLogic.h: interface for the CConfCnsLstLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFCNSLSTLOGIC_H__51A443CE_70D3_45E4_8A90_D5E56C9450C7__INCLUDED_)
#define AFX_CONFCNSLSTLOGIC_H__51A443CE_70D3_45E4_8A90_D5E56C9450C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

enum EM_CnsShowState{
    emShowAll,
        emShowSpeaker,
        emShowMute,
        emShowQuiet,
        emShowOffLine,
        emShowDual,
    }; //ʹ�ò˵�

class CConfCnsLstLogic : public CWndLogicBase  
{
public:
    

    static CConfCnsLstLogic*  GetLogicPtr();
	CConfCnsLstLogic();
	virtual ~CConfCnsLstLogic();

    virtual bool RegCBFun();
    
    virtual bool UnRegFunc( );
    
    virtual bool InitWnd( const IArgs & arg );

 /**	 
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear();
    /**	 
  * ����:  ����뿪����
  * @return  bool
  * @remarks  
  */
   bool BtnHangupLocalCnsClick( const IArgs & arg );

  /**	 
  * ����:  ����Ҷϻ���
  * @return  bool
  * @remarks  
  */
   bool BtnHangupConfClick( const IArgs & arg );

 /**	 
  * ����:  ��� ��˷�
  * @return  bool
  * @remarks  
  */
   bool BtnMicClick( const IArgs & arg );

 /**	 
  * ����:  ��� ��˷�
  * @return  bool
  * @remarks  
  */
   bool BtnSpeakerClick( const IArgs & arg );


 /**	 
  * ����:  ��� ˫������
  * @return  bool
  * @remarks  
  */
   bool BtnDbFlowClick( const IArgs & arg );
   bool BtnStopDbFlowClick( const IArgs & arg );

 /**	 
  * ����:  ���  �᳡��ʾѡ��
  * @return  bool
  * @remarks  
  */
   bool BtnCnsShowOptnClick( const IArgs & arg );


   /**	 
  * ����:  �������Ļ᳡cns�б��е�ĳ����Ŀ
  * @return  bool
  * @remarks ����Ϊ�����ߵ�cns���򵯳����в˵����棬��Ϊ���ߵ�cns���򵯳���ز˵�����
  */
   bool BtnConfCnsItemClick( const IArgs & arg );



   /**	 
  * ����:  ���  ���浱ǰ������Ϣ���ļ�
  * @return  bool
  * @remarks  
  */
  bool BtnSave2File( const IArgs & arg );

  bool OptDlgBtnSave2File( const IArgs & arg );

  bool CloseOptDlg( const IArgs & arg  ); 

  bool CloseCnsLstDlg( const IArgs & arg  );



//--------��ʾ�᳡�б�ѡ��
   /**	 
  * ����:  �����ʾȫ���᳡
  * @return  bool
  * @remarks  
  */
   bool OnShowAllConfCnsClick( const IArgs & arg );

   /**	 
  * ����:  �����ʾ�����߻᳡
  * @return  bool
  * @remarks  
  */
   bool OnShowOfflineCnsClick( const IArgs & arg );


   /**	 
  * ����:  �����ʾ���Ի᳡
  * @return  bool
  * @remarks  
  */
   bool OnShowSpokesCnsClick( const IArgs & arg );


   /**	 
  * ����:  �����ʾ�����᳡
  * @return  bool
  * @remarks  
  */
   bool OnShowMuteCnsClick( const IArgs & arg );

   /**	 
  * ����:  �����ʾ�����᳡
  * @return  bool
  * @remarks  
  */
   bool OnShowSlienceCnsClick( const IArgs & arg );

   /**	 
  * ����:  �����ʾ˫���᳡
  * @return  bool
  * @remarks  
  */
   bool OnShowDbflowCnsClick( const IArgs & arg );


   bool  HungupConf( const IArgs & arg );

   bool  HungupLocalCns( const IArgs & arg );

   
   EM_CnsShowState GetCnsShowState() { return m_emCnsShowState; }
protected:
    
    virtual void RegMsg(); 
	virtual void UnRegMsg();
    HRESULT OnCascadeConfNotify( WPARAM wparam, LPARAM lparam);
    HRESULT OnHungupConfRsp( WPARAM wparam, LPARAM lparam);
    HRESULT OnConfStateNotify( WPARAM wparam, LPARAM lparam);
    HRESULT OnChangeSpeakerNotify( WPARAM wparam, LPARAM lparam);
    
    HRESULT OnUpdateCnsNotify( WPARAM wparam, LPARAM lparam);
    HRESULT OnRefreshCnsLstNotify( WPARAM wparam, LPARAM lparam);
    HRESULT OnSetSpeakerCnsRsp( WPARAM wparam, LPARAM lparam);
    HRESULT OnSetMuteCnsRsp( WPARAM wparam, LPARAM lparam);
    HRESULT OnSetQuietCnsRsp( WPARAM wparam, LPARAM lparam);
    HRESULT OnSetDualCnsRsp( WPARAM wparam, LPARAM lparam);
    HRESULT OnDualCnsNotify( WPARAM wparam, LPARAM lparam);
    
private:
    u16  ShowWindow( bool bShow );
    void UpdateCnsLst( BOOL bRestOffset = FALSE );
    void UpdateWnd();

    //������ʾѡ����Ϣ
    void UpdateShowOption();

    void ResetLstOffset( String strLst );
    
    void InitLst();

private:

    static const String m_strShowAllCns;
    static const String m_strShowSpeakerCns;
    static const String m_strShowMuteCns;
    static const String m_strShowQuietCns;
    static const String m_strShowOffLineCns;
    static const String m_strShowDualCns;


    static CConfCnsLstLogic *m_pLogic;
    static const String m_strStcTitle;              //�᳡�������
    static const String m_strBtnCnsShowSel;         //�᳡��ʾѡ��
    static const String m_strBtnMic;                //��˷�
    static const String m_strBtnSpeaker;            //������
    static const String m_strBtnDbFlow;             //˫��
    static const String m_strBtnHungup;             //�Ҷϻ���
    static const String m_strLstCns;                //�᳡�б�
    static const String m_strDlgCnsShowOptn;        //�᳡��ʾѡ��
    static const String m_strLstCnsShowOptn;
    EM_CnsShowState m_emCnsShowState;               //cns ��ʾ״̬
              
    
};

#endif // !defined(AFX_CONFCNSLSTLOGIC_H__51A443CE_70D3_45E4_8A90_D5E56C9450C7__INCLUDED_)
