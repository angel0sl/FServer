/***********************************************************************
*FileName	:  Singleton
*Author		:  fz
*Date		:  2016.3.8
*Description:  ����(�ο�kbe),ʹ�÷���,�̳к���.cpp��ִ�к�INIT_SINGLETON(A)����
************************************************************************/

#pragma once
#include <iostream>
template <class T>
class Singleton
{
	static T* mInstance;
public:
	Singleton()
	{
#if defined( _MSC_VER ) && _MSC_VER < 1200
		int offset = (int)(T*)1 - (int)(Singleton <T>*)(T*)1;
		mInstance = (T*)((int)this + offset);
#else
		mInstance = static_cast<T*>(this);
#endif
	}
	~Singleton(){ mInstance = NULL; }

	static T* GetInstance()
	{
		if (mInstance == NULL)
			mInstance = new T;
		return mInstance;
	}
	static T& GetInstanceRef(){ return *GetInstance(); }
};

#define InitSingleton(TYPE) template <> TYPE * Singleton<TYPE>::mInstance = NULL;

/*
template <class T>
class Singleton
{
T* mSingleton;
public:
Singleton() :mSingleton(0){}
~Singleton(){ delete mSingleton; }
static T& GetSingleton()
{
if (!mSingleton)
mSingleton = new T;
return (*mSingleton);
}
};*/