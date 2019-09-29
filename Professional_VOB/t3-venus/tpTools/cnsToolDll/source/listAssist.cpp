// listAssist.cpp: implementation of the CListAssist class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cnsToolDll.h"
#include "listAssist.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// 
// CListAssist::CListAssist()
// {
// 	 m_strValTypeFuncMenu = "";//�����б�
// }
// 
// CListAssist::~CListAssist()
// {
// 
// }
bool Value_ItemMenu::SetData( IItemList* pList )
{ 	
	if ( pList == NULL || m_pMenuList == NULL )
	{
		return false;
	}
	
	IBaseItem* pBaseItem = pList->GetItemData();
	pBaseItem->SetLayoutAlgorithm(  m_strAlgroithm ); 
	pBaseItem->SetMoveStatus( m_bDrag );
	
	//	sort( m_pMenuList->begin(), m_pMenuList->end(), CompareListData ); //����
	
	Args_BuildItem args;
	args.pList = pList;
	args.bDrag = m_bDrag;
	args.strClickItemFunc = "";// m_strClickItemFunc;
	args.pVctSubItem =  NULL;// m_pVctSubItem;
	args.strImageItem = m_strImgItemType;
	args.strTxtItem = m_strTxtItemType;  
	
	s32 count =  m_pMenuList->size(); 
	for ( int j = 0; j < count; j++ )
	{ 
        args.strImageItem = m_pMenuList->at(j).szItemType;

		Data_ItemMenu UserData( *( &m_pMenuList->at(j) ) );  
		UserData.SetDataKey( j );
	   
		args.nKey = j;
		args.strTxt =m_pMenuList->at(j).szName;
		args.pUserData = &UserData;
		
		BuildItem( args );
	}
	return true;
}//end SetData()
		
   

bool Value_ItemTPad::SetData( IItemList* pList )
{
	if ( pList == NULL )
	{
		return false;
	}
	
	IBaseItem* pBaseItem = pList->GetItemData();
	pBaseItem->SetLayoutAlgorithm( IAlgorithm::strTPadIpList ); 
	pBaseItem->SetMoveStatus( false );
	
	s32 count =  m_ptTPadList->m_byTPadNum; 
	for ( int j = 0; j < count; j++ )
	{
		IBaseItem* pItem = CItemFactory::GetSingletonPtr()->CreateItem( "TextTpadIPItem" );
		if ( NULL == pItem )
		{			
			return false;
		}
		if ( CTextItem * pTextItem = dynamic_cast<CTextItem*>(pItem)  )
		{
			in_addr tAddr;
			tAddr.S_un.S_addr = m_ptTPadList->m_adwTPadIP[j];
			String strDualIp;
			strDualIp = inet_ntoa(tAddr);
			pTextItem->SetText( strDualIp );
		}
		
		IItemList *pNew = pList->AddItem( j, pItem, emGroup );  //��� һ����Ŀ  
		delete pItem;
		pItem = 0;
	}
	return true;
}


