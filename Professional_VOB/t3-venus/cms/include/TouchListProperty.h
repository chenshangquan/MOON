// TouchListProperty.h: interface for the CTouchListProperty class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TOUCHLISTPROPERTY_H__04260821_1F80_4C85_A679_1B121DF07E09__INCLUDED_)
#define AFX_TOUCHLISTPROPERTY_H__04260821_1F80_4C85_A679_1B121DF07E09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "umclib.h"
#include "cnclib.h"

class Property_TouchListData : public IProperty
{
public: 
	Property_TouchListData() : IProperty( "TouchListData", "通过会议模板设置数据", "0"){} 	
	bool set( Window* tag, const String& value ); 
	bool set( Window* tag, const IValue& value ); 
};


//会议模板列表
class Value_TouchListConfTemp : public IValue
{
public:
	Value_TouchListConfTemp( vector<TTPAlias>* pList,String strItemFunc = IBaseItem::strDefaultFunc ,
                             vector<String> * pVctSubItem = NULL, BOOL32 bDrag = FALSE, BOOL32 bShowALl = FALSE) 
		: IValue( "TouchListConfTemp" ), m_pvctConfTemplate( pList ), m_strItemFunc( strItemFunc ), m_pVctSubItem( pVctSubItem ), m_bDrag(bDrag),m_bShowAll(bShowALl){}
	vector<TTPAlias>* m_pvctConfTemplate;
	String m_strItemFunc;			 // 条目点击回调函数 
    vector<String> * m_pVctSubItem;  //子条目对应的xml中名字
    BOOL32 m_bDrag;                  //是否可以拖动
    BOOL32 m_bShowAll;              //是否全部显示，如果是否，则只显示当前所登录会场是默认主席的模板
};

