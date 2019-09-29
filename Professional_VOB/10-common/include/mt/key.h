#ifndef KEY_H_
#define KEY_H_

#include "kdvtype.h"


//KDC-8010ң����


// ���볤��
#define KEYMARKLEN		1	
// �޼���
#define NOKEY           0xFF   
//��Ч����
#define INVALID_KEY		200

// ���ڰ������
#define OSD_SCANTIMESPACE			12	// 200ms

// �����ͷŵȴ�ʱ��
#define OSD_KEYRELEASE_TPS			9 // 100-ms

//����״̬
#define EV_KEY_UP         0x0012
#define	EV_KEY_DOWN       0x0010


typedef struct tagTKey
{ 
	u8 bySrcType;  //������Դ
	u8 byKeyCode;  //����
	u16 wCount;    //��������
	u8 byReserved;

	tagTKey( ) 
	{
		byReserved = 0;
	}
	
}TKey;

  

//��������
#define KDC8010_MAXKEY	50  
//ң��������
#define MAX_REMOTE_COUNT 3



#define SBLACK_REMOTE           0x67
#define LBLACK_REMOTE           0x60
#define SILVER_REMOTE           0x5a
#define UNKNOW_REMOTE           0xff

//����
//��ɫ��ң����
#define SBLACK_REMOTE_NUM0            0x0a
#define SBLACK_REMOTE_NUM1            0x01
#define SBLACK_REMOTE_NUM2            0x02
#define SBLACK_REMOTE_NUM3            0x03
#define SBLACK_REMOTE_NUM4            0x04
#define SBLACK_REMOTE_NUM5            0x05
#define SBLACK_REMOTE_NUM6            0x06
#define SBLACK_REMOTE_NUM7            0x07
#define SBLACK_REMOTE_NUM8            0x08
#define SBLACK_REMOTE_NUM9            0x09
#define SBLACK_REMOTE_CROSS           0x2d
#define SBLACK_REMOTE_STAR            0x00
#define SBLACK_REMOTE_POWER           0x0c
#define SBLACK_REMOTE_MUTE            0x15
#define SBLACK_REMOTE_QUIET           0x14
#define SBLACK_REMOTE_SELFTEST        0x13
#define SBLACK_REMOTE_PIPENABLE       0x26
#define SBLACK_REMOTE_PIPVERSE        0x3f
#define SBLACK_REMOTE_CHAIRREQ        0x10
#define SBLACK_REMOTE_SPEAKREQ        0x11
#define SBLACK_REMOTE_QUITREQ         0x1e
#define SBLACK_REMOTE_STATE           0x29
#define SBLACK_REMOTE_SHOTSNAP        0x21
#define SBLACK_REMOTE_MENU            0x38
#define SBLACK_REMOTE_UP              0x1c
#define SBLACK_REMOTE_DOWN            0x1d
#define SBLACK_REMOTE_LEFT            0x1f
#define SBLACK_REMOTE_RIGHT           0x27
#define SBLACK_REMOTE_ENTER           0x24


