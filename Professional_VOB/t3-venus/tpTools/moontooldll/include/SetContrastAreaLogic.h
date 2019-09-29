/*****************************************************************************
ģ����      : CSetContrastAreaLogic
�ļ���      : SetContrastAreaLogic.h
����ļ�    : 
�ļ�ʵ�ֹ���: ���öԱ��������
����        : �����
�汾        : V1.0  Copyright(C) 2017-2018 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2017/04/25     1.0         �����      ����
******************************************************************************/
// SetContrastAreaLogic.h: interface for the CSetContrastAreaLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SETCONTRASTAREALOGIC_H__E6D544B7_DA04_4D05_BCB4_10015F3DDCBC__INCLUDED_)
#define AFX_SETCONTRASTAREALOGIC_H__E6D544B7_DA04_4D05_BCB4_10015F3DDCBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class Data_BtnInfo : public IData
{
public:
	Data_BtnInfo() : IData( "BtnInfo" ){}
    Data_BtnInfo( int Btntype ) : IData( "BtnInfo" ), m_dwBtnInfo( Btntype ){}
    
	IData* Clone()
    {
        Data_BtnInfo* pData = new Data_BtnInfo( m_dwBtnInfo );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
	
    int m_dwBtnInfo;
};

class CSetContrastAreaLogic: public CLogicBase,public ISingleTon<CSetContrastAreaLogic>
{
public:
	CSetContrastAreaLogic();
	virtual ~CSetContrastAreaLogic();

public:
	/** ����:  ע��ص�����
	*  @param[in] 
	*  @return 
	*  @remarks  �ڶ�ȡxml�ļ�ʱ��,���������ע��ĺ���
	*/
	virtual void RegCBFun();
	/** ����:  ��ע��ص�����
	*  @param[in] 
	*  @return 
	*  @remarks  �����溯���෴,ע��ע��ĺ���
	*/
	virtual void UnRegFunc();
	/** ����:  ��ʼ������
	*  @param[in] 
	*  @return 
	*  @remarks  �ڶ�ȡxml�ļ�ʱ�����,������������ݳ�ʼ������
	*/	
    virtual bool InitWnd( const IArgs & arg ); 

   /**	 
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

public:

	bool OnBtnClose( const IArgs & arg );

	bool OnEndDragBtn( const IArgs & arg );

	/** ����: ���þ��������Ƿ���ʾ
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/
	bool OnShowRectSwitchBtnChange( const IArgs & arg );

	//���öԱ��������ͼƬ���о����ã�û�оͿ���
	void SetContrastAreaImage( const string strFileName );

	/* ����A ���� */
	bool OnAAreaWidthEditChange( const IArgs & arg );
	bool OnAAreaWidthEditKillFocus( const IArgs & arg );
	bool OnAAreaHeightEditChange( const IArgs & arg );
	bool OnAAreaHeightEditKillFocus( const IArgs & arg );

    /* ����B ���� */
	bool OnBAreaWidthEditChange( const IArgs & arg );
	bool OnBAreaWidthEditKillFocus( const IArgs & arg );
	bool OnBAreaHeightEditChange( const IArgs & arg );
	bool OnBAreaHeightEditKillFocus( const IArgs & arg );

	/* ����C ���� */
	bool OnCAreaWidthEditChange( const IArgs & arg );
	bool OnCAreaWidthEditKillFocus( const IArgs & arg );
	bool OnCAreaHeightEditChange( const IArgs & arg );
	bool OnCAreaHeightEditKillFocus( const IArgs & arg );

	/* ����D ���� */
	bool OnDAreaWidthEditChange( const IArgs & arg );
	bool OnDAreaWidthEditKillFocus( const IArgs & arg );
	bool OnDAreaHeightEditChange( const IArgs & arg );
	bool OnDAreaHeightEditKillFocus( const IArgs & arg );

	bool OnStartCalcBtnClick( const IArgs & arg );

public:
	
	HRESULT OnSecBoundaryNty( WPARAM wparam, LPARAM lparam );
	HRESULT OnChooseRectangleInd( WPARAM wparam, LPARAM lparam );
	
	HRESULT OnShowRectRegionInd( WPARAM wparam, LPARAM lparam );
	
	HRESULT OnCamOutputInfoNty( WPARAM wparam, LPARAM lparam );
	HRESULT OnCamOutputInfoInd( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetDefaultParamNty( WPARAM wparam, LPARAM lparam );

	HRESULT OnSetOnColorSwitchInd( WPARAM wparam, LPARAM lparam );
	
protected: 
	virtual void RegMsg(); 
	virtual void UnRegMsg();

private: 
	void UpdateEditNum(const IArgs & arg);
	void UpdateRectRegionInfo( TTPMoonRectRegion tTPMoonRectRegion );

	//void SetRectAreaValCmd( CString str, u8 byIndex );

private:

	std::vector<string>  m_vecShatShot;                          //��Ӧ������տؼ�

	//�ĸ�����Button:A B C D
	const string m_strRectA;
	const string m_strRectB;
	const string m_strRectC;
	const string m_strRectD;

	//�ĸ����εĳ���
	const string m_strRectAWidth;
	const string m_strRectAHeight;
	const string m_strRectBWidth;
	const string m_strRectBHeight;
	const string m_strRectCWidth;
	const string m_strRectCHeight;
	const string m_strRectDWidth;
	const string m_strRectDHeight;
	const string m_strShowRectSwitchBtn;                         //������ʾ����

	TTPMoonRectRegion m_tTpMoonRectRegionA;
	TTPMoonRectRegion m_tTpMoonRectRegionB;
	TTPMoonRectRegion m_tTpMoonRectRegionC;
	TTPMoonRectRegion m_tTpMoonRectRegionD;

	string m_strRectInfo[4];
	int         m_nTimes;         //�ź�Դ֡����ͬʱͼ�����ű�����һ��

	Window* m_pWnd;

};

#define SETCONTRASTAREALOGIC   CSetContrastAreaLogic::GetSingletonPtr()

#endif // !defined(AFX_SETCONTRASTAREALOGIC_H__E6D544B7_DA04_4D05_BCB4_10015F3DDCBC__INCLUDED_)
