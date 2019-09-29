#ifndef _MON_MSG_H_
#define _MON_MSG_H_

#include "kdvtype.h"
//#include "kdmconst.h"
#include "osp.h"

//#include "kdmstruct.h"

#ifdef _MSC_VER
#pragma pack( push )
#pragma pack( 1 )
#endif

#ifndef min
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#endif

#define LEN_KDM_NO 31
static u32 g_dwSerialNo = 1; // ��ˮ��

#define MON_GEP_MAX_SERIAL (u32)0xFFFFFFF

#define MON_OSP_MSG_MAX_LEN (u16)(0x7000)

struct TOspMonMsgHead
{
    u32  m_dwSerialNo;                //��Ϣ��ˮ��
    
    char m_szSrcID[LEN_KDM_NO + 1]; //ԴID
    char m_szDstID[LEN_KDM_NO + 1]; //Ŀ��ID
    
    u32 m_dwSessID;                 //�ỰID
    
    u16  m_wEventId;                //��ϢID
    u16  m_wTimeout;                //��Ϣ��ʱʱ��
    u32  m_dwErrorCode;              //��Ϣ������
    u16  m_wMsgBodyLen;             //��Ϣ�峤��
    
    u32  m_dwReserved1;	            //����1
    u32  m_dwReserved2;	            //����2
}
#ifndef WIN32
__attribute__ ((packed))
#endif
;

#define MON_MSG_BODY_OFFSET sizeof(TOspMonMsgHead)

#define MON_OSP_MSG_BODY_MAX_LEN (MON_OSP_MSG_MAX_LEN - MON_MSG_BODY_OFFSET)

class CMonMsg
{
public:
    CMonMsg(void)
    {
        memset(m_abyBuffer, 0, MON_OSP_MSG_MAX_LEN);
        SetSerialNo();
    }
    
    CMonMsg& operator= (CMonMsg& cMsg)
    {
        memcpy(m_abyBuffer, cMsg.m_abyBuffer, cMsg.GetMonMsgLen());
        return (*this);
    }
    
    CMonMsg(u8 * const pbyMsg, u16 wMsgLen)
    {
        memset(m_abyBuffer, 0, MON_OSP_MSG_MAX_LEN);
        
        if( wMsgLen < MON_MSG_BODY_OFFSET || pbyMsg == NULL )
            return;
        
        TOspMonMsgHead *m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
        wMsgLen = min( wMsgLen, sizeof( m_abyBuffer ) );
        memcpy( m_abyBuffer, pbyMsg, wMsgLen );
        m_ptMsgHead->m_wMsgBodyLen = htons(wMsgLen - MON_MSG_BODY_OFFSET);
    }
    
//    //����SrcID��DstID
//    void ReverseID()
//    {
//        TKDMNO tSrcId = GetSrcKdmNo();
//        SetSrcID(GetDstKdmNo().GetNOString());
//        SetDstID(tSrcId.GetNOString());
//    }
    
    //////////////////////////////////////////////////////////////////////////
    // ����: ClearMsgHead
    // ����: �����Ϣͷ��
    // ԭ��: void ClearMsgHead()
    // ����: 
    // 
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    void ClearMsgHead(void)                //��Ϣͷ����
    {
        memset(m_abyBuffer, 0, MON_MSG_BODY_OFFSET);
    }
    
    //////////////////////////////////////////////////////////////////////////
    // ����: ClearMsgBody
    // ����: �����Ϣ��ȫ������
    // ԭ��: void ClearMsgBody()
    // ����: 
    // 
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    void ClearMsgBody(void)                //�����Ч��Ϣ��
    {
        TOspMonMsgHead* m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
        if(m_ptMsgHead == NULL)
            return;
        
        memset(&m_abyBuffer[MON_MSG_BODY_OFFSET], 0, ntohs(m_ptMsgHead->m_wMsgBodyLen));
        
        m_ptMsgHead->m_wMsgBodyLen = 0;
    }
    
