#ifndef _h_eventoutcnscamera_h__
#define _h_eventoutcnscamera_h__

#include "tpeventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSCAMERAEVENT
{
#endif 
	
	_ev_segment( outercnscamera  )


/***********************<< 维护工具登陆通知  >>************************	
 *[消息体]		
 *
 *
 *[消息方向]
 *
 *   CNS => CnDevice
 */_event(  ev_GetCameraInfo_Req )
   _ev_end

/**********************<< 导入摄像机配置通知 >>**********************
*[消息体]
*
*
*[消息方向]
*
* UI => cns => cnDevice
*/_event( ev_Cn_LoadCameraFileNty )
  _ev_end

  /**********************<< 摄像机上电通知 >>**********************
  *[消息体]
  *
  *    + BOOL    =TRUE tptools抢登时发送正在上电的通知 FALSE 正常情况
  *
  *[消息方向]
  *
  *   cnDevice => cnDevice
  */_event( ev_Cn_CameraPowerOnNty )
	_body(  BOOL,      1           )
    _ev_end


/***********************<< 摄像机配置通知  >>************************	
 *[消息体]		
 *    + TCnCameraCfg    读取的摄像机配置文件
 *    + u8              当前摄像机索引
 *
 *[消息方向]
 *
 *   CNS => CnDevice
 */_event(  ev_Cn_CameraCfgNty                )
   _body (  TCnCameraCfg, MAX_CNCAMERA_NUM )
   _body (  u8          ,    1             )
   _ev_end


/***********************<< 选择控制摄像机命令  >>************************	
 *[消息体]			 
 *    + u8  摄像头索引 0-2
 *
 *[消息方向]
 *
 *   CNS => CnDevice
 */_event(  ev_Cn_CameraSelectCmd )
   _body (  u8         ,       1 )
   _ev_end

/***********************<< 选择控制摄像机返回命令  >>************************	
 *[消息体]			 
 *    + u8    摄像头索引 0-2
 *    + BOOL  = TRUE 选择成功 =FALSE 选择失败
 *[消息方向]
 *
 *   CNS <= CnDevice
 */_event(  ev_Cn_CameraSelectInd )
   _body (   u8         ,       1 )
   _body (   BOOL       ,       1 )
   _ev_end

/***********************<< 摄像头聚焦命令  >>************************	
 *[消息体]			 
 *    + EmFocus         emFar 远焦  emNear近焦
 *    + EmCnAction      emCnStart/emCnStop
 *
 *[消息方向]
 *
 *   CNS => CnDevice
 */_event(  ev_Cn_CameraFocusCmd   )
   _body (  EmFocus        ,1 )
   _body (  EmCnAction     ,1 )
   _ev_end

/***********************<< 摄像头聚焦返回命令  >>************************	
 *[消息体]			 
 *    + EmFocus         emFar 远焦  emNear近焦
 *    + BOOL        =TRUE 设置成功  =FALSE 设置失败
 *
 *[消息方向]
 *
 *   CNS => CnDevice
 */_event(  ev_Cn_CameraFocusInd   )
   _body (  EmFocus        ,1 )
   _body (  BOOL           ,1 )
   _ev_end

/***********************<< 摄像头自动聚焦命令  >>**********************	
 *[消息体]			 
 *    EmFocusMode 
 *
 *[消息方向]
 *
 *   CNS      => CnDevice
 */_event(  ev_Cn_CameraAutoFocusCmd  	)
   _body (  EmFocusMode,        1  )
   _ev_end
 
/***********************<< 摄像头自动聚焦返回命令  >>**********************	
 *[消息体]			 
 * BOOL   =TRUE 设置成功   =FALSE 设置失败
 *
 *[消息方向]
 *
 *   CNS      <= CnDevice
 */_event(  ev_Cn_CameraAutoFocusInd  	)
   _body (  EmFocusMode,        1  )
   _body (  BOOL ,  1)
   _ev_end


/***********************<< 摄像视野调节命令  >>************************	
 *[消息体]			 
 *    EmZoom          emTele 镜头拉近  emWide 镜头推远 
 *
 *[消息方向]
 *
 *   CNS     => CnDevice
 */_event(  ev_Cn_CameraZoomCmd    )
   _body ( EmZoom               ,1 )
   _ev_end
 
/***********************<< 摄像视野调节返回命令  >>************************	
 *[消息体]			 
 *    EmZoom           拉近/推远
 *    BOOL            =TRUE 设置成功  =FALSE 设置失败  
 *
 *[消息方向]
 *
 *   CNS     <=  CnDevice
 */_event(  ev_Cn_CameraZoomInd  )
   _body (  EmZoom          , 1  )
   _body (  u16             , 1  )
   _body (  BOOL            , 1  )
   _ev_end

 
/***********************<< 预置位保存命令  >>************************	
 *[消息体]	
 *
 *[消息方向]
 *
 *   CNS    => CnDevice
 */_event(  ev_Cn_CameraPersetSaveCmd	  )
   _ev_end

/***********************<< 预置位保存返回命令  >>************************	
 *[消息体]	
 *    + BOOL    TRUE= 保存预置位成功   = FALSE 保存失败		 
 *
 *[消息方向]
 *
 *   CNS    <=  CnDevice
 */_event(  ev_Cn_CameraPersetSaveInd	  )
   _body (  BOOL ,              1     )
   _ev_end

 /***********************<< 保存下次开机调用预置位1  >>************************	
 *[消息体]			 
 *    + BOOL   =TURE 调用  =FALSE 关闭调用
 *
 *[消息方向]
 *
 *   CNS => CnDevice
 */_event(  ev_Cn_CameraPresetCmd )
   _body (  BOOL,    1 )
   _ev_end


 /***********************<< 保存预置位调用返回值  >>************************	
 *[消息体]			 
 *    + BOOL   =TURE 下次开机调用预置位1  =FALSE 关闭调用  
 *    + BOOL   =TURE 写入成功  =FALSE 写入失败
 *[消息方向]
 *
 *   CNS => CnDevice
 */_event(  ev_Cn_CameraPresetInd )
   _body (  BOOL,    1 )
   _body (  BOOL,    1 )
   _ev_end

/***********************<< 恢复摄像机出厂配置 >>************************	
 *[消息体]			 
 * 无
 *[消息方向]
 *   
 *   CNS          => CnDevice
 */_event(  ev_Cn_CameraResetCmd  )
   _ev_end

/***********************<< 恢复摄像机出厂配置返回消息 >>************************	
 *[消息体]			 
 *      TCnCameraCfg 读取恢复到默认的摄像机值 返回给UI
 *      u8           摄像机索引号
 *      BOOL   =TRUE 设置成功  FALSE 设置失败
 *[消息方向]
 *   
 *   CNS          <=  CnDevice
 */_event(  ev_Cn_CameraResetInd  )
   _body (  TCnCameraCfg,      1  )
   _body (  u8   ,             1  )
   _body (  BOOL ,             1  )
   _ev_end

/***********************<< 摄像机 视野在OSD上显示比例命令 >>************************	
 *[消息体]			 
 *   EmOSDShow     显示开关 emOSDOff / emOSDOn
 * 
 *
 *[消息方向]
 *
 *   CNS          =>CnDevice
 */_event(  ev_Cn_CameraOSDShowCmd  )
   _body (  EmOSDShow ,    1)
   _ev_end

/**********************<< 摄像机 视野在OSD上显示比例返回命令 >>************************	
 *[消息体]			 
 *
 * EmOSDShow     emOSDOff/emOSDOn 
 * BOOL          =TRUE 设置成功  =FALSE 设置失败
 *[消息方向]
 *
 *   CNS          <= CnDevice
 */_event(  ev_Cn_CameraOSDShowInd  )
   _body (  EmOSDShow ,    1)
   _body (  BOOL      ,    1)
   _ev_end


/***********************<< 摄像机自动曝光命令 >>************************	
 *[消息体]			 
 *   EmExpMode   
 *
 *[消息方向]
 *   
 *   CNS          =>CnDevice
 */_event(  ev_Cn_CameraAutoExposureCmd  )
   _body (  EmExpMode,                1)
   _ev_end

 /***********************<< 摄像机自动曝光返回命令 >>************************	
 *[消息体]			 
 * BOOL       =TRUE 设置成功  =FALSE 设置失败 
 *
 *[消息方向]
 *   
 *   CNS          <= CnDevice
 */_event(  ev_Cn_CameraAutoExposureInd  )
   _body (  EmExpMode,                1  )
   _body (  BOOL ,                    1  )
   _ev_end


/***********************<< 摄像机手动曝光——增益调节命令 >>************************	
 *[消息体]
 *
 * EmGain  增益范围 0dB  3dB  6dB ···42dB
 *
 *[消息方向]
 *  
 *   CNS          => CnDevice
 */_event(  ev_Cn_CameraGainCmd  )
   _body (  EmGain    ,1)
   _ev_end
   
/***********************<< 摄像机手动曝光——增益调节返回命令 >>************************	
 *[消息体]
 *
 * EmGain  增益范围 0dB  3dB  6dB ···42dB
 * BOOL    =　TRUE 设置成功   =FALSE 设置失败
 *
 *[消息方向]
 *  
 *   CNS          <= CnDevice
 */_event(  ev_Cn_CameraGainInd  )
   _body ( EmGain    ,1)
   _body ( BOOL      ,1)
   _ev_end

/***********************<< 摄像机手动曝光——快门调节命令 >>************************	
 *[消息体]
 *
 * EmShutSpd  快门范围 1/60  1/120 1/250.....1/4000  1/10000
 *
 *[消息方向]
 *   
 *   CNS          => CnDevice
 */_event(  ev_Cn_CameraShutSpdCmd  )
   _body (  EmShutSpd    ,1)
   _ev_end

/***********************<< 摄像机手动曝光——快门调节返回命令 >>************************	
 *[消息体]
 *
 * EmShutSpd  快门范围 1/60  1/120 1/250.....1/4000  1/10000
 * BOOL      =TRUE  设置成功  =FALSE 设置失败
 *
 *[消息方向]
 *   
 *   CNS          <= CnDevice
 */_event(  ev_Cn_CameraShutSpdInd  )
   _body ( EmShutSpd    ,1)
   _body ( BOOL         ,1)
   _ev_end

/***********************<< 摄像机手动曝光——背光调节命令 >>************************	
 *[消息体]
 *
 * EmBackLightType  背光模式  关闭，multi（默认7，范围0-15），center，face detect
 * u8  0--15 multi模式调节  否则 值设置为 0--15之外的值
 *
 *[消息方向]
 *   CNS        => CnDevice
 */_event(  ev_Cn_CameraBackLightCmd  )
   _body (  EmBackLightType    ,1)
   _body (  u8                 ,1)
   _ev_end

/***********************<< 摄像机手动曝光——背光调节返回命令 >>************************	
 *[消息体]
 *
 * EmBackLightType  背光模式  关闭，multi（范围0-15），center，face detect
 * BOOL   =TRUE  设置成功    =FALSE  设置失败
 *
 *[消息方向]
 *   CNS        <= CnDevice
 */_event(  ev_Cn_CameraBackLightInd  )
   _body ( EmBackLightType    ,1)
   _body (  u8                ,1)
   _body ( BOOL               ,1)
   _ev_end

/***********************<< 摄像机手动曝光——光圈调节命令 >>************************	
 *[消息体]
 *
 * u8  光圈大小 范围 0--100
 *
 *[消息方向]
 *   
 *   CNS        => CnDevice
 */_event(  ev_Cn_CameraApertureCmd  )
   _body (  u8    ,1)
   _ev_end

/***********************<< 摄像机手动曝光——光圈调节返回命令 >>************************	
 *[消息体]
 *
 * u8  光圈大小 范围 0--100
 * BOOL   =TRUE 设置成功   =FALSE 设置失败
 *
 *[消息方向]
 *   
 *   CNS        => CnDevice
 */_event(  ev_Cn_CameraApertureInd  )
   _body (  u8    ,1)
   _body (  BOOL  ,1)
   _ev_end

/***********************<< 摄像机自动白平衡命令 >>************************	
 *[消息体]
 *
 *[消息方向]
 *   
 *   CNS        => CnDevice
 */_event(  ev_Cn_CameraAutoWBCmd  )
   _body (  EmWBMode,        1  )
   _ev_end

/***********************<< 摄像机自动白平衡返回命令 >>************************	
 *[消息体]
 *   BOOL       = TRUE  设置成功  =FALSE 设置失败  
 *
 *[消息方向]
 *   
 *   CNS        <= CnDevice
 */_event(  ev_Cn_CameraAutoWBInd  )
   _body (  EmWBMode,           1  )
   _body (  BOOL   ,            1  )
   _ev_end

/***********************<< 摄像机手动白平衡--R Gain命令 >>************************	
 *[消息体]
 *
 *  u16  R Gain 范围 0--100 
 *
 *[消息方向]
 *   
 *   CNS        => CnDevice
 */_event(  ev_Cn_CameraRGainCmd  )
   _body (  u16       , 1)
   _ev_end

/***********************<< 摄像机手动白平衡--R Gain返回命令 >>************************	
 *[消息体]
 *
 *  u16  R Gain 范围 0--100 
 *  BOOL   =TRUE 设置成功      =FALSE  设置失败
 *[消息方向]
 *   
 *   CNS        <=  CnDevice
 */_event(  ev_Cn_CameraRGainInd  )
   _body (  u16       ,        1  )
   _body (  BOOL      ,        1  )
   _ev_end

/***********************<< 摄像机手动白平衡--B Gain命令 >>************************	
 *[消息体]
 *
 *  u16  B Gain 范围 0--100 
 *
 *[消息方向]
 *   
 *   CNS        => CnDevice
 */_event(  ev_Cn_CameraBGainCmd  )
   _body (  u16       , 1)
   _ev_end

/***********************<< 摄像机手动白平衡--B Gain返回命令 >>************************	
 *[消息体]
 *
 *  u16  B Gain 范围 0--100 
 *  BOOL    =TRUE  设置成功  =FALSE 设置失败
 *[消息方向]
 *   
 *   CNS        <= CnDevice
 */_event(  ev_Cn_CameraBGainInd  )
   _body (  u16       , 1  )
   _body (  BOOL      , 1  )
   _ev_end

 /***********************<< 摄像机场景模式 命令 >>************************	
 *[消息体]
 *
 *  EmPicSceMode  场景模式   日光灯模式  太阳光模式 手动模式
 *
 *[消息方向]
 *   
 *   CNS        => CnDevice
 */_event(  ev_Cn_CameraPicSceneModeCmd  )
   _body (  EmPicSceMode       , 1  )
   _ev_end

 /***********************<< 摄像机场景模式返回命令 >>************************	
 *[消息体]
 *
 *  EmPicSceMode  场景模式   日光灯模式  太阳光模式 手动模式
 *  BOOL     =TRUE   设置成功   =FALSE  设置失败
 *[消息方向]
 *   
 *   CNS        <=  CnDevice
 */_event(  ev_Cn_CameraPicSceneModeInd  )
   _body (  EmPicSceMode       , 1  )
   _body (  BOOL               , 1  )
   _ev_end

/***********************<< 摄像机 模式--- 手动 GAMMA调节命令 >>************************	
 *[消息体]
 *
 *  EmGamma 
 *
 *[消息方向]
 *   
 *   CNS        => CnDevice
 */_event(  ev_Cn_CameraGammaCmd  )
   _body (  EmGamma       , 1)
   _ev_end

/***********************<< 摄像机 模式--- 手动 GAMMA调节返回命令 >>************************	
 *[消息体]
 *
 *  EmGamma  emGammaOff、emGammaOn 、emSmart1、 emStrat2
 *  BOOL   =TRUE  设置成功   =FALSE 设置失败
 *[消息方向]
 *   
 *   CNS        <= CnDevice
 */_event(  ev_Cn_CameraGammaInd  )
   _body (  EmGamma       , 1  )
   _body (  BOOL          , 1  )
   _ev_end

/***********************<< 摄像机 模式--- 光圈调节命令 >>************************	
 *[消息体]
 *
 *  u8 光圈大小  1--15
 *
 *[消息方向]
 *   
 *   CNS        => CnDevice
 */_event(  ev_Cn_CameraPicSceAptCmd  )
   _body (  u8          , 1  )
   _ev_end

 /***********************<< 摄像机 模式--- 光圈调节返回命令 >>************************	
 *[消息体]
 *
 *  u8 光圈大小  1--15
 *  BOOL    =TRUE  设置成功   =FALSE  设置失败
 *[消息方向]
 *   
 *   CNS        <= CnDevice
 */_event(  ev_Cn_CameraPicSceAptInd  )
   _body (  u8          , 1  )
   _body (  BOOL        , 1  )
   _ev_end  

/***********************<< 摄像机 图片调节---对比度 调节命令 >>************************	
 *[消息体]
 *
 *  u16  大小  0--200
 *
 *[消息方向]
 *   
 *   CNS        => CnDevice
 */_event(  ev_Cn_CameraContrastCmd  )
   _body (  u16       , 1)
   _ev_end

/***********************<< 摄像机 图片调节---对比度 调节返回命令 >>************************	
 *[消息体]
 *
 *  u16  大小  0--200
 *  BOOL     =TRUE  设置成功    =FALSE  设置失败
 *[消息方向]
 *   
 *   CNS        =< CnDevice
 */_event(  ev_Cn_CameraContrastInd  )
   _body (  u16       , 1)
   _body (  BOOL      , 1)
   _ev_end

/***********************<< 摄像机 图片调节---色度 调节命令 >>************************	
 *[消息体]
 *
 *  u16  大小  0--200
 *
 *[消息方向]
 *  
 *   CNS        => CnDevice
 */_event(  ev_Cn_CameraHueCmd  )
   _body (  u16       , 1)
   _ev_end

/***********************<< 摄像机 图片调节---色度 调节返回命令 >>************************	
 *[消息体]
 *
 *  u16  大小  0--200
 *  BOOL      =TRUE  设置成功   =FALSE  设置失败
 *[消息方向]
 *  
 *   CNS        <=  CnDevice
 */_event(  ev_Cn_CameraHueInd  )
   _body (  u16       , 1)
   _body (  BOOL      , 1)
   _ev_end

/***********************<< 摄像机 图片调节---饱和度 调节命令 >>************************	
 *[消息体]
 *
 *  u16  大小  0--200
 *
 *[消息方向]
 *   
 *   CNS        => CnDevice
 */_event(  ev_Cn_CameraSaturatCmd  )
   _body (  u16       , 1)
   _ev_end

/***********************<< 摄像机 图片调节---饱和度 调节返回命令 >>************************	
 *[消息体]
 *
 *  u16  大小  0--200
 *  BOOL      =TRUE  设置成功  =FALSE 设置失败
 *[消息方向]
 *   
 *   CNS        <=  CnDevice
 */_event(  ev_Cn_CameraSaturatInd  )
   _body (  u16       , 1)
   _body (  BOOL      , 1)
   _ev_end

/***********************<< 摄像机 图片调节---亮度 调节命令 >>************************	
 *[消息体]
 *
 *  u16  大小  0--200
 *
 *[消息方向]
 *   
 *   CNS        => CnDevice
 */_event(  ev_Cn_CameraBrightCmd  )
   _body (  u16       , 1)
   _ev_end

/***********************<< 摄像机 图片调节---亮度 调节返回命令 >>************************	
 *[消息体]
 *
 *  u16  大小  0--200
 *  BOOL       =TRUE 设置成功  FALSE 设置失败
 *[消息方向]
 *   
 *   CNS        <=  CnDevice
 */_event(  ev_Cn_CameraBrightInd  )
   _body (  u16       , 1)
   _body (  BOOL      , 1)
   _ev_end

/***********************<< 摄像机 降噪---噪点过滤 调节命令 >>************************	
 *[消息体]
 *
 *  EmStmClean  默认LOW  范围OFF,LOW,MID,HIGH
 *
 *[消息方向]
 *   
 *   CNS        => CnDevice
 */_event(  ev_Cn_CameraNRStmCleanCmd  )
   _body (  EmStmClean        , 1)
   _ev_end

/***********************<< 摄像机 降噪---噪点过滤 调节返回命令 >>************************	
 *[消息体]
 *
 *  EmStmClean  默认LOW  范围OFF,LOW,MID,HIGH
 *  BOOL      =TURE   设置成功  =FALSE  设置失败
 *[消息方向]
 *   
 *   CNS        <= CnDevice
 */_event(  ev_Cn_CameraNRStmCleanInd  )
   _body (  EmStmClean        , 1)
   _body (  BOOL              , 1)
   _ev_end

/***********************<< 摄像机 降噪---3D降噪 调节命令 >>************************	
 *[消息体]
 *
 *  Em3DNR   em3DNROff 关OFF，em3DNROn 开
 *
 *[消息方向]
 *   
 *   CNS        => CnDevice
 */_event(  ev_Cn_Camera3DNRCmd  )
   _body (  Em3DNR       ,  1)
   _ev_end

/***********************<< 摄像机 降噪---3D降噪 调节返回命令 >>************************	
 *[消息体]
 *  Em3DNR   em3DNROff 关OFF，em3DNROn 开
 *  BOOL     =TRUE  设置成功  =FALSE 设置失败
 *  
 *[消息方向]
 *   
 *   CNS        <= CnDevice
 */_event(  ev_Cn_Camera3DNRInd  )
   _body (  Em3DNR       ,  1)
   _body (  BOOL         , 1)
   _ev_end
		
/***********************<< 精确设置摄像机zoom值 >>************************	
 *[消息体]
 *    + u16  由于消息无法传递浮点值 ，这里界面保留两位小数，乘100转为u16传递
 *  
 *[消息方向]
 *   
 *   CNS       => CnDevice
 */_event(  ev_Cn_SetCameraZoomCmd  )
   _body (  u16        ,       1    )
   _ev_end		

 /********************<< 精确设置摄像机zoom值返回值 >>**********************	
 *[消息体]
 *    + u16
 *    + BOOL
 *  
 *[消息方向]
 *   
 *   CNS        <= CnDevice
 */_event(  ev_Cn_SetCameraZoomInd  )
   _body (  u16        ,       1    )
   _body (  BOOL       ,       1    )
   _ev_end
   
 /********************<< 中控控制主摄像机电源命令 >>**********************	
 *[消息体]
 *    + EmCamPowerMode     emCamPowerOn/emCamPowerOff
 *  
 *[消息方向]
 *   
 *   Centre   <= CnDevice
 */_event(  ev_Cn_SetCamPowerModeCmd  )
   _body (  EmCamPowerMode,      1    )
   _ev_end

/********************<< 主摄像机电源状态通知中控维护工具 >>**********************	
 *[消息体]
 *    + EmCamPowerMode     emCamPowerOn/emCamPowerOff
 *  
 *[消息方向]
 *   
 *   Centre   <= CnDevice
 */_event(  ev_Cn_CamPowerStateNty          )
   _body (  EmCamPowerMode, MAX_CNCAMERA_NUM)
   _ev_end

/********************<< 摄像机上电延时定时器 >>**********************	
 *[消息体]
 *  
 *[消息方向]
 *   
 *   CnDevice   <= CnDevice
 */_event(  ev_Cn_CamPowerOnTimer  )
   _ev_end


#ifndef _MakeTpEventDescription_
		_ev_segment_end( outercnscamera )
};
#endif
#endif 