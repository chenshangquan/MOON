// HZPYSearch.cpp: implementation of the CHZPYSearch class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "HZPYSearch.h" 
#include "AddrList.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*
�ڵ���Լ���
CNode* pNode:  �������Ľӵ�
char *pString: �������Ĵ�
0����ʧ�ܻ�0������0����˳�������ȷ�ĸ���
*/
int Calc( CNode* pNode, char *pString )
{
	if( NULL == pNode || 0 == strlen( pString ) )
	{
		return 0;
	}
	
	int bResult = 0;
	if( pNode->m_bySymbol != pString[0] )
	{
		if( NULL != pNode->m_pMultiNext )
		{
			CNode *pCurNode = pNode->m_pMultiNext;
			for(; pCurNode; pCurNode = pCurNode->m_pMultiNext )
			{
				if( pCurNode->m_bySymbol == pString[0] )
				{
					if( NULL != pCurNode->m_pNodeNext )
					{
						bResult = Calc( pCurNode->m_pNodeNext, pString + 1);
						if( bResult )
						{
							bResult = Calc( pNode->m_pNodeNext, pString + 2) + 2;
						}
					}
					else
					{
						bResult = Calc( pNode->m_pNodeNext, pString + 1 ) + 1;
					}
					break;
				}
			}
		}
	}
	else
	{
		bResult = Calc( pNode->m_pNodeNext, pString + 1 ) + 1;
	}
	return bResult;
}

/*
�ݹ�ڵ���Լ��������Ϣ
CNode* pNode:  �������Ľӵ�
char *pString: �������Ĵ�
0����ʧ�ܻ�0������0����˳�������ȷ�ĸ���
*/
int OutCalc( CNode* pNode, char *pString )
{
	if ( NULL == pString )
	{
		return 0;
	}
	
	int bResult = Calc( pNode, pString );

	//if( 0 != bResult )  //���"ssh" "cch"��������������
	if( /*0*/strlen(pString) != bResult )
	{
		pNode = pNode->m_pNodeNext;
		while( pNode )
		{
			bResult = Calc( pNode, pString );

			if ( strlen(pString) != bResult )
			{
				if ( pNode->m_pNodeNext != NULL )
				{
					pNode = pNode->m_pNodeNext;
				}
				else
				{
					break;
				}
			}
			else
			{
				break;
			}
		}
	}
	return bResult;
}

void strtolower( char *string )
{
	if ( NULL == string )
	{
		return;
	}
	
	int nLen = strlen(string);
	for ( int i = 0; i < nLen; i++ )
	{
		if ( string[i] >= 'A' && string[i] <= 'Z' )
		{
			string[i] += 'a' - 'A';
		}
	}
}

