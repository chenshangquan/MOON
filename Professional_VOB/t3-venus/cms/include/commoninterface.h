/*****************************************************************************
ģ����      : CMS����̨
�ļ���      : commoninterface.h
����ļ�    : commoninterface.cpp , umcconf.cpp, umcconftemplate.cpp, umctvw.cpp, umcumsconfig.cpp, umcuser.cpp
�ļ�ʵ�ֹ���: ��װ��umclib��cnclib�ӿڣ�UI��cns��ums��ͨ��ͳһ�����ýӿڴ���
����        : �����
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2011/4/28  1.0          �����      ����
******************************************************************************/

#if !defined(AFX_COMMONINTERFACE_H__E6AFC64B_E6AB_4404_930B_546D1178FF87__INCLUDED_)
#define AFX_COMMONINTERFACE_H__E6AFC64B_E6AB_4404_930B_546D1178FF87__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "umclib.h" 
#include "cnclib.h"
#include "printCtrl.h"
//#include "netadapter.h"
  
 
enum EM_EqType
{
	emEqUmsCns,     
	emEqUms,         
	emEqCns        
};



// enum EMLocalCnsState
// {   
//     emLocalCnsIdle,          //����״̬
//         emLocalCnsCalling,   //���ں�����
//         emLocalCallingTimeOut,    //���ж�������ʾ����5�룬Ӧ���л�������״̬
//         emLocalCnsInConf,    //�ڻ�����
//         emLocalCnsHunguping, //���鿪����localCns �����ߣ�ִ���˹Ҷϲ���
//         emLocalCnsLocking,   //���鿪����localCns ������,��ǰ����������״̬
// };

class CCommonInterface:public CWnd   
{

public: 
/** @defgroup  CCommonInterface��UI �ӿڲ��֣�
 *  @{
 */

    

//-----session ���-------------
/** @defgroup  ums��cns �Ự�����ֽӿ�
 * @{
 */  


 /**
  * ��  ��	�����Ự������Ums��Cns����
  * @return u16 �ɹ�����0;ʧ�ܷ��ط�0������ 
  */
	void  CreateSession();

 /**
  * ��  ��	���ٻỰ������Ums��Cns����
  * @return u16 �ɹ�����0;ʧ�ܷ��ط�0������ 
  */
	void DesdroySession();

  /**
	* ����   ���ӵ�UMS �� CNS
	* @param [in]  dwIP	������UMS��IP��ַ��������
	* @param [in]  pStrUserName �û���	
	* @param [in]  pStrPswd	����
	* @return u16 �ɹ�����0;ʧ�ܷ��ط�0������ 
	*/
	u16 Connect( u32 dwIp, u16 nPort, LPCTSTR pStrUserName, LPCTSTR pStrPswd ); 
   

  /**
	* ����:  ��ǰ��¼���û��Ƿ��ǹ���Ա
	* @return  TRUE �ǹ���Ա��FALSE һ���û�
	*/
	BOOL IsManagerUser();
   
  /**
   * ����:	�Ƿ�������ums/cns
   * @return �ɹ�����0,ʧ�ܷ��ط�0������
   */ 
	BOOL32 IsConnect( EM_EqType emConnEq = emEqCns)  ; 

  /**
    * ����:	�Ͽ���UMS��CNS������
	* @param [in]  emConnEq	Ҫ�Ͽ����ӵĶ���
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks	��û�����ӵ�UMS/CNSʱ���ô˷����������κ�����
	*/
	u16 DisConnect( EM_EqType emConnEq = emEqCns ) ; 
  
    /**
	* ����:	��ȡ��½cns ��IP 
	* @return  u32  IP
    */
	u16 GetLoginIp( u32 & IP ); 
  
    /**
	* ����:	��ȡ���� ��IP 
	* @return  u32  IP
    */
	 u16 GetLocalIP( u32 & IP ) ;

	/**
	* ����:	��ȡ��¼���û���Ϣ
	* @return   
    */
	//u16 GetConnectedUser( CLoginRequest& user);

	/**
	* ����:	��ȡ���ӵ�Cns�б�
	* @return   
    */
	u16 GetConnectCnsList( TTPCnList& tCnList );

	/**
	* ����:	��¼Cns�᳡
	* @return   
    */
	u16 LoginCnsIns( u8 byIns );

/** @}*/ 

 
//-----����ģ����� -------------
/** @defgroup  ����ģ����ؽӿ�
 *  @{
 */

 /**
    * �� ��:	��ȡ����ģ���б�
	* @param ��
	* @return  ����ģ���б��ָ��
	*/
    //TplArray<TTPConfTemplate>* GetConfTemplateList();

    /**
    * �� ��:	��ȡ����ģ���б�
	* @param ��
	* @return  ����ģ���б��ָ��
	*/
	vector<TTPAlias>* GetConfTempList();

	/**
    * �� ��:	���»���ģ��
	* @return  �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 UpdateConfTemplate();


    /*��  ��	�޸Ļ���ģ��
    ��  ��	tConfTem������ģ�� 
    ����ֵ  0 ��ʾ��ums��������ɹ�����0 ��ʾ����ʧ��
    ˵  ��	 ������ģ���Ѵ��ڣ����޸ģ��������ڣ������*/
    //u16  ModifyConfTemplate( const TTPConfTemplate & tConfTem ) ;


    /**
    * ����:  ��ӻ���ģ��
	* @param [in]	tConfTemp	 ����ģ�� 
	* @return	�ɹ�����0,ʧ�ܷ��ط�0������
	*/
	//u16 AddConfTemplate( const TTPConfTemplate & tConfTem ) ;

    /**
    * ����:  �޸Ļ���ģ��
	* @param [in]	tConfTemp	 ����ģ�� 
	* @return	�ɹ�����0,ʧ�ܷ��ط�0������
	*/
	//u16 UpdateConfTemplate( const TTPConfTemplate & tConfTem ) ;

    /**
    * ����:  ɾ������ģ��
	* @param [in] wConfTempID	 ����ģ��ID 
	* @return	�ɹ�����0,ʧ�ܷ��ط�0������
	*/
	//u16 DeleteConfTemplate( const u16 wConfTemplateID )  ;

	/**��ȡ��������������������Ϣҳ���� */

	u16 GetNetMngData( vector<TTPNMServerCfg> &vecTTPNMServerCfg );

