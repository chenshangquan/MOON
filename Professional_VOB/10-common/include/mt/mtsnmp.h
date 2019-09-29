#include "tptype.h"



//�ն��ͺ�
const u32  MTSYSHARDWARETYPE_UNKNOWNMTMODEL   = 0;//(u32)emUnknownMtModel ;
const u32  MTSYSHARDWARETYPE_PCMT             = 1;//(u32)emPCMT ;//�����ն�
const u32  MTSYSHARDWARETYPE_8010             = 2;//(u32)em8010 ;
const u32  MTSYSHARDWARETYPE_8010A            = 3;//(u32)em8010A ;
const u32  MTSYSHARDWARETYPE_8010APLUS        = 4;//(u32)em8010Aplus ;//8010A+
const u32  MTSYSHARDWARETYPE_8010C            = 5;//(u32)em8010C ;
const u32  MTSYSHARDWARETYPE_8010C1           = 6;//(u32)em8010C1 ;
const u32  MTSYSHARDWARETYPE_IMT              = 7;//(u32)emIMT ;
const u32  MTSYSHARDWARETYPE_8220A            = 8;
const u32  MTSYSHARDWARETYPE_5210             = 9;//(u32)em8220B;
const u32  MTSYSHARDWARETYPE_V5               = 10;//(u32)em8220C;
const u32  MTSYSHARDWARETYPE_3210             = 11;//(u32)em8620A;
const u32  MTSYSHARDWARETYPE_6610E            = 12;//(u32)emTS6610E;
const u32  MTSYSHARDWARETYPE_6210             = 13;//(u32)emTS6210;
const u32  MTSYSHARDWARETYPE_8010A_2          = 14;//(u32)em8010A_2 ;
const u32  MTSYSHARDWARETYPE_8010A_4          = 15;//(u32)em8010A_4 ;
const u32  MTSYSHARDWARETYPE_8010A_8          = 16;//(u32)em8010A_8 ;
const u32  MTSYSHARDWARETYPE_7210             = 17;//(u32)em7210 ;
const u32  MTSYSHARDWARETYPE_7610             = 18;//(u32)em7610 ;
const u32  MTSYSHARDWARETYPE_5610             = 19;//(u32)emTS5610 ;
const u32  MTSYSHARDWARETYPE_6610             = 20;//(u32)emTS6610 ;
const u32  MTSYSHARDWARETYPE_7810             = 21;//(u32)em7810 ;
const u32  MTSYSHARDWARETYPE_7910             = 22;//(u32)em7910 ;
const u32  MTSYSHARDWARETYPE_7620_4           = 23;//(u32)em7620_A ;
const u32  MTSYSHARDWARETYPE_7620_2           = 24;//(u32)em7620_B ;
const u32  MTSYSHARDWARETYPE_7820_A           = 25;//(u32)em7820_A ;
const u32  MTSYSHARDWARETYPE_7820_B           = 26;//(u32)em7820_B ;
const u32  MTSYSHARDWARETYPE_7920_A           = 27;//(u32)em7920_A ;
const u32  MTSYSHARDWARETYPE_7920_B           = 28;//(u32)em7920_B ;

const u32  MTUSED    = TRUE;
const u32  MTNOTUSED = FALSE;

//TOS ����	
const u32  MTQOSTOS_TOSNONE           = (u32)emTOSNone;//��ʹ�� ; 
const u32  MTQOSTOS_TOSMINCOST        = (u32)emTOSMinCost ; //��С����
const u32  MTQOSTOS_TOSMAXRELIABLE    = (u32)emTOSMaxReliable ;// ��߿ɿ���
const u32  MTQOSTOS_TOSMAXTHRUPUT     = (u32)emTOSMaxThruput ; //���������
const u32  MTQOSTOS_TOSMINDELAY       = (u32)emTOSMinDelay ;//��С�ӳ�

//E1��֤����
const u32  MTE1CONFIGAUTHENTICATIONTYPE_PAP    = (u32)emPAP ;
const u32  MTE1CONFIGAUTHENTICATIONTYPE_CHAP   = (u32)emCHAP ;

