// MfcDefaultWndProperty.h: interface for the MfcDefaultWndProperty class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MFCDEFAULTWNDPROPERTY_H__066949F7_66EC_4E10_ABDB_0E55210594D6__INCLUDED_)
#define AFX_MFCDEFAULTWNDPROPERTY_H__066949F7_66EC_4E10_ABDB_0E55210594D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*
 * @defgroup DefaultProperty Ĭ�ϵ����� \n
 * ʹ������������Լ���������ԣ�ͬʱ�ᶨ���Ӧ��Value��Value����Ҫʵ�֣�
 * ������Ҫʵ����Ĭ�ϵ�һЩ����
 * ����������ˣ���Ҫ��CRegDefaultData����ȥע��������������ԣ������Ϳ�����xml����ʹ����
 * @author  Ĳ��ï
 * @version 1.0
 * @date  2011/05/31
 * @{
 */

#include "uifactorydef.h"
#include "IProperty.h"
namespace AutoUIFactory
{

#define DECLARE_VALUE_BEGIN( name, descrpit, default ) \
class Property_##name : public IProperty \
	{ \
public: \
    Property_##name() : IProperty( #name, descrpit, default){} \
	bool get( const Window* src, String& value ) const;	\
	bool get( const Window* src, IValue& value ) const;	\
	bool set( Window* tag, const String& value ); \
	bool set( Window* tag, const IValue& value ); \
}; \
class Value_##name : public IValue \
	{ \
public: \
	Value_##name() : IValue( #name ) {} 
	
#define DECLARE_VALUE_END };

/*
 * @name WindowName ������������
 * @{
 */
DECLARE_VALUE_BEGIN( WindowCaption,"Property to get/set window caption", "Window" )
String strCaption; // name
DECLARE_VALUE_END
/** @} */

/*
 * @name WindowPos ����λ������
 * @{
 */
DECLARE_VALUE_BEGIN( WindowPos,"Property to get/set window Position", "x:0y:0" )
int nX; // xpos
int nY; // ypos
DECLARE_VALUE_END
/** @} */

/*
 * @name WindowSize ���ڴ�С����
 * @{
 */
DECLARE_VALUE_BEGIN( WindowSize,"Property to get/set window Size", "h:100l:100" )
int nWidth; // w
int nHeight; // h
DECLARE_VALUE_END
/** @} */

/*
 * @name WindowVisible �����Ƿ�ɼ�����
 * @{
 */
DECLARE_VALUE_BEGIN( WindowVisible,"Property to get/set window visable", "true" )
bool bVisible;
DECLARE_VALUE_END
/** @} */

/*
 * @name WindowEnable �����Ƿ��������
 * @{
 */
DECLARE_VALUE_BEGIN( WindowEnable,"Property to get/set window enable", "true" )
bool bEnable;
DECLARE_VALUE_END
/** @} */

/*
 * @name WindowEnable �����Ƿ��������
 * @{
 */
DECLARE_VALUE_BEGIN( WindowOwer,"Property to get/set window Ower", "" )
Window* pWnd;
DECLARE_VALUE_END
/** @} */

/*
 * @name CTransparentDlg 
 * @{
 */
DECLARE_VALUE_BEGIN( TransparentDlgBaseMoveStatus,"Property to get/set TransparentDlg move status", "" )
bool bMove; //status 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentDlgBaseAutoHideStatus,"Property to get/set TransparentDlg lost focus hide status", "" )
bool bHide; //�ļ��� 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentDlgBaseImage,"Property to get/set TransparentDlg Image", "" )
String strImage; //�ļ��� 
DECLARE_VALUE_END
/** @} */

/*
 * @name CTransparentDlg 
 * @{
 */
DECLARE_VALUE_BEGIN( TransparentDlgBaseBkStretch,"Property to get/set TransparentDlg Bk Stretch", "" )
bool bIsBkStretch; //�Ƿ����챳��ͼƬ    Ĭ��Dlg����ͼ�ͶԻ���ͬ��С 
DECLARE_VALUE_END

/*
 * @name IPAddressCtrlData ��ȡIP��ַ
 * @{
 */
DECLARE_VALUE_BEGIN( CIPAddressCtrlData,"Property to get/set IP", "0" )
DWORD dwIP; // name
DECLARE_VALUE_END
/** @} */
/*
DECLARE_VALUE_BEGIN( BmpWndImage,"Property to get/set bmpwnd image", "" )
String strImage; // name
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( BmpWndMoveStatus,"Property to get/set bmpwnd Move status", "" )
bool bCanMove; // name
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( BmpWndStrethStatus,"Property to get/set bmpwnd is streth", "" )
bool bStreth; // name
DECLARE_VALUE_END
*/
DECLARE_VALUE_BEGIN( BmpWndChanageRgnStatus,"Property to get/set bmpwnd is change rgn", "" )
bool bChanageRgn; // name
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( LayoutAlgorithm,"Property to get/set TouchList Layout Algorithm", "" )
String strAlgorithm; // name
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( SortAlgorithm,"Property to get/set TouchList Sort Algorithm", "" )
String strAlgorithm; // name
DECLARE_VALUE_END


DECLARE_VALUE_BEGIN( TransparentListDrag,"Property to get/set TransparentList Drag status", "" )
bool bCanDrag; // name
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentListClickNoSel,"Property to get/set TransparentList ClickNoSel status", "" )
bool bNoSel; 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentListSelItem,"Property to get/set TransparentList get/set select item", "" )
unsigned long dwDataKey;  //����ʱʹ��
IBaseItem* pSelItem;      //��ȡʱʹ��
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentListOffset,"Property to get/set TransparentList offset", "" )
int nOffset;  
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentListClickFocus,"Property to get/set TransparentList clickfoucs status", "" )
bool bFocus;  
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentListBkgColor,"Property to get/set TransparentList bkgcolor status", "" )
Color colorBkg;   
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentListItemSizeSame,"Property to get/set TransparentList EveryItemSizeSame", "" )
bool bAllItemsSizeSame; 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentListMultiSel,"Property to get/set TransparentList MultiSel", "" )
bool bMultiSel; 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransHoriListOffset,"Property to get/set TransparentHoriList offset", "" )
int nOffset;  
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransHoriListSelItem,"Property to get/set TransparentHoriList SelItem", "" )
unsigned long dwDataKey;  //����ʱʹ��
IBaseItem* pSelItem;      //��ȡʱʹ�� 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentListData,"Property to get/set TransparentList Data", "" ) 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentListOver,"Property to get/set TransparentList Over", "" )
bool bOver;		//�Ƿ���ҪOver״̬
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentViewListImage,"Property to get/set TransparentViewList Image", "" )
String strImage; //�ļ��� 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( ViewListSelItem,"Property to get/set TransparentViewList select item", "" )
unsigned long dwDataKey;  //����ʱʹ��
IBaseItem* pSelItem;      //��ȡʱʹ��
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentViewListOver,"Property to get/set TransparentViewList Over", "" )
bool bOver;		//�Ƿ���ҪOver״̬
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( ViewListVertSliderOffset,"Property to get/set VertSlider Offset Position", "x:0y:0" )
int nX; // xpos
int nY; // ypos
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( ViewListHoriSliderOffset,"Property to get/set HoriSlider Offset Position", "x:0y:0" )
int nX; // xpos
int nY; // ypos
DECLARE_VALUE_END
 

