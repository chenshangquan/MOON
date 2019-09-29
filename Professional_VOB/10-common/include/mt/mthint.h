#ifndef _HINT_MSG_HEADER_
#define _HINT_MSG_HEADER_

#define MAX_HINTMSG_LEN    256

#ifndef _MakeHintDescription_

#define _hint_segment_fail_begin emHintMsgBegin = 0,

#define _hint_no( emHintId ) emHintId,
#define _hint_body( language, description )
#define _hint_end

#define _hint_segment_sucess_begin emHintMsgHalf = 3000,

#define _hint_segment_end emHintMsgEnd

enum EmHintMsgNo
{

#else

#define _hint_segment_fail_begin
#define _hint_segment_sucess_begin
#define _hint_segment_end

#endif 

/************************************************************************/
/*                            ʧ�ܵ���ʾ��                              */
/************************************************************************/
 _hint_segment_fail_begin

/***********************<< ����˫��ʧ�� >>*************************/	
_hint_no( emFailtoSendDual )
_hint_body( emEnglish, "peer not support the dual by current fmt and res" )
_hint_body( emChineseSB, "�Զ˲�֧�ֵ�ǰ��ʽ�ͷֱ����µ�˫��" )
_hint_end

/***********************<< ����˫��ʧ�� >>*************************/	
_hint_no( emFailtoRecvDual )
_hint_body( emEnglish, "not support peer's dual fmt or res" )
_hint_body( emChineseSB, "��������֧�ֶԶ˷����˫��" )
_hint_end

/***********************<< vod��¼ʧ�� >>*************************/	
_hint_no( emFailtoVodLogin )
_hint_body( emEnglish, "VOD login failled" )
_hint_body( emChineseSB, "VOD ��¼ʧ��" )
_hint_end

/***********************<< vod��¼��ʱ >>*************************/	
_hint_no( emFailtoVodConnect )
_hint_body( emEnglish, "VOD login time out" )
_hint_body( emChineseSB, "VOD ��¼��ʱ" )
_hint_end

/***********************<< DHCP��ȡ��ַ��ʱ >>*************************/	
_hint_no( emDHCPTimeOut )
_hint_body( emEnglish, "DHCP get ip time out" )
_hint_body( emChineseSB, "��ȡDHCP��ַ��ʱ" )
_hint_end

/***********************<< DHCP��ַ��Լ���� >>*************************/	
_hint_no( emDHCPOverdue )
_hint_body( emEnglish, "DHCP ip overdue" )
_hint_body( emChineseSB, "DHCP��ַ��Լ����" )
_hint_end


/***********************<< PPPOE�����֤���� >>*************************/	
_hint_no( emPPPoEAuthorError )
_hint_body( emEnglish, "PPPoE authentication error" )
_hint_body( emChineseSB, "PPPOE�����֤����" )
_hint_end

/***********************<< PPPOE�Ҳ��������� >>*************************/	
_hint_no( emPPPoEAgentError )
_hint_body( emEnglish, "PPPoE agent not exist" )
_hint_body( emChineseSB, "PPPOE�Ҳ���ISP������" )
_hint_end

/***********************<< PPPOE���ų�ʱ >>*************************/	
_hint_no( emPPPoETimeOutError )
_hint_body( emEnglish, "PPPoE dial time out" )
_hint_body( emChineseSB, "PPPOE���ų�ʱ" )
_hint_end

/***********************<< PPPOE���� >>*************************/	
_hint_no( emPPPoELinkDownError )
_hint_body( emEnglish, "PPPoE link down" )
_hint_body( emChineseSB, "PPPOE����" )
_hint_end

/***********************<< PPPOE�������� >>*************************/	
_hint_no( emPPPoEGeneralError )
_hint_body( emEnglish, "PPPoE General down" )
_hint_body( emChineseSB, "PPPOE��������" )
_hint_end

/***********************<< ����˫��ʧ�� >>*************************/	
_hint_no( emFailtoSendDualAsBeject )
_hint_body( emEnglish, "peer reject to receive dual video" )
_hint_body( emChineseSB, "��Զ˵�ý��������ƥ��, ����˫��ʧ��" )
_hint_end

/***********************<< LDAP����������ʧ�� >>*************************/	
_hint_no( emFailtoConnectLdapSvr )
_hint_body( emEnglish, "Failed to connect to LDAP server" )
_hint_body( emChineseSB, "LDAP����������ʧ�ܻ����" )
_hint_end

/***********************<< LDAP������Ŀ������ >>*************************/	
_hint_no( emLdapEntryNotExist )
_hint_body( emEnglish, "The inquired entry doesn't exist" )
_hint_body( emChineseSB, "����ѯ��LDAP��Ŀ������" )
_hint_end

/**************<< ����������Ч���µ�MC������չʧ�� >>**************/	
_hint_no( emCallRateNotValidForMc )
_hint_body( emEnglish, "Call rate isn't valid for Mc" )
_hint_body( emChineseSB, "�������ʹ���,�ܾ�MC��չ" )
_hint_end

/***********************<< 1080p/iʱ���ͻ����˫��ʧ����ʾ >>*************************/	
_hint_no( em1080pDualFail )
_hint_body( emEnglish, "Dual failed when current display 1080p/i!" )
_hint_body( emChineseSB, "��ǰ����ֱ���Ϊ1080p/i,˫��ʧ��!" )
_hint_end

/***********************<< 720p/iʱ���ͻ����˫��ʧ����ʾ >>*************************/	
_hint_no( em720pDualFail )
_hint_body( emEnglish, "Dual failed when resolution 720p,>30fps!" )
_hint_body( emChineseSB, "��ǰ����ֱ���Ϊ720p����30֡/��,˫��ʧ��!" )
_hint_end

/***********************<< 1080ʱֻ������VGA˫��ʧ����ʾ >>*************************/	
_hint_no( em1080pNotVGADualFail )
_hint_body( emEnglish, "Only vga or PC dual when priom video 1080p!" )
_hint_body( emChineseSB, "��ǰ����ֱ���Ϊ1080p,ʵʱ˫��ʧ��!" )
_hint_end

/***********************<< 1080Դʱ���ܷ���ʵʱ˫��ʧ����ʾ >>*************************/	
_hint_no( em1080pSrcRealTimeDualFail )
_hint_body( emEnglish, "Only vga or PC dual when dual video source 1080p/i!" )
_hint_body( emChineseSB, "��ǰ�ڶ�·��ƵԴΪ1080p/i,ʵʱ˫��ʧ��!" )
_hint_end

/************************************************************************/
/*                            �ɹ�����ʾ��                              */
/************************************************************************/

