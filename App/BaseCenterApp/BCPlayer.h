#pragma once
#include <GPDef.h>
#include <PoolManager.h>

class BCPlayer : public PoolObject
{
	/*����base��AppID*/
	APP_ID mAppID;
	/*guid*/
	unsigned long long mGuid;
public:
	BCPlayer();
	~BCPlayer();

	virtual void OnReset();
};
