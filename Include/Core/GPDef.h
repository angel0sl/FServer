/***********************************************************************
*FileName	:  GPDef
*Author		:  fz
*Date		:  2016.4.9
*Description:  �������Ͷ�����ض���
************************************************************************/
#pragma once
#include <memory>
#include <chrono>
#include <functional>
#include <mutex>
#include <thread>

/*c11 shared_ptr*/
#define GP_PTR std::shared_ptr
/*c11 thread*/
#define GP_THREAD std::thread
/*c11 mutex*/
#define GP_MUTEX std::mutex
/*c11 chrono*/
#define GP_TIME std::chrono
/*c11 function*/
#define GP_FUNC std::function

typedef int	APP_ID;//�����App��ID
typedef int	APP_TYPE;//�����App��Type