// diagTestFrameLogic.h: interface for the DiagTestFrameLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIAGTESTFRAMELOGIC_H__D1C4B9F6_49CD_434B_AB12_DE974E184DE6__INCLUDED_)
#define AFX_DIAGTESTFRAMELOGIC_H__D1C4B9F6_49CD_434B_AB12_DE974E184DE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "logicBase.h"

class CDiagTestFrameLogic : public CLogicBase, public ISingleTon<CDiagTestFrameLogic>  
{
public:
	CDiagTestFrameLogic();
	virtual ~CDiagTestFrameLogic();
	
	//CLogicBase
public:	 	
	/** ����:  ע��ص�����
	*  @param[in] 
	*  @return 
	*  @remarks  �ڶ�ȡxml�ļ�ʱ��,���������ע��ĺ���
	*/
	virtual void RegCBFun();
	/** ����:  ��ע��ص�����
	*  @param[in] 
	*  @return 
	*  @remarks  �����溯���෴,ע��ע��ĺ���
	*/
	virtual void UnRegFunc();
	/** ����:  ��ʼ������
	*  @param[in] 
	*  @return 
	*  @remarks  �ڶ�ȡxml�ļ�ʱ�����,������������ݳ�ʼ������
	*/	
    virtual bool InitWnd( const IArgs & arg ); 
	/** ����:  ������
	*  @param[in] 
	*  @return 
	*  @remarks  �ڴ��ڹرյ�ʱ�����,��մ�������
	*/
    virtual void Clear();

protected:	
	/** ����: ע����Ϣ,��������lib���з���������Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	virtual void RegMsg(); 
		
	/** ����: ��ע����Ϣ,�����溯���෴,ע��ע�����Ϣ
	*  @param[in] 
	*  @return 
	*  @remarks  
	*/	
	virtual void UnRegMsg();
};

#endif // !defined(AFX_DIAGTESTFRAMELOGIC_H__D1C4B9F6_49CD_434B_AB12_DE974E184DE6__INCLUDED_)