 	/**
    * ����:	 	        ���������������
 	* @param [in]       ������Ϣ
 	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
 	*/
 	u16  NetMngAddCmd( const TTPNMServerCfg& tTPNMServerCfg );

     /**
    * ����:	 	        �����޸���������
 	* @param [in]       ������Ϣ
 	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
 	*/
	u16  NetMngModifyCmd( const TTPNMServerCfg& tTPNMServerCfg );

    /**
    * ����:	 	        ����ɾ����������
	* @param [in]       ������Ϣ
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  NetMngDeleteCmd( const TTPNMServerCfg& tTPNMServerCfg );
  
  
    /**
    * ����:  ���ݻ���ID��ȡ����ģ��ָ��
	* @param [in] wConfTempID	 ����ģ��ID 
	* @return	ID��Ӧ�Ļ���ģ��
	*/  
	//TTPConfTemplate* GetConfTemplateByID( u16 wConfTemplateID ) const ;

     /**
    * ����:  ����һ������ģ��
	* @param [in] temp	 Ҫ������ģ�� 
	* @return 
	*/  
	void InvalidConfTemp( TTPConfTemplate &temp) const ;


    
    /**
    * ����:  ���ݻ���ģ��ID��cnsID ��ȡcns ������Ϣ
	* @param [in] wConfTempID	 ����ģ��ID 
	* @return	ID��Ӧ�Ļ���ģ��
	*/  
	//TTPAlias* GetCnsInfoFromTemplateByID( u16 wConfTemplateID , u16 wCnsID ) const ;
    
  
    /**
    * ����:  ����ģ������Ƿ��Ѵ���
	* @param [in] Alias:����ģ�����
	* @return  TRUE�����ڣ�FALSE��������
	*/  
	//BOOL32  IsConfTemplateAliasExist( const s8* Alias   ) const;


 
	/**
    * ����:  �жϻ���ģ��ı�����E164���Ƿ����
	* @param [in] Alias:����ģ�����
	* @return  �ɹ�����0��ʧ�ܷ��ط�0������
	* @remarks ��Ҫ�����޸�ʱ�жϣ��Ҹ�ģ���ID������UMS����� ���õ� 
	*/  
	//u16    CheckConfTemplateValidate( const TTPConfTemplate & tConfTem ) const;
 
  
    /**
    * ����:  ����ģ��E164���Ƿ��Ѵ���
	* @param [in] E164������ģ��E164��
	* @return  TRUE�����ڣ�FALSE��������
	*/ 
	//BOOL32  IsConfTemplateE164Exist( const s8* E164  ) const;

    /**
    * ����:  �жϻ���ģ�����ϯcns �Ƿ�Ϊ������cns
	* @param [in] tConfTem:����ģ�� 
	* @return  �ɹ�����0��ʧ�ܷ��ط�0������
	* @remarks ��Ҫʹ�ø�ģ�忪��ʱ
	*/  
	//u16    CheckConfTemplateChairMan( TCMSConfTemplate & tConfTem )  ;

    /**
    * ����:  �жϻ���ģ�����ϯcns �Ƿ�Ϊ������cns
	* @param [in] wConfTemID:����ģ��ID
	* @return  �ɹ�����0��ʧ�ܷ��ط�0������
	* @remarks ��Ҫʹ�ø�ģ�忪��ʱ
	*/  
	//u16    CheckConfTemplateChairMan( const u16 & wConfTemID )  ;
  

/** @}*/ 	
	
//-----�����ؽӿ� -------------
/** @defgroup  �����ؽӿ�
 *  @{
 */
 
   BOOL32 IsInConf( TCMSConf *pConf = NULL );

    

   /**
	* ����:  ��ȡ������Ϣ  
	* @return  �����б�ָ��
	*/
    TCMSConf  &GetConfInfo(){ return m_tConfInfo ; }


    /**
    * ����:  �ж� cns�Ƿ�Ϊ �������ϯ
	* @param  
	* @return   
	* @remarks  
	*/
    BOOL32 IsCnsChairMan(  u16 wCnsID );

   
 
   
     
 
	/**
	* ����:  ��ȡ�����cns�б�
	* @param [in]wConfID	 ����ID 
	* @return �ɹ����ػ�����Ϣָ��,ʧ�ܷ���NULL
	*/
	TplArray<TCnsInfo>* GetConfCnsList( const u16 wConfID ) ;

    /*
	* @param [in]achRoomName �᳡��
	* @return �ڷ���TRUE,���ڷ���FALSE
	* @remarks 
	*/
	BOOL32 IsCnsInConf( s8* achRoomName )   ;  


    /**
	* ����:  ����cns�Ƿ��Ƿ�����
	* @param [int]wConfID ������Ϣ 
	* @return �ɹ�����TRUE,ʧ�ܷ���FALSE
	* @remarks  
	*/
    BOOL32 IsLocalCnsSpeaker(  )  ; 


    /**
	* ����:  �������б���cns�Ƿ��Ƿ�˫��
	* @param [int]wConfID ������Ϣ 
	* @return �ɹ�����TRUE,ʧ�ܷ���FALSE
	* @remarks  
	*/
    BOOL32 IsLocalCnsDualInConf( )  ; 

     

    /**
	* ����:  ��ȡ����cns����״̬
	* @param [out]tConfInfo  ����cns�μӵĻ�����Ϣ
	* @return �ɹ�����TRUE,ʧ�ܷ���FALSE
	* @remarks 
	*/
    TTPCnsConfStatus GetLocalCnsConfState() const; 

   



	/**
	* ����:  ����cns�Ƿ�����ϯ 
	* @return �ɹ�����TRUE,ʧ�ܷ���FALSE
	* @remarks ��CNS��������״̬
	*/
	BOOL32 IsLocalCnsChairMan()  ;

 

   /**
    * ����:  �ж� �Ƿ�Ϊ������cns
	* @param strAliars ����
	* @return   
	* @remarks  
	*/
    BOOL32 IsLocalCns( String strAliars );   


   /**
	* ����:  ʹ�û���ģ�忪�� 
	* @param [in]  achTempName: ģ����
	* @return �ɹ�����0��ʧ�ܷ��ش�����
	*/
	u16 StartTemplateConf( s8* achTempName ) ;

