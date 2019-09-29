// IBaseItem.cpp: implementation of the IBaseItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h" 
#include "item.h"
#include "srcManage.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
  
CImageItem::CImageItem( Image* pImage, int nWidht, int nHeight, String strFunc, 
					   String strLayout, String strSort, bool bCanDrag, bool bCanMove, 
                       CPoint ptOffset, EmItemStatus emItemStatus, bool bAlwaysShow, CPoint ptImgOffset ) : 
IBaseItem( nWidht, nHeight, strFunc, strLayout, strSort, bCanDrag, bCanMove, ptOffset, emItemStatus, bAlwaysShow )  
/*m_pImgNormal( pImage ),  m_pImgDown( pImage ), m_pImgSel( pImage ) , m_pImgDisable( pImage )*/
{
	m_pImgNormal = pImage;
	m_pImgDown = pImage;
	m_pImgSel  = pImage;
	m_pImgDisable = pImage;
    m_pImgOver = pImage;
    m_ptImgOffset = ptImgOffset;
}

CImageItem::CImageItem( String strImageFolder , int nWidht, int nHeight, String strFunc,
					   String strLayout, String strSort, bool bCanDrag, bool bCanMove, 
                       CPoint ptOffset, EmItemStatus emItemStatus, bool bAlwaysShow, CPoint ptImgOffset ) : 
IBaseItem( nWidht, nHeight, strFunc, strLayout, strSort, bCanDrag, bCanMove, ptOffset, emItemStatus, bAlwaysShow )
{
	m_pImgNormal = 0;
	m_pImgDown = 0;
	m_pImgSel  = 0;
	m_pImgDisable = 0;
    m_pImgOver = 0;

	SetImageFolder( strImageFolder );
    m_ptImgOffset = ptImgOffset;
}

void CImageItem::SetImageFolder( String strFolder )
{ 
	String strFile = strFolder + "//" + strNormalImg;
	m_pImgNormal  = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" +  strSelImg;
	m_pImgSel  = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + strOverImg;
	m_pImgOver = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" +  strDisableImg;
	m_pImgDisable  = CSrcManage::GetImage( strFile.c_str() ); 
}

void CImageItem::SetImagePath( String strImagePath )
{ 
	m_pImgNormal  = CSrcManage::GetImage( strImagePath.c_str() );
	m_pImgSel  = CSrcManage::GetImage( strImagePath.c_str() );
	m_pImgOver = CSrcManage::GetImage( strImagePath.c_str() );
	m_pImgDisable  = CSrcManage::GetImage( strImagePath.c_str() ); 
}

void CImageItem::Draw( IArgs* pArgs )
{
	if ( Args_Graphics* p = dynamic_cast<Args_Graphics*>( pArgs ) )
	{
		Graphics* pGraphics = p->m_pGraphics;
		Image* pDrawImage = m_pImgNormal;
		switch ( m_emItemStatus )
		{
		case emItemStatusSel:
			{
				if ( m_pImgSel != 0 )
				{
					pDrawImage = m_pImgSel;
				}
			}
			break;
		case emItemStatusDown:
			{
				if ( m_pImgDown != 0 )
				{
					pDrawImage = m_pImgDown;
				}
				else if ( m_pImgSel != 0 )
				{
					pDrawImage = m_pImgSel;
				}
			}
			break;
		case emItemStatusOver:
			{
				if ( m_pImgOver != 0 )
				{
					pDrawImage = m_pImgOver;
				}
			}
			break;
		case emItemStatusDisable:
			{
				if ( m_pImgDisable != 0 )
				{
					pDrawImage = m_pImgDisable;
				}
			}
			break;
		default:
			{
				pDrawImage = m_pImgNormal;
			}
			break;
		}	
		if ( pDrawImage != NULL && pGraphics != NULL )
		{	 
			//ȥ��ƫ���� 2012-8-6 ���xp��ocx���б�ֻ����ʾ�߰˰ٸ���Ŀ������ by yjj
 	//		pGraphics->DrawImage( pDrawImage, m_rcItem.left + m_ptImgOffset.x + p->m_ptOffset.x,
      //           m_rcItem.top + m_ptImgOffset.y + p->m_ptOffset.y, pDrawImage->GetWidth(), pDrawImage->GetHeight() );	    ���б��ITEM��ͼƬ������Χ��ֻ����ʾһ���֣�������������Ӧ���� -�ֲܾ�
			//�޸�Ϊ1080P����Ӧ 2013.1.17 by577 
 			pGraphics->DrawImage( pDrawImage, m_rcItem.left + m_ptImgOffset.x + p->m_ptOffset.x,
                   m_rcItem.top + m_ptImgOffset.y + p->m_ptOffset.y, m_rcItem.Width(), m_rcItem.Height() );				
		} 
 
	}
}

