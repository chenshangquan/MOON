// IValue.h: interface for the IValue class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IVALUE_H__7D0A5DF0_E43B_40EF_8028_E9AFD70E0C24__INCLUDED_)
#define AFX_IVALUE_H__7D0A5DF0_E43B_40EF_8028_E9AFD70E0C24__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "uifactorydef.h"
#include "ItemFactory.h"

// dynamic_cast
namespace AutoUIFactory
{
/*---------------------------------------------------------------------
* ��	����IValue
* ��    �ܣ�ֵ�Ļ��� һ�������propertyһ�𱻶���
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/06/02	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
Interface IValue  
{
public:
	IValue( String strType );
	virtual ~IValue();
	String GetType() const { return m_strType; } 

protected:
	String m_strType;
};


//�б��д���Item�������
class Args_BuildItem : public IArgs
{
public:  
	IItemList* pList;
	BOOL32 bDrag;					//��item�Ƿ�����϶�
	int nKey;						//��item���䵱ǰ����б�����ռ�Ĵ���
	String strTxt;					//item����ʾ���ַ���
	IData* pUserData;				//�û���Ϣ����Ҫ���ڵ��ʱ������click�¼��Ĳ���
	String strClickItemFunc;		//����¼�
	vector<String>* pVctSubItem;		//item����ʾ��ͼ��
	String strImageItem ;			//��Ӧ��imgItem����
	String strTxtItem;				//��Ӧ��txtItem����
	String strLayoutAlgorithm;		//item�Ĳ����㷨
	EmItemStatus emItemStatus;		//item״̬
	
	Args_BuildItem( ):IArgs("BuildItem" )
	{
		pList = NULL;
		bDrag = FALSE;
		nKey =-1;
		strTxt.erase();
		pUserData = 0;
		strClickItemFunc.erase();
		pVctSubItem  = NULL;
		strImageItem ="";
		strTxtItem = "";
		strLayoutAlgorithm= IAlgorithm::strNormalItem ;
		emItemStatus = emItemStatusNormal; 
	}
};

/*---------------------------------------------------------------------
* ��	����Value_ListBase
* ��    �ܣ���Ҫ�����б�����
* ����˵�����ⲿʹ��ʱ��ֻ��̳и��࣬�������Լ�����������ʵ��SetData������ɶ��б�ĸ�ֵ
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2012/12/18	v1.0	    �����		����
----------------------------------------------------------------------*/
//�˵����б�
class Value_ListBase:public IValue
{
public:
	Value_ListBase():IValue("TransparentListData"){} 
	
	virtual bool SetData( IItemList* pList ){return true;} 

	//�б�����������Ĭ���ַ�����������
	virtual bool CompareListData( LPTSTR str1, LPTSTR str2, BOOL bAsc = TRUE );

protected:
	//����agrs�����б�
	bool BuildItem(  Args_BuildItem &agrs );

	
 
};


} // namespace AutoUIFactory end
#endif // !defined(AFX_IVALUE_H__7D0A5DF0_E43B_40EF_8028_E9AFD70E0C24__INCLUDED_)
