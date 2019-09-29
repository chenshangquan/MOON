// simulateCnsLogic.h: interface for the CSimulateCnsLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMULATECNSLOGIC_H__1CEC2AB2_3CCB_4983_9535_B9657B1395F9__INCLUDED_)
#define AFX_SIMULATECNSLOGIC_H__1CEC2AB2_3CCB_4983_9535_B9657B1395F9__INCLUDED_

#include "wndLogicBase.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//����չ��Ϣ
typedef struct tagScreenInfoEx{
	String strCtlScreen;                    //�ؼ������� 
	String strCtlScreenState;          //�ؼ�������״̬ 
    String strCtlCnsName;              //�ؼ�������ǰ�����ڲ��ŵ�cns��  
 
} TScreenInfoEx,*PTScreenInfoEx;


typedef struct tagSeatInfoEx{
	String strCtrlSeat;            //�ؼ�������ϯ
	String strCtrlSpoksBtn;    //�ؼ�����button��ָ�������� 
 
}TSeatInfoEx, *PTSeatInfoEx;

#define  MAX_SCREEN_COUNT    5
#define  MAX_SEAT_COUNT      3

class CSimulateCnsLogic: public CWndLogicBase
{ 
public:  
	static CSimulateCnsLogic* GetLogicPtr(); 
	CSimulateCnsLogic();
	virtual ~CSimulateCnsLogic();
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


	bool BtnSetSpokesman1Click( const IArgs & arg );

	bool BtnSetSpokesman2Click( const IArgs & arg );

	bool BtnSetSpokesman3Click( const IArgs & arg );

    /**	 
        * ����:  �����Ļ
        * @return  bool
        * @remarks  
	*/
    bool BtnSrcn1Click( const IArgs & arg );
    bool BtnSrcn2Click( const IArgs & arg );
    bool BtnSrcn3Click( const IArgs & arg );
   
 
 
   
protected:   
	//����״̬֪ͨ
	afx_msg HRESULT OnConfStateNotify( WPARAM wparam, LPARAM lparam );

	//��������֪ͨ
	afx_msg HRESULT OnScreenNameNotify( WPARAM wparam, LPARAM lparam );

	//��״̬����֪ͨ
	afx_msg HRESULT OnScreenStateNotify( WPARAM wparam, LPARAM lparam );
	
	//�����˸���֪ͨ
	afx_msg HRESULT OnSpokesManNotify( WPARAM wparam, LPARAM lparam );
    
 

protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();

    bool GetPosFrmArg( const IArgs & arg , CPoint &pos);
	
   
private: 

	//������״̬
	void UpdateScreenState( TScreenInfo tInfo );

	//ˢ�»᳡��
    void RefreshCnsScreen();
	
	//ˢ����ϯ
	void RefreshSpeakSeat();

 
private:

    static CSimulateCnsLogic *m_pLogic;    
	static const String   m_strConfTitle;
    static TScreenInfoEx  m_screenInfoArry[MAX_SCREEN_COUNT];       //����Ϣ     
	static TSeatInfoEx    m_seatInfoArry[MAX_SEAT_COUNT];		    //��ϯ��Ϣ  

    
    const  static String         m_strSchmActive;                   //�����
    const  static String         m_strSchmUnActive;                 //δ����
    const static String          m_strSchnCancleView;               //ȡ��ѡ��

	static String                m_BtnScreenArry[MAX_SEAT_COUNT];   //�����ɼ�����
    const static String          m_strSwitchBtnScrn1;               //
    const static String          m_strSwitchBtnScrn2;
    const static String          m_strSwitchBtnScrn3;

    u8     m_bySelScreenID;                                         //��ǰѡ�е����� 

    u8    m_byCurSpokesSeatID;						                //��ǰ������ID
	BOOL  m_bInConf;
    
};

#endif // !defined(AFX_SIMULATECNSLOGIC_H__1CEC2AB2_3CCB_4983_9535_B9657B1395F9__INCLUDED_)



    
