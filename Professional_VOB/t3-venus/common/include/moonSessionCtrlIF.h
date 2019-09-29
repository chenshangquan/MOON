/** @defgroup MoonLib���ƽӿ�
 *  @author  ���`�`
 *  @version V1.0  Copyright(C) 2013-2014 KDC, All rights reserved.
 *  @date    2013-2014
 *  @{
 */

#if !defined(AFX_MOONSESSIONCTRIF_H__EAE7EF3A_F4D7_4942_AFD0_9DC72544033B__INCLUDED_)
#define AFX_MOONSESSIONCTRIF_H__EAE7EF3A_F4D7_4942_AFD0_9DC72544033B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "camconfigif.h"
#include "sysconfigif.h"


class CMoonSessionCtrlIF : public CKdvDispEvent 
{
public:
	
    /*��    ��  ��ʼ��lib�⻷��
	��    ��  dwAppID�� ����ʹ�õ�appID
              dwDesIID: Ŀ��appID,Ĭ��MAKEIID(AID_CN_UE, 1)
	�� �� ֵ   
	˵    ��   ʹ�������ӿ�֮ǰ������øýӿ�*/ 
	virtual void InitEnv( u16 wAppID, u32 dwDesIID = MAKEIID(AID_MOON_UE, 1) ) = 0;


	/** ����  ��ȡ�ض��Ŀ��ƽӿ� 
	 *  @param[out] ppCtrl CCncAddrbookIF�ӿ�
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 *  @remarks �����ӵ��ն�ʱ,���Ի�ȡ��Щ�ӿ�,�ڶϿ����Ӻ�,������Щ�ӿ�����ʧЧ
	 */
	virtual u16 MoonGetInterface(CCamConfigIF **ppCtrl) = 0;

	// important if not add F5 pass but have other effects 577
	virtual u16 MoonGetInterface(CSysConfigIF **ppCtrl) = 0;
	
	/** ����  ���ӵ�Moon90��������� 
	 *  @param[in] dwIP	������CNS��IP��ַ
	 *  @param[in] dwPort  ������CNS�Ķ˿�
	 *  @param[in] strUser	�û���
	 *  @param[in] strPwd	����
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 *  @remarks 
	 */
	virtual u16 ConnectMoon(u32 dwIP, u32 dwPort, BOOL32 bConnect = TRUE) = 0;

	/** ����  �Ͽ�Moon90������������� 
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 *  @remarks ��û�����ӵ�Moon90���������ʱ���ô˷����������κ�����
	 */
	virtual u16 DisconnectMoon() = 0;

	/** ����  ��ѯ�Ƿ�������CNS 
	 *  @return  TRUE �����ӣ�FALSE	û����
	 *  @remarks 
	 */
	virtual BOOL IsConnectedMoon() = 0;

	/** ����  ��¼CNS�᳡
	 *  @param[in] byIns	�᳡Ins
	 *  @return  �ɹ�����0,ʧ�ܷ��ط�0������
	 *  @remarks 
	 */
	virtual u16 LoginMoonIns( u8 byIns ) = 0;

    /** ����  ��ȡ����ip
	 *  @param[in] 
	 *  @return  ����ip 
	 *  @remarks 
	 */
    virtual u32 GetLocalHostIP() = 0;

    /** ����  ��ȡ��½ip
	 *  @param[in] 
	 *  @return  ��½ip
	 *  @remarks 
	 */
	virtual u32 GetLoginIp() = 0;
    
	 /** ���� �п�֪ͨtpad ��tpad������cns����
	 *  @param[in] strSysName ���õ�ϵͳ����
	 *  @return  �ɹ�����0,ʧ�ܷ��ط�0������
	 *  @remarks 
	 */
//	virtual u16 DisConnectTpad() = 0;
};


#endif // !defined(AFX_MOONSESSIONCTRIF_H__EAE7EF3A_F4D7_4942_AFD0_9DC72544033B__INCLUDED_)