IBaseItem* CImageItem::Clone()
{
	CImageItem* pItem = new CImageItem( m_pImgNormal, m_rcItem.Width(), m_rcItem.Height(), m_strFunc, 
        m_strLayoutAlgorithm, m_strSortAlgorithm, m_bCanDrag, m_bCanMove, m_ptOffset, m_emItemStatus, m_bAlwaysShow, m_ptImgOffset );	
	pItem->m_pImgNormal  = m_pImgNormal;
    pItem->m_pImgDown  = m_pImgDown;
	pItem->m_pImgDisable = m_pImgDisable;
	pItem->m_pImgSel = m_pImgSel;
	pItem->m_pImgOver = m_pImgOver;
	if ( m_pData != NULL )
	{
		pItem->SetUserData( m_pData );
	}
	return pItem;
}
 

void CImageItem::SetImage( UINT nNormalImage, UINT nSelImage, const CString& strImgType, UINT nDownImage )
{
	m_pImgNormal = CSrcManage::GetImage( nNormalImage, strImgType );
	m_pImgSel = CSrcManage::GetImage( nSelImage, strImgType );
	m_pImgDown = CSrcManage::GetImage( nDownImage, strImgType );
}

/*---------------------------------------------------------------------
* ��	����CListItem
* ��    �ܣ��б���Ŀ
* ����˵����ͼƬƴ�Ӷ��ɣ����������б��һ������Ŀ
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/09/01	v1.0		Ф��Ȼ		  ����
----------------------------------------------------------------------*/
const String CListItem::strNormalLeft = "NormalLeft.png";
const String CListItem::strNormalMid = "NormalMid.png";
const String CListItem::strNormalRight = "NormalRight.png";
const String CListItem::strFocusLeft = "FocusLeft.png";
const String CListItem::strFocusMid = "FocusMid.png";
const String CListItem::strFocusRight = "FocusRight.png";
const String CListItem::strCutLine = "cutline.png";

CListItem::CListItem( String strImageFolder, int nWidht, int nHeight, String strFunc, 
					 String strLayout, String strSort, 
					 bool bCanDrag, bool bCanMove, CPoint ptOffset, EmItemStatus emItemStatus, bool bAlwaysShow ) :
	IBaseItem( nWidht, nHeight, strFunc, strLayout, strSort, bCanDrag, bCanMove, ptOffset, emItemStatus, bAlwaysShow )
{
	SetImageFolder( strImageFolder );
}

void CListItem::Draw( IArgs* pArgs )
{
	if ( Args_Graphics* p = dynamic_cast<Args_Graphics*>( pArgs ) )
	{
		Graphics* pGraphics = p->m_pGraphics;

		Image *pImgLeft = NULL;
		Image *pImgMiddle = NULL;
		Image *pImgRight = NULL;
		if ( m_emItemStatus == emItemStatusSel || m_emItemStatus == emItemStatusDown )
		{
			pImgLeft = m_pImgFocusLeft;
			pImgMiddle = m_pImgFocusMiddle;
			pImgRight = m_pImgFocusRight;
		}
		else
		{
			pImgLeft = m_pImgNormalLeft;
			pImgMiddle = m_pImgNormalMiddle;
			pImgRight = m_pImgNormalRight;
		}
		
        // m_rcItem.left;  2012-8-6 ���xp��ocx���б�ֻ����ʾ�߰˰ٸ���Ŀ������ by yjj
		CPoint ptBegin = m_rcItem.TopLeft() + p->m_ptOffset;
	 
        ImageAttributes ImgAtt;
        ImgAtt.SetWrapMode(WrapModeTileFlipXY);

		if ( pImgLeft != NULL && pImgMiddle != NULL && pImgRight != NULL && pImgMiddle->GetWidth() != 0 )
		{		
			unsigned int dwMiddleWidth = 0;
			if ( m_rcItem.Width() > pImgLeft->GetWidth() + pImgRight->GetWidth() )
			{
				dwMiddleWidth = m_rcItem.Width() - pImgLeft->GetWidth() - pImgRight->GetWidth();
			}
			unsigned int nPosX = ptBegin.x + pImgLeft->GetWidth();
			
			// ��
			pGraphics->DrawImage( pImgLeft, ptBegin.x, ptBegin.y, pImgLeft->GetWidth(), pImgLeft->GetHeight()/*m_rcItem.Height()*/ );
			// ��
			pGraphics->DrawImage( pImgRight, ptBegin.x + m_rcItem.Width() - pImgRight->GetWidth(), 
				                        ptBegin.y, pImgRight->GetWidth(), pImgRight->GetHeight()/*m_rcItem.Height()*/ );			
			// ��
            //�м�ͼƬ��Ϊֱ�����죬��߻���Ч�� -xcr
            Rect rcDes(nPosX, ptBegin.y, dwMiddleWidth, pImgMiddle->GetHeight());
            pGraphics->DrawImage( pImgMiddle, rcDes, 0, 0, pImgMiddle->GetWidth(), pImgMiddle->GetHeight(), UnitPixel, &ImgAtt );
			//for ( unsigned int nIndex = 0; nIndex < ( dwMiddleWidth / pImgMiddle->GetWidth() ); nIndex++ )
			//{
			//	pGraphics->DrawImage( pImgMiddle, nPosX,ptBegin.y, pImgMiddle->GetWidth(), pImgMiddle->GetHeight()/*m_rcItem.Height()*/ );
			//	nPosX += pImgMiddle->GetWidth();
			//}
			//pGraphics->DrawImage( pImgMiddle, nPosX, ptBegin.y, dwMiddleWidth % pImgMiddle->GetWidth(), pImgMiddle->GetHeight()/*m_rcItem.Height()*/ );
		}

		if ( m_pImgCutLine != NULL && m_pImgCutLine->GetWidth() != 0 )
		{
			//�ָ������Ҹ���2����
            int nLineLength = m_rcItem.Width() - 4;
			unsigned int nPosLine = ptBegin.x + 2;// m_rcItem.left;  2012-8-6 ���xp��ocx���б�ֻ����ʾ�߰˰ٸ���Ŀ������ by yjj

            Rect rcDes(nPosLine, ptBegin.y + m_rcItem.Height(), nLineLength, m_pImgCutLine->GetHeight());
            pGraphics->DrawImage( m_pImgCutLine, rcDes, 0, 0, m_pImgCutLine->GetWidth(), m_pImgCutLine->GetHeight(), UnitPixel, &ImgAtt );
			/*for ( unsigned int nIndex = 0; nIndex < ( nLineLength / m_pImgCutLine->GetWidth() ); nIndex++ )
			{
				pGraphics->DrawImage( m_pImgCutLine, nPosLine, ptBegin.y + m_rcItem.Height() , m_pImgCutLine->GetWidth(), m_pImgCutLine->GetHeight() );
				nPosLine += m_pImgCutLine->GetWidth();
			}
			pGraphics->DrawImage( m_pImgCutLine, nPosLine, ptBegin.y + m_rcItem.Height() , nLineLength % m_pImgCutLine->GetWidth(), m_pImgCutLine->GetHeight() );*/
		}
	}
}

