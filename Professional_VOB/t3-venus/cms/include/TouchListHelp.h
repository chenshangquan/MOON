// TouchListHelp.h: interface for the CTouchListHelp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOUCHLISTHELP_H__D7E8F6C1_53D8_42D1_ADF1_62E897B0276C__INCLUDED_)
#define AFX_TOUCHLISTHELP_H__D7E8F6C1_53D8_42D1_ADF1_62E897B0276C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "umclib.h"
#include "cnclib.h"
#include "tplarray.h"
#include "cmsstruct.h"
#include "TouchListProperty.h"


 
class CTouchListHelp  
{
public:
	const static String strConfTemplate;
    const static String strTempCns;
    const static String strItemTempPoll;
	const static String strListAddr;
	const static String strItemConf;
    const static String strConfCns;    //�����л᳡�б�
    const static String strConfLst;    //�����б�
    const static String strListUser;   //�û��б�
	const static String strListTvw;		//����ǽ�б�
	const static String strListAlarm;

	const static String strItemDefault;
	const static String strItemText;
    const static String strItemAddrList;
    const static String strListMenu;
	const static String strListCnsList;
	const static String strListConnectCn;
	const static String strListConfMenu;
    const static String strVerListConfMenu;
    const static String strListDualSrc;
	const static String strListWebManage;
    
    //static MapLstName m_mapStrListName;
	typedef IItem< IBaseItem, int > IItemList;

    //�б��д���Item�������
    class Args_MakeItem : public IArgs
    {
    public:  
        IItemList* pList;
        BOOL32 bDrag;   //��item�Ƿ�����϶�
        int nKey;      //��item���䵱ǰ����б�����ռ�Ĵ���
        String strTxt;  //item����ʾ���ַ���
        IData* pUserData;  //�û���Ϣ����Ҫ���ڵ��ʱ������click�¼��Ĳ���
        String strClickItemFunc; //����¼�
        ARRAY<String>* pVctSubItem; //item����ʾ��ͼ��
        String strImageItem ;      //��Ӧ��imgItem����
        String strTxtItem;          //��Ӧ��txtItem����
        String strLayoutAlgorithm;  //item�Ĳ����㷨
        EmItemStatus emItemStatus;  //item״̬

        Args_MakeItem( ):IArgs("MakeItem" )
        {
            pList = NULL;
            bDrag = FALSE;
            nKey =-1;
            strTxt.erase();
            pUserData = 0;
            strClickItemFunc.erase();
            pVctSubItem  = NULL;
            strImageItem = CTouchListHelp::strItemAddrList;
            strTxtItem = CTouchListHelp::strItemText;
            strLayoutAlgorithm= IAlgorithm::strNormalItem ;
            emItemStatus = emItemStatusNormal; 
        }
        
};

public:
    CTouchListHelp();
    virtual ~CTouchListHelp();
    static bool SetData( IItemList* pList, const IValue* pValue );
protected: 
//     ģ���б�
//         static bool TransData( IItemList* pList, TplArray<TTPConfTemplate>* pConfTemplate, String strItemFunc, 
//                        ARRAY<String> * pVctSubItem ,BOOL32 bDrag); 

    //ģ���б�
    static bool TransData( IItemList* pList, Value_TouchListConfTemp &val); 
    
//     //ģ���е�cns�б�
//     static bool TransData( IItemList* pList, TEpAddrList  &tCnsLst ,  String strClickItemFunc,  
//                    ARRAY<String> * pVctSubItem,BOOL32 bDrag);
    
    
    //ģ���е�cns�б�
    static bool TransData( IItemList* pList, Value_TouchListTempCns &val );


    //ģ���е���ѯ�б�
    static bool TransData( IItemList* pList, TCMSConfTemplate &tConfTemp,  String strClickItemFunc,  
                  ARRAY<String> * pVctSubItem,BOOL32 bDrag);
    
    //��ַ���б�
    static bool TransData( IItemList* pList, Value_TouchListAddr& valAddr/*ARRAY<TAddrItem>* pArray, String strItemFunc, ARRAY<String>* pSubItem, BOOL bSort*/ );

    //������cns�б�
    static bool TransData( IItemList* pList, Value_TouchListConfInfo &val);

    //�����б�
    static bool TransData( IItemList* pList, Value_TouchListConf &val);
      
    //�˵��б�
    static bool TransData( IItemList* pList, ARRAY<TMenuItemInfo> *pvctMenuLst, BOOL32 bDrag );

	//CNS�����ӵĻ᳡�б�
	static bool TransData( IItemList* pList, ARRAY<TTPCnsInfo>* pArray, String strItemFunc, ARRAY<String>* pSubItem );

	//�û��б�
	static bool TransData( IItemList* pList, Value_TouchListUser &val);

	//�澯�б�
	static bool TransData( IItemList* pList, ARRAY<String>* pArray );

	//����ʱ��Cns�б�
	static bool TransData( IItemList* pList, TTPCnList* ptCnList, String strItemFunc );

	//���������˵��б�  ˮƽ�б�  
	static bool TransData( IItemList* pList, ARRAY<TConfMenuInfo>* pArray );
  
    //��ֱ�б�   ���������˵��б�
    static bool TransData( IItemList* pList, Value_VerListConfMenu &val);

    //˫��Դ�б�
    static bool TransData( IItemList* pList, Value_ListDualSrc &val );
 
private:
    static bool MakeItem ( Args_MakeItem &agrs )  ;
};

#endif // !defined(AFX_TOUCHLISTHELP_H__D7E8F6C1_53D8_42D1_ADF1_62E897B0276C__INCLUDED_)
