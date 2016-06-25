/***********************************************************************
*FileName	:  NetWork
*Author		:  fz
*Date		:  2016.1.17
*Description:  ����ʵ��(�������)
************************************************************************/
#pragma once
#include <map>
#include <vector>
#include <thread>
#include <memory>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/thread.h>
#include <event2/event_compat.h>
#include "NetDefine.h"
#include "NetListener.h"
#include "NetIO.h"
#include "NetObject.h"

typedef std::function<int(const NetPacket& msg)> OnNetCB;
typedef std::shared_ptr<OnNetCB> OnNetCBPtr;

class NetWork
{
	event_base*	mEvBase;
	/*�����߳�*/
	NetListener* mListener;
	/*��������Ķ˿�*/
	int mPort;
	/*����IO�߳����������*/
	int mConnectCount;
	/*IO�߳���*/
	int mIOCount;
	/*���ڵ���IO�߳�*/
	int mCurIOIndex;
	/*IO�߳��б�*/
	std::vector<NetIO*> mvecNetIO;
	/*���Ӷ���map<fd,obj> Ч�ʿ��ǿ��Ըĳ�vector��unorder_map*/
	std::map<int, NetObject*> mmapObject;
	/*�ϲ㴦�������¼��Ļص�����*/
	OnNetCB mOnNetCB;
public:
	template<typename Entity>
	NetWork(Entity* entity, int (Entity::*OnNet)(const NetPacket&), int port, int connCnt, int ioCnt = 4)
	{
		mEvBase = NULL;
		mListener = NULL;
		mPort = port;
		mConnectCount = connCnt;
		mIOCount = ioCnt;
		mOnNetCB = std::bind(OnNet, entity, std::placeholders::_1);
	}
	virtual ~NetWork(){};
	
	virtual bool CreateNet();
	virtual bool StartNet();
	virtual bool CloseNet();

	/*������������ �൱��client,��������CreateNet,���ӳɹ�Ҳ�����IO�̵߳Ķ���*/
	virtual evutil_socket_t ConnectTo(const std::string& ip, int port);

	/*�����¼��ص����� �ֱ�����������Ӻ����ݵ��շ�,��ϸ��OnEventCB*/
	virtual void OnConnectEvent(void* msg, void* args);
	virtual void OnInputEvent(void* msg, void* args);
	virtual void OnOutputEvent(void* msg, void* args);

	/*�ϲ���÷����ݵĽӿ�*/
	virtual bool SendData(NetPacket* packet);

	virtual bool AddNetObject(const int fd, NetObject* obj){ return mmapObject.insert(std::make_pair(fd, obj)).second; }
	virtual bool RemoveNetObject(const int fd);

	/*�̵߳��� ֻ�Ǽ򵥵��ֻ�,�߼��Ĺ�������Լ���д*/
	virtual NetIO* DispatchIO();

	bool SetEvBufferTimeout(int fd, int sec);

	event_base* GetEvBase() const { return mEvBase; }
	int GetPort() const { return mPort; }
	int GetMaxConnect() const { return mIOCount * mConnectCount; }
	bool CheckConnectFull(){ return mmapObject.size() >= GetMaxConnect(); }
	NetIO* GetNetIO(int tid);
	NetObject* GetNetObject(int fd);
private:
	/*libevent���͵Ľӿ� ����δ�����������¼����� �ϲ㲻Ӧ��ֱ�ӵ�������Send����,Ӧ��ͨ��SendData������Ӧ��IO��Ϣ������������*/
	virtual bool Send(const char* msg, const int len, const int fd);
	virtual bool SendToAll(const char* msg, const int len);

	/*libevent�����д�͵ײ��¼��Ļص�*/
	static void conn_readcb(bufferevent* evBuf, void* uData);
	static void conn_writecb(bufferevent* evBuf, void* uData);
	static void conn_eventcb(bufferevent* evBuf, short events, void* uData);
};
