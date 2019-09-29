#ifndef UIDEF_H
#define UIDEF_H



#pragma warning( disable : 4786 )
#pragma warning( disable : 4503 )
#pragma warning( disable : 4800 )
#include "uilibhead.h"
#include "uiexhead.h"
//#include "LuaPlus.h"
#pragma comment (lib, "uilib.lib")
#pragma comment (lib, "uiex.lib")
//#pragma comment (lib, "luaplus.lib")

#include <map>
#include <string>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
using namespace std;
//using namespace LuaPlus;

namespace AutoUIFactory
{
#ifndef Interface
#define Interface class
#endif

#ifndef Window
#define Window CWnd
#endif

#ifndef String
#define String std::string
#endif

#ifndef WindowMsg
#define WindowMsg MSG
#endif

//������Ϣ
typedef struct tagFontInfo
{
    int     nFontSize;
    String  strFontName;   
    String  strNormalColor;
    String  strFocusColor;
    String  strDisableColor;   
    String  strDisableImg;    //disableʱ�Ƿ���ʾ����ͼ
    
    tagFontInfo()
    {
        nFontSize = 0;
        strFontName = "";       
        strNormalColor = "";
        strFocusColor = "";
        strDisableColor = "";
        strDisableImg = "";
    }
}TFontInfo;

}
#endif