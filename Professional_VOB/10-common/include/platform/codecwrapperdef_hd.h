/*****************************************************************************
  ģ����      : Codecwrapper_HD.a
  �ļ���      : codecwrapperdef_hd.h
  ����ļ�    : codecwrapper_hd.h
  �ļ�ʵ�ֹ���: 
  ����        : ������
  �汾        : V4.0  Copyright(C) 2007-2008 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2007/11/29  4.0         ������      ����
******************************************************************************/
#ifndef _CODECWRAPPER_DEF_HD_H_
#define _CODECWRAPPER_DEF_HD_H_

#ifdef _CODECWRAPPER_TOS_MODULE_  //2013-3-26

#include "tos/codecwrapperdef_hd.h"

#else

//CPU��ʶ
#define CWTI_CPUMASK_MAIN   0x00000001
#define CWTI_CPUMASK_SUB    0x00000002
#define CWTI_CPUMASK_ALL    0x00000003

//������
#define ERROR_CODE_BASE             30000             
#define CODEC_NO_ERROR              0//�޴�

#include "kdvtype.h"
#include "osp.h"

//��ʼ��ʱָ������������
enum enBoardType
{
	en_H600_Board = 1,
	en_H700_Board,
	en_H900_Board,
	en_HDU2_Board,
	en_MPU2_Board,
	en_T300_Board,
	en_APU2_Board,
	en_Invalid_Board,
};
enum enNetraID
{
	ID_NETRA1 = 0,          
	ID_NETRA2 ,             
	ID_NETRA3 ,             
	ID_NETRA4 ,
	ID_NETRA_INVALID
};



//MPU2ģʽ����
#define VMP_BASIC				0
#define VMP_ENHANCED			1
#define BAS_BASIC				2
#define BAS_ENHANCED			3

enum enCodecErr
{
	Codec_Success = CODEC_NO_ERROR,

	Codec_Error_Base = ERROR_CODE_BASE,
	Codec_Error_Param,
	Codec_Error_CPUID,
	Codec_Error_Codec_NO_Create,
	Codec_Error_Audio_CapInstance,
	Codec_Error_Audio_PlyInstance,
	Codec_Error_CreateThread,
	Codec_Error_FastUpdateTooFast,
	Codec_Error_WriteToDSP,
	Codec_Error_CreateHPIChannel,
	Codec_Error_GetMem
};

#define CODECMAXCHANNELNUM         4
#define MAX_VIDENC_CHANNEL         CODECMAXCHANNELNUM
#define MAX_VIDDEC_CHANNEL         CODECMAXCHANNELNUM
#define MAX_AUDENC_CHANNEL         CODECMAXCHANNELNUM
#define MAX_AUDDEC_CHANNEL         CODECMAXCHANNELNUM

#define MAX_NUMLOGO_NUM        4
#define MAX_NOMALLOGO_NUM      16
#define MAX_BMP_NUM            32
#define MIN_BMP_LOGO_ID        1

//Audio mode
enum
{
	AUDIO_MODE_MP3 = 4,
	AUDIO_MODE_PCMA = 5,
	AUDIO_MODE_PCMU,
	AUDIO_MODE_G723_6,
	AUDIO_MODE_G723_5,
	AUDIO_MODE_G728,
	AUDIO_MODE_G722,
	AUDIO_MODE_G729,
	AUDIO_MODE_G719,
	AUDIO_MODE_G7221,
	AUDIO_MODE_ADPCM,
    AUDIO_MODE_AACLC_32,     //32K ˫����
    AUDIO_MODE_AACLC_32_M,   //32K ������
    AUDIO_MODE_AACLC_48,     //48K ˫����
    AUDIO_MODE_AACLC_48_M,   //48K ������
    AUDIO_MODE_AACLD_32,
    AUDIO_MODE_AACLD_32_M,
    AUDIO_MODE_AACLD_48,
    AUDIO_MODE_AACLD_48_M
};

//��Ƶ����������
typedef enum 
{
    SAMPLE_RATE96000 = 0, //������Ϊ96kHz��������0
    SAMPLE_RATE88200,     //������Ϊ88.2kHz��������1
    SAMPLE_RATE64000,     //������Ϊ64kHz��������2
    SAMPLE_RATE48000,     //������Ϊ48kHz��������3
    SAMPLE_RATE44100,     //������Ϊ44.1kHz��������4
    SAMPLE_RATE32000,     //������Ϊ32kHz��������5
    SAMPLE_RATE24000,     //������Ϊ24kHz��������6  
    SAMPLE_RATE22050,     //������Ϊ22.05kHz��������7
    SAMPLE_RATE16000,     //������Ϊ16kHz��������8
    SAMPLE_RATE12000,     //������Ϊ12kHz��������9
    SAMPLE_RATE11025,     //������Ϊ11.025kHz��������10 
    SAMPLE_RATE8000       //������Ϊ8kHz��������11
}enSampleRate;

