
#ifndef UIDATATYPE_H
#define UIDATATYPE_H

#define ARRAY   vector

#define FUNNAME_MAXLEN 64	//��������󳤶�
#define ITEMNAME_MAXLEN 32	//��Ŀ������󳤶�
#define PATH_MAX		512

//�˵���Ŀ
typedef struct tagMenuItem
{   
	char szName[ITEMNAME_MAXLEN];		     //��Ŀ����
	char szClickFunName[FUNNAME_MAXLEN];	 //click��������
 	char szItemType[ITEMNAME_MAXLEN];        //��Ŀ���ͣ�����������itemInfo.xml ����
 	char szImgFolder[PATH_MAX];			  	 //��ĿͼƬ·��
 
	void SetItemName( LPCSTR lpstring  )
	{ 
		_snprintf( szName, sizeof(szName), "%s", lpstring );	
	}

	void SetItemFuncName( LPCSTR lpstring  )
	{ 
		_snprintf( szClickFunName, sizeof(szClickFunName), "%s", lpstring );	
	}

	void SetItemType( LPCSTR lpstring  )
	{ 
		_snprintf( szItemType, sizeof(szItemType), "%s", lpstring );	
	}

	void SetItemImg( LPCSTR lpstring  )
	{ 
		_snprintf( szImgFolder, sizeof(szImgFolder), "%s", lpstring );	
	}


	tagMenuItem()
	{
		ZeroMemory( this, sizeof(tagMenuItem) );
	}

} TMenuItem, *PTMenuItem;

 
enum EM_ORDERPOSOPT_TYPE      //Ԥ��λ��������
{
	em_ORDERPOSOPT_SAVE,
	em_ORDERPOSOPT_MODIFY,
};

enum EM_MENULISTOPT_TYPE      //�������б�����
{
	em_MENULIST_HIDE,
		em_MENULIST_SHOW,
};

#endif