BOOL IsGb2312( short wGbCode )
{
	unsigned char qu = wGbCode >> 8;
	unsigned char wei = wGbCode;
	
	if ( qu >= 0xa1 && qu <= 0xf7 )
	{
		if ( wei >= 0xa1 && wei <= 0xfe )
		{
			return TRUE;
		}
	}
	
	return FALSE;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHZPYSearch::CHZPYSearch()
{
	m_vectNode.clear();
}

CHZPYSearch::~CHZPYSearch()
{
   DestoryNodeList();
}

/*
���ܣ�PinYin�����ж�
������const char *strTextInput: ���жϵĶ���(�û�����PY��)
	  const char* strTextSrc : �ж�Դ�ֶ���(������)
����ֵ:��Գɹ� TRUE, ���ʧ�� FALSE;
*/
BOOL  CHZPYSearch::HZPYMatchList( const char *strTextInput, const char* strTextSrc )
{
	if ( NULL == strTextInput )
	{
		return TRUE;
	}

	if ( NULL == strTextSrc )
	{
		return FALSE;
	}

	//1.ֱ�����ԭ��, ��ʹ��strstr����bug����
	//char *ch = strstr( strTextSrc, strTextInput );   //bug char *ch = strstr( "½�����׳���", "׳" );
	CString str1 = strTextInput;
	CString str2 = strTextSrc;

    //���������ִ�Сд
    str1.MakeLower();
    str2.MakeLower();

	//int nFind = str1.Find(str2);
	int nFind = str2.Find(str1);
	
	if ( nFind != -1 )
	{
		return TRUE;
	}

	CNode* pHead = CreateNodeList( (LPCTSTR)str2 ); /*strTextSrc*/
 
	//int nResult = OutCalc( pHead, (char*)strTextInput );
    int nResult = OutCalc( pHead, (LPSTR)(LPCTSTR)str1 );

	DestoryNodeList();

	if( nResult == strlen( strTextInput ) )
	{
		return TRUE;
	}

	return FALSE;
}

/*
���ܣ�ͨ����Եĺ��֣���ĸ���ִ������������ڵ�����
��������Ҫ����DestoryNodeList()�������ٴ���
������const char *strTextParm  �ж�Ŀ��
*/
CNode* CHZPYSearch::CreateNodeList( const char *strTextParm )
{
	if ( NULL == strTextParm )
	{
		return NULL;
	}
	
	char* strText = NULL;	
	CNode *pHeadMulti = NULL;
	CNode *pHead = NULL;
	
	//�� strTextParm��ת�����strText
	char achText[512] = {0};
	
	int length = strlen(strTextParm);
	
	for (int k=0; k < length; )
	{
		if ( strTextParm[k] & 0x80 ) //����
		{
			achText[length-k-2] = strTextParm[k];
			achText[length-k-1] = strTextParm[k+1];
			k += 2;
		}
		else
		{
			achText[length-k-1] = strTextParm[k];
			k++;
		}
	}
	
	strText = achText;
	
	if ( NULL == strText )
	{
		return NULL;
	}
	
	int nLen = strlen( strText );
	
	for ( int i = 0; i < nLen;  )
	{
		if ( strText[i] & 0x80 ) //����
		{
			char p[3] = {0};
			memcpy( p, strText+i, 2);
			
			//��ȡ��Ӧ��ƴ����
			char arInputChr[ MAX_FIND_HANZI_LEN ] = { 0 }; 
			char arPYResult[ MAX_FIND_HANZI_LEN ][ MAX_FIND_HANZI_PY_CNT ] = {0};
			char pym[10] = {0};

			memcpy(arInputChr,  strText+i, 2);

			bool bRet = ConvertHZPY( arInputChr, arPYResult );

			if ( !bRet )
			{
				return NULL;
			}
		
			int m = 0;

			while ( arPYResult[0][m] != '\0' )
			{
				pym[m] = arPYResult[0][m];
				m++;
			}
		
			int nPymLen = strlen( pym );
			
			pHead = new CNode( '0', pHead );
			
			m_vectNode.push_back( pHead );
			
			for ( int j = 0; j < nPymLen; j++ )
			{			
				if ( j == 0)
				{
					pHeadMulti = new CNode( pym[j] );
				}
				else
				{
					pHeadMulti = new CNode( pym[j], NULL, pHeadMulti );
				}

				m_vectNode.push_back( pHeadMulti );
			}
			
			pHeadMulti = new CNode( p[0], NULL, pHeadMulti );

			m_vectNode.push_back( pHeadMulti );

			pHeadMulti->m_pNodeNext = new CNode( p[1] );

			m_vectNode.push_back( pHeadMulti->m_pNodeNext );

			pHead->m_pMultiNext = pHeadMulti;
			
			i += 2;
		}
		else
		{
			pHead = new CNode( strText[i], pHead );
			
			m_vectNode.push_back( pHead );
			
			i++;
		}  
	}
	
	return pHead;
}

/*
���ܣ��ͷ�CreateNodeList new�����Ľڵ���Դ
*/
void  CHZPYSearch::DestoryNodeList()
{
	int nCnt = m_vectNode.size();

	for ( int i = 0; i < nCnt; ++i )
	{
		CNode* pNode = m_vectNode[i];
		if ( NULL != pNode )
		{
			delete pNode;
			pNode = NULL;
		}
	}
	
	m_vectNode.clear();
}


/*
���ܣ�����ƴ����ת��
����: char arInputChr[ MAX_FIND_HANZI_LEN ] ����ĺ��ִ�
	  char arPYResult[MAX_FIND_HANZI_LEN][MAX_FIND_HANZI_PY_CNT]   ת�����	      
*/
bool  CHZPYSearch::ConvertHZPY( char arInputChr[ MAX_FIND_HANZI_LEN ], char arPYResult[MAX_FIND_HANZI_LEN][MAX_FIND_HANZI_PY_CNT] )
{
	
	// �����Ż���Ĳ���ƴ���ĺ���
    return SearchHZPY( arInputChr, arPYResult );

#if 0
    UINT i;
    HRSRC HGBSrc;
    LPVOID GBTemp;

    // ���Ҷ�Ӧ����Դ
    HGBSrc = FindResource( AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_PYGBK1), "PYGBK" );
    
	if( HGBSrc == NULL )
	{
		return false;
	}

    // �õ���Ӧ�����ݵĴ�С
    DWORD size = SizeofResource( AfxGetInstanceHandle(), HGBSrc );

    // װ���Ӧ��
    HGLOBAL m_HGBStr = LoadResource( AfxGetInstanceHandle(), HGBSrc );

    // ������Դ���õ�����ָ��
    GBTemp = LockResource( m_HGBStr );

    // ת��Ϊ char ���͵�ָ��
    char *buf = (char *)GBTemp;
 
    for( i = 0; i < MAX_FIND_HANZI_LEN; i++ )
	{
		arPYResult[i][0] = 0;
	}

    // ���ò���ƴ���ĺ���
    return SearchHZPY( buf, size, arInputChr, arPYResult );

#endif
}

