#ifndef _h_tperrno_h__
#define _h_tperrno_h__

#define TP_UMS_ChairIsUMS		10000				//主席是UMS
#define TP_UMS_ChairIsMT		10001				//主席是MT
#define TP_UMS_ChairIsMCU		10002				//主席是MCU
#define TP_UMS_SuperDropped		10003				//上级掉线

#define TP_UMS_AdapterQuit		10004				//接入板掉线
#define TP_UMS_AllEpHungUp		10005				//所有会场挂断
#define TP_UMS_BasDisConnect	10006				//适配板掉线
#define TP_UMS_BasStartFail		10007				//适配开启失败
#define TP_UMS_MediaTransQuit	10008				//转发板掉线

#define TP_UMS_QuitAudMix       15000				//会议语音激励关闭：资源不足


#define TP_UMS_Discard_Start	10100				//开启讨论失败：资源不足
#define TP_UMS_Discard_AddEp	10101				//添加会场失败：资源不足
#define TP_UMS_Discard_EpOnLine	10102				//会场xx离开讨论：资源不足   注：m_dwReserve1填的是离开讨论的会场ID
#define TP_UMS_Discard_Error	10103				//会议讨论关闭：资源不足
#define TP_UMS_Discard_Busy	    10104				//会议讨论操作失败：系统忙

#endif // _h_tperrno_h__