//E1��·�������
const u32  MTE1UNITPROTOCOL_PPP                = (u32)emPPP ;
const u32  MTE1UNITPROTOCOL_HDLC               = (u32)emHDLC ;
const u32  MTE1UNITPROTOCOL_PPPOE              = (u32)emPPPOE ;
const u32  MTE1UNITPROTOCOL_MP                 = (u32)emMP ;

//��������
const u32  MTCAMERACFGSERIALTYPE_RS232           = (u32)emRS232 ;
const u32  MTCAMERACFGSERIALTYPE_RS422           = (u32)emRS422 ;
const u32  MTCAMERACFGSERIALTYPE_RS485           = (u32)emRS485 ;
const u32  MTCAMERACFGSERIALTYPE_SERIALTCPIP     = (u32)emSerialTcpip ;

//����У��λ����
const u32  MTSERIALCFGCHECK_NOCHECK              = (u32)emNoCheck ;//��У��
const u32  MTSERIALCFGCHECK_ODDCHECK             = (u32)emOddCheck ;//��У��
const u32  MTSERIALCFGCHECK_EVENCHECK            = (u32)emEvenCheck ;//żУ��

//����ֹͣλ����
const u32  MTSERIALCFGSTOPBITS_1STOPBIT          = (u32)em1StopBit ;
const u32  MTSERIALCFGSTOPBITS_1HALFSTOPBITS     = (u32)em1HalfStopBits ;
const u32  MTSERIALCFGSTOPBITS_2STOPBITS         = (u32)em2StopBits ;

//��Ƶ��ʽ����
const u32  MTVIDEO1INVIDEOSTANDARD_PAL           = (u32)emPAL ;
const u32  MTVIDEO1INVIDEOSTANDARD_NTSC          = (u32)emNTSC ;

//��ƵЭ������
const u32  MTVIDEO1PRIORSTRATEGY_VH261              = (u32)emVH261 ;
const u32  MTVIDEO1PRIORSTRATEGY_VH262              = (u32)emVH262 ;//MPEG2
const u32  MTVIDEO1PRIORSTRATEGY_VH263              = (u32)emVH263 ;
const u32  MTVIDEO1PRIORSTRATEGY_VH263PLUS          = (u32)emVH263plus ;
const u32  MTVIDEO1PRIORSTRATEGY_VH264              = (u32)emVH264 ;
const u32  MTVIDEO1PRIORSTRATEGY_VMPEG4             = (u32)emVMPEG4 ;
const u32  MTVIDEO1PRIORSTRATEGY_VEnd               = (u32)emVEnd ;

//�ֱ�������
//const u32  MTVIDEO1RESOLUTION_VRESOLUTIONAUTO = (u32)emVResolutionAuto ;
//const u32  MTVIDEO1RESOLUTION_VQCIF           = (u32)emVQCIF ;
//const u32  MTVIDEO1RESOLUTION_VCIF            = (u32)emVCIF ;
//const u32  MTVIDEO1RESOLUTION_V2CIF           = (u32)emV2CIF ;
//const u32  MTVIDEO1RESOLUTION_V4CIF           = (u32)emV4CIF ;
//const u32  MTVIDEO1RESOLUTION_V16CIF          = (u32)emV16CIF ;
//const u32  MTVIDEO1RESOLUTION_VGA352240       = (u32)emVGA352240 ;
//const u32  MTVIDEO1RESOLUTION_VGA704480       = (u32)emVGA704480 ;
//const u32  MTVIDEO1RESOLUTION_VGA640480       = (u32)emVGA640480 ;
//const u32  MTVIDEO1RESOLUTION_VGA800600       = (u32)emVGA800600 ;
//const u32  MTVIDEO1RESOLUTION_VGA1024768      = (u32)emVGA1024768 ;
// const u32  MTVIDEO1RESOLUTION_VRESEND         = (u32)emVResEnd ;

