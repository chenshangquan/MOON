/******************************************************************************
 * 模块名      : kprop
 * 文件名      : kfile.h
 * 相关文件    : 
 * 文件实现功能: 带进程锁、线程锁的文件操作定义
 * 作者        : 谢志钢
 * 版本        : v1.0  Copyright(C) 2014-2015 KDC, All rights reserved.
 * ----------------------------------------------------------------------------
 * 修改记录:
 * 日期        版本  修改人  修改内容
 * 2015-01-03  1.0   谢志钢  创建
 ******************************************************************************/
#ifndef KFILE_H
#define KFILE_H

#include <stddef.h>
#include <stdio.h>
#include <sys/stat.h>

// {{{ 前置定义项
#include "kdvtype.h"

#ifndef KEXTERN
#  ifdef KPROP_DLL
#    ifdef KPROP_INTERNAL
#      define KEXTERN extern __declspec(dllexport)
#    else /* ! KPROP_INTERNAL */
#      define KEXTERN extern __declspec(dllimport)
#    endif /* KPROP_INTERNAL */
#  else /* ! KPROP_DLL */
#    define KEXTERN extern
#  endif /* KPROP_DLL */
#endif /* KEXTERN */

#ifndef HAVE_ERROR_TYPE
typedef s32 error_t;
#define HAVE_ERROR_TYPE
#endif // HAVE_ERROR_TYPE

#ifndef NO_ERROR
#define NO_ERROR  (error_t)0
#endif // NO_ERROR
// }}}

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \brief Thread safe and process safe file utility. But,
 *        Be sure strictly use kfiles in thread in which it creates.
 */
typedef struct tag_kfile TKFile;

/*!
 * \brief Initializes an object of kfile.
 *        kfile is thread safe and process safe file utility.
 *        After an object created, it holds the lock of this file util it be
 *        destroyed.
 *
 * \param pptFile     - object pointer returned after created.
 *                      Before pass it in, be sure it holds NULL.
 * \param pszFilename - pszFilename or path to open and to lock.
 * \param pszMode     - mode of file openning, such as: "wb+" or "rb+".
 * \param dwTimeoutUs - Timeout in microseconds waiting for file lock.
 *                      If it is zero, it waits infinit utill gets lock.
 *                      1 second = 1000 milliseconds = 1000, 000 microseconds.
 *
 * \return 0 if successful, otherwise non-zero.
 */
KEXTERN
error_t KFileInit (TKFile **pptFile, const s8* pszFilename, const s8* pszMode,
        u32 dwTimeoutUs);

/*!
 * \brief Destroyes an object of kfile.
 *        If pass NULL, or pointer of NULL, also ok.
 *        After an object is destroyed, the pointer will set NULL.
 */
KEXTERN
void KFileDestroy (TKFile **pptFile);

/*!
 * \brief Reads data from an object file.
 *
 * \param ptFile   - object pointer for kfile.
 * \param pBuff    - buffer to accept data from kfile.
 * \param dwSize   - size of data element, if in record format.
 *                   Normally, often set as 1 as for s8 or byte element.
 * \param dwNum    - number of elements as a block want to read from file.
 *
 * \note  Make sure the buffer to accept data have enough bytes capacity of
 *        dwSize * dwNum, otherwise it will cause memory-stamp with no complaint.
 *
 * \return The number of items/elements readed from file.
 */
KEXTERN
u32 KFileRead (TKFile *ptFile, void *pBuff, u32 dwSize, u32 dwNum);

/*!
 * \brief Reads one line from file.
 *
 * \note  Reads in at most one less than size characters from stream
 *        and stores them into the buffer pointed to by buf. Reading stops
 *        after an EOF or a newline.  If a newline is read, it is stored into
 *        the buffer. A terminating null byte ('\0') is stored after the last
 *        character in the buffer.
 *
 * \note  The readed line is trimed the ending line-end, so you should not
 *        expect a line-end from it.
 *
 * \param ptFile   - object pointer for kfile.
 * \param pBuf     - s8 buffer to accept the line readed from file.
 * \param dwSize   - buffer capacit in bytes, including terminting null.
 *
 * \return buf on success,
 *         and NULL on error or when end of file occurs while no characters
 *         have been read.
 */
KEXTERN
s8* KFileReadLine (TKFile *ptFile, s8 *pBuf, u32 dwSize);

/*!
 * \brief Tests whether the file is end of file.
 * 
 * \return non-zero if is end of file.
 */
KEXTERN
BOOL32 KFileIsEof (TKFile *ptFile);

/*!
 * \brief Writes data into an object file.
 *
 * \param ptFile - object pointer for kfile.
 * \param pData  - buffer which holds data to be written into this file.
 * \param dwSize - size of data element, if in record format.
 *                 Normally, often set as 1 as for s8 or byte element.
 * \param dwNum  - number of elements as a block want to write into file.
 *
 * \note  Make sure the buffer contains data of bytes size * nmemb,
 *        otherwise it will access beyond memory boundary with no complaint.
 *
 * \return The number of items/elements written into file.
 */
KEXTERN
u32 KFileWrite (TKFile *ptFile, const void *pData, u32 dwSize, u32 dwNum);

/*!
 * \brief Writes a string into file without terminal nil.
 *
 * \param ptFile   - object pointer for kfile.
 * \param pszStr   - string to write into file.
 *
 * \return  a nonnegative number on success, or EOF(-1) on error. 
 */
KEXTERN
s32 KFileWriteString (TKFile *ptFile, const s8* pszStr);

/*!
 * \brief Seek possition in file.
 *        Currently, it supports not a large offset of int64_t bytes.
 *
 * \param ptFile   - object pointer for kfile.
 * \param nOffset  - offset based on whence, positive or negative.
 * \param nWhence  - base for offset to locate the position, these values
 *                   acceptable:
 *                     SEEK_SET (0)
 *                     SEEK_CUR (1)
 *                     SEEK_END (2)
 *
 * \return 0 if successful, otherwise non-zero.
 */
KEXTERN
error_t KFileSeek(TKFile *ptFile, s32 nOffset, s32 nWhence);

/*!
 * \brief Tell current position in file.
 *        Currently, it supports not a large offset of int64_t bytes.
 *
 * \param ptFile    - object pointer for kfile.
 *
 * \return Current position in file. Otherwise, -1 is returned.
 */
KEXTERN
s32 KFileTell(TKFile *ptFile);

/*!
 * \brief Gets file status from kfile object.
 *
 * \param ptFile    - object pointer for kfile.
 * \param ptBuf     - buffer to holds file status.
 *
 * \return On success, zero is returned.
 *         On error, -1 or other is returned, and errno is set appropriately.
 */
KEXTERN
error_t KFileStat (TKFile *ptFile, struct stat *ptBuf);

/*!
 * \brief Gets file path from kfile object.
 *
 * \param ptFile    - object pointer for kfile.
 * \param pchBuff   - buffer to accept filename.
 * \param dwBuffLen - byte size of the filename buffer.
 *
 * \return On success, zero is returned.
 *         On error, -1 or other is returned.
 */
KEXTERN
error_t KFileGetPath (TKFile *ptFile, s8* pchBuff, u32 dwBuffLen);

#ifdef __cplusplus
}
#endif

#endif //KFILE_H
/* vim:set foldmethod=marker: */
