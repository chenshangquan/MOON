#ifndef UIFACTORY_HEADER
#define UIFACTORY_HEADER

/*
���һ���¿ؼ�������
1����ӹ����������Ŀռ���ΪCXXX�����ú�DECLARE_WINDOW_FACTORY(CXXX)
2������˹�������Ҫ��CRegDefaultData�����RegDefaultWindowFactory��������ע��
	��ʹ�ú�REG_WINDOW_FACTORY(CXXX)
3���ؼ�д�ú���ҪΪ��������Լ�����ʹ�ú� DECLARE_PROPERTYSET_BEGIN( CXXX, IPropertySet ) �� DECLARE_PROPERTYSET_END
	�����Ҫ����һЩĬ�ϵ����ԣ��뽫IPropertySet�޸�ΪCWndPropertySet
4��д�ÿؼ���������Ҫ��CRegDefaultData�����RegDefaultWindowPropertySet��������ע��
	Ҳ��ʹ�ú�REG_PROPERTY_SET(CXXX)
5������ؼ�������ӵ����ԣ���ʹ�ú�DECLARE_VALUE_BEGIN(CXXXImage) DECLARE_VALUE_END ��������
	����ע��������ο���
6�������������Ҫ�滻�����ԣ�����CXXXImage��Ҫ�滻WindowPos������ԣ�ֱ���ڵ�3���ĺ��м����
	AddProperty( "WindowPos", "CXXXImage" );
7����������Ժ���Ҫ��CRegDefaultData�����RegDefaultWindowProperty��������ע��
	ʹ�ú�REG_PROPERTY(CXXXImage)
*/
#include "uifactorydef.h"
#include "System.h"
#include "windowfactory.h"
#include "WndMsgEventManage.h"
#include "IProperty.h"
#include "IPropertyAssist.h"
#include "PropertySet.h"
#include "templateClass.h"
#include "CallFuncManage.h"
#include "WindowManage.h"
#include "MfcDefaultArgs.h"
#include "MfcDefaultWndFactory.h"
#include "MfcDefaultWndProperty.h"
#include "MfcDefaultWndPropertySet.h"
#include "WndTreeHelp.h"
#include "SaveXmlHelp.h"
#include "UILayoutHelp.h"
#include "ItemFactory.h"
#include "UIExLibArgs.h"
#include "UIExLibPropertySet.h"
#include "SchemeHelp.h"
using namespace AutoUIFactory;
#endif