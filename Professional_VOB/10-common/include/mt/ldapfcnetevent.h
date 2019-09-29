
#ifndef LDAP_FCNET_EVENT_H
#define LDAP_FCNET_EVENT_H

#include "innereventcomm.h"

#ifndef _MakeMtEventDescription_

enum EmLdapFcnet
{
#endif
/***********************************************************/
/*                                                         */
/*                Ldap�����ص���Ϣ                            */
/*                                                         */
/***********************************************************/

    _ev_segment( ldapfcnet )
 
//////////////////////////////////////////////////////////////////////////
//������ص���Ϣ

/***********************<< ����ģ������ָʾ >>********************	
 *[��Ϣ��]			 
 * +BOOL          //�Ƿ�����������ģ��
 *   
 *[��Ϣ����]
 *   ui  => mtservice 
 */_event(  ev_FcNetInitialInd   )
   _body( BOOL, 1 )
   _ev_end

/***********************<< �����ú����������� >>********************	
 *[��Ϣ��]			 
 * +u32_ip          //Ŀ���ip��ַ
 * +u32             //���ʱʹ�õĳ�ʼ����  
 *
 *[��Ϣ����]
 *   ui  => mtservice 
 */_event(  ev_FcNetDetectBandWidthCmd   )
   _body( u32_ip, 1 )
   _body( u32, 1 )
   _ev_end


/***********************<< ���ú������ʼ��֪ͨ >>********************	
 *[��Ϣ��]			 
 * +u32_ip   //Ŀ���ַip
 * +u32      //��ǰ���õĴ���
 *   
 *[��Ϣ����]
 *   fcnet  => mtservice 
 */_event(  ev_FcNetDetectBandWidthInd   )
   _body( u32_ip, 1 )
   _body(u32 , 1 )
   _ev_end
   
/***********************<< ���ú������ʼ��֪ͨ >>********************	
 *[��Ϣ��]			 
 * +u32_ip   //Ŀ���ַip
 * +u32      //��ǰ���õĴ���
 *   
 *[��Ϣ����]
 *   mtservice  => mtservice
 */_event(  ev_FcNetMTDetectBandWidthInd   )
   _body( u32_ip, 1 )
   _body(u32 , 1 )
   _ev_end


/***********************<<  ע�ᵽĿ��ip��������� >>********************	
 *[��Ϣ��]			 
 * +u32_ip   //Ŀ���ַip
 * +u32      //�����ļ��ʱ��
 *   
 *[��Ϣ����]
 *   ui  => mtservice 
 */_event(  ev_FcNetRegisterDetectCmd   )
   _body( u32_ip, 1 )
   _body(u32 , 1 )
   _ev_end

/***********************<<  ע����Ŀ��ip��������� >>********************	
 *[��Ϣ��]			 
 * +u32_ip   //Ŀ���ַip
 * 
 *   
 *[��Ϣ����]
 *   ui  => mtservice 
 */_event(  ev_FcNetUnRegisterDetectCmd   )
   _body( u32_ip, 1 )
   _ev_end


/***********************<< ��ǰ�������֪ͨ >>********************	
 *[��Ϣ��]			 
 * +u32_ip   //Ŀ���ַip
 * +u32      //��ǰ���õĴ���
 *   
 *[��Ϣ����]
 *   ui  => mtservice 
 */_event(  ev_FcNetCurBandWidthInd   )
   _body( u32_ip, 1 )
   _body(u32 , 1 )
   _ev_end
   

//////////////////////////////////////////////////////////////////////////
/*
/*              ldap��ص���Ϣ
/* */
//////////////////////////////////////////////////////////////////////////

/***********************<< LDAP���ӳɹ�ָʾ >>********************	
 *[��Ϣ��]			 
 * +��
 *   
 *[��Ϣ����]
 *   mtservice  => mtservice 
 */_event(   ev_LdapConnectedInd  )
   _ev_end

/***********************<< LDAP����ָʾ >>********************	
 *[��Ϣ��]			 
 * +��
 *   
 *[��Ϣ����]
 *   mtservice  => mtservice 
 */_event(   ev_LdapDisconnectedInd  )
   _ev_end
   
/***********************<< LDAP���������Чָʾ >>********************	
 *[��Ϣ��]			 
 * +��
 *   
 *[��Ϣ����]
 *   mtservice  => mtservice 
 */_event(   ev_LdapMaxRetryFailedInd  )
   _ev_end

/***********************<< LDAP��֤��Ӧ >>********************	
 *[��Ϣ��]			 
 * +BOOL  //��֤�Ƿ�ͨ��
 *   
 *[��Ϣ����]
 *   mtservice  => mtservice 
 */_event(   ev_LdapAuthRsp  )
   _body( BOOL, 1 ) 
   _ev_end

/***********************<< LDAPע����Ӧ >>********************	
 *[��Ϣ��]			 
 * +BOOL  //ע���Ƿ�ɹ�
 *   
 *[��Ϣ����]
 *   mtservice  => mtservice 
 */_event(   ev_LdapRegisterRsp  )
   _body( BOOL, 1 ) 
   _ev_end

/***********************<< LDAPע����Ӧ >>********************	
 *[��Ϣ��]			 
 * +BOOL  //ע���Ƿ�ɹ�
 *   
 *[��Ϣ����]
 *   mtservice  => mtservice 
 */_event(   ev_LdapUnRegisterRsp  )
   _body( BOOL, 1 ) 
   _ev_end
   
/***********************<<  LDAP��ѯ������Ŀ��Ϣ��Ӧ >>********************	
 *[��Ϣ��]			 
 * + BOOL             //��ѯ�Ƿ�ɹ�
 * +                  //����ɹ�ʱ�����ز�ѯ���ն˵���Ϣ  
 *[��Ϣ����]
 *   mtservice  => mtservice 
 */_event(   ev_LdapSearchCallnumInfoRsp  )
   _body( u32 , 1 )
   _ev_end

/***********************<<  ��ѯ�����Ӧ����Ŀ��Ϣ���� >>********************	
 *[��Ϣ��]			 
 * +u8[]             //�Զ˵ĺ���
 *  
 *[��Ϣ����]
 *   mtservice  => mtservice 
 */_event(   ev_LdapSearchCallnumInfoCmd ) 
   _body( u8 , MT_LDAP_MAX_CALLNUM_LENGTH  )
   _ev_end

/***********************<<  ��ѯ�����Ӧ����Ŀ��Ϣָʾ >>********************	
 *[��Ϣ��]
 * +BOOL               //�����ѯ�Ƿ�ɹ�
 * +u32_ip             //�Զ˵ĺ���, ����Ӧ��ip��ַ
 *  
 *[��Ϣ����]
 *   mtservice  => mtservice 
 */_event(   ev_LdapSearchCallnumInfoInd )
   _body( BOOL,  1 )
   _body( u32_ip , 1 )
   _ev_end

//////////////////////////////////////////////////////////////////////////
/*
/*              ƽ��������ص���Ϣ
/* */
//////////////////////////////////////////////////////////////////////////
/***********************<< ����ƽ�����͹��� >>********************	
 *[��Ϣ��]
 * +u32_ip             //ƽ�����͵�Ŀ�ĵ�ַ
 * +u16 , port
 *  u32 dwRate         //ƽ����������
 *  u32 dwPeak         //��ֵ������
 *[��Ϣ����]
 *   mtservice  => mtservice 
 */_event(   ev_SmoothSendSetRule )
   _body( u32_ip , 1 )
   _body( u16, 1 )
   _body( u32,  1 )
   _body( u32,  1 )
   _ev_end

/***********************<< ȡ��ƽ�����͹��� >>********************	
 *[��Ϣ��]
 * +u32_ip             //Ŀ�ĵ�ַ
 * +u16, port
 *[��Ϣ����]
 *   mtservice  => mtservice 
 */_event(   ev_SmoothSendUnSetRule )
   _body( u32_ip , 1 )
   _body( u16, 1 ) 
   _ev_end

/***********************<< �ر�ƽ�����͹��� >>********************	
 *[��Ϣ��]
 *[��Ϣ����]
 *   mtservice  => mtservice 
 */_event(   ev_SmoothSendClose )
   _ev_end


#ifndef _MakeMtEventDescription_
   _ev_segment_end( ldapfcnet )
};
#endif

#endif