//��Ƶ����ģʽ,���T300
enum enAudPlayMode
{
    EN_PLAY_FULL = 0,     //3·����
    EN_PLAY_SINGLE        //��·����	
};

/* ������������*/
enum
{
	VID_DROP_PREFERRED_QUALITY   =   0, 
	VID_DROP_PREFERRED_FAST_SPEED,   
	VID_DROP_PREFERRED_MID_SPEED,
	VID_DROP_PREFERRED_SLOW_SPEED
};

/*��������������λ��*/
enum
{
    VID_CODECTYPE_FPGA = 0,
    VID_CODECTYPE_DSP,
    VID_CODECTYPE_UNKNOW
};

/* ��Ƶ��������ӿں궨��(t300��ʱ����) */ 
#define VIDIO_NOSOURCE              0x00000000
#define VIDIO_HDMI0                 0x00000001
#define VIDIO_HDMI1                 0x00000002
#define VIDIO_HDMI2                 0x00000004
#define VIDIO_HDMI3                 0x00000008
#define VIDIO_VGA0                  0x00000010
#define VIDIO_VGA1                  0x00000020
#define VIDIO_VGA2                  0x00000040
#define VIDIO_YPbPr0                0x00000100
#define VIDIO_YPbPr1                0x00000200  /* ��KDV7180�ϸýӿں�VIDIN_VGA0��ͻ��ֻ��2ѡ1 */
#define VIDIO_YPbPr2                0x00000400
#define VIDIO_SDI0                  0x00001000
#define VIDIO_SDI1                  0x00002000
#define VIDIO_C0                    0x00010000
#define VIDIO_C1                    0x00020000
#define VIDIO_S0                    0x00100000
#define VIDIO_DVI0                  0x01000000
#define VIDIO_DVI1                  0x02000000
#define VIDIO_DVI2                  0x04000000
#define VIDIO_CAMERA0               0x10000000


/*ͼ�����*/
enum
{
    VIDCAP_SCALE_BRIGHTNESS = 0, /* �������ȣ�  C | YPbPr */
    VIDCAP_SCALE_CONTRAST,       /* ���öԱȶȣ�C | YPbPr */
    VIDCAP_SCALE_HUE,            /* ����ɫ�ȣ�  C */
    VIDCAP_SCALE_SATURATION,      /* ���ñ��Ͷȣ�C | YPbPr */
	VIDCAP_SCALE_SHAPNESS,		//������ȵ�ֵ������Ϊint * �ͣ�ȡֵ��Χ2 ��= pArgs ��= 0�� 0�����ǿ��1��֮��2����
	VIDCAP_SCALE_NOISE,			//����ȥ���ֵ������Ϊ int * �ͣ�ȡֵ��Χ3 ��= pArgs ��= 0��3��ʾ�ر�ȥ�룬0ȥ����ǿ��1��֮��2����
	VIDCAP_SCALE_BACKLIGHT

};

