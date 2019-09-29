/*****************************************************************************
ģ����      : CMS����̨
�ļ���      : confTemplateCtrl.h
����ļ�    : 
�ļ�ʵ�ֹ���: ����ģ����ص����в���
����        : �����
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2011/4/25  1.0          �����      ����
******************************************************************************/
//Note:��������ͻ����E164�ž������ظ����һ����������Ϊ�Ǵ����֣�����164�ű���Ϊ������

#if !defined(AFX_CONFTEMPLATECTRL_H__92C02860_1783_462D_9A53_784A335A906C__INCLUDED_)
#define AFX_CONFTEMPLATECTRL_H__92C02860_1783_462D_9A53_784A335A906C__INCLUDED_

#include "confTemplateCtrlIF.h"
#include "umsSession.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CConfTemplateCtrl:public CConfTemplateCtrlIF  
{

/** @defgroup ����ģ��ӿ�ʵ�ֲ���
 *  @{
 */

	friend class CUmsSession;
private:
	CConfTemplateCtrl(CUmsSession &cUmsSession);
	CConfTemplateCtrl(const CConfTemplateCtrl&){}; 
    
public:
	~CConfTemplateCtrl();

	/**
    * �� ��:	��ȡ����ģ���б�
	* @param [out] tplConfTempList	 ����ģ���б�
	* @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	virtual u16 GetConfTemplateList( TplArray<TTPConfTemplate> &tplConfTempList ) const ;
   

  /**
    * ����:  ��ӻ���ģ��
	* @param [in]	tConfTemp	 ����ģ�� 
	* @return	�ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  ��Ϣ��cms->ums    evtp_AddConfTemplate_req \n
	                    Ӧ�ظ�: ums->cms  evpt_OperatorConfTemplate_Ret\n
	                    ����ӳɹ��������� ums->cms  evtp_AddConftemplate_Notify
	*/
	virtual u16 AddConfTemplateReq( const TTPConfTemplate &tConfTemp )    ;
 
 
 /**
    * ����:  �޸Ļ���ģ��
	* @param [in]	tConfTemp	 ����ģ�� 
	* @return	�ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  ��Ϣ��cms->ums  evtp_Updateconftemplate_Req \n
	                    Ӧ�ظ�: ums->cms  evpt_OperatorConfTemplate_Ret\n
	                    ����ӳɹ��������� ums->cms  evtp_UpdateConftemplate_Notify
	*/
	virtual u16 ModifyConfTemplateReq( const TTPConfTemplate &tConfTemp )    ;

  

  /**
    * ����:  ɾ������ģ��
	* @param [in]	wConfTempID	 ����ģ��ID
	* @return	�ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  ��Ϣ��cms->ums  evtp_AddConfTemplate_req \n
	                    Ӧ�ظ�: ums->cms  evpt_OperatorConfTemplate_Ret\n
	                    ����ӳɹ��������� ums->cms  evtp_Delconftemplate_Notify
	*/
	virtual u16 DeleteConfTemplateReq( const u16 wConfTempID )    ;

	/**
    * ����:  ɾ��ȫ��ģ��
	* @param
	* @return	�ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks  ��Ϣ��umc->ums  ev_del_all_conftemp_req \n
	            Ӧ�ظ�: ums->umc  ev_del_all_conftemp_rsp\n
	*/
	virtual u16 DelAllConfTempReq();   //by xhx

protected:

 
  /**
    * ����: ������ӡ�ɾ�����޸Ļ���ģ��Ļظ�
	* @param [in]	cMsg:��Ϣ����
	* @return	��
	* @remarks  ��Ϣ�� ums->cms evpt_OperatorConfTemplate_Ret 
	*/
   void OnOperateConfTempRsp( const CMessage& cMsg );

	 
  
    /**
    * ����: ��ӻ���ģ���б��֪ͨ
	* @param [in]	cMsg:��Ϣ����
	* @return	��
	* @remarks  ��Ϣ�� ums->cms evtp_AddConftemplate_Notify
	*/
   void OnAddConfTempNotify( const CMessage& cMsg );


   
   /**
    * ����: ɾ������ģ���б��֪ͨ 
	* @param [in]	cMsg:��Ϣ����
	* @return	��
	* @remarks  ��Ϣ��ums->cms  evtp_Delconftemplate_Notify
	*/
   void OnDelConfTempNotify( const CMessage& cMsg );

    /**
    * ����: ɾ��ȫ��ģ����ϢӦ��
	* @param [in]	cMsg:��Ϣ����
	* @return	��
	* @remarks  ��Ϣ��ums->umc  ev_del_all_conftemp_rsp
	*/
   void OnDelAllConfTempRsp( const CMessage& cMsg );  //by xhx

  
    /**
    * ����: �޸Ļ���ģ���б��֪ͨ 
	* @param [in]	cMsg:��Ϣ����
	* @return	��
	* @remarks  ��Ϣ��ums->cms  evtp_Updateconftemplate_Notify
	*/
   void OnUpdateConfTempNotify( const CMessage& cMsg );

    /**
    * ����: ���»���ģ����Դռ���� 
	* @param [in]	cMsg:��Ϣ����
	* @return	��
	* @remarks  ��Ϣ��ums->cms  evtp_Updateconftemplate_Notify
	*/
   void OnUpdateResUsedCountNotify( const CMessage& cMsg );

   void OnLinkBreak( const CMessage& cMsg );
   
    
   virtual void DispEvent(const CMessage &cMsg);
   
   virtual void OnTimeOut(u16 wEvent);


private:
   void  BuildEventsMap();
 
   /**
    * ����: ���ĳ����ģ�� �Ƿ��Ѵ���
	* @param [in]	wConfTemplateID��Ҫ���Ļ���ID��
	* @return	TRUE���Ѵ��ڣ�FALSE��������
	*/
   BOOL32  IsExistConfTemplate( u16 wConfTemplateID );

 
  /**
    * ����: ���ݻ���ģ��ID����ȡ����ģ��
	* @param [in]	wConfTemplateID��Ҫ���Ļ���ID��
	* @return	����ģ�����б��е�����
	*/
   int  FindConfTemplateByID( u16 wConfTemplateID );

private:
	TplArray<TTPConfTemplate> m_tplConfTempList;
    
	CUmsSession *m_pUmsSession;

/** @}*/  //����ģ��ӿ�ʵ�ֲ���
};

#endif // !defined(AFX_CONFTEMPLATECTRL_H__92C02860_1783_462D_9A53_784A335A906C__INCLUDED_)
