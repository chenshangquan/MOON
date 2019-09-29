#ifndef _MTSUBDAVINCI_H_
#define _MTSUBDAVINCI_H_

#include "osp.h"

#define  EV_SubDavinciBrdInitCmd         100
#define  EV_CfgSubDavinciEthernetCmd     101   //���ô�davinci����ip
#define  EV_CfgSubDavinciSecEthernetCmd  102   //���ô�davinci�ĵڶ���ip
#define  EV_DelSubDavinciSecEthernetCmd  103   //ɾ����davinci�ĵڶ���ip
#define  EV_CfgSavePxySrvCfgCmd          104   //����Pxy�����������ļ�
#define  EV_RunGkAndPxyCmd               105   //����Gk��Pxy��Ӧ��

#define  EV_SubDavinciIpConflictInitCmd  106   //������davinci��ip��ͻ���
#define  EV_SubDavinciIpConflictInd      107   //��davinci ip��ͻ���ָʾ

#define  EV_SubDavinciLoopTestCmd        108   //���ڲ���������Ϣ�ػ�
#define  EV_SubDavinciLoopTestInd        109   //���ڲ���������Ϣ�ػ�

#define  EV_SubDavinciAddDefaultGWCmd    110   //���Ӵ�davinciĬ������
#define  EV_SubDavinciDelDefaultGWCmd    111   //ɾ����davinciĬ������

#define  MAX_MULTINETSEGMENTPXY_NUM      5     //�����δ�����Ŀ

/************************************************************************/
/* ���ô��������ν��������                                           */
/************************************************************************/
typedef struct tagTSubPxyIPCfg
{
    BOOL bUsed;
    u32  dwIP;         //IP��ַ
    u32  dwMask;       //��������
    u32  dwGateway;    //���ص�ַ
}TSubPxyIPCfg, *PTSubPxyIPCfg;

API BOOL mtSubDavinciEventCallBack(u32 dwEventId, void* pContent, u32 dwContentLen);

//Proxy server
class CSubPxySrvCfgEx
{
private:    
    //[StarInfo]
    u8        m_byStartPxy;      //�Ƿ�����pxy
    u8        m_byStartMp;       //�Ƿ�����mp
    //[LocalInfo]
    u32       m_dwLocalIpAddr;   //server��ַ
    u32       m_dwLocalRasPort;  //server H323������˿�
    u32       m_dwLocalH245Port; 
    u32       m_dwLocalOspPort;  
    //clinet��server֮��������˿�
    u32       m_dwLocalRtpPort;       
    u32       m_dwLocalRtcpPort;      
    u32       m_dwLocalMediaBasePort; 
    //[GKInfo]
    u32       m_dwGKIpAddr;      //GK��ַ
    u32       m_dwGKRasPort;     //GK�˿�
    //[DefaultGW]
    u32       m_dwGateWay;       //���ص�ַ
    TSubPxyIPCfg m_atPxyIPCfg[MAX_MULTINETSEGMENTPXY_NUM]; //�����ν�������
public:
    BOOL   m_bInit;
    static CSubPxySrvCfgEx* GetInstance();
    
protected:
    CSubPxySrvCfgEx()
    {
        m_bInit = FALSE;
        m_byStartPxy = 1;
        m_byStartMp  = 1;
        m_dwLocalIpAddr = inet_addr("127.0.0.1");
        m_dwLocalRasPort  = 1819;
        m_dwLocalH245Port = 1820;
        m_dwLocalOspPort  = 2776;
        m_dwLocalRtpPort  = 2776;
        m_dwLocalRtcpPort = 2777;
        m_dwLocalMediaBasePort = 48000;
        m_dwGKIpAddr = inet_addr("0.0.0.0");
        m_dwGKRasPort = 1719;
        memset( &m_atPxyIPCfg[0], 0, sizeof(m_atPxyIPCfg) );
    }
    BOOL srvCfgPathExist(const s8* path)
    {
		BOOL bRet = TRUE;
#ifdef _LINUX_
        s8  achCurPath[256] ={0};
        s8* pStr = getcwd(achCurPath,sizeof(achCurPath));
        if(NULL == pStr) return FALSE;
        bRet= (chdir(path) >= 0);
        chdir(achCurPath);
#endif
        return bRet;
    }
    
    BOOL srvCfgMakeDir(const s8* path )
    {
        int nRet = 0;
        
#ifdef WIN32
        nRet = CreateDirectory( path, 0 );
#endif
#ifdef _VXWORKS_
        nRet = mkdir( path  );
#endif
#ifdef _LINUX_
        if(srvCfgPathExist(path)) return FALSE;
        
        nRet = mkdir(path,  S_IRUSR//�ļ������߾߿ɶ�ȡȨ��
            |S_IWUSR//�ļ������߾߿�д��Ȩ��
            |S_IXUSR//�ļ������߾߿�ִ��Ȩ��
            |S_IRGRP// �û���߿ɶ�ȡȨ��
            |S_IWGRP//�û���߿�д��Ȩ��
            |S_IXGRP//�û���߿�ִ��Ȩ��
            |S_IROTH//�����û��߿ɶ�ȡȨ��
            |S_IWOTH//�����û��߿�д��Ȩ��
            |S_IXOTH);//���û��߿�ִ��Ȩ��
#endif
        if(nRet < 0)
            printf("%s created failled,error no. = %d\n",path, nRet);
        else
            printf("%s created success\n",path);        
        return TRUE;
    }

public:
    BOOL ReadFromFile();
    BOOL SaveToFile();	
    BOOL SetPxySrvInfo(u32 dwLocalIp, u32 dwGkIp, u32 dwGateway);
    //�����ν���
	BOOL SetPxyIPCfg(TSubPxyIPCfg atPxyIPCfg_old[MAX_MULTINETSEGMENTPXY_NUM], TSubPxyIPCfg atPxyIPCfg_new[MAX_MULTINETSEGMENTPXY_NUM]);
	//���ô���ı���ip, Ҳ����Ҫ�������ص�
	BOOL SetPxyLocalIPCfg(TSubPxyIPCfg tPxy_old, TSubPxyIPCfg tPxy_new );
	//GK��ip������
	BOOL SetPxyGKCfg( u32 dwGKIP);
	void CommonSaveToFile();
	void PxyLocalIPSave();
	void PxyIPArraySave(); 
};

#endif





















