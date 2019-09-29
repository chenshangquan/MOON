/*****************************************************************************
  模块名      : codecwrapper_t300.a
  文件名      : codecwrapper_t300.h
  相关文件    : codecwrapperdef_hd.h
  文件实现功能: 
  作者        : 张涛
  版本        : V4.0  Copyright(C) 2007-2008 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2013/02/20  4.0         张涛        创建
******************************************************************************/
#ifndef _CODECWRAPPER_T300_H_
#define _CODECWRAPPER_T300_H_

#ifdef _CODECWRAPPER_TOS_MODULE_ //2013-3-26

#include "tos/codecwrapper_hd.h"

#else

#include "codecwrapperdef_hd.h"

class CVideoEncoder;
class CAudioEncoder;
class CVideoDecoder;
class CAudioDecoder;


//t300 视频使用 start
enum enVideoPIPIndexEX
{
	VIDEO_PIPINDEX_NULL_EX = 0,             //空画面
	VIDEO_PIPINDEX_LOCAL_EX,			    //本地
	VIDEO_PIPINDEX_DEC1,					//主解码1
	VIDEO_PIPINDEX_DEC2,					//主解码2
	VIDEO_PIPINDEX_DEC3,					//主解码3
	VIDEO_PIPINDEX_AUX_LOCAL,
	VIDEO_PIPINDEX_INVALID_EX
};

//具体编解码器信息，用户通过配置如下参数，在8377上创建远程的codec，并分布到所指定的netra上
typedef struct tagNetraCodecInfo
{
	u32     dwNetraID;						//codec所在的Netra编号 (enNetraID)
	u32     dwIndex;						//编解码通道号 0~x
	u32     dwVidPort;						//采集口(编码器) 播放口(解码器)
	u32     dwPlayStd;						//video口制式，only decoder
	u32     bAdapterOn;						//带适配功能
	void*   pReserve;						//保留参数，若适配功能带，则此处扩展参数(TAdapterInfo)
}TNetraCodecInfo;

//带适配的扩展功能后，回调函数地址必须填充，用于给用户上传码流数据，此结构体编码器或解码器均试用
typedef struct tagAdapterInfo
{
	u32     dwWidth;						//适配分辨率宽度
	u32     dwHeight;						//适配分辨率高度
	u32     dwFramerate;					//适配帧率
	u32     dwMediaType;					//适配码流类型，默认264
	u32     dwBitrate;
	u32     dwProfile;						//Hp or BP
	u32     dwMaxKeyFrameInterval;				//设定最大关键帧间隔
	FRAMECALLBACK pStreamCallBack;			//适配后码流回调函数地址
	void*   pContext;						//回调上下文
}TAdapterInfo;
//t300 视频使用 end


class CKdvVidEnc
{
public:
	CKdvVidEnc();
	~CKdvVidEnc();
public:
	//向下兼容，t300 不使用
	u16    CreateEncoder(TEncoder *pEncoder);                 /*HD1等使用*/
    u16    Create(TVidEncInit* pEnc, void* pReserve = NULL);  /*二代高清终端请使用这个接口*/
	u16    CreateHD3(TVidEncHD3RD* pEnc);							/*三代高清使用这个接口*/

	/************************************************************************/
	/* 函数名:  Create                                                      */  
	/* 函数参数:                                                            */
	/*          TNetraCodecInfo*   pEnc    描述编码器的实际位置以及序号     */
	/* 函数功能: 编码器的创建 创建成功返回0 								*/
	/************************************************************************/	
    u16    Create(TNetraCodecInfo* pEnc); 

	/*获取编码器状态*/
    u16    GetEncoderStatus(TKdvEncStatus &tKdvEncStatus);

	/*获取编码器的统计信息*/
    u16    GetEncoderStatis(TKdvEncStatis &tKdvEncStatis);

	/************************************************************************/
	/* 函数名:   SetVidDataCallback                                          */  
	/* 函数参数:                                                             */
	/*           FRAMECALLBACK fVidData     回调函数地址                     */
	/*           void* pContext             回调函数的参数					*/
	/*																		*/
	/* 函数功能:	设置视频编码数据回调									*/
	/************************************************************************/
	u16    SetVidDataCallback(FRAMECALLBACK fVidData, void* pContext); 

