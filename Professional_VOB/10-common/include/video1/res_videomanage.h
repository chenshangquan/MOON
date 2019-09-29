#ifndef _VIDEO_MEM_H_
#define _VIDEO_MEM_H_

#include "algorithmtype.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RES_MALLOC_SUCESS   0
#define RES_MALLOC_FAIL    -1

#if ((defined(ARCH_X86_WIN32)) || (defined(ARCH_X86_LINUX)) || (defined(ARCH_X86_64_LINUX)) || (defined (ARCH_X86_WIN64)))
#define FAST_MEM_SIZE (54 << 10)
#define FAST_MEM_SCRATCH   (96 << 10)
#else
#define FAST_MEM_SIZE (54 << 10)
#define FAST_MEM_SCRATCH   (96 << 10)//ý���Ǳ�jpeg����4160x3120 //(48 << 10)
#endif

typedef struct
{
    void* pvDMAHandle;              //DMAͨ�����
    void* pvFastMem;                //Ƭ�ڿ����ڴ���
    void* pvSlowMem;                //Ƭ�������ڴ���
    void* pvSlowScratchMem;         //Ƭ��Scratch�ڴ���
    l32 l32FastMemSize;             //Ƭ�ڿ����ڴ��ܴ�С
    l32 l32SlowMemSize;             //Ƭ�������ڴ��ܴ�С
} TInputMemParam;

typedef struct
{
    void* pvSubSlowMem;             //Ƭ�������ڴ���
    void* pvSubFastMem;
    l32 l32UsedSlowPersistMemSize;  //Ƭ������˽���ڴ����ô�С
    l32 l32SubSlowMemSize;
    l32 l32UsedFastPersistMemSize;  //
    l32 l32SubFastMemSize;
    u32 u32Reserved;
} TMemInfo;

//���ڼ���ڴ�Խ����ʵ�����ַ�
#define FILL_BYTE_FP          0xDA
#define FILL_BYTE_FS          0xDB
#define FILL_BYTE_SP          0xDC
#define FILL_BYTE_SS          0xDE

//Davinciƽ̨ʹ�õ��ڴ���亯��
//#ifdef ARCH_DM64XPLUS
#if defined (ARCH_DM64XPLUS) || defined (ARCH_C674X)

#define SLOW_MEM_SCRATCH   (1024 * 768 * 2)

extern u64 au64FastMem[FAST_MEM_SIZE / 8];

extern u64 au64SlowScratchMem[SLOW_MEM_SCRATCH / 8];

typedef struct
{
    void* pvDMAHandle;              //DMAͨ�����
    void* pvFastPersistMem;         //Ƭ�ڿ���˽���ڴ���
    void* pvFastScratchMem;         //Ƭ�ڿ��ٹ����ڴ���
    void* pvSlowPersistMem;         //Ƭ������˽���ڴ���
    void* pvSlowScratchMem;         //Ƭ�����ٹ����ڴ���
    l32 l32FastPersistMemSize;      //Ƭ�ڿ���˽���ڴ��ܴ�С
    l32 l32FastScratchMemSize;      //Ƭ�ڿ��ٹ����ڴ��ܴ�С
    l32 l32SlowPersistMemSize;      //Ƭ������˽���ڴ��ܴ�С
    l32 l32SlowScratchMemSize;      //Ƭ�����ٹ����ڴ��ܴ�С
    l32 l32UsedFastPersistMemSize;  //Ƭ�ڿ���˽���ڴ����ô�С
    l32 l32UsedSlowPersistMemSize;  //Ƭ������˽���ڴ����ô�С
} TMemStatusParam;