	/**
	* ����:  ʹ�û���ģ�忪�� 
	* @param [in]  tTemp: ģ�� 
	* @return �ɹ�����0��ʧ�ܷ��ش�����
	*/
	u16 StartTemplateConf( const TTPAlias& tTemp ) ; 
	

	/**
	* ����:  ����һ����ʱ���� 
	* @param [in] tCnsList :�����ն��б� ,���᳡Ϊ��һ����Ա��������Ϊ���᳡
	* @param [out] achConfName :������
	* @return �ɹ�����0��ʧ�ܷ��ش�����
	* @remarks umsԤ��һ�����ڿ�����ʱ����Ļ���ģ�壨IDΪ0�����û���ģ����治��ʾ
	*/
	u16 StartInstantConf( const vector<TCnAddr>& tCnsList );
 
	
 
 /**
	* ����:  �Ҷϻ��� 
	* @param [in] dwConfID������ID
	* @return �ɹ�����0��ʧ�ܷ��ش�����
	* @remarks ��������
	*/
	u16 HangupConf( )  ;
    
    
  
/**
	* ����:  ����ĳ�᳡������� 
	* @param [in] tEp:�᳡��Ϣ
	* @return �ɹ�����0��ʧ�ܷ��ش�����
	* @remarks �����᳡Ϊ���᳡ʱ���ɲ���
	*/
	u16 InviteCns( const TConfCallEpAddr &tEp );



    /**
    * ����:	���л������Ѿ����ڵ�cns�᳡����ĳ����
	* @param [int]  tEp	 ����ͻ᳡��Ϣ
	* @return  u16 �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks ��Ϣ��cms->ums  evtp_CallEP_cmd  \n
                       Ӧ�ظ���ums->cms evtp_CallEP_result   \n
	                   ���ɹ�����Ӧ����ums->cms evtp_UpdateConfCnsList_Notify
	*/ 
   u16 CallConfCns( const TConfEpID &tEp );



    /**
	* ����:  �������᳡������� 
	* @param [in] tEp:�᳡��Ϣ
	* @return �ɹ�����0��ʧ�ܷ��ش�����
	* @remarks �����᳡Ϊ���᳡ʱ���ɲ���
	*/
	u16 InviteCns( const tagConfCallEpAddrList &tEp );
	 

    /**
	* ����:  ��ȡ������cns����Ϣ
	* @param [in] tEp:�᳡��Ϣ
    * @param [out] tCnsInfo:�᳡��Ϣ
	* @return �ɹ�����0��ʧ�ܷ��ش�����
	* @remarks �����᳡Ϊ���᳡ʱ���ɲ���
	*/
    u16 GetConfCnsByID( const TConfEpID &tConfEpInfo , TCnsInfo* pTCnsInfo);

   
/**
	* ����:  �Ҷ�ĳ�᳡ 
	* @param [in] tConfEpInfo: eqID ����ID
	* @return �ɹ�����0��ʧ�ܷ��ش�����
	* @remarks �����б�����Ȼ���ڸû᳡��ֻ�ǲ�����
	*/
    u16 HangupCNS( const TConfEpID &tConfEpInfo );
 
	
/**
	* ����:  �ӻ������Ƴ�ĳ�᳡ 
	* @param [in] tConfEpInfo: eqID ����ID
	* @return �ɹ�����0��ʧ�ܷ��ش�����
	* @remarks �Ƴ�������б��в����ڸû᳡ ,��ʱ���øýӿ�
	*/
	u16 RemoveCNS( const TConfEpID &tConfEpInfo );

 
	/**
	* ����:  ���÷��� CNS
	* @param [in]wConfID	 ����ID
	* @return �ɹ�����0��ʧ�ܷ��ش����� 
	*/ 
	u16 SetSpokeCns( const TConfEpID &tConfEpInfo );
   
    

    /**
    * ����:	����Զ��cns����
	* @param [int]  wConfID	 �InfoList );


 
	/**
	* ����:  ������ѯ�б����� 
	* @param [in]tTurnInfoList	 ��ѯ�б�
	* @return �ɹ�����0��ʧ�ܷ��ش����� 
	*/ 
	u16 UpdatePollList( const TConfTurnInfo &tTurnInfoList );
 
 
//   /**
// 	* ����:  �������� 
// 	* @param [in]wConfID	 ����ID
// 	* @return �ɹ�����0��ʧ�ܷ��ش����� 
// 	*/ 
// 	u16 StartAuxMix( const u16 wConfID );
// 
//  
// 	/**
// 	* ����:  ֹͣ���� 
// 	* @param [in]wConfID	 ����ID
// 	* @return �ɹ�����0��ʧ�ܷ��ش����� 
// 	*/ 
// 	u16 StopAuxMix( const u16 wConfID );


    
    /*��  ��	���»����б�����
    ��  ��	tMixInfo	 �����б�
    ����ֵ	�ɹ�����0,ʧ�ܷ��ط�0������
    ˵  ��	 */
	u16 UpdateAudMixList( const TConfAuxMixInfo &tMixInfoList );

	 /*
	��  ��	�����б��������
	��  ��	tDisListOpr	 �����б����
	����ֵ	�ɹ�����0,ʧ�ܷ��ط�0������
	˵  ��	 */
	u16 AudMixDisListOpr( const TTPDisListOpr &tDisListOpr );

	/**
	* ����:  ������ѯ 
	* @param [in]wConfID	 ����ID
	* @return �ɹ�����0��ʧ�ܷ��ش����� 
	*/ 
	u16 StartPoll( const u16 wConfID );


 
	/**
	* ����:  ֹͣ��ѯ 
	* @param [in]wConfID	 ����ID
	* @return �ɹ�����0��ʧ�ܷ��ش����� 
	*/ 
	u16 StopPoll( const u16 wConfID ); 

	/**
	* ����:  ��ȡ������������������ҳ��Ϣ 
	* @param [in]wConfID	 ����ID
	* @return �ɹ�����0��ʧ�ܷ��ش����� 
	*/ 
 
/** @}*/ 
	

//-----���������ؽӿ� -------------
/** @defgroup  ���������ؽӿ�
 *  @{
 */ 
 