    /************************************************************************/
    /* 函数名:     SetEncQualityEnhance                                      */  
    /* 函数参数:                                                             */
    /*              BOOL32 bEnhance                                         */
    /* 函数功能:  追加编码清晰度接口，										*/
	/*				TRUE为提高清晰度，FALSE为关闭清晰度。会有性能损失	    */
    /************************************************************************/
	u16    SetEncQualityEnhance(BOOL32 bEnhance);
	
	/************************************************************************/
	/* 函数名:   SetVidCapPortType                                           */  
	/* 函数参数:                                                             */
	/*           u32 dwType                                                  */
	/* 函数功能:	设置采集接口											*/
	/************************************************************************/
	u16    SetVidCapPortType(u32 dwType);

	/************************************************************************/
	/* 函数名:  SetVideoEncParam                                             */  
	/* 函数参数:                                                             */
	/*             TVideoEncParam *ptVideoEncParam                          */
	/* 函数功能: 设置编码参数，可以运行中调用								*/
	/************************************************************************/
    u16    SetVideoEncParam(const TVideoEncParam *ptVideoEncParam); 

	/*得到视频编码参数*/
    u16    GetVideoEncParam(TVideoEncParam &tVideoEncParam );
	
	/*开始压缩图像*/
    u16    StartEnc();

	/*停止压缩图像*/
    u16    StopEnc(); 

	/************************************************************************/
	/* 函数名:         GetVideoSrcInfo                                       */  
	/* 函数参数:                                                             */
	/*                 TVidSrcInfo& tInfo                                    */
	/* 函数功能:	获取输入视频信号制式									*/
	/************************************************************************/
    u16    GetVideoSrcInfo(TVidSrcInfo& tInfo); /**/

	/************************************************************************/
	/* 函数名:      ScaleVideoCap											*/  
	/* 函数参数:															*/
	/*              u32 dwVidSrcPort :视频采集端子							 */
	/*              u8 byType        :调节类型 VIDCAP_SCALE_BRIGHTNESS 等	*/
	/*				u8 byValue       :调节数值 0~255; 0x80为默认值			*/
	/* 函数功能:	调节视频采集参数										*/
	/************************************************************************/
    u16    ScaleVideoCap(u32 dwVidSrcPort,u8 byType, u8 byValue); 

	/************************************************************************/
	/* 函数名:      SetFastUpata                                             */  
	/* 函数参数:                                                             */
	/*              BOOL32 bIsNeedProtect 是否开启1s内保护                   */
	/* 函数功能:	强制编一帧关键帧，调用间隔最少1s						*/
	/************************************************************************/
	u16    SetFastUpata(BOOL32 bIsNeedProtect = TRUE);   

	/************************************************************************/
	/* 函数名:      SetSendStaticPic                                         */  
	/* 函数参数:                                                             */
	/*              BOOL32  bSendStaticPic                                   */
	/* 函数功能:	发送静态图片											 */
	/************************************************************************/
	u16    SetSendStaticPic(BOOL32  bSendStaticPic);

	/************************************************************************/
	/* 函数名:         StartAddLogoInEncStream                              */  
	/* 函数参数:                                                            */
	/*                 TFullLogoParam &tLogoParm                            */
	/* 函数功能:	设置台标参数并开启台标									*/
	/************************************************************************/
    u16	   StartAddLogoInEncStream(TFullLogoParam &tLogoParm);

	/************************************************************************/
	/* 函数名:         StopAddLogoInEncStream                               */  
	/* 函数参数:                                                            */
	/* 函数功能:	关闭台标												*/
	/************************************************************************/
	u16    StopAddLogoInEncStream();

	/************************************************************************/
	/* 函数名:   SetVidEncResizeMode                                         */  
	/* 函数参数:                                                             */
	/*           s32 nMode    0-黑边， 1-裁边， 2-非等比拉伸                 */
	/* 函数功能: 设置编码前处理策略（加黑边，裁边等）						*/
	/************************************************************************/
    u16    SetVidEncResizeMode(s32 nMode);

	/************************************************************************/
	/* 函数名:   SetVidPlayPolicy                                            */  
	/* 函数参数:                                                             */
	/*           u32 dwTimeout     超时                                      */
	/*           u32 dwPlayType    无图像填充类型         					*/
	/* 函数功能: 设置本地播放策略，支持蓝屏和静态图							*/
	/************************************************************************/
    u16    SetVidPlayPolicy(u32 dwTimeout = 5, u32 dwPlayType = EN_PLAY_LAST);

