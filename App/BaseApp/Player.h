/***********************************************************************
*FileName	:  Player
*Author		:  fz
*Date		:  2016.5.21
*Description:  player��,ֻ�Ǽ̳�������Ự,������ģ����Ҫ�������,����ֱ�����ӽű����õĽӿ�,�����߼���Ҫ���ڽű���,Ҳ����C++ʵ��
************************************************************************/
#pragma once
#include <PlayerSession.h>
#include <PoolManager.h>
#include "ProtoMessage.h"


class Player : PlayerSession
{
public:
	Player();
	~Player();

	//void OnReset();//?�Ȳ�����,����kbe��ô������ҵĶ��������

	bool SendToClient(::google::protobuf::Message* pbMsg);
	bool SendToBC(::google::protobuf::Message* pbMsg);
	bool SendToGame(::google::protobuf::Message* pbMsg);

	virtual void Connected();
	virtual void Disconnected();
	virtual void OnMsg(const NetMessage* nmsg, int msgType = 0);
};
