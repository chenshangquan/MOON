// MfcDefaultWndPropertySet.h: interface for the MfcDefaultWndPropertySet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCDEFAULTWNDPROPERTYSET_H__296760B5_4C36_434F_9543_347830BCA392__INCLUDED_)
#define AFX_MFCDEFAULTWNDPROPERTYSET_H__296760B5_4C36_434F_9543_347830BCA392__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "uifactorydef.h"
#include "PropertySet.h"

/*
 * @defgroup MfcĬ�Ͽؼ������Լ� \n
	���������¿ؼ���������Ҫ�̳�wnd��һЩĬ�����ԣ���̳���CWndPropertySet�� \n
	�������¿ռ����µ����ԣ����ڹ��캯���������	\n
	������ļ�������������Լ� ��Ҫ��CRegDefaultData����ע��

 * @author  Ĳ��ï
 * @version 1.0
 * @date  2011/05/31
 * @{
 */
namespace AutoUIFactory
{
/*
 *	Ĭ�ϴ������Լ� ���ڹ��캯�������������
 */
DECLARE_PROPERTYSET_BEGIN( CWnd, IPropertySet )
	AddProperty( "WindowPos", "WindowPos" );
	AddProperty( "WindowCaption", "WindowCaption" );
	AddProperty( "WindowSize", "WindowSize" );
	AddProperty( "WindowVisible", "WindowVisible" );
	AddProperty( "WindowEnable", "WindowEnable" );
	AddProperty( "WindowOwer","WindowOwer" );
DECLARE_PROPERTYSET_END


/*
 *transparentDlgBase���Լ� ���ڹ��캯�������������
 */
DECLARE_PROPERTYSET_BEGIN( CTransparentDlgBase, CWndPropertySet )
	AddProperty( "Image", "TransparentDlgBaseImage" ); 
	AddProperty( "MoveStatus", "TransparentDlgBaseMoveStatus" );
	AddProperty( "AutoHideStatus","TransparentDlgBaseAutoHideStatus" ); 
	AddProperty( "BkStretch","TransparentDlgBaseBkStretch" ); 
DECLARE_PROPERTYSET_END



//�������Լ�
DECLARE_PROPERTYSET_BEGIN( CTransparentDlg, CTransparentDlgBasePropertySet )  
DECLARE_PROPERTYSET_END 
 
 


/*
 *	Ĭ�ϰ�ť���Լ� ���̳���wnd������
 */
DECLARE_PROPERTYSET_BEGIN( CButton, CWndPropertySet )
AddProperty( "CButtonCheckState", "CButtonCheckState" ); 
DECLARE_PROPERTYSET_END
/*
 *	Ĭ�ϱ༭�����Լ� ���̳���wnd������
 */
DECLARE_PROPERTYSET_BEGIN( CEdit, CWndPropertySet )
 // ��������������뵽�������
DECLARE_PROPERTYSET_END

/*
 *	Ĭ�Ͼ�̬�ؼ����Լ� ���̳���wnd������
 */
DECLARE_PROPERTYSET_BEGIN( CStatic, CWndPropertySet )
// ��������������뵽�������
DECLARE_PROPERTYSET_END
/*
 *	Ĭ���б����Լ� ���̳���wnd������
 */
DECLARE_PROPERTYSET_BEGIN( CList, CWndPropertySet )
 // ��������������뵽�������
DECLARE_PROPERTYSET_END


/*
 *	Ĭ��IP�ؼ����Լ� ���̳���wnd������
 */
DECLARE_PROPERTYSET_BEGIN( CIPAddressCtrl, CWndPropertySet ) 
 AddProperty( "CIPAddressCtrlData", "CIPAddressCtrlData" );
DECLARE_PROPERTYSET_END


/*
 *	Ĭ��CSliderCtrl�ؼ����Լ� ���̳���wnd������
 */
DECLARE_PROPERTYSET_BEGIN( CSliderCtrl, CWndPropertySet ) 
 AddProperty( "CSliderCtrlRange", "CSliderCtrlRange" );
 AddProperty( "CSliderCtrlPos", "CSliderCtrlPos" );
DECLARE_PROPERTYSET_END


} // namespace AutoUIFactory end

/** @} */ 

#endif // !defined(AFX_MFCDEFAULTWNDPROPERTYSET_H__296760B5_4C36_434F_9543_347830BCA392__INCLUDED_)
