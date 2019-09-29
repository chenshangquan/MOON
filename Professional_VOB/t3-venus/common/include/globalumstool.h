/*****************************************************************************
模块名      : globalumstool
文件名      : globalumstool.h
相关文件    : 
文件实现功能: umstool库公共项目导出文件
作者        : 刘德印
版本        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期         版本        修改人      修改内容
2012/10/30     1.0         刘德印      创建
******************************************************************************/
#ifndef GLOBALUMSTOOL_H 
#define GLOBALUMSTOOL_H

//10-common
#include "kdvType.h"		// 公共类型
#include "cmsConst.h"

#include "tptooldef.h"
#include "tpsys.h"

#pragma warning( disable : 4786 )	// 标识符名称超过255字节
#pragma warning( disable : 4067 )
#pragma warning( disable : 4129 )
#pragma warning( disable : 4503 )
#pragma warning( disable : 4800 )


///////////////////////////////导出函数////////////////////////////////////////
#ifdef _TPTOOLPRJ
#define TOOLDLL_API extern "C" __declspec(dllimport)

	namespace UMSTOOLSPACE
	{
		/*=============================================================================
		函 数 名:DllPreTranslateMessage
		功    能:dll中CApp接收消息派发
		参    数:无
		注    意:否则dll无法响应控件注册消息
		返 回 值:无
		-------------------------------------------------------------------------------
		修改纪录:
		日      期  版本    修改人    修改内容
		2012/12/05  1.0     刘德印    创建
		=============================================================================*/
		TOOLDLL_API BOOL /*PASCAL*/ DllPreTranslateMessage(MSG *pMsg);

		/*=============================================================================
		函 数 名:DestoryUmsToolUI
		功    能:初始化创建umstool
		参    数:无
		注    意:无
		返 回 值:无
		-------------------------------------------------------------------------------
		修改纪录:
		日      期  版本    修改人    修改内容
		2012/11/21  1.0     刘德印    创建
		=============================================================================*/
		TOOLDLL_API void DestoryUmsToolUI();

		/*=============================================================================
		函 数 名:CreateUmsToolUI
		功    能:初始化创建umstool
		参    数:BOOL bIsWndCenter:	    [in]        窗口居中显示
				 int xPos:              [in]        窗口初始化X坐标
				 int yPos:              [in]        窗口初始化Y坐标
				 BOOL bIsHide:          [in]        窗口创建后是否隐藏
		注    意:无
		返 回 值:BOOL
		-------------------------------------------------------------------------------
		修改纪录:
		日      期  版本    修改人    修改内容
		2012/11/21  1.0     刘德印    创建
		=============================================================================*/
		TOOLDLL_API BOOL ConnectToUms( LPCTSTR strIpAddr, u16 nPort = UMS_LISTIONPORT_CMS, 
												 LPCTSTR pStrUserName = "admin", LPCTSTR pStrPswd = "admin" );

		/*=============================================================================
		函 数 名:InitUmsTool
		功    能:初始化umstool
		参    数:HWND hNotifyWnd:	    [in]        tptool窗口句柄
		注    意:无
		返 回 值:BOOL
		-------------------------------------------------------------------------------
		修改纪录:
		日      期  版本    修改人    修改内容
		2012/11/21  1.0     刘德印    创建
		=============================================================================*/
		TOOLDLL_API void InitUmsTool( HWND hNotifyWnd );

		/*=============================================================================
		函 数 名:IsInitUmsTool
		功    能:判断是否初始化umstool
		参    数:无
		注    意:无
		返 回 值:BOOL
		-------------------------------------------------------------------------------
		修改纪录:
		日      期  版本    修改人    修改内容
		2012/11/21  1.0     刘德印    创建
		=============================================================================*/
		TOOLDLL_API BOOL IsInitUmsTool();

	}

#else 
#define TOOLDLL_API extern "C" __declspec(dllexport)
#endif


#endif