	/************************************************************************/
	/* 函数名:      SetVidSrcCutLines                                       */  
	/* 函数参数:                                                             */
	/*             u32 dwLCutLine 左侧裁边像素数（16 倍数）                 */
	/*             u32 dwRCutline 右侧裁边像素数（16 倍数）					*/
	/* 函数功能: 采集图像左右裁边，主要用于采集图像左右边缘不正常情况		*/
	/************************************************************************/
	u16    SetVidSrcCutLines(u32 dwLCutLine, u32 dwRCutline);
protected:
	CVideoEncoder* m_pCodec;
};


class CKdvVidDec
{
public:
	CKdvVidDec();
	~CKdvVidDec();
public:
	//向之前兼容，t300 ppc侧不使用
	u16	   CreateDecoder(TDecoder *pDecoer);   /*HDU, HD1等使用*/
    u16    Create(TVidDecInit* pDec, void* pReserve = NULL); /*二代高清终端请使用这个接口*/
	u16    CreateHD3(TVidDecHD3RD* pDec);


	/************************************************************************/
	/* 函数名:    Create                                                    */  
	/* 函数参数:                                                            */
	/*            TNetraCodecInfo* pDec    解码器创建参数                   */
	/* 函数功能:  解码器创建												*/
	/************************************************************************/
    u16    Create(TNetraCodecInfo* pDec);

	/************************************************************************/
	/* 函数名:      SetData                                                 */  
	/* 函数参数:                                                             */
	/*              TFrameHeader& tFrameInfo                                */
	/* 函数功能:	设置视频码流数据										*/
	/************************************************************************/
	u16    SetData(const TFrameHeader& tFrameInfo);  
	
	/*开始图像解码*/
    u16    StartDec();

	/*停止图像解码*/
    u16    StopDec(); 

	/*获取解码器状态*/
	u16    GetDecoderStatus(TKdvDecStatus &tKdvDecStatus);

	/*获取解码器的统计信息*/
    u16    GetDecoderStatis(TKdvDecStatis &tKdvDecStatis);	

	//开启适配
	u16    StartAdapter();
	//停止适配
	u16    StopAdapter();
	//获取适配设置参数
	u16    GetAdapterStatus(TAdapterInfo &tKdvEncStatus, BOOL32 &bStart);
	//获取适配统计信息
	u16    GetAdapterStatis(TKdvEncStatis &tKdvEncStatis);
	//适配出关键帧
	void	FastUpdateAda();

	/************************************************************************/
	/* 函数名:      SetVidPIPParam                                           */  
	/* 函数参数:                                                             */
	/*             enVideoPIPMode enMode 画中画风格                          */
	/*             enVideoPIPIndexEX enIndex[3] 子画面内容           		*/
	/* 函数功能:	设置视频画中画模式，最大支持3画面合成					*/
	/************************************************************************/
    u16 SetVidPIPParam(enVideoPIPMode enMode, enVideoPIPIndexEX enIndex[3]);
    

	/************************************************************************/
	/* 函数名:      SetPlayScale                                             */  
	/* 函数参数:                                                             */
	/*               u16 wWidth  :显示宽比例，0为自动                       */
	/*               u16 wHeight :显示高比例，0为自动						*/
	/* 函数功能:	设置播放设备的显示比例									*/
	/*               播放制式为16:9,设置4:3后图像上下加黑边                 */
	/*               播放制式为4:3,设置16:9后图像左右加黑边                 */
	/************************************************************************/
    u16    SetPlayScale(u16 wWidth, u16 wHeight);
    
	/************************************************************************/
	/* 函数名:      SetVidPlyPortType                                        */  
	/* 函数参数:                                                             */
	/*               u32 dwType   播放口                                    */
	/* 函数功能:	设置主解码播放口										*/
	/************************************************************************/
    u16    SetVidPlyPortType(u32 dwType);

	/************************************************************************/
	/* 函数名:      SetVideoPlyInfo                                          */  
	/* 函数参数:                                                             */
	/*               u32 dwOutType     视频制式枚举                          */
	/* 函数功能:	设置视频输出信号制式									 */
	/************************************************************************/
    u16    SetVideoPlyInfo(u32 dwOutType = VID_OUTTYPE_ORIGIN);

	/************************************************************************/
	/* 函数名:      SetVideoPlyInfo                                          */  
	/* 函数参数:                                                             */
	/*               TVidSrcInfo* ptInfo     视频制式                        */
	/* 函数功能:	设置视频输出信号制式									 */
	/************************************************************************/
    u16    SetVideoPlyInfo(TVidSrcInfo* ptInfo); 