/*SD�źŹ̶������ʽ*/
enum
{
	VID_OUTTYPE_ORIGIN = 0,	//ԭʼ��������
	VID_OUTTYPE_576I,		//�̶��� 576i25���
	VID_OUTTYPE_576P,
	VID_OUTTYPE_720P50,		//�̶��� 720p50���
	VID_OUTTYPE_720P60,		//�̶��� 720p60���
	VID_OUTTYPE_1080I50,	//�̶���1080i25���
	VID_OUTTYPE_1080I60,	//�̶���1080i30���
	VID_OUTTYPE_1080P24,	//�̶���1080p24���
	VID_OUTTYPE_1080P25,	//�̶���1080p25���
	VID_OUTTYPE_1080P30,	//�̶���1080p30���
    //��������֧��
	VID_OUTTYPE_1080P50,	//�̶���1080p50���
	VID_OUTTYPE_1080P60,	//�̶���1080p60���
	VID_OUTTYPE_1080P23,	//�̶���1080p23���
	VID_OUTTYPE_1080P29,	//�̶���1080p29���
	VID_OUTTYPE_1080P59,	//�̶���1080p59���
    //VGA��ʽ
	VID_OUTTYPE_VGA60,	   //�̶���VGA 60HZ��� 640x480
	VID_OUTTYPE_VGA75,	   //�̶���VGA 75HZ���
	VID_OUTTYPE_SVGA60,	   //�̶���SVGA 60HZ��� 800x600
	VID_OUTTYPE_SVGA75,	   //�̶���SVGA 75HZ���
	VID_OUTTYPE_XGA60,	  //�̶���XGA 60HZ��� 1024x768
	VID_OUTTYPE_XGA75,	  //�̶���XGA 75HZ���
	VID_OUTTYPE_SXGA60,	  //�̶���SXGA 60HZ���  1280x1024
	VID_OUTTYPE_SXGA75,   //�̶���SXGA 75HZ���  1280x1024
	VID_OUTTYPE_UXGA60,	  //�̶���UXGA 60HZ��� 1600x1200
	VID_OUTTYPE_WXGA1280x768_60,	  //�̶���WXGA 60HZ��� 1280x768
	VID_OUTTYPE_WXGA1280x768_75,	  //�̶���WXGA 75HZ��� 1280x768
	VID_OUTTYPE_WXGA1280x800_60,	  //�̶���WXGA 60HZ��� 1280x800
	VID_OUTTYPE_WXGA1280x800_75,	  //�̶���WXGA 75HZ��� 1280x800
	VID_OUTTYPE_WXGA1360x768_60,	  //�̶���WXGA 60HZ��� 1360x768
	VID_OUTTYPE_WXGA1360x768_75,	  //�̶���WXGA 75HZ��� 1360x768
	VID_OUTTYPE_WSXGA60,	  //�̶���WSXGA 60HZ��� 1440x900
	VID_OUTTYPE_WSXGAPLUS60	  //�̶���SXGA+ 60HZ��� 1680x1050
};
 
//PIP mode
enum  enVideoPIPMode
{
	VIDEO_PIPMODE_ONE = 0,              //������
	VIDEO_PIPMODE_TWO_LEFTRIGHT,         //������,����
	VIDEO_PIPMODE_TWO_LEFTUP,            //������,����
	VIDEO_PIPMODE_TWO_RIGHTUP,		     //������,����
	VIDEO_PIPMODE_TWO_RIGHTDOWN,   	     //������,����
	VIDEO_PIPMODE_TWO_LEFTDOWN,		     //������,����
	VIDEO_PIPMODE_THREE,                 //�����棬Ʒ����
	VIDEO_PIPMODE_THREE_ONEBIG,          //�����棬һ���С
	VIDEO_PIPMODE_THREE_T300_A,			 //�����棬һ����С��С���濿��
	VIDEO_PIPMODE_THREE_T300_B,			 //�����棬һ����С��С���濿��
	VIDEO_PIPMODE_THREE_T300_C,          //�����棬һ����С��С�������
    VIDEO_PIPMODE_INVALID
};

//���л�λ������
enum enVideoPIPIndex
{
	VIDEO_PIPINDEX_NULL = 0,              //�ջ���
	VIDEO_PIPINDEX_LOCAL,			      //����
	VIDEO_PIPINDEX_MAINVIDDEC,            //������
	VIDEO_PIPINDEX_SUBVIDDEC,             //������
	VIDEO_PIPINDEX_SUBLOCAL,              //������
	VIDEO_PIPINDEX_ADD_T300,
    VIDEO_PIPINDEX_INVALID
};

/* ����������豸ID*/
enum
{
	CODECDEV_VIDENC = 0,     //��Ƶ�����豸
	CODECDEV_VIDDEC,         //��Ƶ�����豸
	CODECDEV_AUDDEV          //��Ƶ������豸
};

/* SDI�ӿ�����*/
enum
{
	SDITYPE_NONE = 0,     //û�в�SDIģ��
	SDITYPE_ININ,         //��������ģ��
	SDITYPE_INOUT         //һ�����룬һ�����ģ��
};

/* VGA��1080I��1080P���Ƶ��ѡ��*/
#define  VIDPLYFREQ_AUTO             0     //Ĭ���Զ�����
#define  VIDPLYFREQ_24FPS            24    //����1080P
#define  VIDPLYFREQ_25FPS            25    //����1080P
#define  VIDPLYFREQ_30FPS            30    //����1080P
#define  VIDPLYFREQ_50FPS            50    //����1080I
#define  VIDPLYFREQ_60FPS            60	   //����1080I��VGA
#define  VIDPLYFREQ_75FPS            75	   //����VGA
#define  VIDPLYFREQ_1080POUT1080I    0xFF  //����1080P��1080I���

