/***********************************************************************
*FileName	:  NetDefine
*Author		:  fz
*Date		:  2016.1.17
*Description:  �������ݶ���
************************************************************************/
#pragma once
#include <glog/glog.h>

/*��������*/
struct NetConnect
{
	evutil_socket_t mFD;
	sockaddr_in mAddr;
	unsigned int mIP;
	int mPort;
	bool mCaller;//�Ƿ����ӷ����� true:Client false:Server
};
/*������¼�����*/
enum NetPacketEvent
{
	ENPE_Connected		= 1,	
	ENPE_Disconnect		= 2,
	ENPE_Read			= 3,
	ENPE_Write			= 4,
	ENPE_Broadcast		= 5,
};

/*����� ������ڲ���İ�*/
struct NetPacket
{
	NetPacketEvent mEvent;	//���¼�����
	int mFD;				//socket��fd
	int mIndex;				//
	char mBody[1];			//����ͷ(��Ϣ����)����������
};
/*�������������,��NetPacket��mBody*/
#define NET_PACKET_BASE_LENGTH	sizeof(NetPacketEvent)+sizeof(int)+sizeof(int)

/*������Ϣ ԭʼ����,NetPacket��mBody*/
struct NetMessage
{
	int mLength;	//��Ϣ���� ʵ��NetMessage�ĳ���
	char mMsg[0];	//��Ϣ�� �㳤�ɱ䳤�����飺���ڽṹ���ĩβ,����ռ�ÿռ�,��˶�sizeofû��Ӱ��,����е��������֧��,���Ի���1������  
};
/*��Ϣͷ�ĳ��� NetMessage��mLength*/
#define MSG_HEAD_LENGTH sizeof(int)	
/*��Ϣ��󳤶� ע��,8*1024��һ������ĺ���ֵ,tcp�����鷢�͹��������,����������ӵ�»򶪰��ط����������ɸ�����ӳ�,ʵ�ʴ��������ֵ������ĺܴ�,�������Խ���һЩ�����ļ��ȴ�����,������Ӧ����һЩ����,�����ò���ķ�ʽȥ����*/
#define MSG_MAX_LENGTH 8*1024
/*���糬ʱ���� ����˼��Ϊ2����ʱ��*/
#define NET_TIMEOUT_SECONDS 10