/*
���ܣ�����ƴ���ĺ���(�����Ż������������������)
����: hzstr - ����ĺ��ִ���
	  arPY  - ��������� arPY ���飬���ڱ����뺺�ֶ�Ӧ������ƴ��
����: true: ����ת���ɹ�	      
*/
bool CHZPYSearch::SearchHZPY( char *hzstr, char arPY[MAX_FIND_HANZI_LEN][MAX_FIND_HANZI_PY_CNT])
{
	long len = 0;
	len = strlen( hzstr );
	
	int nCnt = 0;

	for( int k = 0; k<len; )
	{
		if ( hzstr[k] & 0x80 )//����
		{
			char chOneWord[3] = {0};
			memcpy( chOneWord, hzstr+k, 2);
			CString strKey = chOneWord ;
			//std::vector<CString> vect;
			//CHWCiHuiIF::Instance()->GetCiHui( strKey, vect );

			CString strLetter;
			CTransparentAddrList::GetFirstLetter( strKey, strLetter );
			strLetter.MakeLower();			
			
			memcpy( arPY[nCnt], strLetter, 1 );
// 			for ( int m=0; m < vect.size(); m++ )
// 			{
// 				char chPYResult[2] = {0};
// 				memcpy( chPYResult, vect[m], 1);
// 				strcat(arPY[nCnt], vect[m]);
// 			}
			
			k = k + 2;
		}
		else
		{
			memcpy(arPY[nCnt], hzstr+k, 1);	
			k++;
		}
		
		nCnt++;
	}
	
    return true;
}

/*
���ܣ�����ƴ���ĺ���
����: buf - ƴ���ͺ��ֵĶ�Ӧ������
	  size- ������Ĵ�С
	  hzstr - ����ĺ��ִ���
	  arPY  - ��������� arPY ���飬���ڱ����뺺�ֶ�Ӧ������ƴ��
����: true: ����ת���ɹ�	      
*/
bool CHZPYSearch::SearchHZPY(char *buf, long size, char *hzstr, char arPY[MAX_FIND_HANZI_LEN][MAX_FIND_HANZI_PY_CNT])
{
    char *ptr, str[1000], szPY[10], szHZ[1000];
    long i, j, k, start=0, len, len2;
    len2 = strlen(hzstr);    // ����ĺ��ִ��ĳ���
	
	int nPYindex = 0;
	for( k=0; k<len2; /*k=k+2*/)
	{
		start = 0;
		if ( hzstr[k] & 0x80 )//����
		{
			for( i=0; i<size; i++)
			{
				if( buf[i]==0x0a )    // ������ĩ
				{
					ptr = &buf[start];
					len = i-start;    // ���еĳ���
					strncpy(str, ptr, len);    // ȡ���е�����
					str[len]=0;
					start = i+1;    // ��λ��һ�еĿ�ʼλ��
					
					sscanf(str, "%s %s", szPY, szHZ);    // ����ƴ���Ͷ�Ӧ�ĺ���
					len=strlen(szHZ);
					// ѭ������
					for(j=0; j<len; j=j+2)
					{
						// �ҵ�ƥ����
						if(szHZ[j]==hzstr[k] && szHZ[j+1]==hzstr[k+1])
						{
							szPY[1] = '\0'; //��Ҫȫƴʱע�ʹ˾�
							//strcat(arPY[k/2], szPY);
							//strcat(arPY[k/2], ",");
							strcat(arPY[nPYindex], szPY);
							//strcat(arPY[k], ",");
						}
					}
				}
			}
			
			k=k+2;
		}
		else
		{
			
			char ach[2] = {0};
			ach[0] = hzstr[k];
			memcpy(arPY[nPYindex], ach, sizeof( ach ));	
			
			k=k+1;
		}
		
		nPYindex++;
	}
	
	
	
    return true;
}