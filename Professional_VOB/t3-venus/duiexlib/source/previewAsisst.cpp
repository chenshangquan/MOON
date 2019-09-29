#include "StdAfx.h"
#include "previewAsisst.h"

// The GUID of IPreviewHandler
extern const GUID CLSID_IPREVIEWHANDLER   = {0x8895b1c6,0xb41f,0x4c1c,{0xa5,0x62,0x0d,0x56,0x42,0x50,0x83,0x6f} } ;

tString CPreviewAsisst::m_strPreviewHandlerGUID = _T("{8895b1c6-b41f-4c1c-a562-0d564250836f}");
CPreviewAsisst::CPreviewAsisst(void)
{    
	m_pIP = NULL ; 
	m_pIFile = NULL ;
	m_pIStream = NULL ;
	m_hGlobal = NULL;
	m_pStream = NULL;
	CoInitialize(NULL);
}


CPreviewAsisst::~CPreviewAsisst(void)
{
	ClearEnv( );
	CoUninitialize();  
}  

void CPreviewAsisst::ClearEnv(  )
{   
	if( NULL != m_hGlobal)
	{ 
		GlobalFree( m_hGlobal);
		m_hGlobal = NULL;
		m_pStream = NULL;
	} 
	 
	SAFERELEASE( m_pIStream ); 
	SAFERELEASE( m_pIFile ); 
	
	if( NULL != m_pIP )			//���� ����excel���� by ldy
	{
		m_pIP->Unload();
		SAFERELEASE( m_pIP );					
	} 
}

LONG  CPreviewAsisst::SetPrevWindow( HWND hwndPreview, RECT&rc )
{
	LONG re = S_OK; 
	m_hwndPreview = hwndPreview;
	 
	m_rcPreview =rc;
 
	
	if ( NULL != m_pIP )
	{
		 re = m_pIP->SetWindow(hwndPreview,&rc);  
	}

	return re;
}

LONG CPreviewAsisst::SetPrevRect( RECT &Rc )
{
	LONG re = S_OK;
	m_rcPreview = Rc;
	if ( NULL == m_pIP )
	{
		re = m_pIP->SetRect(&Rc);
	}

	return re; 
}

LONG CPreviewAsisst::DoPreview( LPCTSTR szFile /*= NULL */ )
{
	ClearEnv(); 
	LONG hRe = S_OK;
	CLSID rclsid = GUID_NULL; 
	hRe = GetClsidFromFile( szFile, rclsid );
	if ( S_OK != hRe )
	{
		return hRe;
	}

	hRe = CoCreateInstance(  rclsid , NULL, CLSCTX_INPROC_SERVER|CLSCTX_LOCAL_SERVER ,
		IID_IPreviewHandler ,(LPVOID*) &m_pIP  ); 

	if( FAILED(hRe) )
	{
		TRACE(L"\n[CPreviewAsisst::InitEnv] ��ȡע����ʧ�� \n"); 
		return hRe;
	}

	int nInitCase = 1;
	switch( nInitCase )
	{
	case 1:
			hRe = InitByIFile( szFile );
			if ( S_OK == hRe )
			{
				break;
			}
	case 2:
			hRe = InitByIStream( szFile ); 
			if ( S_OK == hRe )
			{
				break;
			}
	default:
			break;
	}
	 
	if( FAILED(hRe) )
	{
		TRACE(L"\n[CPreviewAsisst::DoPreview] Initialize File ʧ�� \n"); 
		return hRe;
	}


	hRe = m_pIP->SetWindow(m_hwndPreview,&m_rcPreview);
	hRe = m_pIP->SetRect(&m_rcPreview);
	if ( SUCCEEDED(hRe) )
	{
		hRe= m_pIP->DoPreview(); 
	} 
	 
	return hRe;
}

LONG CPreviewAsisst::DoPreview( HWND hWnd, RECT &rectPreview, LPCTSTR szFile )
{  
	SetPrevWindow( hWnd, rectPreview );
	return DoPreview(szFile);

}

