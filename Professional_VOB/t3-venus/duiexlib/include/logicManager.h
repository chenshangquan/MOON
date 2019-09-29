/*****************************************************************************
�ļ�ʵ�ֹ���: ����logic �� ����
�ļ���      : logicManager.h 
����ļ�    : UIDlgBuilder.h DUIDialog.h 
��ע		:  
����        : �����
�汾        : V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/4/18      1.0         �����      ����
******************************************************************************/
#pragma once

#include <map>
#include <vector>
namespace DuiLib { 



typedef std::map</*CStdString*/tString,INotifyUI*> LOGICMAP; 
/*****************************************************************************
* ����:����dlgName�����Ӧ�Ĳ���xml��logic���ӳ���ϵ�� ���Ѿ���������dlgָ��
* @remarks	 
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/4/18       1.0         �����      ����
******************************************************************************/
class  CLogicManager 
{
public: 
	
	UILIB_API static BOOL RegLogic( INotifyUI* pLogic, LPCTSTR szLogicName );

	static INotifyUI* FindLogicByName(  LPCTSTR szLogicName  );

protected: 
	static  LOGICMAP m_logicMap; //�洢����logic
	 
};

 #define REG_LOGIC( logicPtr,logicName ) \
	CLogicManager::RegLogic( logicPtr, logicName  ); 


}