    //////////////////////////////////////////////////////////////////////////
    // ����: ClearMsg
    // ����: ���������Ϣ����
    // ԭ��: void ClearMsg()
    // ����: 
    // 
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    void ClearMsg(void)
    {
        memset(m_abyBuffer, 0, MON_OSP_MSG_MAX_LEN);
    }
    
    //////////////////////////////////////////////////////////////////////////
    // ����: GetSerialNo
    // ����: ��ȡ��ˮ��
    // ԭ��: U32 GetSerialNo() const
    // ����: 
    // 
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    u32  GetSerialNo(void) const       //��ȡ��ˮ����Ϣ
    {        
        TOspMonMsgHead *m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
        if(m_ptMsgHead == NULL)
            return 0;
        return ntohl(m_ptMsgHead->m_dwSerialNo);
    }
    
    //////////////////////////////////////////////////////////////////////////
    // ����: SetSerialNo
    // ����: ���õ�ǰ��Ϣ����ˮ��
    // ԭ��: void SetSerialNo(u32 dwSerialNo) // [in] ��ˮ��
    // ����: 
    // [in] dwSerialNo: ��ǰ����ˮ��
    // ��ע: �÷���һ�㲻ʹ��
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    void SetSerialNo(u32 dwSerialNo)    //������ˮ����Ϣ
    {
        TOspMonMsgHead *m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
        if(m_ptMsgHead != NULL)
        {
            m_ptMsgHead->m_dwSerialNo = htonl(dwSerialNo);
        }
    }
    
    //////////////////////////////////////////////////////////////////////////
    // ����: SetSerialNo
    // ����: ������Ϣ����ˮ��
    // ԭ��: void SetSerialNo()
    // ����: 
    // 
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    void SetSerialNo()
    {
        TOspMonMsgHead *m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
        if(m_ptMsgHead != NULL)
        {
            m_ptMsgHead->m_dwSerialNo = htonl(g_dwSerialNo++);
            g_dwSerialNo %= MON_GEP_MAX_SERIAL;
        }
    }
    
    //////////////////////////////////////////////////////////////////////////
    // ����: GetSrcID
    // ����: ��ȡSrc ID
    // ԭ��: LPCSTR GetSrcID() const
    // ����: 
    // 
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    LPCSTR GetSrcID() const
    {
        TOspMonMsgHead* m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
        if(m_ptMsgHead == NULL)
            return "";
        return m_ptMsgHead->m_szSrcID;
    }
//    
//    TKDMNO GetSrcKdmNo() const
//    {
//        TOspMonMsgHead* m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
//        
//        if(m_ptMsgHead == NULL)
//            return TKDMNO();
//        
//        TKDMNO tSrcID;
//        tSrcID.SetNOString(m_ptMsgHead->m_szSrcID);
//        return tSrcID;
//    }
    
    //////////////////////////////////////////////////////////////////////////
    // ����: SetSrcID
    // ����: ����Src ID
    // ԭ��: LPCSTR SetSrcID(LPCSTR lpszSrcID)
    // ����: 
    // 
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    void SetSrcID(LPCSTR lpszSrcID)
    {
        TOspMonMsgHead* m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
        if(m_ptMsgHead == NULL)
            return;
        strncpy(m_ptMsgHead->m_szSrcID, lpszSrcID, sizeof(m_ptMsgHead->m_szSrcID));
        m_ptMsgHead->m_szSrcID[sizeof(m_ptMsgHead->m_szSrcID) - 1] = 0 ;
    }
    
//    void SetSrcID(const TKDMNO& tKdmNo)
//    {
//        TOspMonMsgHead* m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
//        if(m_ptMsgHead == NULL)
//            return;
//        strncpy(m_ptMsgHead->m_szSrcID, tKdmNo.GetNOString(), sizeof(m_ptMsgHead->m_szSrcID));
//        m_ptMsgHead->m_szSrcID[sizeof(m_ptMsgHead->m_szSrcID) - 1] = 0 ;
//    }
    
