/*****************************************************************************
ģ����      : ControlEx
�ļ���      : ControlEx.h
����ļ�    : 
�ļ�ʵ�ֹ���: ͨ�ÿؼ���װ
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/5/1       1.0         ����ӡ      ����
******************************************************************************/
#ifndef CONTROLEX_H
#define CONTROLEX_H

namespace DuiLib {

/////////////////////////////////////////////////////////////////////////////////////
//


/*****************************************************************************
* ����:			�������ҹ�����CContainerUI�ؼ�
* @return		�� 
* @remarks		��
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/6/9       1.0         ����ӡ      ����
******************************************************************************/
class UILIB_API CommonScrollContainerUI : public CScrollContainerUI
{
public:
	enum { SCROLL_TIMERID = 10 };

	CommonScrollContainerUI();											//ScrollContainerUI����

	void DoEvent(TEventUI& event);
	void SetPos(RECT rc);
	tString GetImage(){ return m_strImage;};
	void SetImage( const tString& strImage, double dblZoomRatio = 1.0, bool bFixedYX = false );   // double	dblZoomRatio ����, bool bFixedYX = true���ÿ��ΪͼƬ�߿�

	SIZE GetContainSize(){return m_szContain;};
	void SetContainSize(SIZE szContain){ m_szContain = szContain; };

	void UpdateUILayout( double dblZoomRatio = 1.0, double dbAngle = 0 );										//���´��ڲ���  ���¼��������ͼ��ʾ

private:
	UINT m_uButtonState;
	POINT m_ptLastMouse;
	LONG m_dwDelayDeltaY;
	DWORD m_dwDelayNum;
	DWORD m_dwDelayLeft;

	tString m_strImage;

	SIZE m_szContain;

	TImageInfo* m_pImgData;									//�洢ImageInfo�����ظ�GetImgInfo�����Ч�ʼ������������

	tString m_strScrollXml;
};


/*****************************************************************************
* ����:			CommonScrollContainerUI�еĹ�������
* @return		�� 
* @remarks		��
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/7/5       1.0         ����ӡ      ����
******************************************************************************/
class UILIB_API CScollImageUI : public CLabelUI
{
public:
	CScollImageUI();

	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);
	UINT GetControlFlags() const;

	bool Activate();
	void SetEnabled(bool bEnable = true);
	void DoEvent(TEventUI& event);

 	LPCTSTR GetNormalImage();
 	void SetNormalImage( LPCTSTR pStrImage, TImageInfo* pImgData = NULL );
	SIZE EstimateSize(SIZE szAvailable);
	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	void PaintStatusImage(HDC hDC);

	void SetScrollContainerUI(CommonScrollContainerUI* pScrollContainerUI);

private:
	//������Ϣ����ַ�   2013.07.24 by ldy
	virtual void OnGestureBeg( TEventUI& event );			//POINT ptFrom
	virtual void OnGestureEnd( TEventUI& event );			//POINT ptFrom
	virtual BOOL OnGestureZoom( TEventUI& event );			//POINT ptCenter, long lDelta
	virtual BOOL OnGesturePan( TEventUI& event );			//POINT ptFrom, POINT ptTo
	virtual BOOL OnGestureRotate( TEventUI& event );		//POINT ptCenter, double dblAngle
	virtual BOOL OnGestureTwoFingerTap( TEventUI& event );	//POINT ptCenter
	virtual BOOL OnGesturePressAndTap( TEventUI& event );	//POINT ptFirstFinger, long lDelta

protected:
	UINT m_uButtonState;
	CStdString m_strNormalImage;
	CommonScrollContainerUI* m_pScrollContainerUI; 

	TImageInfo* m_pImgData;									//�洢ImageInfo�����ظ�GetImgInfo�����Ч�ʼ������������

	TEventUI m_eventUI;
	double m_dbAngle;
};


} // namespace DuiLib

#endif CONTROLEX_H