void CListItem::SetItemHeight( int nHeight )
{
	int nWidth = m_rcItem.Width();
	m_rcItem.SetRect( 0, 0, nWidth, nHeight );
}

void CListItem::SetImageFolder( String strFolder )
{
	if ( "" == strFolder )
	{
		return;
	}
	String strFile = strFolder + "\\" + CListItem::strNormalLeft;
	m_pImgNormalLeft = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "\\" + CListItem::strNormalMid;
	m_pImgNormalMiddle = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "\\" + CListItem::strNormalRight;
	m_pImgNormalRight = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "\\" + CListItem::strFocusLeft;
	m_pImgFocusLeft = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "\\" + CListItem::strFocusMid;
	m_pImgFocusMiddle = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "\\" + CListItem::strFocusRight;
	m_pImgFocusRight = CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "\\" + CListItem::strCutLine;
	m_pImgCutLine = CSrcManage::GetImage( strFile.c_str() );
}

void CListItem::SetImage( UINT nImgNormalLeft, UINT nImgNormalMiddle, UINT nImgNormalRight, 
		UINT nImgFocusLeft, UINT nImgFocusMiddle, UINT nImgFocusRight, UINT nImgCutLine )
{
	m_pImgNormalLeft = CSrcManage::GetImage( nImgNormalLeft, "PNG" );
	m_pImgNormalMiddle = CSrcManage::GetImage( nImgNormalMiddle, "PNG" );
	m_pImgNormalRight = CSrcManage::GetImage( nImgNormalRight, "PNG" );
	m_pImgFocusLeft = CSrcManage::GetImage( nImgFocusLeft, "PNG" );
	m_pImgFocusMiddle = CSrcManage::GetImage( nImgFocusMiddle, "PNG" );
	m_pImgFocusRight = CSrcManage::GetImage( nImgFocusRight, "PNG" );
	m_pImgCutLine = CSrcManage::GetImage( nImgCutLine, "PNG" );
}

IBaseItem* CListItem::Clone()
{
	CListItem* pItem = new CListItem( "", m_rcItem.Width(), m_rcItem.Height(), 
		m_strFunc, m_strLayoutAlgorithm, m_strSortAlgorithm, m_bCanDrag, m_bCanMove, m_ptOffset, m_emItemStatus, m_bAlwaysShow );
	pItem->m_pImgNormalLeft = m_pImgNormalLeft;
	pItem->m_pImgNormalMiddle = m_pImgNormalMiddle;
	pItem->m_pImgNormalRight = m_pImgNormalRight;
	pItem->m_pImgFocusLeft = m_pImgFocusLeft;
	pItem->m_pImgFocusMiddle = m_pImgFocusMiddle;
	pItem->m_pImgFocusRight = m_pImgFocusRight;
	pItem->m_pImgCutLine = m_pImgCutLine;
	if ( m_pData != NULL )
	{
		pItem->SetUserData( m_pData );
	}
	return pItem;
}