    //////////////////////////////////////////////////////////////////////////
    // ����: GetDstID
    // ����: ��ȡDst ID
    // ԭ��: LPCSTR GetDstID() const
    // ����: 
    // 
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    LPCSTR GetDstID() const
    {
        TOspMonMsgHead* m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
        if(m_ptMsgHead == NULL)
            return "";
        return m_ptMsgHead->m_szDstID;
    }
    
//    TKDMNO GetDstKdmNo() const
//    {
//        TOspMonMsgHead* m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
//        
//        if(m_ptMsgHead == NULL)
//            return TKDMNO();
//        
//        TKDMNO tDstID;
//        tDstID.SetNOString(m_ptMsgHead->m_szDstID);
//        return tDstID;
//    }
    
    //////////////////////////////////////////////////////////////////////////
    // ����: SetDstID
    // ����: ����Dst ID
    // ԭ��: LPCSTR SetDstID(LPCSTR lpszDstID) const
    // ����: 
    // 
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    void SetDstID(LPCSTR lpszDstID)
    {
        TOspMonMsgHead* m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
        if(m_ptMsgHead == NULL)
            return;
        strncpy(m_ptMsgHead->m_szDstID, lpszDstID, sizeof(m_ptMsgHead->m_szDstID));
        m_ptMsgHead->m_szDstID[sizeof(m_ptMsgHead->m_szDstID) - 1] = 0;
    }
    
//    void SetDstID(const TKDMNO& tKdmNo)
//    {
//        TOspMonMsgHead* m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
//        if(m_ptMsgHead == NULL)
//            return;
//        strncpy(m_ptMsgHead->m_szDstID, tKdmNo.GetNOString(), sizeof(m_ptMsgHead->m_szDstID));
//        m_ptMsgHead->m_szDstID[sizeof(m_ptMsgHead->m_szDstID) - 1] = 0;
//    }
    
    //////////////////////////////////////////////////////////////////////////
    // ����: GetSessID
    // ����: ��ȡ�Ự���
    // ԭ��: U32 GetSessID() const
    // ����: 
    // 
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    u32 GetSessID() const
    {        
        TOspMonMsgHead* m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
        if(m_ptMsgHead == NULL)
            return 0;
        return ntohl(m_ptMsgHead->m_dwSessID);
    }
    
    //////////////////////////////////////////////////////////////////////////
    // ����: GetXuiIns
    // ����: Cmu��ȡXuiSsn��Xui(��Cui��Pui�����ӵ�XuiSsnʵ�����
    // ԭ��: u32 GetXuiID() const
    // ����: 
    // 
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    u16 GetXuiIns() const
    {
        u32 dwSessID = GetSessID();
        return (u16)(dwSessID >> 16);
    }
    
    //////////////////////////////////////////////////////////////////////////
    // ����: GetXuiIns
    // ����: Cmu��ȡXuiSsn��Xui(��Cui��Pui�����ӵ�XuiSsnʵ�����
    // ԭ��: u32 GetXuiIns() const
    // ����: 
    // 
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    static u16 GetXuiIns(u32 dwSessId)
    {
        return (u16)(dwSessId >> 16);
    }
    
    //////////////////////////////////////////////////////////////////////////
    // ����: GetXuIns
    // ����: Xui����Cui��Pui����ȡ��Xu����Cu��Pu�����ӵ�Xuiʵ�����
    // ԭ��: u16 GetXuID() const
    // ����: 
    // 
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    u16 GetXuIns() const
    {        
        u32 dwSessID = GetSessID();
        return ((u16)(dwSessID));
    }
    
    //////////////////////////////////////////////////////////////////////////
    // ����: GetXuIns
    // ����: Xui����Cui��Pui����ȡ��Xu����Cu��Pu�����ӵ�Xuiʵ�����
    // ԭ��: u16 GetXuID() const
    // ����: 
    // 
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    static u16 GetXuIns(u32 dwSessId)
    {
        return ((u16)(dwSessId));
    }
    
