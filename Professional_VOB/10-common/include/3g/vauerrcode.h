#ifndef _VAU_ERR_CODE_H_
#define _VAU_ERR_CODE_H_

//#include "kdmerrorid.h"
#define ERR_SUCCESS 0
#define ERR_CU_BGN  19000
enum EVauErr
{
    ERR_VAU_SUCCESS = ERR_SUCCESS,    // �ɹ�
    ERR_VAU_ERROR = ERR_CU_BGN,       // ʧ��
    ERR_VAU_TIMEOUT,                  // ��ʱ
    ERR_VAU_SESSION_INVALID,          // �Ự����Ч

	ERR_VAU_CREAT_APP_FAIL,           // ����APPʧ��
	ERR_VAU_INTERNAL,				  // VAU�ڲ�����
	ERR_VAU_PARAM,					  // ����Ĳ���

	ERR_VAU_PATH_LEN,                 // �����·������
	ERR_VAU_FILE_NAME_LEN,            // ������ļ��� ����
	ERR_VAU_NOEXIST_FILE,	          // �ļ�������
    ERR_VAU_NOEXIST_USERNAME,         // �û���������
    ERR_VAU_WRONG_USERPWD,            // �������
    ERR_VAU_USER_UNUSED,              // �û��ѱ�ͣ��
    ERR_VAU_EXPIREED_USERNAME,        // �û���ʹ�������ѵ�
    ERR_VAU_EXPIREED_USERPWD,         // ����ʹ�������ѵ�
    ERR_VAU_OVERLOGIN,                // ͬһ�û��ʺ��ѵ�½

    ERR_VAU_URL_INVALID,
    ERR_VAU_PU_INVALID,               // �Ƿ�PU
    ERR_VAU_PU_CHN_INVALID,           // �Ƿ�PUͨ��
    ERR_VAU_TRACK_INVALID,

    ERR_VAU_EXPLORE_EXCEED_RESTRICT,  // ����������·��
	ERR_VAU_REQUEST_EXCEED_RESTRICT,  // �������㲥·��
	ERR_VAU_DISCONNECTED_FROM_CMS,
};

#endif // _VAU_ERR_CODE_H_