	/*获取输出视频信号制式*/
    u16    GetVideoSrcInfo(TVidSrcInfo& tInfo);   

	/************************************************************************/
	/* 函数名:     SetVidDecResizeMode                                       */  
	/* 函数参数:                                                             */
	/*             s32 nMode     处理策略：0：加黑边；1：裁边; 2:非等比      */
	/* 函数功能:   设置解码后处理策略										*/
	/************************************************************************/
	u16	   SetVidDecResizeMode(s32 nMode);

	/************************************************************************/
	/* 函数名:     SetVidOutCallBack                                        */  
	/* 函数参数:                                                             */
	/*             VIDOUTTYPECALLBACK fVidOutType  回调函数地址             */
	/* 函数功能:	设置视频制式创建成功后回调函数							*/
	/************************************************************************/
	u16	   SetVidOutCallBack(VIDOUTTYPECALLBACK fVidOutType);

	/************************************************************************/
	/* 函数名:      TestImage                                               */  
	/* 函数参数:                                                            */
	/*              BOOL32 bSet                                             */
	/* 函数功能:	开启/关闭得带测试										*/
	/************************************************************************/
	u16	   TestImage(BOOL32 bSet);

	/************************************************************************/
	/* 函数名:     SnapShot                                                  */  
	/* 函数参数:                                                             */
	/*             s8* pFileName    文件的全路径                            */
	/* 函数功能:   保存一帧播放图像为jpeg文件								*/
	/************************************************************************/
	u16    SnapShot(s8* pFileName);

	/************************************************************************/
	/* 函数名:     SnapShotView                                              */  
	/* 函数参数:                                                             */
	/*             s8* pFileName    文件的全路径                             */
	/* 函数功能:	播放指定的jpeg图片，必须是快照图，停止					*/
	/************************************************************************/
	u16    SnapShotView(s8* pFileName);

	/************************************************************************/
	/* 函数名:     SetVidPlayPolicy                                          */  
	/* 函数参数:                                                             */
	/*           u32 dwTimeout     超时                                      */
	/*           u32 dwPlayType    无图像填充类型         					*/
	/* 函数功能:	设置解码播放无图像显示策略								*/
	/************************************************************************/
	u16    SetVidPlayPolicy(u32 dwTimeout = 5, u32 dwPlayType = EN_PLAY_LAST);

protected:
	CVideoDecoder* m_pCodec;
};	


class CKdvAudEnc
{
public:
	CKdvAudEnc();
	~CKdvAudEnc();
public:
	/************************************************************************/
	/* 函数名:     CreateEncoder                                            */  
	/* 函数参数:                                                            */
	/*             TEncoder *pEncoder    编码器参数                         */
	/*             u32 dwDevVersion      板卡型号                           */
	/* 函数功能:   编码器创建								                                */
	/************************************************************************/
	u16    CreateEncoder(TEncoder *pEncoder, u32 dwDevVersion=en_T300_Board);
		
	/************************************************************************/
	/* 函数名:   SetAudDataCallback                                         */  
	/* 函数参数:                                                            */
	/*           FRAMECALLBACK fAudData     回调函数地址                    */
	/*           void* pContext             回调函数的参数					        */
	/* 函数功能:	设置音频编码数据回调									                    */
	/************************************************************************/
	u16    SetAudDataCallback(FRAMECALLBACK fAudData, void* pContext);	

	/************************************************************************/
	/* 函数名:   GetInputAudioPower                                         */  
	/* 函数参数:   返回输入功率，范围：0-31                                                      */
	/*                                                                      */
	/* 函数功能:	获取输入音频功率									                        */
	/************************************************************************/
	u32    GetInputAudioPower();

	/*获取卡农采集功率  byPower范围:0-31*/
	u16    GetCanonPower(u32 dwAudPort, u8 &byPower);
	
	/*获取编码器状态*/ 
	u16    GetEncoderStatus(TKdvEncStatus &tKdvEncStatus);	

	/*获取编码器的统计信息*/	
	u16    GetEncoderStatis(TKdvEncStatis &tKdvEncStatis );

	/*开始语音采集*/
	u16    StartAudioCap();

	/*停止语音采集*/
	u16    StopAudioCap(); 

