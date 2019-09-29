// cncaddrbook.cpp: implementation of the CCncAddrbook class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cncaddrbook.h"
#include "cncmsgrecver.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CCncAddrbook::CCncAddrbook( CCnsSession &cSession )
			: CCncAddrbookIF(), m_cAddrBook(MAX_ADDRENTRY, MAX_ADDRGROUP)
{
	m_pSession = &cSession;

	
	// ������ַ��app
    u16 wRet = InitializeAddrOsp();
    ASSERT(wRet == NO_ERROR);
	RegHandler(this);

	g_AddrBookApp.SetNotifyWindow( GetOspRecvWindow() );

	BuildEventsMap();

	m_bAddrLoading = FALSE;
}

CCncAddrbook::~CCncAddrbook()
{
	// ��OSP֪ͨĿ�Ĵ���Ϊ��
    g_AddrBookApp.SetNotifyWindow(NULL);
    g_AddrBookApp.SetNodeId(INVALID_NODE);
    g_AddrBookApp.ClearOspMsg();
}



//�ַ���Ϣ
void CCncAddrbook::DispEvent(const CMessage &cMsg)
{
    DISP_FUN(CCncAddrbook, cMsg);
}

inline void CCncAddrbook::OnTimeOut(u16 wEvent)
{
    //PostEvent(MTC_UI_CMD_TIMEOUT, wEvent);
}

u16 CCncAddrbook::PostCmdToAddr(u16 wEvent, const CAddrBookMsg &cMsg,
							 CKdvDispEvent *pDispEvent,u16 *pwEventTab,
							 s32 nEventNum, u32 dwTimeOut)
{
    CAddrBookMsg msgNew = cMsg;
	
    CMessage *pMsg = GetCMsgPtr();
    pMsg->event = wEvent;
    pMsg->length = sizeof(CAddrBookMsg);
    pMsg->content = reinterpret_cast<u8*>(&msgNew);
    pMsg->dstid = MAKEIID(AID_ADDRBOOK, 1);
	return PostCommand(pDispEvent, pwEventTab, nEventNum, TYPE_CMESSAGE, dwTimeOut);
}

u16 CCncAddrbook::PostCmdToAddr(u16 wEvent, const CAddrBookMsg &cMsg)
{
	CAddrBookMsg msgNew = cMsg;
	
	CMessage *pMsg = GetCMsgPtr();
    pMsg->event = wEvent;
    pMsg->length = sizeof(CAddrBookMsg);
    pMsg->content = reinterpret_cast<u8*>(&msgNew);
    pMsg->dstid = MAKEIID(AID_ADDRBOOK, 1);
	return PostMsg();
}


inline CAddrBook& CCncAddrbook::GetAddrBook()
{
    return m_cAddrBook;
}


u16 CCncAddrbook::RegAddrBook()
{
    u16 awWaitEvent[2];
    awWaitEvent[0] = ADDRBOOK_REGISTER_ACK;
    awWaitEvent[1] = ADDRBOOK_REGISTER_NACK;
    CAddrBookMsg cAddrMsg;
    u16 wRet = PostCmdToAddr(ADDRBOOK_REGISTER_REQ, cAddrMsg, this, awWaitEvent, 2);

    PrtMsg( ADDRBOOK_REGISTER_REQ, emEventTypeCnsSend, "" );
    return wRet;
}

u16 CCncAddrbook::UnRegAddrBook()
{
    m_cAddrBook.ClearAddrBook();
    u16 awWaitEvent[2];
    awWaitEvent[0] = ADDRBOOK_SAVE_ACK;
    awWaitEvent[1] = ADDRBOOK_SAVE_NACK;
    CAddrBookMsg cAddrMsg;	
	u16 wRet =  PostCmdToAddr(ADDRBOOK_UNREG_CMD, cAddrMsg, this, awWaitEvent, 2);

	PrtMsg( ADDRBOOK_UNREG_CMD, emEventTypeCnsSend, "" );
	PostEvent(UI_CNS_ADDRBOOK_CHANGED);
    return wRet;
}


u16 CCncAddrbook::AddEntry(const CAddrEntry& entry)
{	
	u16 awWaitEvent[2];
    awWaitEvent[0] = ADDRBOOK_ADD_ENTRY_ACK;
    awWaitEvent[1] = ADDRBOOK_ADD_ENTRY_NACK;
	
    CAddrEntry entry2 = entry;
    TADDRENTRY tentry;
    ZeroMemory(&tentry, sizeof(TADDRENTRY));
    tentry.SetEntryIndex(entry2.GetEntryIndex());
    TADDRENTRYINFO info;
    ZeroMemory(&info, sizeof(TADDRENTRYINFO));
    entry2.GetEntryInfo(&info);
    tentry.SetEntryInfo(&info);
	
	BOOL32 bExist = m_cAddrBook.IsAddrEntryExist(info) == INVALID_INDEX ? FALSE : TRUE; 
	if (bExist)
	{
		return NO_ERROR;
	}	
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetMsgBody((u8*)(&tentry), sizeof(TADDRENTRY));
	
    u16 wRet = PostCmdToAddr(ADDRBOOK_ADD_ENTRY_REQ, cAddrMsg);

	PrtMsg( ADDRBOOK_ADD_ENTRY_REQ, emEventTypeCnsSend, "��ӵ�ַ��Ŀ Name: %s, E164: %s", info.achEntryName, info.achMtNumber );
	NotifyCns();
	return wRet;
}

u16 CCncAddrbook::ModifyEntry(const CAddrEntry& entry)
{
    u16 awWaitEvent[2];
    awWaitEvent[0] = ADDRBOOK_MODIFYENTRY_ACK;
    awWaitEvent[1] = ADDRBOOK_MODIFYENTRY_NACK;
    
    CAddrEntry entry2 = entry;
    TADDRENTRY tentry;
    ZeroMemory(&tentry, sizeof(TADDRENTRY));
    tentry.SetEntryIndex(entry2.GetEntryIndex());
    TADDRENTRYINFO info;
    ZeroMemory(&info, sizeof(TADDRENTRYINFO));
    entry2.GetEntryInfo(&info);
    tentry.SetEntryInfo(&info);
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetMsgBody((u8*)(&tentry), sizeof(TADDRENTRY));
   
	u16 wRet = PostCmdToAddr(ADDRBOOK_MODIFYENTRY_REQ, cAddrMsg, this, awWaitEvent, 2);

	PrtMsg( ADDRBOOK_MODIFYENTRY_REQ, emEventTypeCnsSend, "�޸ĵ�ַ��Ŀ Name: %s, E164: %s", info.achEntryName, info.achMtNumber );
	NotifyCns();
    return wRet;
}

