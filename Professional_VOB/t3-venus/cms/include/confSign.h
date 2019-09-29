// confSign.h: interface for the CConfSign class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFSIGN_H__05E97249_DDA9_4030_984B_1A9D5F70E848__INCLUDED_)
#define AFX_CONFSIGN_H__05E97249_DDA9_4030_984B_1A9D5F70E848__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CConfSign : public ISingleTon<CConfSign>
{
public:
	CConfSign();
	virtual ~CConfSign();

	/**	 
	* ����: ������ʾ���ֵ�ͼƬ
	* @param    const LPCTSTR strCharacters     [in]     ��������
	* @param    const LPCTSTR strFontFamily     [in]     �����ʽ(���塢΢���źڵ�) 
	* @param    const FontStyle emFontStyle     [in]     ����ṹ(�Ӵ֡��»��ߵ�) 
	* @param    const Color clText				[in]     ������ɫ 
	* @param    const Color clBorder			[in]     ����߽���ɫ 
	* @param    const Color clBkGrd				[in]     ͼƬ������ɫ 
	* @param    const int nFontSizeByPx			[in]     ����Px 
	* @param    const int borderWidthByPx		[in]     ����߽�Px 
	* @param    const LPCTSTR strFileName		[in]     ͼƬ�洢·�� 
	* @return   bool
	* @remarks  
	*/
	BOOL MakeImgByChar( const LPCTSTR strCharacters, const LPCTSTR strFontFamily,const FontStyle emFontStyle, const Color clText, const Color clBorder, 
		const Color clBkGrd, const int nFontSizeByPx,const int borderWidthByPx, const LPCTSTR strFileName);
	
	/**	 
	* ����: ��ȡ��ʾ���ֵĴ�С
	* @param    const WCHAR * strCharacters     [in]     ��������
	* @param    Font*pFont				        [in]     ����������Ϣ
	* @param    CSize& cSize					[out]    ���ֵĴ�С
	* @return   
	* @remarks  
	*/
	void GetCharExtent(IN const WCHAR * strCharacters, Font*pFont, CSize& cSize);

	/**	 
	* ����: �ϴ�����
	* @param    const String strRemotePath      [in]     linux�˴��洢·��
	* @param    const String strLocalFile       [in]     ��������ļ�ȫ·�� 
	* @param    const String strCheckFileName   [in]     ��������ļ��� 
	* @return   bool
	* @remarks  
	*/
	BOOL UploadCore( const String& strRemotePath, const String& strLocalFile, const String& strCheckFileName ); 

private:
	CFtpCtrl m_cFtp;
};

#define	ConfSign     CConfSign::GetSingletonPtr()

#endif // !defined(AFX_CONFSIGN_H__05E97249_DDA9_4030_984B_1A9D5F70E848__INCLUDED_)
