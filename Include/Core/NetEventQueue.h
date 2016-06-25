/***********************************************************************
*FileName	:  EventQueue
*Author		:  fz
*Date		:  2016.1.17
*Description:  �����¼�����
************************************************************************/
#pragma once
#include <functional>
#include <mutex>
#include <event.h>
#include <event2/event_struct.h>

/*�����¼��Ļص� function<��������(�ص�����, �ص���������)>*/
typedef std::function<void(void* msg, void* args)> OnEventCB;

typedef void* Elem;
struct CircleBuffer
{
	int m_head;
	int m_tail;
	int m_curCount;
	int m_maxCount;
	Elem m_elems[1];
};

//������Ϣ�¼�����
class EventQueue
{
	/*���ζ���*/
	CircleBuffer* mQueue;
	//����evutil_socketpairʵ��һ��������дsocket,����дsocketд������ʱ,��socket�ͻ�õ�֪ͨ,�������¼�
	/*дsocket*/
	evutil_socket_t mWriteFD;
	/*��socket*/
	evutil_socket_t mReadFD;
	event mEvent;
	std::mutex mLock;
	/*�ϲ㴦���¼��Ļص�����*/
	OnEventCB mEventCB;
	/*�ϲ㴦���¼��Ļص���������*/
	void* mEventCBArgs;
public:
	EventQueue(OnEventCB eventCB, void* eventCBArgs, int maxSize);
	~EventQueue();

	bool InitQueue(event_base* evBase);
	bool ClearQueue();

	CircleBuffer* GetQueue() { return mQueue; }
	//��ӵ��¼�����
	bool PushToQueue(void* netEvent);

private:
	//socket_pair_write
	int SocketWrite(){ return send(mWriteFD, "", 1, 0); }
	//socket_pair_read
	void SocketRead()
	{
		unsigned char buf[1024];
		while (recv(mReadFD, (char*)buf, sizeof(buf), 0) > 0){}
	}
	//�����Ƴ��¼�,��������ע��õ��¼��ص�������������е��¼�
	static void PopToQueue(evutil_socket_t fd, short events, void* args);
};