	/*设置语音编码参数*/
	u16    SetAudioEncParam(u8 byMediaMode, u8 byMediaType=MEDIA_TYPE_PCMU); 
                        
	/*获取语音编码参数*/                          
	u16    GetAudioEncParam(u8 &byAudioEncParam, u8 *pbyMediaType = NULL);

	/*开始压缩语音*/
	u16    StartAudioEnc();

	/*停止压缩语音*/
	u16    StopAudioEnc(); 

	/*设置是否编静音码流*/
	u16    SetAudioMute( BOOL32 bMute );    

	/*设置输入编码音量*/	
	u16    SetAudioVolume(u8 byVolume ); 

	/*设置单独音频接口采集音量,每次只能设置一路，多个采集口的话需要调用多次*/
	u16	   SetSingleAudInputVol(u32 dwAudPort, u32 dwVol);

	/*获取采集音量*/
	u16    GetAudioVolume(u8 &byVolume );

	/*设置音频采集端口（包括主麦，即所有音频口）；第二个参数只设置主麦，用于AEC处理，其他接口不作AEC处理*/	
	u16    SetAudInPort(u32 dwAudPort, u32 dwAudMasterMic);  

	/*开始回声抵消*/
	u16    StartAec();

	/*停止回声抵消*/
	u16    StopAec();
  
    /*设置Aecdebug值，范围4-64*/
	u16	   AecDebug(u32 dwDebug);

    /*开始smp增益*/
	u16	   StartAgcSmp(); 
	
	/*停止smp增益*/
	u16	   StopAgcSmp(); 
	
	/*开始sin增益*/
	u16	   StartAgcSin(); 
	
	/*停止sin增益*/	
	u16	   StopAgcSin(); 

	/*设置语音增强等级 dwSpeLevel范围0-3, 0最弱，3最强*/
    u16    SetSpeLevel(u32 dwAudPort, u32 dwSpeLevel);

	/*是否使用语音增强 默认关闭*/
	u16    StartSpe(u32 dwAudPort, BOOL32 bStart);
protected:
private:
	CAudioEncoder *m_pCodec;
};

class CKdvAudDec
{
public:
	CKdvAudDec();
	~CKdvAudDec();
public:
	/************************************************************************/
	/* 函数名:     CreateDecoder                                            */  
	/* 函数参数:                                                            */
	/*             TDecoder *pDecoer     解码器参数                         */
	/*             u32 dwDevVersion      板卡型号                           */
	/* 函数功能:   解码器创建								                                */
	/************************************************************************/
	u16	   CreateDecoder(TDecoder *pDecoer, u32 dwDevVersion=en_T300_Board);
	
	/*获取解码器状态*/
	u16    GetDecoderStatus(TKdvDecStatus &tKdvDecStatus);
	
	/*获取解码器的统计信息*/	
	u16    GetDecoderStatis(TKdvDecStatis &tKdvDecStatis);

	/*设置音频码流数据*/
	u16    SetData(const TFrameHeader& tFrameInfo); 

	/*音频解码参数，AAC_LC和AAC_LD有效*/ 
	u16    SetAudioDecParam(const TAudioDecParam& tAudParam);

	/*设置音频播放端口*/
	u16    SetAudOutPort(u32 dwAudPort);  

	/*开始声音解码*/
	u16    StartDec();	

	/*停止声音解码*/
	u16    StopDec(); 	

	/*设置输出声音音量*/
	u16    SetAudioVolume(u8 byVolume );  	

	/*得到输出声音音量*/	
	u16    GetAudioVolume(u8 &pbyVolume );

	/*设置静音*/
	u16    SetAudioMute(BOOL32 bMute);
		
	/*获取输出音频功率*/
	u32    GetOutputAudioPower();
	
	/*播放铃声*/
	u16   PlayRing(s8* pData = NULL);
	
	/*停止铃声播放*/
	u16   StopRing();

	/*设置均衡器,设置每个频段的调节量，目前使用10个频段(参考取值范围为(-12，+12))
	如可以定义一个数组swEquVal[10] = {0,  6,  -8,  0, 0, //1~5频段
									  0,  0,  0,  0, 12, //6~10频段}   
    dwBufLen指字节数*/
	u16  SetAudEQValue(s16* pszEQValue, u32 dwBufLen);

	/*默认关闭*/
	u16  StartAudEQ(BOOL32 bStart);
protected:
private:
	CAudioDecoder *m_pCodec;
};

