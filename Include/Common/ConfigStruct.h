#pragma once
#include <vector>
#include <map>
#include <string>
#include "ServerDefine.h"

/*xml�ļ�Ŀ¼*/
#define SERVERCONFIG_DIR "./Resource/Config/ServerConfig.xml"	//������app����
#define ROBOTCONFIG_DIR "./Resource/Config/RobotConfig.xml"	//������app����
#define GAMECONFIG_DIR "./Resource/Config/GameConfig.xml" //��Ϸ����
#define DBCONFIG_DIR "./Resource/Config/DBConfig.xml" //���ݿ���������

struct ServerCfg
{
	int appID;//�����֮��AppID
	std::string serverIP;
	int serverPort;
	ServerCfg(){ Clear(); }
	void Clear()
	{
		appID = ESAI_Unknown;
		serverIP = "";
		serverPort = 0;
	}
};

struct RobotCfg
{
	int appID;//1��������, 2Ŀ�����������
	std::string serverIP;
	int serverPort;
	int count;
	RobotCfg(){ Clear(); }
	void Clear()
	{
		appID = 0;
		serverIP = "";
		serverPort = 0;
		count = 0;
	}
};

struct DBCfg
{
	DBType		type;					//���ݿ�����
	std::string name;					//���ݿ���
	std::string user;					//��¼���û���
	std::string password;				//��¼������
	std::string host;					//���ݿ��ַ
	int port;							//���ݿ�˿�
	DBCfg(){ Clear(); }
	void Clear()
	{
		type = EDBT_Unknown;
		name = "";
		user = "";
		password = "";
		host = "";
		port = 0;
	}
};