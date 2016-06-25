/***********************************************************************
*FileName	:  AppSession
*Author		:  fz
*Date		:  2016.4.9
*Description:  �����listen��App�Ự
************************************************************************/
#pragma once
#include <GPDef.h>
#include <BaseSession.h>
#include <PoolManager.h>

/*���ඨ���������Ҫ��дOnReset��������*/
class AppSession : public BaseSession, public PoolObject
{
	APP_ID mAppID;
	APP_TYPE mAppType;
public:
	AppSession();
	virtual~AppSession();

	virtual void OnReset();

	virtual void Connected();
	virtual void Disconnected();
	virtual void OnMsg(const NetMessage* nmsg, int msgType = 0);

	void SetAppID(APP_ID appid) { mAppID = appid; }
	APP_ID GetAppID() const { return mAppID; }
	void SetAppType(APP_TYPE apptype) { mAppType = apptype; }
	APP_TYPE GetAppType() const { return mAppType; }
};