/*
 * @name CButton check  ״̬
 * @{
 */
 /*Value Meaning 
 0 Set the button state to unchecked. 
 1 Set the button state to checked. 
 2 Set the button state to indeterminate. This value can be used only if the button has the BS_3STATE or BS_AUTO3STATE style.  
*/
DECLARE_VALUE_BEGIN( CButtonCheckState,"Property to get/set CButtonCheckState", "0" )
int   nCheckState; // checkstate
DECLARE_VALUE_END
/** @} */

DECLARE_VALUE_BEGIN( TransparentBaseWndMoveStatus,"Property to get/set TransparentBaseWnd move status", "" )
bool bMove; //status 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentBaseWndAutoHideStatus,"Property to get/set TransparentBaseWnd lost focus hide status", "" )
bool bHide; //�ļ��� 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentBaseWndImage,"Property to get/set TransparentBaseWnd Image", "" )
String strImage; //�ļ��� 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentListImage,"Property to get/set TransparentList Image", "" )
String strImage; //�ļ��� 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentListSingleImage,"Property to get/set TransparentList Image", "" )
String strImage; //ͼƬ�ļ���
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentBtnImage,"Property to get/set TransparentBtn Image", "" )
String strImage; //�ļ��� 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentBtnUseTimer,"Property to get/set TransparentBtn Image", "" )
bool bUseTimer; //use timer to send message when hold a button 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentCheckBtnImage,"Property to get/set TransparentCheckButton Image", "" )
String strImage; //�ļ��� 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentCheckBtnFontSpan,"Property to get/set TransparentCheckButton FontSpan", "" )
int nFontSpan; //button���ֵļ��
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentCheckBtnFontSize,"Property to get/set TransparentCheckButton FontSize", "" )
int nFontSize;
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentCheckBtnFontColor,"Property to get/set TransparentCheckButton FontColor", "" )
Color color; //��ɫ 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentSwitchBtnImage,"Property to get/set TransparentSwitchButton Image", "" )
String strImage; //�ļ��� 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( SwitchState,"Property to get/set TransparentSwitchButton SwitchState", "" )
bool bState; //on or off
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( SwitchBtnShowText,"Property to get/set TransparentSwitchButton ShowText", "" )
bool bShow;
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentEditImage,"Property to get/set TransparentEdit Image", "" )
String strImage; //�ļ��� 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentEditFontSize,"Property to get/set TransparentEdit FontSize", "" )
int size; //��С
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentEditFontColor,"Property to get/set TransparentEdit FontColor", "" )
Color color; //��ɫ 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentEditLimitLength,"Property to get/set TransparentEdit LimitLength", "" )
int length; //����
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentEditLimitInput,"Property to get/set TransparentEdit LimitInput", "" )
bool bInputLimit; //ֻ�����������ֺ�. - 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentEditFrontLen,"Property to get/set TransparentEdit FrontLen", "" )
int frontlen; //��һ�������ַ��������ƫ��
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentEditBackLen,"Property to get/set TransparentEdit BackLen", "" )
int backlen; //ͼ������Ҳ�ƫ��
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentEditShowIcon,"Property to get/set TransparentEdit ShowIcon", "" )
bool bShow; //
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentEditSearch,"Property to get/set TransparentEdit Search", "" )
bool bSearch; //
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentEditTipStr,"Property to get/set TransparentEdit TipStr", "" )
String strTip; //
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentEditAlign,"Property to get/set TransparentEdit Alignment", "" )
StringAlignment emAlign; //���뷽ʽ
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentEditDeleteText,"Property to get/set TransparentEdit DeleteText", "" )
bool bDelete; 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentEditDisableImg,"Property to get/set TransparentEdit DisableImg", "" )
bool bShowImg; 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentIPAddrCtrlImage,"Property to get/set TransparentIPAddrCtrl Image", "" )
String strImage; //�ļ��� 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentStaticImage,"Property to get/set TransparentStatic Image", "" )
String strImage; //�ļ��� 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentStaticFontColor,"Property to get/set TransparentStatic FontColor", "" )
Color color; //��ɫ 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentStaticFontSize,"Property to get/set TransparentStatic FontSize", "" )
int size; //��С
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentStaticFontName,"Property to get/set TransparentStatic FontName", "" )
String strFontName; //����
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentStaticFontStyle,"Property to get/set TransparentStatic FontStyle", "" )
FontStyle emStyle; //������
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentStaticAlign,"Property to get/set TransparentStatic Alignment", "" )
StringAlignment emAlign; //���뷽ʽ
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( StaticExBkTransparent,"Property to get/set   BkTransparent", "" )
BOOL bBKTransparent; //�����Ƿ���͸����
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( StaticExTextColor,"Property to get/set   StaticExTextColor", "" )
COLORREF clrfTextColor; // ������ɫ
DECLARE_VALUE_END
 
