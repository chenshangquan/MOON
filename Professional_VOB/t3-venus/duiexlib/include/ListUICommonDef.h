/*****************************************************************************
ģ����      : ListUICommonDef
�ļ���      : ListUICommonDef.h
����ļ�    : 
�ļ�ʵ�ֹ���: �б��������ļ���������㡢�б��������͵ȣ�
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/5/20     1.0         ����ӡ      ����
******************************************************************************/
#ifndef LISTUICOMMONDEF_H
#define LISTUICOMMONDEF_H

namespace DuiLib
{

#define PRO_PANE_LISTITEM_HIDE			_T("paneListItemHide")
UILIB_API double CalculateDelay(double state);

//ע��Dataӳ��
#define REG_LIST_DATA_MAP( name, datastruct )	\
class UILIB_API name : public IData	\
{	\
public:	\
	name( datastruct &tData ) : IData( L###name ), m_tData( tData ){}	\
	IData* Clone()	\
{	\
	name* pData = new name( m_tData );	\
	pData->SetDataKey( GetDataKey() );	\
	return pData;	\
}	\
	datastruct  m_tData;	\
};


//�б���Ŀ��Ԫ����Ϣ
typedef struct tagTItemNodeUI
{
	tString strPos;
	tString strWidth;
	tString strHeight;
	tString strText;
	tString strFontColor;
	int nFont;
	int nValue;
	tString strImgPath;

public:
	tagTItemNodeUI()
	{
		Clear();
	}

	void Clear()
	{
		memset( this, 0, sizeof(tagTItemNodeUI) );
	}

}TItemNodeUI;


//�б���Ŀ���ݻ���
class UILIB_API IData
{
public:
	IData( std::wstring strType ) : m_strType( strType ), m_dwKey( -1 ){}
	virtual ~IData(){}
	std::wstring GetType() const { return m_strType; } 
	unsigned long GetDataKey() { return m_dwKey; }
	void SetDataKey( unsigned long dwKey ) { m_dwKey = dwKey; }

	virtual IData* Clone() = 0;
protected:
	unsigned long m_dwKey;      //Data��ֵ�����ڲ���Item
	std::wstring m_strType;
};

//�б�������IData
struct NodeData
{
	int nLevel;
	bool bFolder;
	bool bChildVisible;
	bool bHasChild;
	const IData* pData;
	CListContainerElementUI* pListElement;

public:
	NodeData()
	{
		memset( this, 0, sizeof(NodeData) );
	}
};

class UILIB_API Node
{
public:
	Node();
	explicit Node(NodeData tNodeData);
	Node(NodeData tNodeData, Node* pParent);
	~Node();
	NodeData& GetData();
	int GetChildNum() const;
	Node* GetChild(int nIndex);
	Node* GetParent();
	bool IsFolder() const;
	bool IsHasChild() const;
	void AddChild(Node* child);
	void RemoveChild(Node* child);
	Node* GetLastChild();

	//������
	const IData* GetUserData();
	void SetUserData( IData* pData );

private:
	void SetParent(Node* pParent);

private:
	typedef std::vector <Node*>	Child;

	Child	m_child;
	Node*		m_pNode;
	NodeData    m_nodeData;
};

//////////////////////////�б�Data_Struct////////////////////////////////
//

/////////////////////////////////////////////////////////////////////////
//                     �ļ��б�
//
//�ļ��б�ṹ��
struct TFileListItemInfo
{
	bool bFolder;
	tString strKey;
	tString strFileName;
	tString strPath;

public:
	TFileListItemInfo()
	{
		memset( this, 0, sizeof(TFileListItemInfo) );
	}
};
REG_LIST_DATA_MAP( Data_FileList, TFileListItemInfo )				//�ļ��б�ITEM����


/////////////////////////////////////////////////////////////////////////
//                     �����б�
//
//�����б�ṹ��
struct TConfListItemInfo
{
	tString strKey;
	tString strConfID;
	tString strConfName;
	int     nProgress;

public:
	TConfListItemInfo()
	{
		memset( this, 0, sizeof(TConfListItemInfo) );
	}
};
REG_LIST_DATA_MAP( Data_ConfList, TConfListItemInfo )				//�����б�ITEM����

/////////////////////////////////////////////////////////////////////////
//                     ��̬�б�
//
//��̬�б�ṹ��
struct TDynamicListItemInfo
{
	tString strKey;
	tString strID;
	tString strName;
	int     nProgress;

public:
	TDynamicListItemInfo()
	{
		memset( this, 0, sizeof(TDynamicListItemInfo) );
	}
};
REG_LIST_DATA_MAP( Data_DynamicList, TDynamicListItemInfo )			//��̬�б�ITEM����

/////////////////////////////////////////////////////////////////////////
//                     �����б�
//
//�����б�ṹ��
struct TBoardListItemInfo
{
	tString strKey;
	tString strID;
	tString strName;

public:
	TBoardListItemInfo()
	{
		memset( this, 0, sizeof(TBoardListItemInfo) );
	}
};
REG_LIST_DATA_MAP( Data_BoardList, TBoardListItemInfo )				//�����б�ITEM����

/////////////////////////////////////////////////////////////////////////
//                     ����ǽԤ���б�
//
//����ǽԤ���б�ṹ��
struct TTvwStyleListItemInfo
{
	tString strKey;
	tString strID;
	tString strName;

public:
	TTvwStyleListItemInfo()
	{
		memset( this, 0, sizeof(TTvwStyleListItemInfo) );
	}
};
REG_LIST_DATA_MAP( Data_TvwStyleList, TTvwStyleListItemInfo )		//����ǽԤ���б�ITEM����

/////////////////////////////////////////////////////////////////////////
//                     ��ַ���б�
//
//��ַ���б�ṹ��
struct TAddrListItemInfo
{
	tString strKey;
	//tString strAddrID;
	tString strAddrName;
	tString strAddrNum;
public:
	TAddrListItemInfo()
	{
		memset( this, 0, sizeof(TAddrListItemInfo) );
	}
};
REG_LIST_DATA_MAP( Data_AddrList, TAddrListItemInfo )				//��ַ���б�ITEM����

/////////////////////////////////////////////////////////////////////////
//                     ���½���������
//
//���������ݽṹ��
struct TProgressInfo
{
	int nIndex;
	int nValue;

public:
	TProgressInfo()
	{
		memset( this, 0, sizeof(TProgressInfo) );
	}
};
REG_LIST_DATA_MAP( Data_ProgressInfo, TProgressInfo )				//��ַ���б�ITEM����


} // DuiLib

#endif // LISTUICOMMONDEF_H