    //////////////////////////////////////////////////////////////////////////
    // ����: SetSessID
    // ����: ���ûỰ���
    // ԭ��: void SetSessID() const
    // ����: 
    // 
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    void SetSessID(u32 dwSessID)
    {
        TOspMonMsgHead* m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
        if(m_ptMsgHead == NULL)
            return;
        m_ptMsgHead->m_dwSessID = htonl(dwSessID);
    }
    
    //////////////////////////////////////////////////////////////////////////
    // ����: SetSessID
    // ����: ���ûỰ���
    // ԭ��: void SetSessID() const
    // ����: u16 wXuInsId:Xu(cu��pu)��Xui(cui��pui)�����ӵ�Xuʵ����
    //       u16 wXuiInsId:Cmu��XuiSsn(cuissn��puissn)��Xui��cui��pui�������ӵ�Xuissnʵ����
    // 
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    void SetSessID(u16 wXuInsId, u16 wXuiInsId = 0)
    {
        u32 dwSessId = ((wXuiInsId << 16) + wXuInsId);
        SetSessID(dwSessId);
    }
    
    //////////////////////////////////////////////////////////////////////////
    // ����: GetEventID
    // ����: ��ȡEvent ID
    // ԭ��: u16 GetEventID() const
    // ����: 
    // 
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    u16 GetEventID() const
    {
        TOspMonMsgHead* m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
        if(m_ptMsgHead == NULL)
            return 0;
        return ntohs(m_ptMsgHead->m_wEventId);
    }
    
    //////////////////////////////////////////////////////////////////////////
    // ����: SetEventID
    // ����: ����Event ID
    // ԭ��: void SetEventID(u16 wEventID)
    // ����: 
    // 
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    void SetEventID(u16 wEventID)
    {
        TOspMonMsgHead* m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
        if(m_ptMsgHead == NULL)
            return;
        m_ptMsgHead->m_wEventId = htons(wEventID);
    }
    
    //////////////////////////////////////////////////////////////////////////
    // ����: GetTimeout
    // ����: ��ȡ��ʱʱ��
    // ԭ��: u16 GetTimeout() const
    // ����: 
    // 
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    u16 GetTimeout() const
    {
        TOspMonMsgHead* m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
        if(m_ptMsgHead == NULL)
            return 0;
        return ntohs(m_ptMsgHead->m_wTimeout);
    }
    
    //////////////////////////////////////////////////////////////////////////
    // ����: SetTimeout
    // ����: ���ó�ʱʱ��
    // ԭ��: void SetTimeout(u16 wTimeOut)
    // ����: 
    // 
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    void SetTimeout(u16 wTimeOut)
    {
        TOspMonMsgHead* m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
        if(m_ptMsgHead == NULL)
            return;
        m_ptMsgHead->m_wTimeout = htons(wTimeOut);
    }
    
    //////////////////////////////////////////////////////////////////////////
    // ����: GetErrorCode
    // ����: ��ȡ�����
    // ԭ��: u32 GetErrorCode(void) const
    // ����: 
    // 
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    u32 GetErrorCode(void) const
    {
        TOspMonMsgHead* m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
        if(m_ptMsgHead == NULL)
            return (u32)~0;
        return ntohl(m_ptMsgHead->m_dwErrorCode);
    }
    
    //////////////////////////////////////////////////////////////////////////
    // ����: SetErrorCode
    // ����: ���ô����
    // ԭ��: void SetErrorCode(u32 dwErrorCode)
    // ����: 
    // 
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    void SetErrorCode(u32 dwErrorCode)
    {
        TOspMonMsgHead* m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
        if(m_ptMsgHead == NULL)
            return;
        m_ptMsgHead->m_dwErrorCode = htonl(dwErrorCode);
    }
    
    u32 GetReserved1() const
    {
        TOspMonMsgHead* m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
        if(m_ptMsgHead == NULL)
            return 0;
        return ntohl(m_ptMsgHead->m_dwReserved1);
    }
    
