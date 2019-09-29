#ifndef _UMM_H_
#define _UMM_H_
#include "ummessagestruct.h"

#define AID_UMSERVER                    236
#define MAX_MSG_BUFF_SIZE               (64*1024)

class CUsrManage
{
public:
	CUsrManage(); //Ĭ��
	CUsrManage( u8* acFilePath, u8* achFileName = NULL); //���洢�û���Ϣ�ļ�·��
	~CUsrManage();
private:
	u32 m_uError; //��Ϣ������
	CUserFullInfo m_usrAllMembers[MAX_USERNUM]; //�û��б�
	u8  m_byNumUsr; //�û�����
	char  acCurrentPath[256];//�洢�û���Ϣ�ļ�·��
	char  m_achFileName[MAX_UMFILENAME_LEN];//�洢�����û���Ϣ���ļ���
    s8 m_pMsgBuff[MAX_MSG_BUFF_SIZE];
    BOOL m_bSingle;

public:
	CUserFullInfo m_usrCurLogin; //��ǰ��¼���û�
	//init and quit 
private:
	void	Reset(); //��������û�,��������Ա
protected:
	BOOL WriteAllUserBackToFile();//�����û���Ϣд���ļ�
	//operate
public:	
    void SetSingle(BOOL bSingle); //�Ƿ��û�

    BOOL GetAllUserFromFile();	//���ļ��ж��������û���Ϣ

    s32 GetUserNum(){return m_byNumUsr;};
    //��ȡ��nIndex�û���Ϣ�� nIndex��0��ʼ
    BOOL GetUserFullInfo(CUserFullInfo* ptUserInfo, s32 nIndex);

	BOOL AddUser(CUserFullInfo* newusr); //���һ���û�
	BOOL DelUser(CUserFullInfo* oldinfo);//ɾ��һ���û�
	BOOL DelAllMembers();//ɾ�������û�
	BOOL ModifyInfo(CUserFullInfo* newinfo);//�޸�һ���û�
	BOOL CheckLoginValid(CLoginRequest* curusr);//��鵱ǰ��¼�û���Ϣ
	BOOL GetAllUser(CMessage* pcMsg); //�õ������û���Ϣ
	void CmdLine(int cmdcode); //������ʾ��Ϣ
	void SetPath(char* acFilePath); //���ñ����ļ�·��
	u16 GetLastError() //��ǰ�����Ĵ�����
	{
		return (u16)m_uError;
	}
	void TestDelAllUser(); //���ɲ���ɾ�������û�
	//message
private:
	void OnLigIn(CMessage* pcMsg);
	void OnAddUser(CMessage* pcMsg);
	void OnDelUser(CMessage* pcMsg);
	void OnModifyInfo(CMessage* pcMsg);
	void OnGetAllMembers(CMessage* pcMsg);
	void DisplayMenu();
	void OnDelAllMembers(CMessage* pcMsg);
	
	//interface
public:
	void ShowAll();//���������û���Ϣ
	void ProcessMsg(CMessage* pcMsg);
}
#ifdef _VXWORKS_
__attribute__ ( (packed) ) 
#endif // _VXWORKS_
;

API BOOL32 InitUserManage();

#endif