/*---------------------------------------------------------------------
* ��	����CTextItem
* ��    �ܣ�������Ŀ
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/09/01	v1.0				      ����
----------------------------------------------------------------------*/
CTextItem::CTextItem( String strText, int nWidht, int nHeight, Color col, Color colSel, Font* pFont, StringAlignment align,
					 StringAlignment aLinelign, String strFunc, String strLayout, String strSort, 
		bool bCanDrag, bool bCanMove, CPoint ptOffset, EmItemStatus emItemStatus, bool bAlwaysShow ) : 
IBaseItem( nWidht, nHeight, strFunc, strLayout, strSort, bCanDrag, bCanMove, ptOffset, emItemStatus, bAlwaysShow ), 
m_strText( strText ), m_pFont( pFont ), m_coText( col ), m_coSel( colSel ), m_Alignment( align ), m_LineAlignment(aLinelign)
{

}

void CTextItem::SetFont( Font* pFont )
{
    m_pFont = pFont;

    //�õ�������
    FontFamily fFamily;
    m_pFont->GetFamily( &fFamily );

    WCHAR name[LF_FACESIZE];
    fFamily.GetFamilyName( name );

    char buffer[64] = {0};
    WideCharToMultiByte( CP_ACP, 0, name, 64, buffer, 64, NULL, NULL );
    m_strFontName = buffer;
    
}

void CTextItem::Draw( IArgs* pArgs )
{
	if ( Args_Graphics* p = dynamic_cast<Args_Graphics*>( pArgs ) )
	{
		Graphics* pGraphics = p->m_pGraphics;

		pGraphics->SetSmoothingMode( SmoothingModeHighQuality );
        if ( m_strFontName != _T("����") )
        {
		    pGraphics->SetTextRenderingHint(TextRenderingHint(TextRenderingHintAntiAlias));
        }
		CString strTemp = m_strText.c_str();
		SolidBrush brush( m_coText );
		if ( m_emItemStatus == emItemStatusSel || m_emItemStatus == emItemStatusDown )
		{
			brush.SetColor( m_coSel );
		}
		StringFormat strFormat;
		strFormat.SetAlignment( m_Alignment );
		// Center the block of text (top to bottom) in the rectangle.
		strFormat.SetLineAlignment(StringAlignmentCenter);
		strFormat.SetFormatFlags( StringFormatFlagsNoFitBlackBox /*| StringFormatFlagsLineLimit*/ );
		strFormat.SetTrimming( StringTrimmingEllipsisCharacter );
		//CheckTextLength( strTemp, m_rcItem, pGraphics );
		RectF rc = RectF( m_rcItem.left, m_rcItem.top, m_rcItem.Width(), m_rcItem.Height() );

		BSTR bstr = strTemp.AllocSysString();
		pGraphics->DrawString( bstr, -1, m_pFont, rc, &strFormat, &brush );
		SysFreeString( bstr );
	}
}

IBaseItem* CTextItem::Clone()
{
	CTextItem* pItem = new CTextItem( m_strText, m_rcItem.Width(), m_rcItem.Height(), m_coText, m_coSel, m_pFont, m_Alignment, m_LineAlignment,
		m_strFunc, m_strLayoutAlgorithm, m_strSortAlgorithm, m_bCanDrag, m_bCanMove, m_ptOffset, m_emItemStatus, m_bAlwaysShow );
    pItem->m_strFontName = m_strFontName;
	if ( m_pData != NULL )
	{
		pItem->SetUserData( m_pData );
	}
	return pItem;
}


void CTextItem::AutoAdjustRect( HWND hWnd )
{
    Graphics graphics(hWnd);

    RectF rectString;
    
    StringFormat strFormat;
    strFormat.SetAlignment( m_Alignment );
    strFormat.SetLineAlignment(StringAlignmentCenter);

    CString strText = m_strText.c_str();
    
    WCHAR *pwszText = NULL;
    pwszText = new WCHAR[strText.GetLength() + 1];
    int nLen = MultiByteToWideChar( CP_ACP, 0, strText, -1, NULL, NULL ); 
    MultiByteToWideChar( CP_ACP, 0, strText, -1, pwszText, nLen );
    unsigned int dwTextLen = wcslen(pwszText);
    
	graphics.MeasureString( pwszText, -1, m_pFont, RectF(0,0,0,0), &strFormat, &rectString );

    CRect rc = m_rcItem;
    rc.right = rc.left + rectString.Width + 2;
    SetItemRect( rc );

    if ( NULL != pwszText )
    {
        delete []pwszText;
        pwszText = NULL;
	}
}


/*---------------------------------------------------------------------
* ��	����CExTextItem
* ��    �ܣ�����������Ŀ
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/09/01	v1.0				      ����
----------------------------------------------------------------------*/
CExTextItem::CExTextItem( String strText, int nWidht, int nHeight, Color col, Color colSel, Font* pFont, StringAlignment align,StringAlignment aLinelign,
						 String strFunc, String strLayout, String strSort, 
						 bool bCanDrag, bool bCanMove, CPoint ptOffset, EmItemStatus emItemStatus, bool bAlwaysShow ) : 
