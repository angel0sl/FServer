#pragma once
#include "LoginApp.h"//ע��˳��,������WinDump.hǰ
#ifdef WIN32
#include "WinDump.h"
#endif

#include <vector>
void fun1(int p1, int p2)
{
	&p1;//-		&p1	0x000000bc7cf7fa10 {3}	int *
	&p2;//-		&p2	0x000000bc7cf7fa18 {5}	int *
	p2;//5
	int i = 0;
	i++;
}
char* fun2()
{
	char a[] = "hesad111111111111123";
	return a;
}
class AA
{
	bool ma;
public:
	AA(){};
	~AA(){};

	bool ba(){ return ma; }
};

class BB
{
	bool mb;
public:
	BB(){};
	~BB(){};

	bool bb(){ return mb; }
};

class CC : public BB, public AA
{
public:
	CC(){};
	~CC(){};
};

int main(int argc, char* argv[])
{
#ifdef WIN32
	WinDump wDump("LoginApp");
#endif
	if (!theConfigMgr->ParseCommond(argc, argv))
		return false;
	FLAGS_max_log_size = 100;/*log�ļ���СMB*/
	FLAGS_stop_logging_if_full_disk = false;/*����д��־��������*/ // �ݲ�����
	FLAGS_logbufsecs = 0;/*ʵʱ���*/
	FLAGS_colorlogtostderr = true;
	google::InitGoogleLogging("");
	google::SetLogDestination(google::GLOG_ERROR, "../Binary/Log/Error");
	google::SetLogDestination(google::GLOG_INFO, "../Binary/Log/Info");
	google::SetStderrLogging(google::GLOG_INFO);
	std::stringstream ss;
	ss << "LoginApp" << theConfigMgr->GetAppID() << "-";
	google::SetLogFilenameExtension(ss.str().c_str());//�����ļ�����չ
	
	LOG(INFO) << "info test";
	LOG(ERROR) << "error test";


	char a = 64;
	int b = 0;
	a <<= 1;//Խ��,����
	b = a;
	a >>= 1;
	b = a;

	int c[2] = { 0, 0 };
	int *p = c;
	*p++ = 1;//c[0]=1,*p++ = c[1]

	int oneCnt = 0;
	for (int i = 0; i < 2006; ++i)
	{
		if (i % 10 == 1)
			oneCnt++;
		if (i / 10 % 10 == 1)
			oneCnt++;
		if (i / 100 % 10 == 1)
			oneCnt++;
		if (i / 1000 % 10 == 1)
			oneCnt++;
	}

	int d = 3, e = 4, f = 5;
	int g = d++ > --e&&f--&&++f;// d�����к�++ ,f-- ++f������,����true

	int j = 3;
	int k = 5;
	&k;
	&j;
	fun1(j, k);

	//��ʵ�ܺ����,���̳е��Ⱥ�˳��,�ȼ̳е���ռ�õ�ַ��ǰ,��̳е��࿿��,
	//��new�ĵ�ַ���ػ��࿪ʼ���,���������ʼ��ַӦ�ú��׸��̳еĻ����ַ��ͬ,֮���Ǻ����Ļ����ַ
	CC* cc = new CC;
	AA* ca = (AA*)cc;
	BB* cb = (BB*)cc;

	//���˷�б��n,���������������?
	char* p1 = (char*)malloc(8);
	char p2[5];
	char* str = "Hi world";
	strcpy(p1, str);
	strcpy(p2, str);

	char* p3 = fun2();
	char* str1 = "hello world";
	strcpy(p3, str1);

	std::vector<int> veci;
	for (int i = 0; i < 10; i++)
		veci.push_back(i);

	bool del = true;
	for (auto it = veci.begin(); it != veci.end();)
	{
		it = veci.erase(it);
	}


	if (theLoginApp->Init())
		theLoginApp->StartUp();
	theLoginApp->ShutDown();

	return 0;
}