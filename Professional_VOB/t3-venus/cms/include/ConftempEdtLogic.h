// ConftempEdtLogic.h: interface for the CConftempEdtLogic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONFTEMPEDTLOGIC_H__D2C43ED8_6D8A_4CCE_BF33_46B006780A91__INCLUDED_)
#define AFX_CONFTEMPEDTLOGIC_H__D2C43ED8_6D8A_4CCE_BF33_46B006780A91__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "wndLogicBase.h"

class CConftempEdtLogic : public CWndLogicBase  
{
public: 
    static CConftempEdtLogic* GetLogicPtr(); 
    CConftempEdtLogic();
    virtual ~CConftempEdtLogic(); 
    
public:  
    
    virtual bool RegCBFun();
    
    virtual bool UnRegFunc( );
    
    virtual bool InitWnd( const IArgs & arg );
    
     /**	 
	* 功能:  清空所有状态和数据
	* @return   
	* @remarks	 
	*/
    virtual void Clear() ;

   /**	 
  * 功能: 点击新建
  * @return  bool
  * @remarks 新建会议模板
  */
    bool OnBtnNewClick( const IArgs & arg  );



    /**	 
  * 功能: 点击编辑按钮
  * @return  bool
  * @remarks 开始编辑会议模板
  */
    bool OnBtnEdtClick( const IArgs & arg  );

 /**	 
  * 功能: 点击保存按钮
  * @return  bool
  * @remarks 保存会议模板
  */
    bool OnBtnSaveClick( const IArgs & arg  );

    /**	 
  * 功能: 点击取消按钮
  * @return  bool
  * @remarks 取消会议模板的修改
  */
    bool OnBtnCancleClick( const IArgs & arg  );


    /**	 
  * 功能: 点击了显示会议信息 
  * @return  bool
  * @remarks 取消会议模板的修改
  */
    bool OnBtnShowConfinfoClick( const IArgs & arg  );


    /**	 
  * 功能: 点击了显示轮询信息but
  * @return  bool
  * @remarks 取消会议模板的修改
  */
    bool OnBtnShowPollClick( const IArgs & arg  );

     /**	 
  * 功能: 点击显示地址簿按钮
  * @return  bool
  * @remarks  
  */
    bool OnBtnShowAddrClick( const IArgs & arg  );

     /**	 
  * 功能: 点击显示地址簿分组按钮
  * @return  bool
  * @remarks  
  */
     bool OnBtnShowAddrGrpClick( const IArgs & arg  );

       /**	 
  * 功能: 点击添加所有分会场到轮询列表
  * @return  bool
  * @remarks  
  */
     bool OnBtnAddAllCnsToPollClick( const IArgs & arg  );



          /**	 
  * 功能: 点清空轮询列表
  * @return  bool
  * @remarks  
  */
     bool OnBtnClearPollClick( const IArgs & arg  );



   /**	 
  * 功能: 分会场列表 拖拽结束
  * @return  bool
  * @remarks  
  */
   bool OnEndDragSecdryCns( const IArgs & arg  );

    /**	 
  * 功能: 向轮询列表 拖拽条目结束
  * @return  bool
  * @remarks  
  */
   bool OnEndDragPollLst( const IArgs & arg  ); 


   //从 轮询列表 拖拽条目结束
   bool  OnEndDragFrmPollLst( const IArgs & arg  );


//-------------点击列表中的条目-------------------------begin
    /**	 
  * 功能: 点击会议模板的列表的某个条目
  * @return  bool
  * @remarks 把会议模板信息更新到详细信息界面
  */
    bool OnTempItemClick( const IArgs & arg  );

    /**	 
  * 功能: 点击会议模板的列表 条目中的删除图标
  * @return  bool
  * @remarks 删除某个图标
  */
    bool OnTempLstDelIcon( const IArgs & arg  );

  

    /**	 
  * 功能: 删除分会场列表中的“删除图标” 
  * @return  bool
  * @remarks  删除所选分会场 
  */
    bool OnCnsLstDelIcon( const IArgs & arg  );
    
   
  /**	 
  * 功能: 点击了地址簿中的“添加图标”
  * @return  bool
  * @remarks  把地址簿中选择的条目添加到会场列表中,
  *          会场列表中的cnsID ，若有删除，则ID号会重新被刷新
  */
    bool OnAddrAddIcon( const IArgs & arg  );


 /**	 
  * 功能: 点击了地址簿分组中的“添加图标”
  * @return  bool
  * @remarks  把地址簿中分组中选择的分组添加到会场列表中
  */
    bool OnAddGrpAddIcon( const IArgs & arg  );  


    /**	 
  * 功能: 点击了cns的“添加图标”
  * @return  bool
  * @remarks  把cns列表中选择的cns添加到轮询列表中
  */
    bool OnCnsLstAddICon( const IArgs & arg  );  
 

