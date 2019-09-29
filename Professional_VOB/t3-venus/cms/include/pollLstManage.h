// pollLstManage.h: interface for the CPollLstManage class.
//��ģ��༭�������
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_POLLLSTMANAGE_H__D111FDD9_A620_4D9D_8595_F924FA1963A6__INCLUDED_)
#define AFX_POLLLSTMANAGE_H__D111FDD9_A620_4D9D_8595_F924FA1963A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "ConftempEdtLogic.h"
class CPollLstManage  
{
public:
    static CPollLstManage*GetPollLstManage();
    virtual ~CPollLstManage();
public: 
    void Init( TCMSConfTemplate* pTemp, CConftempEdtLogic *pLogic );
      
    void SetCurCns( u16 wCnsID ){ m_wCnsID = wCnsID;} 
   
    //�����ѯ�б�
    bool ClearPollLst( const IArgs &args );

    //ɾ���б��cns
    bool DeletePollCns( const IArgs &args );
   
    //��CNS �ö�
    bool SetCnsTop( const IArgs &args );

    //cns �õ�
    bool SetCnsBottom( const IArgs &args );

    //cns����
    bool SetCnsUp( const IArgs &args );

    //cns����
    bool SetCnsDown(const IArgs &args );
   

    //��������ѯ�б��ĳ����Ŀ
    //bool OnClickPollItem(const IArgs &args );
    
   void ShowPollLstManage( BOOL bShow = TRUE );
protected:
    CPollLstManage();
    u16 GetCnsIDFrmItem(const IArgs &args);
private:
    TCMSConfTemplate* m_pTemp;
    u16 m_wCnsID;
    static CPollLstManage* m_stcPThis;
    CConftempEdtLogic *m_pTempEdtLog;
//     static const String  m_strDlgPollManageMenu;
//     static const String  m_strLstPollManage ;
};

#endif // !defined(AFX_POLLLSTMANAGE_H__D111FDD9_A620_4D9D_8595_F924FA1963A6__INCLUDED_)