// ����ɫң����
#define SILVER_REMOTE_NUM0            0x48
#define SILVER_REMOTE_NUM1            0x62
#define SILVER_REMOTE_NUM2            0x55
#define SILVER_REMOTE_NUM3            0x6A
#define SILVER_REMOTE_NUM4            0x61
#define SILVER_REMOTE_NUM5            0x51
#define SILVER_REMOTE_NUM6            0x69
#define SILVER_REMOTE_NUM7            0x60
#define SILVER_REMOTE_NUM8            0x50
#define SILVER_REMOTE_NUM9            0x58
#define SILVER_REMOTE_CROSS           0x68
#define SILVER_REMOTE_STAR            0x66
#define SILVER_REMOTE_POWER           0x6D
#define SILVER_REMOTE_MUTE            0x6B
#define SILVER_REMOTE_QUIET           0x6C
#define SILVER_REMOTE_SELFTEST        0x42
#define SILVER_REMOTE_PIPENABLE       0x72
#define SILVER_REMOTE_PIPVERSE        0x52
#define SILVER_REMOTE_SHOTSNAP        0x6F
#define SILVER_REMOTE_MENU            0x70
#define SILVER_REMOTE_UP              0x4F
#define SILVER_REMOTE_DOWN            0x4E
#define SILVER_REMOTE_LEFT            0x77
#define SILVER_REMOTE_RIGHT           0x47
#define SILVER_REMOTE_ENTER           0x40
#define SILVER_REMOTE_VOLINC          0x46
#define SILVER_REMOTE_VOLDEC          0x45
#define SILVER_REMOTE_CONNECT         0x76
#define SILVER_REMOTE_DISCONNECT      0x75
#define SILVER_REMOTE_ADDRBOOK        0x4D
#define SILVER_REMOTE_DEL             0x74 
#define SILVER_REMOTE_MAINVSRC        0x63
#define SILVER_REMOTE_AV              0x56
#define SILVER_REMOTE_FARCTRL         0x6E
#define SILVER_REMOTE_VGA             0x64
#define SILVER_REMOTE_S               0x57
#define SILVER_REMOTE_FUNC            0x65
#define SILVER_REMOTE_AUTOFOCUS       0x44
#define SILVER_REMOTE_BRIGHTINC       0x43
#define SILVER_REMOTE_BRIGHTDEC       0x4B
#define SILVER_REMOTE_NEARZOOM        0x73
#define SILVER_REMOTE_FARZOOM         0x53
#define SILVER_REMOTE_PRESAVE         0x4C
#define SILVER_REMOTE_PREMOVE         0x54
#define SILVER_REMOTE_DUAL            0x4A
#define SILVER_REMOTE_HOTKEY1         0x71
#define SILVER_REMOTE_HOTKEY2         0x49
#define SILVER_REMOTE_HOTKEY3         0x41
#define SILVER_REMOTE_HELP            0x59


// ��ɫ��ң����
#define LBLACK_REMOTE_NUM0            0x48
#define LBLACK_REMOTE_NUM1            0x62
#define LBLACK_REMOTE_NUM2            0x55
#define LBLACK_REMOTE_NUM3            0x6A
#define LBLACK_REMOTE_NUM4            0x61
#define LBLACK_REMOTE_NUM5            0x51
#define LBLACK_REMOTE_NUM6            0x69
#define LBLACK_REMOTE_NUM7            0x60
#define LBLACK_REMOTE_NUM8            0x50
#define LBLACK_REMOTE_NUM9            0x58
#define LBLACK_REMOTE_CROSS           0x68
#define LBLACK_REMOTE_STAR            0x66
#define LBLACK_REMOTE_POWER           0x6D
#define LBLACK_REMOTE_MUTE            0x6B
#define LBLACK_REMOTE_QUIET           0x6C
#define LBLACK_REMOTE_PIPENABLE       0x72
#define LBLACK_REMOTE_PIPVERSE        0x52
#define LBLACK_REMOTE_SHOTSNAP        0x6F
#define LBLACK_REMOTE_MENU            0x70
#define LBLACK_REMOTE_UP              0x4F
#define LBLACK_REMOTE_DOWN            0x4E
#define LBLACK_REMOTE_LEFT            0x77
#define LBLACK_REMOTE_RIGHT           0x47
#define LBLACK_REMOTE_ENTER           0x40
#define LBLACK_REMOTE_VOLINC          0x46
#define LBLACK_REMOTE_VOLDEC          0x45
#define LBLACK_REMOTE_CONNECT         0x76
#define LBLACK_REMOTE_DISCONNECT      0x75
#define LBLACK_REMOTE_ADDRBOOK        0x4D
#define LBLACK_REMOTE_DEL             0x74 
#define LBLACK_REMOTE_MAINVSRC        0x63
#define LBLACK_REMOTE_AV              0x56
#define LBLACK_REMOTE_FARCTRL         0x6E
#define LBLACK_REMOTE_VGA             0x64
#define LBLACK_REMOTE_S               0x57
#define LBLACK_REMOTE_RETURN          0x65
#define LBLACK_REMOTE_AUTOFOCUS       0x44
#define LBLACK_REMOTE_BRIGHTINC       0x43
#define LBLACK_REMOTE_BRIGHTDEC       0x4B
#define LBLACK_REMOTE_NEARZOOM        0x73
#define LBLACK_REMOTE_FARZOOM         0x53
#define LBLACK_REMOTE_PRESAVE         0x4C
#define LBLACK_REMOTE_PREMOVE         0x54
#define LBLACK_REMOTE_HOTKEY1         0x71
#define LBLACK_REMOTE_HOTKEY2         0x49
#define LBLACK_REMOTE_HOTKEY3         0x41
#define LBLACK_REMOTE_HELP            0x59





