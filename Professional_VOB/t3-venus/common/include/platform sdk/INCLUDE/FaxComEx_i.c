

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0361 */
/* Compiler settings for faxcomex.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if !defined(_M_IA64) && !defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IFaxJobStatus,0x8B86F485,0xFD7F,0x4824,0x88,0x6B,0x40,0xC5,0xCA,0xA6,0x17,0xCC);


MIDL_DEFINE_GUID(IID, IID_IFaxServer,0x475B6469,0x90A5,0x4878,0xA5,0x77,0x17,0xA8,0x6E,0x8E,0x34,0x62);


MIDL_DEFINE_GUID(IID, IID_IFaxDeviceProviders,0x9FB76F62,0x4C7E,0x43A5,0xB6,0xFD,0x50,0x28,0x93,0xF7,0xE1,0x3E);


MIDL_DEFINE_GUID(IID, IID_IFaxDevices,0x9E46783E,0xF34F,0x482E,0xA3,0x60,0x04,0x16,0xBE,0xCB,0xBD,0x96);


MIDL_DEFINE_GUID(IID, IID_IFaxInboundRouting,0x8148C20F,0x9D52,0x45B1,0xBF,0x96,0x38,0xFC,0x12,0x71,0x35,0x27);


MIDL_DEFINE_GUID(IID, IID_IFaxFolders,0xDCE3B2A8,0xA7AB,0x42BC,0x9D,0x0A,0x31,0x49,0x45,0x72,0x61,0xA0);


MIDL_DEFINE_GUID(IID, IID_IFaxLoggingOptions,0x34E64FB9,0x6B31,0x4D32,0x8B,0x27,0xD2,0x86,0xC0,0xC3,0x36,0x06);


MIDL_DEFINE_GUID(IID, IID_IFaxActivity,0x4B106F97,0x3DF5,0x40F2,0xBC,0x3C,0x44,0xCB,0x81,0x15,0xEB,0xDF);


MIDL_DEFINE_GUID(IID, IID_IFaxOutboundRouting,0x25DC05A4,0x9909,0x41BD,0xA9,0x5B,0x7E,0x5D,0x1D,0xEC,0x1D,0x43);


MIDL_DEFINE_GUID(IID, IID_IFaxReceiptOptions,0x378EFAEB,0x5FCB,0x4AFB,0xB2,0xEE,0xE1,0x6E,0x80,0x61,0x44,0x87);


MIDL_DEFINE_GUID(IID, IID_IFaxSecurity,0x77B508C1,0x09C0,0x47A2,0x91,0xEB,0xFC,0xE7,0xFD,0xF2,0x69,0x0E);


MIDL_DEFINE_GUID(IID, IID_IFaxDocument,0xB207A246,0x09E3,0x4A4E,0xA7,0xDC,0xFE,0xA3,0x1D,0x29,0x45,0x8F);


MIDL_DEFINE_GUID(IID, IID_IFaxSender,0x0D879D7D,0xF57A,0x4CC6,0xA6,0xF9,0x3E,0xE5,0xD5,0x27,0xB4,0x6A);


MIDL_DEFINE_GUID(IID, IID_IFaxRecipient,0x9A3DA3A0,0x538D,0x42b6,0x94,0x44,0xAA,0xA5,0x7D,0x0C,0xE2,0xBC);


MIDL_DEFINE_GUID(IID, IID_IFaxRecipients,0xB9C9DE5A,0x894E,0x4492,0x9F,0xA3,0x08,0xC6,0x27,0xC1,0x1D,0x5D);


MIDL_DEFINE_GUID(IID, IID_IFaxIncomingArchive,0x76062CC7,0xF714,0x4FBD,0xAA,0x06,0xED,0x6E,0x4A,0x4B,0x70,0xF3);


MIDL_DEFINE_GUID(IID, IID_IFaxIncomingQueue,0x902E64EF,0x8FD8,0x4B75,0x97,0x25,0x60,0x14,0xDF,0x16,0x15,0x45);


MIDL_DEFINE_GUID(IID, IID_IFaxOutgoingArchive,0xC9C28F40,0x8D80,0x4E53,0x81,0x0F,0x9A,0x79,0x91,0x9B,0x49,0xFD);


MIDL_DEFINE_GUID(IID, IID_IFaxOutgoingQueue,0x80B1DF24,0xD9AC,0x4333,0xB3,0x73,0x48,0x7C,0xED,0xC8,0x0C,0xE5);


MIDL_DEFINE_GUID(IID, IID_IFaxIncomingMessageIterator,0xFD73ECC4,0x6F06,0x4F52,0x82,0xA8,0xF7,0xBA,0x06,0xAE,0x31,0x08);


MIDL_DEFINE_GUID(IID, IID_IFaxIncomingMessage,0x7CAB88FA,0x2EF9,0x4851,0xB2,0xF3,0x1D,0x14,0x8F,0xED,0x84,0x47);


MIDL_DEFINE_GUID(IID, IID_IFaxOutgoingJobs,0x2C56D8E6,0x8C2F,0x4573,0x94,0x4C,0xE5,0x05,0xF8,0xF5,0xAE,0xED);


MIDL_DEFINE_GUID(IID, IID_IFaxOutgoingJob,0x6356DAAD,0x6614,0x4583,0xBF,0x7A,0x3A,0xD6,0x7B,0xBF,0xC7,0x1C);


MIDL_DEFINE_GUID(IID, IID_IFaxOutgoingMessageIterator,0xF5EC5D4F,0xB840,0x432F,0x99,0x80,0x11,0x2F,0xE4,0x2A,0x9B,0x7A);


MIDL_DEFINE_GUID(IID, IID_IFaxOutgoingMessage,0xF0EA35DE,0xCAA5,0x4A7C,0x82,0xC7,0x2B,0x60,0xBA,0x5F,0x2B,0xE2);


MIDL_DEFINE_GUID(IID, IID_IFaxIncomingJobs,0x011F04E9,0x4FD6,0x4C23,0x95,0x13,0xB6,0xB6,0x6B,0xB2,0x6B,0xE9);


MIDL_DEFINE_GUID(IID, IID_IFaxIncomingJob,0x207529E6,0x654A,0x4916,0x9F,0x88,0x4D,0x23,0x2E,0xE8,0xA1,0x07);


MIDL_DEFINE_GUID(IID, IID_IFaxDeviceProvider,0x290EAC63,0x83EC,0x449C,0x84,0x17,0xF1,0x48,0xDF,0x8C,0x68,0x2A);


MIDL_DEFINE_GUID(IID, IID_IFaxDevice,0x49306C59,0xB52E,0x4867,0x9D,0xF4,0xCA,0x58,0x41,0xC9,0x56,0xD0);


MIDL_DEFINE_GUID(IID, IID_IFaxActivityLogging,0x1E29078B,0x5A69,0x497B,0x95,0x92,0x49,0xB7,0xE7,0xFA,0xDD,0xB5);


MIDL_DEFINE_GUID(IID, IID_IFaxEventLogging,0x0880D965,0x20E8,0x42E4,0x8E,0x17,0x94,0x4F,0x19,0x2C,0xAA,0xD4);


MIDL_DEFINE_GUID(IID, IID_IFaxOutboundRoutingGroups,0x235CBEF7,0xC2DE,0x4BFD,0xB8,0xDA,0x75,0x09,0x7C,0x82,0xC8,0x7F);


MIDL_DEFINE_GUID(IID, IID_IFaxOutboundRoutingGroup,0xCA6289A1,0x7E25,0x4F87,0x9A,0x0B,0x93,0x36,0x57,0x34,0x96,0x2C);


MIDL_DEFINE_GUID(IID, IID_IFaxDeviceIds,0x2F0F813F,0x4CE9,0x443E,0x8C,0xA1,0x73,0x8C,0xFA,0xEE,0xE1,0x49);


MIDL_DEFINE_GUID(IID, IID_IFaxOutboundRoutingRules,0xDCEFA1E7,0xAE7D,0x4ED6,0x85,0x21,0x36,0x9E,0xDC,0xCA,0x51,0x20);


MIDL_DEFINE_GUID(IID, IID_IFaxOutboundRoutingRule,0xE1F795D5,0x07C2,0x469F,0xB0,0x27,0xAC,0xAC,0xC2,0x32,0x19,0xDA);


MIDL_DEFINE_GUID(IID, IID_IFaxInboundRoutingExtensions,0x2F6C9673,0x7B26,0x42DE,0x8E,0xB0,0x91,0x5D,0xCD,0x2A,0x4F,0x4C);


MIDL_DEFINE_GUID(IID, IID_IFaxInboundRoutingExtension,0x885B5E08,0xC26C,0x4EF9,0xAF,0x83,0x51,0x58,0x0A,0x75,0x0B,0xE1);


MIDL_DEFINE_GUID(IID, IID_IFaxInboundRoutingMethods,0x783FCA10,0x8908,0x4473,0x9D,0x69,0xF6,0x7F,0xBE,0xA0,0xC6,0xB9);


MIDL_DEFINE_GUID(IID, IID_IFaxInboundRoutingMethod,0x45700061,0xAD9D,0x4776,0xA8,0xC4,0x64,0x06,0x54,0x92,0xCF,0x4B);


MIDL_DEFINE_GUID(IID, LIBID_FAXCOMEXLib,0x2BF34C1A,0x8CAC,0x419F,0x85,0x47,0x32,0xFD,0xF6,0x50,0x5D,0xB8);


MIDL_DEFINE_GUID(IID, DIID_IFaxServerNotify,0x2E037B27,0xCF8A,0x4abd,0xB1,0xE0,0x57,0x04,0x94,0x3B,0xEA,0x6F);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxServer,0xCDA8ACB0,0x8CF5,0x4F6C,0x9B,0xA2,0x59,0x31,0xD4,0x0C,0x8C,0xAE);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxDeviceProviders,0xEB8FE768,0x875A,0x4F5F,0x82,0xC5,0x03,0xF2,0x3A,0xAC,0x1B,0xD7);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxDevices,0x5589E28E,0x23CB,0x4919,0x88,0x08,0xE6,0x10,0x18,0x46,0xE8,0x0D);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxInboundRouting,0xE80248ED,0xAD65,0x4218,0x81,0x08,0x99,0x19,0x24,0xD4,0xE7,0xED);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxFolders,0xC35211D7,0x5776,0x48CB,0xAF,0x44,0xC3,0x1B,0xE3,0xB2,0xCF,0xE5);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxLoggingOptions,0x1BF9EEA6,0xECE0,0x4785,0xA1,0x8B,0xDE,0x56,0xE9,0xEE,0xF9,0x6A);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxActivity,0xCFEF5D0E,0xE84D,0x462E,0xAA,0xBB,0x87,0xD3,0x1E,0xB0,0x4F,0xEF);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxOutboundRouting,0xC81B385E,0xB869,0x4AFD,0x86,0xC0,0x61,0x64,0x98,0xED,0x9B,0xE2);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxReceiptOptions,0x6982487B,0x227B,0x4C96,0xA6,0x1C,0x24,0x83,0x48,0xB0,0x5A,0xB6);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxSecurity,0x10C4DDDE,0xABF0,0x43DF,0x96,0x4F,0x7F,0x3A,0xC2,0x1A,0x4C,0x7B);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxDocument,0x0F3F9F91,0xC838,0x415E,0xA4,0xF3,0x3E,0x82,0x8C,0xA4,0x45,0xE0);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxSender,0x265D84D0,0x1850,0x4360,0xB7,0xC8,0x75,0x8B,0xBB,0x5F,0x0B,0x96);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxRecipients,0xEA9BDF53,0x10A9,0x4D4F,0xA0,0x67,0x63,0xC8,0xF8,0x4F,0x01,0xB0);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxIncomingArchive,0x8426C56A,0x35A1,0x4C6F,0xAF,0x93,0xFC,0x95,0x24,0x22,0xE2,0xC2);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxIncomingQueue,0x69131717,0xF3F1,0x40E3,0x80,0x9D,0xA6,0xCB,0xF7,0xBD,0x85,0xE5);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxOutgoingArchive,0x43C28403,0xE04F,0x474D,0x99,0x0C,0xB9,0x46,0x69,0x14,0x8F,0x59);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxOutgoingQueue,0x7421169E,0x8C43,0x4B0D,0xBB,0x16,0x64,0x5C,0x8F,0xA4,0x03,0x57);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxIncomingMessageIterator,0x6088E1D8,0x3FC8,0x45C2,0x87,0xB1,0x90,0x9A,0x29,0x60,0x7E,0xA9);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxIncomingMessage,0x1932FCF7,0x9D43,0x4D5A,0x89,0xFF,0x03,0x86,0x1B,0x32,0x17,0x36);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxOutgoingJobs,0x92BF2A6C,0x37BE,0x43FA,0xA3,0x7D,0xCB,0x0E,0x5F,0x75,0x3B,0x35);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxOutgoingJob,0x71BB429C,0x0EF9,0x4915,0xBE,0xC5,0xA5,0xD8,0x97,0xA3,0xE9,0x24);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxOutgoingMessageIterator,0x8A3224D0,0xD30B,0x49DE,0x98,0x13,0xCB,0x38,0x57,0x90,0xFB,0xBB);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxOutgoingMessage,0x91B4A378,0x4AD8,0x4AEF,0xA4,0xDC,0x97,0xD9,0x6E,0x93,0x9A,0x3A);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxIncomingJobs,0xA1BB8A43,0x8866,0x4FB7,0xA1,0x5D,0x62,0x66,0xC8,0x75,0xA5,0xCC);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxIncomingJob,0xC47311EC,0xAE32,0x41B8,0xAE,0x4B,0x3E,0xAE,0x06,0x29,0xD0,0xC9);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxDeviceProvider,0x17CF1AA3,0xF5EB,0x484A,0x9C,0x9A,0x44,0x40,0xA5,0xBA,0xAB,0xFC);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxDevice,0x59E3A5B2,0xD676,0x484B,0xA6,0xDE,0x72,0x0B,0xFA,0x89,0xB5,0xAF);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxActivityLogging,0xF0A0294E,0x3BBD,0x48B8,0x8F,0x13,0x8C,0x59,0x1A,0x55,0xBD,0xBC);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxEventLogging,0xA6850930,0xA0F6,0x4A6F,0x95,0xB7,0xDB,0x2E,0xBF,0x3D,0x02,0xE3);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxOutboundRoutingGroups,0xCCBEA1A5,0xE2B4,0x4B57,0x94,0x21,0xB0,0x4B,0x62,0x89,0x46,0x4B);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxOutboundRoutingGroup,0x0213F3E0,0x6791,0x4D77,0xA2,0x71,0x04,0xD2,0x35,0x7C,0x50,0xD6);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxDeviceIds,0xCDC539EA,0x7277,0x460E,0x8D,0xE0,0x48,0xA0,0xA5,0x76,0x0D,0x1F);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxOutboundRoutingRules,0xD385BECA,0xE624,0x4473,0xBF,0xAA,0x9F,0x40,0x00,0x83,0x1F,0x54);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxOutboundRoutingRule,0x6549EEBF,0x08D1,0x475A,0x82,0x8B,0x3B,0xF1,0x05,0x95,0x2F,0xA0);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxInboundRoutingExtensions,0x189A48ED,0x623C,0x4C0D,0x80,0xF2,0xD6,0x6C,0x7B,0x9E,0xFE,0xC2);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxInboundRoutingExtension,0x1D7DFB51,0x7207,0x4436,0xA0,0xD9,0x24,0xE3,0x2E,0xE5,0x69,0x88);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxInboundRoutingMethods,0x25FCB76A,0xB750,0x4B82,0x92,0x66,0xFB,0xBB,0xAE,0x89,0x22,0xBA);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxInboundRoutingMethod,0x4B9FD75C,0x0194,0x4B72,0x9C,0xE5,0x02,0xA8,0x20,0x5A,0xC7,0xD4);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxJobStatus,0x7BF222F4,0xBE8D,0x442f,0x84,0x1D,0x61,0x32,0x74,0x24,0x23,0xBB);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxRecipient,0x60BF3301,0x7DF8,0x4bd8,0x91,0x48,0x7B,0x58,0x01,0xF9,0xEF,0xDF);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/



/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0361 */
/* Compiler settings for faxcomex.idl:
    Oicf, W1, Zp8, env=Win64 (32b run,appending)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if defined(_M_IA64) || defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IFaxJobStatus,0x8B86F485,0xFD7F,0x4824,0x88,0x6B,0x40,0xC5,0xCA,0xA6,0x17,0xCC);


MIDL_DEFINE_GUID(IID, IID_IFaxServer,0x475B6469,0x90A5,0x4878,0xA5,0x77,0x17,0xA8,0x6E,0x8E,0x34,0x62);


MIDL_DEFINE_GUID(IID, IID_IFaxDeviceProviders,0x9FB76F62,0x4C7E,0x43A5,0xB6,0xFD,0x50,0x28,0x93,0xF7,0xE1,0x3E);


MIDL_DEFINE_GUID(IID, IID_IFaxDevices,0x9E46783E,0xF34F,0x482E,0xA3,0x60,0x04,0x16,0xBE,0xCB,0xBD,0x96);


MIDL_DEFINE_GUID(IID, IID_IFaxInboundRouting,0x8148C20F,0x9D52,0x45B1,0xBF,0x96,0x38,0xFC,0x12,0x71,0x35,0x27);


MIDL_DEFINE_GUID(IID, IID_IFaxFolders,0xDCE3B2A8,0xA7AB,0x42BC,0x9D,0x0A,0x31,0x49,0x45,0x72,0x61,0xA0);


MIDL_DEFINE_GUID(IID, IID_IFaxLoggingOptions,0x34E64FB9,0x6B31,0x4D32,0x8B,0x27,0xD2,0x86,0xC0,0xC3,0x36,0x06);


MIDL_DEFINE_GUID(IID, IID_IFaxActivity,0x4B106F97,0x3DF5,0x40F2,0xBC,0x3C,0x44,0xCB,0x81,0x15,0xEB,0xDF);


MIDL_DEFINE_GUID(IID, IID_IFaxOutboundRouting,0x25DC05A4,0x9909,0x41BD,0xA9,0x5B,0x7E,0x5D,0x1D,0xEC,0x1D,0x43);


MIDL_DEFINE_GUID(IID, IID_IFaxReceiptOptions,0x378EFAEB,0x5FCB,0x4AFB,0xB2,0xEE,0xE1,0x6E,0x80,0x61,0x44,0x87);


MIDL_DEFINE_GUID(IID, IID_IFaxSecurity,0x77B508C1,0x09C0,0x47A2,0x91,0xEB,0xFC,0xE7,0xFD,0xF2,0x69,0x0E);


MIDL_DEFINE_GUID(IID, IID_IFaxDocument,0xB207A246,0x09E3,0x4A4E,0xA7,0xDC,0xFE,0xA3,0x1D,0x29,0x45,0x8F);


MIDL_DEFINE_GUID(IID, IID_IFaxSender,0x0D879D7D,0xF57A,0x4CC6,0xA6,0xF9,0x3E,0xE5,0xD5,0x27,0xB4,0x6A);


MIDL_DEFINE_GUID(IID, IID_IFaxRecipient,0x9A3DA3A0,0x538D,0x42b6,0x94,0x44,0xAA,0xA5,0x7D,0x0C,0xE2,0xBC);


MIDL_DEFINE_GUID(IID, IID_IFaxRecipients,0xB9C9DE5A,0x894E,0x4492,0x9F,0xA3,0x08,0xC6,0x27,0xC1,0x1D,0x5D);


MIDL_DEFINE_GUID(IID, IID_IFaxIncomingArchive,0x76062CC7,0xF714,0x4FBD,0xAA,0x06,0xED,0x6E,0x4A,0x4B,0x70,0xF3);


MIDL_DEFINE_GUID(IID, IID_IFaxIncomingQueue,0x902E64EF,0x8FD8,0x4B75,0x97,0x25,0x60,0x14,0xDF,0x16,0x15,0x45);


MIDL_DEFINE_GUID(IID, IID_IFaxOutgoingArchive,0xC9C28F40,0x8D80,0x4E53,0x81,0x0F,0x9A,0x79,0x91,0x9B,0x49,0xFD);


MIDL_DEFINE_GUID(IID, IID_IFaxOutgoingQueue,0x80B1DF24,0xD9AC,0x4333,0xB3,0x73,0x48,0x7C,0xED,0xC8,0x0C,0xE5);


MIDL_DEFINE_GUID(IID, IID_IFaxIncomingMessageIterator,0xFD73ECC4,0x6F06,0x4F52,0x82,0xA8,0xF7,0xBA,0x06,0xAE,0x31,0x08);


MIDL_DEFINE_GUID(IID, IID_IFaxIncomingMessage,0x7CAB88FA,0x2EF9,0x4851,0xB2,0xF3,0x1D,0x14,0x8F,0xED,0x84,0x47);


MIDL_DEFINE_GUID(IID, IID_IFaxOutgoingJobs,0x2C56D8E6,0x8C2F,0x4573,0x94,0x4C,0xE5,0x05,0xF8,0xF5,0xAE,0xED);


MIDL_DEFINE_GUID(IID, IID_IFaxOutgoingJob,0x6356DAAD,0x6614,0x4583,0xBF,0x7A,0x3A,0xD6,0x7B,0xBF,0xC7,0x1C);


MIDL_DEFINE_GUID(IID, IID_IFaxOutgoingMessageIterator,0xF5EC5D4F,0xB840,0x432F,0x99,0x80,0x11,0x2F,0xE4,0x2A,0x9B,0x7A);


MIDL_DEFINE_GUID(IID, IID_IFaxOutgoingMessage,0xF0EA35DE,0xCAA5,0x4A7C,0x82,0xC7,0x2B,0x60,0xBA,0x5F,0x2B,0xE2);


MIDL_DEFINE_GUID(IID, IID_IFaxIncomingJobs,0x011F04E9,0x4FD6,0x4C23,0x95,0x13,0xB6,0xB6,0x6B,0xB2,0x6B,0xE9);


MIDL_DEFINE_GUID(IID, IID_IFaxIncomingJob,0x207529E6,0x654A,0x4916,0x9F,0x88,0x4D,0x23,0x2E,0xE8,0xA1,0x07);


MIDL_DEFINE_GUID(IID, IID_IFaxDeviceProvider,0x290EAC63,0x83EC,0x449C,0x84,0x17,0xF1,0x48,0xDF,0x8C,0x68,0x2A);


MIDL_DEFINE_GUID(IID, IID_IFaxDevice,0x49306C59,0xB52E,0x4867,0x9D,0xF4,0xCA,0x58,0x41,0xC9,0x56,0xD0);


MIDL_DEFINE_GUID(IID, IID_IFaxActivityLogging,0x1E29078B,0x5A69,0x497B,0x95,0x92,0x49,0xB7,0xE7,0xFA,0xDD,0xB5);


MIDL_DEFINE_GUID(IID, IID_IFaxEventLogging,0x0880D965,0x20E8,0x42E4,0x8E,0x17,0x94,0x4F,0x19,0x2C,0xAA,0xD4);


MIDL_DEFINE_GUID(IID, IID_IFaxOutboundRoutingGroups,0x235CBEF7,0xC2DE,0x4BFD,0xB8,0xDA,0x75,0x09,0x7C,0x82,0xC8,0x7F);


MIDL_DEFINE_GUID(IID, IID_IFaxOutboundRoutingGroup,0xCA6289A1,0x7E25,0x4F87,0x9A,0x0B,0x93,0x36,0x57,0x34,0x96,0x2C);


MIDL_DEFINE_GUID(IID, IID_IFaxDeviceIds,0x2F0F813F,0x4CE9,0x443E,0x8C,0xA1,0x73,0x8C,0xFA,0xEE,0xE1,0x49);


MIDL_DEFINE_GUID(IID, IID_IFaxOutboundRoutingRules,0xDCEFA1E7,0xAE7D,0x4ED6,0x85,0x21,0x36,0x9E,0xDC,0xCA,0x51,0x20);


MIDL_DEFINE_GUID(IID, IID_IFaxOutboundRoutingRule,0xE1F795D5,0x07C2,0x469F,0xB0,0x27,0xAC,0xAC,0xC2,0x32,0x19,0xDA);


MIDL_DEFINE_GUID(IID, IID_IFaxInboundRoutingExtensions,0x2F6C9673,0x7B26,0x42DE,0x8E,0xB0,0x91,0x5D,0xCD,0x2A,0x4F,0x4C);


MIDL_DEFINE_GUID(IID, IID_IFaxInboundRoutingExtension,0x885B5E08,0xC26C,0x4EF9,0xAF,0x83,0x51,0x58,0x0A,0x75,0x0B,0xE1);


MIDL_DEFINE_GUID(IID, IID_IFaxInboundRoutingMethods,0x783FCA10,0x8908,0x4473,0x9D,0x69,0xF6,0x7F,0xBE,0xA0,0xC6,0xB9);


MIDL_DEFINE_GUID(IID, IID_IFaxInboundRoutingMethod,0x45700061,0xAD9D,0x4776,0xA8,0xC4,0x64,0x06,0x54,0x92,0xCF,0x4B);


MIDL_DEFINE_GUID(IID, LIBID_FAXCOMEXLib,0x2BF34C1A,0x8CAC,0x419F,0x85,0x47,0x32,0xFD,0xF6,0x50,0x5D,0xB8);


MIDL_DEFINE_GUID(IID, DIID_IFaxServerNotify,0x2E037B27,0xCF8A,0x4abd,0xB1,0xE0,0x57,0x04,0x94,0x3B,0xEA,0x6F);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxServer,0xCDA8ACB0,0x8CF5,0x4F6C,0x9B,0xA2,0x59,0x31,0xD4,0x0C,0x8C,0xAE);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxDeviceProviders,0xEB8FE768,0x875A,0x4F5F,0x82,0xC5,0x03,0xF2,0x3A,0xAC,0x1B,0xD7);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxDevices,0x5589E28E,0x23CB,0x4919,0x88,0x08,0xE6,0x10,0x18,0x46,0xE8,0x0D);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxInboundRouting,0xE80248ED,0xAD65,0x4218,0x81,0x08,0x99,0x19,0x24,0xD4,0xE7,0xED);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxFolders,0xC35211D7,0x5776,0x48CB,0xAF,0x44,0xC3,0x1B,0xE3,0xB2,0xCF,0xE5);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxLoggingOptions,0x1BF9EEA6,0xECE0,0x4785,0xA1,0x8B,0xDE,0x56,0xE9,0xEE,0xF9,0x6A);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxActivity,0xCFEF5D0E,0xE84D,0x462E,0xAA,0xBB,0x87,0xD3,0x1E,0xB0,0x4F,0xEF);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxOutboundRouting,0xC81B385E,0xB869,0x4AFD,0x86,0xC0,0x61,0x64,0x98,0xED,0x9B,0xE2);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxReceiptOptions,0x6982487B,0x227B,0x4C96,0xA6,0x1C,0x24,0x83,0x48,0xB0,0x5A,0xB6);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxSecurity,0x10C4DDDE,0xABF0,0x43DF,0x96,0x4F,0x7F,0x3A,0xC2,0x1A,0x4C,0x7B);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxDocument,0x0F3F9F91,0xC838,0x415E,0xA4,0xF3,0x3E,0x82,0x8C,0xA4,0x45,0xE0);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxSender,0x265D84D0,0x1850,0x4360,0xB7,0xC8,0x75,0x8B,0xBB,0x5F,0x0B,0x96);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxRecipients,0xEA9BDF53,0x10A9,0x4D4F,0xA0,0x67,0x63,0xC8,0xF8,0x4F,0x01,0xB0);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxIncomingArchive,0x8426C56A,0x35A1,0x4C6F,0xAF,0x93,0xFC,0x95,0x24,0x22,0xE2,0xC2);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxIncomingQueue,0x69131717,0xF3F1,0x40E3,0x80,0x9D,0xA6,0xCB,0xF7,0xBD,0x85,0xE5);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxOutgoingArchive,0x43C28403,0xE04F,0x474D,0x99,0x0C,0xB9,0x46,0x69,0x14,0x8F,0x59);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxOutgoingQueue,0x7421169E,0x8C43,0x4B0D,0xBB,0x16,0x64,0x5C,0x8F,0xA4,0x03,0x57);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxIncomingMessageIterator,0x6088E1D8,0x3FC8,0x45C2,0x87,0xB1,0x90,0x9A,0x29,0x60,0x7E,0xA9);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxIncomingMessage,0x1932FCF7,0x9D43,0x4D5A,0x89,0xFF,0x03,0x86,0x1B,0x32,0x17,0x36);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxOutgoingJobs,0x92BF2A6C,0x37BE,0x43FA,0xA3,0x7D,0xCB,0x0E,0x5F,0x75,0x3B,0x35);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxOutgoingJob,0x71BB429C,0x0EF9,0x4915,0xBE,0xC5,0xA5,0xD8,0x97,0xA3,0xE9,0x24);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxOutgoingMessageIterator,0x8A3224D0,0xD30B,0x49DE,0x98,0x13,0xCB,0x38,0x57,0x90,0xFB,0xBB);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxOutgoingMessage,0x91B4A378,0x4AD8,0x4AEF,0xA4,0xDC,0x97,0xD9,0x6E,0x93,0x9A,0x3A);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxIncomingJobs,0xA1BB8A43,0x8866,0x4FB7,0xA1,0x5D,0x62,0x66,0xC8,0x75,0xA5,0xCC);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxIncomingJob,0xC47311EC,0xAE32,0x41B8,0xAE,0x4B,0x3E,0xAE,0x06,0x29,0xD0,0xC9);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxDeviceProvider,0x17CF1AA3,0xF5EB,0x484A,0x9C,0x9A,0x44,0x40,0xA5,0xBA,0xAB,0xFC);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxDevice,0x59E3A5B2,0xD676,0x484B,0xA6,0xDE,0x72,0x0B,0xFA,0x89,0xB5,0xAF);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxActivityLogging,0xF0A0294E,0x3BBD,0x48B8,0x8F,0x13,0x8C,0x59,0x1A,0x55,0xBD,0xBC);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxEventLogging,0xA6850930,0xA0F6,0x4A6F,0x95,0xB7,0xDB,0x2E,0xBF,0x3D,0x02,0xE3);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxOutboundRoutingGroups,0xCCBEA1A5,0xE2B4,0x4B57,0x94,0x21,0xB0,0x4B,0x62,0x89,0x46,0x4B);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxOutboundRoutingGroup,0x0213F3E0,0x6791,0x4D77,0xA2,0x71,0x04,0xD2,0x35,0x7C,0x50,0xD6);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxDeviceIds,0xCDC539EA,0x7277,0x460E,0x8D,0xE0,0x48,0xA0,0xA5,0x76,0x0D,0x1F);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxOutboundRoutingRules,0xD385BECA,0xE624,0x4473,0xBF,0xAA,0x9F,0x40,0x00,0x83,0x1F,0x54);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxOutboundRoutingRule,0x6549EEBF,0x08D1,0x475A,0x82,0x8B,0x3B,0xF1,0x05,0x95,0x2F,0xA0);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxInboundRoutingExtensions,0x189A48ED,0x623C,0x4C0D,0x80,0xF2,0xD6,0x6C,0x7B,0x9E,0xFE,0xC2);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxInboundRoutingExtension,0x1D7DFB51,0x7207,0x4436,0xA0,0xD9,0x24,0xE3,0x2E,0xE5,0x69,0x88);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxInboundRoutingMethods,0x25FCB76A,0xB750,0x4B82,0x92,0x66,0xFB,0xBB,0xAE,0x89,0x22,0xBA);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxInboundRoutingMethod,0x4B9FD75C,0x0194,0x4B72,0x9C,0xE5,0x02,0xA8,0x20,0x5A,0xC7,0xD4);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxJobStatus,0x7BF222F4,0xBE8D,0x442f,0x84,0x1D,0x61,0x32,0x74,0x24,0x23,0xBB);


MIDL_DEFINE_GUID(CLSID, CLSID_FaxRecipient,0x60BF3301,0x7DF8,0x4bd8,0x91,0x48,0x7B,0x58,0x01,0xF9,0xEF,0xDF);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* defined(_M_IA64) || defined(_M_AMD64)*/

