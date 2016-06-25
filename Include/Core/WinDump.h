/************************************************************************
*	@brief		��	Windows������Dump�ļ�
*	@author		��	
*	@date		��	2015-5
************************************************************************/
#pragma once
#ifdef WIN32//_MSC_VER//WIN32
#include <tchar.h>
#include <time.h>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <DbgHelp.h>

using namespace std;

class WinDump
{
public:
	/* Ŀ¼�ļ���ҪԤ�ȴ���,Ĭ��Ϊִ���ļ�ͬ��Ŀ¼,ʵ���ļ�����file+ʱ��Ȼ�����Ϣ���,��ϸ��ExceptionFilter */
	WinDump(char * file, char * dir = "./");
	~WinDump();

	static LONG WINAPI					ExceptionFilter( struct _EXCEPTION_POINTERS * pExceptionInfo );
	static std::stringstream			m_fileDir;
	static std::stringstream			m_fileName;
};

#endif