l32 VideoMemInitial_dm64xplus(void **ppvMemHandle, void *pvInputMemParam);
void *VideoMallocFastPersist_dm64xplus(void *pvMemHandle, l32 l32MemSize, l32 l32AlignByte);
void *VideoMallocFastScratch_dm64xplus(void *pvMemHandle, l32 l32MemSize, l32 l32AlignByte);
void *VideoMallocSlowPersist_dm64xplus(void *pvMemHandle, l32 l32MemSize, l32 l32AlignByte);
void *VideoMallocSlowScratch_dm64xplus(void *pvMemHandle, l32 l32MemSize, l32 l32AlignByte);
l32 VideoSetFastPersistSize_dm64xplus(void* pvMemHandle, l32 l32UsedMemSize);
l32 VideoFreeFastPersist_dm64xplus(void *pvMemHandle, void *pvMem);
l32 VideoFreeFastScratch_dm64xplus(void *pvMemHandle, void *pvMem);
l32 VideoFreeSlowPersist_dm64xplus(void *pvMemHandle, void *pvMem);
l32 VideoFreeSlowScratch_dm64xplus(void *pvMemHandle, void *pvMem);
l32 VideoMemClose_dm64xplus(void *pvMemHandle);
void* GetDMAHandle_dm64xplus(void* pvMemHandle);
l32 VideoMemGetStatus_dm64xplus(void *pvMemHandle, TMemStatusParam *ptMemStatus);
l32 VideoGetMemInfoBegin_dm64xplus(void *pvMemHandle, void *pvMemInfo);
l32 VideoGetMemInfoEnd_dm64xplus(void *pvMemHandle, void *pvMemInfo);
l32 VideoSetMemInfo_dm64xplus(void *pvMemHandle, void *pvMemInfo);
l32 VideoResumeMemInfo_dm64xplus(void *pvMemHandle, void *pvMemInfo);
void VideoMemGetMemSize_dm64xplus(l32 *pl32MemSize);

#define VideoMemInitial VideoMemInitial_dm64xplus
#define VideoMallocFastPersist VideoMallocFastPersist_dm64xplus
#define VideoMallocFastScratch VideoMallocFastScratch_dm64xplus
#define VideoMallocSlowPersist VideoMallocSlowPersist_dm64xplus
#define VideoMallocSlowScratch VideoMallocSlowScratch_dm64xplus
#define VideoSetFastPersistSize VideoSetFastPersistSize_dm64xplus
#define VideoFreeFastPersist VideoFreeFastPersist_dm64xplus
#define VideoFreeFastScratch VideoFreeFastScratch_dm64xplus
#define VideoFreeSlowPersist VideoFreeSlowPersist_dm64xplus
#define VideoFreeSlowScratch VideoFreeSlowScratch_dm64xplus
#define VideoMemClose VideoMemClose_dm64xplus
#define GetDMAHandle GetDMAHandle_dm64xplus
#define VideoMemGetStatus VideoMemGetStatus_dm64xplus
#define VideoGetMemInfoBegin VideoGetMemInfoBegin_dm64xplus
#define VideoGetMemInfoEnd VideoGetMemInfoEnd_dm64xplus
#define VideoSetMemInfo VideoSetMemInfo_dm64xplus
#define VideoResumeMemInfo VideoResumeMemInfo_dm64xplus
#define VideoMemGetMemSize VideoMemGetMemSize_dm64xplus
#define VideoMemReport(pvMemHandle)

#else //����Davinciƽ̨����������ƽ̨���õ��ڴ���������

#define SLOW_MEM_SCRATCH   (1920 * 1088 * 2)