/*������GroupID*/
/*ע:A��Bģʽͨ�����ɽ��洴��*/
enum
{
	ADAPTER_MODEA_NOR = 0,     //Aģʽ����ͨ����ͨ��
	ADAPTER_MODEA_VGA,         //Aģʽ��VGA����ͨ��
	ADAPTER_MODEB_H264ToH263,		   //Bģʽ��H264ToH263ͨ��
	ADAPTER_MODEB_H263ToH264           //Bģʽ��H263ToH264ͨ��
};

//�豸��ʼ��ģʽ
enum enInitMode
{
    INITMODE_All_VMP = 0,           //���嵥VMPģʽ���൱�ڵ��� HardMPUInitDev(1,2,4)
    INITMODE_HALF_VMP,              //����˫VMPģʽ���൱�ڵ��� HardMPUInitDev(2,2,4)
    INITMODE_EVMP,                  //���嵥VMPģʽ���൱�ڵ��� HardMPUInitDev(1,2,4)
    INITMODE_HDBAS,                 //��������ģʽ���൱�ڵ���  HardMPUInitDev(2,2,4)
    INITMODE_EBAS,                  //��������ģʽ���൱�ڵ���  HardMPUInitDev(2,0,4)
    INITMODE_HDU,                   //�������ǽģʽ���൱�ڵ���  HardMPUInitDev(0,1,1)
    INITMODE_NUM
};

/* ��Ƶ��������ӿں궨�� */
#define AUDIO_C0		  0x00000003//RCA0
#define AUDIO_C0_LEFT     0x00000001//RCA0��������
#define AUDIO_C0_RIGHT	  0x00000002//RCA0��������
#define AUDIO_C1          0x00000004//RCA1
#define AUDIO_C2          0x00000008//RCA2
#define AUDIO_C3          0x00000010//RCA3
#define AUDIO_C4          0x00000020//RCA4
#define AUDIO_C5          0x00000040//RCA5
#define AUDIO_MIC0        0x00000080//��ũ0
#define AUDIO_MIC1        0x00000100//��ũ1
#define AUDIO_MIC2        0x00000200//��ũ2
#define AUDIO_MIC3        0x00000400//��ũ3
#define AUDIO_MIC4        0x00000800//��ũ4
#define AUDIO_MIC5        0x00001000//��ũ5
#define AUDIO_MIC6        0x00002000//��ũ6
#define AUDIO_MIC7        0x00004000//��ũ7
#define AUDIO_MIC8        0x00008000//��ũ8
#define AUDIO_MIC9        0x00010000//��ũ9
#define AUDIO_DIGIT0      0x00020000//�������0
#define AUDIO_DIGIT1      0x00040000//�������1
#define AUDIO_DIGIT2      0x00080000//�������2
#define AUDIO_35mm0		  0x00100000//3.5mm0
#define AUDIO_35mm1		  0x00200000//3.5mm1
#define AUDIO_35mm2		  0x00400000//3.5mm2
#define AUDIO_35mm3		  0x00800000//3.5mm3
#define AUDIO_HDMI0		  0x01000000//DVI-HDMI0
#define AUDIO_HDMI1       0x02000000//DVI-HDMI1 ��Ӧ�忨�ϵ�AUX1
#define AUDIO_HDMI2       0x04000000//DVI-HDMI2 ��Ӧ�忨�ϵ�AUX2
#define AUDIO_HDMI3       0x08000000//DVI-HDMI3 ��Ӧ�忨�ϵ�AUX3
#define AUDIO_HDMI4       0x10000000//DVI-HDMI4 ��Ӧ�忨�ϵ�AUX4
#define AUDIO_HDMI5       0x20000000//DVI-HDMI5 ��Ӧ�忨�ϵ�AUX5
#define AUDIO_HDMI6       0x40000000//DVI-HDMI6 ��Ӧ�忨�ϵ�AUX6
#define AUDIO_SPEAKER     0x80000000//������

/* ����Ϣ�����������ʽ�궨�� */
//������ʽ
#define RUNMODE_STATIC     0    //����Ϣ��֧��
#define RUNMODE_LEFTRIGHT  1    
#define RUNMODE_UPDWON     2    
#define RUNMODE_UPDWONPAGE 3    //�����ҳ����
//�����ٶ�
#define RUNSPEED_FAST      4
#define RUNSPEED_HIGH      3
#define RUNSPEED_NORM      2
#define SPEED_LOW          1

//����Ƶ���ʱ���Ų���
enum enplayMode
{
    EN_PLAY_LAST = 0,
    EN_PLAY_BLUE,
	EN_PLAY_BMP,
	EN_PLAY_ERROR
};
enum enZoomMode
{
    EN_ZOOM_FILLBLACK = 0,//�Ӻڱ�
    EN_ZOOM_CUT,//�ñ�
    EN_ZOOM_SCALE//���ȱ�����
};
/*�����������Ƶ���VP*/
#define MAKEVPID(nMain,nSub)          (u32)( ((u32)nMain&0x000000FF) | (((u32)(nSub+1)&0x000000FF)<<8) )

