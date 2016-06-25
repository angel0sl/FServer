#pragma once
#include <Singleton.h>
#include "ConfigStruct.h"

#define theConfigMgr ConfigManager::GetInstance()
class ConfigManager : public Singleton<ConfigManager>
{
	/*��ǰ���̵�appid*/
	APP_ID mAppID;
	std::map<int, ServerCfg>			mmapServerCfg;
	std::map<int, RobotCfg>				mmapRobotCfg;
	std::map<std::string, std::string>	mmapGameCfg;
	std::map<int, DBCfg>				mmapDBCfg;
public:
	ConfigManager();
	~ConfigManager();

	/*����������*/
	bool ParseCommond(int argc, char* argv[]);
	/*����appid������������� ��������app���̶���Ҫ��������,Ϊ������ز���Ҫ������,����AppID������,�����о�����Ҫ��ȡ��xml*/
	bool LoadingConfig();
	/*��ȡ��������,����ʹ��LoadingConfig*/
	bool LoadingAll();

	bool LoadSeverConfig();
	bool LoadRobotConfig();
	bool LoadGameConfig();
	bool LoadDBConfig();
	bool LoadT(){ return true; }

	std::map<int, ServerCfg>* GetServerMap() { return &mmapServerCfg; }
	ServerCfg* GetServerCfg(int appid);
	RobotCfg* GetRobotCfg(int appid);
	APP_ID GetAppID() const { return mAppID; }
	int GetBaseAppID()
	{
		if (mAppID >= ESAI_MinBaseApp && mAppID <= ESAI_MaxBaseApp)
		{
			if (mAppID % 2 == 0)
				return mAppID;
			else
				return (mAppID - 1);
		}
		return ESAI_Unknown;
	}
	int GetGameAppID()
	{
		if (mAppID >= ESAI_MinBaseApp && mAppID <= ESAI_MaxBaseApp)
		{
			if (mAppID % 2 == 1)
				return mAppID;
			else
				return (mAppID + 1);
		}
		return ESAI_Unknown;
	}
	int GetConfigVal(std::string s);
	std::string GetConfigStr(std::string s);
	void GetConfigArray(std::string s, std::string sign, std::vector<int>* vec);

	std::map<int, DBCfg>* GetDBCfgMap() { return &mmapDBCfg; };
	DBCfg* GetDBCfg(int id);
	
};

// void SplitStr(std::string &str, std::string sign, std::vector<std::string>& outVec)
// {
// 	int begin = 0, end = 0;
// 	do
// 	{
// 		end = str.find_first_of(sign);
// 		if (begin < str.size())
// 			outVec.push_back(str.substr(begin, end - begin));
// 		begin = end + 1;
// 	} while (end != std::string::npos);
// }

#include <sstream>
template<class Data>
std::string DataToStr(Data data)
{
	std::ostringstream oss;
	oss << data;
	return oss.str();
}

template<class Data>
Data StrToData(std::string str, Data& data)
{
	std::istringstream iss(str);
	iss >> data;
	return data;
}