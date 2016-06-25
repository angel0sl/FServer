/***********************************************************************
*FileName	:  NetIO
*Author		:  fz
*Date		:  2016.1.17
*Description:  ����IO�߳�
************************************************************************/
#pragma once
#include <event.h>
#include "NetEventQueue.h"

class NetWork;

class NetIO
{
	event_base* mEvBase;
	/*�߳�ID ����thread::id��һ����,��̫��,���Ե�������һ��������ID*/
	int mTID;
	/*�������ӵĶ���*/
	EventQueue* mConnectQueue;
	/*������Ϣ�Ķ���*/
	EventQueue* mInputQueue;
	/*������Ϣ�Ķ���*/
	EventQueue* mOutputQueue;
public:
	NetIO();
	~NetIO();

	bool Init(NetWork* net, int tid);
	void Run();
	void Stop();
	bool IsValid() { return mTID >= 0; }
	event_base* GetEvBase() { return mEvBase; }
	int GetTID() { return mTID; }
	//����3���¼�����ָ���Ǹ�netIstance���õ�,���ڽ�������ӵ�����������,������մ�����Ϣ
	EventQueue* GetInputQueue() { return mInputQueue; }
	EventQueue* GetOutputQueue() { return mOutputQueue; }
	EventQueue* GetConnectQueue() { return mConnectQueue; }
};

