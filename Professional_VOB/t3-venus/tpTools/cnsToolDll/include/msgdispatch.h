// MsgDispatch.h: interface for the CMsgDispatch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MSGDISPATCH_H__88B55A09_8C28_4EA6_B12B_C8DBFEBFE51E__INCLUDED_)
#define AFX_MSGDISPATCH_H__88B55A09_8C28_4EA6_B12B_C8DBFEBFE51E__INCLUDED_

#pragma warning( disable : 4786 )	// ��ʶ�����Ƴ���255�ֽ�

#include <map>
#include <vector>
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
using namespace std;


class CCallBackFunBase
{ 
public:
    //����ص������ĸ�ʽ
     virtual HRESULT operator() ( WPARAM wParam, LPARAM lParam ) = 0;
};

template<class T> class CMsgCallBackFun:public  CCallBackFunBase
{
public:
    //����ص������ĸ�ʽ
    typedef LRESULT (T::*MemberFunctionType)(  WPARAM wParam, LPARAM lParam  );
    
    // �����ʱ����ҪΪ������ֵ
    CMsgCallBackFun ( MemberFunctionType pFunc, T* pObject )
    {
         m_pObject = pObject;
         m_pFuc = pFunc ;
    }
    
    virtual HRESULT operator()( WPARAM wParam, LPARAM lParam )
    {
        return (m_pObject->*m_pFuc)( wParam, lParam);
    }
    
private:
    T* m_pObject;
    MemberFunctionType m_pFuc;	
};

 
typedef std::map< DWORD ,  vector< CCallBackFunBase * > > FuncMap;

class CMsgDispatch 
{
public:
	CMsgDispatch();
	virtual ~CMsgDispatch();
/**  ע��ȫ�ֺ���
 *  @param[in] strName ��������Ӧ������ ����Ψһ
 *  @param[in] piFunc ����ָ�룬�����Ǿ�̬�����������ǳ�Ա������
 *  @return �Ƿ�ɹ�
 */
	static bool RegFunc( DWORD dwMsgID, CCallBackFunBase* piFunc );

/**  ��ע��ȫ�ֺ���
 *  @param[in] dwMsgID ��������Ӧ����ϢID
 *  @return �Ƿ�ɹ�
 */
    static bool UnRegFunc( DWORD dwMsgID , CCallBackFunBase* piFunc );
//	static bool UnRegFunc( DWORD dwMsgID);


   static bool SendMessage( u32 dwMessage, WPARAM wParam, LPARAM lParam );

/**  ִ�к���
 *  @param[in] dwMsgID ��������Ӧ����ϢID
 *  @param[in]  
 *  @see IArgs
 *  @param[out] 
 *  @return �Ƿ�ɹ�
 */
//	bool ExeFunc( DWORD dwMsgID, WPARAM wParam, LPARAM lParam );
protected:
	
    static FuncMap m_mapFuncs;
 
};

/*
* ע��ȫ�ֺ����������Ա������Ϊ����ָ�� \n
* dwMsgID ����ID func ������ obj ��ָ�� objType ������
*/
#ifndef REG_MSG_HANDLER
#define REG_MSG_HANDLER( dwMsgID, func, obj, objType ) \
CMsgDispatch::RegFunc( dwMsgID, new CMsgCallBackFun<objType>( func, obj ) );
#endif 

 

/*
* ��ע��ȫ�ֺ��� \n
* str ������ʾ
*/
#ifndef UN_REG_MSG_HANDLER
#define UN_REG_MSG_HANDLER(  dwMsgID, func, obj, objType  ) CMsgDispatch::UnRegFunc( dwMsgID ,new CMsgCallBackFun<objType>( func, obj ) );
#endif


#endif