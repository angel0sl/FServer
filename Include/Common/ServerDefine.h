/*���������ö�ٵȶ���*/
#pragma once
#include <GPDef.h>

#define MAX_PLAYER_COUNT 5000
#define MAX_CONNECT_COUNT 10000
#define RECONNECT_MSEC 1000 //����


/*������App���Ͷ���*/
enum ServerAppType
{
	ESAT_Unknown = 0,
	ESAT_DBMgr,
	ESAT_Base,
	ESAT_BaseCenter,
	ESAT_Game,
	ESAT_GameCenter,
	ESAT_Cubby,
	ESAT_Login,
	ESAT_Payment,
	ESAT_Interface,
};

/*������AppID����*/
enum ServerAppID
{
	ESAI_Unknown = 0,
	ESAI_DBMgrApp,
	ESAI_BaseCenterApp,
	ESAI_GameCenterApp,
	ESAI_LoginApp,
	ESAI_PaymentApp,
	ESAI_InterfaceApp,

	/*baseappΪ100���ż��,+1��Ϊ��Ӧ��gameapp*/
	ESAI_MinBaseApp = 100,
	ESAI_MinGameApp = 101,

	ESAI_MaxBaseApp = 998,
	ESAI_MaxGameApp = 999
};

/*���ݿ�����*/
enum DBType
{
	EDBT_Unknown = 0,
	EDBT_Global,
	EDBT_Game,
	EDBT_Log,
};

/*�ʺ�Ȩ�� LoginApp���ݴ�Ȩ�޹����¼*/
#define ACCOUNT_LEVEL_DEFAULT			0x00	//Ĭ�����κ�Ȩ��
#define ACCOUNT_LEVEL_ADMINISTRATOR		0x01	//����Ա
#define ACCOUNT_LEVEL_GAMEMASTER		0x02	//GM
#define ACCOUNT_LEVEL_ALPHA				0x04	//a���ʺ�
#define ACCOUNT_LEVEL_BETA				0x08	//b���ʺ�
#define ACCOUNT_LEVEL_GAMER				0x10	//��ʽ�ʺ�
#define ACCOUNT_LEVEL_FREE				0x20	//
#define ACCOUNT_LEVEL_UNDER_AGE			0x40	//δ����
#define ACCOUNT_LEVEL_128				0x80	//
#define ACCOUNT_LEVEL_ALL				0xff	//All


/*��ȫ���ͷ�һ��ָ���ڴ�*/
#define SAFE_DELETE(i) if (i){ delete i; i = NULL;}
/*��ȫ���ͷ�һ��ָ�������ڴ�*/
#define SAFE_DELETE_ARRAY(i) if (i){ delete[] i; i = NULL;}