DECLARE_VALUE_BEGIN( StaticExFontSize,"Property to get/set   StaticExFontSize", "" )
int nFontSize; // �����С
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentSliderCtrlImage,"Property to get/set TransparentSliderCtrl Image", "" )
String strImage; //�ļ��� 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( LetterIndexImage,"Property to get/set LetterIndex Image", "" )
String strImage; //�ļ��� 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( BindList,"Property to get/set LetterIndex BindList", "" )
String strListName; //�б��� 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( IpEditData,"Property to get/set TransparentEdit Data", "0" )
DWORD dwIP; //Ip 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( SwitchBtnBindWnd,"Property to get/set TransparentSwitchButton BindWnd", "" )
String strWndName; //������ 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentSlideBlockImage,"Property to get/set TransparentSlideBlock Image", "" )
String strImage; //�ļ��� 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentCalendarImage,"Property to get/set TransparentCalendar Image", "" )
String strImage; //�ļ��� 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentDragBtnImage,"Property to get/set TransparentDragBtn Image", "" )
String strImage; //�ļ��� 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( DragButtonOnline,"Property to get/set TransparentDragBtn Online", "" )
bool bOnline;  
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( DragButtonSel,"Property to get/set TransparentDragBtn SelState", "" )
bool bSel;   
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( DragButtonData,"Property to get/set TransparentDragBtn Data", "" )
IData* pData;   
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentProgressImage,"Property to get/set TransparentProgress Image", "" )
String strImage;   
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( ProgressPos,"Property to get/set TransparentProgress Pos", "" )
int nPos;   
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( VirtualBatteryImage,"Property to get/set VirtualBattery Image", "" )
String strImage;   
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( BatteryLife,"Property to get/set VirtualBattery Life", "" )
int nLife;   
DECLARE_VALUE_END
/** @} */ 

