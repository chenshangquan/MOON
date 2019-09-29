
#ifndef ALGORITHM_HEAD_H
#define ALGORITHM_HEAD_H
#include "uiexBaseData.h"
#include "iAlgorithm.h" 


class CAlgorithmFactory
{
public:
	static IAlgorithm* GetAlgorithm( String alg );
	static bool AddAlgorithm( String strName, IAlgorithm* pAlgorithm );
protected:
	typedef map< String, IAlgorithm* > AlgorithmMap;
	static AlgorithmMap m_mapAlgorithms;
};

#ifndef REG_ALGORITHM
#define REG_ALGORITHM( name, AlgClass ) \
CAlgorithmFactory::AddAlgorithm( name, new AlgClass );
#endif


typedef IItem< IBaseItem, int > IItemList;

class Args_ItemList : public IArgs
{
	//typedef IItem< IBaseItem, int > IItemList;
public:
	Args_ItemList( IItemList* pList ) : IArgs( "ItemList" ) , m_pList( pList ) {}
	
	IItemList* m_pList;
};

class CLayoutAlgorithm_Vert : public IAlgorithm
{
public:
	static /*const*/ int nXSpace;
	static const int nYSpace;

	bool Transition( IArgs* pArgs );
	bool TransitionByIndex( int nIndex, IArgs* pArgs );
};

class CLayoutAlgorithm_VertNoSplit : public IAlgorithm
{
public:
	static const int nXSpace;
	static const int nYSpace;
	
	bool Transition( IArgs* pArgs );
	bool TransitionByIndex( int nIndex, IArgs* pArgs );
};

class CLayoutAlgorithm_Hori : public IAlgorithm
{
public:
	static const int nXSpace;
	static const int nYSpace;

	bool Transition( IArgs* pArgs );
};

class CLayoutAlgorithm_NormalItem : public IAlgorithm
{
public:
	bool Transition( IArgs* pArgs );
	bool TransitionByIndex( int nIndex, IArgs* pArgs );
};

class CLayoutAlgorithm_HoriConfLst : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

class CLayoutAlgorithm_AddrGroupItem : public IAlgorithm
{
public:
	bool Transition( IArgs* pArgs );
};

class CLayoutAlgorithm_TextOnly : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

class CLayoutAlgorithm_DoubleColumn : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

//TPad�������б�
class CLayoutAlgorithm_TPadMainMenu : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

//����λ�ڵײ�
class CLayoutAlgorithm_TextBottom : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

//Wifi�б���Ŀ
class CLayoutAlgorithm_WifiItem : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

//�����б�
class CLayoutAlgorithm_BoardView : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

//��������
class CLayoutAlgorithm_BoardItem : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

class CSortAlgorithm_Char : public IAlgorithm
{
public:
	bool Transition( IArgs* pArgs );
};

//TPad�б�
class CLayoutAlgorithm_TPadIPList : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

//�����б�
class CLayoutAlgorithm_NetMngList : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

/*---------------------------------------------------------------------
* ��	CLayoutAlgorithm_MultiColumn
* ��    �ܣ�����ͨ���㷨
* ����˵�������������б���ʾ
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2013/1/16   	v1.0		Ф��Ȼ		  ����
----------------------------------------------------------------------*/
class CLayoutAlgorithm_MultiColumn : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

//Combox�㷨
class CLayoutAlgorithm_ComboxItem : public IAlgorithm
{
public:
	bool Transition( IArgs* pArgs );
};

//�ļ������б�
class CLayoutAlgorithm_FileManagerItem : public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};

//Ԥ��λ�б�
class CLayoutAlgorithm_PreTextBottom :  public IAlgorithm
{
public:
    bool Transition( IArgs* pArgs );
};




#endif