bool Value_ItemNetMng::SetData( IItemList* pList )
{
	if ( pList == NULL )
	{
		return false;
	}
	
	IBaseItem* pBaseItem = pList->GetItemData();
	pBaseItem->SetLayoutAlgorithm( /*IAlgorithm::strNetMngList*/IAlgorithm::strVert );
	pBaseItem->SetMoveStatus( false );
	
	int nListCount = m_pVecNMServerCfgLst->size(); 
	int nRow = 0;
	int nColSize = 5;
	
	for ( vector<TTPNMServerCfg>::iterator it = m_pVecNMServerCfgLst->begin(); it != m_pVecNMServerCfgLst->end(); it++ )
	{
		IBaseItem* pItem = CItemFactory::GetSingletonPtr()->CreateItem( "ImageItemNetMng" );
		
		TTPNMServerCfg tTPNMServerCfg;
		tTPNMServerCfg = *it;
		//tTPNMServerCfg.dwNMServerIP = ntohl(tTPNMServerCfg.dwNMServerIP);
		
		Data_NetMng dataNetMng(tTPNMServerCfg);
		dataNetMng.SetDataKey( nRow );
		
		pItem->SetFunc("CCfgNetMngLogic::OnClickNetMngLst");
		pItem->SetUserData( &dataNetMng );
		pItem->SetLayoutAlgorithm( /*IAlgorithm::strNetMngList*/ IAlgorithm::strHori );
		
		IItemList *pNew = pList->AddItem( nRow, pItem, emGroup );
		delete pItem;
		pItem = 0;
		
		
		for ( int i = 0; i < nColSize; i++ )
		{
			IBaseItem* pSubItem = CItemFactory::GetSingletonPtr()->CreateItem( "TextItemNetMng" );
			
			if ( NULL == pSubItem )
			{			
				return false;
			}
			
			if ( CTextItem * pTextItem = dynamic_cast<CTextItem*>(pSubItem)  )
			{
				
				String strItem;
				switch(i)
				{
				case 0:
					{
						in_addr tAddr;
						tAddr.S_un.S_addr = it->dwNMServerIP;
						strItem = inet_ntoa(tAddr);
						break;
					}
				case 1:
					{
						strItem = tTPNMServerCfg.achNMReadCommunity;
						break;
					}
				case 2:
					{
						strItem = tTPNMServerCfg.achNMWriteCommunity;
						break;
					}
				case 3:
					{
						char chTemp[10] = {0};
						_itot( tTPNMServerCfg.wNMGetSetPort, chTemp, 10 );
						strItem = chTemp;
						break;
					}
				case 4:
					{
						char chTemp[10] = {0};
						_itot( tTPNMServerCfg.WNMTrapPort, chTemp, 10 );
						strItem = chTemp;
						break;
					}
				default:
					break;
				}
				
				pTextItem->SetText( strItem );
				pNew->AddItem( i, pTextItem, emGroup );  //��� һ����Ŀ
			}
			
			delete pSubItem;
			pSubItem = 0;
		}
		nRow++;
	}
	return true;
}

bool Value_ItemLight::SetData( IItemList* pList )
{
	if ( pList == NULL )
	{
		return false;
	}
	
	IBaseItem* pBaseItem = pList->GetItemData();
	pBaseItem->SetLayoutAlgorithm( IAlgorithm::strTPadIpList ); 
	pBaseItem->SetMoveStatus( false );
	
	int z = 1;			//ͨ��j��z�Ĳ�ֵ����ȷ�ĵó������ƹ�����Ӧ��״̬
	s32 count =  16; 
	for ( int j = 0; j < count; j++ )
	{
		IBaseItem* pItem = CItemFactory::GetSingletonPtr()->CreateItem( "TextLightItem" );
		if ( NULL == pItem )
		{			
			return false;
		}
		if ( CTextItem * pTextItem = dynamic_cast<CTextItem*>(pItem)  )
		{
			String strState;
			if ( j%2 == 0 )
			{
				switch(j)
				{
				case 0:
					strState = "�ƹ�һ";
					break;
				case 2:
					strState = "�ƹ��";
					break;
				case 4:
					strState = "�ƹ���";
					break;
				case 6:
					strState = "�ƹ���";
					break;
				case 8:
					strState = "�ƹ���";
					break;
				case 10:
					strState = "�ƹ���";
					break;				
				case 12:
					strState = "�ƹ���";
					break;
				case 14:
					strState = "�ƹ��";
					break;
				default:
					break;
				}
			} 
			else
			{	
				if ( j == 3)
				{
					switch(m_ptSchCfg->emSchMidLight)
					{
					case emSchMidLightOn:
						strState = "��";
						break;
					case emSchMidLightOff:
						strState = "��";
						break;
					case emSchMidLightInvalid:
						strState = "��";
						break;
					default:
						break;
					}
				}
				else if ( j == 13)
				{
					switch(m_ptSchCfg->emSchScrLight)
					{
					case emSchScrLightOn:
						strState = "��";
						break;
					case emSchScrLightOff:
						strState = "��";
						break;
					case emSchScrLightInvalid:
						strState = "��";
						break;
					default:
						break;
					}
				}
				else if ( j != 3 && j != 13 )
				{
					switch(m_ptSchCfg->emSchLight)
					{
					case emSchLightOn:
						strState = "��";
						break;
					case emSchLightOff:
						strState = "��";
						break;
					case emSchLightInvalid:
						strState = "��";
						break;
					default:
						break;
					}
				}
				z++;
			}
			pTextItem->SetText( strState );
		}
		
		IItemList *pNew = pList->AddItem( j, pItem, emGroup );  //��� һ����Ŀ  
		delete pItem;
		pItem = 0;
	}
	return true;
}

