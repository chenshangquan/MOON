#include "stdafx.h"
#include "socketmanager.h"
#include <afxsock.h>
//#include "windows.h"

#include "rkcConst.h"
#include "rkcmsgrecver.h"
#include "rkcmsgdriver.h"
#include "rkcevent.h"
#include "rkcprintctrl.h"

static UINT     g_nHeartBeatLostCount;                      //��������ʧ����
static bool     g_bHeartBeatKeep;                           //
#define         TIME_HEARTBEAT_INTERVAL        5000         //ʱ����

bool     CSocketManager::m_bIsSocketOpen = false;    //Socket�Ƿ���

CSocketManager* CSocketManager::m_pSocketManager = NULL;

UINT ThreadHeartBeat(LPVOID lpParam)
{
    while ( g_bHeartBeatKeep )
    {
        g_nHeartBeatLostCount++;
        if (g_nHeartBeatLostCount > 2)//��������û��Ӧ����Ϊ����
        {
            PrtRkcMsg( UI_RKC_DISCONNECTED, emEventTypeScoketRecv, "�����ر�...");
            SOCKETWORK->CloseSocket();
            return 0;
        }
        TRK100MsgHead tRK100MsgHead;//������Ϣͷ�ṹ��
        memset(&tRK100MsgHead,0,sizeof(TRK100MsgHead));
        //���ʹ����ݼ���ת������
        tRK100MsgHead.dwEvent = htonl(RK100_EVT_SET_HEART_BEAT);
        CRkMessage rkmsg;//������Ϣ
        rkmsg.SetBody(&tRK100MsgHead, sizeof(TRK100MsgHead));//���ͷ����

        PrtRkcMsg( RK100_EVT_SET_HEART_BEAT, emEventTypeScoketSend, "����������...");
        SOCKETWORK->SendDataPack(rkmsg);//��Ϣ����

        Sleep(TIME_HEARTBEAT_INTERVAL);
    }
    return 0;
}

UINT ThreadSendDadaPack(LPVOID lpParam)
{
    while (CSocketManager::m_bIsSocketOpen)
    {
        SOCKETWORK->SendDataPack();
        Sleep(100);
    }
    return 0;
}

UINT ThreadRevcDadaPack(LPVOID lpParam)
{
    while (CSocketManager::m_bIsSocketOpen)
    {
        SOCKETWORK->RecvDataPack();
    }
    return 0;
}

CSocketManager::CSocketManager()
{
    g_nHeartBeatLostCount = 0;
    g_bHeartBeatKeep = false;

    InitializeCriticalSection(&m_csMsgLock);

    memset(m_achIP, 0, 16 );
    m_dwPort = 0;
    m_evWaitMsg = 0;

    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA data;
    WSAStartup(sockVersion, &data);
}

CSocketManager::~CSocketManager()
{
    DeleteCriticalSection(&m_csMsgLock);
    WSACleanup();
}

CSocketManager* CSocketManager::GetSocketManager()
{
    if (CSocketManager::m_pSocketManager == NULL)
    {
        CSocketManager::m_pSocketManager = new CSocketManager();
    }
    return CSocketManager::m_pSocketManager;
}

void CSocketManager::setSocketIP(char* pchbuf)
{
    if(pchbuf == NULL)
    {
        return;
    }
    memset(m_achIP, 0, MAX_IP_LENGTH);
    int nlength = (strlen(pchbuf) >= MAX_IP_LENGTH ? MAX_IP_LENGTH: strlen(pchbuf));
    memcpy(m_achIP, pchbuf, nlength);
    m_achIP[nlength] = '\0';
}

void CSocketManager::SetSocketPort(u32 dwPort)
{
    m_dwPort = dwPort;
}

