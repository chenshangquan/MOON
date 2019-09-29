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
函 数 名: Zip
功    能: 压缩
参    数: LPCSTR lpszSrcFile        [in]    待压缩文件
          LPCSTR lpszDstFile        [in]    压缩结果文件
注    意: 无
返 回 值: 压缩成功: TRUE; 压缩失败: FALSE
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2007/06/29  1.0     王昊    创建
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
函 数 名: Unzip
功    能: 解压
参    数: LPCSTR lpszSrcFile        [in]    待解压文件
          LPCSTR lpszDstFile        [in]    解压结果文件
注    意: 无
返 回 值: 解压成功: TRUE; 解压失败: FALSE
-------------------------------------------------------------------------------
修改纪录:
日      期  版本    修改人  修改内容
2007/06/29  1.0     王昊    创建
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