CTextItem( strText, nWidht, nHeight, col, colSel, pFont, align, aLinelign, strFunc, strLayout, strSort, bCanDrag, bCanMove, ptOffset, emItemStatus, bAlwaysShow )
{
	
}

void CExTextItem::Draw( IArgs* pArgs )
{
	if ( Args_Graphics* p = dynamic_cast<Args_Graphics*>( pArgs ) )
	{
		Graphics* pGraphics = p->m_pGraphics;
		
		pGraphics->SetSmoothingMode( SmoothingModeHighQuality );
        if ( m_strFontName != _T("����") )
        {
		    pGraphics->SetTextRenderingHint(TextRenderingHint(TextRenderingHintAntiAlias));
        }
		CString strTemp = m_strText.c_str();
		SolidBrush brush( m_coText );
		StringFormat strFormat;
		strFormat.SetAlignment( m_Alignment );
		// Center the block of text (top to bottom) in the rectangle.
		strFormat.SetLineAlignment(m_LineAlignment); 
		strFormat.SetFormatFlags( StringFormatFlagsNoFitBlackBox | StringFormatFlagsLineLimit );
		strFormat.SetTrimming( StringTrimmingEllipsisCharacter ); //���ı���������ӽ����ַ������ڱ��������е�ĩβ����һ��ʡ�Ժ�

		if ( m_emItemStatus == emItemStatusSel || m_emItemStatus == emItemStatusDown )
		{
			brush.SetColor( m_coSel );
		}
		
		int nTextCounts = 0;
		nTextCounts += m_vecOtherText.size();
		int nTextHeight = m_rcItem.Height() * 41/70;
		
		RectF rc = RectF( m_rcItem.left, m_rcItem.top, m_rcItem.Width(), nTextHeight );
		//�������޼�...
		//CRect rect;
		//rect.SetRect( m_rcItem.left, m_rcItem.top, m_rcItem.left + m_rcItem.Width(), m_rcItem.top + nTextHeight );
		//CheckTextLength( strTemp, rect, pGraphics );
		
		BSTR bstr = strTemp.AllocSysString();
		pGraphics->DrawString( bstr, -1, m_pFont, rc, &strFormat, &brush );
		SysFreeString( bstr );
	
        if ( nTextCounts == 0 )
        {
            return;
        }
		int nOtherTextHeight = ( m_rcItem.Height() - nTextHeight ) / nTextCounts;
		int nOtherTop = m_rcItem.top + nTextHeight;
		TextInfoVec::iterator itr = m_vecOtherText.begin();
		int nIndex = 0;
		while ( itr != m_vecOtherText.end() )
		{
			CTextInfo textInfo = *itr;
			
			CString strTemp = textInfo.m_strText.c_str();
			SolidBrush brush( textInfo.m_coText );
			StringFormat strFormat;
			strFormat.SetAlignment( textInfo.m_Alignment );
			// Center the block of text (top to bottom) in the rectangle.
			strFormat.SetLineAlignment(StringAlignmentNear);
			strFormat.SetTrimming( StringTrimmingEllipsisCharacter );

			if ( m_emItemStatus == emItemStatusSel || m_emItemStatus == emItemStatusDown )
			{
				brush.SetColor( m_coSel );
			}
			
			int nTop = nOtherTop + (nOtherTextHeight* nIndex++);
			//rect.SetRect( m_rcItem.left, nTop, m_rcItem.left + m_rcItem.Width(), nTop + nOtherTextHeight );
			//CheckExTextLength( strTemp, rect, strFormat, pGraphics );

			RectF rc = RectF( m_rcItem.left, nTop, m_rcItem.Width(), nOtherTextHeight );
			
			BSTR bstr = strTemp.AllocSysString();			
			pGraphics->DrawString( bstr, -1, textInfo.m_pFont, rc, &strFormat, &brush );
			SysFreeString(bstr);
			
			itr++;
		}
	}
}

IBaseItem* CExTextItem::Clone()
{
	CExTextItem* pItem = new CExTextItem( m_strText, m_rcItem.Width(), m_rcItem.Height(), m_coText, m_coSel, m_pFont, m_Alignment, m_LineAlignment,
		m_strFunc, m_strLayoutAlgorithm, m_strSortAlgorithm, m_bCanDrag, m_bCanMove, m_ptOffset, m_emItemStatus, m_bAlwaysShow );
	pItem->m_vecOtherText = m_vecOtherText;
    pItem->m_strFontName = m_strFontName;
	if ( m_pData != NULL )
	{
		pItem->SetUserData( m_pData );
	}
	return pItem;
}

void CExTextItem::AddText( String strText, Font* pFont /* = 0 */, Color col /* = Color::Black */, StringAlignment align )
{
	if ( pFont == 0 )
	{
		pFont = m_pFont;
	} 
	CTextInfo cTextInfo( strText, pFont, col, align );
	m_vecOtherText.push_back( cTextInfo );
}

void CExTextItem::SetSecondText( String strText )
{
	if ( m_vecOtherText.size() == 0 )
	{
		return;
	}
	
	m_vecOtherText[0].m_strText = strText;
}
 

