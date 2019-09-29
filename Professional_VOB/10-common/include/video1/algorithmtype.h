/*****************************************************************************
   ģ����      : algorithm type 
   �ļ���      : algorithmtype.h
   ����ļ�    : 
   �ļ�ʵ�ֹ���: ý�����㷨�������Ͷ���
   ����        : ����
   �汾        : V1.0  Copyright(C) 2009-2010 KDC, All rights reserved.
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
   2009/04/03  1.0         �� ��       ����
******************************************************************************/
#ifndef _ALGORITHM_TYPE_H_
#define _ALGORITHM_TYPE_H_

#ifdef __cplusplus
extern "C" {
#endif   /* __cplusplus */

// BOOL��BOOL32����
#ifdef NEED_TYPE_BOOL32
    typedef int BOOL32;
#endif

#if defined(ARCH_ARMV6_ANDROID) || defined(ARCH_ARMV7_ANDROID) || defined(ARCH_ARMV8_ANDROID)//mac 
    #define ARCH_ARM_ANDROID
#endif

#if defined(ARCH_ARM_LINUX) || defined(ARCH_ARMV6_IOS) || defined(ARCH_ARMV7_IOS) || defined(ARCH_ARMV8_IOS) || defined(ARCH_ARM_ANDROID)
    typedef signed char s8;
#else
    typedef char s8; 
#endif
           
typedef short           s16;
typedef unsigned char   u8;
typedef unsigned short  u16;
typedef double  d64;

#if defined (_TMS320C6400) || defined (ARCH_DM64XPLUS) || defined (ARCH_C674X) //TI DM64Xƽ̨�궨��
    typedef double                  x64;
    typedef long long               s64;
    typedef unsigned long long      u64;
    typedef int                     l32;
    typedef unsigned int            u32;
    
    #define INLINE inline
    #define FAST_CALL 
#elif defined(ARCH_X86_LINUX) || defined(ARCH_ATOM_LINUX) || defined(ARCH_ARM_LINUX)  || defined(ARCH_POWERPC_LINUX)//(x86��ARMƽ̨)Linuxϵͳ
  
    typedef unsigned long long      x64;
    typedef long long               s64;
    typedef unsigned long long      u64;
    typedef long                    l32;
    typedef unsigned long           u32;
    
    #define INLINE inline
    #define FAST_CALL __attribute__((fastcall))
#elif defined(ARCH_X86_64_LINUX) //(x86_64)Linuxϵͳ
  
    typedef unsigned long long      x64;
    typedef long long               s64;
    typedef unsigned long long      u64;
    typedef int                     l32;
    typedef unsigned int            u32;
    
    #define INLINE inline
    #define FAST_CALL __attribute__((fastcall))
#elif defined (ARCH_ARMV8_IOS) || defined(ARCH_ARMV8_ANDROID)
    /*iOS and android 64λϵͳ  */
    typedef unsigned long long  x64;
    typedef long long           s64;
    typedef unsigned long long  u64;
    typedef int                 l32;
    typedef unsigned int        u32;

    #define INLINE inline
    #define FAST_CALL
    #define RESTRICT 
    #define MEM_ALIGN(n) __attribute__((aligned(n)))
    #define MEM_ALIGN_8  MEM_ALIGN(8)
    #define MEM_ALIGN_16  MEM_ALIGN(16)
    #define MEM_ALIGN_64  MEM_ALIGN(64)
#elif defined(ARCH_ARMV6_IOS) || defined(ARCH_ARMV7_IOS) || defined(ARCH_ARM_ANDROID) || defined (ARCH_MAC_LINUX) ||defined(ARCH_ARMV7_ANDROID)
    /*  GCC������ iOSϵͳ  */
    typedef unsigned long long  x64;
    typedef long long           s64;
    typedef unsigned long long  u64;
    typedef long                l32;
    typedef unsigned long       u32;
    
    #define INLINE inline
    #define FAST_CALL
    #define RESTRICT 
    #define MEM_ALIGN(n) __attribute__((aligned(n)))
    #define MEM_ALIGN_8  MEM_ALIGN(8)
    #define MEM_ALIGN_16  MEM_ALIGN(16)
    #define MEM_ALIGN_64  MEM_ALIGN(64)
#else //Ŀǰ����Windowsϵͳ
//    typedef unsigned __int64   x64;
//    typedef __int64            s64;
//    typedef unsigned __int64   u64;
    typedef long               l32;
    typedef unsigned long      u32;
    
    #define INLINE __inline
    #define FAST_CALL __fastcall
#endif

//Ubuntuϵͳ����
#ifdef ARCH_ARM_UBUNTU
    typedef signed char     s8;
    typedef signed short    s16;
//    typedef signed __int64  s64;
#endif

#ifndef TRUE
    #define TRUE    1
#endif

#ifndef FALSE
    #define FALSE   0
#endif

#ifndef NULL
  #ifdef  __cplusplus
    #define NULL    0
  #else
    #define NULL    ((void *)0)
  #endif
#endif

#ifndef ARCH_ARM_WINCE
//typedef int BOOL;
#if !defined(TYPE_BOOL) && !defined(__INCvxTypesh)
    typedef int BOOL, *PBOOL;
    #define TRUE 1
    #define FALSE 0
    #define TYPE_BOOL
#endif /* BOOL */

#if !defined(TYPE_SCODE)
    typedef int SCODE, *PSCODE;
    #define TYPE_SCODE
#endif /* SCODE */

#endif

#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* _ALGORITHM_TYPE_H_ */