//设置画面合成小画面尺寸位置信息

void SetSubPicInfo(u32 dwNetraId, TSmallPicRectInfo tSubPicInfo);
//采集画面合成开关
void StartCapMerge(BOOL32 bMerge);
//语音激励回调
typedef void (*SPEECHACTIVECALLBACK)(u32 dwChID, void* pContext);

//设置语音激励回调
u16 SetSpeechActiveCallBack(SPEECHACTIVECALLBACK fSpeechActiveCB, void* pContext);

//设置语音激励保持时间，单位秒
u16 SetSpeechActiveKeepTime(u32 dwKeepTime);

/*=============================================================================
  函 数 名： SetAudPlayMode
  功    能： 设置音频播放模式
  算法实现： 
  全局变量： 
  参    数： u32 dwPlayMode   EN_PLAY_FULL:3路播放，EN_PLAY_SINGLE:单路播放
             u32 dwChnID      单路播放时通道号，范围0-2，只对EN_PLAY_SINGLE有效
  返 回 值： u16 
=============================================================================*/
u16 SetAudPlayMode(u32 dwPlayMode = EN_PLAY_FULL, u32 dwChnID = 0);

/*=============================================================================
  函 数 名： SetAudSubPlay
  功    能： 设置音频双流本地播放
  算法实现： 
  全局变量： 
  参    数： BOOL32 bPlay        
  返 回 值： u16 
=============================================================================*/
u16 SetAudSubPlay(BOOL32 bPlay);

/*=============================================================================
  函 数 名： SetAudNoisePlay
  功    能： 设置音频白噪声本地播放，用于测试采集和播放的一致性
  算法实现： 
  全局变量： 
  参    数： BOOL32 bPlay     
             u32 dwAudPort
  返 回 值： u16 
=============================================================================*/
u16 SetAudNoisePlay(BOOL32 bPlay, u32 dwAudPort);

//设定当前*.bin,*.out路径，默认/usr/bin
void SetCodecAppDir(s8* szPath);
//注册OSP命令
void RegsterCommands();

//初始化DSP芯片
u16 HardCodecInitDSP(TDSPInit* pInit);
u16 HardCodecDestroyDSP(u32 dwDSPID);
//初始化FPGA
u16 HardCodecDevInit(u32 nDecDevNum, u32 nEncDevNum);
u16 HardCodecDestroy();
u16 HardEnvInitial(u32 dwHWtype);

s32    ScaleVideoCap(u32 dwVidSrcPort,u8 byType, u8 byValue); /* 视频采集调节 */

/*=============================================================================
  函 数 名： GetVGAPhaseClock
  功    能： 获取VGA源相位时钟和分辨率
  算法实现： 
  全局变量： 
  参    数： u32 dwVGAPort
             TVidSrcInfo* ptVGAInfo
             u32& dwPhaseValue
  返 回 值： u16 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2010/6/17     1.0	        王雪宁                   创建
=============================================================================*/
u16 GetVGAPhaseClock(u32 dwVGAPort, TVidSrcInfo* ptVGAInfo, u32& dwPhaseValue);
/*=============================================================================
  函 数 名： SetVGAPhaseClock
  功    能： 设置VGA源相位时钟
  算法实现： 
  全局变量： 
  参    数： u32 dwVGAPort
             u32 dwPhaseValue
  返 回 值： u16 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2010/6/17     1.0	        王雪宁                   创建
=============================================================================*/
u16 SetVGAPhaseClock(u32 dwVGAPort, u32 dwPhaseValue);
/*=============================================================================
  函 数 名： GetVGAFiltStatus
  功    能： 获取VGA源滤波状态
  算法实现： 
  全局变量： 
  参    数： u32 dwVGAPort
             TVidSrcInfo* ptVGAInfo
             u32& dwFiltSet
  返 回 值： u16 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2010/6/17     1.0	        王雪宁                   创建
=============================================================================*/
u16 GetVGAFiltStatus(u32 dwVGAPort, TVidSrcInfo* ptVGAInfo, u32& dwFiltSet);
/*=============================================================================
  函 数 名： SetVGAFiltStatus
  功    能： 设置VGA源滤波
  算法实现： 
  全局变量： 
  参    数： u32 dwVGAPort
             u32 dwFiltSet
  返 回 值： u16 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2010/6/17     1.0	        王雪宁                   创建
=============================================================================*/
u16 SetVGAFiltStatus(u32 dwVGAPort, u32 dwFiltSet);


