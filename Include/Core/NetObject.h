/***********************************************************************
*FileName	:  NetObject
*Author		:  fz
*Date		:  2016.1.17
*Description:  �������Ӷ���
************************************************************************/
#pragma once
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/event_compat.h>
class NetWork;

class NetObject
{
	NetWork* mNetWork;
	int mFD;
	bufferevent* mEvBuf;
	int mTID;//����IO�̵߳�ID
	//unsigned int mIP;//IP
	/*�������� ��NetInterface��mIndex,ֻ��Ϊ�����Ч��,����ȥ��session,ͬʱ������Ϊһ������״̬,ȷ���Ƿ��session��*/
	int mIndex;
	/*�Ƿ������ӵı�־λ*/
	bool mConnected;
	/*�Ƿ������� ֻ�Լ�������Ч,Ĭ�ϼ����������Ӷ���Ҫ�������,�粻��Ҫ���,���߼������о����ر��������*/
	bool mDetect;
public:
	NetObject(NetWork* net, int fd, bufferevent* bev, int tid) :
		mNetWork(net), mFD(fd), mEvBuf(bev), mTID(tid), mIndex(-1), mConnected(false), mDetect(false){}
	~NetObject(){};

	void SetIndex(int index){ mIndex = index; }
	void SetConnected(bool flag) { mConnected = flag; }
	void SetDetect(bool detect) { mDetect = detect; }

	NetWork* GetNetWork() const { return mNetWork; }
	bufferevent* GetEvBuf() const { return mEvBuf; }
	int GetTID() const { return mTID; }
	int GetFD()const { return mFD; }
	int GetIndex() const { return mIndex; }
	bool IsConnected() const { return mConnected; }
	bool IsDetect() const { return mDetect; }
};
