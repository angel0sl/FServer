/***********************************************************************
*FileName	:  BaseSession
*Author		:  fz
*Date		:  2016.1.17
*Description:  ����Ự����,server��client�ĻỰ�õĶ��Ǵ˻���
************************************************************************/
#pragma once
#include <glog/glog.h>

struct NetMessage;

class BaseSession
{
	/*���ӵ�FD*/
	int mFD;
	/*�Ự���� �������Ϊһ���ỰID*/
	int mIndex;
	/*����session����û�б����κ�NetWork��NetInterfaceָ����Ϣ,�����Ҫsession������Ϣ�Ľӿ�,���Լ̳к����߼����Լ�ʵ��,���õײ�ӿ�*/
public:
	BaseSession():mFD(-1), mIndex(-1){};
	virtual ~BaseSession(){};

	/*�ѽ�������*/
	virtual void Connected() = 0;
	/*�ѶϿ�����*/
	virtual void Disconnected() = 0;
	/*����Ϣ*/
	virtual void OnMsg(const NetMessage* nmsg, int msgType = 0) = 0;

	void SetFD(int fd) { mFD = fd; }
	void SetIndex(int index){ mIndex = index; }
	int GetFD() const { return mFD; }
	int GetIndex() const { return mIndex; }
	bool IsAttach() const { return mIndex >= 0; }
};
