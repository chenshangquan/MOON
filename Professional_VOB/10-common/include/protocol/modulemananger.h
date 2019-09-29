#ifndef MODULEMANANGER
#define MODULEMANANGER
/*******************************************************************************
*  ģ����   : �ն�ҵ��                                                        *
*  �ļ���   : modulemananger.h                                                *
*  ����ļ� :                                                                 *
*  ʵ�ֹ��� : ģ�����                                                        *
*  ����     : ����                                                            *
*  �汾     :																  *
*                                                                             *
*    =======================================================================  *
*  �޸ļ�¼:                                                                  *
*    ��  ��      �汾        �޸���      �޸�����                             *
*																			  *
*                                                                             *
 *******************************************************************************/
#include "osp.h"
#include "kdvtype.h"
#include "xmlengine.h"

#define MODULE_MSG_HEADER_LEN 4
#define MAX_MODULE_MSG_LEN 65532

#define ev_module_msg_init OSP_USEREVENT_BASE + 1
#define ev_module_msg_exit OSP_USEREVENT_BASE + 2

#define MAX_TITLE_LEN  32

struct TXEVENTINFO;
class CModuleMsg;
class CModuleObject : public CInstance
{
public:
	CModuleObject();
	virtual ~CModuleObject();
	
	friend class CModuleHandler;
	
protected:
	BOOL32    m_bInit;//��ʼ����־
private:
    void DaemonInstanceEntry( CMessage *const pcMsg, CApp* pcApp );							//daemon��Ϣ��ں���
	void InstanceEntry( CMessage *const ptMsg );											//��Ϣ������ں���
protected:
	
	virtual void MessageProc( CModuleMsg *const ptMsg ) {};										//��Ϣ��ں������˺�����Ҫ����
	virtual void DaemonMessageProc( CModuleMsg *const ptMsg,CApp* pcApp ){}					//daemon��Ϣ��ں������˺�����Ҫ����
	
	virtual BOOL32 DaemonObjectInit( u32 wParam, u32 lParam );								//daemon��ʼ����������Ҫ����
	virtual void DaemonObjectExit( void );													//daemon�˳���������Ҫ����
	virtual BOOL PreDaemonMessageProc( CMessage *const ptMsg )	{ return FALSE; }		    //daemon��ϢԤ����������Ҫ����
	
protected:
	virtual BOOL32 ObjectInit( u32 wParam, u32 lParam ) = 0;									//object��ʼ����������Ҫ����
	virtual void ObjectExit( void );															//object�˳���������Ҫ����
	
	virtual BOOL PreMessageProc( CMessage *const ptMsg )	{ return FALSE; }			    //��ϢԤ����������Ҫ����
	
public:
	void SetLogTitle( s8* title );															//����ģ���ӡǰ׺(ģ����)

	void Error(s8* szFormat, ...);
	void Hint(s8* szFormat, ...);
	void LowHint(s8* szFormat, ... );

	BOOL NotifySelf( CModuleMsg &cMsg );
    
private:
	void*     m_plog;
	BOOL      m_bShowMsg;
	TXEVENTINFO* m_ptXmlTable;
};


class CModuleMsg;
class CModuleHandler
{
protected:
	CModuleObject* m_pcInstance;
public:

	CModuleHandler( CModuleObject* pcObject ){ m_pcInstance = pcObject; }
	~CModuleHandler();

	virtual BOOL32 Handler( CModuleMsg *const ptMsg ) = 0;
	
	virtual BOOL32 Create()	{ return TRUE; }
	virtual void Destroy(){};
	void Error( s8* szFormat, ... );
	void Hint( s8* szFormat, ... );
	void LowHint( s8* szFormat, ... );

protected:

	int SetTimer( u32 nTimer, long nMilliSeconds, u32 nPara=0)
	{
		if( m_pcInstance )
			return m_pcInstance->SetTimer( nTimer ,nMilliSeconds ,nPara );
		return 0;
	};
	
	int KillTimer( u32 nTimerNo )
	{
		if( m_pcInstance )
			return m_pcInstance->KillTimer( nTimerNo );
		return 0;
	};
	
	CModuleObject*   GetInstance(){ return m_pcInstance; }
};

class CModuleMsg
{
protected:

	u16 m_wEvent;
	u16 m_wBodyLen;
	u32 m_dwSrcIId;
	u32 m_dwSrcNode;
	