	/**
	* ����:  ��ȡ����cns��Ϣ 
	*  @param[out] tCnsInfo����CNS��Ϣ
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
	u16 GetLocalCnsInfo( TTPCnsInfo& tCnsInfo ) const;
  
	/**
	* ����:  ��ȡ��cns�б� 
	* @param[out] vctCnsList������cns�б���Ϣ
	* @return �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
	u16 GetLocalCnsList( vector<TTPCnsInfo>& vctCnsList ) const;

	/**
	* ����:  ����cns��Ϣ 
	* @param[in] tInfo CNS��Ϣ  byIndex ��Ϣ��������(0Ϊcnc 1Ϊά������)
	* @return �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
	u16 UpdateCnsInfo( const TTPCnsInfo& tInfo, u8 byIndex );

	/**
	* ����:  ����cns���᳡ 
	* @param[in] pbyRoomName �᳡��
	* @return �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
	u16 SetMainCns( s8* pbyRoomName );

	/**
	* ����:  ��ȡcns���᳡ 
	* @return �ɹ����ػ᳡��,ʧ�ܷ���NULL
	* @remarks 
	*/
	const s8* GetMainCnsName();

	/**
	* ����:  ��ȡ��cns����Ϣ 
	* @param[out] vctScreenInfo����cns����Ϣ
	* @return �ɹ�����0,ʧ�ܷ��ط�0������
	* @remarks 
	*/
	u16 GetCnsScreenInfo( vector<TScreenInfo>& vctScreenInfo ) const;

    u16 GetCnsScreenInfoByID( u8 screenID, TScreenInfo& tScreenInfo ) const;

	/**
	* ����:  ��ձ�cns����Ϣ 
	* @remarks 
	*/
	void ClearCnsScreenInfo();

/** @}*/ 
	
//----����ǽ���--------------
/** @defgroup  ����ǽ���
 *  @{
 */

    /**
	* ����:  �ж�cns�Ƿ��ڵ���ǽ��
	* @return �ɹ�����true,
	* @remarks 
	*/ 
    BOOL32 IsCnsInTvw( s8 *abyCnsAliars );

	//��ȡ����ǽԤ���б�
    //TplArray<TCmsTvwInfo>* GetTvwList()  ;
 
    //���ݵ���ǽHandle�Ż�ȡ����ǽ��Ϣ
    //TCmsTvwInfo * GetTvwInfoByHandleID( const u32 dwHandleID ) const;

	//���ŵ���ǽԤ��
    //u16 PlayTvw ( const TTPHduPlayReq & tTvwInfo ); 
   
	//ɾ������ǽԤ��
    //u16 DeleteTvw( const TTPHduPlayReq & tTvwInfo ); 

	//��ȡHDU �忨��Ϣ

/** @}*/ 


 //-----�û���� -------------
/** @defgroup  �û����
 *  @{
 */
	

 
	/**
	* ����:  ��ȡ�û��б�  
	* @return  �ɹ������û��б�ָ�룬ʧ�ܷ��ؿ�
	*/
   TplArray<CUserFullInfo>* GetUserList() ;
	
 
   /**
	* ����:  ����û� 
	* @param [in]  user  
	* @return  �ɹ�����0��ʧ�ܷ��ش�����
	*/
	u16 AddUser( const CUserFullInfo& user )    ;
    

 
	/**
	* ����:  �޸��û���Ϣ 
	* @param [in]  user  
	* @return  �ɹ�����0��ʧ�ܷ��ش�����
	*/
	u16 UpdateUser( const CUserFullInfo& user )   ;
	 
 
	/**
	* ����:  ɾ���û� 
	* @param [in]  user  
	* @return  �ɹ�����0��ʧ�ܷ��ش�����
	*/
    u16 DeleteUser( const CUserFullInfo & user ) ;
	
 
	/**
	* ����:  �����û�����ȡ�û���Ϣ 
	* @param [in]  pUserName  
	* @return  �ɹ������û���Ϣָ�룬ʧ�ܷ��ؿ�ָ��
	*/
	CUserFullInfo *GetUserByName ( s8 *pUserName )  const ;


 
/**
	* ����:  �ж��û����Ƿ��Դ��� 
	* @param [in]  pUserName  
	* @return  �ɹ�����TREU��ʧ�ܷ���FLASE
	*/
	BOOL32  IsExistUser ( s8 *pUserName ) const ;

/** @}*/ 

 
	
 //-----CNS  ����-------------  
/** @defgroup  CNS ����
 *  @{
 */

    /**��Ե����
	*  @param[in] 
	*  @return  
	*/
    u16 MakeCall( TCnAddr& tCnAddr );

	u16 MakeCall( const TTPAlias& tAlias );

    u16 HungupPtpConf();

	/**��ȡ��ǰspeaker״̬���Ƿ�Ϊ����
	*  @param[in] 
	*  @return BOOL �Ƿ�Ϊ����
	*/
	BOOL32 IsLocalCnsQuite();

	/**��ȡ��ǰMic״̬���Ƿ�Ϊ ����
	*  @param[in] 
	*  @return BOOL �Ƿ�Ϊ����
	*/
	BOOL32 IsLocalCnsMute(); 

	/**���ػ᳡���� ����
	*  @param[in] Quite �Ƿ���
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 SetLocalCnsQuite( BOOL bQuite = TRUE );

	/**���ػ᳡���� ����
	*  @param[in] bMute �Ƿ�����
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 SetLocalCnsMute( BOOL bMute = TRUE );

	/**���ڻ᳡��������
	*  @param[in] byVolume ����
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 AdjustInputVol( u8 byVolume );

	/**���ڻ᳡�������
	*  @param[in] byVolume ����
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 AdjustOutputVol( u8 byVolume );
	
	/**��ȡ�᳡��������
	*  @return  byVolume ����
	*/
	u8 GetInputVol();

	/**��ȡ�᳡�������
	*  @return byVolume ����
	*/
	u8 GetOutputVol();

  

  /**���û᳡������ϯ
	*  @param[in] bySeatId ��ϯID
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 SetCnsInnerSpeaker( u8 bySeatId );

	/**��ȡ�᳡������ϯ
	*  @param[in] 
	*  @return ��ϯID
	*/
	u8 GetCnsInnerSpeaker();