/*
 * @name CSliderCtrlRange  
 * @{
 */
DECLARE_VALUE_BEGIN( CSliderCtrlRange,"Property to get/set Range", "0" )
int nMax;//���ֵ
int nMin;// ��Сֵ
DECLARE_VALUE_END
/** @} */

/*
 * @name CSliderCtrlPos  
 * @{
 */
DECLARE_VALUE_BEGIN( CSliderCtrlPos,"Property to get/set Pos", "0" )
int nPos;  //thumb ��ǰ����λ��
DECLARE_VALUE_END
/** @} */

DECLARE_VALUE_BEGIN( CTransparentListShowItemStatus,"Property to get/set always to show item", "true" )
bool bAlways;  //thumb ��ǰ����λ��
DECLARE_VALUE_END
/** @} */


DECLARE_VALUE_BEGIN( CTransparentSliderWndStyle,"Property to get/set TransparentSliderWnd  Style  ", "" )
int nStyle; //0:��ֱ�����slider  1��ˮƽ�����slider
DECLARE_VALUE_END


DECLARE_VALUE_BEGIN( CTransparentSliderWndImage,"Property to get/set TransparentSliderCtrl Image", "" )
String strImage; //�ļ��� 
DECLARE_VALUE_END

/*
 * @name CSliderCtrlRange  
 * @{
 */
DECLARE_VALUE_BEGIN( CTransparentSliderWndRange,"Property to get/set Range", "0" )
int nMax;//���ֵ
int nMin;// ��Сֵ
DECLARE_VALUE_END
/** @} */

/*
 * @name CSliderCtrlPos  
 * @{
 */
DECLARE_VALUE_BEGIN( CTransparentSliderWndPos,"Property to get/set Pos", "0" )
int nPos;  //thumb ��ǰ����λ��
DECLARE_VALUE_END
/** @} */

DECLARE_VALUE_BEGIN( TransparentComboBoxIPStyle,"Property to get/set TransparentComboBox IPStyle", "" )
bool bIsIPStyle;     //�Ƿ���IP����Combobox
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentComboBoxListBkColor,"Property to get/set TransparentComboBox ListBkColor", "" )
COLORREF clrfBkColor; // �б�����ɫ
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentComboBoxFontSize,"Property to get/set TransparentComboBox FontSize", "" )
int nFontSize;			 //�ֺŴ�С
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentComboBoxImage,"Property to get/set TransparentComboBox Image", "" )
String strImage;     //�ļ��� 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentComboBoxEditEdgeHeight,"Property to get/set TransparentComboBox EditEdgeHeight", "" )
int nEditEdgeHeight;	 //��ӦͼƬ��Դ�༭������Ե��С  Ŀ����List��Edit����
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentComboBoxDropListHeight,"Property to get/set TransparentComboBox DropListHeight", "" )
int nDropListHeight; //����Combobox�������߶�
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentComboBoxEditFrontLen,"Property to get/set TransparentComboBox EditFrontLen", "" )
int nComboEditFrontLen; //��һ�������ַ��������ƫ��
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentComboBoxEditBackLen,"Property to get/set TransparentComboBox EditBackLen", "" )
int nComboEditBackLen; //ͼ������Ҳ�ƫ��
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentComboBoxShowIcon,"Property to get/set TransparentComboBox ShowIcon", "" )
bool bIsShowIcon;
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentComboBoxReadOnly,"Property to get/set TransparentComboBox ReadOnly", "" )
bool bIsReadOnly;    //�Ƿ�ֻ��
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN(  TransparentComboBoxText ,"Property to get/set TransparentComboBox TEXT", "" )
String strComboText;     //combobox�༭���ı� 
DECLARE_VALUE_END

DECLARE_VALUE_BEGIN( TransparentComboBoxLimitLength,"Property to get/set TransparentEdit LimitLength", "" )
int length; //�������볤��
DECLARE_VALUE_END

} // namespace AutoUIFactory end
 

#endif // !defined(AFX_MFCDEFAULTWNDPROPERTY_H__066949F7_66EC_4E10_ABDB_0E55210594D6__INCLUDED_)
