/***********************************************************************
*FileName	:  PlayerSession
*Author		:  fz
*Date		:  2016.5.21
*Description:  �����listen��player�Ự
************************************************************************/
#pragma once
#include <GPDef.h>
#include <BaseSession.h>
#include <PoolManager.h>

/*���ඨ���������Ҫ��дOnReset��������*/
class PlayerSession : public BaseSession, public PoolObject
{
public:
	PlayerSession();
	virtual~PlayerSession();

	virtual void OnReset();

	virtual void Connected();
	virtual void Disconnected();
	virtual void OnMsg(const NetMessage* nmsg, int msgType = 0);

};