u16 CCncAddrbook::DeleteEntry(u32 dwIndex)
{
    u16 awWaitEvent[2];
	awWaitEvent[0] = ADDRBOOK_DEL_ENTRY_ACK;
	awWaitEvent[1] = ADDRBOOK_DEL_ENTRY_NACK;
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetEntryIndex(dwIndex);
    
	u16 wRet = PostCmdToAddr(ADDRBOOK_DEL_ENTRY_REQ, cAddrMsg);
	PrtMsg( ADDRBOOK_DEL_ENTRY_REQ, emEventTypeCnsSend, "ɾ����ַ��Ŀ: %d", dwIndex );
	NotifyCns();
    return wRet;
}


u16 CCncAddrbook::DeleteMultiEntry( vector<u32> vctEntry )
{
	CAddrBookMsg cAddrMsg;
	cAddrMsg.SetEntryIndex( MULTI_ENTRY );

    int nSize = vctEntry.size();
    if ( nSize > MAX_DELENTRY_NUM )
    {
        return ERR_CNC_ARRAY_OVERBOUNDS;
    }

    u32 adwEntry[MAX_DELENTRY_NUM] = {0};
    for ( int i = 0; i < nSize; i++ )
    {
        adwEntry[i] = htonl( vctEntry.at(i) );
    }

    cAddrMsg.SetMsgBody( (u8*)adwEntry, sizeof(u32)*nSize );

	u16 wRet = PostCmdToAddr( ADDRBOOK_DEL_ENTRY_REQ, cAddrMsg );
	PrtMsg( ADDRBOOK_DEL_ENTRY_REQ, emEventTypeCnsSend, "ɾ����ַ��Ŀ %d��", nSize );
	NotifyCns();
	return wRet;
}


u16 CCncAddrbook::AddGroup(const CAddrMultiSetEntry& group)
{
    u16 awWaitEvent[2];
    awWaitEvent[0] = ADDRBOOK_ADD_MULSETENTRY_ACK;
    awWaitEvent[1] = ADDRBOOK_ADD_MULSETENTRY_NACK;
    
    TADDRMULTISETENTRY tgroup;
    ZeroMemory(&tgroup, sizeof(TADDRMULTISETENTRY));
    tgroup.SetEntryIndex(group.GetGroupIndex());//��Ŀ����
    TMULTISETENTRYINFO info;
    ZeroMemory(&info, sizeof(TMULTISETENTRYINFO));
    CAddrMultiSetEntry group2 = group;
    group2.GetGroupInfo(&info);
    tgroup.SetEntryInfo(&info);//��������Ϣ
    tgroup.SetListEntryNum(group2.GetEntryCount());
    tgroup.SetListEntryIndex(group2.GetEntryTable(), group2.GetEntryCount());//�������б�
    
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetMsgBody((u8*)(&tgroup), sizeof(TADDRMULTISETENTRY));

	u16 wRet = PostCmdToAddr(ADDRBOOK_ADD_MULSETENTRY_REQ, cAddrMsg, this, awWaitEvent, 2);
	PrtMsg( ADDRBOOK_ADD_MULSETENTRY_REQ, emEventTypeCnsSend, "��ӵ�ַ��: %s", info.achGroupName );
	NotifyCns();
    return wRet;
}


u16 CCncAddrbook::ModifyGroup(const CAddrMultiSetEntry& group)
{
    u16 awWaitEvent[2];
    awWaitEvent[0] = ADDRBOOK_MODIFYMULSETENTRY_ACK;
    awWaitEvent[1] = ADDRBOOK_MODIFYMULSETENTRY_NACK;
    
    TADDRMULTISETENTRY tgroup;
    ZeroMemory(&tgroup, sizeof(TADDRMULTISETENTRY));
    tgroup.SetEntryIndex(group.GetGroupIndex());
    TMULTISETENTRYINFO info;
    ZeroMemory(&info, sizeof(TMULTISETENTRYINFO));
    CAddrMultiSetEntry group2 = group;
    group2.GetGroupInfo(&info);
    tgroup.SetEntryInfo(&info);
    tgroup.SetListEntryNum(group2.GetEntryCount());
    tgroup.SetListEntryIndex(group2.GetEntryTable(), group2.GetEntryCount());
    
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetMsgBody((u8*)(&tgroup), sizeof(TADDRMULTISETENTRY));

	u16 wRet = PostCmdToAddr(ADDRBOOK_MODIFYMULSETENTRY_REQ, cAddrMsg, this, awWaitEvent, 2);
	PrtMsg( ADDRBOOK_MODIFYMULSETENTRY_REQ, emEventTypeCnsSend, "�޸ĵ�ַ��: %s", info.achGroupName );
	NotifyCns();
    return wRet;
}

u16 CCncAddrbook::DeleteGroup(u32 dwIndex)
{
    u16 awWaitEvent[2];
    awWaitEvent[0] = ADDRBOOK_DEL_MULSETENTRY_ACK;
    awWaitEvent[1] = ADDRBOOK_DEL_MULSETENTRY_NACK;
	
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetEntryIndex(dwIndex);
 
	u16 wRet = PostCmdToAddr(ADDRBOOK_DEL_MULSETENTRY_REQ, cAddrMsg );
	//u16 wRet = PostCmdToAddr(ADDRBOOK_DEL_MULSETENTRY_REQ, cAddrMsg, this, awWaitEvent, 2);
	PrtMsg( ADDRBOOK_DEL_MULSETENTRY_REQ, emEventTypeCnsSend, "ɾ����ַ��: %d", dwIndex );
	NotifyCns();
    return wRet;
}

u16 CCncAddrbook::DeleteMultiGroup( vector<u32> vctGroup )
{
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetEntryIndex( MULTI_ENTRY );

    int nSize = vctGroup.size();
    if ( nSize > MAX_ADDRGROUP )
    {
        return ERR_CNC_ARRAY_OVERBOUNDS;
    }
    
    u32 adwGroup[MAX_ADDRGROUP] = {0};
    for ( int i = 0; i < nSize; i++ )
    {
        adwGroup[i] = htonl( vctGroup.at(i) );
    }
    
    cAddrMsg.SetMsgBody( (u8*)adwGroup, sizeof(u32)*nSize );

    u16 wRet = PostCmdToAddr(ADDRBOOK_DEL_MULSETENTRY_REQ, cAddrMsg );

    PrtMsg( ADDRBOOK_DEL_MULSETENTRY_REQ, emEventTypeCnsSend, "ɾ����ַ�� %d��", nSize );
	NotifyCns();
    return wRet;
}