	/** ����:  CNS����SIPע������ 
	*  @param[in] tSipCfg Sipע������
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 CnsRegSipService( const TTPSipRegistrarCfg &tSipCfg );

	/** ����:  CNSע��SIP���� 
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 CnsUnRegSipService();

	/** ����   ���SIP����
	*  @param[out] tSipCfg SIP����
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetSipCfg( TTPSipRegistrarCfg& tSipCfg );


    /** ����:  CNS����Gkע������ 
	*  @param[in] tSipCfg Sipע������
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 CnsRegGkService( const TTPGKCfg &tCfg );


    /** ����   ���Gk����
	*  @param[out] tGkCfg
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetGkCfg( TTPGKCfg& tGkCfg );


	/** ����:  ������������
	*  @param[in] tInfo ��������
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*  @remarks 
	*/
	u16 UpdateEthnetCfg( const TTPEthnetInfo& tInfo );

	/** ����   �����������
	*  @param[out] tInfo ��������
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetEthnetCfg( TTPEthnetInfo& tInfo );

	/** ����:  ����NAT����
	*  @param[in] tInfo NAT����
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*  @remarks 
	*/
	u16 UpdateNATCfg( const TTPNatCfg& tInfo );

	/** ����   ���NAT����
	*  @param[out] tInfo NAT����
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetNATCfg( TTPNatCfg& tInfo );

     /** ����   ����ϵͳʱ��
	 *  @return �ɹ����ػ᳡��,ʧ�ܷ���NULL
	 *  @remarks 
	 */
     u16 UpdateSysTime( const TTPTime& time ) ;
    
    
    /** ����   ��ȡϵͳʱ��
	 *  @return �ɹ����ػ᳡��,ʧ�ܷ���NULL
	 *  @remarks 
	 */
    u16 ReqSysTime();

	/** ����   ������������ַ
	*   @param[in] TTPUpgradeSer ��������ַ�ṹ��
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */
	u16 UpgradeSerCmd( const TTPUpgradeSer& tUpgradeSer );

	/** ����   ��÷�������ַ
	*  @param[out] TTPUpgradeSer ��������ַ�ṹ��
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetUpgradeSerInfo( TTPUpgradeSer& tUpgradeSer );

	/** ����   ���з�����
	*   @param[in] u32_ip ��������ַ
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */
	u16 CallServerCmd( const TTPCallSerInfo& tCallSerInfo );

	/** ����   ��ȡ���з���������
	*  @param[out] TTPCallSerInfo ���з���������
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 GetCallServerInfo( TTPCallSerInfo& tCallSerInfo );

    /** 
	* ����  ���õ���ǽѡ��
    * @param [in]  byScreenID  ����
	* @return  
	* @remarks 
	*/
	u16 SetSelTVSView( u8 byScreenID ) ;

     /** 
	* ����  ȡ������ǽѡ��
    * @param [in]  byScreenID  ����
    * @param [in]  wEpID  ѡ����cnsID
	* @return  
	* @remarks 
	*/
	u16 CancleSelTVSView( u8 byScreenID ) ;

    /** 
	* ����  ����ѡ��
    * @param [in]  byScreenID  ����
    * @param [in]  wEpID  ѡ����cnsID
	* @return  
	* @remarks 
	*/
	u16 SetSelView( u8 byScreenID, u16 wEpID ) ;

     /** 
	* ����  ȡ��ѡ��
    * @param [in]  byScreenID  ����
    * @param [in]  wEpID  ѡ����cnsID
	* @return  
	* @remarks 
	*/
	u16 CancleSelView( u8 byScreenID ) ;

   /** 
	* ����  ����/ֹͣ��ѯ
    * @param [in]  bStart   true:������false���ر�
	* @return  
	* @remarks 
	*/
	u16 StartPoll( BOOL  bStart ) ;

   /** 
	* ����  ����cns�Ƿ�����ѯ
    * @param [in]  
	* @return  true:������false���ر�  
	*/
	BOOL32  IsLocalCnsPoll();

    /** 
	* ����  ����/ֹͣ˫��
    * @param [in]  bStart   true:������false���ر�
	* @return  
	* @remarks 
	*/
	u16 StartDual( BOOL  bStart ) ;

   /** 
	* ����  ����cns�Ƿ���˫��
    * @param [in]  
	* @return  true:������false���ر�  
	*/
	BOOL32 IsLocalCnsDual() const;
    
/** @}*/ 

//-----��ַ�����-------------  
/** @defgroup  ��ַ�����
 *  @{
 */	 

	/** ����:  ��ȡ��ַ��
	 *  @return CAddrBook ���ص�ַ������
	 */
	CAddrBook& GetAddrBook();

	BOOL GetAddrLoadingState();
	void SetAddrLoadingState(BOOL bAddrLoading);

	/** ����:  ��ӵ�ַ����Ŀ
	 *  @param[in] entry ��ַ����Ŀ
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */ 
	u16 AddEntry( const CAddrEntry& entry );

	/** ����:  �޸ĵ�ַ����Ŀ
	 *  @param[in] entry ��ַ����Ŀ
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */
	u16 ModifyEntry( const CAddrEntry& entry );

	/** ����:  ɾ����ַ����Ŀ
	 *  @param[in] dwIndex ��ַ����Ŀ����
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */
	u16 DeleteEntry( u32 dwIndex );

	/** ����:  ɾ�������ַ����Ŀ
	 *  @param[in] vctEntry ��ַ����Ŀ������
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */
	u16 DeleteMultiEntry( vector<u32>& vctEntry );

	/** ��ӵ�ַ����Ŀ��
	 *  @param[in] group ��ַ����Ŀ��
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */
	u16 AddGroup( const CAddrMultiSetEntry& group );

	/** �޸ĵ�ַ����Ŀ��
	 *  @param[in] entry ��ַ����Ŀ��
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */
	u16 ModifyGroup( const CAddrMultiSetEntry& group );

	/** ɾ����ַ����Ŀ��
	 *  @param[in] dwIndex ��ַ��������
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */
	u16 DeleteGroup( u32 dwIndex );

    /** ����:  ɾ�������ַ����
	 *  @param[in] vctGroup ��ַ����������
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */
    u16 DeleteMultiGroup( vector<u32>& vctGroup );

	/** ��ӵ�ַ�����Ա
	 *  @param[in] tGroupEntry ��ַ������Ϣ
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */
	u16 AddEntryToGroup( const TADDRMULTISETENTRY& tGroupEntry );

	/** ɾ����ַ�����Ա
	 *  @param[in] tGroupEntry ��ַ������Ϣ
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */
	u16 DelEntryFromGroup( const TADDRMULTISETENTRY& tGroupEntry );

