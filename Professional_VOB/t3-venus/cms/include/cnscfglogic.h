// cnscfglogic.h: interface for the CCnsCfgLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNSCFGLOGIC_H__B1519AAD_78A9_40FD_9ECB_83ED22AB7CDB__INCLUDED_)
#define AFX_CNSCFGLOGIC_H__B1519AAD_78A9_40FD_9ECB_83ED22AB7CDB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"


#define  MAX_CNS_SCREEN  5
struct TCnsScreenIp 
{
	String  strScreenPic;                     //屏图片
	String  strCnsScreen;                     //第几屏
	String  strScreenIP;                      //屏IP

	TCnsScreenIp()
	{
		strScreenPic = "";
		strCnsScreen = "";
		strScreenIP = "";
	}
};

class CCnsCfgLogic : public CWndLogicBase  
{
public:
	CCnsCfgLogic();
	virtual ~CCnsCfgLogic();
	static CCnsCfgLogic* GetLogicPtr();
	
public:
	virtual bool RegCBFun();
	virtual bool UnRegFunc();
	virtual void RegMsg();
	
     /**	 
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear();
		
	/**	 
	* 功能: 更新上传进度
	* @return   bool
	* @remarks  
	*/
	bool OnUploadProgress( const IArgs & arg );

	/**	 
	* 功能: 上传核心
	* @param    const String strRemotePath      [in]     linux端待存储路径
	* @param    const String strLocalFile       [in]     待传输的文件全路径 
	* @param    const String strCheckFileName   [in]     待传输的文件名 
	* @param    bAutoEnd						[in]     是否由ftp内部自己关闭ftp   默认由内部关闭
	* @return   bool
	* @remarks  
	*/
	BOOL UploadCore( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName, BOOL bAutoEnd = TRUE ); 

protected:
	bool InitWnd( const IArgs & args );

	/**
	* 功能:  打开会场条目
	* @return  bool
	* @remarks  
	*/
	bool OnOpenCnsInfo( const IArgs & args );

    bool OnCnsLstItem( const IArgs & args );


    
	/**
	* 功能:  点击保存
	* @return  bool
	* @remarks  
	*/
	bool OnSave( const IArgs& args );
	/**	 
	* 功能:  点击取消
	* @return  bool
	* @remarks  
	*/
	bool OnCancel( const IArgs& args );
	/**	 
	* 功能:  点击编辑
	* @return  bool
	* @remarks  
	*/
	bool OnEdit( const IArgs& args );

	bool OnSetMainCns( const IArgs& args );

	bool OnSysCfg( const IArgs& args );

	bool OnCfgCnsList( const IArgs& args );

	bool BtnSwitchCnsCfgClick( const IArgs& args );

	bool OnBtnCnsLevel1( const IArgs& args );

	bool OnBtnCnsLevel2( const IArgs& args );

	bool OnBtnCnsLevel3( const IArgs& args );

	bool OnCloseDlg( const IArgs& args );

	bool BtnSwitchNATClick( const IArgs& args );

	BOOL CheckAllIp();	//检查所有界面Ip变化

	bool SaveEthnetCfg( const IArgs& args );

	void ShowCnsInfo();

	void UpdateCnsLevel( EmTPSipLevel emLevel );

	LRESULT OnMainRoomNotify( WPARAM wParam, LPARAM lParam );

	LRESULT OnCnsInfoNotify( WPARAM wparam, LPARAM lparam );
	
	LRESULT UpdateEthnetInfo( WPARAM wParam, LPARAM lParam );
	
	LRESULT UpdateNatInfo( WPARAM wParam, LPARAM lParam );

private:
	vector<TTPCnsInfo>   m_vctCnsList;
	TTPCnsInfo           m_SelCnsInfo;
	EmTPSipLevel         m_emLevel;
	s8                   m_achMainCns[TP_MAX_ALIAS_LEN+1];

	EmFtpStatus m_emFileFtpStatus;
	CFtpCtrl m_cFtp;
	Window* m_pWnd;
	std::vector<String> m_vecConfFile;
	
	static CCnsCfgLogic* m_pLogic;

	static const String m_strCnsLst;         
    static const String m_strDlgCnsConfig;
	static const String m_strBtnMainCns;	
	static const String m_strStTitle;
	static const String m_strEdtCnsName;
	static const String m_strEdtCnsNumber;
	static const String m_strBtnCnsCfgSwitch;
	static const String m_strRadioProvince;
	static const String m_strRadioCity;
	static const String m_strRadioCounty;
	static const String m_strStDualIp;
	static const String m_strBtnNATSwitch;
	static const String m_strEdtNatIP;
	static const String m_strEdtIp;
	static const String m_strEdtSubMask;
	static const String m_strEdtGateWay;
	static TCnsScreenIp m_tCtrlScreenIp[MAX_CNS_SCREEN]; 
};

#endif // !defined(AFX_CNSCFGLOGIC_H__B1519AAD_78A9_40FD_9ECB_83ED22AB7CDB__INCLUDED_)
