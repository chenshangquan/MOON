/*****************************************************************************
ģ����      : �б��������ͼ��б��������÷�����ʵ��
�ļ���      : listAssist.h
����ļ�    : ��������ʹ�õ������б�����ݶ�Ӧͳһ�ڴ��ļ�����
�ļ�ʵ�ֹ���: �б��������ݲ����Ѿ����ģ�UI��ֻ��Ҫ����̳���Value_ListBase���࣬
              ��ʵ��SetData��������б����ݵ����ã�����������������ע����������õ�ģ��
����        : �����
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/12/17     1.0         �����      ����
******************************************************************************/
#if !defined(AFX_LISTASSIST_H__01F8A625_C9CB_49C2_BB33_C02D30F86D1A__INCLUDED_)
#define AFX_LISTASSIST_H__01F8A625_C9CB_49C2_BB33_C02D30F86D1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
 
#include "PropertyHelp.h"
#include "uiDataType.h"

/*---------------------------------------------------------------------
* ��	Data_ItemMenu
* ��    �ܣ�
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2012/12/19	v1.0		�����		����
----------------------------------------------------------------------*/ 
class Data_ItemMenu : public IData
{
public:
    Data_ItemMenu( TMenuItem t ) : IData( "MenuItem" ), m_tMenuItem( t ){}
    IData* Clone()
    {
        Data_ItemMenu* pData = new Data_ItemMenu( m_tMenuItem );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
    TMenuItem  m_tMenuItem;
};
 
/*---------------------------------------------------------------------
* ��	Value_ItemMenu
* ��    �ܣ����ܱ�ǩҳ�б���������
* ����˵�����������ڱ�ǩҳ�б���ʾʱ���valueֵ
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2012/12/19	v1.0		�����		����
----------------------------------------------------------------------*/
class Value_ItemMenu : public Value_ListBase
{
public:
	Value_ItemMenu( vector<TMenuItem>* pArray, String strClickItemFunc = IBaseItem::strDefaultFunc ,
        vector<String> * pVctSubItem = NULL, String strAlgroithm = IAlgorithm::strHori,
        BOOL32 bDrag = FALSE ): Value_ListBase(  ),
		m_pMenuList( pArray ), 
	//	m_strClickItemFunc( strClickItemFunc ),
    //    m_pVctSubItem( pVctSubItem ), 
		m_strAlgroithm(strAlgroithm),
		m_bDrag(bDrag){} 
 
	vector<TMenuItem>* m_pMenuList;
//	vector<String> * m_pVctSubItem;         //����Ŀ��Ӧ��xml������
    string m_strImgItemType;
	string m_strTxtItemType;
//	String m_strClickItemFunc;		    	// ��Ŀ����ص�����   
    String m_strAlgroithm;                  //�����㷨
	BOOL32 m_bDrag;                         //�Ƿ�����϶�
	
	//ʹ��Value_ItemMenu���б� �������� ��ʵ��
	virtual bool SetData( IItemList* pList );
 
};

/*---------------------------------------------------------------------
* ��	Value_ItemTPad
* ��    �ܣ�TPad�б���������
* ����˵������������TPad�б���ʾʱ���valueֵ
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2012/12/19	v1.0		������		����
----------------------------------------------------------------------*/
class Value_ItemTPad : public Value_ListBase
{
public:
	Value_ItemTPad( TTPTPadList* ptTPadList, String strAlgroithm = IAlgorithm::strVert,
        BOOL32 bDrag = FALSE ): Value_ListBase(),
		m_ptTPadList( ptTPadList ), 
		m_strAlgroithm(strAlgroithm),
		m_bDrag(bDrag){}   
	
	TTPTPadList*      m_ptTPadList;
    String m_strAlgroithm;                  //�����㷨
	BOOL32 m_bDrag;                         //�Ƿ�����϶�
	virtual bool SetData( IItemList* pList );
};


//�п���Ϣ�еƹ��״̬�б�
class Value_ItemLight : public Value_ListBase
{
public:
	Value_ItemLight( TCentreSchCfg* ptSchCfg, String strAlgroithm = IAlgorithm::strVert,
        BOOL32 bDrag = FALSE ): Value_ListBase(),
		m_ptSchCfg( ptSchCfg ), 
		m_strAlgroithm(strAlgroithm),
		m_bDrag(bDrag){}   
	
	TCentreSchCfg* m_ptSchCfg;
    String m_strAlgroithm;                  //�����㷨
	BOOL32 m_bDrag;                         //�Ƿ�����϶�
	virtual bool SetData( IItemList* pList );
};

//��ϲ��Խ���п�ũ��˷��б�
class Value_ItemCOMMON : public Value_ListBase
{
public:
	Value_ItemCOMMON( TTPAudioDiagInfo* ptAudioDiagInfo, String strAlgroithm = IAlgorithm::strVert,
        BOOL32 bDrag = FALSE ): Value_ListBase(),
		m_ptAudioDiagInfo( ptAudioDiagInfo ), 
		m_strAlgroithm(strAlgroithm),
		m_bDrag(bDrag){}   
	
	TTPAudioDiagInfo*      m_ptAudioDiagInfo;
    String m_strAlgroithm;                  //�����㷨
	BOOL32 m_bDrag;                         //�Ƿ�����϶�
	virtual bool SetData( IItemList* pList );
	String CommonToStr( int u );			//�����������ֵת��Ϊstring����
};


// class CListAssist 
// {
// public: 
//     static bool SetData( IItemList* pList, const IValue* pValue );
// 	static bool SetData( IItemList* pList,  const Value_ListItem* pValue );
//   
// 
// 	CListAssist();
// 	virtual ~CListAssist();
// private:
//     static bool MakeItem ( Args_MakeItem &agrs )  ;
// };
// 	
// private:
// 	CString m_strValTypeFuncMenu;//�����б�
// 	
// };



//�����б� 
class Value_ItemNetMng : public Value_ListBase
{
public:
	Value_ItemNetMng( vector<TTPNMServerCfg>* pVecNMServerCfgLst, String strAlgroithm = IAlgorithm::strVert, BOOL32 bDrag = FALSE ) 
		: Value_ListBase(),
		m_pVecNMServerCfgLst( pVecNMServerCfgLst ), 
		m_strAlgroithm(strAlgroithm),
		m_bDrag(bDrag){}   
	
	vector<TTPNMServerCfg> *m_pVecNMServerCfgLst; 
    String m_strAlgroithm;                  //�����㷨
	BOOL32 m_bDrag;                         //�Ƿ�����϶�
	virtual bool SetData( IItemList* pList );
};

class Data_NetMng : public IData
{
public:
    Data_NetMng( TTPNMServerCfg &tTPNMServerCfg ) : IData( "NetMngInfo" ), m_tTPNMServerCfg( tTPNMServerCfg ){}
    IData* Clone()
    {
        Data_NetMng* pData = new Data_NetMng( m_tTPNMServerCfg );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
	
    TTPNMServerCfg m_tTPNMServerCfg;
};

#endif // !defined(AFX_LISTASSIST_H__01F8A625_C9CB_49C2_BB33_C02D30F86D1A__INCLUDED_)
