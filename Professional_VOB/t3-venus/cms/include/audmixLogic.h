// audmixLogic.h: interface for the CAudmixLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUDMIXLOGIC_H__CA9844A6_5C1C_4D7A_B85B_B2EF515B850E__INCLUDED_)
#define AFX_AUDMIXLOGIC_H__CA9844A6_5C1C_4D7A_B85B_B2EF515B850E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

#define  MAX_AUD_MIX_COUNT 4
struct TAudMixCtrls 
{
    String strEdtMem;                           //������Ա�༭��
    String strRadioSpokes;                      //���Ի᳡ ѡ�ť
    u16 wCnsID;                                 //��Ӧ��cnsID

	TAudMixCtrls()
	{
		strEdtMem = "";
		strRadioSpokes = "";
		wCnsID = TP_INVALID_INDEX;
	}
};

class CAudmixLogic : public CWndLogicBase  
{
public:
    static CAudmixLogic* GetLogicPtr(); 
	CAudmixLogic();
	virtual ~CAudmixLogic();
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

	bool OnBtnSwitchAudMixClick( const IArgs & arg );

	/**	 
	* ����:  ��������
	* @return  bool
	* @remarks  
	*/
	void StartAudMix();

	/**	 
	* ����: �رջ���
	* @return  bool
	* @remarks  
	*/
	void StopAudMix();

	/**	 
	* ����: ���»����б�
	* @return  bool
	* @remarks  
	*/
	bool UpdateAudMixLst();


	bool OnBtnEdtAudMix1( const IArgs & arg );
	bool OnBtnEdtAudMix2( const IArgs & arg );
	bool OnBtnEdtAudMix3( const IArgs & arg );
	bool OnBtnEdtAudMix4( const IArgs & arg );
	bool OnDelEdtAudMix1( const IArgs & arg );
	bool OnDelEdtAudMix2( const IArgs & arg );
	bool OnDelEdtAudMix3( const IArgs & arg );
	bool OnDelEdtAudMix4( const IArgs & arg );
	bool OnBtnRadioSpeak1( const IArgs & arg );
	bool OnBtnRadioSpeak2( const IArgs & arg );
	bool OnBtnRadioSpeak3( const IArgs & arg );
	bool OnBtnRadioSpeak4( const IArgs & arg );

	bool OnAddToAudMixList( const IArgs& args );

	bool OnDragEnd( const IArgs& args );

	bool OnEdtKillFocus( const IArgs& args );

	bool OnDragOverEdit( const IArgs& args );

	bool OnDragLeaveEdit( const IArgs& args );

	/**	 
	* ����: ���»����б�
	* @return  bool
	* @remarks  
	*/
	void UpdateCnsList();

	/**	 
	* ����:  ���  ���浱ǰ������Ϣ���ļ�
	* @return  bool
	* @remarks  
	*/
	bool BtnSave2File( const IArgs & arg );

	bool  CloseDlg( const IArgs & arg );
protected: 
    virtual void RegMsg(); 
    virtual void UnRegMsg();


	void OprAudMixCtrl( int nIndex, EmDisListOprType emOprType );

	/**	 
	* ����:  �᳡�Ƿ��ڻ����ؼ���
	* @return  bool
	* @remarks  
	*/
	BOOL IsInAudMixCtrl( u16 wCnsId );

	BOOL IsAudMixListEmpty();
	void ClearAudMixCtrl();

    HRESULT RefreshAudMixList( WPARAM wparam, LPARAM lparam );
	HRESULT OnRefreshCnsList( WPARAM wparam, LPARAM lparam );
    HRESULT OnConfStateNotify( WPARAM wparam, LPARAM lparam );

private:
    BOOL   m_bAudSwitchOn;
    int    m_nSelRadioSpeak;
	int    m_nSelEdit;
	int    m_nDragSelEdit;     //��¼��קoverʱ��ѡ����
	
    static CAudmixLogic *m_pLogic;  
    static const String m_strCnsLst;         //cns �б�
    static const String m_strDlgAudmixSet;   //�������ý���
	static String m_strBtnAudSwitch;
    static TAudMixCtrls m_tCtrlAudmixArray[MAX_AUD_MIX_COUNT];             //�����ؼ�
    
};

#endif // !defined(AFX_AUDMIXLOGIC_H__CA9844A6_5C1C_4D7A_B85B_B2EF515B850E__INCLUDED_)
