// titleBarLogic.h: interface for the CTitleBarLogic class.
 /*****************************************************************************
 ģ����      : CMS����̨
 �ļ���      : titleBarLogic.h
 ����ļ�    : 
 �ļ�ʵ�ֹ���: �������ϵı���
 ˵��       �� ������ʵʱ������ʱ�� �ͱ���cns�ľ��� ���� ˫�� ״̬
 ����        : �����
 �汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
 -----------------------------------------------------------------------------
 �޸ļ�¼:
 ��  ��         �汾        �޸���      �޸�����
 2011/5/24  1.0          �����      ����
******************************************************************************/

#if !defined(AFX_TITLEBARLOGIC_H__05CDA343_9A18_4A1D_9F89_D9F3349926D9__INCLUDED_)
#define AFX_TITLEBARLOGIC_H__05CDA343_9A18_4A1D_9F89_D9F3349926D9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CTitleBarLogic : public CWndLogicBase  
{
public: 
    static CTitleBarLogic* GetLogicPtr(); 
    CTitleBarLogic();
    virtual ~CTitleBarLogic(); 
    
public:  
    
    virtual bool RegCBFun();
    
    virtual bool UnRegFunc( );
    
    virtual bool InitWnd( const IArgs & arg );
    
    virtual bool ShowWindow( BOOL32 bShow );
    /**	 
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear();

    bool BtnSaveToFileClick( const IArgs & arg );
    
    void UpdateSysTime();//����ϵͳʱ��
    void UpdateConfTime();//���»������ʱ��
protected:  
    
    HRESULT OnCnsInfoNotify( WPARAM wparam, LPARAM lparam );
    HRESULT OnVoiceNotify( WPARAM wparam, LPARAM lparam); 
    HRESULT OnDualNotify( WPARAM wparam, LPARAM lparam); 

    HRESULT OnConfStateNotify( WPARAM wparam, LPARAM lparam); 
    HRESULT OnChangeSpeakerNotify( WPARAM wparam, LPARAM lparam); 
    
    HRESULT OnModifySysTimeNotify( WPARAM wparam, LPARAM lparam); 
    
    void  AdjustTime( s64 &time );
protected: 
    virtual void RegMsg(); 
    virtual void UnRegMsg();
    
private:
    void Init();
    void UnInit();

private:
    
    static CTitleBarLogic *m_pLogic;
    static const String m_stcStrCnsName;
    static const String m_stcStrMuteIcon;  //����ͼ��
    static const String m_stcStrQuietIcon; //����ͼ��
    static const String m_stcStrDualIcon;  //˫��ͼ��
    static const String m_stcStrSpeakerIcon;//������ͼ��

    static const String m_stcStrDate;      //ϵͳ����
    static const String m_stcStrTime;      //ϵͳʱ�� 

    static const String m_stcStrConfTime;  //�������ʱ��


    s64   m_dwConfStartTime;                //����Ŀ�ʼʱ��   
    
    s16   m_nElapse;                       //timer���
    TCMSConf m_tCurConf;
    CTimeSpan  m_tmConfDuration;                   //��ǰ�������ʱ��
};

#endif // !defined(AFX_TITLEBARLOGIC_H__05CDA343_9A18_4A1D_9F89_D9F3349926D9__INCLUDED_)
