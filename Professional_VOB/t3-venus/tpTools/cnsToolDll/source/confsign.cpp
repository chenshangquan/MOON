// confsign.cpp: implementation of the CConfSign class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "confsign.h"
#include "msgBoxLogic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CConfSign::CConfSign()
{

}

CConfSign::~CConfSign()
{

}

BOOL CConfSign::MakeImgByChar( const LPCTSTR strCharacters, const LPCTSTR strFontFamily,const FontStyle emFontStyle, const Color clText, const Color clBorder, 
								  const Color clBkGrd, const int nFontSizeByPx,const int borderWidthByPx, const LPCTSTR strFileName)
{
	HDC hDc = ::GetDC( NULL );
    HDC hDcMem =  CreateCompatibleDC( hDc); 
		
	Font *pFont = CSrcManage::GetFont( strFontFamily, nFontSizeByPx*72/96, emFontStyle ); 
	
	CString txt(strCharacters);
	BSTR bstrText = txt.AllocSysString();
	
	// ���㵱ǰ���ֵĳ��ȣ���ȷ��ͼƬ�ĳ��Ϳ�
	CSize cSize(0,0);
    GetCharExtent( bstrText,pFont,cSize);
    cSize.cx += borderWidthByPx;
	cSize.cy += borderWidthByPx;
	while ( cSize.cx % 4 != 0 )
	{
	   cSize.cx++;
	}
	while ( cSize.cy % 4 != 0 )
	{
		cSize.cy++;
	}

	BITMAPINFOHEADER stBmpInfoHeader = { 0 };   
    int nBytesPerLine = ((cSize.cx * 32 + 31) & (~31)) >> 3;
    stBmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);   
    stBmpInfoHeader.biWidth = cSize.cx;   
    stBmpInfoHeader.biHeight = cSize.cy;   
    stBmpInfoHeader.biPlanes = 1;
    stBmpInfoHeader.biBitCount = 32;   
    stBmpInfoHeader.biCompression = BI_RGB;   
    stBmpInfoHeader.biClrUsed = 0;   
    stBmpInfoHeader.biSizeImage = nBytesPerLine * cSize.cy;	
	
    PUINT32 pvBits = NULL;   
    HBITMAP hBtMap = ::CreateDIBSection(NULL, (PBITMAPINFO)&stBmpInfoHeader, DIB_RGB_COLORS, (LPVOID*)&pvBits, NULL, 0);
    if (hBtMap)   
    {   
		::SelectObject(  hDcMem, hBtMap); 
	}
	
	
	Graphics graph(hDcMem); 
	graph.Clear( clBkGrd ); 

	if ( strFontFamily != "����")
	{
		graph.SetSmoothingMode(SmoothingModeAntiAlias);     
		graph.SetInterpolationMode(InterpolationModeHighQualityBicubic); 
	}

	StringFormat  cStringFormat ;
	cStringFormat.SetAlignment( StringAlignmentNear );
	cStringFormat.SetLineAlignment(StringAlignmentCenter);
	cStringFormat.SetFormatFlags( StringFormatFlagsNoWrap | StringFormatFlagsMeasureTrailingSpaces );
	 
	GraphicsPath txtPath(FillModeWinding);
	FontFamily fm;
	pFont->GetFamily(&fm); 
	
	txtPath.AddString(bstrText, -1 ,&fm, FontStyleBold , nFontSizeByPx/*  + borderWidthByPx*/ , RectF(0, 0, cSize.cx, cSize.cy ), &cStringFormat); 
	  
    SolidBrush brush( clText );  
	Pen borderPen( clBorder, borderWidthByPx *2 ); 
	borderPen.SetLineJoin(LineJoinRound);
 
 
    graph.DrawPath(&borderPen,&txtPath);
    graph.FillPath(&brush,&txtPath); 

	SysFreeString( bstrText ); 
	BOOL bSuccess = SaveBmp(hBtMap,strFileName);
	DeleteObject(hBtMap);
	DeleteObject(hDcMem);
	::ReleaseDC(NULL, hDc );
	return bSuccess;
}

void CConfSign::GetCharExtent(IN const WCHAR * strCharacters, Font*pFont, CSize& cSize)
{
    HDC hDc = ::GetDC( NULL ); 
	Graphics graph(hDc);
	RectF rcf;
	graph.MeasureString(strCharacters,-1,pFont,PointF(0,0),&rcf); 
	
	cSize.cx = rcf.Width;
	cSize.cy =  rcf.Height;

	if ( rcf.Width > cSize.cx )
	{
		cSize.cx += 1;
	}

	if ( rcf.Height > cSize.cy )
	{
		cSize.cy += 1;
	}

 	::ReleaseDC(NULL, hDc ); 

	// 	GraphicsPath path;     
	//	FontFamily fontfamily;   
	// 	StringFormat strFormat;           
	// 	strFormat.SetAlignment(StringAlignmentNear); 
	// 	pFont->GetFamily(&fontfamily);    
	// 	path.AddString(strCharacters,-1,&fontfamily,pFont->GetStyle(),pFont->GetSize(),PointF(0,0),&strFormat);     
	// 	RectF rcBound;     
	// 	path.GetBounds(&rcBound);     
	// 	cSize.cx = rcBound.Width;
	// 	cSize.cy =  rcBound.Height;		
}

BOOL CConfSign::UploadCore( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName )
{
	CString strIpAddr;

	u32 dwIp;
	LIBDATAMGRPTR->GetLoginIp(dwIp);		
	struct in_addr addrIPAddr;
	addrIPAddr.S_un.S_addr = htonl(dwIp);
	strIpAddr = inet_ntoa(addrIPAddr);

	BOOL32 bRet = m_cFtp.SetServerParam( strIpAddr, "admin", "admin" );
	if ( !bRet )
	{	
		MSG_BOX_OK("����FTP�ϴ�������ʧ��!");	
		return FALSE;
	}

	String strRemoteFilePath = strRemotePath;
	strRemoteFilePath += strCheckFileName;

	if ( !m_cFtp.BeginUpload( NULL, strRemoteFilePath.c_str(), strLocalFile.c_str(), FTP_TRANSFER_TYPE_BINARY, FTP_AGENT ) )
	{
		MSG_BOX_OK("�ϴ��ļ�ʧ�ܣ���������!");		
		return FALSE;		
	}
	return TRUE;
}