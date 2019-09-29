// BitmapHelp.h: interface for the CBitmapHelp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BITMAPHELP_H__D76D0E48_A149_44F2_ACD8_D2740BB13B2F__INCLUDED_)
#define AFX_BITMAPHELP_H__D76D0E48_A149_44F2_ACD8_D2740BB13B2F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBitmapHelp  
{
	typedef IItem< IBaseItem, int > IItemList;
public:
	CBitmapHelp();
	virtual ~CBitmapHelp();

	static Bitmap* CreateBitmap( IItemList* pItemList );
	static Bitmap* CreateBitmap( IBaseItem* pBaseItem );

	static BOOL GetBitmap( Bitmap* pBitmap, IItemList* pItemList );

protected:
	static void DrawItem( IItemList* pItemList, IArgs* pArgs );

private:
	static Bitmap* m_pBitmap;
};

#endif // !defined(AFX_BITMAPHELP_H__D76D0E48_A149_44F2_ACD8_D2740BB13B2F__INCLUDED_)
