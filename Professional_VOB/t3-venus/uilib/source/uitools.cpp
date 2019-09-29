/********************************************************************
	ģ����:      UILib
	�ļ���:      uitools.cpp
	����ļ�:    UILibHead.h
	�ļ�ʵ�ֹ��� UI�е�һЩ���ù��ܼ���
    ���ߣ�       ������
	�汾��       1.0
--------------------------------------------------------------------------------
	�޸ļ�¼:
	��  ��		�汾		�޸���		�߶���    �޸�����
	2004/4/8	1.0			������                 ����

*********************************************************************/


#include "stdafx.h"
#include "UILIbHead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CUITools::CUITools()
{
}

CUITools::~CUITools()
{
}

/*====================================================================
������	��    CreateImage
����		������BMP��Դ�ŵõ�ͼƬ���
�㷨ʵ��	������ѡ�
����ȫ�ֱ�������
�������˵����nBitmap ͼƬ��Դ��
����ֵ˵����  ͼƬ��������ɹ�ΪNULL��
----------------------------------------------------------------------
�޸ļ�¼:
��  ��		�汾		�޸���		�߶���    �޸�����
2004/04/08	1.0			������                  ����
====================================================================*/
HBITMAP CUITools::CreateImage(UINT nBitmap)
{
    if (nBitmap == 0)
    {
        return NULL;
    }

    HINSTANCE	hInstResource	= NULL;
	
	// Find correct resource handle
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nBitmap), RT_BITMAP);
    if (hInstResource == NULL)
    {
        return NULL;
    }
    return (HBITMAP)::LoadImage(hInstResource, MAKEINTRESOURCE(nBitmap), IMAGE_BITMAP, 0, 0, 0);
}

/*====================================================================
������	��    DrawStepBk
����		��������ɫ
�㷨ʵ��	������ɫ������ɫ�任���ٶȣ�Ȼ�����ÿ�ε���ɫ��Ϊ�����Ч��
                ÿ�λ������ص���
����ȫ�ֱ�������
�������˵����pDC ��ͼ��CDCָ��
              crFrom ��ʼ����ɫ�������棨������ߣ�����ɫ��
              crTo ��������ɫ�������棨�����ұߣ�����ɫ��
              rcAll  ������ɫ�������������Χ��
              rcItem ʵ�ʵ���ͼ������
              nStyle ����ķ���STEPBK_VERT�����ϵ��£�STEPBK_HORZ�������ҡ�
����ֵ˵����  ��
----------------------------------------------------------------------
�޸ļ�¼:
��  ��		�汾		�޸���		�߶���    �޸�����
2004/04/08	1.0			������                  ����
2004/04/23	1.0			������                  �Ż�
====================================================================*/
void CUITools::DrawStepBk(CDC *pDC, COLORREF crFrom, COLORREF crTo, CRect rcAll, CRect rcItem, UINT nStyle)
{
    if (rcItem.IsRectEmpty())
    {
        rcItem = rcAll;
    }

    if (crFrom == crTo)
    {
        pDC->FillSolidRect(rcItem, crTo);
        return;
    }
    
    const int nStep = 1;
    int rFrom,gFrom,bFrom;
    int rTo, gTo, bTo;
    
    rFrom = (crFrom & 0x000000ff) << 8;
    gFrom = crFrom & 0x0000ff00;
    bFrom = crFrom & 0x00ff0000;

    rTo = (crTo & 0x000000ff) << 8;
    gTo = crTo & 0x0000ff00;
    bTo = crTo & 0x00ff0000;
    

    int nLength;

    if (nStyle == STEPBK_VERT)
    {
        nLength = rcAll.Height()/nStep;
    }
    else
    {
        nLength = rcAll.Width()/nStep;
    }
    
    int dbMarginr = (rTo-rFrom)/nLength;
    int dbMarging = (gTo-gFrom)/nLength;
    int dbMarginb = (bTo-bFrom)/nLength;

    COLORREF cr;
    if (nStyle == STEPBK_VERT)
    {
        rFrom += (rcItem.top-rcAll.top)*dbMarginr;
        gFrom += (rcItem.top-rcAll.top)*dbMarging;
        bFrom += (rcItem.top-rcAll.top)*dbMarginb;
        for (int y=rcItem.top; y < rcItem.bottom; y+=nStep)
        {
           cr = (bFrom & 0x00ff0000) | (gFrom & 0x0000ff00) | (rFrom >> 8);
           pDC->FillSolidRect(rcItem.left, y, rcItem.right-rcItem.left, nStep, cr);
           rFrom += dbMarginr;
           gFrom += dbMarging;
           bFrom += dbMarginb;
          
        }
    }
    else
    {
        rFrom += (rcItem.left-rcAll.left)*dbMarginr;
        gFrom += (rcItem.left-rcAll.left)*dbMarging;
        bFrom += (rcItem.left-rcAll.left)*dbMarginb;
        for (int x=rcItem.left; x < rcItem.right; x+=nStep)
        {
           cr = (bFrom & 0x00ff0000) | (gFrom & 0x0000ff00) | (rFrom >> 8);
           pDC->FillSolidRect(x, rcItem.top, nStep, rcItem.bottom-rcItem.top, cr);
           rFrom += dbMarginr;
           gFrom += dbMarging;
           bFrom += dbMarginb;
        }
    }
}
HRGN CUITools::GenerateRegion(HBITMAP hBitmap, BYTE red, BYTE green, BYTE blue)
{
	WORD wBmpWidth,wBmpHeight;
	HRGN hRgn, hTmpRgn;
	
	// 24bit pixels from the bitmap
	BYTE *pPixels = Get24BitPixels(hBitmap, &wBmpWidth, &wBmpHeight);
	if (!pPixels) return NULL;
	
	// create our working region
	hRgn = CreateRectRgn(0,0,wBmpWidth,wBmpHeight);
	if (!hRgn) { delete pPixels; return NULL; }
	
	DWORD p=0;
	for (WORD y=0; y<wBmpHeight; y++)
	{
		for (WORD x=0; x<wBmpWidth; x++)
		{
			BYTE jRed   = pPixels[p+2];
			BYTE jGreen = pPixels[p+1];
			BYTE jBlue  = pPixels[p+0];
			
			if (jRed==red && jGreen==green && jBlue==blue)
			{
				// remove transparent color from region
				hTmpRgn = CreateRectRgn(x,y,x+1,y+1);
				CombineRgn(hRgn, hRgn, hTmpRgn, RGN_XOR);
				DeleteObject(hTmpRgn);
			}
			
			// next pixel
			p+=3;
		}
	}
	
	// release pixels
	delete pPixels;
	
	// return the region
	return hRgn;
}

