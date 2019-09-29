#ifndef _MTMC_RMTTESTER_H
#define _MTMC_RMTTESTER_H
class CMtMcRmtTester
{
private:
	u32 m_mcNode;				//MC�ڵ��
public:
	//=====================================
	//��ʼ���ӿ�
	//=====================================
	BOOL Init(u32 mcNode = 0);
public:
	//=====================================
	//�����ӿ�
	//=====================================
	//����MC
	void SetMcActive();
	//ȥ����MC
	void SetMcInActive();
	//�����º��д���ģʽ
	void SetNewCallMode(u8 mode);
	//�������
	void MakeCall(u32 ip,u16 port = 1720,u8 callType = CALL_TYPE_CREATE);
	//ע�����л�����Ϣ
	void SetConfInfo(TMCRegConf& tRegConf);
public:
	//=====================================
	//��ѯ�ӿ�
	//=====================================
	//��ȡMC��ǰ״̬
	u32 GetMcState();
	//ĳ���ն��Ƿ��ڻ�����
	BOOL IsInConf(u32 ip);
	//ĳ���ն˱���Ƿ��ڻ�����
	BOOL IsLabelInConf(TTERLABEL label);
	//��ѯ��ǰ������
	TTERLABEL GetFloorer();
	//��ѯ��ǰ��ϯ
	TTERLABEL GetChair();
	//��ѯ������Ϣ
	CConference GetConfInfo();
	//��ѯ����ģʽ
	u8 GetConfMode();
	//��ѯ���뷢���ն�
	TTERLABEL GetApplyFloorer();
	//��ѯ������ϯ�ն�
	TTERLABEL GetApplyChair();
	//��ѯ����Ϊ�������ն�
	TTERLABEL GetToBeFloorer();
	//��ѯ��ǰ��ƵԴ
	TTERLABEL GetSrcLabel();
protected:
	//������Ϣ��MC
	BOOL PostMsgToMc(u16 wEvent,
					  const void* pBody = NULL,
					  u16 wLen = 0,
					  PTHANDLE ptHandle = NULL);
	//���ͼ��ɲ�����Ϣ�ӿ�
	BOOL SendIntTestMsgToMc(u32 dwEvent,
							const void* pBody = NULL,
							u16  wLen = 0,
							void* ackbuf=NULL,
							u16  ackbuflen=0,
							u16* realacklen=NULL);
};
#endif 