	u8  m_abyMsg[ MAX_MODULE_MSG_LEN + MODULE_MSG_HEADER_LEN ];
	s32 m_nXMLIndex;
	
protected:
	enum EmMsgCodeIndex
	{
		CODEC_FLAG        = 0, //���ֽ� = 0��ʾδ���� = 1��ʾ�������� = 2��ʾxml����
		CODEC_HOMEPLACE   = 1,
		CODEC_User        = 2,
		CODEC_RESERVER3   = 3,
		CODEC_BODY		  = 4,

	};
	enum EmMsgCodecFlagStatus
	{
		CODEC_NONE         = 0,
		CODEC_XML_MARSHAL = 2,//���ݾɵ��ն�xml����2��ʼ
		CODEC_XML_COMPRESS,
	};
	enum EmMsgDataType
	{
		emRawData     = 0 ,//δ��������ԭʼ����
		emCodeData         //������������
	};
	//��Ϣ�Ƿ񾭹�����
	u8 IsMsgCoder()
	{
		return m_abyMsg[0];
	}

public:
	CModuleMsg(){ memset( this,0,sizeof(CModuleMsg) ); }
	CModuleMsg( const CMessage* ptMsg )
	{
		memset( this,0,sizeof(CModuleMsg) );
		m_nXMLIndex = -1;

		m_dwSrcIId  = ptMsg->srcid;
		m_dwSrcNode = ptMsg->srcnode;

		m_wEvent = ptMsg->event;
		m_wBodyLen = ptMsg->length - MODULE_MSG_HEADER_LEN;
		memcpy( m_abyMsg , ptMsg->content , ptMsg->length );

	}

	//�����Ϣ��ָ��
	u8*	GetBody(){ return m_abyMsg+CODEC_BODY; }
	
	//�����Ϣ�峤��
	u16	GetBodyLen() { return m_wBodyLen; }

	//�����Ϣָ��
	u8*	GetMsg(){ return m_abyMsg; }
	
	//�����Ϣ����
	u16	GetMsgLen() { return m_wBodyLen + MODULE_MSG_HEADER_LEN; }

	//������Ϣ������
	BOOL SetBody(const void* buf ,u16 len )
	{ 
		if( len > (u16)(MAX_MODULE_MSG_LEN) )
			return FALSE;
		if( NULL == buf || 0 == len )
		{
			m_wBodyLen = 0;
			return TRUE;
		}
		memcpy( m_abyMsg+CODEC_BODY ,buf ,len );
		m_wBodyLen = len;
		return TRUE;
	}

	//�����Ϣ������
	BOOL CatBody( const void* buf ,u16 len )
	{
		if( len + m_wBodyLen > (u16)(MAX_MODULE_MSG_LEN) )
			return FALSE;

		memcpy( m_abyMsg +CODEC_BODY +m_wBodyLen ,buf ,len );
		m_wBodyLen += len;
		return TRUE;

	}

	void SetEvent(u16 event ) { m_wEvent = event; }
	u16  GetEvent() { return m_wEvent; }

	u32 GetSrcIId(){ return m_dwSrcIId; }
	u32 GetSrcNode(){ return m_dwSrcNode; }

	//��ȡ��Ϣ�ķ�����
	u8   GetHomeplace()
	{
		return m_abyMsg[CODEC_HOMEPLACE];
	}

	void SetHomeplace( u8 byNode )
	{
		m_abyMsg[CODEC_HOMEPLACE] = byNode;
	}

	u8   GetUserData()
	{
		return m_abyMsg[CODEC_User];
	}

	void   SetUserData( u8 byData )
	{
		m_abyMsg[CODEC_User] = byData;
	}

protected:
    void  DisplayMsgStream( u32 srcid , u32 dstid );
};

struct TXEVENTINFO
{
	u16   eventid;				//Event idֵ
	char* name;					//Event description
	TXDATANODE* tDataNode;		//����Ӧ�ṹ����
	
	TXEVENTINFO()
	{
		eventid = 0;
		name = 0;
		tDataNode = 0;
	}
};

typedef struct tagMdlInitParam
{
	s8 m_achTitle[MAX_TITLE_LEN+1];		//ģ��title����			
	TXEVENTINFO* m_ptXmlTable;			//XML�����
	u32 wParam;
	u32 lParam;			//�û��Զ���
	SEMHANDLE Sem;
	
	tagMdlInitParam()
	{
		memset( this , 0 , sizeof(tagMdlInitParam) );
	}
}TMDLInitParam;

#endif
