/***********************************************************************
*FileName	:  NetInterface
*Author		:  fz
*Date		:  2016.1.17
*Description:  ����ӿ�(����㹩�߼�����õ�һ���ӿ�,�������Ϊһ��������߼�֮����м��)
************************************************************************/
#pragma once
#include <vector>
#include <google/protobuf/message.h>
#include "BaseSession.h"
#include "NetWork.h"

class NetInterface
{
	NetWork* mNetWork;
	std::vector<BaseSession*> mvecSession;
public:
	NetInterface();
	virtual~NetInterface();

	/*��ʼ���� Server (�˿�, �����߳��е�������, �߳���)*/
	bool Init(int port, int connCnt, int ioCnt = 4);
	
	/*�������� Client (Ŀ��IP, Ŀ��˿�) �����ɹ����صײ�FD�������session*/
	evutil_socket_t OnConnectTo(const std::string& ip, int port);
	/*OnConnectTo�ɹ��������Ļص� ���߼����Լ������Ƿ��session,�ⲿ���������ӿ���ͨ��OnMessage���д���*/
	virtual void OnConnected(const NetPacket& msg){};

	/*�����յ�����Ϣ ����ֻ�Ǵ�����session����Ϣ,δ��ӻ���Ҫ���session����Ϣ���Լ̳к���д�˺���*/
	virtual void OnMessage(const NetPacket& msg, int msgType = 0);
	/*�����͵���Ϣ Ӧ�ö��ô�session�ķ�ʽ,ֻ������session��ʱ�����fd*/
	virtual bool OnSend(BaseSession* session, ::google::protobuf::Message* pbMsg);
	virtual bool OnSend(int fd, ::google::protobuf::Message* pbMsg);
	virtual bool OnSendToAll(::google::protobuf::Message* pbMsg);

	/*�Ͽ�����*/
	bool OnDisconnect(int index);
	bool OnDisconnectByFD(int fd);
	
	/*����/���session �������ӷּ���(listen)����������(connect)*/
	bool AttachSession(BaseSession* session);
	void RemoveSession(BaseSession* session);

	NetWork* GetNetWork() const { return mNetWork; }
	NetObject* GetNetObject(BaseSession* session);
	BaseSession* GetSession(int index);
	BaseSession* GetSessionByFD(int fd);
private:
	/*���������¼� �������ȡ���¼������ת���߼���*/
	int OnNetEvent(const NetPacket& msg);

	/*�齨���͵İ�*/
	NetPacket* BuildOutPacket(BaseSession* session, ::google::protobuf::Message* pbMsg);
	NetPacket* BuildOutPacket(int fd, ::google::protobuf::Message* pbMsg);
	NetPacket* BuildBroadcastPacket(::google::protobuf::Message* pbMsg);

	/*������㷢����Ϣ�Ľӿ� ��OnSend����*/
	bool SendPacket(NetPacket* packet);
	bool SendPacketToAll(NetPacket* packet);
};