bool Value_ItemCOMMON::SetData( IItemList* pList )
{
	if ( pList == NULL )
	{
		return false;
	}
	
	IBaseItem* pBaseItem = pList->GetItemData();
	pBaseItem->SetLayoutAlgorithm( IAlgorithm::strMultiColumn ); 
	pBaseItem->SetMoveStatus( false );

	TListRangeInfo tRangeInfo;
	tRangeInfo.nFirstLeft = 0;
	tRangeInfo.nFirstTop = 0;
	tRangeInfo.nMaxColumn = 2;
	tRangeInfo.nVertSpace = 16;

	Data_ListRangeInfo dataRangeInfo(tRangeInfo);
	pBaseItem->SetUserData( &dataRangeInfo );

	//������ɸѡ����ѡ�еĿ�ٯ��˷�ţ����ҽ���ٯ��˷�10������������һ��
	u32 count = 0;			//��ʾ����ĳ����ٯ��˷�ı��
	u32 bUse10 = 0;			//������������ĸ���Ŀ�ٯ��˷�10
	u32 bIsUse[10];			//������ž������ĸ���ٯ��˷类ѡ��
	for ( int i=0; i<3; i++ )
	{
		for ( int j=0; j<4; j++ )
		{
			if (TRUE == m_ptAudioDiagInfo->m_atPrimAudioInputPort[i].m_abAudioPort[j])
			{
				for ( count; count<10; )			
 				{
					if ( 0 == i )
					{
						bIsUse[count] = j;
					}
					if ( 1 == i )
					{
						bIsUse[count] = j+3;
					}
					if ( 2 == i )
					{
						bIsUse[count] = j+6;
					}
					if ( 3 == j && 0 == i )
					{
						bUse10 = 110;
						count -= 1;
					}
					if ( 3 == j && 1 == i )
					{
						bUse10 = 210;
						count -= 1;
					}
					if ( 3 == j && 2 == i )
					{
						bUse10 = 310;
						count -= 1;
					}
					count++;
					break;
				}
			}
		}
	}
	if ( bUse10 != 0 )
	{
		bIsUse[count] = bUse10;
		count += 1;
	}

	//�����Ƕ������У���ÿһ�е�������һ���ȡ�ģ����Բ������·�ʽ
	u32 b = 0;
	u32 CommonNum;			//��ٯ��˷�����
	
	for ( int a = 0; a < 2*count; a++ )
	{
		IBaseItem* pItem = CItemFactory::GetSingletonPtr()->CreateItem( "TextCOMMONItem" );
		if ( NULL == pItem )
		{			
			return false;
		}
		if ( CTextItem * pTextItem = dynamic_cast<CTextItem*>(pItem)  )
		{	
			if ( a == 2 )
			{
				b = 1;
			}
			if ( a == 2*b )
			{					
				CommonNum = bIsUse[b];
				if ( a != 0 )
				{
					b++;
				}				
			}
			if ( a%2 == 0 )
			{
				s8 chCOMMON[50] = {0};
				if ( 110 == CommonNum || 210 == CommonNum || 310 == CommonNum )
				{
					sprintf( chCOMMON, "��ٯ��˷�10��" );
				}
				else
				{
					sprintf( chCOMMON, "��ٯ��˷�%u��", CommonNum+1 );
				}			
				pTextItem->SetText( chCOMMON );
				pTextItem->SetFontColor(Color(15,79,81));
				pTextItem->SetAlignment(StringAlignmentNear);
			}					
			else
			{
				String strVoice = CommonToStr(CommonNum);
				if ( "δ��⵽�ź�" == strVoice )
				{
					pTextItem->SetFontColor(Color(224,34,34));
				}
				else
				{
					pTextItem->SetFontColor(Color(15,79,81));
				}
				pTextItem->SetText( strVoice );
				pTextItem->SetAlignment(StringAlignmentNear);
			}
		}
		IItemList *pNew = pList->AddItem( a, pItem, emGroup );  //��� һ����Ŀ  
		delete pItem;
		pItem = 0;
	}
	return true;
}

