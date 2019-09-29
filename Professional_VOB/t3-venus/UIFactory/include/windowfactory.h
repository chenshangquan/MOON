#ifndef WINDOWFACTORY_H
#define WINDOWFACTORY_H
#include "uifactorydef.h"
/*---------------------------------------------------------------------
* ��	����windowfactory
* ��    �ܣ�UI�ؼ���������
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/05/09	v1.0		Ĳ��ï		����
---------------------------------------------------------------------*/
namespace AutoUIFactory
{

class IWindowFactory
{
public:
	/*---------------------------------------------------------------------
	* �� �� ����createWindow
	* ��    �ܣ�����һ���ؼ�
	* ����˵����[in] name ����
	* �� �� ֵ��Ŀǰ����CWndָ��
	* �޸ļ�¼��
	* ����			�汾		�޸���		�޸ļ�¼
	* 2011/05/09	v1.0		Ĳ��ï		����
	----------------------------------------------------------------------*/
	virtual Window* Create( IArgs& iAgrs ) = 0;

	static unsigned int GetUniqID()
	{
		static unsigned int wID = 10000;
		return wID++;
	}
public:
	static const DWORD m_dwDefaultStyle;
	static const DWORD m_dwDebugStyle;
	static const CRect m_rcDefaultRect;
};

#ifndef GETUNIQID
#define GETUNIQID IWindowFactory::GetUniqID()
#endif


#define DECLARE_WINDOW_FACTORY( classname ) \
class classname ## Factory : public IWindowFactory \
{ \
public: \
	virtual Window* Create( IArgs& iArgs ); \
}; 

/*---------------------------------------------------------------------
* ��	CWindowDefaultStyleMap
* ��    �ܣ��ṩһ�����ַ��������Styleת��������WS_VISIBLE��һ���ַ�������Ҫת��Ϊ��
* ����˵����
* �޸ļ�¼��
* ����			�汾		�޸���		�޸ļ�¼
* 2011/06/02	v1.0		Ĳ��ï		����
----------------------------------------------------------------------*/
class CWindowDefaultStyleMap
{
public:
	static const char m_chPartitionChar;
public:
	/**  ͨ��һ���ַ���ת��Ϊһ�����
	 *  @param[in] str �ַ���
	 *  @param[out] dwStyle ���
	 *  @return �Ƿ�ɹ�
	 */
	static bool StringToStyle( String& str, DWORD& dwStyle );


    static bool StringToStyle( String& str, DWORD& dwStyle, DWORD& dwStyleEx );

	/**  ע��һ������Ӧ��ϵ Ĭ��ע�����CRegDefaultData����
	 *  @param[in] dwStyle	���
	 *  @param[in] str		�ַ���
	 *  @return �Ƿ�ɹ�
	 */
	static bool RegStyle( DWORD dwStyle, String str );
protected:
	typedef std::map< String, DWORD > DefaultStyleMap;
	static DefaultStyleMap m_mapStyles;
};

/*
 * ע���һ��ID��һ���ַ�����ӳ��\n 
 */
#ifndef REG_DEFAULT_WINDOW_STYLE
#define REG_DEFAULT_WINDOW_STYLE( id ) CWindowDefaultStyleMap::RegStyle( id, #id );
#endif


} // namespace AutoUIFactory end
#endif