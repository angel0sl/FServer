#pragma once
#include "CubbyApp.h"
#ifdef WIN32
#include "WinDump.h"
#endif

int main(int argc, char* argv[])
{
#ifdef WIN32
	WinDump wDump("CubbyApp");
#endif
	if (!theConfigMgr->ParseCommond(argc, argv))
		return false;
	FLAGS_max_log_size = 100;/*log�ļ���СMB*/
	FLAGS_stop_logging_if_full_disk = false;/*����д��־��������*/ // �ݲ�����
	FLAGS_logbufsecs = 0;/*ʵʱ���*/
	FLAGS_colorlogtostderr = true;
	google::InitGoogleLogging("");
	google::SetLogDestination(google::GLOG_ERROR, "./Log/Error");
	google::SetLogDestination(google::GLOG_INFO, "./Log/Info");
	google::SetStderrLogging(google::GLOG_INFO);
	std::stringstream ss;
	ss << "CubbyApp" << theConfigMgr->GetAppID() << "-";
	google::SetLogFilenameExtension(ss.str().c_str());//�����ļ�����չ

	LOG(INFO) << "info test";
	LOG(ERROR) << "error test";

	if (theCubbyApp->Init())
		theCubbyApp->StartUp();
	theCubbyApp->ShutDown();

	return 0;
}