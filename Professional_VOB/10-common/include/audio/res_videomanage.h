#ifndef _VIDEO_MEM_H_
#define _VIDEO_MEM_H_

#include "algorithmtype.h"

#ifdef __cplusplus
extern "C" {
#endif

#define RES_MALLOC_SUCESS   0
#define RES_MALLOC_FAIL    -1

#define FAST_MEM_SIZE (54 << 10)
#define FAST_MEM_SCRATCH   (48 << 10)

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

#ifdef C_CODE

#define SLOW_MEM_SCRATCH   (1920 * 1088 * 2)

l32 VideoMemInitial_c(void **ppvMemHandle, void *pvInputMemParam);
void *VideoMemMalloc_c(void *pvMemHandle, l32 l32MemSize, l32 l32AlignByte);
void *VideoMallocFastMemScratch_c(void *pvMemHandle, l32 l32MemSize, l32 l32AlignByte);
void *VideoMallocSlowMemScratch_c(void *pvMemHandle, l32 l32MemSize, l32 l32AlignByte);
l32 VideoMemFree_c(void *pvMemHandle, void *pvMem);
l32 VideoMemClose_c(void *pvMemHandle);
void* GetDMAHandle_c(void* pvMemHandle);
l32 VideoGetMemInfoBegin_c(void *pvMemHandle, void *pvMemInfo);
l32 VideoGetMemInfoEnd_c(void *pvMemHandle, void *pvMemInfo);
l32 VideoSetMemInfo_c(void *pvMemHandle, void *pvMemInfo);
l32 VideoResumeMemInfo_c(void *pvMemHandle, void *pvMemInfo);

#define VideoMemInitial VideoMemInitial_c
#define VideoMallocFastPersist VideoMemMalloc_c
#define VideoMallocFastScratch VideoMemMalloc_c
#define VideoMallocSlowPersist VideoMemMalloc_c
#define VideoMallocSlowScratch VideoMemMalloc_c
#define VideoSetFastPersistSize 
#define VideoFreeFastPersist VideoMemFree_c
#define VideoFreeFastScratch VideoMemFree_c
#define VideoFreeSlowPersist VideoMemFree_c
#define VideoFreeSlowScratch VideoMemFree_c
#define VideoMemClose VideoMemClose_c
#define GetDMAHandle GetDMAHandle_c
#define VideoMemGetStatus
#define VideoGetMemInfoBegin VideoGetMemInfoBegin_c
#define VideoGetMemInfoEnd VideoGetMemInfoEnd_c
#define VideoSetMemInfo VideoSetMemInfo_c
#define VideoResumeMemInfo VideoResumeMemInfo_c

#elif defined CHIP_DM64XPLUS

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
#endif

#ifdef __cplusplus
}
#endif

#endif