BYTE* CUITools::Get24BitPixels(HBITMAP pBitmap, WORD *pwWidth, WORD *pwHeight)
{
	BITMAP bmpBmp;
	LPBITMAPINFO pbmiInfo;
	BITMAPINFO bmiInfo;
	WORD wBmpWidth, wBmpHeight;
	
	GetObject(pBitmap, sizeof(bmpBmp),&bmpBmp);
	pbmiInfo   = (LPBITMAPINFO)&bmpBmp;
	
	wBmpWidth  = (WORD)pbmiInfo->bmiHeader.biWidth;
	wBmpWidth -= (wBmpWidth%4);
	wBmpHeight = (WORD)pbmiInfo->bmiHeader.biHeight;
	
	*pwWidth  = wBmpWidth;
	*pwHeight = wBmpHeight;
	
	BYTE *pPixels = new BYTE[wBmpWidth*wBmpHeight*3];
	if (!pPixels) return NULL;
	
	HDC hDC =::GetWindowDC(NULL);
	
	bmiInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmiInfo.bmiHeader.biWidth = wBmpWidth;
	bmiInfo.bmiHeader.biHeight = -wBmpHeight;
	bmiInfo.bmiHeader.biPlanes = 1;
	bmiInfo.bmiHeader.biBitCount = 24;
	bmiInfo.bmiHeader.biCompression = BI_RGB;
	bmiInfo.bmiHeader.biSizeImage = wBmpWidth*wBmpHeight*3;
	bmiInfo.bmiHeader.biXPelsPerMeter = 0;
	bmiInfo.bmiHeader.biYPelsPerMeter = 0;
	bmiInfo.bmiHeader.biClrUsed = 0;
	bmiInfo.bmiHeader.biClrImportant = 0;
	
	// get pixels from the original bitmap converted to 24bits
	int iRes = GetDIBits(hDC,pBitmap,0,wBmpHeight,(LPVOID)pPixels,&bmiInfo,DIB_RGB_COLORS);
	
	// release the device context
	::ReleaseDC(NULL,hDC);
	
	// if failed, cancel the operation.
	if (!iRes)
	{
		delete pPixels;
		return NULL;
	};
	
	// return the pixel array
	return pPixels;
}

