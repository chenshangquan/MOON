#ifndef MPUHARDWARE_AUTO_TEST_H
#define MPUHARDWARE_AUTO_TEST_H

#include "eventid.h"
#include "kdvtype.h"
#include "osp.h"
#include "mcuconst.h"


#define MPU_SERVER_APPID            101             // ���Է�����APPID��

//���в��Ե�ģʽ
#define		TYPE_MPUSVMP				11	 //MPU-VMP
#define		TYPE_MPUBAS					13	 //MPU-BAS

//MPU����������ʼ�˿� 
#define MPUTEST_RECVBASEPORT	    VMP_EQP_STARTPORT		//(VMP)
#define MPUTEST_BAS_RECVBASEPORT	BAS_EQP_STARTPORT		//(BAS)

//MPU���͵����Է������õĶ˿� 
#define MPUTEST_SENDSVRPORT			VMP_MCU_STARTPORT + PORTSPAN	//(vmp)��·��Ӧ720p			
#define MPUTEST_BAS_SENDSVRPORT		BAS_MCU_STARTPORT				//(BAS)


/*MPU�Զ������Ϣ*/ 
//��Ϣ�壺	  u8 ���Ե�ģʽ��VMP/BAS��+ u8 *31  ��	+ �û���Ϣ + �豸��Ϣ
#define C_S_MPUTest_REQ                     EV_MPUAUTOTEST_BGN       // ע������
#define S_C_MPUTest_ACK                     EV_MPUAUTOTEST_BGN + 1       // ACK
#define S_C_MPUTest_NACK                    EV_MPUAUTOTEST_BGN + 2      // NACK

#define  C_S_MPUREADY_NOTIF                 EV_MPUAUTOTEST_BGN + 3      //(��VMP��)֪ͨ���������Կ�ʼ������

#define  S_C_MPURESTORE_CMD                 EV_MPUAUTOTEST_BGN + 5      //�ָ�Ĭ��ֵ��Ϣ
#define  C_S_MPURESTORE_NOTIF               EV_MPUAUTOTEST_BGN + 6      //�ָ��ɹ���Ϣ

//��Ϣͷ��channelIdx 
//(��VMP���ԣ�ֻ����1; ��BAS���ԣ����ݲ�����ֱ���0��1��2��3)
#define  S_C_FASTUPDATEPIC_CMD				EV_MPUAUTOTEST_BGN + 7		  //��������MPU����ؼ�֡

//----------MPU-BAS ����-----------
//ĳBAS ͨ��׼������
//��Ϣͷ�� channelIdx ( 0~3, �յ�3�������ͨ��׼������ ) 
#define  C_S_BASCHNL_NOTIF					EV_MPUAUTOTEST_BGN + 8		

//����������ʼ����
#define  S_C_STARTBASTEST_REQ				EV_MPUAUTOTEST_BGN + 9
#define  C_S_STARTBASTEST_ACK				EV_MPUAUTOTEST_BGN + 10		//��Ϣͷ�� channel id
#define  C_S_STARTBASTEST_NACK				EV_MPUAUTOTEST_BGN + 11
	 
//�ı����ģʽ��VMP->BAS��
//��Ϣ�壺u8 byMode�� 11 --��ת��VMPģʽ�� 13 -- ��ת��BASģʽ ����֮ǰ�ĺ궨�壩
#define  S_C_CHANGETESTMODE_CMD				EV_MPUAUTOTEST_BGN + 12		

const s8 achServIpAddr[] = "10.1.1.1";

#endif