 _hint_segment_sucess_begin
/***********************<< ����˫���ɹ� >>*************************/	
_hint_no( emSuccedetoSendDual )
_hint_body( emEnglish, "succeed to send dual video stream" )
_hint_body( emChineseSB, "����˫���ɹ�" )
_hint_end

/***********************<< ����˫���ɹ� >>*************************/	
_hint_no( emSuccedetoRecvDual )
_hint_body( emEnglish, "succeed to receive dual video stream" )
_hint_body( emChineseSB, "����˫���ɹ�" )
_hint_end

/***********************<< �澯VGA/Video�л����� >>*************************/	
_hint_no( emWillSwitchVgaVideoRestart )
_hint_body( emEnglish, "Persist pushing for 10s to switch VGA/Video" )
_hint_body( emChineseSB, "�������ü�ʮ����л�VGA/Video!" )
_hint_end

/***********************<< PPPOE���ųɹ� >>*************************/	
_hint_no( emPPPoELinkUp )
_hint_body( emEnglish, "PPPoE link up" )
_hint_body( emChineseSB, "PPPOE���ųɹ�" )
_hint_end

/***********************<< PCMTû��ע��GK,û�л��鹦�� >>*************************/	
_hint_no( emPCMTNoGKNoConf )
_hint_body( emEnglish, "PCMT Unregister GK, can't make/join conference!" )
_hint_body( emChineseSB, "PCMTδע��GK, ���ܿ���!" )
_hint_end

/***********************<< ��ʾ�ն˽���MCU��ѵ�� >>*************************/	
_hint_no( emBePolledNext )
_hint_body( emEnglish, "This Meeting-terminal will be polled by MCU soon!" )
_hint_body( emChineseSB, "���ն˼�����MCU��ѯ��!" )
_hint_end


/***********************<< D1ʱ���ͻ����˫��ʧ����ʾ >>*************************/	
_hint_no( emD1DualFial )
_hint_body( emEnglish, "Dual failed when current display 4CIF!" )
_hint_body( emChineseSB, "��ǰ����ֱ���Ϊ4CIF,˫��ʧ��!" )
_hint_end




/***********************<< Gk���õ�δע��ɹ����ҶϺ�����ʾ >>*************************/	
_hint_no( emGkFailForbidCall )
_hint_body( emEnglish, "Forbid call when Gk register failed!" )
_hint_body( emChineseSB, "Gkע�᲻�ɹ���ֹ���У�" )
_hint_end


/***********************<< ����˫��ʧ�� >>*************************/	
_hint_no( emFailtoSendDualMcNotSpeak )
_hint_body( emEnglish, "peer not support the dual by current fmt and res, or peer only permit spokesman send dual" )
_hint_body( emChineseSB, "�Զ˲�֧�ֵ�ǰ��ʽ�ͷֱ����µ�˫�������߶Զ�ֻ�������˷���˫��" )
_hint_end


/***********************<< �������óɹ� >>*************************/	
_hint_no( emEthSetSuccess1 )
_hint_body( emEnglish, "Network ports settings succeeded, current available network port is LAN1" )
_hint_body( emChineseSB, "�������óɹ�, ����������1" )
_hint_end


/***********************<< �������óɹ� >>*************************/	
_hint_no( emEthSetSuccess2 )
_hint_body( emEnglish, "Network ports settings succeeded, current available network port is LAN2" )
_hint_body( emChineseSB, "�������óɹ�, ����������2" )
_hint_end

_hint_no( emDualFailInterlace720)
_hint_body( emEnglish, "Dual Video Stream is forbade, because second video source is interlace standard and the resolution capacity of send channel is 4CIF or 720P." )
_hint_body( emChineseSB, "���ڵڶ�·ԴΪi��, �ҷ���ͨ������Ϊ4CIF��720p, ����������޷�����˫��" )
_hint_end

/***********************<< VGA��λʱ�����ò��ɹ� >>*************************/	
_hint_no( emSetVGAPhaseClockFail )
_hint_body( emEnglish, "Set VGA Phase Clock Not Success" )
_hint_body( emChineseSB, "VGA��λʱ�����ò��ɹ�" )
_hint_end

/***********************<< VGA�˲�״̬���ò��ɹ� >>*************************/	
_hint_no( emSetVGAFiltStatusFail )
_hint_body( emEnglish, "Set Filter Status Not Success" )
_hint_body( emChineseSB, "VGA�˲�״̬���ò��ɹ�" )
_hint_end

/***********************<< SIPע��ɹ� >>*************************/	
_hint_no( emSipRegisterSuccess )
_hint_body( emEnglish, "SIP Register Success" )
_hint_body( emChineseSB, "SIPע��ɹ�" )
_hint_end

/***********************<< SIPע��ʧ�� >>*************************/	
_hint_no( emSipRegisterFail )
_hint_body( emEnglish, "SIP Register Fail" )
_hint_body( emChineseSB, "SIPע��ʧ��" )
_hint_end

/***********************<< SIPע���ɹ� >>*************************/	
_hint_no( emSipUnregisterSuccess )
_hint_body( emEnglish, "SIP Unregister Success" )
_hint_body( emChineseSB, "SIPע���ɹ�" )
_hint_end

/***********************<< ����ƵԴ����˫��ʧ�� >>*************************/	
_hint_no( emNoVidSrcDualFail )
_hint_body( emEnglish, "Dual failed for invalid dual video source!" )
_hint_body( emChineseSB, "�ڶ�·��ƵԴ��Ч,˫��ʧ��!" )
_hint_end

_hint_segment_end

#ifndef _MakeHintDescription_
};
#endif 



#undef _hint_no 
#undef _hint_body 
#undef _hint_end 
#undef _hint_segment_fail_begin
#undef _hint_segment_sucess_begin
#undef _hint_segment_end

#endif 


