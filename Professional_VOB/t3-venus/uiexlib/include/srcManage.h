
#ifndef SRCMANAGE_HEAD_H
#define SRCMANAGE_HEAD_H
#include "uiexBaseData.h"

//�������ô��ڱ���ͼƬ����Ϸ�ʽ  2012.12.18 yjj
typedef enum EmImgCompType
{
	    emImgCompMasic,      //�����б���������8��ͼƬƴ�Ӷ���
		emImgCompSingle,     //����ͼƬ
		emImgCompLMR,		//��Ҫ ������ ��ʽƴ�ӵ�ͼƬ
		emImgCompTMB		//��Ҫ ������ ��ʽƴ�ӵ�ͼƬ
};

class CFontInfo
{
public:
	CFontInfo( CString strFontFamily, unsigned int wSize, FontStyle emStyle ) : 
      m_strFontFamily( strFontFamily ), m_wSize( wSize ), m_emFontStyle( emStyle ){}
	CString m_strFontFamily;
	unsigned int m_wSize;
    FontStyle m_emFontStyle;
	bool operator<( const CFontInfo& tag) const {
		if ( m_strFontFamily != tag.m_strFontFamily )
 		{
 			return true;
 		}
        if ( m_emFontStyle != tag.m_emFontStyle )
        {
            return true;
        }
		return m_wSize < tag.m_wSize;
	};
	
};
class CSrcManage 
{
    enum{STEPBK_VERT = 0, STEPBK_HORZ}; //����ɫ�ķ��� DrawStepBk��
public:
    /*====================================================================
    ������	��    CreateImage
    ����		������BMP��Դ�ŵõ�ͼƬ���
    �㷨ʵ��	������ѡ�
    ����ȫ�ֱ�������
    �������˵����nBitmap ͼƬ��Դ��
    ����ֵ˵����  ͼƬ��������ɹ�ΪNULL��
    ====================================================================*/
    static HBITMAP CreateImage(UINT nBitmap);

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
    ====================================================================*/
    static void DrawStepBk(CDC *pDC, COLORREF crFrom, COLORREF crTo, CRect rcAll, CRect rcItem=CRect(0,0,0,0), UINT nStyle=STEPBK_VERT);

	static BYTE* Get24BitPixels(HBITMAP pBitmap, WORD *pwWidth, WORD *pwHeight);
	static HRGN GenerateRegion(HBITMAP hBitmap, BYTE red, BYTE green, BYTE blue);

/**  ���һ��ͼƬ��Դ
 *  @param[in] strpath ·��
 *  @param[in] bNewCreate �Ƿ���Ҫ���¼��أ�������ȫ�ֹ��������ȡ
 *  @param[out] pImage ͼƬ��Դ
 *  @return �Ƿ�ɹ�
 */
	static Image* GetImage( CString strPath, BOOL bNewCreate = FALSE );

/**  ���ػ��ͼƬ��Դ
 *  @param[in] nID ��ԴID
 *  @param[in] lpszType ͼƬ��ʽ����"PNG"
 *  @param[in] hInstance Ӧ�ó�����Դ�����Ϊ�ձ�ʾ������
 *  @return pImage ͼƬ��Դ
 */
	static Image*  GetImage( UINT nID, LPCTSTR lpszType, HINSTANCE hInstance = NULL );
	static Image* LoadImage( UINT nID, LPCTSTR lpszType, HINSTANCE hInstance = NULL );


/**   ������������ͼ�� ƴ�� Ϊһ��ͼƬ
 *  @param[in] Rect  ����Ҫƴ�ӵ�ͼƬ��С
 *  @param[in] pImgLeft  
 *  @param[in] pImgRight  
 *  @param[in] pImgMiddle
 *  @return pImage ƴ�ӵ�ͼ��
 */
    static Image* MosaicHoriImage(  CRect& cRect, Image* pImgLeft, Image* pImgRight, Image* pImgMiddle );


    /**   �������� ����ͼ�� ƴ�� Ϊһ��ͼƬ
 *  @param[in] Rect  ����Ҫƴ�ӵ�ͼƬ��С
 *  @param[in] pImgTop  
 *  @param[in] pImgBottom  
 *  @param[in] pImgMiddle
 *  @return pImage ƴ�ӵ�ͼ��
 */ 
    static Image* MosaicVertImage(  CRect& cRect,  Image* pImgTop, Image* pImgBottom, Image* pImgMiddle );
	
/**  ��ȡ������Դ
 *  @param[in] strFontFamily ��������
 *  @param[in] wSize �����С
 *  @return ����ָ��
 */
	static Font* GetFont( CString strFontFamily, unsigned int wSize, FontStyle emFontStyle = FontStyleRegular, BOOL bNewCreate = FALSE );
	static void GetChsAndEngCnt( CString cstrText, unsigned short& wChsCnt, unsigned short& wEngCnt);

/**  ��ȡͼƬ��С
 *  @param[in] strImgFullPath ͼƬȫ·��
 *  @return ͼƬ��С
 */
	static CSize GetImageSize(CString strImgFullPath);

/**  �ڽ����˳�ʱ�ͷ�m_smapImageͼƬ��Դ
 *  @param[in] void
 *  @return void
 */
	static void ReleaseImage();

/**  �ڽ����˳�ʱ�ͷ�m_smapFonts������Դ
 *  @param[in] void
 *  @return void
 */
	static void ReleaseFont();
 /**  �ͷŸ�·����ͼƬ��Դ
 *  @param[in] void
 *  @return void
 */
	static void ReleaseSingleImage( CString strPath );
private:
/*
 *  ȫ�ֵ�һ������������ЩͼƬ����Ҫ���ض��\n 
 */
	typedef std::map<CString, Image*> ImageMap;
	static ImageMap m_mapImages;

	typedef std::map<UINT, Image*> CImageMap;
	static CImageMap m_smapImage;

	typedef CFontInfo FontKey; 
	typedef std::map<FontKey, Font*> FontMap;
	static FontMap m_smapFonts;
};

#endif