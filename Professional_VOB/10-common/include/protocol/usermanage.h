#ifndef _UMM_H_
#define _UMM_H_
#include "ummessagestruct.h"

#define AID_UMSERVER                    236
#define MAX_MSG_BUFF_SIZE               (64*1024)

class CUsrManage
{
public:
	CUsrManage(); //默认
	CUsrManage( u8* acFilePath, u8* achFileName = NULL); //带存储用户信息文件路径
	~CUsrManage();
private:
	u32 m_uError; //消息错误码
	CUserFullInfo m_usrAllMembers[MAX_USERNUM]; //用户列表
	u8  m_byNumUsr; //用户个数
	char  acCurrentPath[256];//存储用户信息文件路径
	char  m_achFileName[MAX_UMFILENAME_LEN];//存储保存用户信息的文件名
    s8 m_pMsgBuff[MAX_MSG_BUFF_SIZE];
    BOOL m_bSingle;

public:
	CUserFullInfo m_usrCurLogin; //当前登录的用户
	//init and quit 
private:
	void	Reset(); //清空所有用户,包括管理员
protected:
	BOOL WriteAllUserBackToFile();//所有用户信息写入文件
	//operate
public:	
    void SetSingle(BOOL bSingle); //是否单用户

    BOOL GetAllUserFromFile();	//从文件中读入所有用户信息

    s32 GetUserNum(){return m_byNumUsr;};
    //获取第nIndex用户信息， nIndex从0开始
    BOOL GetUserFullInfo(CUserFullInfo* ptUserInfo, s32 nIndex);

	BOOL AddUser(CUserFullInfo* newusr); //添加一个用户
	BOOL DelUser(CUserFullInfo* oldinfo);//删除一个用户
	BOOL DelAllMembers();//删除所有用户
	BOOL ModifyInfo(CUserFullInfo* newinfo);//修改一个用户
	BOOL CheckLoginValid(CLoginRequest* curusr);//检查当前登录用户信息
	BOOL GetAllUser(CMessage* pcMsg); //得到所有用户信息
	void CmdLine(int cmdcode); //命令显示信息
	void SetPath(char* acFilePath); //设置保存文件路径
	u16 GetLastError() //当前操作的错误码
	{
		return (u16)m_uError;
	}
	void TestDelAllUser(); //集成测试删除所有用户
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
	void ShowAll();//命令所有用户信息
	void ProcessMsg(CMessage* pcMsg);
}
#ifdef _VXWORKS_
__attribute__ ( (packed) ) 
#endif // _VXWORKS_
;

API BOOL32 InitUserManage();

#endif
