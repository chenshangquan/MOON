// SystemInfoManage.h: interface for the CSystemInfoManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SYSTEMINFOMANAGE_H__8E14DCCF_C21D_42AE_9164_99599EF344B0__INCLUDED_)
#define AFX_SYSTEMINFOMANAGE_H__8E14DCCF_C21D_42AE_9164_99599EF344B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
namespace AutoUIFactory
{

class CSystemInfoManage : public IObserver, public Singleton<CSystemInfoManage>
{
public:
	static const String strSystemInfo;
	static const String strVersion;
	static const String strName;
	static const String strValue;
	static const String strImagePath;
	static const String strLayoutPath;
	static const String strItemInfo;
    static const String strResolution;//�ֱ���
    static const String strBeSelAdpResolution;
    static const String strEditInfo;
    static const String strStaticInfo;
public:
	CSystemInfoManage();
	virtual ~CSystemInfoManage();
public:
	/**  ����ϵͳͼƬ��Դ·��
	 *  @param[in] strPath ·��
	 *  @return 
	 */
	void SetImagePath( String strPath );

	String GetImagePath() { return m_strImagePath; }

	/**  ����ϵͳ�����ļ�·��
	 *  @param[in] strPath ·��
	 *  @return 
	 */
    void SetLayoutPath( String strPath );

	String GetLayoutPath() { return m_strLayoutPath; }

	/**  ����ItemInfo�ļ�·��
	 *  @param[in] strPath ·��
	 *  @return 
	 */
    void SetItemInfoPath( String strPath );

	String GetItemInfoPath() { return m_strItemInfo; }

	void Update( IArgs* pArgs );
   
   //��ĳ���ļ������·������Ϊ����·��
    void MakeFullPath( String& strFileSubPath );
     
    void SetResolution( String strValue );
    void GetResolution( int &cx, int &cy ) ;
    String GetResolution(){ return m_strResolution;}
  
    //�Ƿ�����Ӧ�ֱ���
    void SetBeSelAdpResolution( String strValue );
    BOOL IsSelAdpResolution() ;

    //Edit������Ϣ
    void SetFontInfo( TFontInfo &tFontInfo, XMLAttributes& xmlAttribs );
    TFontInfo GetEditFontInfo(){ return m_tEditFontInfo; }

    //Static������Ϣ   
    TFontInfo GetStaticFontInfo(){ return m_tStaticFontInfo; }

	string GetVersion(){ return m_strVersion; }

    void  SetVersion( string strVer );
protected:

	void UpdateSystemInfo( XMLAttributes& xmlAttribs );
	/*
	 * �����ļ�·��
	 *  
	 */
	String m_strMainXml;

	/*
	 *  ͼƬ��Դ·��
	 */
	String m_strImagePath;

	/*
	 *  �����ļ�·��
	 */
	String m_strLayoutPath;

	
    /*
	 * ��Ŀ��Ϣ��·��\n 
	 */
	String m_strItemInfo;
    
    /*
	 * �ֱ��� \n 
	 */
    String m_strResolution;

    /*
	 * �Ƿ�����Ӧ�ֱ��� \n 
	 */
    BOOL m_bBeSelAdpResolution;

	/*
	 * �汾�� \n 
	 */
	String m_strVersion;

    /*
	 * EditĬ��������Ϣ \n 
	 */
    TFontInfo m_tEditFontInfo;

    /*
	 * StaticĬ��������Ϣ \n 
	 */
    TFontInfo m_tStaticFontInfo;
};

};
#endif // !defined(AFX_SYSTEMINFOMANAGE_H__8E14DCCF_C21D_42AE_9164_99599EF344B0__INCLUDED_)