u16 CCncAddrbook::AddEntryToGroup(const TADDRMULTISETENTRY& tGroupEntry)
{
    TADDRMULTISETENTRY tMultiEntry = tGroupEntry;
    u16 awWaitEvent[2];
    awWaitEvent[0] = ADDRBOOK_ADD_ENTRYTOMULSET_ACK;
    awWaitEvent[1] = ADDRBOOK_ADD_ENTRYTOMULSET_NACK;
	
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetMsgBody((u8*)(&tMultiEntry), sizeof(TADDRMULTISETENTRY));
   
	u16 wRet = PostCmdToAddr(ADDRBOOK_ADD_ENTRYTOMULSET_REQ, cAddrMsg);
	PrtMsg( ADDRBOOK_ADD_ENTRYTOMULSET_REQ, emEventTypeCnsSend, "��ӵ�ַ��Ŀ����" );
	NotifyCns();
    return wRet;
}


u16 CCncAddrbook::DelEntryFromGroup(const TADDRMULTISETENTRY& tGroupEntry)
{
    TADDRMULTISETENTRY tMultiEntry = tGroupEntry;
       
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetMsgBody((u8*)(&tMultiEntry), sizeof(TADDRMULTISETENTRY));
    
    u16 wRet = PostCmdToAddr(ADDRBOOK_DEL_ENTRYFRMULSET_REQ, cAddrMsg);
   	PrtMsg( ADDRBOOK_DEL_ENTRYFRMULSET_REQ, emEventTypeCnsSend, "������ɾ����ַ��Ŀ" );
	NotifyCns();
	return wRet;
}

u16 CCncAddrbook::AddGroupToGroup( u32 dwGroupIndex, u32 dwUpGroupIndex )
{
	u16 awWaitEvent[2];
    awWaitEvent[0] = ADDRBOOK_ADD_MULSETTOMULSET_ACK;
    awWaitEvent[1] = ADDRBOOK_ADD_MULSETTOMULSET_NACK;
	
	u32 adwGroup[2];
	adwGroup[0] = htonl(dwGroupIndex);
	adwGroup[1] = htonl(dwUpGroupIndex);

    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetMsgBody( (u8*)adwGroup, sizeof(adwGroup) );
	
	u16 wRet = PostCmdToAddr( ADDRBOOK_ADD_MULSETTOMULSET_REQ, cAddrMsg );
	//u16 wRet = PostCmdToAddr(ADDRBOOK_ADD_MULSETTOMULSET_REQ, cAddrMsg, this, awWaitEvent, 2);
	PrtMsg( ADDRBOOK_ADD_MULSETTOMULSET_REQ, emEventTypeCnsSend, "��ӵ�ַ���ϵ: %d���ϼ�Ϊ%d", dwGroupIndex, dwUpGroupIndex );
	NotifyCns();
	return wRet;
}

u16 CCncAddrbook::DelGroupFromGroup( u32 dwGroupIndex, u32 dwUpGroupIndex )
{
	u16 awWaitEvent[2];
    awWaitEvent[0] = ADDRBOOK_DEL_MULSETFROMMULSET_ACK;
    awWaitEvent[1] = ADDRBOOK_DEL_MULSETFROMMULSET_NACK;
	
	u32 adwGroup[2];
	adwGroup[0] = htonl(dwGroupIndex);
	adwGroup[1] = htonl(dwUpGroupIndex);
	
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetMsgBody( (u8*)adwGroup, sizeof(adwGroup) );
	
	u16 wRet = PostCmdToAddr( ADDRBOOK_DEL_MULSETFROMMULSET_REQ, cAddrMsg );
	//u16 wRet = PostCmdToAddr(ADDRBOOK_DEL_MULSETFROMMULSET_REQ, cAddrMsg, this, awWaitEvent, 2);
	PrtMsg( ADDRBOOK_DEL_MULSETFROMMULSET_REQ, emEventTypeCnsSend, "ɾ����ַ���ϵ: %d���ϼ�Ϊ%d", dwGroupIndex, dwUpGroupIndex );
	NotifyCns();
	return wRet;
}


void CCncAddrbook::BuildEventsMap()
{	
	REG_PFUN(ADDRBOOK_REGISTER_ACK, OnRegister);
	REG_PFUN(ADDRBOOK_REGISTER_NACK, OnNack);
	REG_PFUN(ADDRBOOK_UNREG_ACK, OnAck);

	REG_PFUN(ADDRBOOK_GETENTRYNUM_ACK, OnGetEntryNum);
	REG_PFUN(ADDRBOOK_GETENTRYNUM_NACK, OnNack);
	REG_PFUN(ADDRBOOK_GETENTRY_ACK, OnGetEntry);
	REG_PFUN(ADDRBOOK_GETENTRY_NACK, OnNack);

    REG_PFUN(ADDRBOOK_GETMULSETENTRYNUM_ACK, OnGetMulsetEntryNum);
	REG_PFUN(ADDRBOOK_GETMULSETENTRYNUM_NACK, OnNack);
    REG_PFUN(ADDRBOOK_GETMULSETENTRY_ACK, OnGetMulsetEntry);
	REG_PFUN(ADDRBOOK_GETMULSETENTRY_NACK, OnNack);

	REG_PFUN(ADDRBOOK_GETMULSETRELATIONNUM_ACK, OnGetMulsetRelationNum);
	REG_PFUN(ADDRBOOK_GETMULSETRELATIONNUM_NACK, OnNack);         
    REG_PFUN(ADDRBOOK_GETMULSETRELATION_ACK, OnGetMulsetRelation);
	REG_PFUN(ADDRBOOK_GETMULSETRELATION_NACK, OnNack);

	REG_PFUN(ADDRBOOK_REFRESHENTRY_NOTIF, OnRefresh);
	REG_PFUN(ADDRBOOK_DELENTRY_NOTIF, OnDelete);
	REG_PFUN(ADDRBOOK_REFRESHMULSETENTRY_NOTIF, OnRefreshGroup);
    REG_PFUN(ADDRBOOK_DELMULSETENTRY_NOTIF, OnDeleteGroup);
	REG_PFUN(ADDRBOOK_REFRESHMULSETRELATION_NOTIF, OnRefreshRelation);

	REG_PFUN(ADDRBOOK_ADD_ENTRY_ACK, OnAck);
	REG_PFUN(ADDRBOOK_ADD_ENTRY_NACK, OnNack);
	REG_PFUN(ADDRBOOK_MODIFYENTRY_ACK, OnAck);
    REG_PFUN(ADDRBOOK_MODIFYENTRY_NACK, OnNack);
	REG_PFUN(ADDRBOOK_DEL_ENTRY_ACK, OnAck);
	REG_PFUN(ADDRBOOK_DEL_ENTRY_NACK, OnNack);

	REG_PFUN(ADDRBOOK_ADD_MULSETENTRY_ACK, OnAck);
    REG_PFUN(ADDRBOOK_ADD_MULSETENTRY_NACK, OnNack);
	REG_PFUN(ADDRBOOK_MODIFYMULSETENTRY_ACK, OnAck);
    REG_PFUN(ADDRBOOK_MODIFYMULSETENTRY_NACK, OnNack);
	REG_PFUN(ADDRBOOK_DEL_MULSETENTRY_ACK, OnAck);
    REG_PFUN(ADDRBOOK_DEL_MULSETENTRY_NACK, OnNack);

	REG_PFUN(ADDRBOOK_ADD_ENTRYTOMULSET_ACK, OnAck);
	REG_PFUN(ADDRBOOK_ADD_ENTRYTOMULSET_NACK, OnNack);
	REG_PFUN(ADDRBOOK_DEL_ENTRYFRMULSET_ACK, OnAck);
	REG_PFUN(ADDRBOOK_DEL_ENTRYFRMULSET_NACK, OnNack);
	REG_PFUN(ADDRBOOK_ADD_MULSETTOMULSET_ACK, OnAck);
	REG_PFUN(ADDRBOOK_ADD_MULSETTOMULSET_NACK, OnNack);
	REG_PFUN(ADDRBOOK_DEL_MULSETFROMMULSET_ACK, OnAck);
	REG_PFUN(ADDRBOOK_DEL_MULSETFROMMULSET_NACK, OnNack);
}


