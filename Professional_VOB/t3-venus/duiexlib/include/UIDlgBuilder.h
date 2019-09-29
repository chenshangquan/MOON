#ifndef __UIDLGBUILDER_H__
#define __UIDLGBUILDER_H__

#pragma once

namespace DuiLib {

class IDialogBuilderCallback
{
public:
    virtual CControlUI* CreateControl(LPCTSTR pstrClass) = 0;
};


class UILIB_API CDialogBuilder
{
public:
    CDialogBuilder();
    CControlUI* Create(STRINGorID xml, LPCTSTR type = NULL, IDialogBuilderCallback* pCallback = NULL,
        CPaintManagerUI* pManager = NULL, CControlUI* pParent = NULL);
    CControlUI* Create(IDialogBuilderCallback* pCallback = NULL, CPaintManagerUI* pManager = NULL,
        CControlUI* pParent = NULL);

    CMarkup* GetMarkup();

    void GetLastErrorMessage(LPTSTR pstrMessage, SIZE_T cchMax) const;
    void GetLastErrorLocation(LPTSTR pstrSource, SIZE_T cchMax) const;


	//2013.4.26 ִ�� Ĭ�Ϸ��� yjj
	//��param��in  pstrXml Ҫִ��Ĭ�Ϸ�����xml�ļ��� 
	//bool DoDefCase( LPCTSTR pstrXm, IDialogBuilderCallback* pCallback, CPaintManagerUI* pManager, CControlUI* pParent );
private:
    CControlUI* _Parse(CMarkupNode* parent, CControlUI* pParent = NULL, CPaintManagerUI* pManager = NULL);
	bool		CreateChildControl( CMarkupNode* pNode, CControlUI* pParent = NULL, CPaintManagerUI* pManager = NULL);
    CMarkup m_xml;
    IDialogBuilderCallback* m_pCallback;
    LPCTSTR m_pstrtype;
};

} // namespace DuiLib

#endif // __UIDLGBUILDER_H__