//��������������
#define VIDENC_MBSIZE_ALL         (u32)0xFF0FFFFF
#define VIDENC_MBSIZE_P8x8UP      (u32)0xFF0FE0FF
#define VIDENC_MBSIZE_DEFAULT     0  //ĿǰΪ0xFF0FFFFF

#define VIDENC_MBSIZE_ENABLE      VIDENC_MBSIZE_ALL
#define VIDENC_MBSIZE_DISABLE     VIDENC_MBSIZE_P8x8UP
//////////////////////////////////////////////////////////////////////////

#define NF_MODE_DISABLE               0
#define NF_MODE_LOW                   1
#define NF_MODE_MED					  2
#define NF_MODE_HIGH                  3

//�ӿڽṹ
typedef struct tagDSPInit
{
	u32     m_dwDspID;          //��ʼ����DSP���
	u32     m_dwLogoNum;        //��(1)��(0)��Ҫ��DSP�ϼ�logo��banner��OSD��
	u32     m_dwNumLogoNum;     //�ݲ�ʹ��
	u32     m_dwAudEncNum;      //��Ƶ����·��
	u32     m_dwAudDecNum;      //��Ƶ����·��
	BOOL32  m_bInitAec;         //�Ƿ�ʹ��AEC
    BOOL32  m_bOutD1;           //�Ƿ�̶����D1
    u32     m_bDspDDRFreq;      //Dsp DDRƵ��(135��162)
}TDSPInit;

typedef struct tagCodecInit
{
	u32     dwDspID;   //Dspid kdv7810(0:videnc, 1:viddec, 2:audio)
	u32     dwChnID;   // 0,1....
	u32     dwVPID;    // 0:��ͨ��DSPֱ�Ӳɼ��� 1:ͨ��DSP���غ�ɼ�
                       /* ��������VP����� ռ�õ�VP�ڣ�һ��chnl���ͬʱ��4��VP�������
                       32λ���Ϊ4��Byte,ÿ��byte��Ӧһ����Ƶ�����:
                       Bit[ 7: 0]Ϊ����Ƶ���: ��Χ0~FPGA_DEC_VP_MAX_NUM-1,�ֱ��ӦVP0/1/2/3��
                       Bit[15: 8]Ϊ����Ƶ���1��
                       Bit[23:16]Ϊ����Ƶ���2��
                       Bit[31:24]Ϊ����Ƶ���3��
                       3������Ƶ����β���[VP��+1]��ָʾ��Ӧ��VP�ţ�
                       0 ��ʾ��Ӧ����Ƶ����رա�
                       ��ʹ��MAKEVPID(nMain,nSub),�����ɣ�nMainΪ��VPID�� nSubΪ��VPID*/

	u32     dwCapPort; //�ɼ��˿�
}
TEncoder, TDecoder;

typedef struct tagVidEncInit 
{
    u32 dwChnID;
    u32 dwCapPort;
    u32 dwEncTaosID;
    u32 dwTaosVPID;
    u32 dwBeforeDSP;
    u32 dwDspLinkToTaosVP;
    u32 dwEncDspID;
    u32 dwDspInVPID;
    u32 dwPlyLocalDspID;
    u32 dwPlyLocalVP;
	BOOL32 bFpsInStream;
}
TVidEncInit;

typedef struct tagVidDecInit 
{
    u32 dwChnID;
    u32 dwPlyPort;
    u32 dwDecTaosID;
    u32 dwTaosVPID;
    u32 dwAfterDSP;
    u32 dwDspLinkToTaosVP;
    u32 dwDecDspID;
    u32 dwDspOutVPID;
    u32 dwSubOutDsp;
    u32 dwSubOutVP;
    u32 dwPlyStd;   //Ĭ�� VID_OUTTYPE_1080P50
}
TVidDecInit;
//HD3 �ṹ��
typedef struct tagVidEncIntit3RD
{
    u32 dwChnID;
    u32 dwCapPort;
    u32 dwPlyStd;   //Ĭ�� VID_OUTTYPE_1080P50
	u32 dwReserved;
}TVidEncHD3RD;
typedef struct tagVidDecBufInfo
{
	u32 dwPlayBufferCnt; //�ϲ�����趨�����û�������(1~5) Ĭ��Ϊ0 ���ײ㰴��������
	u32 dwDecBufferCnt; //�ϲ����Ľ������buffer����(1~5)��Ĭ��Ϊ0���ײ㰴��������
}TVidDecBufInfo;