void CCncAddrbook::OnRegister(const CMessage &cMsg)
{
	PrtMsg( ADDRBOOK_REGISTER_ACK, emEventTypeCnsRecv, "ע���ַ���ɹ�" );
	
    m_cAddrBook.ClearAddrBook();    //���ԭ���ĵ�ַ����Ŀ
	
	u16 awWaitEvent[2];	
	awWaitEvent[0] = ADDRBOOK_GETENTRYNUM_ACK;
    awWaitEvent[1] = ADDRBOOK_GETENTRYNUM_NACK;
    CAddrBookMsg cAddrMsg;
    BOOL32 bRet = PostCmdToAddr(ADDRBOOK_GETENTRYNUM_REQ, cAddrMsg, this, awWaitEvent, 2);

	PrtMsg( ADDRBOOK_GETENTRYNUM_REQ, emEventTypeCnsSend, "��ʼ���ص�ַ����Ŀ" );
	return;
}


void CCncAddrbook::OnGetEntryNum(const CMessage &cMsg)
{
	CAddrBookMsg cAddrMsg;
    cAddrMsg.SetAddrBookMsg(cMsg.content, cMsg.length);
    u32 dwNum = cAddrMsg.GetEntryNum();

	PrtMsg( ADDRBOOK_GETENTRYNUM_ACK, emEventTypeCnsRecv, "��ַ����Ŀ: ��%u��", dwNum );
  
    LoadEntries( INVALID_INDEX, dwNum );
}


//���ص�ַ����Ŀ
void CCncAddrbook::LoadEntries(u32 dwIndex, u32 dwNum)
{
    static u32 s_dwCount = 0;
    static u32 s_dwLoaded = 0;
    //����ַ����Ŀ������ʱ,dwIndex == INVALID_INDEX,��ʱ����s_dwCount������
    if(dwIndex == INVALID_INDEX)
    {
        s_dwCount = dwNum;
        s_dwLoaded = 0;
    }
    else
    {
        s_dwLoaded += dwNum;
    }
    
    s32 dwLeft = s_dwCount - s_dwLoaded;
	
    if(dwLeft > 0)	// һ��ֻ����MAX_GETENTRY_NUM��
    {
        u16 awWaitEvent[2];
        awWaitEvent[0] = ADDRBOOK_GETENTRY_ACK;
        awWaitEvent[1] = ADDRBOOK_GETENTRY_NACK;
		
        CAddrBookMsg cAddrMsg;
        cAddrMsg.SetEntryIndex(dwIndex);
        cAddrMsg.SetEntryNum(dwLeft < MAX_GETENTRY_NUM ? dwLeft : MAX_GETENTRY_NUM);
        //PostCmdToAddr(ADDRBOOK_GETENTRY_REQ, cAddrMsg, this, awWaitEvent, 2);

		PostCmdToAddr( ADDRBOOK_GETENTRY_REQ, cAddrMsg );

		//PrtMsg( ADDRBOOK_GETENTRY_REQ, emEventTypeCnsSend, "��ַ������: ����������%d, ��Ŀ%d",
		//												dwIndex, dwLeft < MAX_GETENTRY_NUM? dwLeft : MAX_GETENTRY_NUM );

		//ÿ����1000��ˢ��һ�ν���
		if ( s_dwLoaded > 0 && ( s_dwLoaded % 1000 == 0 ) )
		{
			PrtMsg( "\n\tˢ�µ�ַ�� �� %d \n", s_dwLoaded );
			PostEvent(UI_CNS_ADDRBOOK_CHANGED);
		}
    }
    else
    {
        u16 awWaitEvent[2];
		awWaitEvent[0] = ADDRBOOK_GETMULSETENTRYNUM_ACK;
		awWaitEvent[1] = ADDRBOOK_GETMULSETENTRYNUM_NACK;

		CAddrBookMsg cAddrMsg;
		PostCmdToAddr(ADDRBOOK_GETMULSETENTRYNUM_REQ, cAddrMsg, this, awWaitEvent, 2);

		PrtMsg( ADDRBOOK_GETMULSETENTRYNUM_REQ, emEventTypeCnsSend, "��ʼ���ص�ַ����" );
		//PostEvent(UI_CNS_ADDRBOOK_CHANGED, TRUE,-1);
    }
}


//��ַ��Ŀ������Ϣ
void CCncAddrbook::OnGetEntry(const CMessage& cMsg)
{
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetAddrBookMsg(cMsg.content, cMsg.length);
    TADDRENTRY *pEntry = (TADDRENTRY*)(cAddrMsg.GetMsgBody());
    //��ӱ��浽����
    for(s32 nIndex = 0; nIndex < cAddrMsg.GetEntryNum(); nIndex++)
    {
		u32 Index = pEntry[nIndex].GetEntryIndex();
        m_cAddrBook.AddAddrEntry( pEntry[nIndex].GetEntryInfo(), pEntry[nIndex].GetEntryIndex() );

		//PrtMsg( ADDRBOOK_GETENTRY_ACK, emEventTypeCnsRecv, "��ַ������: %s", pEntry[nIndex].GetEntryInfo().achEntryName );
    }

    LoadEntries(pEntry[cAddrMsg.GetEntryNum()-1].GetEntryIndex(), cAddrMsg.GetEntryNum());
}



void CCncAddrbook::OnGetMulsetEntryNum(const CMessage& cMsg)
{
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetAddrBookMsg(cMsg.content, cMsg.length);
    u32 dwNum = cAddrMsg.GetEntryNum();

	PrtMsg( ADDRBOOK_GETMULSETENTRYNUM_ACK, emEventTypeCnsRecv, "��ַ����: ��%u��", dwNum );

    LoadMulsetEntries( INVALID_INDEX, dwNum );
}

