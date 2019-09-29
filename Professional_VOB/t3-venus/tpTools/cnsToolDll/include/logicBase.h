   
/*****************************************************************************
ģ����      : ���ڵ��߼��������
�ļ���      : CLogicBase.h
����ļ�    : ���д��ڵ��߼�����ģ�鶼Ӧ�̳и���
�ļ�ʵ�ֹ���: ���ڵ��߼�����
����        : �����
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/11/23     1.0         �����      ����
******************************************************************************/

#if !defined(AFX_LOGICBASE_H__A66AA693_6ED0_4B3C_977E_1EC92248A074__INCLUDED_)
#define AFX_LOGICBASE_H__A66AA693_6ED0_4B3C_977E_1EC92248A074__INCLUDED_ 

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning (disable: 4503)

#include "uifactorylib.h" 
#include "templateClass.h" 

class CLogicBase//: public Singleton<CLogicBase>
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
	virtual void RegCBFun(){  }

   /**	 
	* ����:  ע��ĳ�ص�����
	* @return  void
	* @remarks	 
	*/
//	virtual void UnRegFunc( u32 dwMsgID ); 


	 /**	 
	* ����:  ע��ĳ�ص�����
	* @return  void
	* @remarks	 
	*/
	virtual void UnRegFunc(){  }

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
     
	 
	 bool IsAllE164Number( String strText );
	 
	 bool IsValidTPStr( String strText );
    
    
     IWndTree * GetWndTree(){ return m_pWndTree; }

protected:
   
   /**	 
	* ����:  ע��Ҫ�������Ϣ
	* @return  void
	* @remarks	 ע������Ϣ���ܷ��͵����߼�ģ�飬���򣬽��ղ�������Ϣ
	*/
    virtual void RegMsg(){};

	virtual void UnRegMsg(){};
															
	/** ����: ������ݺ����m_vctWndName������ 
	*  @param[in] strCtrlName  �ؼ�����
					bChange    �ؼ��е������Ƿ�仯
	*  @return 
	*  @remarks   �ؼ������ݱ仯,����m_vctWndName���Ƿ��иÿؼ�������
				  ���ݸı�,m_vctWndName����������ӽ�ȥ.����û��,m_vctWndName������ɾ��
	*/	
	void CheckData( String strCtrlName, bool bChange );
	
	/** ����:  ��m_vctWndName�в������ݱ仯�ؼ�������	
	*  @param[in] 
	*  @return 
	*  @remarks   true ��ʾm_vctWndName�Ѵ��иÿؼ�������
				  false ��ʾm_vctWndNameû�иÿؼ�������
	*/	
	bool FindCtrlName( String strWindow );	
												
	/** ����:  ɾ��m_vctWndName������û�б仯�Ŀؼ�����
	*  @param[in] strWndName  �ؼ�����
	*  @return 
	*  @remarks   
	*/	
	void DelVctWndName( String strWindow );
										
	/** ����:  ����m_vctWndName�е�����ȷ�����½ǵı���ȡ����ť�Ƿ����
	*  @param[in] 
	*  @return 
	*  @remarks   
	*/	
	bool UpBtnState();
					  
public:
	CLogicBase()
    {   
        m_pWndTree = NULL;
	  	RegMsg();  
	}
	
	virtual ~CLogicBase(){
		UnRegFunc(); 
	}

protected:
	IWndTree * m_pWndTree; 
    vector<String> m_vctWndName;			//�洢����ؼ����� 
	static String m_strCurWnd;				//��ǰ��ʾ�Ĵ��� 
};



#endif // !defined(AFX_WNDLOGIC_H__A66AA693_6ED0_4B3C_977E_1EC92248A074__INCLUDED_)
