#include "GCNetLogic.h"
#include "GameCenterApp.h"
#include "ProtoMessage.h"
#include "AppManager.h"

GCNetLogic::GCNetLogic()
{
}

GCNetLogic::~GCNetLogic()
{
}

void GCNetLogic::OnMessage(const NetPacket& packet)
{
	NetMessage* nmsg = (NetMessage*)(packet.mBody);

	auto msgType = theProtoMsgMgr->GetMsgType(nmsg);
#ifdef DEBUG
	LOG(INFO) << "msg " << msgType;
#endif
	switch (msgType)
	{
	case Msg_RegisterApp:
		OnRegisterApp(nmsg, packet.mFD);
		break;
	case Msg_UnRegisterApp:
		OnUnRegisterApp(nmsg);
		break;
	default:
		NetInterface::OnMessage(packet, msgType);
		break;
	}
}

void GCNetLogic::OnRegisterApp(const NetMessage* nmsg, int fd)
{
	MsgRegisterApp msg;
	if (!MsgFromBytes(nmsg, msg))
		return;
	auto app = theAppMgr->AddObject(msg.app_id());
	if (app == NULL)
		return;//���ظ���,��ʱ���Ͽ�����,�����б�Ҫ

	app->SetFD(fd);
	app->SetAppID(msg.app_id());
	app->SetAppType(msg.app_type());
	AttachSession(app);

	MsgRespondApp res;
	res.mutable_base()->set_type(Msg_RespondApp);
	res.mutable_base()->set_result(1);
	app->SendToApp(&res);

	LOG(INFO) << "RegisterApp" << LogValue("apptype", msg.app_type()) << LogValue("appid", msg.app_id());
}

void GCNetLogic::OnUnRegisterApp(const NetMessage* nmsg)
{
	MsgUnRegisterApp msg;
	if (!MsgFromBytes(nmsg, msg))
		return;
	auto app = theAppMgr->GetObject(msg.app_id());
	if (!app)
		return;
	OnDisconnect(app->GetIndex());
	theAppMgr->RemoveObject(app->GetAppID());

	LOG(INFO) << "UnRegisterApp" << LogValue("apptype", msg.app_type()) << LogValue("appid", msg.app_id());
}