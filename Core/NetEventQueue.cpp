#include "NetEventQueue.h"
#include <glog/glog.h>

CircleBuffer* CBufferNew(unsigned int maxCount)
{
	if (maxCount == 0)
		return NULL;
	CircleBuffer* cBuf = (CircleBuffer*)calloc(1, sizeof(CircleBuffer)+sizeof(Elem)*maxCount - 1);//-1����ΪCircleBuffer������Elem����
	if (cBuf == NULL)
		return NULL;
	cBuf->m_head = 0;
	cBuf->m_tail = 0;
	cBuf->m_curCount = 0;
	cBuf->m_maxCount = maxCount;
	return cBuf;
}
static void CBufferFree(CircleBuffer* cBuf)
{
	free(cBuf);
}
//������ˣ���cBuf���
static inline void CBufferClear(CircleBuffer* cBuf)
{
	cBuf->m_head = 0;
	cBuf->m_tail = 0;
	cBuf->m_curCount = 0;
}
static bool CBufferPush(CircleBuffer* cBuf, const Elem em)
{
	if (cBuf->m_curCount >= cBuf->m_maxCount) //buf�����Ƿ���Ҫ������û��ǽ�em���⴦�����ϲ����д���
		return false;
	cBuf->m_elems[cBuf->m_tail++] = em;
	if (cBuf->m_tail >= cBuf->m_maxCount)
		cBuf->m_tail = 0;
	++cBuf->m_curCount;
	return true;
}
static Elem CBufferPop(CircleBuffer* cBuf)
{
	if (cBuf->m_curCount == 0)
		return NULL;
	Elem em = cBuf->m_elems[cBuf->m_head++];
	if (cBuf->m_head >= cBuf->m_maxCount)
		cBuf->m_head = 0;
	--cBuf->m_curCount;
	return em;
}
static inline unsigned int CBufferSize(CircleBuffer* cq)
{
	return cq->m_curCount;
}
static inline bool CBufferIsEmpty(CircleBuffer* cBuf)
{
	return cBuf->m_curCount == 0;
}
static inline bool CBufferIsFull(CircleBuffer* cBuf)
{
	return cBuf->m_curCount >= cBuf->m_maxCount;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/

EventQueue::EventQueue(OnEventCB eventCB, void* eventCBArgs, int maxSize)
{
	mQueue = NULL;
	mWriteFD = -1;
	mReadFD = -1;
	mEventCB = eventCB;
	mEventCBArgs = eventCBArgs;
	mQueue = CBufferNew(maxSize);
}

EventQueue::~EventQueue()
{
}

bool EventQueue::InitQueue(event_base* evBase)
{
	evutil_socket_t fds[2];
	if (evutil_socketpair(AF_UNIX, SOCK_STREAM, 0, fds) == -1)
		return false;

	mWriteFD = fds[0];
	mReadFD = fds[1];
	evutil_make_socket_nonblocking(mWriteFD);
	evutil_make_socket_nonblocking(mReadFD);
	event_assign(&mEvent, evBase, mReadFD, EV_READ | EV_PERSIST, PopToQueue, this);
	event_add(&mEvent, NULL);
	return true;
}

bool EventQueue::ClearQueue()
{
	if (mQueue)
	{
		CBufferFree(mQueue);
		mQueue = NULL;
	}
	event_del(&mEvent);
	if (mReadFD != -1) 
	{
		evutil_closesocket(mReadFD);
		mReadFD = -1;
	}
	if (mWriteFD != -1) 
	{
		evutil_closesocket(mWriteFD);
		mWriteFD = -1;
	}
	return true;
}

bool EventQueue::PushToQueue(void* netEvent)
{
	mLock.lock();
	if (CBufferIsFull(mQueue))
	{
		LOG(ERROR) << "MsgQueue is full! " << LogValue("size", CBufferSize(mQueue));
		CBufferClear(mQueue);
	}
	if (!CBufferPush(mQueue, netEvent))
	{
		mLock.unlock();
		return false;
	}
	if (CBufferSize(mQueue) == 1)
		SocketWrite();
	mLock.unlock();
	return true;
}

void EventQueue::PopToQueue(evutil_socket_t fd, short events, void* args)
{
	auto eq = (EventQueue*)args;
	eq->SocketRead();
	eq->mLock.lock();
	while (CBufferSize(eq->GetQueue()) >= 1)
	{
		auto netEvent = CBufferPop(eq->GetQueue());
		eq->mEventCB(netEvent, eq->mEventCBArgs);
		//�����ڴ˴�д��log���鿴ʵ�������ÿ��IOһ�ε��״����˶����߼�,��Ҫ���߼��߳�,�ڿ���Ҫ��Ҫ��
	}
	eq->mLock.unlock();
}

/*
bool EventQueue::SocketInit(event_base* evBase, event_callback_fn fn, void* args)
{
evutil_socket_t fds[2];
if (evutil_socketpair(AF_UNIX, SOCK_STREAM, 0, fds) == -1)
return false;

mWriteFD = fds[0];
mReadFD = fds[1];
evutil_make_socket_nonblocking(mWriteFD);
evutil_make_socket_nonblocking(mReadFD);
//event_assign��mReadFD��Ϊ�����¼����ڲ�fd,�����ص�������fn�ص�����,������IO�ĵײ�ʵ��,���е��¼�����Ӧ����ص���fn�������
event_assign(&mEvent, evBase, mReadFD, EV_READ | EV_PERSIST, fn, args);
event_add(&mEvent, NULL);
/ *�����������ģ�evsig_add��Ϊ��ں�������������̽�ĳ��linux�ź�ͨ��sigaction��signal������evsig_handler����ص�������
�ڻص��������ڲ����ź�����Ϊ����д��socketpair[0]�����͸���һ�ˡ���һ��ͨ�� socketpair[1]��ȡ���źź�
�ص������� base->sig.ev_signal �еĻص��������� evsig_cb.������������ڲ�������˽��¼�֪ͨ���ϲ㣬
����ʱ����ʵ����IO���¼�������ȫһ���ˡ�* /

return true;
}
*/
