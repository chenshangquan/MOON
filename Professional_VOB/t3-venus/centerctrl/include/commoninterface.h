// commoninterface.h: interface for the CCommonInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMONINTERFACE_H__148AE296_7426_4700_8D89_6A7ECFFE1847__INCLUDED_)
#define AFX_COMMONINTERFACE_H__148AE296_7426_4700_8D89_6A7ECFFE1847__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cnclib.h"

class CCommonInterface : public CWnd
{
public:	
	virtual ~CCommonInterface();

    /** ��ȡ�ӿ�ָ�� */
	static CCommonInterface* GetCommIF();

    /** ���ٽӿ�ָ�� */
    void DestroyCommIF();

    /**
    * ��  ��  �����Ự
    * @return ��
    */
	void CreateSession();

    /**
    * ��  �� ���ٻỰ
    * @return 
    */
	void DesdroySession();

    //���ӵ�TPad
    u16 ConnectTPad();

    //�пط���Ϣ��TPad TPad������cns����
	u16 DisConnectTpad();


/** @defgroup  �пؽӿ�
 *  @{
 */	

    u16 SetSysPower( EmSchPower emPower );

    u16 SetSysAllLight( EmSchLight emLight );

    u16 SetSysMainLight( EmSchMidLight emLight );

    u16 SetSysAuxiLight( EmSchScrLight emLight );

    u16 SelectTVMonitor( u8 byIndex );

    u16 SetTVPowerMode( u8 byIndex, EmTvPowerMode emMode );

    u16 SetTVAudVisMode( EmTVAudVisMode emMode );

    u16 SetTVDisMode( EmTVDisplayMode emMode );

    u16 SetTVInpSelect( u8 byIndex, EmTVInputSelect emSelect );
    
    TCentreTVCfg* GetCentreTVCfg();

    u16 SetDCamPower( EmDCamPower emPower );

    u16 SetDCamAFMode( EmDCamAFMode emMode );

    u16 SetDCamWBMode( EmDCamWBMode emMode );

    u16 SetDCamZoom( EmDCamZoom emZoom, EmCnAction emAction = emCnStop );

    u16 SetDCamPreset( EmDCamRecallNum emNum );

    u16 SetDCamRecall( EmDCamRecallNum emNum );

//	u16 SetAirPower( EmCentreACPower emPower );

	u16 SetACMode( EmCentreACMode emMode );

	u16 SetACTemp( u8 byTemp );

	u16 SetACAirVol( EmCentreACAirVol emAirVol );
    //�յ���Ļѡ������Ϣ
	u16 SelectAirMonitor( u8 byIndex );

	u16 GetCentreACCfg( vector<TCentreACCfg> &vecTCentreACCfg );

	u16 SetACPowerMode( u8 byIndex, EmCentreACPower emMode );
	
	u16 SetApplyToAll( u8 byIndex, BOOL* abIsCtrl );

	u16 GetApplyToAllInfo( BOOL** pIsCtrl );

	u16 SetCurtainState( BOOL* bIsCtrl, EmCurAction emCurAction );

	u16 GetCentreCurName( vector<TCentreCurName> &vecTCentreCurName );

/** @}*/

protected:
    CCommonInterface();

    DECLARE_MESSAGE_MAP()
        
    virtual BOOL PreCreateWindow( CREATESTRUCT& cs );
    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam); 

    HWND GetRecvWnd(){ return m_pMySelf->GetSafeHwnd(); }

private:
    static CCommonInterface*  m_pMySelf;

    CCnsSessionCtrlIF   *m_pCnsSession;       //cns�Ự

    CCncCenterCtrlIF    *m_pCenterCtrl;

};

#define ComInterface   CCommonInterface::GetCommIF()

#endif // !defined(AFX_COMMONINTERFACE_H__148AE296_7426_4700_8D89_6A7ECFFE1847__INCLUDED_)