//���ص�ַ��
void CCncAddrbook::LoadMulsetEntries(u32 dwIndex, u32 dwNum)
{
    static u32 s_dwCount = 0;
	static u32 s_dwLoaded = 0;

    if(dwIndex == INVALID_INDEX)
    {
        s_dwCount = dwNum;
        s_dwLoaded = 0;
    }
    else
    {
        s_dwLoaded += dwNum;
    }
    u32 dwLeft = s_dwCount - s_dwLoaded;
    if(dwLeft > 0)	// һ��ֻ����MAX_GETGROUP_NUM��
    {
        u16 awWaitEvent[2];
        awWaitEvent[0] = ADDRBOOK_GETMULSETENTRY_ACK;
        awWaitEvent[1] = ADDRBOOK_GETMULSETENTRY_NACK;
        CAddrBookMsg cAddrMsg;
        cAddrMsg.SetEntryIndex(dwIndex);
        cAddrMsg.SetEntryNum(dwLeft < MAX_GETGROUP_NUM ? dwLeft : MAX_GETGROUP_NUM);

        PostCmdToAddr( ADDRBOOK_GETMULSETENTRY_REQ, cAddrMsg );

		PrtMsg( ADDRBOOK_GETMULSETENTRY_REQ, emEventTypeCnsSend, "��ַ�������: ����������%d, ��Ŀ%d",
														dwIndex, dwLeft < MAX_GETENTRY_NUM ? dwLeft : MAX_GETENTRY_NUM );
    }
	else
	{
		u16 awWaitEvent[2];
		awWaitEvent[0] = ADDRBOOK_GETMULSETRELATIONNUM_ACK;
		awWaitEvent[1] = ADDRBOOK_GETMULSETRELATIONNUM_NACK;
		
		CAddrBookMsg cAddrMsg;
		PostCmdToAddr(ADDRBOOK_GETMULSETRELATIONNUM_REQ, cAddrMsg, this, awWaitEvent, 2);
		
		PrtMsg( ADDRBOOK_GETMULSETRELATIONNUM_REQ, emEventTypeCnsSend, "��ʼ���ص�ַ�����ϵ" );

		//PostEvent(UI_CNS_ADDRBOOK_CHANGED);
	}
}


void CCncAddrbook::OnGetMulsetEntry(const CMessage& cMsg)
{
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetAddrBookMsg(cMsg.content, cMsg.length);
    TADDRMULTISETENTRY *pEntry = (TADDRMULTISETENTRY*)(cAddrMsg.GetMsgBody());
    for(s32 nIndex = 0; nIndex < cAddrMsg.GetEntryNum(); nIndex++)
    {
        //��ӻ�������Ϣ
        m_cAddrBook.AddAddrMultiSetEntry(pEntry[nIndex].GetEntryInfo(),
            pEntry[nIndex].GetEntryIndex());
        u32 dwNum = pEntry[nIndex].GetListEntryNum();
        u32 *pdwEntries = new u32[dwNum + 1];
		memset( pdwEntries, 0 , sizeof(int) * (dwNum + 1) );
        pEntry[nIndex].GetListEntryIndex(pdwEntries, dwNum);
        //��ӻ���������Ŀ
        for(s32 nEntryIdx=0; nEntryIdx < dwNum; nEntryIdx++)
        {
            m_cAddrBook.AddAddrEntry(pEntry[nIndex].GetEntryIndex(), pdwEntries[nEntryIdx]);
        }
        delete []pdwEntries;

		//PrtMsg( ADDRBOOK_GETMULSETENTRY_ACK, emEventTypeCnsRecv, "��ַ�������: %s", pEntry[nIndex].GetEntryInfo().achGroupName );
    }

    LoadMulsetEntries( pEntry[cAddrMsg.GetEntryNum()-1].GetEntryIndex(), cAddrMsg.GetEntryNum() );
}


//��ȡ�����ϵ����
void CCncAddrbook::OnGetMulsetRelationNum(const CMessage& cMsg)
{
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetAddrBookMsg(cMsg.content, cMsg.length);
    u32 dwNum = cAddrMsg.GetEntryNum();
	
	PrtMsg( ADDRBOOK_GETMULSETRELATIONNUM_ACK, emEventTypeCnsRecv, "��ַ�����ϵ: ��%u��", dwNum );
	
    LoadMulsetRelation( 0, dwNum );
}


//���ص�ַ���ϵ
void CCncAddrbook::LoadMulsetRelation(u32 dwIndex, u32 dwNum)
{
    static u32 s_dwCount = 0;
	static u32 s_dwLoaded = 0;
	
    if(dwIndex == 0)
    {
        s_dwCount = dwNum;
        s_dwLoaded = 0;
    }
    else
    {
        s_dwLoaded += dwNum;
    }
    u32 dwLeft = s_dwCount - s_dwLoaded;
    if(dwLeft > 0)	// һ��ֻ����MAX_GETGROUPRELATION_NUM��
    {
        u16 awWaitEvent[2];
        awWaitEvent[0] = ADDRBOOK_GETMULSETRELATION_ACK;
        awWaitEvent[1] = ADDRBOOK_GETMULSETRELATION_NACK;
        CAddrBookMsg cAddrMsg;
        cAddrMsg.SetEntryIndex(dwIndex);
        cAddrMsg.SetEntryNum(dwLeft < MAX_GETGROUPRELATION_NUM ? dwLeft : MAX_GETGROUPRELATION_NUM);
		
        PostCmdToAddr(ADDRBOOK_GETMULSETRELATION_REQ, cAddrMsg, this, awWaitEvent, 2);
    }
	else
	{		
		//�������
		PrtMsg( "\n\t��ַ���������\n" );
		PostEvent(UI_CNS_ADDRBOOK_CHANGED);
	}
}


//��ַ���ϵ����
void CCncAddrbook::OnGetMulsetRelation(const CMessage& cMsg)
{
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetAddrBookMsg(cMsg.content, cMsg.length);
    TMultiLevel* pLevel = (TMultiLevel*)(cAddrMsg.GetMsgBody());

    //��ӱ��浽����
    for(s32 nIndex = 0; nIndex < cAddrMsg.GetEntryNum(); nIndex++)
    {
		m_cAddrBook.AddGroupToGroup( pLevel[nIndex].GetGroupIndex(), pLevel[nIndex].GetUpGroupIndex() );
		
		//PrtMsg( ADDRBOOK_GETMULSETRELATION_ACK, emEventTypeCnsRecv, "��ַ�����ϵ����: %u���ϼ���%u", pLevel[nIndex].GetGroupIndex(), pLevel[nIndex].GetUpGroupIndex() );
    }
    LoadMulsetRelation( cAddrMsg.GetEntryIndex() + cAddrMsg.GetEntryNum(), cAddrMsg.GetEntryNum() );
}


