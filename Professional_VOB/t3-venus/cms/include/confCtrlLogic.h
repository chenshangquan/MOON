// confCtrlLogic.h: interface for the CConfCtrlLogic class.
//�������в˵�����  
//�����᳡���Ʋ˵���Զ��cns�ľ��� �����ȵ����ã�
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFCTRLLOGIC_H__88CFE78B_FF1C_4A35_A5A4_77BEE3083150__INCLUDED_)
#define AFX_CONFCTRLLOGIC_H__88CFE78B_FF1C_4A35_A5A4_77BEE3083150__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"
enum EM_CallType
{
    emCallTpCfTemp,             //����һ������ģ��
    emCallTpInstantCf,          //��ʱ����
    emCallTpInvitCns,          //����ԭ�����ڻ����е�cns���
    emCallTpCallConfCns,       //���л����е��ߵ�cns
    emCallTpPtp,//��Ե�
};


 

class CConfCtrlLogic : public CWndLogicBase  
{
public:
    static CConfCtrlLogic* GetLogicPtr(); 
	CConfCtrlLogic();
	virtual ~CConfCtrlLogic();

public:  
    
    virtual bool RegCBFun();
    
    virtual bool UnRegFunc( );
    
    virtual bool InitWnd( const IArgs & arg );
    
    /**	 
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear();


    void RefreshConfCnsCtrlDlg( );

 /**	 
  * ����:  ���øõ�ԪҪ������cns����Ϣ
  * @return  bool
  * @remarks  
  */
    void SetCallInfo(   u16 wCnsID, u16 wConfID );
    
    void SetCallInfo(  u16 wConfTempID = INVALID_WORD); 

    void SetCallInfo(  TEpAddrList  &tEqAddrLst ); 

    void SetCallInfo(  TConfCallEpAddrList  &tEqAddrLst ); 

	void SetCallInfo( TTPAlias &tAlias );
 /**	 
  * ����:  ����
  * @return  bool
  * @remarks  
  */
    bool OnCallClick( const IArgs & arg );


 /**	 
  * ����:  ָ������cns
  * @return  bool
  * @remarks  
  */
    bool OnSetSpokeCnsClick( const IArgs & arg );


      /**	 
  * ����:  �������ͼ��
  * @return  bool
  * @remarks  
  */
   bool OnSetMuteClick( const IArgs & arg );


    /**	 
  * ����:  ���ȡ������ͼ��
  * @return  bool
  * @remarks  
  */
   bool OnSetUnMuteClick( const IArgs & arg );

    /**	 
  * ����:  ��� ����ͼ��
  * @return  bool
  * @remarks  
  */
   bool OnSetQuietClick( const IArgs & arg );


    /**	 
  * ����:  ��� ȡ������ͼ��
  * @return  bool
  * @remarks  
  */
   bool OnSetUnQuietClick( const IArgs & arg );

   
    /**	 
  * ����:  �������˫������
  * @return  bool
  * @remarks  
  */
   bool OnStartDualClick ( const IArgs & arg );

    /**	 
  * ����:  ����ر�˫������
  * @return  bool
  * @remarks  
  */
   bool OnStopDualClick ( const IArgs & arg );
  

/**	 
  * ����:  ����cns���
  * @return  bool
  * @remarks  
  */
   bool OnInviteCnsClick( const IArgs & arg );

 /**	 
  * ����:  ����Ҷϻ���c
  * @return  bool
  * @remarks  
  */
   bool OnHungupConfClick( const IArgs &arg);

    /**	 
  * ����:  �Ҷϻ���c
  * @return  bool
  * @remarks  
  */
   bool HungupConf( const IArgs & arg );


   /**	 
  * ����:  ����Ҷ�cns
  * @return  bool
  * @remarks  
  */ 
   bool OnHungupCnsClick( const IArgs &arg );

  
 /**	 
  * ����:   �Ҷ�cns
  * @return  bool
  * @remarks  
  */ 
   bool HungupCns( const IArgs & arg); 


  
  
