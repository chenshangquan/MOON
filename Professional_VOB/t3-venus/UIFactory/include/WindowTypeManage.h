// WindowTypeManage.h: interface for the CWindowTypeManage class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WINDOWTYPEMANAGE_H__63893F50_A110_4278_9C0C_0DEC1D3E5C9F__INCLUDED_)
#define AFX_WINDOWTYPEMANAGE_H__63893F50_A110_4278_9C0C_0DEC1D3E5C9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*---------------------------------------------------------------------
* ��	������Ҫ���ڴ������ͱ����Ĺ���
* ��    �ܣ�
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/07/08	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
namespace AutoUIFactory
{

class CWindowTypeManage : public IObserver, public Singleton<CWindowTypeManage>
{
public:
	static const String strSrcType;
	static const String strTagType;
	static const String strType;
public:
	CWindowTypeManage();
	virtual ~CWindowTypeManage();
	void Update( IArgs* pArgs );
	String GetType( String& strSrcType );
protected:
	void Update( XMLAttributes& xmlAttribs );
	typedef std::map<String,String> TypeMaps;
	TypeMaps m_mapTypes;
};

}

#endif // !defined(AFX_WINDOWTYPEMANAGE_H__63893F50_A110_4278_9C0C_0DEC1D3E5C9F__INCLUDED_)