void CCncAddrbook::OnRefresh(const CMessage& cMsg)
{	
	PrtMsg( ADDRBOOK_REFRESHENTRY_NOTIF, emEventTypeCnsRecv, "" );

    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetAddrBookMsg(cMsg.content, cMsg.length);
    TADDRENTRY &entry = *(TADDRENTRY*)cAddrMsg.GetMsgBody();
	
    if(cAddrMsg.GetEntryOptType() == ADD_ENTRY)
    {
        m_cAddrBook.AddAddrEntry(entry.GetEntryInfo(), entry.GetEntryIndex());
		PostEvent( UI_CNS_ADDRBOOK_ADDENTRY, entry.GetEntryIndex(), (LPARAM)entry.GetEntryInfo().achEntryName );
    }
    else
    {
        m_cAddrBook.ModifyAddrEntry(entry.GetEntryIndex(), entry.GetEntryInfo());

		PostEvent( UI_CNS_ADDRBOOK_MODIFY, TRUE, entry.GetEntryIndex() );
    }
    PostEvent(UI_CNS_ADDRBOOK_CHANGED, TRUE);
}

void CCncAddrbook::OnDelete(const CMessage& cMsg)
{
	PrtMsg( ADDRBOOK_DELENTRY_NOTIF, emEventTypeCnsRecv, "" );
	
    CAddrBookMsg cAddrMsg;
    cAddrMsg.SetAddrBookMsg(cMsg.content, cMsg.length);

    u32 dwEntryIndex = cAddrMsg.GetEntryIndex();
    if( dwEntryIndex != MULTI_ENTRY )
    {
        m_cAddrBook.DelAddrEntry( dwEntryIndex );
    }
    else
    {
        int nDelSize = cAddrMsg.GetMsgBodyLen() / sizeof(u32);
        u32 adwDelEntry[MAX_DELENTRY_NUM] = {0};
        memcpy( adwDelEntry, (u32*)cAddrMsg.GetMsgBody(), cAddrMsg.GetMsgBodyLen() );
        for ( int i = 0; i < nDelSize; i++ )
        {
            m_cAddrBook.DelAddrEntry( ntohl(adwDelEntry[i]) );
        }
    }
    
    PostEvent(UI_CNS_ADDRBOOK_CHANGED, TRUE);
}


void CCncAddrbook::OnRefreshGroup(const CMessage& cMsg)
{
	PrtMsg( ADDRBOOK_REFRESHMULSETENTRY_NOTIF, emEventTypeCnsRecv, "" );

	CAddrBookMsg cAddrMsg;
    cAddrMsg.SetAddrBookMsg(cMsg.content, cMsg.length);
    TADDRMULTISETENTRY &tGroupEntry = *(TADDRMULTISETENTRY*)cAddrMsg.GetMsgBody();
    if(cAddrMsg.GetEntryOptType() == ADD_ENTRY)
    {
        TADDRMULTISETENTRY addrtGroupEntry = tGroupEntry;
        m_cAddrBook.AddAddrMultiSetEntry( addrtGroupEntry.GetEntryInfo(), addrtGroupEntry.GetEntryIndex() );
        u32 dwNum = addrtGroupEntry.GetListEntryNum();
        u32 *pdwEntries = new u32[dwNum];
        addrtGroupEntry.GetListEntryIndex( pdwEntries, dwNum );
        for(u32 nIndex = 0; nIndex < dwNum; nIndex++)
        {
            m_cAddrBook.AddAddrEntry(addrtGroupEntry.GetEntryIndex(), pdwEntries[nIndex]);
        }
        delete []pdwEntries;
		PostEvent( UI_CNS_ADDRBOOK_ADDGROUP, addrtGroupEntry.GetEntryIndex(), (LPARAM)addrtGroupEntry.GetEntryInfo().achGroupName );
    }
    else
    {
        TADDRMULTISETENTRY addrtGroupEntry = tGroupEntry;
        u32 dwNum = addrtGroupEntry.GetListEntryNum();
        u32 *pdwEntries = new u32[dwNum];
        addrtGroupEntry.GetListEntryIndex(pdwEntries, dwNum);
        m_cAddrBook.ModifyAddrGroup(addrtGroupEntry.GetEntryIndex(), addrtGroupEntry.GetEntryInfo(),
            (u8)dwNum, pdwEntries);
        delete []pdwEntries;
		PostEvent( UI_CNS_ADDRBOOK_MODIFY, FALSE, addrtGroupEntry.GetEntryIndex() );
    }
    PostEvent( UI_CNS_ADDRBOOK_CHANGED, FALSE, tGroupEntry.GetEntryIndex() );
}

void CCncAddrbook::OnDeleteGroup(const CMessage& cMsg)
{
	PrtMsg( ADDRBOOK_DELMULSETENTRY_NOTIF, emEventTypeCnsRecv, "" );

	CAddrBookMsg cAddrMsg;
    cAddrMsg.SetAddrBookMsg(cMsg.content, cMsg.length);

    u32 dwGroupIndex = cAddrMsg.GetEntryIndex();
    if( dwGroupIndex != MULTI_ENTRY )
    {
        m_cAddrBook.DelAddrMultiSetEntry( dwGroupIndex );
    }
    else
    {
        int nDelSize = cAddrMsg.GetMsgBodyLen() / sizeof(u32);
        u32 adwDelEntry[MAX_DELENTRY_NUM] = {0};
        memcpy( adwDelEntry, (u32*)cAddrMsg.GetMsgBody(), cAddrMsg.GetMsgBodyLen() );
        for ( int i = 0; i < nDelSize; i++ )
        {
            m_cAddrBook.DelAddrMultiSetEntry( ntohl(adwDelEntry[i]) );
        }
    }

    PostEvent( UI_CNS_ADDRBOOK_CHANGED, TRUE );
}

void CCncAddrbook::OnRefreshRelation(const CMessage& cMsg)
{
	PrtMsg( ADDRBOOK_REFRESHMULSETRELATION_NOTIF, emEventTypeCnsRecv, "" );

	CAddrBookMsg cAddrMsg;
    cAddrMsg.SetAddrBookMsg(cMsg.content, cMsg.length);
	//������ת������
	u32 dwGroupIndex = *(u32*)cAddrMsg.GetMsgBody();
	dwGroupIndex = ntohl( dwGroupIndex );
	u32 dwUpGroupIndex = *(u32*)( cAddrMsg.GetMsgBody() + sizeof(u32) );
	dwUpGroupIndex = ntohl( dwUpGroupIndex );
	if ( cAddrMsg.GetEntryOptType() == ADD_ENTRY )
	{
		m_cAddrBook.AddGroupToGroup( dwGroupIndex, dwUpGroupIndex );
	}
	else
	{
		m_cAddrBook.DeleteGroupFromGroup( dwGroupIndex, dwUpGroupIndex );
	}
	PostEvent(UI_CNS_ADDRBOOK_CHANGED, TRUE);
}