const String CCheckItem::strCutLine = "cutline.png";

CCheckItem::CCheckItem( String strImageFolder, int nWidht, int nHeight, BOOL bSel, String strFunc, 
					 String strLayout, String strSort, 
					 bool bCanDrag, bool bCanMove, CPoint ptOffset, EmItemStatus emItemStatus, bool bAlwaysShow ) :
	IBaseItem( nWidht, nHeight, strFunc, strLayout, strSort, bCanDrag, bCanMove, ptOffset, emItemStatus, bAlwaysShow )
{
    m_pImgCutLine = NULL;
	SetImageFolder( strImageFolder );

	m_bSel = bSel;
}


void CCheckItem::Draw( IArgs* pArgs )
{
	if ( Args_Graphics* p = dynamic_cast<Args_Graphics*>( pArgs ) )
	{
		Graphics* pGraphics = p->m_pGraphics;
		Image* pDrawImage = m_pImgNormal;
		switch ( m_emItemStatus )
		{
		case emItemStatusSel:
			{
				if ( m_bSel )
				{
					pDrawImage = m_pImgSel;
				}
				else
				{
					pDrawImage = m_pImgNormal;
				}
			}
			break;
		case emItemStatusDown:
			{
				if ( m_pImgDown != 0 )
				{
					pDrawImage = m_pImgDown;
				}
			}
			break;
		case emItemStatusDisable:
			{
				if ( m_pImgDisable != 0 )
				{
					pDrawImage = m_pImgDisable;
				}
			}
			break;
		default:
			{					
				pDrawImage = m_pImgNormal;					
			}
			break;
		}	
		pGraphics->DrawImage( pDrawImage, m_rcItem.left, m_rcItem.top, m_rcItem.Width(), m_rcItem.Height() );		

		//�ұ߻��ָ���
		if ( m_pImgCutLine != NULL )
		{
			pGraphics->DrawImage( m_pImgCutLine, m_rcItem.right - m_pImgCutLine->GetWidth(), m_rcItem.top, m_pImgCutLine->GetWidth(), m_pImgCutLine->GetHeight()/*m_rcItem.Height()*/ );
		}
	}
}

void CCheckItem::Click()
{
	m_bSel = !m_bSel;
}

void CCheckItem::SetItemStatus( EmItemStatus emStatus )
{
	m_emItemStatus = emStatus; 
	if ( emStatus == emItemStatusNormal )
	{
		m_bSel = FALSE;
	}
}

IBaseItem* CCheckItem::Clone()
{
	CCheckItem* pItem = new CCheckItem( "", m_rcItem.Width(), m_rcItem.Height(), m_bSel, 
		m_strFunc, m_strLayoutAlgorithm, m_strSortAlgorithm, m_bCanDrag, m_bCanMove, m_ptOffset, m_emItemStatus, m_bAlwaysShow );
	pItem->m_pImgNormal = m_pImgNormal;
	pItem->m_pImgDown = m_pImgDown;
	pItem->m_pImgSel = m_pImgSel;
	pItem->m_pImgDisable = m_pImgDisable;
	pItem->m_pImgCutLine = m_pImgCutLine;
	if ( m_pData != NULL )
	{
		pItem->SetUserData( m_pData );
	}
	return pItem;
}

void CCheckItem::SetImageFolder( String strFolder )
{
    String strFile = strFolder + "//" + strNormalImg;
    m_pImgNormal = CSrcManage::GetImage( strFile.c_str() );
    strFile = strFolder + "//" + strDownImg;
    m_pImgDown = CSrcManage::GetImage( strFile.c_str() );
    strFile = strFolder + "//" + strSelImg;
    m_pImgSel = CSrcManage::GetImage( strFile.c_str() );
    strFile = strFolder + "//" + strDisableImg;
	m_pImgDisable = CSrcManage::GetImage( strFile.c_str() );

    strFile = strFolder + "//" + CCheckItem::strCutLine;
    m_pImgCutLine= CSrcManage::GetImage( strFile.c_str() );
} 


const String CButtonItem::strCutLine = "cutline.png";
//2012.12.20 yjj �����cutline��Ҫ��iteminfo�����ô�Сʱ�ѷָ��ߵĴ�СҲ�������ڣ�����ָ���λ�ûᱻitem����
const String CButtonItem::strLftCutline = "CutlineLeft.png";
const String CButtonItem::strRgtCutline = "CutlineRight.png";
const String CButtonItem::strDwnCutline = "CutlineDown.png";
const String CButtonItem::strUpCutline = "CutlineUp.png";

CButtonItem::CButtonItem( String strImageFolder, int nWidht, int nHeight, String strFunc, 
					 String strLayout, String strSort, 
					 bool bCanDrag, bool bCanMove, CPoint ptOffset, EmItemStatus emItemStatus, bool bAlwaysShow ) :
	IBaseItem( nWidht, nHeight, strFunc, strLayout, strSort, bCanDrag, bCanMove, ptOffset, emItemStatus, bAlwaysShow )
{
	m_pUpCutlineImg = NULL;
	m_pDwnCutlineImg = NULL;
	m_pRgtCutlineImg = NULL;
	m_pLftCutlineImg = NULL;
	SetImageFolder( strImageFolder );
}


