// AddrList.cpp: implementation of the CAddrList class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AddrList.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

 
CTransparentAddrList::CTransparentAddrList( CString strName, CString strUI, CRect rcWnd, CWnd* pWnd, UINT nID, 
					 DWORD dwStyle, DWORD dwExStyle ) :
CTransparentList(strName, rcWnd, pWnd, strUI, nID, dwStyle, dwExStyle)
{
	
}

CTransparentAddrList::~CTransparentAddrList()
{
	
}

void CTransparentAddrList::Clicked( UINT nFlags, CPoint point )
{
	if ( m_pSelItem == 0 )
	{
		return;
	}
	IBaseItem* pBaseItem = m_pSelItem->GetItemData();
	if ( pBaseItem == 0 )
	{
		return;
	}
	
	bool bFind = false;
	String strFunc = pBaseItem->GetFunc();
	IItemList* pList = m_pSelItem;
	while( pList != 0 && pList->GetParentItem() != 0 )
	{		
		pBaseItem = pList->GetItemData();
		strFunc = pBaseItem->GetFunc();
		if ( strFunc != IBaseItem::strDefaultFunc )
		{
			bFind = true;
			break;
		}
		pList = pList->GetParentItem();
	}
	if ( bFind == true )
	{
		CRect rcFrame = GetFrameInScreen( pList );
		Args_ClickItemInfo clickInfo( this, pList, rcFrame );
		
		CFuncManage::GetSingletonPtr()->ExeFunc( strFunc, clickInfo );
	}	
	else
	{
		LOGEVENT( "条目点击，但是没有找到任何注册的事件" );
	}
}

CString CTransparentAddrList::FirstLetter(int nCode)
{
	if(nCode >= 1601 && nCode < 1637) return _T("A");
	if(nCode >= 1637 && nCode < 1833) return _T("B");
	if(nCode >= 1833 && nCode < 2078) return _T("C");
	if(nCode >= 2078 && nCode < 2274) return _T("D");
	if(nCode >= 2274 && nCode < 2302) return _T("E");
	if(nCode >= 2302 && nCode < 2433) return _T("F");
	if(nCode >= 2433 && nCode < 2594) return _T("G");
	if(nCode >= 2594 && nCode < 2787) return _T("H");
	if(nCode >= 2787 && nCode < 3106) return _T("J");
	if(nCode >= 3106 && nCode < 3212) return _T("K");
	if(nCode >= 3212 && nCode < 3472) return _T("L");
	if(nCode >= 3472 && nCode < 3635) return _T("M");
	if(nCode >= 3635 && nCode < 3722) return _T("N");
	if(nCode >= 3722 && nCode < 3730) return _T("O");
	if(nCode >= 3730 && nCode < 3858) return _T("P");
	if(nCode >= 3858 && nCode < 4027) return _T("Q");
	if(nCode >= 4027 && nCode < 4086) return _T("R");
	if(nCode >= 4086 && nCode < 4390) return _T("S");
	if(nCode >= 4390 && nCode < 4558) return _T("T");
	if(nCode >= 4558 && nCode < 4684) return _T("W");
	if(nCode >= 4684 && nCode < 4925) return _T("X");
	if(nCode >= 4925 && nCode < 5249) return _T("Y");
	if(nCode >= 5249 && nCode < 5590) return _T("Z");

    return "";
}

void CTransparentAddrList::GetFirstLetter(CString strName, CString& strFirstLetter)
{
    TBYTE ucHigh, ucLow;
    int  nCode;
    CString strRet;
	
    strFirstLetter.Empty();
	int nStrLength = strName.GetLength();
	
    for ( int i = 0; i < nStrLength; i++ )
    {
        if ( (TBYTE)strName[i] < 0x80 )
		{
			strRet = strName[i];
			strRet.MakeUpper();
			strFirstLetter += strRet;
            continue;
		}
		
		if ( i+1 >= nStrLength )
		{
			break;
		}

        ucHigh = (TBYTE)strName[i];		
        ucLow  = (TBYTE)strName[i+1];
        if ( ucHigh < 0xa1 || ucLow < 0xa1)
		{
            continue;
		}
        else
		{
            nCode = (ucHigh - 0xa0) * 100 + ucLow - 0xa0;
		}
		
        if ( nCode < 5590 )
        {
            strRet = FirstLetter( nCode );
        }
        else
        {
            strRet = CPYChar::GetPYChar( strName[i], strName[i+1] ); 
        }
        
        strFirstLetter += strRet;
        i++;
    }
}

