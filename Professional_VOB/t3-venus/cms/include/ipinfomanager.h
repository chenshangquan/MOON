// IPInfoManager.h: interface for the CIPInfoManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IPINFOMANAGER_H__984725AF_3E77_42C2_85D2_14634CC3F03B__INCLUDED_)
#define AFX_IPINFOMANAGER_H__984725AF_3E77_42C2_85D2_14634CC3F03B__INCLUDED_


#include <vector>
 
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
using namespace std;
 

class CIPInfoManager  
{
public:
	CIPInfoManager();
	virtual ~CIPInfoManager();
public:
	CString GetCurNetWorkName();  //��ȡ��ǰ�����ӿ�����

private:
	int  GetAllLinker(vector<CString> &v_strLinker);

	CString GetAppPath();
 
    BOOL ExistBatFile();
	
	BOOL WinExecAndWait(LPSTR lpExeName, LPSTR lpCmdLine);
 
private:
	CString m_strDumpFile;      //����������ӿ������ļ�
	CString m_strBatFile;       //�����ļ���bat�ļ�
	vector<CString> m_vcLinker;	
};

#endif // !defined(AFX_IPINFOMANAGER_H__984725AF_3E77_42C2_85D2_14634CC3F03B__INCLUDED_)
