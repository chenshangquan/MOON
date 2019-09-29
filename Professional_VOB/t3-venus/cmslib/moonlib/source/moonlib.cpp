// cnclib.cpp: implementation of the CCncLib class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "moonlib.h"
#include "cmsConst.h"
#include "moonSession.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMoonLib::CMoonLib()
{

}

CMoonLib::~CMoonLib()
{

}

/*=============================================================================
  �� �� ���� CreateSession
  ��    �ܣ� ����ʵ���˽ӿ�CCnsSessionCtrlIF�Ķ���
  �㷨ʵ�֣� �ӿ�ʹ����ɺ�,����DestroyInstance�������ٶ���
  ȫ�ֱ����� 
  ��    ���� CCnsSessionCtrlIF **ppICnt �ɹ�����CCnsSessionCtrlIF�ӿ�,ʧ�ܷ���NULL
  �� �� ֵ�� u16 
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
 2011.05.04     1.0		    Ф��Ȼ                  ����
=============================================================================*/
u16 CMoonLib::CreateSession(CMoonSessionCtrlIF **ppICnt)
{
	CMoonSession *pConnect = new CMoonSession();
	if(pConnect == NULL)
	{
		*ppICnt = NULL;
		return ERR_CNC_CREATINSTANCE;
	}
	else
	{
		*ppICnt = pConnect;
		return NO_ERROR;
	}
}

/*=============================================================================
  �� �� ���� DestroySession
  ��    �ܣ� ����ʵ���˽ӿ�CCnsSessionCtrlIF�Ķ���
  �㷨ʵ�֣� 
  ȫ�ֱ����� 
  ��    ���� CCnsSessionCtrlIF **ppICnt ����ӿ�CCnsSessionCtrlIF,�ɹ��󷵻�NULL
  �� �� ֵ�� u16 
  ˵    ���� ֻ��������CreateInstance���������Ķ���
  -----------------------------------------------------------------------------
  �޸ļ�¼��
  ��  ��		�汾		�޸���		�߶���    �޸�����
 2011.05.04     1.0		    Ф��Ȼ                  ����
=============================================================================*/
u16 CMoonLib::DestroySession(CMoonSessionCtrlIF **ppICnt)
{
	CMoonSession *pConnect = dynamic_cast<CMoonSession*>(*ppICnt);
	if(pConnect == NULL)
    {
        return ERR_CNC_INTERFACE;
    }
	delete pConnect;
	*ppICnt = NULL;
	return NO_ERROR;
}