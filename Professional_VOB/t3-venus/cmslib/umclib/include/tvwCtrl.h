// tvwCtrl.h: interface for the CTvwCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TVWCTRL_H__E4797A29_3C89_45DE_AA25_727E6705780B__INCLUDED_)
#define AFX_TVWCTRL_H__E4797A29_3C89_45DE_AA25_727E6705780B__INCLUDED_

#include "tvwCtrlIF.h"
#include "umssession.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTvwCtrl : public CTvwCtrlIF 
{  
	friend class CUmsSession;
private:
	CTvwCtrl( CUmsSession &cUmsSession );
	CTvwCtrl( const CTvwCtrl & ){};
	 
public:
     
     /**
    * ����:	 ���󲥷�
    * @param [int]  tTvwInfo�����󲥷ŵĵ���ǽ��Ϣ
    * @return    
    * @remarks  �ɹ�����0��ʧ�ܷ��ش�����
    */
    u16 PlayHduReq( const TTPHduPlayReq & tTvwInfo ) ;

     /**
    * ����:	 ֹͣ����
    * @param [int]  tTvwInfo������ֹͣ���ŵĵ���ǽ��Ϣ
    * @return    
    * @remarks  �ɹ�����0��ʧ�ܷ��ش�����
    */
    u16 StopHduReq( const TTPHduPlayReq & tTvwInfo );

    /**
    * ����:	 ֹͣ���е���ǽ����
    * @return    
    * @remarks  �ɹ�����0��ʧ�ܷ��ش�����
    */
    u16 StopAllHduReq();
    
    /** ����   ��õ���ǽ��������
	 *  @return THduPlanData ����ǽ������Ϣ
	 */
	virtual const THduPlanData& GetTvwPlanData() const;
   
protected:
    /**
    * ����:	  tvw ע�� �� ע�� �ĸ��� ֪ͨ��������ӡ�ɾ�� ��
    * @param [out]  cMsg ��Ϣ
    * @return  ��
    * @remarks   
    */
    //void  OnRefeshTvwNotify(const CMessage& cMsg);

    /**
    * ����:	  ����hdu�Ļظ�
    * @param [out]  cMsg	��Ϣ
    * @return  ��
    * @remarks   
    */
    void  OnOperateHduRsp(const CMessage& cMsg);
    
    /**
    * ����:	  
    * @param [out]  cMsg	��Ϣ
    * @return  ��
    * @remarks   
    */
    //void OnCodeStreamNotify(const CMessage& cMsg);

    /**
    * ����: ����ǽ����֪ͨ
    * @return  ��
    * @remarks   
    */
    void OnTvwPlanNotify(const CMessage& cMsg);
    /**
    * ����: ����ǽע��״̬֪ͨ
    * @return  ��
    * @remarks   
    */
    void OnTvwRegStatusNotify(const CMessage& cMsg);

    /**
    * ����:	  ע����Ϣ��Ӧ����
	* @param [in]  cMsg	��Ϣ
	* @return  ��
	* @remarks   
	*/
	void  BuildEventsMap();
   
	virtual void DispEvent(const CMessage &cMsg);
	
    virtual void OnTimeOut(u16 wEvent);

    void  OnLinkBreak(const CMessage& cMsg);
private:
	CUmsSession *m_pUmsSession;
    //TplArray<TCmsTvwInfo> m_tplTvwLst;

    THduPlanData  m_tHduPlanData;
};

#endif // !defined(AFX_TVWCTRL_H__E4797A29_3C89_45DE_AA25_727E6705780B__INCLUDED_)