//�ն���Ƶ�˿�
const u32  MTVIDEO1SOURCE_MTVGA                  = (u32)emMtVGA ;//VGA 
const u32  MTVIDEO1SOURCE_MTSVID                 = (u32)emMtSVid ;//S ����
const u32  MTVIDEO1SOURCE_MTPC                   = (u32)emMtPC ;//PC
const u32  MTVIDEO1SOURCE_MTC1VID                = (u32)emMtC1Vid ;//C1����
const u32  MTVIDEO1SOURCE_MTC2VID                = (u32)emMtC2Vid ;//C2����
const u32  MTVIDEO1SOURCE_MTC3VID                = (u32)emMtC3Vid ;//C3����
const u32  MTVIDEO1SOURCE_MTC4VID                = (u32)emMtC4Vid ;//C4����
const u32  MTVIDEO1SOURCE_MTC5VID                = (u32)emMtC5Vid ;//C5����
const u32  MTVIDEO1SOURCE_MTC6VID                = (u32)emMtC6Vid ;//C6����

//��ƵЭ������
const u32  MTAUDIOENCFORMAT_AG711A                = (u32)emAG711a ;
const u32  MTAUDIOENCFORMAT_AG711U                = (u32)emAG711u ;
const u32  MTAUDIOENCFORMAT_AG722                 = (u32)emAG722 ;
const u32  MTAUDIOENCFORMAT_AG7231                = (u32)emAG7231 ;
const u32  MTAUDIOENCFORMAT_AG728                 = (u32)emAG728 ;
const u32  MTAUDIOENCFORMAT_AG729                 = (u32)emAG729 ;
const u32  MTAUDIOENCFORMAT_AMP3                  = (u32)emAMP3 ;
const u32  MTAUDIOENCFORMAT_AEND                  = (u32)emAEnd ;

//�����㷨
const u32  MTLOCALINFOENCRYARITHMETIC_ENCRYPTNONE      = (u32)emEncryptNone ;
const u32  MTLOCALINFOENCRYARITHMETIC_DES              = (u32)emDES ;
const u32  MTLOCALINFOENCRYARITHMETIC_AES              = (u32)emAES ;
const u32  MTLOCALINFOENCRYARITHMETIC_ENCRYPTAUTO      = (u32)emEncryptAuto ;

//��������
const u32  MTLOCALINFOLANGUAGE_ENGLISH             = (u32)emEnglish ;
const u32  MTLOCALINFOLANGUAGE_CHINESESB           = (u32)emChineseSB ;

//̨������
const u32  MTDISPLAYCFGSYMBOLSHOWMODE_LABELAUTO      = (u32)emLabelAuto ;//�Զ�
const u32  MTDISPLAYCFGSYMBOLSHOWMODE_LABELUSERDEF   = (u32)emLabelUserDef ;//�Զ���
const u32  MTDISPLAYCFGSYMBOLSHOWMODE_LABELOFF       = (u32)emLabelOff ; //�ر�

//˫����ʾģʽ
const u32  MTDISPLAYCFGDUALVIDEOSHOWMODE_DUALVIDEOONSIGLESCREEN   = (u32)emDualVideoOnSigleScreen ;//����˫��
const u32  MTDISPLAYCFGDUALVIDEOSHOWMODE_EACHVIDEOOWNSCREEN       = (u32)emEachVideoOwnScreen ;//˫��˫��

//Ӧ��ʽ����
const u32  MTCALLCFGANSWERMODE_TRIPMODENEGATIVE         = (u32)emTripModeNegative ;//�ܾ����ر�
const u32  MTCALLCFGANSWERMODE_TRIPMODEAUTO             = (u32)emTripModeAuto ;//�Զ�
const u32  MTCALLCFGANSWERMODE_TRIPMODEMANU             = (u32)emTripModeManu ;//�ֶ�



//////////////////////////�澯��Ϣ///////////////////////////////////////////
//ϵͳ״̬
const u32  MTSYSSTATE_RUNNING   = 1;//ϵͳ����
const u32  MTSYSSTATE_REBOOT	= 2;//ϵͳ����
const u32  MTSYSSTATE_DOWN   = 3;//ϵͳ�ϵ�




//E1��·״̬�ı�,����Ϊ4��
#define GETE1NUM4INFO(dwVal) (u8)(dwVal & 0xFF)
#define GETE1NUM3INFO(dwVal) (u8)((dwVal >> 8) & 0xFF)
#define GETE1NUM2INFO(dwVal) (u8)((dwVal >> 16) & 0xFF)
#define GETE1NUM1INFO(dwVal) (u8)((dwVal >> 24) & 0xFF)
//ÿ��ĺ�������,��ӦλΪ1��澯��Ϊ0������
const u8 MTE1_NORMAL = 0;
const u8 MTE1_TRAP   = 1;
// E1ȫ1�澯   
#define GET_MTE1LINE_ALL1(byVal) (u8)(byVal & 0x1) 
//E1ʧͬ���澯 
#define GET_MTE1LINE_UNSYNCHRONIZATION(byVal) (u8)(byVal &0x2)
//E1Զ�˸澯
#define GET_MTE1LINE_REMOTEALARM(byVal) (u8)(byVal & 0x4)
//E1ʧ�ز��澯
#define GET_MTE1LINE_UNCARRIERWAVE(byVal) (u8)(byVal & 0x8)
//E1��CRC��֡����澯
#define GET_MTE1LINE_UNCRCERROR(byVal) (u8)(byVal & 0x10)
//E1��·��֡����澯
#define GET_MTE1LINE_RMERROR(byVal) (u8)(byVal & 0x20)



//����״̬�ı�
//��16λΪ����id��
#define GETTASKID(dwVal) (u16)(dwVal >> 16)
//����״̬,Ϊ1������æ��Ϊ0������
const u16 MTTASK_RUNNING   =  1;//����æ
const u16 MTTASK_STOP      =  0;//��������
#define GETTASKSTATUS(dwVal) (u16)(dwVal & 0xFFFF)



// MAP״̬�ı�
//map��
#define GET_MAPID(dwVal) (u8)(dwVal >> 24)
//MAP״̬
const u8 MTMAP_NATURAL    = 0;//����
const u8 MTMAP_ABNOMIT    = 1;//����
#define GET_MAPSTATUS(dwVal) (u8)((dwVal >> 16) & 0xFF)
// ��16λ��ʾ��MAP��������
#define GET_MAPSTOPTIMES(dwVal) (u16)(dwVal & 0xFFFF)


//��̫��״̬�ı� 
//��ȡ������
#define GET_ETHERNETID(dwVal) (u16)(dwVal >> 16)
//��̫��״̬��0 ������1���߶Ͽ�
const u16  MTETHERNET_NORMAL = 0;
const u16  MTETHERNET_DOWN   = 1;
#define GET_ETHERNETSTATUS(dwVal) (u16)(dwVal & 0xFFFF)


// ����״̬�ı�
//��ȡ���Ⱥ�
#define GET_FAINID(dwVal) (u8)(dwVal >> 16)
//����״̬����Ӧλ���Ϊ1���ʾ������0���ʾ�쳣
const u8 MTTASKNOMAL = 1;
const u8 MTTASKABNOMAL = 0;
#define GET_FAIN_STATUS(dwVal) (u8)(dwVal & 0xFFFF)


// V35״̬�ı�
//1Ϊ������0Ϊ����
const u8 MTV35_TRAP = 1;
const u8 MTV35_NORMAL = 0;
//Carrier Detect, �ز����ʧ��
#define GET_MTV35_CARRIERDETECTDOWN(dwVal) (u8)(dwVal & 0x1)
//Clear To Send, �������ʧ��
#define GET_MTV35_CLEARTOSEND(dwVal)       (u8)(dwVal & 0x2)
//Request To Send, ������ʧ��
#define GET_MTV35_REQUESTTOSEND(dwVal)     (u8)(dwVal & 0x4)
//�����ն�δ����
#define GET_MTV35_DATAMTUNREADY(dwVal)     (u8)(dwVal & 0x8)
//����δ׼����
#define GET_MTV35_DATAUNREADY(dwVal)       (u8)(dwVal & 0x10)


// -------- �����¶�״̬�ı�����ӿڡ����� ---------
#define MT_BRD_TEMP_TRAP           (u8)1
#define MT_BRD_TEMP_NORMAL         (u8)0 
#define GET_BRD_TEMP_STATUS(dwVal) (u8)(dwVal & 0xFFFF)
// -------- ���ӵ�ѹ״̬�ı�����ӿڡ����� ---------
#define MT_BRD_VOLT_TRAP           (u8)1
#define MT_BRD_VOLT_NORAML         (u8)0
#define GET_BRD_VOLT_STATUS(dwVal) (u8)(dwVal & 0xFFFF)