/*=============================================================================
  函 数 名： GetVidPortInfo
  功    能： 获取视频源端口和制式
  算法实现： 
  全局变量： 
  参    数： u32 dwVidPortType:查询接口，如VIDIO_DVI0等
             TVidPortInfo* ptVidPortInfo:返回实际端口和制式
  返 回 值： void 
  -----------------------------------------------------------------------------
  修改记录：
  日  期		版本		修改人		走读人    修改内容
  2011/4/27     1.0	        王雪宁                   创建
=============================================================================*/
void GetVidPortInfo(u32 dwVidPortType, TVidPortInfo* ptVidPortInfo);

/*函数名： SetMicVol
功    能： 卡农麦克风增益，范围0-50
参    数： u32 dwAudPort
           s32 nVol
返 回 值： API void 
说    明： */
API void SetMicVol(u32 dwAudPort, s32 nVol);

API s32 GetMicVol();

//设置h600摄像头制式
API void SetVidInPortStd(TVidSrcInfo* ptCamInfo);

//获取输出DVI接口上实际的物理接口类型
void GetVidOutPortType(u32 dwDVIId, u32 &dwRealPortType);
//获取输入接口上的制式
void GetVidInPortStd(u32 dwCapPort, TVidSrcInfo& tCamStdInfo);

/*函数名： SetCanonPowerOn
功    能： 卡农麦克风输入接口48v供电开关接口实现
参    数： BOOL32 bEnable=TRUE
返 回 值： 
说    明： */
void SetCanonPowerOn(u32 dwAudPort, BOOL32 bEnable=TRUE);

//获取数字麦插入状态
API BOOL32 GetDigitalMicStatus(u32 dwAudPort);

//获取3.5口插入状态  bIsAudIn = TRUE:采集口  FALSE:播放口
API BOOL32 Get35InOrOutStatus(BOOL32 bIsAudIn);

API BOOL32 GetTRS635Status(u32 dwAudPort);

//获取HDMI音频口状态
API BOOL32 GetAudHdmiStatus(u32 dwAudPort);

/*获取SDI接口类型 SDITYPE_ININ SDITYPE_INOUT*/
API u32 GetHDMtSDIIntType();

/*设置播放分辨率改变消息通知*/
API void SetNtscPalChangeCallBack(CHANGECALLBACK pChangeProc);

//设置芯片死机通知回调
API void SetCpuResetNotify(CpuResetNotify fNotify);
//无视频源或无码流时，超时播放图像:EN_PLAY_LAST/EN_PLAY_BLUE
u16    SetVidPlayPolicy(u32 dwTimeout = 5, u32 dwPlayType = EN_PLAY_LAST);

//是否启用全屏OSD
API void UseFullOSD(BOOL32 bFullOsd = TRUE);
//HDMI口输出HDMI、DVI信号选择
API void HDMIDVISwitch(BOOL32 bHDMI = TRUE);
//设置SD信号输出制式
API void SetSDOutType(u32 dwOutType = VID_OUTTYPE_ORIGIN);	   //参数参加codecwrapperdef_hd
//重启编解码设备
API void RebootCodecDev(u32 dwDevID = CODECDEV_VIDENC);	   //参数参加codecwrapperdef_hd
//判断2批D版或之前版本
API void SetHardWareVer(BOOL32 bBefore2ndD = FALSE);

//追加kdvlog输出回调接口
API void SetKdvLogOutputCallBack(KdvLogOutput fLogoutput);
s32 HardMPUInit(u32 dwHWType_Mode); //指定开发板类型以及工作模式:codecwrapperdef_hd:enBoardType
s32 HardMPUInitDev(u32 nEncTos, u32 nDecTos, u32 nDspNum);
s32 HardMPUDestroy();
//高清终端初始化
s32 HardMTInit(u32 nMode);
s32 HardMTDestroy();
//关闭与恢复视频显示
void SetVideoShow(BOOL32 bShow);
//设置降噪等级 参见 codecwrapperdef_hd.h： NF_MODE_DISABLE etc，仅对第一路有效
void SetNfMode(u32 dwMode);
//设置降噪开关 推荐使用 TRUE
void SetNfEnable(BOOL32 bOpen);
//设置是否启用第二路编码前处理
void SetAuxEncScaleEnable(BOOL32 bEnable);
#endif

#endif  //2013-3-21