void CButtonItem::Draw( IArgs* pArgs )
{
	if ( Args_Graphics* p = dynamic_cast<Args_Graphics*>( pArgs ) )
	{
		Graphics* pGraphics = p->m_pGraphics;
		Image* pDrawImage = m_pImgNormal;
		switch ( m_emItemStatus )
		{
		case emItemStatusSel:
			{
				if ( m_pImgSel != 0 )
				{
					pDrawImage = m_pImgSel;
				}
			}
			break;
		case emItemStatusDown:
			{
				if ( m_pImgDown != 0 )
				{
					pDrawImage = m_pImgDown;
				}
			}
			break;
		case emItemStatusDisable:
			{
				if ( m_pImgDisable != 0 )
				{
					pDrawImage = m_pImgDisable;
				}
			}
			break;
		case emItemStatusOver:
			{
				if ( m_pImgOver != 0 )
				{
					pDrawImage = m_pImgOver;
				}
			}
			break;
		default:
			{					
				pDrawImage = m_pImgNormal;					
			}
			break;
		}
		
		CPoint ptStart(m_rcItem.left, m_rcItem.top);//��ʼ��ͼ��λ�� 

		//�ϱ߻��ָ��� 2012.12.20 yjj
		if (  NULL != m_pUpCutlineImg )
		{
			pGraphics->DrawImage( m_pImgCutLine, ptStart.x,  ptStart.y, m_pUpCutlineImg->GetWidth(), m_pUpCutlineImg->GetHeight() );
			ptStart.y += m_pUpCutlineImg->GetHeight();
		}

		//��߻��ָ���  2012.12.20 yjj
		if (  NULL != m_pLftCutlineImg )
		{
			pGraphics->DrawImage( m_pLftCutlineImg, ptStart.x,  ptStart.y, m_pLftCutlineImg->GetWidth(), m_pLftCutlineImg->GetHeight() );
			ptStart.x += m_pLftCutlineImg->GetWidth();
		}

        if ( NULL != pDrawImage )
        {
			pGraphics->DrawImage( pDrawImage, ptStart.x,  ptStart.y, /*m_rcItem.Width(), m_rcItem.Height()*/ pDrawImage->GetWidth(), pDrawImage->GetHeight() );	
		 
        }
			

		//�ұ߻��ָ���  //Ϊ����b2�汾֮ǰ�İ汾������    2012.12.20 yjj
		if ( m_pImgCutLine != NULL )
		{
			pGraphics->DrawImage( m_pImgCutLine, m_rcItem.right - m_pImgCutLine->GetWidth(), m_rcItem.top, m_pImgCutLine->GetWidth(), m_pImgCutLine->GetHeight() /*m_rcItem.Height()*/ );
		}

		//�±߻��ָ��� 2012.12.20 yjj
		if (  NULL != m_pDwnCutlineImg )
		{   
			if ( pDrawImage )
			{
				ptStart.y += pDrawImage->GetHeight();
			} 
			pGraphics->DrawImage( m_pImgCutLine, ptStart.x,  ptStart.y, m_pUpCutlineImg->GetWidth(), m_pUpCutlineImg->GetHeight() );
		 
		}
		
		//�ұ߻��ָ���  2012.12.20 yjj
		if (  NULL != m_pRgtCutlineImg )
		{
			if ( pDrawImage )
			{
				ptStart.x += pDrawImage->GetWidth();
			} 
			pGraphics->DrawImage( m_pRgtCutlineImg, ptStart.x,  ptStart.y, m_pRgtCutlineImg->GetWidth(), m_pRgtCutlineImg->GetHeight() ); 
		}

	
	}
}

IBaseItem* CButtonItem::Clone()
{
	CButtonItem* pItem = new CButtonItem( "", m_rcItem.Width(), m_rcItem.Height(), 
		m_strFunc, m_strLayoutAlgorithm, m_strSortAlgorithm, m_bCanDrag, m_bCanMove, m_ptOffset, m_emItemStatus, m_bAlwaysShow );
	pItem->m_pImgNormal = m_pImgNormal;
	pItem->m_pImgSel = m_pImgSel;
	pItem->m_pImgDown = m_pImgDown;
	pItem->m_pImgDisable = m_pImgDisable;
	pItem->m_pImgOver = m_pImgOver;
	pItem->m_pImgCutLine = m_pImgCutLine;
	pItem->m_pUpCutlineImg = m_pUpCutlineImg;
	pItem->m_pDwnCutlineImg = m_pDwnCutlineImg;
	pItem->m_pRgtCutlineImg = m_pRgtCutlineImg;
	pItem->m_pLftCutlineImg = m_pLftCutlineImg;
	if ( m_pData != NULL )
	{
		pItem->SetUserData( m_pData );
	}
	return pItem;
}

