// cncsipinfoctrl.h: interface for the CCncSipInfoCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CNCSIPINFOCTRL_H__DE3450DC_3385_4C0F_8520_21D1F89F6A98__INCLUDED_)
#define AFX_CNCSIPINFOCTRL_H__DE3450DC_3385_4C0F_8520_21D1F89F6A98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cnsSession.h"

class CCncSipInfoCtrl : public CCncSipInfoCtrlIF 
{
public:
	CCncSipInfoCtrl( CCnsSession &cSession );
	virtual ~CCncSipInfoCtrl();

	/** 
	* ����  ����SIPע����Ϣ
	* @param [in]  
	* @return  
	* @remarks 
	*/
	virtual u16 ReqSipRegInfo( EmGetRegInfoType emType );

	/** 
	* ����  ��ȡCnsע����Ϣ
	* @param [in]  
	* @return  
	*/
	virtual const vector<TAddrInfo>& GetCnsRegInfo() const;

	/** 
	* ����  ��ȡUmsע����Ϣ
	* @param [in]  
	* @return  
	*/
	virtual const vector<TTPAlias>& GetUmsRegInfo() const;


protected:
    virtual void OnTimeOut(u16 wEvent); 
    virtual void DispEvent(const CMessage &cMsg);
	void BuildEventsMap();

	//��Ϣ����
	void OnRegInfoRsp(const CMessage& cMsg);
	void OnRegInfoNty(const CMessage& cMsg);

    void OnGetGkRegInfo(const CMessage& cMsg);
    void OnGetCnsRegInfo(const CMessage& cMsg);
    void OnGetUmsRegInfo(const CMessage& cMsg);

	void OnLinkBreak(const CMessage& cMsg);

private:
	CCnsSession       *m_pSession;

    vector<TAddrInfo>  m_vctGkRegInfo;
	vector<TAddrInfo>  m_vctCnsRegInfo;
	vector<TTPAlias>   m_vctUmsRegInfo;

};

#endif // !defined(AFX_CNCSIPINFOCTRL_H__DE3450DC_3385_4C0F_8520_21D1F89F6A98__INCLUDED_)
