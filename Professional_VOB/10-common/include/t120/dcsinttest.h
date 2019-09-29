/*****************************************************************************
模块名      : DCS-DcServerIntTest
文件名      : DcServerIntTest.h
相关文件    : DcServerIntTest.cpp
文件实现功能: DCServer集成测试查询库
作者		: 赖齐
版本        : V4.0
-----------------------------------------------------------------------------
修改记录:
日  期      版本     修改人      修改内容
2005/09/21  0.1      赖齐        从V3.6移植
******************************************************************************/

#if !defined DCSERVERINTTEST_H
#define DCSERVERINTTEST_H

#include "dcstrc.h"

class CDCServerIntTest
{
private:
    DWORD m_dwDCSNodeId;

public:
    CDCServerIntTest(); 
	
    virtual ~CDCServerIntTest();

/******************************************************    
    参数:	  dwDCSIp －－ DCS的Ip地址（主机序）
              wPort －－ DCS的Osp端口（主机序）
    返回值:   无
    用途:	  与DCS建立连接
*******************************************************/
    bool ConnectToDCS( u32 dwDCSIp=0, u16 wPort=2090 );

/******************************************************    
    参数:	  无
    返回值:   无
    用途:	  断链
*******************************************************/
    void Disconnect();

/****************************************************** 
    参数:	  无
    返回值:   true - 命令下发成功
              false - 命令下发失败
    用途:	  下发清空用户名册命令
*******************************************************/
    bool ClearDCUserBookCmd();

/******************************************************
    参数:	  无
    返回值:   true - 命令下发成功
              false - 命令下发失败
              用途:	  下发清空地址簿中所有终端的命令
*******************************************************/
    bool ClearMtEntryBookCmd();

/******************************************************
    参数:	  无
    返回值:   true - 命令下发成功
              false - 命令下发失败
    用途:	  下发清空地址簿中所有模板的命令
*******************************************************/
    bool ClearConftEntryBookCmd();
    
/******************************************************
    参数:	  无
    返回值:   true - 命令下发成功
              false - 命令下发失败
    用途:	  下发结束所有会议的命令
*******************************************************/
    bool TermAllConfCmd();
    
/******************************************************
    参数:	  tDCUser--用户信息
    返回值:   true - 用户存在
              false - 用户不存在
    用途:	  查询某个用户是否存在并且信息是否正确
*******************************************************/
    bool IsDCUserExist( TDCUser tDCUser );

/******************************************************
    参数:	  tMt--终端信息
    返回值:   true - 终端存在
              false - 终端不存在
    用途:	  查询某个终端是否存在
*******************************************************/
    bool IsMtEntryExist( TDCBaseMt tMt );

/******************************************************
    参数:	  tTemplate--模板信息
    返回值:   true - 模板存在
              false - 模板不存在
    用途:	  查询某个模板是否存在
*******************************************************/
    bool IsConfTmplExist( TDataConfTemplate tTemplate );

/******************************************************
    参数:	  tConfInfo--会议信息
    返回值:   true - 会议存在
              false - 会议不存在
    用途:	  查询某个会议是否存在
*******************************************************/
    bool IsConfExist( TDataConfFullInfo tConfInfo );
    
/******************************************************
    参数:	  tConfInfo--会议信息
              tMt－－终端信息
    返回值:   true - 终端在会议中
              false - 终端不在会议中
    用途:	  查询某个终端是否在会议中
*******************************************************/
    bool IsMtInConf( TDataConfFullInfo tConfInfo, TDCMt tMt );

/******************************************************
    参数:	  tConfInfo--会议信息
              tMt－－终端信息
    返回值:   true - 终端上线
              false - 终端没上线
    用途:	  查询某个终端是否上线
*******************************************************/
    bool IsMtOnline( TDataConfFullInfo tConfInfo, TDCMt tMt );

/******************************************************
    参数:	  tConfInfo--会议信息
              tChairman－－输出参数，主席信息
    返回值:   true - 会议有主席
              false - 会议没主席
    用途:	  查询会议是否有主席
*******************************************************/
    bool IsChairmanExist( TDataConfFullInfo tConfInfo, TDCMt& tChairman );

/******************************************************
    参数:	  无
    返回值:   true - 命令执行成功
              false - 命令执行失败
    用途:	  查询命令结果
*******************************************************/
    bool QueryCmdRet();

/******************************************************
    参数:	  tDCUser －－ 得到的DCUser信息，必须指定用户名字段
    返回值:   true - 用户存在
              false - 消息发送失败 
    用途:	  查询用户信息
*******************************************************/
    bool QueryDCUser( TDCUser& tDCUser );

/******************************************************
    参数:	  nSum －－ 返回的总数
    返回值:   true - 消息发送成功
              false - 消息发送失败 
    用途:	  查询用户总数
*******************************************************/	
    bool QueryDCUserSum( u32& dwSum );

/******************************************************
    参数:	  nIndex －－ 从0开始的索引
              tDCUser －－返回值
    返回值:   true - 消息发送成功
              false - 消息发送失败 
    用途:	  通过索引查询用户信息
*******************************************************/	
    bool QueryDCUserByIndex( u32 dwIndex, TDCUser& tDCUser );

/******************************************************
    参数:	  tDCBaseMt －－ 得到的终端信息，必须指定Alias字段
    返回值:   true - 终端存在
              false - 消息发送失败
    用途:	  查询终端信息
*******************************************************/
    bool QueryTDCBaseMt( TDCBaseMt& tDCBaseMt  );

/******************************************************
    参数:	  nSum －－ 返回的总数
    返回值:   true - 消息发送成功
              false - 消息发送失败 
    用途:	  查询地址簿中的终端总数
*******************************************************/	
    bool QueryTDCBaseMtSum( u32& dwSum );

/******************************************************
    参数:	  nIndex －－ 从0开始的索引
              tMt －－返回值
    返回值:   true - 消息发送成功
              false - 消息发送失败 
    用途:	  通过索引查询地址簿中的终端信息
*******************************************************/	
    bool QueryTDCBaseMtByIndex( u32 dwIndex, TDCBaseMt& tMt );

/******************************************************
    参数:	  tDCTmpl －－ 得到的会议模板信息，必须指定模板Id字段
    返回值:   true - 会议模板存在
              false - 消息发送失败
    用途:	  查询会议模板信息
*******************************************************/
    bool QueryConfTmpl( TDataConfTemplate& tDCTmpl );

/******************************************************
    参数:	  nSum －－ 返回的总数
    返回值:   true - 消息发送成功
              false - 消息发送失败 
    用途:	  查询地址簿中的模板总数
*******************************************************/	
    bool QueryConfTmplSum( u32& dwSum );

/******************************************************
    参数:	  nIndex －－ 从0开始的索引
              tTmpl －－返回值
    返回值:   true - 消息发送成功
              false - 消息发送失败 
    用途:	  通过索引查询地址簿中的模板信息
*******************************************************/	
    bool QueryConfTmplByIndex( u32 dwIndex, TDataConfTemplate& tTmpl );

/******************************************************
    参数:	  tDCFullInfo －－ 得到的会议信息，必须指定会议名字段
    返回值:   true - 会议存在
              false - 消息发送失败
    用途:	  查询会议信息
*******************************************************/
    bool QueryConfInfo( TDataConfFullInfo& tDCFullInfo );

/******************************************************
    参数:	  nSum －－ 返回的总数
    返回值:   true - 消息发送成功
              false - 消息发送失败 
    用途:	  查询正在举行的会议总数
*******************************************************/	
    bool QueryConfSum( u32& dwSum );

/******************************************************
    参数:	  nIndex －－ 从0开始的索引
              tConfInfo －－返回值
    返回值:   true - 消息发送成功
              false - 消息发送失败 
    用途:	  通过索引查询正在举行的会议信息
*******************************************************/	
    bool QueryConfByIndex( u32 dwIndex, TDataConfFullInfo& tConfInfo );


/******************************************************
    参数:	  dwSum －－ 当前DCS的处理中的事件个数
    返回值:   true - 消息发送成功
              false - 消息发送失败 
    用途:	  查询会议当前处理中的事件个数
*******************************************************/
    bool GetTransactionSum( u32& dwSum );
};

#endif