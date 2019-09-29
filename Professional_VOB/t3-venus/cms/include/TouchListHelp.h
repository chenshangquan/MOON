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
    const static String strConfCns;    //会议中会场列表
    const static String strConfLst;    //会议列表
    const static String strListUser;   //用户列表
	const static String strListTvw;		//电视墙列表
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

    //列表中创建Item所需参数
    class Args_MakeItem : public IArgs
    {
    public:  
        IItemList* pList;
        BOOL32 bDrag;   //该item是否可以拖动
        int nKey;      //该item在其当前层的列表中所占的次序
        String strTxt;  //item上显示的字符串
        IData* pUserData;  //用户信息，主要用于点击时产生的click事件的参数
        String strClickItemFunc; //点击事件
        ARRAY<String>* pVctSubItem; //item上显示的图标
        String strImageItem ;      //对应的imgItem类型
        String strTxtItem;          //对应的txtItem类型
        String strLayoutAlgorithm;  //item的布局算法
        EmItemStatus emItemStatus;  //item状态

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
//     模板列表
//         static bool TransData( IItemList* pList, TplArray<TTPConfTemplate>* pConfTemplate, String strItemFunc, 
//                        ARRAY<String> * pVctSubItem ,BOOL32 bDrag); 

    //模板列表
    static bool TransData( IItemList* pList, Value_TouchListConfTemp &val); 
    
//     //模板中的cns列表
//     static bool TransData( IItemList* pList, TEpAddrList  &tCnsLst ,  String strClickItemFunc,  
//                    ARRAY<String> * pVctSubItem,BOOL32 bDrag);
    
    
    //模板中的cns列表
    static bool TransData( IItemList* pList, Value_TouchListTempCns &val );


    //模板中的轮询列表
    static bool TransData( IItemList* pList, TCMSConfTemplate &tConfTemp,  String strClickItemFunc,  
                  ARRAY<String> * pVctSubItem,BOOL32 bDrag);
    
    //地址簿列表
    static bool TransData( IItemList* pList, Value_TouchListAddr& valAddr/*ARRAY<TAddrItem>* pArray, String strItemFunc, ARRAY<String>* pSubItem, BOOL bSort*/ );

    //会议中cns列表
    static bool TransData( IItemList* pList, Value_TouchListConfInfo &val);

    //会议列表
    static bool TransData( IItemList* pList, Value_TouchListConf &val);
      
    //菜单列表
    static bool TransData( IItemList* pList, ARRAY<TMenuItemInfo> *pvctMenuLst, BOOL32 bDrag );

	//CNS已连接的会场列表
	static bool TransData( IItemList* pList, ARRAY<TTPCnsInfo>* pArray, String strItemFunc, ARRAY<String>* pSubItem );

	//用户列表
	static bool TransData( IItemList* pList, Value_TouchListUser &val);

	//告警列表
	static bool TransData( IItemList* pList, ARRAY<String>* pArray );

	//连接时的Cns列表
	static bool TransData( IItemList* pList, TTPCnList* ptCnList, String strItemFunc );

	//会议中主菜单列表  水平列表  
	static bool TransData( IItemList* pList, ARRAY<TConfMenuInfo>* pArray );
  
    //垂直列表   会议中主菜单列表
    static bool TransData( IItemList* pList, Value_VerListConfMenu &val);

    //双流源列表
    static bool TransData( IItemList* pList, Value_ListDualSrc &val );
 
private:
    static bool MakeItem ( Args_MakeItem &agrs )  ;
};

#endif // !defined(AFX_TOUCHLISTHELP_H__D7E8F6C1_53D8_42D1_ADF1_62E897B0276C__INCLUDED_)
