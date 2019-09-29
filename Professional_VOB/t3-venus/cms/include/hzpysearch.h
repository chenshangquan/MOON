/*=======================================================================
ģ����      : ����ƴ������
�ļ���      : HZPYSearch.h
����ļ�    : 
�ļ�ʵ�ֹ���: ���ݺ��ֱ���к���ƴ������ĸ�ļ�����ʵ�ֺ��ֻ�ƴ����������
����        : ��ȫ
�汾        : V3.0  Copyright(C) 1997-2011 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2011/06/01  3.0         ��ȫ        ����
=======================================================================*/
#if !defined(AFX_HZPYSEARCH_H__1170A217_233E_4427_87AD_8806710D4DF0__INCLUDED_)
#define AFX_HZPYSEARCH_H__1170A217_233E_4427_87AD_8806710D4DF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <vector>

//֧�ֵ��������������
#define  MAX_FIND_HANZI_LEN      32     
//һ�����ֵ����ƴ����ʾ�����Ƕ����ֺ�ȫƴ��ʾ����Ҫ�ŵ�50����
#define  MAX_FIND_HANZI_PY_CNT   10 //50


//�����ڵ�
class CNode
{
public:
	CNode()
	{
		m_bySymbol = '0';
		m_pNodeNext = NULL;
		m_pMultiNext = NULL;
	}
	
	CNode( char bySymbol, CNode* pNodeNext = NULL, CNode* pMultiNext = NULL )
	{
		m_bySymbol = bySymbol;
		m_pNodeNext = pNodeNext;
		m_pMultiNext = pMultiNext;
	}
	
	char m_bySymbol;      //�ڵ���ű�ʾ
	CNode *m_pNodeNext;   //��һ�ڵ�
	CNode *m_pMultiNext;  //ĳ�����ֵġ�ƴ���������ֽڵ�
};


/*
�ڵ���Լ���
CNode* pNode:  �������Ľӵ�
char *pString: �������Ĵ�
0����ʧ�ܻ�0������0����˳�������ȷ�ĸ���
*/
int Calc( CNode* pNode, char *pString );

/*
�ݹ�ڵ���Լ��������Ϣ
CNode* pNode:  �������Ľӵ�
char *pString: �������Ĵ�
0����ʧ�ܻ�0������0����˳�������ȷ�ĸ���
*/
int OutCalc( CNode* pNode, char *pString );

/*
�ַ���תСд
*/
void strtolower( char *string );

/*
Gb2312�ַ��ж�
*/
BOOL IsGb2312( short wGbCode );

class CHZPYSearch  
{
public:
	CHZPYSearch();
	virtual ~CHZPYSearch();

	/*
	���ܣ�PinYin�����ж�
	������const char *strTextInput: ���жϵĶ���(�û�����PY��)
	      const char* strTextSrc : �ж�Դ�ֶ���(������)
	����ֵ:��Գɹ� TRUE, ���ʧ�� FALSE;
	*/
	BOOL  HZPYMatchList( const char *strTextInput,  const char* strTextSrc );

private:

	/*
	���ܣ�ͨ����Եĺ��֣���ĸ���ִ������������ڵ�����
	��������Ҫ����DestoryNodeList()�������ٴ���
	������const char *strTextParm  �ж�Ŀ��
	*/
	CNode* CreateNodeList( const char *strTextParm );

	/*
	���ܣ��ͷ�CreateNodeList new�����Ľڵ���Դ
	*/
	void   DestoryNodeList();

	/*
	���ܣ�����ƴ����ת��
	����: char arInputChr[ MAX_FIND_HANZI_LEN ] ����ĺ��ִ�
	      char arPYResult[MAX_FIND_HANZI_LEN][MAX_FIND_HANZI_PY_CNT]   ת�����	      
	*/
	bool  ConvertHZPY(  char arInputChr[ MAX_FIND_HANZI_LEN ], char arPYResult[MAX_FIND_HANZI_LEN][MAX_FIND_HANZI_PY_CNT] );

	/*
	���ܣ�����ƴ���ĺ���
	����: buf - ƴ���ͺ��ֵĶ�Ӧ������
	      size- ������Ĵ�С
		  hzstr - ����ĺ��ִ���
		  arPY  - ��������� arPY ���飬���ڱ����뺺�ֶ�Ӧ������ƴ��
    ����: true: ����ת���ɹ�	      
	*/
	bool  SearchHZPY(char *buf, long size, char *hzstr, char arPY[MAX_FIND_HANZI_LEN][MAX_FIND_HANZI_PY_CNT]);

	/*
	���ܣ�����ƴ���ĺ���(�����Ż������������������)
	����: hzstr - ����ĺ��ִ���
		  arPY  - ��������� arPY ���飬���ڱ����뺺�ֶ�Ӧ������ƴ��
    ����: true: ����ת���ɹ�	      
	*/
	bool  SearchHZPY( char *hzstr, char arPY[MAX_FIND_HANZI_LEN][MAX_FIND_HANZI_PY_CNT]);

private:
	std::vector<CNode*>  m_vectNode;

};

#endif // !defined(AFX_HZPYSEARCH_H__1170A217_233E_4427_87AD_8806710D4DF0__INCLUDED_)