//����״̬֪ͨ
//ָʾ����˸״̬
const u8 BRD_LED_NOT_EXIST   =              0;      /* ������ */
const u8 BRD_LED_STATE_ON    =              1;      /* �� */
const u8 BRD_LED_STATE_OFF   =              2;      /* �� */
const u8 BRD_LED_STATE_QUICK =              3;      /* ���� */
const u8 BRD_LED_STATE_SLOW  =              4;      /* ���� */

//����
//�����Ͻӿ�
#define GET_PANELLED_POWER(dwVal) (u8)((0x3   &  dwVal           ) + 1)
#define GET_PANELLED_ALM(dwVal)   (u8)((0x3   &  (dwVal >> 2)    ) + 1)
#define GET_PANELLED_RUN(dwVal)   (u8)((0x3   &  (dwVal >> 4)    ) + 1)
#define GET_PANELLED_LINK(dwVal)  (u8)((0x3   &  (dwVal >> 6)    ) + 1)
#define GET_PANELLED_DSP1(dwVal)  (u8)((0x3   &  (dwVal >> 8)    ) + 1)
#define GET_PANELLED_DSP2(dwVal)  (u8)((0x3   &  (dwVal >> 10)   ) + 1)
#define GET_PANELLED_DSP3(dwVal)  (u8)((0x3   &  (dwVal >> 12)   ) + 1)
#define GET_PANELLED_ETH1(dwVal)  (u8)((0x3   &  (dwVal >> 14)   ) + 1)
#define GET_PANELLED_ETH2(dwVal)  (u8)((0x3   &  (dwVal >> 16)   ) + 1)
#define GET_PANELLED_ETH3(dwVal)  (u8)((0x3   &  (dwVal >> 18)   ) + 1)
#define GET_PANELLED_IR(dwVal)    (u8)((0x3   &  (dwVal >> 20)   ) + 1)

//�����½ӿ�
enum EmLedComponent
{
	emLedStatusPower = 0,
	emLedStatusAlarm,
	emLedStatusRun,
	emLedStatusLink,
	emLedStatusDSP1,
	emLedStatusDSP2,
	emLedStatusDSP3,     // 8010C�������
	emLedStatusETH1,
	emLedStatusIR,
	emLedStatusEnd
};

//T2��LED�����½ӿ�
//add by xujinxing,2007-5-9
enum  EmT2LedComponent
{
	emT2LedStatusGreen =0,
	emT2LedStatusOrange,
	emT2LedStatusEnd
};

inline u8 mtGetLedStatus(EmLedComponent emLedStatus, const s8* pbyBuf)
{
	if ( strlen(pbyBuf) > emLedStatusEnd + 1)
	{
		return BRD_LED_NOT_EXIST;
	}
	u8 byRel = pbyBuf[emLedStatus] - '0';
	return byRel;
}