void CPreviewAsisst::Unload()
{
	ClearEnv();
}


HRESULT CPreviewAsisst::InitByIFile( LPCTSTR pchFile )
{
	if( NULL == m_pIP ||  NULL == pchFile )
	{
		return S_FALSE;
	}  

	HRESULT re = S_OK;

	re = m_pIP->QueryInterface(IID_IInitializeWithFile, (LPVOID*)&m_pIFile );

	if( S_OK == re  )
	{ 
		re = m_pIFile->Initialize( pchFile, STGM_READ) ;
	}  
	
	return re;
}

HRESULT CPreviewAsisst::InitByIStream( LPCTSTR pchFile )
{
	if( NULL == m_pIP ||  NULL == pchFile )
	{
		return S_FALSE;
	}  

	HRESULT re = S_OK;

	re = m_pIP->QueryInterface( IID_IInitializeWithStream, (LPVOID*)&m_pIStream );
	if ( S_OK != re || NULL == m_pIStream )
	{
		return re;
	}

	HANDLE hFile = CreateFile(pchFile,FILE_READ_DATA,FILE_SHARE_READ,NULL,OPEN_EXISTING,0,NULL );
	if( INVALID_HANDLE_VALUE != hFile )
	{
		DWORD dwSize = GetFileSize( hFile,NULL );
		m_hGlobal= GlobalAlloc(GPTR, dwSize );
		BYTE * pByte = (BYTE *)GlobalLock(m_hGlobal);

		if( pByte )
		{
			ReadFile(hFile,pByte,dwSize,&dwSize,NULL);	
			GlobalUnlock(m_hGlobal);

			CreateStreamOnHGlobal(m_hGlobal, TRUE, &m_pStream);	
			re = m_pIStream->Initialize( m_pStream,STGM_READ);
		}

		CloseHandle( hFile );
	}
	 
	return re;

}



LONG CPreviewAsisst::GetClsidFromFile( IN LPCTSTR szFile, OUT CLSID& rclsid )
{  
	
	if(   NULL == szFile )
	{
		return S_FALSE;

	} 

	TCHAR *ptcExtn = StrRChr(szFile, NULL,_T('.') ); 
	if ( NULL == ptcExtn )
	{
		return S_FALSE;
	}

	
	tString strClsid = _T("");
	HRESULT re = S_FALSE;
	int nCase = 1;
	switch( nCase )
	{ 
	case 1:
		re = GetClsidByExtnCase1(ptcExtn, strClsid);
		if ( S_OK == re )
		{
			break;
		}
	case 2:
		re = GetClsidByExtnCase2(ptcExtn, strClsid);
		if ( S_OK == re )
		{
			break;
		}
	case 3:
		re = GetClsidByExtnCase3(ptcExtn, strClsid);
		if ( S_OK == re )
		{
			break;
		}
	default:
		re = GetClsidByExtnCase4(ptcExtn, strClsid);
		if ( S_OK == re )
		{
			break;
		} 
	} 

	if ( S_OK == re )
	{   
		re = CLSIDFromString( strClsid.c_str(), &rclsid); 
	} 
	return re;
}
 

/*------------------------------------------------------------------
	* ��    �ܣ�ͨ����׺��ֱ�ӻ�ȡclsid�ַ��� ����1
	* ���������szFileExt �ļ���׺
	* ���������strClsid  guid�ַ���
	* �� �� ֵ���ɹ�����S_OK,ʧ�ܷ��ش�����
	* ��    ע����.docxΪ��
	*          �� HKEY_CLASSES_ROOT\.docx\ShellEx\{8895b1c6-b41f-4c1c-a562-0d564250836f}��ȡ
	*          �����ɹ����ɵ��÷���2������
	* ����          �汾        �޸���      �޸ļ�¼
	* 2013.3.5      1.0         �����        ����
---------------------------------------------------------------------*/
LONG CPreviewAsisst::GetClsidByExtnCase1(IN  LPCTSTR pchFileExt,OUT tString& strClsid )
{
	if( NULL == pchFileExt )
	{
		return S_FALSE;
	}
	  
	WCHAR wcData[MAX_PATH]={};
	LONG cData = sizeof( wcData ) ;
	tString strSubKey;
	//strSubKey.Format(_T("%s\\ShellEx\\%s"), pchFileExt, m_strPreviewHandlerGUID ); 

	strSubKey = pchFileExt;
	strSubKey += _T("\\ShellEx\\");
	strSubKey += m_strPreviewHandlerGUID;

	if( ERROR_SUCCESS == RegQueryValue(HKEY_CLASSES_ROOT,strSubKey.c_str(),wcData, &cData) )
	{
		strClsid = wcData;
		return S_OK; 
	}
	
	return S_FALSE;
}