void CCncAddrbook::OnAck(const CMessage& cMsg)
{
	CAddrBookMsg cAddrMsg;
	cAddrMsg.SetAddrBookMsg( cMsg.content, cMsg.length );
	u16 wCmd = 0;
	switch( cMsg.event ) 
	{
	case ADDRBOOK_REGISTER_ACK:			
		wCmd = ADDRBOOK_REGISTER_REQ;
		PrtMsg( ADDRBOOK_REGISTER_ACK, emEventTypeCnsRecv, "ע���ַ���ɹ�" );
		break;
	case ADDRBOOK_UNREG_ACK:
		wCmd = ADDRBOOK_UNREG_REQ;
		PrtMsg( ADDRBOOK_UNREG_ACK, emEventTypeCnsRecv, "ע����ַ���ɹ�" );
		break;
    case ADDRBOOK_SAVE_ACK:				
		wCmd = ADDRBOOK_UNREG_REQ;
		PrtMsg( ADDRBOOK_SAVE_ACK, emEventTypeCnsRecv, "��ַ������ɹ�" );
		break;
    case ADDRBOOK_ADD_ENTRY_ACK:			
		wCmd = ADDRBOOK_ADD_ENTRY_REQ;
		PrtMsg( ADDRBOOK_ADD_ENTRY_ACK, emEventTypeCnsRecv, "��ӵ�ַ��Ŀ�ɹ�" );
		break;
    case ADDRBOOK_MODIFYENTRY_ACK:			
		wCmd = ADDRBOOK_MODIFYENTRY_REQ;
		PrtMsg( ADDRBOOK_MODIFYENTRY_ACK, emEventTypeCnsRecv, "�޸ĵ�ַ��Ŀ�ɹ�" );
		break;
    case ADDRBOOK_DEL_ENTRY_ACK:			
		wCmd = ADDRBOOK_DEL_ENTRY_REQ;
		PrtMsg( ADDRBOOK_DEL_ENTRY_ACK, emEventTypeCnsRecv, "ɾ����ַ��Ŀ�ɹ�" );
		break;
    case ADDRBOOK_ADD_MULSETENTRY_ACK:		
		wCmd = ADDRBOOK_ADD_MULSETENTRY_REQ;
		PrtMsg( ADDRBOOK_ADD_MULSETENTRY_ACK, emEventTypeCnsRecv, "�����ɹ�" );
		break;
    case ADDRBOOK_MODIFYMULSETENTRY_ACK:	
		wCmd = ADDRBOOK_MODIFYMULSETENTRY_REQ;
		PrtMsg( ADDRBOOK_MODIFYMULSETENTRY_ACK, emEventTypeCnsRecv, "�޸���ɹ�" );
		break;
    case ADDRBOOK_DEL_MULSETENTRY_ACK:		
		wCmd = ADDRBOOK_DEL_MULSETENTRY_REQ;
		PrtMsg( ADDRBOOK_DEL_MULSETENTRY_ACK, emEventTypeCnsRecv, "ɾ����ɹ�" );
		break;
    case ADDRBOOK_ADD_ENTRYTOMULSET_ACK:
		wCmd = ADDRBOOK_ADD_ENTRYTOMULSET_REQ;
		PrtMsg( ADDRBOOK_ADD_ENTRYTOMULSET_ACK, emEventTypeCnsRecv, "��ӵ�ַ��Ŀ����ɹ�" );
		break;
    case ADDRBOOK_DEL_ENTRYFRMULSET_ACK:	
		wCmd = ADDRBOOK_DEL_ENTRYFRMULSET_REQ;
		PrtMsg( ADDRBOOK_DEL_ENTRYFRMULSET_ACK, emEventTypeCnsRecv, "������ɾ����ַ��Ŀ�ɹ�" );
		break;
	case ADDRBOOK_ADD_MULSETTOMULSET_ACK:
		PrtMsg( ADDRBOOK_ADD_MULSETTOMULSET_ACK, emEventTypeCnsRecv, "������ϵ�ɹ�" );
		break;
	case ADDRBOOK_DEL_MULSETFROMMULSET_ACK:
		PrtMsg( ADDRBOOK_DEL_MULSETFROMMULSET_ACK, emEventTypeCnsRecv, "ɾ�����ϵ�ɹ�" );
		break;
    default:
		wCmd = 0;
		break;
	}
//	PostEvent( MTC_UI_CMD_SUCCESS, wCmd );
}

