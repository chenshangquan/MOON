/*****************************************************************************
ģ����      : CWndLogicBase
�ļ���      : wndlogicbase.h
����ļ�    : 
�ļ�ʵ�ֹ���: umstool�߼�����
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/10/30     1.0         ����ӡ      ����
******************************************************************************/
#if !defined(AFX_WNDLOGICBASE_H__F3320A42_A78A_40B7_9B1F_A0FD13BDB0C0__INCLUDED_)
#define AFX_WNDLOGICBASE_H__F3320A42_A78A_40B7_9B1F_A0FD13BDB0C0__INCLUDED_

#pragma warning (disable: 4503)

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CWndLogicBase  
{
public: 
   
	/**	 
	* ����:  ��ʼ��
	* @return   
	* @remarks	 
	*/
	void InitLogic()
	{
        
		RegCBFun();
        RegMsg();
	};


    /**	 
	* ����:  �������״̬������
	* @return   
	* @remarks	 
	*/
    virtual void Clear() = 0;
    

	/**	 
	* ����:  ע���logic�����еĻص�����
	* @return  void
	* @remarks	�ڴ�ע��Ļص�������Ҫ�ǿؼ�����Ӧ�¼�����Ϊ��Ա�ص�����,Ҳ��ע�������Ļص�����
	                    ע��ʱ��Ӧע��ص�������Ӧ���ӵ��������򣺡�����::��������
	*/
	virtual bool RegCBFun(){ return true; }

	 /**	 
	* ����:  ע��ĳ�ص�����
	* @return  void
	* @remarks	 
	*/
	 virtual bool UnRegFunc(){ return true;}

	/**	 
	* ����:  ��ʼ����������,
	* @return  void
	* @remarks	���ڸù��ܱ��������ؼ����Բ���xml����ؼ��󶨣�
	                    ��Ҫ��RegCBFun������ע�ᵽ�ص���������ģ�� 
	*/
	 virtual bool InitWnd(  const IArgs  & arg ) { 
		 Args_WindowTree argTree =* dynamic_cast< Args_WindowTree *>( const_cast<IArgs*>( &arg ));
		 m_pWndTree = argTree.m_piTree; 
		 return true;
	 }

     //��ʾ����ʱ�е�״̬��Ҫ��ʼ��,�˴�ӦΪ���麯����ÿ��logic��Ӧǿ��ʵ�֣��ⲿ��ʾ��Ӧ����ʱͳһ���ô˴���showwindow
     virtual bool ShowWindow( BOOL32 bShow ){ return true; } 
    
     IWndTree * GetWndTree(){ return m_pWndTree; }


    /**	 
	* ����:  ��ʼ������ע����½������ʼ��
	* @return   
	* @remarks	 
	*/
	 virtual void InitLogicData(){ return;}

protected:
   
   /**	 
	* ����:  ע��Ҫ�������Ϣ
	* @return  void
	* @remarks	 ע������Ϣ���ܷ��͵����߼�ģ�飬���򣬽��ղ�������Ϣ
	*/
    virtual void RegMsg(){};

	virtual void UnRegMsg(){};
  
public:
	CWndLogicBase()
    {   
        m_pWndTree = NULL;
	  	RegMsg();  
	}
	
	virtual ~CWndLogicBase(){}

protected:
	IWndTree * m_pWndTree; 

};

#endif // !defined(AFX_WNDLOGICBASE_H__F3320A42_A78A_40B7_9B1F_A0FD13BDB0C0__INCLUDED_)
