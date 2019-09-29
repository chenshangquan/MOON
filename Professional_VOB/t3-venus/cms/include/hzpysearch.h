/*=======================================================================
模块名      : 汉字拼音检索
文件名      : HZPYSearch.h
相关文件    : 
文件实现功能: 根据汉字表进行汉字拼音首字母的检索，实现汉字或拼音检索功能
作者        : 过全
版本        : V3.0  Copyright(C) 1997-2011 KDC, All rights reserved.
-----------------------------------------------------------------------------
修改记录:
日  期      版本        修改人      修改内容
2011/06/01  3.0         过全        创建
=======================================================================*/
#if !defined(AFX_HZPYSEARCH_H__1170A217_233E_4427_87AD_8806710D4DF0__INCLUDED_)
#define AFX_HZPYSEARCH_H__1170A217_233E_4427_87AD_8806710D4DF0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <vector>

//支持的最多搜索字数量
#define  MAX_FIND_HANZI_LEN      32     
//一个汉字的最多拼音标示，考虑多音字和全拼显示，需要放到50左右
#define  MAX_FIND_HANZI_PY_CNT   10 //50


//检索节点
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
	
	char m_bySymbol;      //节点符号表示
	CNode *m_pNodeNext;   //下一节点
	CNode *m_pMultiNext;  //某个汉字的、拼音、多音字节点
};


/*
节点配对计算
CNode* pNode:  待分析的接点
char *pString: 待分析的串
0返回失败或0个，非0返回顺序配对正确的个数
*/
int Calc( CNode* pNode, char *pString );

/*
递归节点配对计算配对信息
CNode* pNode:  待分析的接点
char *pString: 待分析的串
0返回失败或0个，非0返回顺序配对正确的个数
*/
int OutCalc( CNode* pNode, char *pString );

/*
字符串转小写
*/
void strtolower( char *string );

/*
Gb2312字符判断
*/
BOOL IsGb2312( short wGbCode );

class CHZPYSearch  
{
public:
	CHZPYSearch();
	virtual ~CHZPYSearch();

	/*
	功能：PinYin检索判断
	参数：const char *strTextInput: 待判断的对象串(用户输入PY项)
	      const char* strTextSrc : 判断源字对象串(汉字项)
	返回值:配对成功 TRUE, 配对失败 FALSE;
	*/
	BOOL  HZPYMatchList( const char *strTextInput,  const char* strTextSrc );

private:

	/*
	功能：通过配对的汉字，字母数字串，创建分析节点链表，
	创建后需要调用DestoryNodeList()进行销毁处理
	参数：const char *strTextParm  判断目标
	*/
	CNode* CreateNodeList( const char *strTextParm );

	/*
	功能：释放CreateNodeList new出来的节点资源
	*/
	void   DestoryNodeList();

	/*
	功能：汉字拼音码转换
	参数: char arInputChr[ MAX_FIND_HANZI_LEN ] 输入的汉字串
	      char arPYResult[MAX_FIND_HANZI_LEN][MAX_FIND_HANZI_PY_CNT]   转换结果	      
	*/
	bool  ConvertHZPY(  char arInputChr[ MAX_FIND_HANZI_LEN ], char arPYResult[MAX_FIND_HANZI_LEN][MAX_FIND_HANZI_PY_CNT] );

	/*
	功能：查找拼音的函数
	参数: buf - 拼音和汉字的对应表数组
	      size- 此数组的大小
		  hzstr - 输入的汉字串，
		  arPY  - 结果保存在 arPY 数组，用于保存与汉字对应的所有拼音
    参数: true: 查找转换成功	      
	*/
	bool  SearchHZPY(char *buf, long size, char *hzstr, char arPY[MAX_FIND_HANZI_LEN][MAX_FIND_HANZI_PY_CNT]);

	/*
	功能：查找拼音的函数(性能优化，解决大数据量检索)
	参数: hzstr - 输入的汉字串，
		  arPY  - 结果保存在 arPY 数组，用于保存与汉字对应的所有拼音
    参数: true: 查找转换成功	      
	*/
	bool  SearchHZPY( char *hzstr, char arPY[MAX_FIND_HANZI_LEN][MAX_FIND_HANZI_PY_CNT]);

private:
	std::vector<CNode*>  m_vectNode;

};

#endif // !defined(AFX_HZPYSEARCH_H__1170A217_233E_4427_87AD_8806710D4DF0__INCLUDED_)