    void SetReserved1(u32 dwReserved)
    {
        TOspMonMsgHead* m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
        if(m_ptMsgHead == NULL)
            return;
        m_ptMsgHead->m_dwReserved1 = htonl(dwReserved);
    }
    
    u32 GetReserved2() const
    {
        TOspMonMsgHead* m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
        if(m_ptMsgHead == NULL)
            return 0;
        return ntohl(m_ptMsgHead->m_dwReserved2);
    }
    
    void SetReserved2(u32 dwReserved)
    {
        TOspMonMsgHead* m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
        if(m_ptMsgHead == NULL)
            return;
        m_ptMsgHead->m_dwReserved2 = htonl(dwReserved);
    }
    
    //////////////////////////////////////////////////////////////////////////
    // ����: GetMsgBodyLen
    // ����: ��ȡ��Ϣ�峤��
    // ԭ��: u16 GetMsgBodyLen(void) const
    // ����: 
    // 
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    u16 GetMsgBodyLen(void) const
    {
        TOspMonMsgHead* m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
        if(m_ptMsgHead == NULL)
            return 0;
        return ntohs(m_ptMsgHead->m_wMsgBodyLen);
    }
    
    //////////////////////////////////////////////////////////////////////////
    // ����: GetMsgBody
    // ����: ��ȡ��Ϣ����
    // ԭ��: WORD GetMsgBody(   void* pMsgBody, // [in/out] ��Ϣ����
    //                          u16 wBodyLen, // [in] ��Ϣ����
    //                          u16 wOffset) // [in] ��Ϣƫ��
    // ����: 
    // [in/out] pMsgBody: ��ȡ�õ�����Ϣ����
    // [in] wBodyLen: ��Ϣ�ĳ���
    // [in] wOffset: ��Ϣ��ƫ��
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    u16 GetMsgBody(void* pMsgBody, u16 wBodyLen, u16 wOffset = 0)
    {
        if(pMsgBody == NULL)
        {
            return 0;
        }
        TOspMonMsgHead* m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
        if(m_ptMsgHead == NULL)
            return 0;
        u16 wLen = min(wBodyLen, ntohs(m_ptMsgHead->m_wMsgBodyLen));
        memcpy(pMsgBody, &m_abyBuffer[MON_MSG_BODY_OFFSET + wOffset], wLen);
        return wLen;
    }
    //////////////////////////////////////////////////////////////////////////
    
    //////////////////////////////////////////////////////////////////////////
    // ����: GetMsgBody
    // ����: ��ȡ��Ϣ����
    // ԭ��: void* GetMsgBody(u16 wOffset) // [in] ����ƫ��
    // ����: 
    // [in] wOffset: ��Ϣƫ��
    // ��ע: ֱ�ӷ�����Ϣ����ָ��
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    void* GetMsgBody(u16 wOffset = 0) const
    {
        TOspMonMsgHead* m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
        if(m_ptMsgHead == NULL)
            return NULL;
        if(m_ptMsgHead->m_wMsgBodyLen == 0)
            return NULL;
        return (void*)&m_abyBuffer[MON_MSG_BODY_OFFSET + wOffset];
    }
    
    //////////////////////////////////////////////////////////////////////////
    // ����: SetMsgBody
    // ����: ������Ϣ������
    // ԭ��: void SetMsgBody(void* pMsgBody, // [in] ��Ϣ����
    // u16 wBodyLen) // [in] ���ݳ���
    // ����: 
    // [in] pMsgBody: ������Ϣ������
    // [in] wBodyLen: ������Ϣ�����ݳ���
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    bool SetMsgBody(const void* pMsgBody, u16 wBodyLen)
    {
        if(pMsgBody != NULL && wBodyLen > 0)
        {			
            if(wBodyLen > MON_OSP_MSG_BODY_MAX_LEN)
            {
                return false;;
            }
            TOspMonMsgHead* m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
            if(m_ptMsgHead == NULL)
                return false;;
            
            memcpy(&m_abyBuffer[MON_MSG_BODY_OFFSET], pMsgBody, wBodyLen);
            m_ptMsgHead->m_wMsgBodyLen = htons(wBodyLen);
            
            return true;
        }
        return false;
    }
    //////////////////////////////////////////////////////////////////////////
    