u8 CSocketManager::OpenSocket()
{
    m_sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(m_sclient == INVALID_SOCKET)
    {
        return ERR_SOCKET_INIT;
    }
    //���÷��ͽ��ܳ�ʱ
    UINT g_nNetTimeout = 3000;//��ʱʱ�� 1s
    setsockopt(m_sclient, SOL_SOCKET, SO_SNDTIMEO, (char *)&g_nNetTimeout,sizeof(int));
    setsockopt(m_sclient, SOL_SOCKET, SO_RCVTIMEO, (char *)&g_nNetTimeout, sizeof(int));

    // ����Ϊ��������socket  
    int iMode = 1;  
    ioctlsocket(m_sclient, FIONBIO, (u_long FAR*)&iMode);

    sockaddr_in serAddr;
    serAddr.sin_family = AF_INET;
    serAddr.sin_port = htons(m_dwPort);
    serAddr.sin_addr.S_un.S_addr = inet_addr(m_achIP);

    // ��ʱʱ��  
    struct timeval tm;  
    tm.tv_sec  = 5;  
    tm.tv_usec = 0;  

    if(connect(m_sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
    {
        fd_set set;  
        FD_ZERO(&set);  
        FD_SET(m_sclient, &set);  

        if (select(-1, NULL, &set, NULL, &tm) <= 0)  
        {  
            //����ʧ�� 
            closesocket(m_sclient);
            return -1;
        }  
        else  
        {  
            int error = -1;  
            int optLen = sizeof(int);  
            getsockopt(m_sclient, SOL_SOCKET, SO_ERROR, (char*)&error, &optLen);   
            // ֮��������ĳ���д����Ŀ���������ʽ�� ��Ϊ�˸�ֱ�ۣ� ����ע��  
            if (0 != error)  
            {  
                //����ʧ�� 
                closesocket(m_sclient);
                return -1;  
            }  
        }
    }

    // ���Ϊ����socket  
    iMode = 0;  
    ioctlsocket(m_sclient, FIONBIO, (u_long FAR*)&iMode); //����Ϊ����ģʽ  

    CSocketManager::m_bIsSocketOpen = true;
    //�������������߳�
    AfxBeginThread(ThreadSendDadaPack, NULL);
    //�������������߳�
    //AfxBeginThread(ThreadRevcDadaPack, NULL);
    //������������Timer
    StartHeartBeat();
    return NOERROR;
}

void CSocketManager::CloseSocket()
{
    EnterCriticalSection(&m_csMsgLock);
    m_RkcMsgQueue.Clear();
    LeaveCriticalSection(&m_csMsgLock);
    m_evWaitMsg = 0;
    closesocket(m_sclient);
    StopHeartBeat();
    CSocketManager::m_bIsSocketOpen = false;
    OspPost(MAKEIID(AID_RKC_APP,0), UI_RKC_DISCONNECTED);
    PrtRkcMsg( "�ر� Scoket...");
}

bool CSocketManager::IsSocket()
{
    return CSocketManager::m_bIsSocketOpen;
}

void CSocketManager::SendDataPack(CRkMessage rkmsg)
{
    EnterCriticalSection(&m_csMsgLock);
    m_RkcMsgQueue.PushMsg(rkmsg);
    LeaveCriticalSection(&m_csMsgLock);
}

void CSocketManager::SendDataPack()
{
    if (m_evWaitMsg != 0)
    {
        PrtRkcMsg( m_evWaitMsg, emEventTypeScoketSend, "�ȴ���Ӧ��,�ܾ�����...");
        return;
    }
    EnterCriticalSection(&m_csMsgLock);
    BOOL bIsMsgEmpty = m_RkcMsgQueue.IsEmpty();
    LeaveCriticalSection(&m_csMsgLock);
    if (!bIsMsgEmpty)
    {
        CRkMessage rkmsg;
        EnterCriticalSection(&m_csMsgLock);
        m_RkcMsgQueue.PopMsg(rkmsg);
        LeaveCriticalSection(&m_csMsgLock);
        TRK100MsgHead tRK100MsgHead = *(TRK100MsgHead*)(rkmsg.GetBody());
        //���õȴ��ظ�����ϢΪ���͵���Ϣ+1 û�лظ��ⲻ�ɼ���������Ϣ
        m_evWaitMsg = ntohl(tRK100MsgHead.dwEvent) + 1;
        int ret = send(m_sclient, (const char*)rkmsg.GetBody(), rkmsg.GetBodyLen(), 0);
        if (ret == -1)
        {
            //���ͳ�ʱ
            PrtRkcMsg( tRK100MsgHead.dwEvent, emEventTypeScoketSend, "���ͳ�ʱ��");
        }
        //���ͺ�ȴ�������Ϣ
        while (m_evWaitMsg != 0)
        {
            RecvDataPack();
        }
    }
}

void CSocketManager::RecvDataPack()
{
    char recData[RK_MAXLEN_MESSAGE] = {0};
    int ret = recv(m_sclient, recData, RK_MAXLEN_MESSAGE, 0);
    if(ret>0)
    {
        recData[ret] = 0x00;
        //��Ϣ�ŵ�OSP�ص��߳�
        CRkMessage rkmsg;
        memset(&rkmsg,0,sizeof(CRkMessage));
        TRK100MsgHead tRK100MsgHead = *(TRK100MsgHead*)(recData);
        tRK100MsgHead.dwEvent = ntohl(tRK100MsgHead.dwEvent);

        //�ǵȴ��Ļָ���Ϣ �ͷż�������
        if (m_evWaitMsg == tRK100MsgHead.dwEvent)
        {
            m_evWaitMsg = 0;
        }
        if (RK100_EVT_SET_HEART_BEAT_ACK == tRK100MsgHead.dwEvent)//������
        {
            g_nHeartBeatLostCount = 0;//δ���� ���¼���
            PrtRkcMsg( RK100_EVT_SET_HEART_BEAT_ACK, emEventTypeScoketRecv, "�յ�������...");
        }
        else
        {
            rkmsg.SetBody(recData, sizeof(TRK100MsgHead) + tRK100MsgHead.wMsgLen);
            OspPost(MAKEIID(AID_RKC_APP,0), tRK100MsgHead.dwEvent , rkmsg.GetBody() , sizeof(TRK100MsgHead) + tRK100MsgHead.wMsgLen);
        }
    }
    else if (ret == -1)
    {
        //���ܳ�ʱ
        PrtRkcMsg( m_evWaitMsg, emEventTypeScoketRecv, "���ܳ�ʱ��");

        if (m_evWaitMsg == RK100_EVT_LOGIN_ACK)//��¼��ʱ
        {
            TRK100MsgHead tRK100MsgHead;
            memset(&tRK100MsgHead, 0, sizeof(TRK100MsgHead));
            tRK100MsgHead.dwEvent = RK100_EVT_LOGIN_ACK;
            tRK100MsgHead.wOptRtn = RK100_OPT_ERR_UNKNOWN;
            OspPost(MAKEIID(AID_RKC_APP,0), tRK100MsgHead.dwEvent , &tRK100MsgHead , sizeof(TRK100MsgHead));
        }
        m_evWaitMsg = 0;
    }
}

void CSocketManager::StartHeartBeat()
{
    g_nHeartBeatLostCount = 0;
    //���������߳�
    g_bHeartBeatKeep = true;
    AfxBeginThread(ThreadHeartBeat, NULL);
}
void CSocketManager::StopHeartBeat()
{
    g_bHeartBeatKeep = false;
    g_nHeartBeatLostCount = 0;
}