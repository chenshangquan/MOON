/*******************************************************************************
 * 模块名      : TiVidDrv
 * 文件名      : Timer.h
 * 相关文件    : Timer.c
 * 文件实现功能: 定时器驱动接口
 * 作者        : 钮月忠㊣
 * 版本        : V1.0 Copyright(C) 1995-2006 KEDACOM, All rights reserved.
 * -----------------------------------------------------------------------------
 * 修改记录:
 * 日  期       版本        修改人      修改内容
 * 2006/05/21   1.0a        钮月忠      创建	
*******************************************************************************/
#ifndef TIMER_H
#define TIMER_H 1

enum
{
    TIMER_OK = 0,
    TIMER_OPEN_FAILED
    
};

/*==============================================================================
    函数名      : TimerSetup
    功能        ：初始化定时器
    算法实现    ：略
    引用全局变量：无
    输入参数说明：无
	返回值说明  ：TIMER_OK，        成功
                  其他值，          失败
==============================================================================*/
s32 TimerSetup();

/*==============================================================================
    函数名      : TimerRelease
    功能        ：释放定时器
    算法实现    ：略
    引用全局变量：无
    输入参数说明：无
	返回值说明  ：TIMER_OK，        成功
                  其他值，          失败
==============================================================================*/
s32 TimerRelease();

/*==============================================================================
    函数名      : TimerGetRunTime
    功能        ：取得系统初始化之后的运行时间，单位为微秒
    算法实现    ：本函数在某些情况下不能正常工作，但概率极低
    引用全局变量：无
    输入参数说明：无
    返回值说明  ：系统初始化之后的运行时间（微秒）
==============================================================================*/
u64 TimerGetRunTime();

/*==============================================================================
    函数名      : TimerGetRunCount
    功能        ：取得系统初始化之后的运行时间（CYCLE）
    算法实现    ：本函数在某些情况下不能正常工作，但概率极低
    引用全局变量：无
    输入参数说明：无
    返回值说明  ：系统初始化之后的运行时间（CYCLE）
==============================================================================*/
u64 TimerGetRunCycle();

/*==============================================================================
    函数名      : TimerGetRegCount
    功能        ：取得定时器的 COUNT 寄存器的当前值
    算法实现    ：略
    引用全局变量：无
    输入参数说明：无
    返回值说明  ：定时器的 COUNT 寄存器的当前值
==============================================================================*/
u32 TimerGetRegCount();

/*==============================================================================
    函数名      : Delay
    功能        ：延时函数（秒）
    算法实现    ：略
    引用全局变量：无
    输入参数说明：dwTime(I):    延时秒数
    返回值说明  ：无
==============================================================================*/
void Delay(u32 dwTime);

/*==============================================================================
    函数名      : MDelay
    功能        ：延时函数（毫秒）
    算法实现    ：略
    引用全局变量：无
    输入参数说明：dwTime(I):    延时毫秒数
    返回值说明  ：无
==============================================================================*/
void MDelay(u32 dwTime);

/*==============================================================================
    函数名      : UDelay
    功能        ：延时函数（微秒）
    算法实现    ：略
    引用全局变量：无
    输入参数说明：dwTime(I):    延时微秒数
    返回值说明  ：无
==============================================================================*/
void UDelay(u32 dwTime);

#endif /*#ifndef TIMER_H*/