 /**	 
  * 功能: 单击了轮询列表的条目 
  * @return  bool
  * @remarks   
  */
    bool OnPollItemClick(const IArgs &args );
//-------------点击列表中的条目-------------------------end
 
   /**	 
  * 功能: 删除所选会议模板
  * @return  bool
  * @remarks 删除 
  */
   bool DelSelConfTemp( const IArgs & arg  );

   bool BtnSaveToFileClick( const IArgs & arg );
   bool BtnSavePollMenueToFileClick( const IArgs & arg );
   
   bool CloseDlg( const IArgs & arg  );
   
   
   void UpdateTempInfoDlg(); 
   
   //更新会议模板信息界面的编辑框
   void UPdateTempInfoEdtWnd();

   //更新会议模板信息界面的列表
   void UPdateTempInfoLst();


   bool UnSelConfTemp( const IArgs & arg  );
   
protected: 
   /**	 
  * 功能: 刷新会议模板列表通知
  * @return  bool
  * @remarks  
  */
    afx_msg HRESULT OnRefreshConftempLstNotify( WPARAM wparam, LPARAM lparam);


    afx_msg HRESULT OnOperateTempRet( WPARAM wparam, LPARAM lparam);

    

  /**	 
  * 功能: 刷新地址簿通知
  * @return  bool
  * @remarks  
  */
    afx_msg HRESULT OnUpdateAddrBook( WPARAM wparam, LPARAM lparam);
    

    
protected: 
    virtual void RegMsg(); 
    virtual void UnRegMsg();
    

    //根据当前会议模板信息界面显示内容更新会议模板显示和隐藏的内容
    void UpDateShowInfo();
   
    //获取cns会场列表，该列表中不包括本地会场，和轮询cns
    TEpAddrList GetCnsLstExceptPoll();
    
    //更新地址簿列表
    void UpdateAddrList();
    
    //更新地址簿分组列表
    void UpdateAddrGrpList();
  
    //把地址簿条目或分组添加到会议模板的cns列表
    bool AddAddrToConfTempEpLst(TAddrItem* pAddrItem);

    //j检查本地cns是否已经添加到cn的列表中，如果没有，则添加进去，默认添加到列表的第一个成员,且为默认为主席 
    bool CheckLocalCnsInLst();


    void ShowConfinfo();

    void SetTempSubList();
private:

    //当前会议模板信息界面所显示信息
    enum EM_TempInfoDlgShow
    {
        emDlgShowConfInfo,  //显示会议信息界面
        emDlgShowPollInfo,  //显示轮询信息界面
    };

    static CConftempEdtLogic *m_pLogic;
    TCMSConfTemplate  m_tConfTempSel;                       //当前选中的条目
    BOOL32           m_bEdtState;                            //当前是否在编辑状态 
    EM_TempInfoDlgShow m_emShowInfo;                        //当前会议模板信息界面显示的内容

	vector<TAddrItem> m_vctAddrList;                        //地址簿条目列表
	vector<TAddrItem> m_vctGroupList;                       //地址簿组列表

    static const String  m_strDlgLst ;                      //包含列表的界面
    static const String  m_strLstTemp;                       //模板列表
    static const String  m_strLstCns;                        //cns列表
    static const String  m_strBtnCreateTemp;                 //btn  新建会议模板
    static const String  m_strBtnShwConfInfo;                //btn  显示会议信息
    static const String  m_strBtnShwPollInfo;               //btn  显示轮询信息
    static const String  m_strBtnEdit;                       //btn  编辑
    static const String  m_strBtnSave;                      //btn  保存
    static const String  m_strBtnCancle;                    //btn  取消
 
    static const String  m_strDlgInfo  ;                   //所有信息的父界面
    static const String  m_strDlgConfInfo;                  //Dlg 会议信息
    static const String  m_strEdtConfName;                  //会议名
    static const String  m_strEdtConfE164;                   //E164
    static const String  m_strEdtPrimaCnsName;              //主会场名
    static const String  m_strLstSecondaryCns ;              //cns分会场列表
    
    static const String  m_strDlgPollInfo;                   //Dlg 轮询信息
    static const String  m_strEdtPollIntv;                    //轮询间隔
    static const String  m_strLstPollCns;                    //cns 轮询列表

    //界面左侧窗口
    static const String  m_strLstAddr ;                     //地址簿
    static const String  m_strLstAddrGrp ;                  //地址簿分组
    static const String  m_strBtnShowAddrGrp ;                  //显示地址簿分组
    static const String  m_strBtnShowAddr;                      //显示地址簿
    
  
    static const String  m_strDlgPollManageMenu; 
    static const String  m_strLstPollManage ;
   
};

#endif // !defined(AFX_CONFTEMPEDTLOGIC_H__D2C43ED8_6D8A_4CCE_BF33_46B006780A91__INCLUDED_)
