// EventManage.h: interface for the CEventManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTMANAGE_H__142A8FFB_5D50_4671_B38A_1245E490A17F__INCLUDED_)
#define AFX_EVENTMANAGE_H__142A8FFB_5D50_4671_B38A_1245E490A17F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*---------------------------------------------------------------------
* ��	����CEventManage
* ��    �ܣ�ȫ��Ĭ���¼���һ��������
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/05/13	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
class CEventManage : public Singleton< CEventManage >
{
public:
	CEventManage();
	virtual ~CEventManage();

};

#endif // !defined(AFX_EVENTMANAGE_H__142A8FFB_5D50_4671_B38A_1245E490A17F__INCLUDED_)
