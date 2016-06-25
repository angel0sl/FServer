#include "LoginNetLogic.h"
#include <Guid.h>
#include "ProtoMessage.h"
#include "LoginApp.h"
#include "ClientManager.h"

LoginNetLogic::LoginNetLogic()
{
}

LoginNetLogic::~LoginNetLogic()
{
}

void LoginNetLogic::OnMessage(const NetPacket& packet)
{
	NetMessage* nmsg = (NetMessage*)(packet.mBody);

	auto msgType = theProtoMsgMgr->GetMsgType(nmsg);
#ifdef DEBUG
	LOG(INFO) << "msg " << msgType;
#endif
	switch (msgType)
	{
	case Msg_VerifyAccountReq:
		OnRegisterClient(nmsg, packet.mFD);
		break;
	case Msg_VerifyAccountRes:
		OnUnRegisterClient(nmsg);
		break;
	default:
		NetInterface::OnMessage(packet, msgType);
		break;
	}
}

void LoginNetLogic::OnRegisterClient(const NetMessage* nmsg, int fd)
{
	MsgVerifyAccountReq msg;
	if (!MsgFromBytes(nmsg, msg))
		return;
	//��֤�汾
	msg.version();
// 	auto it = theClientMgr->GetClientByAccount(msg.account());
// 	if (it)//������֤����,�����֤ǰ����������
// 		return;
// 	//���ݷ�������������һ����ʱKey,���ڴ���ɹ��󷵻�LoginApp
// 	int verifyKey = 0;
// 	do 
// 	{
// 		verifyKey = theGuid->Generate32Guid(ESAT_Login);
// 		it = theClientMgr->AddObject(verifyKey);
// 	} while (it == NULL);

	auto it = theClientMgr->AddObject(msg.account());
	if (it)//������֤����,�����֤ǰ����������
		return;
	it->SetFD(fd);//�����м���
//	it->SetClientID(verifyKey);
	it->SetAccount(msg.account());
	AttachSession(it);//����ײ����Ӱ�
	SMsgVerifyAccountReq bcMsg;
	bcMsg.mutable_base()->set_type(Msg_VerifyAccountReq);
	bcMsg.set_account(msg.account());
	bcMsg.set_password(msg.password());
	bcMsg.set_dev_type(msg.dev_type());
	bcMsg.set_dev_key(msg.dev_key());
	bcMsg.set_pf_type(msg.pf_type());
	bcMsg.set_verify_key(0);//������֤Key��򵥵����ɹ�����һ��ʱ�����λ�� + ĳ�����ֵ,����,���õ����ظ�,ÿ���˶���һ��.��ʹ�ظ�Ҳ����ν
	theLoginApp->GetBCSession()->SendToBC(&bcMsg);
}

void LoginNetLogic::OnUnRegisterClient(const NetMessage* nmsg)
{
	SMsgVerifyAccountRes msg;
	if (!MsgFromBytes(nmsg, msg))
		return;
	auto it = theClientMgr->GetObject(msg.account());
	if (!it)
		return;
	MsgVerifyAccountRes cMsg;
	cMsg.mutable_base()->set_type(Msg_VerifyAccountRes);
	cMsg.set_base_ip(msg.base_ip());
	cMsg.set_base_port(msg.base_port());
	cMsg.set_base_key(msg.base_key());
	it->SendToClient(&cMsg);
	//���Ǽ���һ��ɾ������,���ӳ�ɾ��
// 	OnDisconnect(it->GetIndex());
// 	theClientMgr->RemoveObject(it->GetAccount());
}