typedef struct tagVidDecIntit3RD
{
    u32 dwChnID;
    u32 dwPlyPort;
    u32 dwPlyStd;   //Ĭ�� VID_OUTTYPE_1080P50
	BOOL32 bCPortOutputEnable;// c����������� Ĭ�Ϲر�
	//���²������û�����Ҳ��ʹ��Ĭ�ϣ�buffer����������ʱ�����ٻ����𶶶�
	TVidDecBufInfo* pExtraBufInfo;//if NULL - use defult num
	u32 dwReserved;
}TVidDecHD3RD;

typedef struct tagVidSrcInfo
{
    u16	    m_wWidth;                     /* ��Ƶ��������Ϊ��λ,Ϊ0��ʾ���ź� */
    u16	    m_wHeight;                    /* ��Ƶ�ߣ���Ϊ��λ,Ϊ0��ʾ���ź� */
    BOOL32  m_bProgressive;               /* ���л���У�TRUE=���У�FALSE=���� */
    u32     m_dwFrameRate;                /* ֡�ʣ�����ʱ=��Ƶ������ʱ=��Ƶ/2����60i=30P,Ϊ0��ʾ���ź� */
}
TVidSrcInfo;

typedef struct tagVidPortInfo
{
    TVidSrcInfo m_tVidSrcInfo;	//��Ƶ��ʽ
	u32			m_dwVidPort;	//��Ƶ�˿�			
}
TVidPortInfo;

typedef struct tagVidFrameInfo
{
	BOOL32    m_bKeyFrame;    //Ƶ֡���ͣ�I or P��
	u16       m_wVideoWidth;  //��Ƶ֡��
	u16       m_wVideoHeight; //��Ƶ֡��
}
TVidFrameInfo;

typedef struct tagFrameHeader
{
	u32     m_dwMediaType;    //��������
	u32     m_dwFrameID;      //֡��ʶ�����ڽ��ն�
	u32     m_dwSSRC;         //ͬ��Դ��Ϣ�����ڽ��ն�
	u8*     m_pData;          //����Ƶ����
	u32     m_dwDataSize;     //���ݳ���
	u32		m_dwFPS;		  //֡��
    union
    {
		TVidFrameInfo m_tVideoParam;
        u32           m_dwAudioMode;//��Ƶģʽ
    };
}
TFrameHeader, *PTFrameHeader;

//��Ƶ�������,ֻ��AAC_LC��Ч
typedef struct 
{
    u32 m_dwMediaType;            //��Ƶý������ MEDIA_TYPE_AACLC
    u32 m_dwSamRate;              //��Ƶ������, SAMPLE_RATE32000��
    u32 m_dwChannelNum;           //��Ƶ������, 1��2
}
TAudioDecParam;

typedef struct
{
	u32 dwFrmType;				    //0:���̶�����, 1: half cif, 2: 1 cif, 3: 2 cif,  4: 4 cif,  5: ����ͼ��ϳɱ���
	u32 dwFrameRate;				//֡��
	u32 dwIFrmInterval;				//I֡���
	u32 dwBitRate;					//����
	BOOL32 bFrmRateLittleThanOne;	//����֡��С��1 ?
	BOOL32 bFramRateCanSet;			//����֡���Ƿ����ⲿ�趨? 1:�ǣ�0����
	BOOL32 bAutoDelFrame;			//�������Ƿ��Զ���֡1���ǣ�0����				
}TMpv4FrmParam;


typedef struct 
{
	u32 m_dwReserve;
}
TVideoDecParam;

/*��Ƶ�������*/
typedef struct tagVideoEncParam
{
	u16 m_wVideoWidth;				/*ͼ�����(default:1280)*/
	u16	m_wVideoHeight;				/*ͼ��߶�(default:720)*/
	u8  m_byEncType;				/*ͼ���������*/
 	u8  m_byImageQulity;			/*ͼ��ѹ������,0:�ٶ�����;1:��������, ��Ч*/
	u16 m_wBitRate;					/*���������(Kbps)*/
	
	u8  m_byFrameFmt;				/*�ֱ���*/ 
    u8  m_byRcMode;					/*ͼ��ѹ�����ʿ��Ʋ���*/    
	u8  m_byMaxQuant;				/*�����������(1-51)*/
    u8  m_byMinQuant;				/*��С��������(1-51)*/
	u32 m_dwAvgQpI;					/* ƽ��qp Ĭ��0- 28*/
	u32 m_dwAvgQpP;
	u8	m_byFrameRate;				/*֡��(default:60)*/	 
	u8	m_byFrmRateCanSet;			/*֡���Ƿ�������趨 ?, ��Ч*/
	u8  m_byFrmRateLittleThanOne;	/* ֡���Ƿ�С��1 ?, ��Ч*/
	u8  m_byLoopFilterMask;		    /*������·�˲� Ĭ��Ϊ0 ������*/
    u32	m_dwMaxKeyFrameInterval;	/*I֡�����P֡��Ŀ*/
	
	
	u32  m_dwProfile;				// 0 BaseLine | 1 HighProfile
	u32  m_dwReserved;				/*����*/
	//׷�ӱ���������
	u32  m_dwCabacDisable;			/*�Ƿ���CABAC*/
	u32  m_dwSilceMbCont;           /*slice�ĺ��������������Ϊ��slice*/
	u32  m_dwRateControlAlg;        /*���ʿ����㷨������m_byRcMode == 1 ʱ��Ч*/
	
}TVideoEncParam;