l32 VideoMemInitial_c(void **ppvMemHandle, void *pvInputMemParam);
void *VideoMemMalloc_c(void *pvMemHandle, l32 l32MemSize, l32 l32AlignByte,u8 u8FillBytes, const s8 * pstrFileName, l32 l32LineNum);
l32 VideoMemFree_c(void *pvMemHandle, void *pvMem,u8 u8FillBytes, const s8 * pstrFileName, l32 l32LineNum);
void *VideoMemMallocFastScrach_c(void *pvMemHandle, l32 l32MemSize, l32 l32AlignByte, u8 u8FillBytes, const s8 * pstrFileName, l32 l32LineNum);
l32 VideoMemFreeFastScrach_c(void* pvMemHandle, void* pvMem, u8 u8FillBytes, const s8 * pstrFileName, l32 l32LineNum);
l32 VideoMemClose_c(void *pvMemHandle);
void* GetDMAHandle_c(void* pvMemHandle);
l32 VideoGetMemInfoBegin_c(void *pvMemHandle, void *pvMemInfo);
l32 VideoGetMemInfoEnd_c(void *pvMemHandle, void *pvMemInfo);
l32 VideoSetMemInfo_c(void *pvMemHandle, void *pvMemInfo);
l32 VideoResumeMemInfo_c(void *pvMemHandle, void *pvMemInfo);
// �ڴ涯̬���䡢�ͷź���
void *VideoMemDynMalloc_c(void *pvMemHandle, l32 l32MemSize, l32 l32AlignByte,u8 u8FillBytes, const s8 * pstrFileName, l32 l32LineNum);
l32 VideoMemDynFree_c(void *pvMemHandle, void *pvMem,u8 u8FillBytes, const s8 * pstrFileName, l32 l32LineNum);

#define VideoMemInitial VideoMemInitial_c
#define VideoMallocFastPersist(pvMemHandle, l32MemSize, l32AlignByte) VideoMemMalloc_c(pvMemHandle, l32MemSize, l32AlignByte, FILL_BYTE_FP, __FILE__, __LINE__)
#define VideoMallocFastScratch(pvMemHandle, l32MemSize, l32AlignByte) VideoMemMallocFastScrach_c(pvMemHandle, l32MemSize, l32AlignByte, FILL_BYTE_FS, __FILE__, __LINE__)
#define VideoMallocSlowPersist(pvMemHandle, l32MemSize, l32AlignByte) VideoMemMalloc_c(pvMemHandle, l32MemSize, l32AlignByte, FILL_BYTE_SP, __FILE__, __LINE__)
#define VideoMallocSlowScratch(pvMemHandle, l32MemSize, l32AlignByte) VideoMemMalloc_c(pvMemHandle, l32MemSize, l32AlignByte, FILL_BYTE_SS, __FILE__, __LINE__)
#define VideoSetFastPersistSize 
#define VideoFreeFastPersist(pvMemHandle, pvMem) VideoMemFree_c(pvMemHandle, pvMem, FILL_BYTE_FP, __FILE__, __LINE__)
#define VideoFreeFastScratch(pvMemHandle, pvMem) VideoMemFreeFastScrach_c(pvMemHandle, pvMem, FILL_BYTE_FS, __FILE__, __LINE__)
#define VideoFreeSlowPersist(pvMemHandle, pvMem) VideoMemFree_c(pvMemHandle, pvMem, FILL_BYTE_FP, __FILE__, __LINE__)
#define VideoFreeSlowScratch(pvMemHandle, pvMem) VideoMemFree_c(pvMemHandle, pvMem, FILL_BYTE_FP, __FILE__, __LINE__)
#define VideoMemClose VideoMemClose_c
#define GetDMAHandle GetDMAHandle_c
#define VideoMemGetStatus
#define VideoGetMemInfoBegin VideoGetMemInfoBegin_c
#define VideoGetMemInfoEnd VideoGetMemInfoEnd_c
#define VideoSetMemInfo VideoSetMemInfo_c
#define VideoResumeMemInfo VideoResumeMemInfo_c
#define VideoMemReport(pvMemHandle) VideoMemReport_c(pvMemHandle)
#define VideoMemGetMemSize

// ��̬���䡢�ͷź���
#define VideoMemDynMalloc(pvMemHandle, l32MemSize, l32AlignByte) VideoMemDynMalloc_c(pvMemHandle, l32MemSize, l32AlignByte, FILL_BYTE_SP, __FILE__, __LINE__)
#define VideoMemDynFree(pvMemHandle, pvMem) VideoMemDynFree_c(pvMemHandle, pvMem, FILL_BYTE_FP, __FILE__, __LINE__)

#endif

#ifdef __cplusplus
}
#endif

#endif