   /**	 
  * ����:   �Ҷ�cns
  * param [in] strMsg Ҫ��ʾ����Ϣ
  * param [in] tCns Ҫ�Ҷϵ�cns��Ϣ
  * param [in] bShowCancle �Ƿ���ʾȡ��
  * @return  bool
  * @remarks ���ⲿ���� 
  */ 
   bool HungupLocalConf( const confID, const CString strMsg, bool bShowCancle = true, Window *pParendWnd = NULL ); 
  

   //�Ҷϱ���cns
   bool HungupLocalCns( const TConfEpID& tCns, const CString strMsg, bool bShowCancle = true ,Window *pParendWnd = NULL); 
 
   /**	 
  * ����:  ���  ���浱ǰ������Ϣ���ļ�
  * @return  bool
  * @remarks  
  */
   bool BtnSave2File( const IArgs & arg );

   bool CloseConfCnsMenuDlg( const IArgs & arg  );
   
   bool BtnSaveConfCnsMenu2FileClick( const IArgs & arg );


   bool UserDefinedFun( const IArgs & arg );

   
   void  AdjustMenuPos ( );
protected: 
    virtual void RegMsg(); 
    virtual void UnRegMsg();

    
	/**	 
	* ����:  �����˻�����ĳ��cns��Ŀ
	* @return  bool
	* @remarks  
	*/
	HRESULT OnConfCnsItemClick( WPARAM wparam, LPARAM lparam );

	 /**	 
	* ����:  �����˻���ģ���б���ĳ��ģ����Ŀ
	* @return  bool
	* @remarks  
	*/ 
	HRESULT  OnConfTempItemClick( WPARAM wparam, LPARAM lparam );

	/**	 
	* ����:  ������ַ���б���ĳ����Ŀ���к���
	* @return  bool
	* @remarks  
	*/  
	HRESULT OnAddrItemCallClick( WPARAM wparam, LPARAM lparam );


    //���������ظ�
    HRESULT OnSetSpeakerCnsRsp( WPARAM wparam, LPARAM lparam);
    HRESULT OnSetMuteCnsRsp( WPARAM wparam, LPARAM lparam);
    HRESULT OnSetQuietCnsRsp( WPARAM wparam, LPARAM lparam);
    HRESULT OnSetDualCnsRsp( WPARAM wparam, LPARAM lparam);
    HRESULT OnDualCnsNotify( WPARAM wparam, LPARAM lparam);
 
    HRESULT OnConfStateNotify( WPARAM wParam, LPARAM lParam );
    HRESULT OnConfCnsListNotify( WPARAM wParam, LPARAM lParam );
   
private:
    static CConfCtrlLogic *m_pLogic;  

    //-----����cns���������Ϣ
    // static TCnsInfo            m_tCnsInfo;    //�ò�����ԪҪ������cns��Ϣ��������cns��Ӧ�ľ��������� ��״̬ ״̬���ýṹ����confCnsLstLogic��Ԫ���и�ֵ�͸���
    static  u16                   m_wCnsID;     //Ҫ������cns��ID
    static  u16                   m_wConfID;    //��Ӧ�Ļ���ID 

    TTPAlias                     m_tTPAlias;   //���еı�����Ϣ

    TCnAddr                      m_tCallAddr;  //��Ե���еĵ�ַ

    vector<TCnAddr>              m_tCnAddrList; //��ʱ������е�ַ

    //����һ����ʱ����������Ϣ/����cns
    static TConfCallEpAddrList    m_tEqAddrLst;

    static EM_CallType           m_emCallTp;     //�������� 

    CRect       m_rectClickItem;

    String      m_strConfCnsCtrlDlg;
};

#endif // !defined(AFX_CONFCTRLLOGIC_H__88CFE78B_FF1C_4A35_A5A4_77BEE3083150__INCLUDED_)
