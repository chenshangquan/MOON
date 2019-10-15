// sysconfig.h: interface for the CSysConfig class.
//
//////////////////////////////////////////////////////////////////////
#if !defined(AFX_SYSCONFIG_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
#define AFX_SYSCONFIG_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "rkcSession.h"

class CSysConfig : public CSysConfigIF 
{  
    friend class CRkcSession;
/** @defgroup  �����û��ӿ�ʵ�ֲ���
 *  @{
 */
public:

    CSysConfig( CRkcSession &cSession );
	virtual ~CSysConfig();

	//������������
	virtual const TTPEthnetInfo& GetEthnetCfg() const;

	/** 
	* ����  �����Ƶ��ʽ����
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 SetOutPortTypeCmd( EmTPDVIOutPortType emDVIOutPortType, EmTPMOONOutMode emMOONOutMode );

	/** 
	* ���� ͼƬ��ת��ʽ����
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	virtual u16 SetImageAdjustCmd( EmTPImageAdjust emImageAdjust );

	virtual u16 UpdateEthnetCfg( const TTPEthnetInfo& cfg );

	virtual	u16 SetBaudRateCmd( EmTPLVDSBaud emBaudRate );

protected:
 
	virtual void DispEvent(const CMessage &cMsg);
	
    virtual void OnTimeOut(u16 wEvent); 

    void OnLinkBreak(const CMessage& cMsg);

	void OnSoftWareVerInfoNty(const CMessage& cMsg);

	void OnCamOutputInfoNty(const CMessage& cMsg);

	void OnCamImageAdjustNty(const CMessage& cMsg);

	void OnEthnetInfoInd(const CMessage& cMsg);

	void OnCamOutputInfoInd(const CMessage& cMsg);

	void OnCamImageAdjustInd(const CMessage& cMsg);

	void OnLVDBaudInd( const CMessage& cMsg );
	
	void OnLVDBaudNty( const CMessage& cMsg );

private:
 
	/**
    * ����:	  ע����Ϣ��Ӧ����
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void  BuildEventsMap();
   
private:
	CRkcSession *m_pSession; 
	TTPEthnetInfo m_tEthnetInfo;       //������Ϣ
/** @}*/ // �����û��ӿ�ʵ�ֲ���
};

#endif // !defined(AFX_USERCTRL_H__EB116E65_7B63_4B3E_B267_9C0B112DA0C1__INCLUDED_)