void CButtonItem::SetImageFolder( String strFolder )
{
    String strFile = strFolder + "//" + strNormalImg;
    m_pImgNormal = CSrcManage::GetImage( strFile.c_str() );
    strFile = strFolder + "//" + strDownImg;
    m_pImgDown = CSrcManage::GetImage( strFile.c_str() );
    strFile = strFolder + "//" + strSelImg;
    m_pImgSel = CSrcManage::GetImage( strFile.c_str() );
    strFile = strFolder + "//" + strDisableImg;
    m_pImgDisable = CSrcManage::GetImage( strFile.c_str() );
    strFile = strFolder + "//" + strOverImg;
    m_pImgOver = CSrcManage::GetImage( strFile.c_str() );

	strFile = strFolder + "//" + CButtonItem::strCutLine;
	m_pImgCutLine= CSrcManage::GetImage( strFile.c_str() );

	strFile = strFolder + "//" + CButtonItem::strUpCutline;
	m_pUpCutlineImg= CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CButtonItem::strDwnCutline;
	m_pDwnCutlineImg= CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CButtonItem::strRgtCutline;
	m_pRgtCutlineImg= CSrcManage::GetImage( strFile.c_str() );
	strFile = strFolder + "//" + CButtonItem::strLftCutline;
	m_pLftCutlineImg= CSrcManage::GetImage( strFile.c_str() );
}


/*---------------------------------------------------------------------
* ��	����CMidImageItem
* ��    �ܣ�������ʾͼƬ����Ŀ
* ����˵��������Tpad������
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2012/04/01	v1.0		Ф��Ȼ		����
----------------------------------------------------------------------*/
CMidImageItem::CMidImageItem( String strImageFolder , int nWidht, int nHeight, String strFunc,
							 String strLayout, String strSort, 
					   bool bCanDrag, bool bCanMove, CPoint ptOffset, EmItemStatus emItemStatus, bool bAlwaysShow ) : 
IBaseItem( nWidht, nHeight, strFunc, strLayout, strSort, bCanDrag, bCanMove, ptOffset, emItemStatus, bAlwaysShow )
{
	SetImageFolder( strImageFolder );
}


void CMidImageItem::Draw( IArgs* pArgs )
{
	if ( Args_Graphics* p = dynamic_cast<Args_Graphics*>( pArgs ) )
	{
		Graphics* pGraphics = p->m_pGraphics;
		Image* pDrawImage = m_pImgNormal ;
		switch ( m_emItemStatus )
		{
		case emItemStatusSel:
			{
				if ( m_pImgSel  != 0 )
				{
					pDrawImage = m_pImgSel;
				}
			}
			break;
		case emItemStatusDown:
			{
				if ( m_pImgSel != 0 )
				{
					pDrawImage = m_pImgSel;
				}
			}
			break;
		case emItemStatusDisable:
			{
				if ( m_pImgDisable != 0 )
				{
					pDrawImage = m_pImgDisable;
				}
			}
			break;
		default:
			{
				pDrawImage = m_pImgNormal ;
			}
			break;
		}	
		if ( pDrawImage != NULL && pDrawImage->GetWidth() != 0 )
		{	
			int nWidth = pDrawImage->GetWidth();
			//ͼƬ����Ӧ�ֱ���
			//nWidth = m_rcItem.Width() - 6;
			int nHeight = pDrawImage->GetHeight(); // *nWidth / pDrawImage->GetWidth();
			int nOffset = 0;
			if ( m_rcItem.Width() > nWidth )
			{
				nOffset = ( m_rcItem.Width() - nWidth ) / 2;
			}
			pGraphics->DrawImage( pDrawImage, m_rcItem.left + nOffset, m_rcItem.top/* + nOffset*/, nWidth, nHeight );	
		}
	}
}

IBaseItem* CMidImageItem::Clone()
{
	CMidImageItem* pItem = new CMidImageItem( "", m_rcItem.Width(), m_rcItem.Height(), 
		m_strFunc, m_strLayoutAlgorithm, m_strSortAlgorithm, m_bCanDrag, m_bCanMove, m_ptOffset, m_emItemStatus, m_bAlwaysShow );
	pItem->m_pImgDown  = m_pImgDown ;
	pItem->m_pImgNormal  = m_pImgNormal ;
	pItem->m_pImgDisable = m_pImgDisable;
	pItem->m_pImgSel = m_pImgSel;
	if ( m_pData != NULL )
	{
		pItem->SetUserData( m_pData );
	}
	return pItem;
}

void CMidImageItem::SetImageFolder( String strFolder )
{
    String strFile = strFolder + "//" + strNormalImg;
    m_pImgNormal = CSrcManage::GetImage( strFile.c_str() );
    strFile = strFolder + "//" + strDownImg;
    m_pImgDown = CSrcManage::GetImage( strFile.c_str() );
    strFile = strFolder + "//" + strSelImg;
    m_pImgSel = CSrcManage::GetImage( strFile.c_str() );
    strFile = strFolder + "//" + strDisableImg;
    m_pImgDisable = CSrcManage::GetImage( strFile.c_str() );
}
 