const u8 g_abyKeyMark[MAX_REMOTE_COUNT][KDC8010_MAXKEY] = 
{
	{ 
	    SBLACK_REMOTE_NUM0,	//0
	    SBLACK_REMOTE_NUM1,	//1
	    SBLACK_REMOTE_NUM2,	//2
	    SBLACK_REMOTE_NUM3,	//3
    	SBLACK_REMOTE_NUM4,	//4
	    SBLACK_REMOTE_NUM5,	//5
	    SBLACK_REMOTE_NUM6,	//6
	    SBLACK_REMOTE_NUM7,	//7
	    SBLACK_REMOTE_NUM8,	//8
	    SBLACK_REMOTE_NUM9,	//9
	    SBLACK_REMOTE_POWER,	//��Դ
	    SBLACK_REMOTE_STAR,	//*
	    SBLACK_REMOTE_CROSS,	//#
	    SBLACK_REMOTE_MUTE,	//���ؾ���
	    SBLACK_REMOTE_QUIET,	//Զ�˾���
	    SBLACK_REMOTE_SELFTEST,	//�Լ�
	    SBLACK_REMOTE_PIPENABLE,	//���л�����
	    SBLACK_REMOTE_PIPVERSE,		//���л�����
	    SBLACK_REMOTE_CHAIRREQ,	//������ϯ
	    SBLACK_REMOTE_SPEAKREQ,	//���뷢��
	    SBLACK_REMOTE_QUITREQ,	//�����˻�
	    SBLACK_REMOTE_STATE,	//״̬
	    SBLACK_REMOTE_SHOTSNAP,	//����
	    SBLACK_REMOTE_MENU,	//�˵�
	    SBLACK_REMOTE_UP,	//��
	    SBLACK_REMOTE_DOWN,	//��
	    SBLACK_REMOTE_LEFT,		//��
	    SBLACK_REMOTE_RIGHT,	//��
	    SBLACK_REMOTE_ENTER		//ȷ��
	},
	{
        SILVER_REMOTE_FUNC,	//����
		SILVER_REMOTE_POWER,	//��Դ
		SILVER_REMOTE_MAINVSRC,	//����Ƶ
		SILVER_REMOTE_AV,	// AV
		SILVER_REMOTE_FARCTRL,	//Զң
		SILVER_REMOTE_QUIET,	//����
		SILVER_REMOTE_VGA,	// VGA
		SILVER_REMOTE_S,	//S
		SILVER_REMOTE_SHOTSNAP,	//����
		SILVER_REMOTE_MUTE,	//����
		SILVER_REMOTE_NUM1,	//1
		SILVER_REMOTE_NUM2,	//2
		SILVER_REMOTE_NUM3,	//3
		SILVER_REMOTE_NUM4,	//4
		SILVER_REMOTE_NUM5,	//5
		SILVER_REMOTE_NUM6,	//6
		SILVER_REMOTE_NUM7,	//7
		SILVER_REMOTE_NUM8,	//8
		SILVER_REMOTE_NUM9,	//9
		SILVER_REMOTE_STAR,	//*
		SILVER_REMOTE_NUM0,	//0
		SILVER_REMOTE_CROSS,	//#
		SILVER_REMOTE_MENU,	//�˵�
		SILVER_REMOTE_ENTER,	//ȷ��
		SILVER_REMOTE_UP,	//��
		SILVER_REMOTE_DOWN,	//��
		SILVER_REMOTE_LEFT,	//��
		SILVER_REMOTE_RIGHT,	//��
		SILVER_REMOTE_CONNECT,	//����
		SILVER_REMOTE_DISCONNECT,	//�Ҷ�
		SILVER_REMOTE_ADDRBOOK,	//��ַ��
		SILVER_REMOTE_VOLINC,	//+
		SILVER_REMOTE_VOLDEC,	//��
		SILVER_REMOTE_DEL,	//ɾ��
		SILVER_REMOTE_PREMOVE,	//Ԥ��
		SILVER_REMOTE_PRESAVE,	//����
		SILVER_REMOTE_AUTOFOCUS,	//�Զ�����
		SILVER_REMOTE_NEARZOOM,	//����
		SILVER_REMOTE_FARZOOM,	//Զ��
		SILVER_REMOTE_BRIGHTDEC,	//����
		SILVER_REMOTE_BRIGHTINC,	//����
		SILVER_REMOTE_PIPENABLE,	//���л�����
		SILVER_REMOTE_PIPVERSE,	//���л�λ���л�
		SILVER_REMOTE_DUAL,	//˫��
		SILVER_REMOTE_SELFTEST,	//�Ի�
		SILVER_REMOTE_HOTKEY1,	//��ݼ���
		SILVER_REMOTE_HOTKEY2,	//��ݼ���
		SILVER_REMOTE_HOTKEY3,	//��ݼ���
		SILVER_REMOTE_HELP,	//����
	
	},
	{
        LBLACK_REMOTE_RETURN,	//����
		LBLACK_REMOTE_POWER,	//��Դ
		LBLACK_REMOTE_MAINVSRC,	//����Ƶ
		LBLACK_REMOTE_AV,	// AV
		LBLACK_REMOTE_FARCTRL,	//Զң
		LBLACK_REMOTE_QUIET,	//����
		LBLACK_REMOTE_VGA,	// VGA
		LBLACK_REMOTE_S,	//S
		LBLACK_REMOTE_SHOTSNAP,	//����
		LBLACK_REMOTE_MUTE,	//����
		LBLACK_REMOTE_NUM1,	//1
		LBLACK_REMOTE_NUM2,	//2
		LBLACK_REMOTE_NUM3,	//3
		LBLACK_REMOTE_NUM4,	//4
		LBLACK_REMOTE_NUM5,	//5
		LBLACK_REMOTE_NUM6,	//6
		LBLACK_REMOTE_NUM7,	//7
		LBLACK_REMOTE_NUM8,	//8
		LBLACK_REMOTE_NUM9,	//9
		LBLACK_REMOTE_STAR,	//*
		LBLACK_REMOTE_NUM0,	//0
		LBLACK_REMOTE_CROSS,	//#
		LBLACK_REMOTE_MENU,	//�˵�
		LBLACK_REMOTE_ENTER,	//ȷ��
		LBLACK_REMOTE_UP,	//��
		LBLACK_REMOTE_DOWN,	//��
		LBLACK_REMOTE_LEFT,	//��
		LBLACK_REMOTE_RIGHT,	//��
		LBLACK_REMOTE_CONNECT,	//����
		LBLACK_REMOTE_DISCONNECT,	//�Ҷ�
		LBLACK_REMOTE_ADDRBOOK,	//��ַ��
		LBLACK_REMOTE_VOLINC,	//+
		LBLACK_REMOTE_VOLDEC,	//��
		LBLACK_REMOTE_DEL,	//ɾ��
		LBLACK_REMOTE_PREMOVE,	//Ԥ��
		LBLACK_REMOTE_PRESAVE,	//����
		LBLACK_REMOTE_AUTOFOCUS,	//�Զ�����
		LBLACK_REMOTE_NEARZOOM,	//����
		LBLACK_REMOTE_FARZOOM,	//Զ��
		LBLACK_REMOTE_BRIGHTDEC,	//����
		LBLACK_REMOTE_BRIGHTINC,	//����
		LBLACK_REMOTE_PIPENABLE,	//���л�����
		LBLACK_REMOTE_PIPVERSE,	//���л�λ���л�
		LBLACK_REMOTE_HOTKEY1,	//��ݼ���
		LBLACK_REMOTE_HOTKEY2,	//��ݼ���
		LBLACK_REMOTE_HOTKEY3,	//��ݼ���
		LBLACK_REMOTE_HELP,	//����
	
	}
};

enum EmCombinationKey
{
    emVideoVGAOutSwitch = 0,
    emCombinationEnd
};

const EmCombinationKey g_aemCombinationKeys[] = 
{
	emVideoVGAOutSwitch, emCombinationEnd 
};

#define FindCombinationKey( byIndex ) g_aemCombinationKeys[byIndex>emCombinationEnd?emCombinationEnd:byIndex]
#endif // KEY_H_

