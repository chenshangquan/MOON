/*****************************************************************************
ģ����      : SNMP����ģ��
�ļ���      : snmpadp_nodes.h
����ļ�    : snmpadp_nodes.cpp
�ļ�ʵ�ֹ���: 
����        : ��  ��
�汾        : V4.0  Copyright(C) 2005-2006 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2005/08/18  4.0         ��  ��      ����
******************************************************************************/ 
#ifndef _SNMPADP_NODES_H_
#define _SNMPADP_NODES_H_

#if ( _SNMPADP_MANAGER_ || WIN32 )
#include <snmp_pp/snmp_pp.h>
#include <snmp_pp/notifyqueue.h>
#endif

#ifdef _VXWORKS_
#include <snmp.h>
#endif

//#if defined(_LINUX_) 
#if (_SNMPADP_AGENT_ && _LINUX_)
#include "net-snmp-agent-includes.h"
#endif

class CNodeCollection
{
public:
    CNodeCollection();
    virtual ~CNodeCollection();

    u16  AddNodeValue(u32 dwNodeName);

    u16  AddNodeValue(u32 dwNodeName, void * pBuf, u16 wBufLen);

    u16  GetNodeValue(u32 dwNodeName, void * pBuf, u16 wBufLen); //u16 wBufLen����Ӧ����Ƴɷ��ز���
    
    u16  GetNodeValue(u32 dwNodeName, void * pBuf, u16 wBufLen, s32 nIndex);

    u16  GetNodeNum(void);

    u16  SetTrapType(u16 wTrapType);
    
    u16  GetTrapType(void);
    
    u16  Clear(void);

#ifdef _SNMPADP_MANAGER_
	void GetPduTimeStamp(TimeTicks &ticks);
#endif

#if( _SNMPADP_MANAGER_ || WIN32 )	
    Pdu & GetPduFromNodes(void);
    u16   SetPduToNodes(Pdu & pdu);
#endif
    
#ifdef _VXWORKS_
    SNMP_PKT_T * GetPduFromNodes(void);
#endif

#if( _LINUX_ && _SNMPADP_AGENT_ )
    netsnmp_variable_list * GetVariableFromNodes(void);
    u16  SetVariableToNodes(netsnmp_variable_list * ptValList);
    void FreeVariableList(void);
#endif 


protected:

#if( _SNMPADP_MANAGER_ || WIN32 )
    Pdu  m_pdu;
#endif

#ifdef _VXWORKS_    
    SNMP_PKT_T m_tPkt;
#endif

#if( _LINUX_ && _SNMPADP_AGENT_ )
    u16  m_wTrapType;
    netsnmp_variable_list * m_ptValList;
#endif
    
};

#endif  //!_SNMPADP_NODES_H_