class Data_ConfTemp : public IData
{
public:
    Data_ConfTemp( TTPAlias &tConfTemp ) : IData( "ConfTemp" ), m_tConfTemp( tConfTemp ){}
    IData* Clone()
    {
        Data_ConfTemp* pData = new Data_ConfTemp( m_tConfTemp );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
    TTPAlias  m_tConfTemp;
};

//会议模板所含的cns列表
class Value_TouchListTempCns : public IValue
{
public: 
    Value_TouchListTempCns( TEpAddrList  &tCnsLst , String strClickItemFunc =  IBaseItem::strDefaultFunc , 
        vector<String> * pVctSubItem = NULL,BOOL bDrag = FALSE , u16 wChaim = -1 )
        : IValue( "TouchListTempCns" ), m_tCnsLst( tCnsLst ),m_strClickItemFunc(strClickItemFunc),  m_pVctSubItem( pVctSubItem ),m_bDrag(bDrag), m_wChairManID( wChaim ) {}
     TEpAddrList  m_tCnsLst;           // cns列表 
     u16          m_wChairManID;       //主席对应的cnsID，如果无主席的列表，则为0xffff 
     String  m_strClickItemFunc;	   // 条目点击回调函数 
     vector<String> * m_pVctSubItem;   //子条目对应的xml中名字
     BOOL32 m_bDrag;                   //是否可以拖动
};

class Data_CnsID : public IData
{
public:
    Data_CnsID( u16 wCnsID ) : IData( "CnsID" ), m_wData( wCnsID ){}
    IData* Clone()
    {
        Data_CnsID* pData = new Data_CnsID( m_wData );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
    u16  m_wData;
};
 

//会议模板所含的轮询列表
class Value_TouchListTempPoll : public IValue
{
public: 
    Value_TouchListTempPoll(TCMSConfTemplate &tConfTemp ,String m_strClickItemFunc  =  IBaseItem::strDefaultFunc  , 
           vector<String> * pVctSubItem = NULL, BOOL bDrag = FALSE )
        : IValue( "TouchListTempPoll" ), m_tTemp( tConfTemp ), m_strClickItemFunc(m_strClickItemFunc), m_pVctSubItem( pVctSubItem ),m_bDrag(bDrag) {}
    TCMSConfTemplate  m_tTemp;          // 
    String  m_strClickItemFunc;	      // 条目点击回调函数 
    vector<String> * m_pVctSubItem;  //子条目对应的xml中名字
    BOOL32 m_bDrag;
};

class Data_CnsAddr : public IData
{
public:
    Data_CnsAddr( TEpAddr  tCnsAddr ) : IData( "CnsAddr" ), m_tEpAddr( tCnsAddr ){}
    IData* Clone()
    {
        Data_CnsAddr* pData = new Data_CnsAddr( m_tEpAddr );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
    TEpAddr    m_tEpAddr;
};

class Value_TouchListAddr : public IValue
{
public:
	Value_TouchListAddr( vector<TAddrItem>* pArray, vector<String>* pSubItem = NULL, String strItemFunc = IBaseItem::strDefaultFunc,
        BOOL32 bSort = TRUE, BOOL32 bGlobalAddr = FALSE )
		: IValue( "TouchListAddr" ), m_pAddrList( pArray ), m_strItemFunc( strItemFunc ), m_pSubItem( pSubItem ),
          m_bSort( bSort ), m_bGlobalAddr( bGlobalAddr ){}
	vector<TAddrItem>* m_pAddrList;
	String             m_strItemFunc;
	vector<String>*    m_pSubItem;
	BOOL32             m_bSort;
    BOOL32             m_bGlobalAddr;
};

class Data_AddrItemInfo : public IData
{
public:
	Data_AddrItemInfo( TAddrItem& tItem ) : IData( "AddrItemInfo" ), m_tAddrItem( tItem ){}
	IData* Clone()
	{
		Data_AddrItemInfo* pItemInfo = new Data_AddrItemInfo( m_tAddrItem );
		pItemInfo->SetDataKey( GetDataKey() );
		return pItemInfo;
	}
	TAddrItem  m_tAddrItem;
};


//登录连接时的会场列表
class Value_ListConnectCns : public IValue
{
public:
	Value_ListConnectCns( TTPCnList* ptCnList, String strItemFunc = IBaseItem::strDefaultFunc )
		: IValue( "ListConnectCns" ), m_ptCnList( ptCnList ), m_strItemFunc( strItemFunc ){}
	TTPCnList*          m_ptCnList;
	String              m_strItemFunc;
};

class Data_TPCnInfo : public IData
{
public:
	Data_TPCnInfo( TTPCn& tInfo ) : IData( "TPCnInfo" ), m_tCnInfo( tInfo ){}
	IData* Clone()
	{
		Data_TPCnInfo* pCnInfo = new Data_TPCnInfo( m_tCnInfo );
		pCnInfo->SetDataKey( GetDataKey() );
		return pCnInfo;
	}
	TTPCn  m_tCnInfo;
};


//系统配置，CNS连接的会场列表
class Value_TouchListCnsList : public IValue
{
public:
	Value_TouchListCnsList( vector<TTPCnsInfo>* pArray, String strItemFunc = IBaseItem::strDefaultFunc, vector<String>* pSubItem = NULL )
		: IValue( "TouchListCnsList" ), m_pCnsList( pArray ), m_strItemFunc( strItemFunc ), m_pSubItem( pSubItem ) {}
	vector<TTPCnsInfo>* m_pCnsList;
	String              m_strItemFunc;
	vector<String>*     m_pSubItem;
};

class Data_TPCnsInfo : public IData
{
public:
	Data_TPCnsInfo( TTPCnsInfo* pInfo ) : IData( "TPCnsInfo" ), m_pCnsInfo( pInfo ){}
	IData* Clone()
	{
		Data_TPCnsInfo* pCnsInfo = new Data_TPCnsInfo( m_pCnsInfo );
		pCnsInfo->SetDataKey( GetDataKey() );
		return pCnsInfo;
	}
	TTPCnsInfo*  m_pCnsInfo;
};


//会议列表
class Value_TouchListConf : public IValue
{
public:
    Value_TouchListConf( ARRAY<TCMSConf>* pList, String strItemFunc = IBaseItem::strDefaultFunc ,
        ARRAY<String> * pVctSubItem = NULL, BOOL32 bDrag = FALSE) 
        : IValue( "TouchListConf" ), m_pTplAryConf( pList ), m_strItemFunc( strItemFunc ), m_pVctSubItem( pVctSubItem ), m_bDrag(bDrag) {}
    ARRAY<TCMSConf>* m_pTplAryConf ;
    String m_strItemFunc;			 // 条目点击回调函数 
    vector<String> * m_pVctSubItem;  //子条目对应的xml中名字
    BOOL32 m_bDrag;                  //是否可以拖动
};


class Data_Conf : public IData
{
public:
    Data_Conf( TCMSConf  &tConf  ) : IData( "Conf" ), m_tCmsConf( tConf ){}
    IData* Clone()
    {
        Data_Conf* pData = new Data_Conf ( m_tCmsConf );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }

    TCMSConf  m_tCmsConf ;
};



enum EM_ConfLst_Type
{
   em_ConfLstTypeCns,    //会议中cns列表
   em_ConfLstTypeAudmix, //混音列表
   em_ConfLstTypePoll,   //会议中轮询列表
   em_ConfLstTypeTvw,    //电视墙界面中的
   em_ConfLstTypwSelView, //选看列表
};

//会议中cns列表
class Value_TouchListConfInfo : public IValue
{
public:
    Value_TouchListConfInfo( TCMSConf &tConf, String strClickItemFunc = IBaseItem::strDefaultFunc ,
        vector<String> * pVctSubItem = NULL, String strAlgroithm = IAlgorithm::strVert,
        BOOL32 bDrag = FALSE,EM_ConfLst_Type lstType = em_ConfLstTypeCns ) 
        : IValue( "TouchListConfInfo" ), m_tConf( tConf ), m_strClickItemFunc( strClickItemFunc ),
        m_pVctSubItem( pVctSubItem ), m_strAlgroithm(strAlgroithm),m_bDrag(bDrag),m_lstType(lstType) {}
    TCMSConf m_tConf ;
    String m_strClickItemFunc;		    	// 条目点击回调函数 
    vector<String> * m_pVctSubItem;  //子条目对应的xml中名字
    BOOL32 m_bDrag;                  //是否可以拖动
    String m_strAlgroithm;           //排列算法
    EM_ConfLst_Type m_lstType;
};

class Data_ConfCns : public IData
{
public:
    Data_ConfCns( TCnsInfo tConfCns ) : IData( "ConfCns" ), m_tConfCns( tConfCns ){}
    IData* Clone()
    {
        Data_ConfCns* pData = new Data_ConfCns( m_tConfCns );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
    TCnsInfo  m_tConfCns;
};



//用户列表
class Value_TouchListUser : public IValue
{
public:
    Value_TouchListUser( TplArray<CUserFullInfo>* pUserLst, String strClickItemFunc = IBaseItem::strDefaultFunc ,
        vector<String> * pVctSubItem = NULL, String strAlgroithm = IAlgorithm::strVert,
        BOOL32 bDrag = FALSE,EM_ConfLst_Type lstType = em_ConfLstTypeCns ) 
        : IValue( "TouchListUser" ), m_pTplArryUser( pUserLst ), m_strClickItemFunc( strClickItemFunc ),
        m_pVctSubItem( pVctSubItem ), m_strAlgroithm(strAlgroithm),m_bDrag(bDrag),m_lstType(lstType) {}
   
    TplArray<CUserFullInfo>*  m_pTplArryUser ;
    String m_strClickItemFunc;		    	// 条目点击回调函数 
    vector<String> * m_pVctSubItem;  //子条目对应的xml中名字
    BOOL32 m_bDrag;                  //是否可以拖动
    String m_strAlgroithm;           //排列算法
    EM_ConfLst_Type m_lstType;
};

class Data_User : public IData
{
public:
    Data_User( CUserFullInfo &cUser ) : IData( "User" ), m_cUser( cUser ){}
    IData* Clone()
    {
        Data_User* pData = new Data_User( m_cUser );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }

    CUserFullInfo m_cUser;
};

struct TMenuItemInfo
{
    String strTxt;  //条目显示的文字
    vector<String> * m_pVctSubItem;  //子条目对应的xml中名字
    String strItemFunc; //条目的单击事件
    String strImageItem;  
    String strTxtItem;  
    TMenuItemInfo()
    {
        Clear();
    }

    void Clear()
    {
        m_pVctSubItem = NULL;
        strTxt = "";
        strItemFunc = "";
        strImageItem =  "SysCfgItem";
        strTxtItem =  "TextItemWhite"; 
    }
};


//菜单列表 
class Value_TouchListMenu: public IValue
{
public:
    Value_TouchListMenu( ARRAY<TMenuItemInfo> *pvctMenuList,  BOOL32 bDrag = FALSE) 
        : IValue( "TouchListMenu" ), m_pMenuLst( pvctMenuList ),  m_bDrag(bDrag) {}
    ARRAY<TMenuItemInfo> *m_pMenuLst; 
    BOOL32 m_bDrag;                  //是否可以拖动
};
 
class Data_Menu : public IData
{
public:
    Data_Menu( TMenuItemInfo &tMenu ) : IData( "Menu" ), m_tMenuInfo( tMenu ){}
    IData* Clone()
    {
        Data_Menu* pData = new Data_Menu( m_tMenuInfo );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
    
    TMenuItemInfo m_tMenuInfo;
};


//电视墙列表 
class Value_TouchListTvw: public IValue
{
public:  
    Value_TouchListTvw( TplArray<TCmsTvwInfo> *pTvwLst, String strClickItemFunc = IBaseItem::strDefaultFunc ,
        vector<String> * pVctSubItem = NULL, String strAlgroithm = IAlgorithm::strVert,
        BOOL32 bDrag = FALSE,EM_ConfLst_Type lstType = em_ConfLstTypeCns ) 
        : IValue( "TouchListTvw" ), m_pTvwLst( pTvwLst ), m_strClickItemFunc( strClickItemFunc ),
        m_pVctSubItem( pVctSubItem ), m_strAlgroithm(strAlgroithm),m_bDrag(bDrag),m_lstType(lstType) {}
    
