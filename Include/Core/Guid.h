/***********************************************************************
*FileName	:  Guid
*Author		:  fz
*Date		:  2016.4.9
*Description:  ����Guid
************************************************************************/
#pragma once
#include <Singleton.h>

/*ʱЧΪ2016.1.1��0�����34��315��,�˷�ʧЧʱ��,ֻ�ǳ�����ʱЧ�����������ظ��Ŀ���,������ִ��������������������ID,�滻��ID,��������ʱЧ����*/
#define EPOCH_TIME 1451577600000

#define theGuid Guid::GetInstance()
class Guid : public Singleton<Guid>
{
	int m32Order;
	int m64Order;
public:
	Guid();
	~Guid();
	/*40λʱЧ + 12λkey + 12λ����*/
	unsigned long long Generate64Guid(short key = 0);
	/*8λkey + 23λ���� ע��ʹ�ó���23λ�������нϵ͵ĸ��ʻ��ظ�,����ֻ����һЩ����ID,�����ڶԷ���������ά��,����ֱ������64λID*/
	int Generate32Guid(unsigned char key = 0);
};
