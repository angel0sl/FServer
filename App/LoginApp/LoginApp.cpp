#include "LoginApp.h"
#include "ConfigManager.h"

InitSingleton(LoginApp)
LoginApp::LoginApp() :
mNetLogic(NULL),
mBCSession(NULL),
mLoginLevel(ACCOUNT_LEVEL_DEFAULT)
{
}

LoginApp::~LoginApp()
{
	Clear();
}

bool LoginApp::Init()
{
	if (!theConfigMgr->LoadingConfig())
	{
		LOG(ERROR) << "Loading config failed!";
		return false;
	}
	auto cfg = theConfigMgr->GetServerCfg(theConfigMgr->GetAppID());
	if (!cfg)
	{
		LOG(ERROR) << "Server config error!";
		return false;
	}

	mNetLogic = new LoginNetLogic;
	/*����ֱ�Ӻ͵�½�ҹ���Ϊ��ֹ����Ƶ������Ч��½,���Ծ����࿪����IO�߳�Ӧ�ԣ�һ�㵥��LoginApp�Ѿ��㹻��������������޸�Ϊ���LoginApp����ӦҲҪ����Client�ĵ�¼����*/
	if (!mNetLogic->Init(cfg->serverPort, MAX_CONNECT_COUNT, 8))
	{
		LOG(ERROR) << "NetLogic init failed!";
		return false;
	}
	auto bcCfg = theConfigMgr->GetServerCfg(ESAI_BaseCenterApp);
	if (!bcCfg)
	{
		LOG(ERROR) << "BaseCenterApp config error!";
		return false;
	}
	mBCSession = new BCSession;
	if (!mBCSession->Connect(mNetLogic, bcCfg->serverIP, bcCfg->serverPort, RECONNECT_MSEC))
		return false;
	/*���õ�ǰ���Ե�¼���ʺŵȼ� ��ʱ�������ƿ������еȼ�*/
	SetLoginLevel(ACCOUNT_LEVEL_ALL /*ACCOUNT_LEVEL_ADMINISTRATOR | ACCOUNT_LEVEL_GAMEMASTER*/);
	return true;
}

void LoginApp::Clear()
{
	mLoginLevel = ACCOUNT_LEVEL_DEFAULT;
	if (mNetLogic)
	{
		delete mNetLogic;
		mNetLogic = NULL;
	}
	if (mBCSession)
	{
		delete mBCSession;
		mBCSession = NULL;
	}
}

bool LoginApp::StartUp()
{
	if (!mNetLogic)
		return false;
	mNetLogic->GetNetWork()->StartNet();
	return true;
}

void LoginApp::ShutDown()
{
	if (mNetLogic)
		mNetLogic->GetNetWork()->CloseNet();
	Clear();
}

bool LoginApp::CheckLoginLevel(short lvl)
{
	return mLoginLevel & lvl;
}