    //////////////////////////////////////////////////////////////////////////
    // ����: CatMsgBody
    // ����: �����Ϣ����
    // ԭ��: void CatMsgBody(void* pMsgBody, // [in] ��Ϣ����
    // u16 wBodyLen) // [in] ���ݳ���
    // ����: 
    // [in] pMsgBody: ������ӵ���Ϣ����
    // [in] wBodyLen: ���ݵĳ���
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    bool CatMsgBody(const void* pMsgBody, u16 wBodyLen)
    {
        if(pMsgBody != NULL && wBodyLen > 0)
        {
            TOspMonMsgHead* m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
            if(m_ptMsgHead == NULL)
                return false;
            
            if(wBodyLen > (MON_OSP_MSG_BODY_MAX_LEN - ntohs(m_ptMsgHead->m_wMsgBodyLen)))
            {
                return false;;
            }
            
            memcpy(&m_abyBuffer[MON_MSG_BODY_OFFSET + ntohs(m_ptMsgHead->m_wMsgBodyLen)],
                pMsgBody, wBodyLen);
            m_ptMsgHead->m_wMsgBodyLen = htons(ntohs(m_ptMsgHead->m_wMsgBodyLen) + wBodyLen);
            return true;
        }
        return false;
    }
    
    //////////////////////////////////////////////////////////////////////////
    // ����: GetMonMsgLen
    // ����: ��ȡ������Ϣ����
    // ԭ��: u16 GetMonMsgLen(void) const
    // ����: 
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    u16 GetMonMsgLen(void) const
    {
        TOspMonMsgHead* m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
        if(m_ptMsgHead == NULL)
            return 0;
        return (ntohs(m_ptMsgHead->m_wMsgBodyLen) + MON_MSG_BODY_OFFSET);
    }
    
    //////////////////////////////////////////////////////////////////////////
    // ����: SetMonMsg
    // ����: ������Ϣ
    // ԭ��: void SetMonMsg(u8 * const pbyMsg, u16 wMsgLen)
    // ����: 
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2005/12/9 V2.00 luxz ���� 
    //________________________________________________________________________
    void SetMonMsg(u8 * const pbyMsg, u16 wMsgLen)
    {        
        memset(m_abyBuffer, 0, MON_OSP_MSG_MAX_LEN);
        
        if( wMsgLen < MON_MSG_BODY_OFFSET || pbyMsg == NULL )
            return;
        
        TOspMonMsgHead *m_ptMsgHead = (TOspMonMsgHead*)m_abyBuffer;
        wMsgLen = min( wMsgLen, sizeof( m_abyBuffer ) );
        memcpy( m_abyBuffer, pbyMsg, wMsgLen );
        m_ptMsgHead->m_wMsgBodyLen = htons(wMsgLen - MON_MSG_BODY_OFFSET);
    }
    //////////////////////////////////////////////////////////////////////////
    // ����: SetMonMsg
    // ����: ������Ϣ
    // ԭ��: void SetMonMsg(u8 * const pbyMsg, u16 wMsgLen)
    // ����: 
    // ��ע: 
    //
    // �޸ļ�¼
    // ���� �汾 �޸��� �޸�����
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2006/03/17 V2.00 ������ ���� 
    //________________________________________________________________________    
    u8 * const GetMonMsg( void ) const//��ȡ������Ϣָ�룬�û������ṩBUFFER
    {
        return( ( u8 * const )( m_abyBuffer ) );
    }
protected:    
    u8   m_abyBuffer[MON_OSP_MSG_MAX_LEN];		//��ϢBuffer��28K
};

#ifdef _MSC_VER
#pragma pack( pop )
#endif

#endif