	/** ��ӵ�ַ�����ϵ
	 *  @param[in] dwGroupIndex ������
	 *  @param[in] dwUpGroupIndex �ϼ�������
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */
	u16 AddGroupToGroup( u32 dwGroupIndex, u32 dwUpGroupIndex );

	/** ɾ����ַ�����ϵ
	 *  @param[in] dwGroupIndex ������
	 *  @param[in] dwUpGroupIndex �ϼ�������
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */
	u16 DelGroupFromGroup( u32 dwGroupIndex, u32 dwUpGroupIndex );

	/** ����ȫ�ֵ�ַ��
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 */
	u16 UpdateGlobalAddrbook();

	/**
	* ����:  ��ȡ���ص�ַ���б�  
	* @return  �ɹ����ص�ַ���б�ָ�룬ʧ�ܷ��ؿ�
	*/
	const vector<TAddrItem>* GetLocalAddrList();

	/**
	* ����:  ��ȡȫ�ֵ�ַ���б�  
	* @return  �ɹ����ص�ַ���б�ָ�룬ʧ�ܷ��ؿ�
	*/
	const vector<TAddrItem>* GetGlobalAddrList();

	/**
	* ����:  ��ȡcnsע��ĵ�ַ����Ŀ  
	* @return  �ɹ����ص�ַ���б�ָ�룬ʧ�ܷ��ؿ�
	*/
	void GetCnsRegInfo( vector<TAddrInfo>* pvctCnsRegInfo );

	/**
	* ����:  ��ȡ��ַ�����б� 
	* @return  �ɹ����ص�ַ�����б�ָ�룬ʧ�ܷ��ؿ�
	*/
	const vector<TAddrItem>* GetAddrGroupList();

    /**
	* ����:  ��ȡ���ص�ַ����Ŀ�б�  
	* @return  �ɹ����ص�ַ���б�ָ�룬ʧ�ܷ��ؿ�
	*/
    const vector<TAddrItem>* GetAddrEntryList();

	/**
	* ����:  ��ȡ��ַ�������Ա�б�  
	* @param[in]  dwGroupIndex  ������
	* @param[out] vctGroupMemberList  �����Ա�б�
	* @return  
	*/
	void GetAddrGroupMember( u32 dwGroupIndex, vector<TAddrItem>& vctGroupMemberList );

	/**
	* ����:  ��ȡ��ַ��������Ϣ
	*  @param[in]  dwGroupIndex  ������
	*  @param[out] tGroupInfo  ������Ϣ
	*  @return
	*/
	void GetAddrGroupInfo( u32 dwGroupIndex, TGroupInfo& tGroupInfo );

	/**
	* ����:  ��ȡ��ַ������·����
	*  @param[in]  dwGroupIndex  ������
	*  @return  ·����
	*/
	CString GetAddrGroupPath( u32 dwGroupIndex );

	/** ��CAddrEntry�����赽TAddrInfo��
	 *  @param[out] tAddrInfo  ��ַ��Ŀ��Ϣ
	 *  @param[in]  cAddrEntry ��ַ����Ŀ��Ϣ
	 *  @return 
	 */
	void SetAddrItemInfo( TAddrInfo& tAddrInfo, CAddrEntry& cAddrEntry );

	/** ��ȡ���е���Ŀ��Ϣ
	 *  @param[in]   tGroupInfo  ��ַ����Ϣ
	 *  @param[out]  vctAddrInfo ��ַ��Ŀ��Ϣ�б�
	 *  @return 
	 */
	void GetGroupAddrInfo( const TGroupInfo& tGroupInfo, vector<TAddrInfo>& vctAddrInfo );  
/** @}*/


    u16  IsThisCnsHaveConf() const;


    //���õ�ǰ�����Ļ�����
    void SetCurConfName( s8 *pConfName ){ 
        InvalidConfTemp(m_tCurConfTemplate );
        _snprintf(m_tCurConfTemplate.m_achConfName, sizeof(m_tCurConfTemplate.m_achConfName),"%s" , pConfName);
    }

    void SetCurConfTemplate( TTPConfTemplate  &tCurConfTemplate ){
        m_tCurConfTemplate = tCurConfTemplate ;
        m_tCurConfTemplate.m_wID = tCurConfTemplate.m_wID; 
    }

    //��ȡ��ǰ�����Ļ�����
    s8*GetCurConfName(){ return m_tCurConfTemplate.m_achConfName; }
    TTPConfTemplate GetCurConfTemplate(){ return m_tCurConfTemplate; }
/** @}*/
    
    void  ShutDownOS(BOOL bRestart = FALSE );
    
    void  ShutDownCmc( BOOL bRestart = FALSE );


    void DisableTaskMgr( BOOL bDisable );


    //��������
    u16 StartDualCodeStream( const TTPCnMediaTransPort  &tVedioTransAddr, const TTPCnMediaTransPort  &tAudioTransAddr  ) const;
    u16 StopDualCodeStream() const;

    u16 ReqKeyFrame( BOOL32 bForce = TRUE ) const;

    TTPCnMediaTransPort GetVedioTransAddr() const  ;
    TTPCnMediaTransPort GetAudioTransAddr() const  ;

  
     /** 
	* ����  ��Ļ��ʾ˫��ͼ��
	* @return  BOOL  TRUE:������ FALSE:ֹͣ
	* @remarks 
	*/
    u16 ScrnDisplayDual( const u16 wScrnID ) const ;

     /** 
	* ����  ��Ļ��ʾ˫��ͼ��
	* @return  
	* @remarks 
	*/
    u16 ScrnStopDisplayDual( const u16 wScrnID ) const ;

    /** 
	* ����  ��Ļ����
	* @return    

	* @remarks 
	*/
    u16 ScrnDisplayLocal( const u16 wScrnID ) const  ;


    /** 
	* ����  ȡ����Ļ����
	* @return    
	* @remarks 
	*/
    u16 ScrnStopDisplayLocal( const u16 wScrnID ) const  ;


	BOOL32 IsRcvDual() const; 


	u16 SetMuteCns( const TConfEpID &tConfEpInfo , BOOL32 bMute);

	u16 SetQuietCns( const TConfEpID &tConfEpInfo, BOOL32 bQuiet);

	u16 SetDualCns( const TConfEpID &tConfEpInfo, BOOL32 bStart );