BEGIN_MESSAGE_MAP(CTransparentAddrList, CTransparentList)
	ON_MESSAGE( UI_LETTERINDEX_CLICK, OnLetterClick )
END_MESSAGE_MAP()

                       
LRESULT CTransparentAddrList::OnLetterClick( WPARAM wParam, LPARAM lParam )
{   
	int nLetterIndex = (int)wParam;
	CString strIndex;
	nLetterIndex = 'A' + nLetterIndex;
	strIndex.Format( "%c", (char)nLetterIndex );
	int nYOffset = 0;
	int nItemCount = m_pItemList->GetItemCount();

	//2012-8-6 解决条目过多时，点击字母会卡的问题 ，使用二分法  by yjj
	int swLowIndex = 0;
	int swHighIndex = nItemCount;
	int swMidIndex = 0;   //置当前查找区间上、下界的初值 

	while( swLowIndex < swHighIndex )
	{   
		int nMidIndex = swMidIndex;
		//当前查找区间R[low..high]非空 
		swMidIndex =( swLowIndex + swHighIndex )/2; 
		if ( nMidIndex == swMidIndex )
		{
			break;
		}

		IItemList* pList = m_pItemList->GetItemByIndex( swMidIndex );
		if ( pList == NULL )
		{
			break;
		}	 
		IItemList* pSubList = pList->GetItemByIndex( 0 );
		if ( pSubList == NULL )
		{
			break;
		}

		IBaseItem* pItem = pSubList->GetItemData();
		if ( CTextItem* pTextItem = dynamic_cast<CTextItem*>(pItem) )
		{
			CString cStr = "";
			CString strLetter = "";
			cStr.Format( "%s", pTextItem->GetText().c_str() );
			GetFirstLetter( cStr, strLetter ); 

			int nRe = strIndex.Compare( strLetter );
			if(  nRe == 0 )  
			{                                            
				break;                                   
			} 
			else if ( nRe < 0 )
			{   
				swHighIndex = swMidIndex;  //当前查找区间R[low..mid]  
			}
			else
			{   
				swLowIndex = swMidIndex + 1;//当前查找区间R[mid..heith] 
			}						 
		}               
	} 

	//swLowIndex与swHighIndex相等时，跟swMidIndex比较
	if ( swLowIndex == swHighIndex )
	{
		if ( swMidIndex < swHighIndex )
		{
			swHighIndex = swMidIndex;
		}
		else
		{
			swLowIndex = swMidIndex;
		}
	}

	//取swLowIndex和swHighIndex中第一个比strIndex大的返回
	if ( swLowIndex > swHighIndex )
	{
		IItemList* pList = m_pItemList->GetItemByIndex( swHighIndex );
		if ( pList == NULL )
		{
			return S_OK;
		}		
		IItemList* pSubList = pList->GetItemByIndex( 0 );
		if ( pSubList == NULL )
		{
			return S_OK;
		}		
		IBaseItem* pItem = pSubList->GetItemData();
		if ( CTextItem* pTextItem = dynamic_cast<CTextItem*>(pItem) )
		{
			CString cStr = "";
			CString strLetter = "";
			cStr.Format( "%s", pTextItem->GetText().c_str() );
			GetFirstLetter( cStr, strLetter ); 

			int nRe = strIndex.Compare( strLetter );
			if( nRe > 0 )		 
			{
				swMidIndex = swLowIndex;
			}
			else
			{
				swMidIndex = swHighIndex;
			}
		}		
	}

	nYOffset = GetOffsetHeight( swMidIndex );
	 
	SetYOffset( nYOffset );
 
// 	DWORD dwEnd = GetTickCount() - dwStart; 	 
// 	strTime.Format("\nCTransparentAddrList::OnLetterClick  耗时=%ld\n",dwEnd);
// 	PrtMsg( 0, emEventTypeCmsWindow, (LPSTR)(LPCSTR)strTime );

	return S_OK;
}


