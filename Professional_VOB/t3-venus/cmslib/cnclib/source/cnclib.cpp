// cnclib.cpp: implementation of the CCncLib class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cnclib.h"
#include "cmsConst.h"
#include "cnsSession.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCncLib::CCncLib()
{

}

CCncLib::~CCncLib()
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
u16 CCncLib::CreateSession(CCnsSessionCtrlIF **ppICnt)
{
	CCnsSession *pConnect = new CCnsSession();
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
u16 CCncLib::DestroySession(CCnsSessionCtrlIF **ppICnt)
{
	CCnsSession *pConnect = dynamic_cast<CCnsSession*>(*ppICnt);
	if(pConnect == NULL)
    {
        return ERR_CNC_INTERFACE;
    }
	delete pConnect;
	*ppICnt = NULL;
	return NO_ERROR;
}