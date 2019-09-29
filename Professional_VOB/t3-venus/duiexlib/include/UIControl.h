#ifndef __UICONTROL_H__
#define __UICONTROL_H__

#pragma once

namespace DuiLib {

/////////////////////////////////////////////////////////////////////////////////////
//
const static LPCTSTR pTopleft = _T("list_topleft.png");
const static LPCTSTR pTopmiddle = _T("list_topmiddle.png");
const static LPCTSTR pTopright = _T("list_topright.png");
const static LPCTSTR pMiddleleft = _T("list_middleleft.png");
const static LPCTSTR pMiddleright = _T("list_middleright.png");
const static LPCTSTR pBottomleft = _T("list_bottomleft.png");
const static LPCTSTR pBottommiddle = _T("list_bottommiddle.png");
const static LPCTSTR pBottomright = _T("list_bottomright.png");

typedef CControlUI* (CALLBACK* FINDCONTROLPROC)(CControlUI*, LPVOID);
class CContainerUI;
class UILIB_API CControlUI
{
public:
    CControlUI();
    virtual ~CControlUI();

public:
    virtual /*CStdString*/tString GetName() const;
    virtual void SetName(LPCTSTR pstrName);
    virtual LPCTSTR GetClass() const;
    virtual LPVOID GetInterface(LPCTSTR pstrName);
    virtual UINT GetControlFlags() const;

    virtual bool Activate();
    virtual CPaintManagerUI* GetManager() const;
    virtual void SetManager(CPaintManagerUI* pManager, CControlUI* pParent, bool bInit = true);
    virtual CControlUI* GetParent() const;

    // �ı����
    virtual CStdString GetText() const;
    virtual void SetText(LPCTSTR pstrText);

    // ͼ�����
    DWORD GetBkColor() const;
    void SetBkColor(DWORD dwBackColor);
    DWORD GetBkColor2() const;
    void SetBkColor2(DWORD dwBackColor);
    DWORD GetBkColor3() const;
    void SetBkColor3(DWORD dwBackColor);
    /*virtual*/ LPCTSTR GetBkImage();
    /*virtual*/ void SetBkImage(LPCTSTR pStrImage);
    DWORD GetBorderColor() const;
    void SetBorderColor(DWORD dwBorderColor);
	DWORD GetFocusBorderColor() const;
	void SetFocusBorderColor(DWORD dwBorderColor);
    bool IsColorHSL() const;
    void SetColorHSL(bool bColorHSL);
    int GetBorderSize() const;
    void SetBorderSize(int nSize);
    SIZE GetBorderRound() const;
    void SetBorderRound(SIZE cxyRound);
	void SetImageInfo(LPCTSTR pStrImage);

	//bool xtiled ˮƽ����   bool ytiled ��ֱ����  Ĭ��falseΪ���� by ldy 2013.06.06
    bool DrawImage( HDC hDC, LPCTSTR pStrImage, LPCTSTR pStrModify = NULL, bool bTiledX = false, bool bTiledY = false );

	//bool bRepeatDraw �ظ�����(���ظ����ƣ����ֶ�����SetImageInfo�������λ�ȡͼƬ��Ϣ)
	bool DrawImageGDIPlus( HDC hDC, TEventUI& event, CPoint ptInCtl = CPoint( 0, 0), bool bRepeatDraw = true, LPCTSTR pStrImage = NULL, bool bSuportGesture = false );

	//֧��ͼƬƴ��(�߿����ͼƬ)  //by xhx
	virtual void DrawImageMosaicBk( HDC hDC );

	//������������ͼ�� ƴ�� Ϊһ��ͼƬ   bDrawCorner �Ƿ���Ҫ���߽�  //by xhx
	BOOL MosaicHoriImage( HDC hDC, LPCTSTR pstrImgLeft, LPCTSTR pstrImgRight, LPCTSTR pstrImgMiddle, int nFixedWidth, BOOL bDrawCorner = TRUE, CPoint ptInCtl = CPoint( 0, 0) );

	//�������� ����ͼ�� ƴ�� Ϊһ��ͼƬ  bDrawCorner �Ƿ���Ҫ���߽�  //by xhx
	BOOL MosaicVertImage( HDC hDC, LPCTSTR pstrImgTop, LPCTSTR pstrImgBottom, LPCTSTR pstrImgMiddle, int nFixedHeight, BOOL bDrawCorner = TRUE, CPoint ptInCtl = CPoint( 0, 0) );

    // λ�����
    virtual const RECT& GetPos() const;
    virtual void SetPos(RECT rc);
    virtual int GetWidth() const;
    virtual int GetHeight() const;
    virtual int GetX() const;
    virtual int GetY() const;
    virtual RECT GetPadding() const;
    virtual void SetPadding(RECT rcPadding); // ������߾࣬���ϲ㴰�ڻ���
    virtual SIZE GetFixedXY() const;         // ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ
    virtual void SetFixedXY(SIZE szXY);      // ��floatΪtrueʱ��Ч
    virtual int GetFixedWidth() const;       // ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ
    virtual void SetFixedWidth(int cx);      // Ԥ��Ĳο�ֵ
    virtual int GetFixedHeight() const;      // ʵ�ʴ�Сλ��ʹ��GetPos��ȡ������õ�����Ԥ��Ĳο�ֵ
    virtual void SetFixedHeight(int cy);     // Ԥ��Ĳο�ֵ
    virtual int GetMinWidth() const;
    virtual void SetMinWidth(int cx);
    virtual int GetMaxWidth() const;
    virtual void SetMaxWidth(int cx);
    virtual int GetMinHeight() const;
    virtual void SetMinHeight(int cy);
    virtual int GetMaxHeight() const;
    virtual void SetMaxHeight(int cy);
    virtual void SetRelativePos(SIZE szMove,SIZE szZoom);
    virtual void SetRelativeParentSize(SIZE sz);
    virtual TRelativePosUI GetRelativePos() const;
    virtual bool IsRelativePos() const;