/*---------------------------------------------------------------
	* ��    �ܣ�ͨ����׺��ֱ�ӻ�ȡclsid�ַ��� ����2
	* ���������szFileExt �ļ���׺
	* ���������strClsid  guid�ַ���
	* �� �� ֵ���ɹ�����S_OK,ʧ�ܷ��ش�����
	* ��    ע����.html��׺Ϊ��
	*           ���������·���õ�GUID 
	*           HKEY_CLASSES_ROOT\SystemFileAssociations\.html\ShellEx\{8895b1c6-b41f-4c1c-a562-0d564250836f}
	*           �����ɹ����ɵ��÷���3������
	* ����          �汾        �޸���      �޸ļ�¼
	* 2013.3.5      1.0         �����        ����
--------------------------------------------------------------------*/
LONG CPreviewAsisst::GetClsidByExtnCase2( IN LPCTSTR szFileExt,OUT tString& strClsid )
{
	if( NULL == szFileExt )
	{
		return S_FALSE;
	}

	WCHAR wcData[MAX_PATH]={};
	LONG cData = sizeof( wcData ) ; 
	tString strSubKey;
	//strSubKey.Format(_T("SystemFileAssociations\\%s\\ShellEx\\%s"), szFileExt, m_strPreviewHandlerGUID ); 

	strSubKey = _T("SystemFileAssociations\\");
	strSubKey += szFileExt;
	strSubKey += _T("\\ShellEx\\");
	strSubKey += m_strPreviewHandlerGUID;

	if( ERROR_SUCCESS == RegQueryValue(HKEY_CLASSES_ROOT,strSubKey.c_str(),wcData, &cData) )
	{
		strClsid = wcData;
		return S_OK; 
	}

	return S_FALSE;
}



/*---------------------------------------------------------------
	* ��    �ܣ�ͨ����׺��ֱ�ӻ�ȡclsid�ַ���
	* ���������szFileExt �ļ���׺
	* ���������strClsid  guid�ַ���
	* �� �� ֵ���ɹ�����S_OK,ʧ�ܷ��ش�����
	* ��    ע����.txtΪ��
	   �ȴ�HKEY_CLASSES_ROOT\.txt �õ�PerceivedType���ֵ�ֵtext
	   �ٵ����·���õ�GUID 
	   HKEY_CLASSES_ROOT\SystemFileAssociations\text\ShellEx\{8895b1c6-b41f-4c1c-a562-0d564250836f}
	* ����          �汾        �޸���      �޸ļ�¼
	* 2013.3.5      1.0         �����        ����
--------------------------------------------------------------------*/
LONG CPreviewAsisst::GetClsidByExtnCase3( IN LPCTSTR szFileExt,OUT tString& strClsid )
{  
	LONG hRe = S_FALSE; 
	tString csSubKey = _T("");
	//csSubKey.Format( _T("%s"), szFileExt );
	csSubKey = szFileExt;

	HKEY hKey = NULL;
	LONG lRe = RegOpenKeyEx(HKEY_CLASSES_ROOT,csSubKey.c_str(),0, KEY_READ, &hKey);
    DWORD err = GetLastError( );
	if( ERROR_SUCCESS == lRe )
	{   
		TCHAR tchKeyName[MAX_PATH]=_T("PerceivedType");
		TCHAR wcData[MAX_PATH]={};
		DWORD dwDataSize = sizeof(wcData)/sizeof(TCHAR) ;
		DWORD dwType = REG_SZ;
		lRe = RegQueryValueEx( hKey, tchKeyName, NULL, &dwType,  (unsigned char *)wcData, &dwDataSize );
		if ( ERROR_SUCCESS != lRe )
		{
			return S_FALSE;
		} 
		 
		//csSubKey.Format( _T("SystemFileAssociations\\%s\\ShellEx\\%s"), wcData, m_strPreviewHandlerGUID );

		csSubKey = _T("SystemFileAssociations\\");
		csSubKey += wcData;
		csSubKey += _T("\\ShellEx\\");
		csSubKey += m_strPreviewHandlerGUID;

		LONG wDataSize = sizeof(wcData)/sizeof(TCHAR) ;
		ZeroMemory(wcData,dwDataSize); 
		lRe = RegQueryValue(HKEY_CLASSES_ROOT,csSubKey.c_str(),wcData, &wDataSize);
		if ( ERROR_SUCCESS == lRe )
		{
			strClsid = wcData;
			hRe = S_OK;
		} 
	}
	return hRe; 
}


