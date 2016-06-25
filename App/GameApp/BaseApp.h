#pragma once
#include <AppSession.h>
#include <PoolManager.h>
#include "GameApp.h"

class BaseApp : public AppSession
{
public:
	BaseApp();
	~BaseApp();

	bool SendToApp(::google::protobuf::Message* pbMsg);//����SendToBase����,ͳһ��������App���͵�����App����Ϣ�ӿ�����ΪSendToApp

	virtual void Connected();
	virtual void Disconnected();
	virtual void OnMsg(const NetMessage* nmsg, int msgType = 0);
};