    // �����ʾ
    virtual CStdString GetToolTip() const;
    virtual void SetToolTip(LPCTSTR pstrText);

    // ��ݼ�
    virtual TCHAR GetShortcut() const;
    virtual void SetShortcut(TCHAR ch);

    // �˵�
    virtual bool IsContextMenuUsed() const;
    virtual void SetContextMenuUsed(bool bMenuUsed);

    // �û�����
    virtual UINT_PTR GetTag() const;						// �������ݣ����û�ʹ��
    virtual void SetTag(UINT_PTR pTag);						// �������ݣ����û�ʹ��      line by ldy 130723: �����б���Ϊ���ITEM����

    // һЩ��Ҫ������
    virtual bool IsVisible() const;
    virtual void SetVisible(bool bVisible = true);
    virtual void SetInternVisible(bool bVisible = true);	// �����ڲ����ã���ЩUIӵ�д��ھ������Ҫ��д�˺���
    virtual bool IsEnabled() const;
    virtual void SetEnabled(bool bEnable = true);
    virtual bool IsMouseEnabled() const;
    virtual void SetMouseEnabled(bool bEnable = true);
    virtual bool IsFocused() const;
    virtual void SetFocus();
    virtual bool IsFloat() const;
    virtual void SetFloat(bool bFloat = true);

	virtual bool IsGesture() const;
	virtual void SetGesture(bool bGetture = false);

	void SetMosaicBk(bool bIsMosaicBk){ m_bIsMosaicBk = bIsMosaicBk;};
	bool GetMosaicBk(){return m_bIsMosaicBk;};

	void SetScrollVisible(bool bVisible){ m_bScrollVisible = bVisible; };
	bool GetScrollVisible(){ return m_bScrollVisible; };


    virtual CControlUI* FindControl(FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags);

    void Invalidate();
    bool IsUpdateNeeded() const;
    void NeedUpdate();
    void NeedParentUpdate();
    DWORD GetAdjustColor(DWORD dwColor);

    virtual void Init();
    virtual void DoInit();

    virtual void Event(TEventUI& event);
    virtual void DoEvent(TEventUI& event);

    virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
    CControlUI* ApplyAttributeList(LPCTSTR pstrList);

    virtual SIZE EstimateSize(SIZE szAvailable);

    virtual void DoPaint(HDC hDC, const RECT& rcPaint);
    virtual void PaintBkColor(HDC hDC);
    virtual void PaintBkImage(HDC hDC);
    virtual void PaintStatusImage(HDC hDC);
    virtual void PaintText(HDC hDC);
    virtual void PaintBorder(HDC hDC);

    virtual void DoPostPaint(HDC hDC, const RECT& rcPaint);


	//�õ��ؼ�rect
	void SetControlRect(RECT rc){ m_rcItem= rc; };
	RECT GetControlRect(){ return m_rcItem;};
	RECT GetControlPaintRect(){ return m_rcPaint;};	

	//TImageInfo* GetScrollBkImgInfo(){return m_ImgInfoTop;};
	

public:
    CEventSource OnInit;
    CEventSource OnDestroy;
    CEventSource OnSize;
    CEventSource OnEvent;
    CEventSource OnNotify;

protected:

	//������Ϣ����ַ�   2013.07.24 by ldy
	virtual void OnGestureBeg( TEventUI& event );			//POINT ptFrom
	virtual void OnGestureEnd( TEventUI& event );			//POINT ptFrom
	virtual BOOL OnGestureZoom( TEventUI& event );			//POINT ptCenter, long lDelta
	virtual BOOL OnGesturePan( TEventUI& event );			//POINT ptFrom, POINT ptTo
	virtual BOOL OnGestureRotate( TEventUI& event );		//POINT ptCenter, double dblAngle
	virtual BOOL OnGestureTwoFingerTap( TEventUI& event );	//POINT ptCenter
	virtual BOOL OnGesturePressAndTap( TEventUI& event );	//POINT ptFirstFinger, long lDelta


protected:
	CPaintManagerUI* m_pManager;
	CControlUI* m_pParent;
	CStdString m_sName;
	bool m_bUpdateNeeded;
	bool m_bMenuUsed;
	RECT m_rcItem;
	RECT m_rcPadding;
	SIZE m_cXY;
	SIZE m_cxyFixed;
	SIZE m_cxyMin;
	SIZE m_cxyMax;
	bool m_bVisible;
	bool m_bInternVisible;
	bool m_bEnabled;
	bool m_bMouseEnabled;
	bool m_bFocused;
	bool m_bFloat;
    bool m_bSetPos; // ��ֹSetPosѭ������
    TRelativePosUI m_tRelativePos;

    CStdString m_sText;
    CStdString m_sToolTip;
    TCHAR m_chShortcut;
    CStdString m_sUserData;
    UINT_PTR m_pTag;

    DWORD m_dwBackColor;
    DWORD m_dwBackColor2;
    DWORD m_dwBackColor3;
    CStdString m_sBkImage;
    DWORD m_dwBorderColor;
	DWORD m_dwFocusBorderColor;
    bool m_bColorHSL;
    int m_nBorderSize;
    SIZE m_cxyBorderRound;
    RECT m_rcPaint;

	bool m_bGesture;

	bool m_bIsMosaicBk;     //���Ʊ����Ƿ����ƴ��
	bool m_bScrollVisible;  //�������Ƿ�ɼ�
	TImageInfo* m_ptImageInfo;
	Image* m_pImage;    
};

} // namespace DuiLib

#endif // __UICONTROL_H__