    /** ����   ��õ�½CNS������
	*  @param[out] tLoginInfo
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
    u16 GetLoginInfo( TLoginInfo& tLoginInfo );


	/** ����  ��ջ�ȡ����Sipע����Ϣ
	*  @param[in] emTyep  ����
	*  @return ��
	*/
	void ClearSipRegInfo( EmGetRegInfoType emTyep );

    /** ����   �����ʾԴ��Ϣ
	*  @param[out] tDualSrcinfo ��ʾԴ����
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
    u16 GetDualSrcInfo( TDualSrcInfo& tDualSrcinfo );

    /** ����   ѡ����ʾԴ�˿�
	*  @param[out] emType ��ʾԴ����
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
    u16 SelDualInputPort( EmVgaType emType );

    /** ����   ������ʾԴ��Ϣ
	*  @param[in] tVgaInfo ��ʾԴ��Ϣ
    *  @param[in] bDefault �Ƿ�Ĭ����ʾԴ
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
    u16 SetDualPortInfo( const TVgaInfo& tVgaInfo, BOOL bDefault );

	/** ����   ����ϵͳ������Ϣ
	*  @param[in] tTPSleepInfo ϵͳ������Ϣ
    *  @param[in] bDefault �Ƿ�����ϵͳ����
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
    u16 SetSysSleepInfo( const TCenDevSleepInfo& tCenDevSleepInfo );

	/** ����   ���ϵͳ������Ϣ
	*  @param[out] tDualSrcinfo ��ʾԴ����
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
    u16 GetSysSleepInfo( TCenDevSleepInfo& tCenDevSleepInfo );

	/** ����   ̨���ļ��ϴ��ɹ�֪ͨ
	*  @param[in] byIndex ��Ϣ��������(0Ϊcnc 1Ϊά������)
	*  @return �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16 ConfSignCmd( const BOOL& bOk, u8 byIndex );

	//�ж�Ŀ¼�Ƿ����
	BOOL ExistDir( const CString strDir );
	
	//����Ŀ¼
    BOOL CreateDir( CString strDir );

	/**
    * ����:	 	        ���û�����ѡ��ʽ
	* @param [in]       
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  VideoFormatCmd( const TTPVidForamt& tVidForamt );
 
	/**
    * ����:	 	        ������ʾ��ѡ��ʽ
	* @param [in]       
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  DualVideoFormatCmd( const TTPVidForamt& tVidForamt );
 
	/**
    * ����:	 	        ���õ�������
	* @param [in]       
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  CallRateCmd( const u16 wCallRate );
 
	/**
    * ����:	 	        ������ʾ����
	* @param [in]       
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  DualCallRateCmd( const u16 wDualCallRate );
 
	/**
    * ����:	 	        ���û�������״̬
	* @param [in]       
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  ConfDisCmd( const BOOL& bDis );
 
	/**
    * ����:	 	        ���û�����ѯ��Ϣ
	* @param [in]       
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  ConfPollCmd( const TTPPollInfo& tPollInfo );
 
	/**
    * ����:	 	        �������л�֪ͨ
	* @param [in]       
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  ViewLocalPIPCmd( const u8 byScrnID, const BOOL bLocalP );
  
	/**
    * ����:	 	        ������Ƶ��ʽ��Ϣ
	* @param [in]       
	* @return           u16 �ɹ�����0,ʧ�ܷ��ط�0������
	*/
	u16  AudioFormatCmd( const EmTpAudioFormat& emAudioFormat );
 
	/** 
	* ����  	��ȡ������ѡ��ʽ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetVideoFormatInfo( TTPVidForamt& tVidForamt )const;
	/** 
	* ����  	��ȡ��ʾ��ѡ��ʽ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetDualVideoFormatInfo( TTPVidForamt& tVidForamt )const;
	/** 
	* ����  	��ȡ��������
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCallRateInfo( u16& wCallRate )const;
	/** 
	* ����  	��ȡ��ʾ����
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetDualCallRateInfo( u16& wDualCallRate )const;
	/** 
	* ����  	��ȡ������ѯ��Ϣ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetConfPollInfo( TTPPollInfo& tPollInfo )const;
	/** 
	* ����  	��ȡ����������Ϣ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetConfDisInfo( BOOL& bDis )const;
	/** 
	* ����  	��ȡ��Ƶ��ʽ��Ϣ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	EmTpAudioFormat GetAudioFormatInfo()const;
	/** 
	* ����  	���л��������
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	BOOL IsViewLocalPIP()const;

	/** 
	* ����  	��ȡ�пص���ǽ����״̬
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	BOOL GetDisplayState() const;

protected:
    /**
	* ����   ���ӵ�UMS 
	* @param [in]  dwIP	������UMS��IP��ַ��������
	* @param [in]  pStrUserName �û���	
	* @param [in]  pStrPswd	����
	* @return u16 �ɹ�����0;ʧ�ܷ��ط�0������ 
	*/
	u16 ConnectUms(); 


    
  /**
	* ����   ���ӵ�CNS 
	* @param [in]  dwIP	������UMS��IP��ַ��������
	* @param [in]  pStrUserName �û���	
	* @param [in]  pStrPswd	����
	* @return u16 �ɹ�����0;ʧ�ܷ��ط�0������ 
	*/
	u16 ConnectCns( /*u32 dwIp, u16 nPort, CString strUserName, CString strPswd */); 


protected:  
/** @defgroup  ��Ϣ��Ӧ����
 *  @{
 */	
	 
