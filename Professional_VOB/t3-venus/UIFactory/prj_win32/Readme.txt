======================================================================================
								UIFactory
/*
���һ���¿ؼ�������
1����ӹ����������Ŀؼ���ΪCXXX�����ú�DECLARE_WINDOW_FACTORY(CXXX) 
	�������������ᵼ���޷�������Ӧ�ؼ���

2������˹�������Ҫ��CRegDefaultData�����RegDefaultWindowFactory��������ע��	
	��ʹ�ú�REG_WINDOW_FACTORY(CXXX)
	�������������ᵼ���޷�������Ӧ�ؼ���

3���ؼ�д�ú���ҪΪ��������Լ�����ʹ�ú� DECLARE_PROPERTYSET_BEGIN( CXXX, IPropertySet ) �� DECLARE_PROPERTYSET_END
	�����Ҫ����һЩĬ�ϵ����ԣ��뽫IPropertySet�޸�ΪCWndPropertySet
	�������������ᵼ���޷���xml�������õ������޷����õ���Ӧ�Ŀؼ��ϣ�

4��д�ÿؼ���������Ҫ��CRegDefaultData�����RegDefaultWindowPropertySet��������ע��
	Ҳ��ʹ�ú�REG_PROPERTY_SET(CXXX)
	�������������ᵼ���޷���xml�������õ������޷����õ���Ӧ�Ŀؼ��ϣ�

5������ؼ�������ӵ����ԣ���ʹ�ú�DECLARE_VALUE_BEGIN(CXXXImage) DECLARE_VALUE_END ��������
	����ע��������ο���
	�������������ᵼ���޷���xml��������������ò���ȥ��

6�������������Ҫ�滻�����ԣ�����CXXXImage��Ҫ�滻WindowPos������ԣ�ֱ���ڵ�3���ĺ��м����
	AddProperty( "WindowPos", "CXXXImage" );
	�������Ҫ�滻�����ں��м�д
	AddProperty( "CXXXImage", "CXXXImage" );
	�������������ᵼ���޷���xml��������������ò���ȥ��

7����������Ժ���Ҫ��CRegDefaultData�����RegDefaultWindowProperty��������ע��
	ʹ�ú�REG_PROPERTY(CXXXImage)
	�������������ᵼ���޷���xml��������������ò���ȥ��
*/
======================================================================================