// czip.cpp: implementation of the CGZip class.
//
//////////////////////////////////////////////////////////////////////
#include "czip.h"
#include <shlwapi.h>
#include <io.h>
#include <FCNTL.H>
#include <sys/STAT.H>


// global variables instancied in gzip 
extern "C" {

extern int dozip( int, int);
extern int dounzip( int, int );


//extern long time_stamp;
//extern char ifname[MAX_PATH_LEN]; 
//extern int save_orig_name;

extern int ifd;
extern int ofd;

}

//int inFile, outFile;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#pragma comment(lib, "shlwapi.lib")

CGZip::CGZip()
{

}

CGZip::~CGZip()
{

}

/*=============================================================================
�� �� ��: Zip
��    ��: ѹ��
��    ��: LPCSTR lpszSrcFile        [in]    ��ѹ���ļ�
          LPCSTR lpszDstFile        [in]    ѹ������ļ�
ע    ��: ��
�� �� ֵ: ѹ���ɹ�: TRUE; ѹ��ʧ��: FALSE
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2007/06/29  1.0     ���    ����
=============================================================================*/
BOOL32 CGZip::Zip(LPCSTR lpszSrcFile, LPCSTR lpszDstFile)
{
    if ( lpszSrcFile == NULL || lpszDstFile == NULL )
    {
        return FALSE;
    }

    s32 nSrcLen = strlen( lpszSrcFile );
    s32 nDstLen = strlen( lpszDstFile );

    if ( nSrcLen == 0 || nDstLen <= 3 )
    {
        return FALSE;
    }

    s8 szDstPost[4] = {0};

    memcpy( szDstPost, lpszDstFile + (nDstLen - 3), 3 );
    szDstPost[3] = '\0';
    if ( stricmp( szDstPost, ".gz" ) != 0 )
    {
        return FALSE;
    }

    if ( PathFileExists( lpszDstFile ) )
    {
        if ( ! DeleteFile( lpszDstFile ) )
        {
            return FALSE;
        }
    }
    if ( ! PathFileExists( lpszSrcFile ) )
    {
        return FALSE;
    }

    int nInFile = open( lpszSrcFile, _O_BINARY | _O_RDONLY );
    if ( nInFile == -1 )
    {
        return FALSE;
    }

    int nOutFile = open( lpszDstFile, _O_BINARY | _O_RDWR | _O_CREAT | _O_EXCL,
                         _S_IREAD | _S_IWRITE );
    if ( nOutFile == -1 )
    {
        close( nInFile );
        return FALSE;
    }

    ifd = nInFile;
    ofd = nOutFile;

    int nRet = dozip( nInFile, nOutFile );

    close( nInFile );
    close( nOutFile );

    if ( nRet != 0 )
    {
        return FALSE;
    }

    return TRUE;
}

/*=============================================================================
�� �� ��: Unzip
��    ��: ��ѹ
��    ��: LPCSTR lpszSrcFile        [in]    ����ѹ�ļ�
          LPCSTR lpszDstFile        [in]    ��ѹ����ļ�
ע    ��: ��
�� �� ֵ: ��ѹ�ɹ�: TRUE; ��ѹʧ��: FALSE
-------------------------------------------------------------------------------
�޸ļ�¼:
��      ��  �汾    �޸���  �޸�����
2007/06/29  1.0     ���    ����
=============================================================================*/
BOOL32 CGZip::Unzip(LPCSTR lpszSrcFile, LPCSTR lpszDstFile)
{
    if ( lpszSrcFile == NULL || lpszDstFile == NULL )
    {
        return FALSE;
    }

    s32 nSrcLen = strlen( lpszSrcFile );
    s32 nDstLen = strlen( lpszDstFile );

    if ( nSrcLen <= 3 || nDstLen == 0 )
    {
        return FALSE;
    }

    s8 szSrcPost[4] = {0};

    memcpy( szSrcPost, lpszSrcFile + (nSrcLen - 3), 3 );
    szSrcPost[3] = '\0';
    if ( stricmp( szSrcPost, ".gz" ) != 0 )
    {
        return FALSE;
    }

    if ( PathFileExists( lpszDstFile ) )
    {
        if ( ! DeleteFile( lpszDstFile ) )
        {
            return FALSE;
        }
    }
    if ( ! PathFileExists( lpszSrcFile ) )
    {
        return FALSE;
    }

    int nInFile = open( lpszSrcFile, _O_BINARY | _O_RDONLY );
    if ( nInFile == -1 )
    {
        return FALSE;
    }

    int nOutFile = open( lpszDstFile, _O_BINARY | _O_RDWR | _O_CREAT | _O_EXCL,
                         _S_IREAD | _S_IWRITE );
    if ( nOutFile == -1 )
    {
        close( nInFile );
        return FALSE;
    }

    ifd = nInFile;
    ofd = nOutFile;

    int nRet = dounzip( nInFile, nOutFile );

    close( nInFile );
    close( nOutFile );

    if ( nRet != 0 )
    {
        return FALSE;
    }
    
    return TRUE;
}