	afx_msg LRESULT OnRefreshConfTemplateLst(  WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnRefreshUserLst(  WPARAM wParam, LPARAM lParam ) ;
	
	/**ums�������*/
	afx_msg LRESULT OnRefreshConf( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnRefreshConfCnsLst( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnRefreshConfAudMixLst( WPARAM wParam, LPARAM lParam );
	afx_msg LRESULT OnRefreshConfPollLst( WPARAM wParam, LPARAM lParam ); 

    
    afx_msg LRESULT OnSpeakerNotify( WPARAM wParam, LPARAM lParam ); 
    afx_msg LRESULT OnSetSpeakerRsp( WPARAM wParam, LPARAM lParam ); 
    afx_msg LRESULT OnSetMuteCnsRsp( WPARAM wParam, LPARAM lParam ); 
    afx_msg LRESULT OnSetSlienceCnsRsp( WPARAM wParam, LPARAM lParam ); 
    afx_msg LRESULT OnSetDaulCnsRsp( WPARAM wParam, LPARAM lParam ); 
    afx_msg LRESULT OnDaulCnsUpdateNotify( WPARAM wParam, LPARAM lParam );     

    /*cns ���ػ������*/ 
    
    afx_msg LRESULT OnCnsEthnetInfoNotify( WPARAM wParam, LPARAM lParam );
    afx_msg LRESULT OnCnsRegSigServNotify( WPARAM wParam, LPARAM lParam );

    afx_msg LRESULT OnConnectCns(  WPARAM wParam, LPARAM lParam ) ;
	afx_msg LRESULT OnCnsInfoNotify( WPARAM wParam, LPARAM lParam );

	afx_msg LRESULT UpdateAddrBook( WPARAM wParam, LPARAM lParam );
	
	afx_msg LRESULT OnRefreshGlobalAddrBook( WPARAM wParam, LPARAM lParam );

    afx_msg LRESULT OnTPadLoginUserNty( WPARAM wParam, LPARAM lParam );

    //����ǽ
    //afx_msg LRESULT OnRefreshTvw(WPARAM wParam, LPARAM lParam);
    //afx_msg LRESULT OnPlayHduRsp(WPARAM wParam, LPARAM lParam);
    //afx_msg LRESULT OnStopHduRsp(WPARAM wParam, LPARAM lParam);
    //afx_msg LRESULT OnHduCodeStreamNotify(WPARAM wParam, LPARAM lParam);    
   
    DECLARE_MESSAGE_MAP()
/** @}*/ 

protected:

	void UpdateAddrList();
	void UpdateAddrEntryList();
	void UpdateAddrGroupList();
	void UpdateLevelOneGroup();
   
public:
    u16 LinkUms();
    u16 LinkCns();

    //���ӵ�TPad
    u16 ConnectTPad();
        
    //�޸�ϵͳ���� dyy 2013��8��29��
    u16 SetTpadSysName( string strSysName );
   
private:
/** @defgroup  ��Ա ��������
 *  @{
 */	
    //CUmsSessionCtrlIF   * m_pUmsSessionCtrl;  ///<ums�ĻỰ����
    CCnsSessionCtrlIF   *m_pCnsSession;       ///<cns�Ự
    TLoginInfo           m_tLoginInfo;
	u32	   m_dwCnsIp;	  //���ӵ�CNS��IP
	CLoginRequest   m_cUser; 
    
	/**UMS ��ؽӿ�*/
	//CConfTemplateCtrlIF *m_pConfTemplateCtrl;
	//CConfCtrlIF         *m_pConfCtrl;
	//CTvwCtrlIF          *m_pTvwCtrl;
	//CUmsConfigCtrlIF    *m_pUmsConfigCtrl;
	//CUserCtrlIF         *m_pUserCtrl;

	/**CNS ��ؽӿ�*/
	CCncConfigIF        *m_pCnsConfigCtrl;
	CCncConfCtrlIF      *m_pCnsConfCtrl;
    CUmcConfCtrlIF      *m_pUmsConfCtrl;
	CCncAddrbookIF      *m_pAddrBookCtrl;
	CCncUserCtrlIF      *m_pCnsUserCtrl;
	CCncSipInfoCtrlIF   *m_pSipInfoCtrl;
	CCncNetMngCtrlIF    *m_pNetMngCtrl;
	CCncPortDiagCtrlIF	*m_pPortDiagCtrl;
	CCncCenterCtrlIF    *m_pCenterCtrlIF;

	/**ums �������*/
	//TplArray<TTPConfTemplate> m_tplConfTempList;       ///< ����ģ���б�
	TplArray<CUserFullInfo>   m_tplUserList;           ///<�û��б�
	ARRAY<TCMSConf>           m_tplConfList;           ///<�����б�  ����� Bug00073719:ͬһ���᳡��������6�����޷��ٹҶϸû᳡�� 
    //TplArray<TCmsTvwInfo>     m_tplTvwList;            ///<����ǽ�б�
    
 
	/**cns �������*/
	vector<TAddrItem>         m_vctLocalAddrList;       //���ص�ַ��
	vector<TAddrItem>         m_vctGlobalAddrList;      //ȫ�ֵ�ַ��
    vector<TAddrItem>         m_vctEntryList;           //���ص�ַ��������Ŀ
	vector<TAddrItem>         m_vctGroupList;

	vector<TTPAlias>          m_vctConfTempList;        //����ģ���б�	

	static const u16 m_stcCstConnectUmsFail;			//���� umsʧ��
	static const u16 m_stcCstConnectUmsSuc;				//���� ums�ɹ�
	static const u16 m_stcCstConnectCnsFail;			//���� cns�ɹ�
	static const u16 m_stcCstConnectCnsOk;              //����cnsʧ��
	static const u16 m_stcCstConnectSuc;                //���ӳɹ�
	static const u16 m_stcCstConnectFail;               //����ʧ��
   
    TTPSipRegistrarCfg        m_tSipRegCfg;             ///<  ע��sip��������Ϣ
    TTPEthnetInfo             m_tServEthnetInfo;

	enum EM_ConnectState{
		emConnectNotStart,
			emConnectUmsFail,
			emConnectCnsFail,
			emConnectSuc,
			emConnectUmsSuc, 
			emConnectCnsSuc, 
	};
	EM_ConnectState                  m_emConnectState;                    //����״̬
/** @}*/ 
public:
	
	/** ��ȡ�ӿ�ָ�� */
	static CCommonInterface* GetCommIF();

   /**���ٽӿ�ָ�� */
    void DestroyCommIF();
    
	HWND GetRecvWnd(){return m_pMySelf->GetSafeHwnd();}
 
	virtual ~CCommonInterface();

private:
	CCommonInterface();
   
protected:
    virtual BOOL PreCreateWindow( CREATESTRUCT& cs );
    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam); 
    
    
private:
   static  CCommonInterface*  m_pMySelf;

  
   TTPConfTemplate      m_tCurConfTemplate;         ///<��ǰ�����Ļ�������

   TCMSConf                  m_tConfInfo;

/** @}*/   
};

#define ComInterface    CCommonInterface::GetCommIF()
#define BusinessManagePtr CCommonInterface::GetCommIF()
#endif // !defined(AFX_COMMONINTERFACE_H__E6AFC64B_E6AB_4404_930B_546D1178FF87__INCLUDED_)
