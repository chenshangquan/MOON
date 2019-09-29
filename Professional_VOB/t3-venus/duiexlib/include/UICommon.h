/*****************************************************************************
ģ����      : UICommon
�ļ���      : UICommon.h
����ļ�    : 
�ļ�ʵ�ֹ���: �������ͨ�ù��ߺ�����
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/6/06      1.0         ����ӡ      ����
******************************************************************************/
#ifndef __UICOMMON_H__
#define __UICOMMON_H__

namespace DuiLib {
//////////////////////////////////////////////////////////////////////////
//	����������
typedef std::map<tString, Image*> ImageMap;
class UILIB_API CUICommon
{
	CUICommon();
	virtual ~CUICommon();

public:

	static BOOL IsImgFile( LPCTSTR szFile );				//����ļ��Ƿ�ΪͼƬ
	static TImageInfo* GetImgInfo( LPCTSTR szImgFile );		//��ȡͼƬ��Ϣ���� �ߵȣ�

	static Image* GetImage( tString strPath, BOOL bNewCreate = FALSE );

private:
/*
 *  ȫ�ֵ�һ������������ЩͼƬ����Ҫ���ض��\n 
 */

	static ImageMap m_mapImages;


};




};

#endif