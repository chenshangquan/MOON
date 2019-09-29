#ifndef _LOCAL_XML_TYPE_H_
#define _LOCAL_XML_TYPE_H_

#include "tpcommonxmltype.h"

const char XmlLocalTypeVersion[] = "2016-12-7 11:15:53";

 
#define TpEnumIdString(type, index) index, GetTpEnumString(emx_##type, index)
#define TpEnumString(type, index) GetTpEnumString(emx_##type, index)
s8* GetTpEnumString(u16 wType, u16 wIndex);
TXDATAINFO** CombineEnumDateInfo(void);
TXDATAINFO** CombineStructDateInfo(void);
void CombineEnumXDescripTbl(void);

#endif //_LOCAL_XML_TYPE_H_