//�����T300 abc���ַ��
typedef struct
{
	BOOL32 bUsrCfg;		//�Ƿ�ʹ���û����岼��
	u32 dwMergeStyle;	//��Ӧ�Ļ����� T300����A,B,C
	u32 dwPosIndex;		//��ͼ��λ��
	u32 dwScaleX;		//X������ռ���� �ٷֱ�
	u32 dwScaleY;		//Y������ռ����
	u32 dwScaleW;		//������ռ����
	u32 dwScaleH;		//�߶���ռ����
}TSmallPicRectInfo;

/*������״̬*/
typedef struct tagKdvEncStatus
{
	BOOL32 			m_bVideoSignal;			/*�Ƿ�����Ƶ�ź�*/
	BOOL32			m_bAudioCapStart;       /*�Ƿ�ʼ��Ƶ����*/
	BOOL32			m_bEncStart;            /*�Ƿ�ʼ����*/	
}TKdvEncStatus;

/*������ͳ����Ϣ*/
typedef struct tagKdvEncStatis
{
    u32  m_dwFrameRate;  /*֡��*/
    u32  m_dwBitRate;    /*�����ٶ�*/
    u32  m_dwPackLose;   /*��֡��*/
    u32  m_dwPackError;  /*��֡��*/
	u32  m_wAvrBitRate;  /*1��������Ƶ����ƽ������*/
}TKdvEncStatis;



/*������״̬*/
typedef struct tagKdvDecStatus
{
	BOOL32	m_bDecStart;         /*�Ƿ�ʼ����*/	
	u32     m_dwAudioDecType;    /*��������*/
    u32     m_dwHeart;           /*�����߳�����*/
	u32     m_dwPos;             /*�����߳�λ��*/
    u32     m_dwDecType;
}TKdvDecStatus;

/*������ͳ����Ϣ*/
typedef struct tagKdvDecStatis
{
	u16	   m_wFrameRate;           /*����֡��*/
    u16    m_wLoseRatio;           /*��ʧ��,��λ��%*/ 
	u32    m_dwRecvFrame;          /*�յ���֡��*/
	u32    m_dwLoseFrame;          /*��ʧ��֡��*/		
	u32    m_dwPackError;          /*��֡��*/ 
	u32    m_dwIndexLose;          /*��Ŷ�֡*/
	u32    m_dwSizeLose;           /*��С��֡*/
	u32    m_dwFullLose;           /*����֡*/	
	u16	   m_wBitRate;             /*��Ƶ��������*/
	u16    m_wAvrVideoBitRate;     /*1�����ڽ���ƽ������*/
	BOOL32 m_bVidCompellingIFrm;   /*��Ƶǿ������I֡*/								  
	u32    m_dwDecdWidth;	       /*�����Ŀ�*/
	u32    m_dwDecdHeight;         /*�����ĸ�*/
}TKdvDecStatis;

typedef struct tagTranspDColor
{
	u8 RColor;          //R����
	u8 GColor;          //G����
	u8 BColor;          //B����	
	u8 u8Transparency;  //͸����(0��ʾȫ͸����255��ʾ��͸����1~254��ʾ����͸��)
}TTranspColor;

typedef struct BackBGDColor
{
    u8 RColor;    //R����
    u8 GColor;    //G����
    u8 BColor;    //B����	
}TBackBGDColor;       //��Ϊ�ն˼���ʹ��

/* ����������� */
typedef struct
{
	u32 dwXPos;
    u32 dwYPos;//��ʾ�����Y����
    u32 dwWidth;//��ʾ����Ŀ�
    u32 dwHeight;//��ʾ����ĸ�
    u32 dwBMPWight;//BMPͼ���
    u32 dwBMPHeight;//BMPͼ���
    u32 dwBannerCharHeight;//����߶ȣ�����Ҫ�������¹���ʱ��ȷ��ͣ�ٵ�λ��
    TTranspColor tBackBGDColor;//����ɫ 
    u32 dwPicClarity;          //����ͼƬ͸����
    u32 dwRunMode;//����ģʽ������or����or��ֹ���궨�����ϣ�
    u32 dwRunSpeed;//�����ٶ� �ĸ��ȼ����궨�����ϣ�
    u32 dwRunTimes;//�������� 0Ϊ�����ƹ���
 	u32 dwHaltTime;//ͣ��ʱ��(��)�����¹���ʱ��ÿ����һ���ֵ�ͣ�ټ����0ʼ��ͣ�����뾲ֹ��ͬ�� 
}TAddBannerParam;

typedef struct
{
    u32 dwWidth;    //ͼƬ����Ӧ����ƵԴ��ʽ����
    u32 dwHeight;  //ͼƬ����Ӧ����ƵԴ��ʽ�߶�
    u8 *pBMP;
    u32 dwBmpLen;
}TBmpInfo;
typedef struct
{
    TBmpInfo tBmpInfo[3];
    TAddBannerParam tBannerParam[3];
    u32 Reserver;
}TFullBannerParam;

typedef struct {
    u32 dwXPos;
    u32 dwYPos;
    u32 dwLogoWidth;//logo��
    u32 dwLogoHeight;//logo��
    TTranspColor tBackBGDColor;    
}TAddLogoParam;

typedef struct
{
    TBmpInfo tBmpInfo[3];
    TAddLogoParam tLogoParam[3];
}TFullLogoParam;
////////////////////////////////////////////////////////////////////////////
//

//////////////////////////////////////////////////////////////////////////
//adapter structs

/* ��Ƶ������� */
typedef struct
{
    u8  byAudioEncMode; /*��������ģʽ*/
    u8  byAudioDuration;/*ʱ��*/
}TAdapterAudioEncParam;

/* ������������� */
typedef union
{
    TVideoEncParam          tVideoEncParam[6];
    TAdapterAudioEncParam   tAudioEncParam;
}TAdapterEncParam;

//����ͨ��
typedef struct
{
    u8 byChnNo;//ͨ����
    u8 byMediaType;//Ŀ����������(����ָ��)
    TAdapterEncParam  tAdapterEncParam; // �������
}TAdapterChannel;

//������״̬
typedef struct
{
    BOOL32     bAdapterStart;      //�����Ƿ�ʼ
    u8     byCurChnNum;  //Ŀǰ���������ͨ����Ŀ
    TAdapterChannel atChannel[6];  //���е�ͨ��
}TAdapterGroupStatus;

//ͨ��ͳ����Ϣ
typedef struct	
{
    u32  dwRecvBitRate;        //��������
    u32  dwRecvPackNum;        //�յ��İ���
    u32  dwRecvLosePackNum;    //������ն�����
    u32  dwSendBitRate;        //��������
    u32  dwSendPackNum;        //���͵İ���
    u32  dwSendLosePackNum;    //���Ͷ�����
    BOOL32 m_bVidCompellingIFrm;	//�Ƿ�Ҫǿ�ƹؼ�֡
#ifdef MAU_VMP
    u32  dwDecChnl;                 //*****��
#endif
}TAdapterChannelStatis;

typedef struct
{
    u32 dwChannelNum;
}TAdapterInit;


typedef void ( *FRAMECALLBACK)(PTFrameHeader pFrameInfo, void* pContext);
typedef void ( *TDecodeVideoScaleInfo)(u16 wVideoWidth, u16 wVideoHeight);
typedef void ( *TDebugCallBack )(char *pbyBuf, int dwBufLen);
typedef void ( *CHANGECALLBACK)(void* pContext);
typedef void ( *CpuResetNotify)(s32 nCpuType);  //nCpuType��DSP ID��0��1��2 ��
typedef void ( *VIDENCCALLBACK)(TVideoEncParam* pFrameInfo, void* pContext);	//�����������
typedef void ( *VIDOUTTYPECALLBACK)(TVidSrcInfo* pSetVidOutInfo, TVidSrcInfo* pUseVidOutInfo);	//������ʽ����
typedef void ( *VIDDECPLAYTYPECALLBACK)(BOOL32 bVGAStream, BOOL32 bVGAPlayPort);	//˫��������ʽ�Ͳ��Žӿڲ�ƥ��ʱ
typedef void ( *KdvLogOutput)(const s8* pschInfo);
#endif

#endif  //2013-3-21