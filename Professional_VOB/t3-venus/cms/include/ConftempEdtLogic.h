// ConftempEdtLogic.h: interface for the CConftempEdtLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFTEMPEDTLOGIC_H__D2C43ED8_6D8A_4CCE_BF33_46B006780A91__INCLUDED_)
#define AFX_CONFTEMPEDTLOGIC_H__D2C43ED8_6D8A_4CCE_BF33_46B006780A91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CConftempEdtLogic : public CWndLogicBase  
{
public: 
    static CConftempEdtLogic* GetLogicPtr(); 
    CConftempEdtLogic();
    virtual ~CConftempEdtLogic(); 
    
public:  
    
    virtual bool RegCBFun();
    
    virtual bool UnRegFunc( );
    
    virtual bool InitWnd( const IArgs & arg );
    
     /**	 
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear() ;

   /**	 
  * ����: ����½�
  * @return  bool
  * @remarks �½�����ģ��
  */
    bool OnBtnNewClick( const IArgs & arg  );



    /**	 
  * ����: ����༭��ť
  * @return  bool
  * @remarks ��ʼ�༭����ģ��
  */
    bool OnBtnEdtClick( const IArgs & arg  );

 /**	 
  * ����: ������水ť
  * @return  bool
  * @remarks �������ģ��
  */
    bool OnBtnSaveClick( const IArgs & arg  );

    /**	 
  * ����: ���ȡ����ť
  * @return  bool
  * @remarks ȡ������ģ����޸�
  */
    bool OnBtnCancleClick( const IArgs & arg  );


    /**	 
  * ����: �������ʾ������Ϣ 
  * @return  bool
  * @remarks ȡ������ģ����޸�
  */
    bool OnBtnShowConfinfoClick( const IArgs & arg  );


    /**	 
  * ����: �������ʾ��ѯ��Ϣbut
  * @return  bool
  * @remarks ȡ������ģ����޸�
  */
    bool OnBtnShowPollClick( const IArgs & arg  );

     /**	 
  * ����: �����ʾ��ַ����ť
  * @return  bool
  * @remarks  
  */
    bool OnBtnShowAddrClick( const IArgs & arg  );

     /**	 
  * ����: �����ʾ��ַ�����鰴ť
  * @return  bool
  * @remarks  
  */
     bool OnBtnShowAddrGrpClick( const IArgs & arg  );

       /**	 
  * ����: ���������зֻ᳡����ѯ�б�
  * @return  bool
  * @remarks  
  */
     bool OnBtnAddAllCnsToPollClick( const IArgs & arg  );



          /**	 
  * ����: �������ѯ�б�
  * @return  bool
  * @remarks  
  */
     bool OnBtnClearPollClick( const IArgs & arg  );



   /**	 
  * ����: �ֻ᳡�б� ��ק����
  * @return  bool
  * @remarks  
  */
   bool OnEndDragSecdryCns( const IArgs & arg  );

    /**	 
  * ����: ����ѯ�б� ��ק��Ŀ����
  * @return  bool
  * @remarks  
  */
   bool OnEndDragPollLst( const IArgs & arg  ); 


   //�� ��ѯ�б� ��ק��Ŀ����
   bool  OnEndDragFrmPollLst( const IArgs & arg  );


//-------------����б��е���Ŀ-------------------------begin
    /**	 
  * ����: �������ģ����б��ĳ����Ŀ
  * @return  bool
  * @remarks �ѻ���ģ����Ϣ���µ���ϸ��Ϣ����
  */
    bool OnTempItemClick( const IArgs & arg  );

    /**	 
  * ����: �������ģ����б� ��Ŀ�е�ɾ��ͼ��
  * @return  bool
  * @remarks ɾ��ĳ��ͼ��
  */
    bool OnTempLstDelIcon( const IArgs & arg  );

  

    /**	 
  * ����: ɾ���ֻ᳡�б��еġ�ɾ��ͼ�ꡱ 
  * @return  bool
  * @remarks  ɾ����ѡ�ֻ᳡ 
  */
    bool OnCnsLstDelIcon( const IArgs & arg  );
    
   
  /**	 
  * ����: ����˵�ַ���еġ����ͼ�ꡱ
  * @return  bool
  * @remarks  �ѵ�ַ����ѡ�����Ŀ��ӵ��᳡�б���,
  *          �᳡�б��е�cnsID ������ɾ������ID�Ż����±�ˢ��
  */
    bool OnAddrAddIcon( const IArgs & arg  );


 /**	 
  * ����: ����˵�ַ�������еġ����ͼ�ꡱ
  * @return  bool
  * @remarks  �ѵ�ַ���з�����ѡ��ķ�����ӵ��᳡�б���
  */
    bool OnAddGrpAddIcon( const IArgs & arg  );  


    /**	 
  * ����: �����cns�ġ����ͼ�ꡱ
  * @return  bool
  * @remarks  ��cns�б���ѡ���cns��ӵ���ѯ�б���
  */
    bool OnCnsLstAddICon( const IArgs & arg  );  
 

 /**	 
  * ����: ��������ѯ�б����Ŀ 
  * @return  bool
  * @remarks   
  */
    bool OnPollItemClick(const IArgs &args );
//-------------����б��е���Ŀ-------------------------end
 
   /**	 
  * ����: ɾ����ѡ����ģ��
  * @return  bool
  * @remarks ɾ�� 
  */
   bool DelSelConfTemp( const IArgs & arg  );

   bool BtnSaveToFileClick( const IArgs & arg );
   bool BtnSavePollMenueToFileClick( const IArgs & arg );
   
   bool CloseDlg( const IArgs & arg  );
   
   
   void UpdateTempInfoDlg(); 
   
   //���»���ģ����Ϣ����ı༭��
   void UPdateTempInfoEdtWnd();

   //���»���ģ����Ϣ������б�
   void UPdateTempInfoLst();


   bool UnSelConfTemp( const IArgs & arg  );
   
protected: 
   /**	 
  * ����: ˢ�»���ģ���б�֪ͨ
  * @return  bool
  * @remarks  
  */
    afx_msg HRESULT OnRefreshConftempLstNotify( WPARAM wparam, LPARAM lparam);


    afx_msg HRESULT OnOperateTempRet( WPARAM wparam, LPARAM lparam);

    

  /**	 
  * ����: ˢ�µ�ַ��֪ͨ
  * @return  bool
  * @remarks  
  */
    afx_msg HRESULT OnUpdateAddrBook( WPARAM wparam, LPARAM lparam);
    

    
protected: 
    virtual void RegMsg(); 
    virtual void UnRegMsg();
    

    //���ݵ�ǰ����ģ����Ϣ������ʾ���ݸ��»���ģ����ʾ�����ص�����
    void UpDateShowInfo();
   
    //��ȡcns�᳡�б����б��в��������ػ᳡������ѯcns
    TEpAddrList GetCnsLstExceptPoll();
    
    //���µ�ַ���б�
    void UpdateAddrList();
    
    //���µ�ַ�������б�
    void UpdateAddrGrpList();
  
    //�ѵ�ַ����Ŀ�������ӵ�����ģ���cns�б�
    bool AddAddrToConfTempEpLst(TAddrItem* pAddrItem);

    //j��鱾��cns�Ƿ��Ѿ���ӵ�cn���б��У����û�У�����ӽ�ȥ��Ĭ����ӵ��б�ĵ�һ����Ա,��ΪĬ��Ϊ��ϯ 
    bool CheckLocalCnsInLst();


    void ShowConfinfo();

    void SetTempSubList();
private:

    //��ǰ����ģ����Ϣ��������ʾ��Ϣ
    enum EM_TempInfoDlgShow
    {
        emDlgShowConfInfo,  //��ʾ������Ϣ����
        emDlgShowPollInfo,  //��ʾ��ѯ��Ϣ����
    };

    static CConftempEdtLogic *m_pLogic;
    TCMSConfTemplate  m_tConfTempSel;                       //��ǰѡ�е���Ŀ
    BOOL32           m_bEdtState;                            //��ǰ�Ƿ��ڱ༭״̬ 
    EM_TempInfoDlgShow m_emShowInfo;                        //��ǰ����ģ����Ϣ������ʾ������

	vector<TAddrItem> m_vctAddrList;                        //��ַ����Ŀ�б�
	vector<TAddrItem> m_vctGroupList;                       //��ַ�����б�

    static const String  m_strDlgLst ;                      //�����б�Ľ���
    static const String  m_strLstTemp;                       //ģ���б�
    static const String  m_strLstCns;                        //cns�б�
    static const String  m_strBtnCreateTemp;                 //btn  �½�����ģ��
    static const String  m_strBtnShwConfInfo;                //btn  ��ʾ������Ϣ
    static const String  m_strBtnShwPollInfo;               //btn  ��ʾ��ѯ��Ϣ
    static const String  m_strBtnEdit;                       //btn  �༭
    static const String  m_strBtnSave;                      //btn  ����
    static const String  m_strBtnCancle;                    //btn  ȡ��
 
    static const String  m_strDlgInfo  ;                   //������Ϣ�ĸ�����
    static const String  m_strDlgConfInfo;                  //Dlg ������Ϣ
    static const String  m_strEdtConfName;                  //������
    static const String  m_strEdtConfE164;                   //E164
    static const String  m_strEdtPrimaCnsName;              //���᳡��
    static const String  m_strLstSecondaryCns ;              //cns�ֻ᳡�б�
    
    static const String  m_strDlgPollInfo;                   //Dlg ��ѯ��Ϣ
    static const String  m_strEdtPollIntv;                    //��ѯ���
    static const String  m_strLstPollCns;                    //cns ��ѯ�б�

    //������ര��
    static const String  m_strLstAddr ;                     //��ַ��
    static const String  m_strLstAddrGrp ;                  //��ַ������
    static const String  m_strBtnShowAddrGrp ;                  //��ʾ��ַ������
    static const String  m_strBtnShowAddr;                      //��ʾ��ַ��
    
  
    static const String  m_strDlgPollManageMenu; 
    static const String  m_strLstPollManage ;
   
};

#endif // !defined(AFX_CONFTEMPEDTLOGIC_H__D2C43ED8_6D8A_4CCE_BF33_46B006780A91__INCLUDED_)