String Value_ItemCOMMON::CommonToStr( int u )
{
	s8 chCOMMON[8] = {0};	
	String strNoSignal = "255";
	String strAudio = "";//����	
	switch(u)
	{
	case 0:
		
		sprintf( chCOMMON, "%u", m_ptAudioDiagInfo->m_atPrimAudioInputPort[0].m_abyVolume[0] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "δ��⵽�ź�";
			break;
		}
		strAudio += chCOMMON; 
		break;
	case 1:
			
		sprintf( chCOMMON, "%u", m_ptAudioDiagInfo->m_atPrimAudioInputPort[0].m_abyVolume[1] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "δ��⵽�ź�";
			break;
		}
		strAudio += chCOMMON; 
		break;
	case 2:
	
		sprintf( chCOMMON, "%u", m_ptAudioDiagInfo->m_atPrimAudioInputPort[0].m_abyVolume[2] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "δ��⵽�ź�";
			break;
		}
		strAudio += chCOMMON;
		break;
	case 3:
		
		sprintf( chCOMMON, "%u", m_ptAudioDiagInfo->m_atPrimAudioInputPort[1].m_abyVolume[0] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "δ��⵽�ź�";
			break;
		}	
		strAudio += chCOMMON;
		break;
	case 4:
	
		sprintf( chCOMMON, "%u", m_ptAudioDiagInfo->m_atPrimAudioInputPort[1].m_abyVolume[1] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "δ��⵽�ź�";
			break;
		}
		strAudio += chCOMMON;
		break;
	case 5:
	
		sprintf( chCOMMON, "%u", m_ptAudioDiagInfo->m_atPrimAudioInputPort[1].m_abyVolume[2] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "δ��⵽�ź�";
			break;
		}
		strAudio += chCOMMON;
		break;
	case 6:
	
		sprintf( chCOMMON, "%u", m_ptAudioDiagInfo->m_atPrimAudioInputPort[2].m_abyVolume[0] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "δ��⵽�ź�";
			break;
		}
		strAudio += chCOMMON;
		break;
	case 7:
		
		sprintf( chCOMMON, "%u", m_ptAudioDiagInfo->m_atPrimAudioInputPort[2].m_abyVolume[1] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "δ��⵽�ź�";
			break;
		}
		strAudio += chCOMMON;
		break;
	case 8:
	
		sprintf( chCOMMON, "%u", m_ptAudioDiagInfo->m_atPrimAudioInputPort[2].m_abyVolume[2] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "δ��⵽�ź�";
			break;
		}
		strAudio += chCOMMON;
		break;
	case 110:		//���������Ե�һ���е�10
 			
 		sprintf( chCOMMON, "%u", m_ptAudioDiagInfo->m_atPrimAudioInputPort[0].m_abyVolume[3] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "δ��⵽�ź�";
			break;
		}
		strAudio += chCOMMON;
		break;
	case 210:		//���������Եڶ����е�10
		
		sprintf( chCOMMON, "%u", m_ptAudioDiagInfo->m_atPrimAudioInputPort[1].m_abyVolume[3] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "δ��⵽�ź�";
			break;
		}
		strAudio += chCOMMON; 
		break;
	case 310:		//���������Ե������е�10
		
		sprintf( chCOMMON, "%u", m_ptAudioDiagInfo->m_atPrimAudioInputPort[2].m_abyVolume[3] );
		if ( !StrCmp( chCOMMON, strNoSignal.c_str() ) )
		{
			strAudio = "δ��⵽�ź�";
			break;
		}	
		strAudio += chCOMMON;
		break;
	default:
		break;	
	}
	return strAudio;
}
