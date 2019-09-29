// IScript.h: interface for the IScript class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ISCRIPT_H__5142ED78_9EC4_4E00_A49B_86D0DFA8E5F8__INCLUDED_)
#define AFX_ISCRIPT_H__5142ED78_9EC4_4E00_A49B_86D0DFA8E5F8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/*---------------------------------------------------------------------
* ��	����IScript
* ��    �ܣ��ű�ִ����
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/05/11	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
namespace AutoUIFactory
{

Interface IScript : public Singleton<IScript>
{
public:
	IScript();
	virtual ~IScript();
	/*
		strScript �ű��ı���nType �ű�����(�������ű�)
	*/
	virtual bool ExecuteScript( String strScript, String strType = "" ) = 0;
};

} // namespace AutoUIFactory end
#endif // !defined(AFX_ISCRIPT_H__5142ED78_9EC4_4E00_A49B_86D0DFA8E5F8__INCLUDED_)