bool CTransparentAddrList::AddrItemCompare( TAddrItem& tItem1, TAddrItem& tItem2 )
{
	if ( tItem1 == tItem2 )
	{
		return true;
	}
	
	if ( tItem1.strNameLetter.Compare( tItem2.strNameLetter ) < 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool CTransparentAddrList::UserItemCompare( CUserFullInfo& tItem1, CUserFullInfo& tItem2 )
{
    CString strLetter1;
    CString strLetter2;	
    
    GetFirstLetter( tItem1.GetName(), strLetter1 );
    GetFirstLetter( tItem2.GetName(), strLetter2 );
       
    if ( strLetter1.Compare( strLetter2 ) < 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool CTransparentAddrList::CnsInfoCompare(TCnsInfo& tInfo1, TCnsInfo& tInfo2)
{
	if ( tInfo1 == tInfo2 )
	{
		return true;
	}

	CString strLetter1;
	CString strLetter2;	
	
	GetFirstLetter( tInfo1.m_achRoomName, strLetter1 );
	GetFirstLetter( tInfo2.m_achRoomName, strLetter2 );
	
	if ( strLetter1.Compare( strLetter2 ) < 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool CTransparentAddrList::TPCnsInfoCompare(TTPCnsInfo& tInfo1, TTPCnsInfo& tInfo2)
{

	CString strLetter1;
	CString strLetter2;	
	
	GetFirstLetter( tInfo1.m_achRoomName, strLetter1 );
	GetFirstLetter( tInfo2.m_achRoomName, strLetter2 );
	
	if ( strLetter1.Compare( strLetter2 ) < 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool CTransparentAddrList::TempCnsCompare( TEpAddr& tCns1, TEpAddr& tCns2 )
{
	
    CString strLetter1;
    CString strLetter2;	
    
    GetFirstLetter( tCns1.m_tAlias.m_abyAlias, strLetter1 );
    GetFirstLetter( tCns2.m_tAlias.m_abyAlias, strLetter2 );
    
    if ( strLetter1.Compare( strLetter2 ) < 0 )
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool CTransparentAddrList::ConfTempCompare( TTPAlias& tAlias1, TTPAlias& tAlias2 )
{   
// 	if ( tAlias1 == tAlias2 )
// 	{
// 		return true;
// 	}

    CString strLetter1;
    CString strLetter2;	

	GetFirstLetter( tAlias1.m_abyAlias, strLetter1 );
	GetFirstLetter( tAlias2.m_abyAlias, strLetter2 );

	if ( strLetter1.Compare( strLetter2 ) < 0 )
	{
	   return true;
	}
	else
	{
	   return false;
	}
   
	/*
    int count  = pAryConfTemplate->Size();

    for (int i = 0; i < count-1; i++)
	{
        for (int j = 0; j < count-1-i; j++)
		{
			GetFirstLetter( pAryConfTemplate->GetAt(j).m_achConfName, strLetter1 );
            GetFirstLetter( pAryConfTemplate->GetAt(j + 1 ).m_achConfName, strLetter2 );
            if (bAscend)
            {                 
                // 升序
                if ( strLetter1.Compare( strLetter2 ) > 0 )
                {
                    TTPConfTemplate temp = pAryConfTemplate->GetAt(j);
                    temp.m_dwTimeID = pAryConfTemplate->GetAt(j).m_dwTimeID;
                    temp.m_wID = pAryConfTemplate->GetAt(j).m_wID;

                    pAryConfTemplate->GetAt(j) = pAryConfTemplate->GetAt(j + 1 );
                    pAryConfTemplate->GetAt(j).m_dwTimeID = pAryConfTemplate->GetAt(j + 1 ).m_dwTimeID;
                    pAryConfTemplate->GetAt(j).m_wID = pAryConfTemplate->GetAt(j + 1 ).m_wID;

                    pAryConfTemplate->GetAt(j + 1 ) = temp;
                    pAryConfTemplate->GetAt(j + 1 ).m_wID =  temp.m_wID;
                    pAryConfTemplate->GetAt(j + 1 ).m_dwTimeID = temp.m_dwTimeID ;

                }
            }
            else
            {
                // 降序
                if (strLetter1.Compare( strLetter2 ) < 0 )
                {
                    TTPConfTemplate temp = pAryConfTemplate->GetAt(j);
                    temp.m_dwTimeID = pAryConfTemplate->GetAt(j).m_dwTimeID;
                    temp.m_wID = pAryConfTemplate->GetAt(j).m_wID;


                    pAryConfTemplate->GetAt(j) = pAryConfTemplate->GetAt(j + 1 );
                    pAryConfTemplate->GetAt(j).m_dwTimeID = pAryConfTemplate->GetAt(j + 1 ).m_dwTimeID;
                    pAryConfTemplate->GetAt(j).m_wID = pAryConfTemplate->GetAt(j + 1 ).m_wID;


                    pAryConfTemplate->GetAt(j + 1 ) = temp;
                    pAryConfTemplate->GetAt(j + 1 ).m_wID =  temp.m_wID;
                    pAryConfTemplate->GetAt(j + 1 ).m_dwTimeID = temp.m_dwTimeID ;
                }
            }
		}
	}
	
	return true;
	*/
}


bool CTransparentAddrList::ConfMenuCompare(TConfMenuInfo& tItem1, TConfMenuInfo& tItem2)
{    
    if ( tItem1.nIndex < tItem2.nIndex )
    {
        return true;
    }
    else
    {
        return false;
    }
}

//CPYChar类，用于获取二级汉字首字母拼音
CString CPYChar::m_ArrQWSecond[32];
CPYChar g_PYChar;

CPYChar::CPYChar()
{
    m_ArrQWSecond[0]="CJWGNSPGCGNESYPBTYYZDXYKYGTDJNNJQMBSGZSCYJSYYQPGKBZGYCYWJKGKLJSWKPJQHYTWDDZLSGMRYPYWWCCKZNKYDG";
    
    m_ArrQWSecond[1]="TTNGJEYKKZYTCJNMCYLQLYPYQFQRPZSLWBTGKJFYXJWZLTBNCXJJJJZXDTTSQZYCDXXHGCKBPHFFSSWYBGMXLPBYLLLHLX";
    
    m_ArrQWSecond[2]="SPZMYJHSOJNGHDZQYKLGJHSGQZHXQGKEZZWYSCSCJXYEYXADZPMDSSMZJZQJYZCDJZWQJBDZBXGZNZCPWHKXHQKMWFBPBY";
    
    m_ArrQWSecond[3]="DTJZZKQHYLYGXFPTYJYYZPSZLFCHMQSHGMXXSXJJSDCSBBQBEFSJYHWWGZKPYLQBGLDLCCTNMAYDDKSSNGYCSGXLYZAYBN";
    
    m_ArrQWSecond[4]="PTSDKDYLHGYMYLCXPYCJNDQJWXQXFYYFJLEJBZRXCCQWQQSBNKYMGPLBMJRQCFLNYMYQMSQTRBCJTHZTQFRXQHXMJJCJLX";
    
    m_ArrQWSecond[5]="QGJMSHZKBSWYEMYLTXFSYDSGLYCJQXSJNQBSCTYHBFTDCYZDJWYGHQFRXWCKQKXEBPTLPXJZSRMEBWHJLBJSLYYSMDXLCL";
    
    m_ArrQWSecond[6]="QKXLHXJRZJMFQHXHWYWSBHTRXXGLHQHFNMNYKLDYXZPWLGGTMTCFPAJJZYLJTYANJGBJPLQGDZYQYAXBKYSECJSZNSLYZH";
    
    m_ArrQWSecond[7]="ZXLZCGHPXZHZNYTDSBCJKDLZAYFMYDLEBBGQYZKXGLDNDNYSKJSHDLYXBCGHXYPKDJMMZNGMMCLGWZSZXZJFZNMLZZTHCS";
    
    m_ArrQWSecond[8]="YDBDLLSCDDNLKJYKJSYCJLKOHQASDKNHCSGANHDAASHTCPLCPQYBSDMPJLPCJOQLCDHJJYSPRCHNWJNLHLYYQYYWZPTCZG";
    
    m_ArrQWSecond[9]="WWMZFFJQQQQYXACLBHKDJXDGMMYDJXZLLSYGXGKJRYWZWYCLZMSSJZLDBYDCFCXYHLXCHYZJQSFQAGMNYXPFRKSSBJLYXY";
    
    m_ArrQWSecond[10]="SYGLNSCMHCWWMNZJJLXXHCHSYDSTTXRYCYXBYHCSMXJSZNPWGPXXTAYBGAJCXLYSDCCWZOCWKCCSBNHCPDYZNFCYYTYCKX";
    
    m_ArrQWSecond[11]="KYBSQKKYTQQXFCWCHCYKELZQBSQYJQCCLMTHSYWHMKTLKJLYCXWHEQQHTQHZPQSQSCFYMMDMGBWHWLGSSLYSDLMLXPTHMJ";
    
    m_ArrQWSecond[12]="HWLJZYHZJXHTXJLHXRSWLWZJCBXMHZQXSDZPMGFCSGLSXYMJSHXPJXWMYQKSMYPLRTHBXFTPMHYXLCHLHLZYLXGSSSSTCL";
    
    m_ArrQWSecond[13]="SLDCLRPBHZHXYYFHBBGDMYCNQQWLQHJJZYWJZYEJJDHPBLQXTQKWHLCHQXAGTLXLJXMSLXHTZKZJECXJCJNMFBYCSFYWYB";
    
    m_ArrQWSecond[14]="JZGNYSDZSQYRSLJPCLPWXSDWEJBJCBCNAYTWGMPAPCLYQPCLZXSBNMSGGFNZJJBZSFZYNDXHPLQKZCZWALSBCCJXJYZGWK";
    
    m_ArrQWSecond[15]="YPSGXFZFCDKHJGXDLQFSGDSLQWZKXTMHSBGZMJZRGLYJBPMLMSXLZJQQHZYJCZYDJWBMJKLDDPMJEGXYHYLXHLQYQHKYCW";
    
    m_ArrQWSecond[16]="CJMYYXNATJHYCCXZPCQLBZWWYTWBQCMLPMYRJCCCXFPZNZZLJPLXXYZTZLGDLDCKLYRZZGQTGJHHHJLJAXFGFJZSLCFDQZ";
    
    m_ArrQWSecond[17]="LCLGJDJCSNCLLJPJQDCCLCJXMYZFTSXGCGSBRZXJQQCTZHGYQTJQQLZXJYLYLBCYAMCSTYLPDJBYREGKLZYZHLYSZQLZNW";
    
    m_ArrQWSecond[18]="CZCLLWJQJJJKDGJZOLBBZPPGLGHTGZXYGHZMYCNQSYCYHBHGXKAMTXYXNBSKYZZGJZLQJDFCJXDYGJQJJPMGWGJJJPKQSB";
    
    m_ArrQWSecond[19]="GBMMCJSSCLPQPDXCDYYKYFCJDDYYGYWRHJRTGZNYQLDKLJSZZGZQZJGDYKSHPZMTLCPWNJAFYZDJCNMWESCYGLBTZCGMSS";
    
    m_ArrQWSecond[20]="LLYXQSXSBSJSBBSGGHFJLWPMZJNLYYWDQSHZXTYYWHMCYHYWDBXBTLMSYYYFSXJCSDXXLHJHFSSXZQHFZMZCZTQCXZXRTT";
    
    m_ArrQWSecond[21]="DJHNNYZQQMNQDMMGYYDXMJGDHCDYZBFFALLZTDLTFXMXQZDNGWQDBDCZJDXBZGSQQDDJCMBKZFFXMKDMDSYYSZCMLJDSYN";
    
    m_ArrQWSecond[22]="SPRSKMKMPCKLGDBQTFZSWTFGGLYPLLJZHGJJGYPZLTCSMCNBTJBQFKTHBYZGKPBBYMTTSSXTBNPDKLEYCJNYCDYKZDDHQH";
    
    m_ArrQWSecond[23]="SDZSCTARLLTKZLGECLLKJLQJAQNBDKKGHPJTZQKSECSHALQFMMGJNLYJBBTMLYZXDCJPLDLPCQDHZYCBZSCZBZMSLJFLKR";
    
    m_ArrQWSecond[24]="ZJSNFRGJHXPDHYJYBZGDLQCSEZGXLBLGYXTWMABCHECMWYJYZLLJJYHLGBDJLSLYGKDZPZXJYYZLWCXSZFGWYYDLYHCLJS";
    
    m_ArrQWSecond[25]="CMBJHBLYZLYCBLYDPDQYSXQZBYTDKYXJYYCNRJMPDJGKLCLJBCTBJDDBBLBLCZQRPPXJCGLZCSHLTOLJNMDDDLNGKAQHQH";
    
    m_ArrQWSecond[26]="JGYKHEZNMSHRPHQQJCHGMFPRXHJGDYCHGHLYRZQLCYQJNZSQTKQJYMSZSWLCFQQQXYFGGYPTQWLMCRNFKKFSYYLQBMQAMM";
    
    m_ArrQWSecond[27]="MYXCTPSHCPTXXZZSMPHPSHMCLMLDQFYQXSZYJDJJZZHQPDSZGLSTJBCKBXYQZJSGPSXQZQZRQTBDKYXZKHHGFLBCSMDLDG";
    
    m_ArrQWSecond[28]="DZDBLZYYCXNNCSYBZBFGLZZXSWMSCCMQNJQSBDQSJTXXMBLTXZCLZSHZCXRQJGJYLXZFJPHYMZQQYDFQJJLZZNZJCDGZYG";
    
    m_ArrQWSecond[29]="CTXMZYSCTLKPHTXHTLBJXJLXSCDQXCBBTJFQZFSLTJBTKQBXXJJLJCHCZDBZJDCZJDCPRNPQCJPFCZLCLZXZDMXMPHJSGZ";
    
    m_ArrQWSecond[30]="GSZZQJYLWTJPFSYASMCJBTZKYCWMYTCSJJLJCQLWZMALBXYFBPNLSFHTGJWEJJXXGLLJSTGSHJQLZFKCGNNDSZFDEQFHBS";
    
    m_ArrQWSecond[31]="AQTGLLBXMMYGSZLDYDQMJJRGBJTKGDHGKBLQKBDMBYLXWCXYTTYBKMRTJZXQJBHLMHMJJZMQASLDCYXYQDLQCAFYWYXQHZ";
    
}

CPYChar::~CPYChar()
{
    
}

//功能：检测Value  是否在Lp..Hp之间   
BOOL CPYChar::In(int Lp, int Hp,int Value)   
{   
    ASSERT(Lp<=Hp);   
    return  ((Value<=Hp)&&(Value>=Lp));   
}  

//参数：一个汉字   
//返回值：该汉字的拼音   
char CPYChar::GetPYChar(CString HZ)   
{   
    ASSERT(HZ.GetLength()==2); 
    return GetPYChar(HZ.GetAt(0),HZ.GetAt(1));
}   

//参数：一个汉字   
//返回值：该汉字的拼音   
char CPYChar::GetPYChar(TCHAR c1,TCHAR c2)   
{   
    WORD  Hi=WORD(c1)<<8;   
    WORD  Lo=BYTE(c2);   
    int  n= Hi + Lo;
    if ( n<=0xD7F9 )
    {
        if   (In(0xB0A1,0xB0C4,n))   return   'A';   
        if   (In(0XB0C5,0XB2C0,n))   return   'B';   
        if   (In(0xB2C1,0xB4ED,n))   return   'C';   
        if   (In(0xB4EE,0xB6E9,n))   return   'D';   
        if   (In(0xB6EA,0xB7A1,n))   return   'E';   
        if   (In(0xB7A2,0xB8C0,n))   return   'F';   
        if   (In(0xB8C1,0xB9FD,n))   return   'G';   
        if   (In(0xB9FE,0xBBF6,n))   return   'H';   
        if   (In(0xBBF7,0xBFA5,n))   return   'J';   
        if   (In(0xBFA6,0xC0AB,n))   return   'K';   
        if   (In(0xC0AC,0xC2E7,n))   return   'L';   
        if   (In(0xC2E8,0xC4C2,n))   return   'M';   
        if   (In(0xC4C3,0xC5B5,n))   return   'N';   
        if   (In(0xC5B6,0xC5BD,n))   return   'O';   
        if   (In(0xC5BE,0xC6D9,n))   return   'P';   
        if   (In(0xC6D1,0xC8BA,n))   return   'Q';   
        if   (In(0xC8BB,0xC8F5,n))   return   'R';   
        if   (In(0xC8F6,0xCBF9,n))   return   'S';   
        if   (In(0xCBFA,0xCDD9,n))   return   'T';   
        if   (In(0xCDDA,0xCEF3,n))   return   'W';   
        if   (In(0xCEF4,0xD1B8,n))   return   'X';   
        if   (In(0xD1B9,0xD4D0,n))   return   'Y';   
        if   (In(0xD4D1,0xD7F9,n))   return   'Z';  
        return   char(0);
    }
    else
    {
        char b1 = (c1&0x7F)-0x20 - 56;
        char b2 = (c2&0x7F)-0x20 - 1;
        if (b1>=0 && b1<=31 && b2>=0 && b2<=93)
        {
            return m_ArrQWSecond[b1].GetAt(b2);
        }
        return   char(0);
    }
}   
