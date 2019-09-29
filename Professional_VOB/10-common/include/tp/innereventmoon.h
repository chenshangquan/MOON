#ifndef _h_innereventmoon_h__
#define _h_innereventmoon_h__


#include "mooneventcomm.h"


#ifndef _MakeTpEventDescription_
enum EmUmsInnerToCns
{
#endif

_ev_segment( innermoon )

 /***********************<< 喂狗定时器  >>******************
 *[消息体]
 *  NULL
 *[消息方向]
 *           => MtService
 */_event( ev_TpWatchdogtimer_Nty )
   _ev_end

/***********************<< 喂狗通知消息  >>*********************
 *[消息体]
 *  NULL
 *[消息方向]
 *  MtSysApi <= MtService
 */_event( ev_TpNotifyWatchdog_Ind )
   _ev_end

/***********************<< 运行喂狗  >>*************************
 *[消息体]
 *  +BOOL TRUE=运行喂狗 FALSE=停止喂狗
 *[消息方向]
 *  MtSysApi => MtService
 */_event( ev_TpRunWatchdog_Cmd )
   _ev_end

/***********************<<moon各模块启动命令>>************************	
 *[消消息体]			 
 *  NULL
 *[消息方向]
 *    moon => moon
 */
_event(  ev_TpModuleStartCmd )
_ev_end

/***********************<<moon上线>>************************	
 *[消消息体]			 
 *  TMtTPEpParam 会场参数
 *[消息方向]
 *   moon => moon
 */
_event(  ev_TpMoonOnline_Nty )
_ev_end

 /***********************<<cam登录>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  moonue->moon
 */
_event(  ev_TpCamCPLogin_Ind )
_ev_end

 /***********************<<cam登录>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  moon->moon
 */
_event(  ev_TpCamCPLoginInst_Req )
_ev_end

 /***********************<<cam退出>>************************	
 *[消消息体]			 
 * u8 Pad ID
 *[消息方向]
 *  moonue->moon
 */
_event(  ev_TpCamCPLogout_Ind )
_body( u8, 1)
_ev_end

 /***********************<<cam重启命令>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  cns->cns
 */
_event(  ev_TpModuleRebootCmd )
_ev_end

/***********************<<cam设置参数>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  cam <- moon 
 */
_event(  ev_TpMoonCamInfo_Cmd )
_body( TTPMoonCamInfo, 1)
_body( BOOL, 1 )
_body( BOOL, 1 )//标识当前是否为恢复默认时发送机芯信息
_ev_end

/***********************<<cam参数show命令>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  cam <- moon 
 */
_event(  ev_TpMoonCamInfoShow_Cmd )
_ev_end

/***********************<<cam机芯调试信令>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  cam <- moon 
 */
_event(  ev_TpMoonCamTest_Cmd )
_body( u8, 1)
_body( s8, 20)
_ev_end

/***********************<<cam机芯调试信令>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  cam <- moon 
 */
_event(  ev_TpMoonCamQuiryTest_Cmd )
_body( u8, 1)
_body( s8, 20)
_ev_end

/***********************<<cam输出端口制式通知>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  cam <- moon 
 */
_event(  ev_TpOutPotFormat_Nty )
_body( EmTPMOONOutMode, 1)
_ev_end

/***********************<<cam输出端口制式测试>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  cam <- moon 
 */
_event(  ev_TpDVIOutPotTest_Cmd )
_body( EmMOONProductTestType, 1 )
_body( u8, 1)
_ev_end

/***********************<<cam输出端口制式测试>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  cam <- moon 
 */
_event(  ev_TpZoomTest_Timer )
_ev_end

/***********************<<cam串口测试>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  cam -> moon 
 */
_event(  ev_TpRS323Test_Cmd )
_ev_end

/***********************<<cam输出制式命令>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  cam -> moon 
 */
_event(  ev_TpCamOutFoumat_Cmd )
_ev_end

/***********************<<清空串口脏数据定时器>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  cam -> moon 
 */
_event(  ev_TpCamReadDirtyData_Timer )
_ev_end

/***********************<<梯形数据改变>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  moon -> moon 
 */
_event(  ev_TpCorrectChange_Cmd )
_body( TTPDistortParam, 1)
_body( EmTPCorrect, 1)
_body( u8, 1)
_ev_end

/***********************<<查询机芯波特率和输出制式>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  moon -> moon 
 */
_event(  ev_TpQuiryTest_Cmd )
_ev_end

_event(  ev_TpTestLvdsBaud_Cmd )
_body( u8, 1)
_ev_end

//add by youjx 2016.11.8
/***********************<<cam查询图像参数：亮度、色度、饱和度、对比度>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  moon -> cam
 */
_event(  ev_TpInquiryImagePara_Cmd )
_body( EmTPImagePara, 1)
_body( u8, 1)
_ev_end 

/***********************<<cam设置视野倍率限制>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  moon -> cam
 */
_event(  ev_TpCamSetZoomLimit_Cmd )
_body( u8, 1)
_body( u16, 1)
_ev_end

/***********************<<cam设置中心十字架>>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  moon -> cam
 */
 _event( ev_TpCamSetCross_Cmd )
 _body( u8, 1)
 _body( BOOL, 1)
 _ev_end

/***********************<<moon设置梯形校正>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  moon -> cam
 */
 _event( ev_TpDistortChange_Cmd)
 _body(TTPDistortCorrectInfo, 1)
 _body(u8, 1)
 _ev_end

/***********************<<moon设置颜色校正>************************	
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  moon -> cam
 */
 _event( ev_TpChangeColorCoeff_Cmd)
 _body(TTPColorCoeff, 1)
 _body(u8, 1)
 _ev_end

 /************************H650机芯由zoomPos得到zoom后的通知********
 *[消消息体]			 
 * NULL
 *[消息方向]
 *  moon <- cam
 */
 _event( ev_TpH650Zoom_Nty)
 _body(u8, 1)
 _body(u32, 1)
 _ev_end
 //add end

#ifndef _MakeTpEventDescription_
   _ev_segment_end(innermoon)
};
#endif



#endif // _h_innereventregsrv_h__