inline u32 mtModel2HwType( EmMtModel emModel )
{
	switch ( emModel )
	{
	case emUnknownMtModel:
		return MTSYSHARDWARETYPE_UNKNOWNMTMODEL;
	case emPCMT:
		return MTSYSHARDWARETYPE_PCMT;
	case em8010:
		return MTSYSHARDWARETYPE_8010;
	case em8010A:
		return MTSYSHARDWARETYPE_8010A;
	case em8010Aplus:
		return MTSYSHARDWARETYPE_8010APLUS;
	case em8010C:
		return MTSYSHARDWARETYPE_8010C;
	case em8010C1:
		return MTSYSHARDWARETYPE_8010C1;
	case emIMT:
		return MTSYSHARDWARETYPE_IMT;
	case em8220A:
		return MTSYSHARDWARETYPE_8220A;
	case em8220B:
		return MTSYSHARDWARETYPE_5210;
	case em8220C:
		return MTSYSHARDWARETYPE_V5;
	case em8620A:
		return MTSYSHARDWARETYPE_3210;
	case emTS6610E:
		return MTSYSHARDWARETYPE_6610E;
	case emTS6210:
		return MTSYSHARDWARETYPE_6210;
	case em8010A_2:
		return MTSYSHARDWARETYPE_8010A_2;
	case em8010A_4:
		return MTSYSHARDWARETYPE_8010A_4;
	case em8010A_8:
		return MTSYSHARDWARETYPE_8010A_8;
	case em7210:
		return MTSYSHARDWARETYPE_7210;
	case em7610:
		return MTSYSHARDWARETYPE_7610;
	case emTS5610:
		return MTSYSHARDWARETYPE_5610;
	case emTS6610:
		return MTSYSHARDWARETYPE_6610;
	case em7810:
		return MTSYSHARDWARETYPE_7810;
	case em7910:
		return MTSYSHARDWARETYPE_7910;
	case em7620_A:
		return MTSYSHARDWARETYPE_7620_4;
	case em7620_B:
		return MTSYSHARDWARETYPE_7620_2;
	case em7820_A:
		return MTSYSHARDWARETYPE_7820_A;
	case em7820_B:
		return MTSYSHARDWARETYPE_7820_B;
	case em7920_A:
		return MTSYSHARDWARETYPE_7920_A;
	case em7920_B:
		return MTSYSHARDWARETYPE_7920_B;
    default:
		OspPrintf( TRUE, FALSE, "err, wrong mt model->%d!\n", (u32)emModel );
		return MTSYSHARDWARETYPE_UNKNOWNMTMODEL;
	}
}

//�豸����״̬�ı�
//�豸���ͣ�������
#define GETEQPTYPE(dwVal) (u8)(dwVal >> 24)
//�豸���
#define GETEQPNUM(dwVal) (u8)((dwVal >> 16) & 0xFF)
//��16λ��ʾ�豸״̬ 1 ���� 2������ 3��֪��
const u32 MTEQPCONN_ONLINE   = 1;
const u32 MTEQPCONN_UNONLINE = 2;
const u32 MTEQPCONN_UNKNOWN  = 3;
#define GETEQPSTATUS(dwVal) (u16)(dwVal & 0xFFFF)

// CCI״̬�ı�
//MAP��
#define GETMAPID(dwVal)   (u8)(dwVal >> 24)
//updwon״̬
//0 ���� 1 ����
const u8 MTCCI_UP = 0;
const u8 MTCCI_DWON = 1;
#define GETUPDOWN(dwVal)  (u8)((dwVal >> 16) & 0xFF)
//���к�
#define GETQUEUEID(dwVal) (u8)((dwVal >> 8) & 0xFF)
//����״̬
// 0 ����  1 ��
const u8 MTCCI_NORMOL = 0;
const u8 MTCCI_FULL   = 1;
#define GETSTATUS(dwVal)  (u8)(dwVal & 0xFF)


// ý����״̬
//ý������(������
#define GETMEDIATYPE(dwVal) (u16)(dwVal >> 16)
//��״̬ 0 ���������� 1 ���́G��
const u16 MTMEDIARCVNOCODESTREAM = 0;
const u16 MTMEDIASNDLOSSPACKEGE  = 1;
#define GETMEDIASTREAMSTATUS(dwVal) (u16)(dwVal & 0xFFFF)

// �ڴ�״̬�ı�
/*
		����
*/

// �ļ�ϵͳ״̬�ı�
/*
		����
*/

// ��ƵԴ״̬�ı�
/*
		����
*/






//����Ϊû��ʵ�ֵ�

/*
//const u32  MTEQPMATRIXENTRY                = 1 ;       //"1.3.6.1.4.1.8888.1.2.1.3.3.1"
const u32  MTEQPMATRIXENTID                = 96 ;       //"1.3.6.1.4.1.8888.1.2.1.3.3.1.1"
const u32  MTEQPMATRIXENTTYPE              = 97 ;       //"1.3.6.1.4.1.8888.1.2.1.3.3.1.2"
const u32  MTEQPMATRIXENTSVRIPADDR         = 98 ;       //"1.3.6.1.4.1.8888.1.2.1.3.3.1.3"
const u32  MTEQPMATRIXENTPORT              = 99 ;       //"1.3.6.1.4.1.8888.1.2.1.3.3.1.4"
const u32  MTEQPMATRIXENTEXIST             = 100 ;      //"1.3.6.1.4.1.8888.1.2.1.3.3.1.5"

const u32  MTEQPNETENCODERID               = 102 ;      //"1.3.6.1.4.1.8888.1.2.1.3.4.1.0"
*/