void CCncAddrbook::OnNack(const CMessage& cMsg)
{
	CAddrBookMsg cAddrMsg;
	cAddrMsg.SetAddrBookMsg( cMsg.content, cMsg.length );
	u16 wCmd = 0;
	switch(cMsg.event)
    {
    case ADDRBOOK_REGISTER_NACK:			
		wCmd = ADDRBOOK_REGISTER_REQ;
		PrtMsg( ADDRBOOK_REGISTER_NACK, emEventTypeCnsRecv, "ע���ַ��ʧ��" );
		break;
	case ADDRBOOK_UNREG_NACK:
		wCmd = ADDRBOOK_UNREG_REQ;
		PrtMsg( ADDRBOOK_UNREG_NACK, emEventTypeCnsRecv, "ע����ַ��ʧ��" );
		break;
    case ADDRBOOK_SAVE_NACK:				
		wCmd = ADDRBOOK_UNREG_REQ;
		PrtMsg( ADDRBOOK_SAVE_NACK, emEventTypeCnsRecv, "��ַ������ʧ��" );
		break;
    case ADDRBOOK_ADD_ENTRY_NACK:			
		wCmd = ADDRBOOK_ADD_ENTRY_REQ;
		PrtMsg( ADDRBOOK_ADD_ENTRY_NACK, emEventTypeCnsRecv, "��ӵ�ַ��Ŀʧ��" );
		break;
    case ADDRBOOK_MODIFYENTRY_NACK:			
		wCmd = ADDRBOOK_MODIFYENTRY_REQ;
		PrtMsg( ADDRBOOK_MODIFYENTRY_NACK, emEventTypeCnsRecv, "�޸ĵ�ַ��Ŀʧ��" );
		break;
    case ADDRBOOK_DEL_ENTRY_NACK:		
		wCmd = ADDRBOOK_DEL_ENTRY_REQ;
		PrtMsg( ADDRBOOK_DEL_ENTRY_NACK, emEventTypeCnsRecv, "ɾ����ַ��Ŀʧ��" );
		break;
    case ADDRBOOK_ADD_MULSETENTRY_NACK:		
		wCmd = ADDRBOOK_ADD_MULSETENTRY_REQ;
		PrtMsg( ADDRBOOK_ADD_MULSETENTRY_NACK, emEventTypeCnsRecv, "�����ʧ��" );
		break;
    case ADDRBOOK_MODIFYMULSETENTRY_NACK:	
		wCmd = ADDRBOOK_MODIFYMULSETENTRY_REQ;
		PrtMsg( ADDRBOOK_MODIFYMULSETENTRY_NACK, emEventTypeCnsRecv, "�޸���ʧ��" );
		break;
    case ADDRBOOK_DEL_MULSETENTRY_NACK:	
		wCmd = ADDRBOOK_DEL_MULSETENTRY_REQ;
		PrtMsg( ADDRBOOK_DEL_MULSETENTRY_NACK, emEventTypeCnsRecv, "ɾ����ʧ��" );
		break;
    case ADDRBOOK_ADD_ENTRYTOMULSET_NACK:	
		wCmd = ADDRBOOK_ADD_ENTRYTOMULSET_REQ;
		PrtMsg( ADDRBOOK_ADD_ENTRYTOMULSET_NACK, emEventTypeCnsRecv, "��ӵ�ַ��Ŀ����ʧ��" );
		break;
    case ADDRBOOK_DEL_ENTRYFRMULSET_NACK:
		wCmd = ADDRBOOK_DEL_ENTRYFRMULSET_REQ;
		PrtMsg( ADDRBOOK_DEL_ENTRYFRMULSET_NACK, emEventTypeCnsRecv, "������ɾ����ַ��Ŀʧ��" );
		break;
    case ADDRBOOK_GETENTRYNUM_NACK:			
		wCmd = ADDRBOOK_GETENTRYNUM_REQ;
		PrtMsg( ADDRBOOK_GETENTRYNUM_NACK, emEventTypeCnsRecv, "��ȡ��ַ��Ŀ����ʧ��" );
		break;
    case ADDRBOOK_GETENTRY_NACK:		
		wCmd = ADDRBOOK_GETENTRY_REQ;
		PrtMsg( ADDRBOOK_GETENTRY_NACK, emEventTypeCnsRecv, "��ȡ��ַ��Ŀʧ��" );
		break;
    case ADDRBOOK_GETMULSETENTRYNUM_NACK:	
		wCmd = ADDRBOOK_GETMULSETENTRYNUM_REQ;
		PrtMsg( ADDRBOOK_GETMULSETENTRYNUM_NACK, emEventTypeCnsRecv, "��ȡ�����ʧ��" );
		break;
    case ADDRBOOK_GETMULSETENTRY_NACK:	
		wCmd = ADDRBOOK_GETMULSETENTRY_REQ;
		PrtMsg( ADDRBOOK_GETMULSETENTRY_NACK, emEventTypeCnsRecv, "��ȡ����Ϣʧ��" );
		break;
	case ADDRBOOK_GETMULSETRELATIONNUM_NACK:
		wCmd = ADDRBOOK_GETMULSETRELATIONNUM_REQ;
		PrtMsg( ADDRBOOK_GETMULSETRELATIONNUM_NACK, emEventTypeCnsRecv, "��ȡ���ϵ����ʧ��" );
		break;
	case ADDRBOOK_GETMULSETRELATION_NACK:
		wCmd = ADDRBOOK_GETMULSETRELATION_REQ;
		PrtMsg( ADDRBOOK_GETMULSETRELATION_NACK, emEventTypeCnsRecv, "��ȡ���ϵʧ��" );
		break;
	case ADDRBOOK_ADD_MULSETTOMULSET_NACK:
		PrtMsg( ADDRBOOK_ADD_MULSETTOMULSET_NACK, emEventTypeCnsRecv, "������ϵʧ��" );
		break;
	case ADDRBOOK_DEL_MULSETFROMMULSET_NACK:
		PrtMsg( ADDRBOOK_DEL_MULSETFROMMULSET_NACK, emEventTypeCnsRecv, "ɾ�����ϵʧ��" );
		break;
    default:
		wCmd = 0;
		break;
    }
    u32 dwError = ntohl(*(u32*)cAddrMsg.GetMsgBody());
	PostEvent( UI_CNS_ADDRBOOKOPT_FAILED, wCmd, dwError );
}


void CCncAddrbook::OnLinkBreak( u32 dwNodeId )
{
	ClearWaiting();	// OSP������,��δִ����������ж�ִ�� 
	ClearAllCommand(); // ��������ڶ����еȴ�ִ�е�����
    g_AddrBookApp.ClearOspMsg();  
    
    //��cns����������tpadδ����������NodeId�ÿ�
    if ( dwNodeId == g_AddrBookApp.GetNodeId() )
    {
        g_AddrBookApp.SetNodeId(INVALID_NODE);
    }

    m_cAddrBook.ClearAddrBook();
	m_bAddrLoading = FALSE;

    PrtMsg( "\n\t[CCncAddrbook::OnLinkBreak]��յ�ַ����Ϣ\n" );
}


u16 CCncAddrbook::InitializeAddrOsp()
{
	char szOspApp[] = "CncAddrbook";
	u32 dwPrior = 180; //���ȼ�����
	int nRet = g_AddrBookApp.CreateApp(&szOspApp[0], AID_CNCADDRBOOK_APP, dwPrior, 300, 1024);
	ASSERT(nRet == 0);

	PrtMsg( "AID_CNCADDRBOOK_APP �����ɹ�\n" );
    
    return NO_ERROR;
}

void CCncAddrbook::NotifyCns()
{
	CTpMsg *pcTpMsg = m_pSession->GetKdvMsgPtr();
    pcTpMsg->SetUserData( m_pSession->GetInst() );
    pcTpMsg->SetEvent( ev_cns_cncAddrBookNty ); 
    
    u16 wRet = m_pSession->PostMsg(TYPE_TPMSG);	

	if ( 0 == wRet )
	{
		PrtMsg( ev_cns_cncAddrBookNty, emEventTypeCnsSend , "֪ͨcns���¼������ʱ��\n" );
	} 
	else
	{
		PrtMsg( ev_cns_cncAddrBookNty, emEventTypeCnsSend , "֪ͨcns���¼������ʱ��ʧ�ܣ�\n" );
	}
}

BOOL CCncAddrbook::GetAddrLoadingState()
{
	return m_bAddrLoading;
}

void CCncAddrbook::SetAddrLoadingState(BOOL bAddrLoading)
{
	m_bAddrLoading = bAddrLoading;
}