    TplArray<TCmsTvwInfo> *m_pTvwLst; 
    String m_strClickItemFunc;		    	// 条目点击回调函数 
    vector<String> * m_pVctSubItem;  //子条目对应的xml中名字
    BOOL32 m_bDrag;                  //是否可以拖动
    String m_strAlgroithm;           //排列算法
    EM_ConfLst_Type m_lstType;
};

class Data_Tvw : public IData
{
public:
    Data_Tvw( TCmsTvwInfo &tTvw ) : IData( "Menu" ), m_tTvwInfo( tTvw ){}
    IData* Clone()
    {
        Data_Tvw* pData = new Data_Tvw( m_tTvwInfo );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
    
    TCmsTvwInfo m_tTvwInfo;
};

//告警信息列表
class Value_TouchListAlarm : public IValue
{
public:
	Value_TouchListAlarm( vector<String>* pArray )
		: IValue( "TouchListAlarm" ), m_pAlarmList( pArray ){}
	vector<String>* m_pAlarmList;
};

 
class Value_HoriListConfMenu : public IValue
{
public:
	Value_HoriListConfMenu( vector<TConfMenuInfo>* pArray )
		: IValue( "HoriListConfMenu" ), m_pMenuList( pArray ){}
	vector<TConfMenuInfo>* m_pMenuList;
};


//会议控制列表 
class Value_VerListConfMenu: public IValue
{
public:  
    Value_VerListConfMenu( ARRAY<TConfMenuInfo> *pLst, String strClickItemFunc = IBaseItem::strDefaultFunc ,
        vector<String> * pVctSubItem = NULL, String strAlgroithm = IAlgorithm::strVert, BOOL32 bDrag = FALSE ) 
        :IValue( "VerListConfMenu" ), m_pConfMenuLst( pLst ), m_strClickItemFunc( strClickItemFunc ),
        m_pVctSubItem( pVctSubItem ), m_strAlgroithm(strAlgroithm),m_bDrag(bDrag){}
    
    ARRAY<TConfMenuInfo> *m_pConfMenuLst; 
    String m_strClickItemFunc;		    	// 条目点击回调函数 
    vector<String> * m_pVctSubItem;  //子条目对应的xml中名字
    BOOL32 m_bDrag;                  //是否可以拖动
    String m_strAlgroithm;           //排列算法
    
};

class Data_ConfMenu : public IData
{
public:
    Data_ConfMenu( TConfMenuInfo &tMenu ) : IData( "Menu" ), m_tConfMenuInfo( tMenu ){}
    IData* Clone()
    {
        Data_ConfMenu* pData = new Data_ConfMenu( m_tConfMenuInfo );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
    
    TConfMenuInfo m_tConfMenuInfo;
};

//双流源列表
class Value_ListDualSrc : public IValue
{
public:  
    Value_ListDualSrc( TDualSrcInfo& tSrcInfo, String strClickItemFunc = IBaseItem::strDefaultFunc, BOOL bConfig = TRUE ) 
        :IValue( "ListDualSrc" ), m_tSrcInfo( tSrcInfo ), m_strClickItemFunc( strClickItemFunc ), m_bConfig( bConfig ){}
    
    TDualSrcInfo m_tSrcInfo; 
    String m_strClickItemFunc;		 // 条目点击回调函数 
    BOOL   m_bConfig;  //是否配置界面   
};

class Data_DualSrc : public IData
{
public:
    Data_DualSrc( TVgaInfo &tInfo ) : IData( "DualSrc" ), m_tVgaInfo( tInfo ){}
    IData* Clone()
    {
        Data_DualSrc* pData = new Data_DualSrc( m_tVgaInfo );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
    
    TVgaInfo m_tVgaInfo;
};

//网管配置列表
class Value_ListNetManage : public Value_ListBase
{
public:  
    Value_ListNetManage( ARRAY<TTPNMServerCfg>* pList, String strClickItemFunc = IBaseItem::strDefaultFunc ) 
		: m_pvctNetList( pList ), m_strClickItemFunc( strClickItemFunc ){}
    
    //TWebManageInfo m_tManaInfo;
	ARRAY<TTPNMServerCfg>* m_pvctNetList;
    String m_strClickItemFunc;		 // 条目点击回调函数 

	bool SetData( IItemList* pList );
};

class Data_NetManage : public IData
{
public:
    Data_NetManage( TTPNMServerCfg &tInfo ) : IData( "NetManage" ), m_tNetListInfo( tInfo ){}
    IData* Clone()
    {
        Data_NetManage* pData = new Data_NetManage( m_tNetListInfo );
        pData->SetDataKey( GetDataKey() );
        return pData;
    }
    
    TTPNMServerCfg m_tNetListInfo;
};

#endif // !defined(AFX_TOUCHLISTPROPERTY_H__04260821_1F80_4C85_A679_1B121DF07E09__INCLUDED_)