/*


const u32  MTPFMENCODERVIDEOFRAMERATE      = 158 ;      //"1.3.6.1.4.1.8888.1.2.1.5.3.1.1.0"
const u32  MTPFMENCODERVIDEOBITRATE        = 159 ;      //"1.3.6.1.4.1.8888.1.2.1.5.3.1.2.0"
const u32  MTPFMENCODERAUDIOBITRATE        = 160 ;      //"1.3.6.1.4.1.8888.1.2.1.5.3.1.3.0"
const u32  MTPFMENCODERVIDEOPACKLOSE       = 161 ;      //"1.3.6.1.4.1.8888.1.2.1.5.3.1.4.0"
const u32  MTPFMENCODERVIDEOPACKERROR      = 162 ;      //"1.3.6.1.4.1.8888.1.2.1.5.3.1.5.0"
const u32  MTPFMENCODERAUDIOPACKLOSE       = 163 ;      //"1.3.6.1.4.1.8888.1.2.1.5.3.1.6.0"
const u32  MTPFMENCODERAUDIOPACKERROR      = 164 ;      //"1.3.6.1.4.1.8888.1.2.1.5.3.1.7.0"

const u32  MTPFMDECODERVIDEOFRAMERATE      = 166 ;      //"1.3.6.1.4.1.8888.1.2.1.5.3.2.1.0"
const u32  MTPFMDECODERVIDEOBITRATE        = 167 ;      //"1.3.6.1.4.1.8888.1.2.1.5.3.2.2.0"
const u32  MTPFMDECODERAUDIOBITRATE        = 168 ;      //"1.3.6.1.4.1.8888.1.2.1.5.3.2.3.0"
const u32  MTPFMDECODERVIDEORECVFRAME      = 169 ;      //"1.3.6.1.4.1.8888.1.2.1.5.3.2.4.0"
const u32  MTPFMDECODERAUDIORECVFRAME      = 170 ;      //"1.3.6.1.4.1.8888.1.2.1.5.3.2.5.0"
const u32  MTPFMDECODERVIDEOLOSEFRAME      = 171 ;      //"1.3.6.1.4.1.8888.1.2.1.5.3.2.6.0"
const u32  MTPFMDECODERAUDIOLOSEFRAME      = 172 ;      //"1.3.6.1.4.1.8888.1.2.1.5.3.2.7.0"
const u32  MTPFMDECODERPACKERROR           = 173 ;      //"1.3.6.1.4.1.8888.1.2.1.5.3.2.8.0"
const u32  MTPFMDECODERINDEXLOSE           = 174 ;      //"1.3.6.1.4.1.8888.1.2.1.5.3.2.9.0"
const u32  MTPFMDECODERSIZELOSE            = 175 ;      //"1.3.6.1.4.1.8888.1.2.1.5.3.2.10.0"
const u32  MTPFMDECODERFULLLOSE            = 176 ;      //"1.3.6.1.4.1.8888.1.2.1.5.3.2.11.0"



const u32  MTPFMDSP1FANSPEED               = 178 ;      //"1.3.6.1.4.1.8888.1.2.1.5.3.3.1.0"
const u32  MTPFMDSP2FANSPEED               = 179 ;      //"1.3.6.1.4.1.8888.1.2.1.5.3.3.2.0"
const u32  MTPFMDSP3FANSPEED               = 180 ;      //"1.3.6.1.4.1.8888.1.2.1.5.3.3.3.0"
const u32  MTPFMSYS1FANSPEED               = 181 ;      //"1.3.6.1.4.1.8888.1.2.1.5.3.3.4.0"
const u32  MTPFMSYS2FANSPEED               = 182 ;      //"1.3.6.1.4.1.8888.1.2.1.5.3.3.5.0"

const u32  MTPFMLEDSTATE                   = 185 ;      //"1.3.6.1.4.1.8888.1.2.1.5.4.1.0"


const u32                    = 233 ;      //"1.3.6.1.4.1.8888.1.2.3.8"

 */