/*---------------------------------------------------------------
	* ��    �ܣ�ͨ����׺��ֱ�ӻ�ȡclsid�ַ��� ����4
	* ���������szFileExt �ļ���׺
	* ���������strClsid  guid�ַ���
	* �� �� ֵ���ɹ�����S_OK,ʧ�ܷ��ش�����
	* ��    ע����.html��׺Ϊ��
	*           �ȴ�HKEY_CLASSES_ROOT\.html�õ���Ĭ��ֵhtmlfile.
	*           �ٵ��������·���õ�GUID 
	*           HKEY_CLASSES_ROOT\htmlfile\ShellEx\{8895b1c6-b41f-4c1c-a562-0d564250836f}
	*           ������1--4 �����ɹ�����˵�����ļ�������Ԥ�������޷�Ԥ��
	* ����          �汾        �޸���      �޸ļ�¼
	* 2013.3.5      1.0         �����        ����
--------------------------------------------------------------------*/
LONG CPreviewAsisst::GetClsidByExtnCase4( IN LPCTSTR szFileExt,OUT tString& strClsid )
{
	LONG hRe = S_FALSE; 
	tString csSubKey = _T("");
	//csSubKey.Format( _T("%s"), szFileExt );
	csSubKey = szFileExt;

	HKEY hKey = NULL;
	LONG lRe = RegOpenKeyEx(HKEY_CLASSES_ROOT,csSubKey.c_str(),0, KEY_READ, &hKey);
	DWORD err = GetLastError( );
	if( ERROR_SUCCESS == lRe )
	{   
		TCHAR tchKeyName[MAX_PATH]=_T("");
		TCHAR wcData[MAX_PATH]={};
		DWORD dwDataSize = sizeof(wcData)/sizeof(TCHAR) ;
		DWORD dwType = REG_SZ;
		lRe = RegQueryValueEx( hKey, tchKeyName, NULL, &dwType,  (unsigned char *)wcData, &dwDataSize );
		if ( ERROR_SUCCESS != lRe )
		{
			return S_FALSE;
		} 

		//csSubKey.Format( _T("%s\\ShellEx\\%s"), wcData, m_strPreviewHandlerGUID );

		csSubKey = wcData;
		csSubKey += _T("\\ShellEx\\");
		csSubKey += m_strPreviewHandlerGUID;

		LONG wDataSize = sizeof(wcData)/sizeof(TCHAR) ;
		ZeroMemory(wcData,dwDataSize); 
		lRe = RegQueryValue(HKEY_CLASSES_ROOT,csSubKey.c_str(),wcData, &wDataSize);
		if ( ERROR_SUCCESS == lRe )
		{
			strClsid = wcData;
			hRe = S_OK;
		} 
	}
	return hRe;
}

