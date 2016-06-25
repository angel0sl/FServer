// proto-build.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <google/protobuf/compiler/command_line_interface.h>
#include <google/protobuf/compiler/cpp/cpp_generator.h>
#include <google/protobuf/stubs/common.h>

void CompileAllProtoFile(google::protobuf::internal::scoped_array<const char*>& param, google::protobuf::compiler::CommandLineInterface& cli)
{
	char szFile[_MAX_PATH + 1] = "";
	sprintf_s(szFile, sizeof(szFile) - 1, "*.proto");

	WIN32_FIND_DATA xFindData;
	HANDLE hFile = FindFirstFile(szFile, &xFindData);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		do
		{
			char szFileName[_MAX_PATH];
			sprintf_s(szFileName, _MAX_PATH - 1, "%s", xFindData.cFileName);
			param[2] = szFileName;

			int nResult = cli.Run(3, param.get());
			if (nResult == 0)
			{
				std::cout << nResult << " : ���� [" << xFindData.cFileName << " ] ���!" << std::endl;
			}
			else
			{
				std::cout << nResult << " : ���� [" << xFindData.cFileName << " ] ʧ��!" << std::endl;
			}

		} while (FindNextFile(hFile, &xFindData));
		FindClose(hFile);
	}
}

void CompileProtoFile(std::string& strFile, google::protobuf::internal::scoped_array<const char*>& param, google::protobuf::compiler::CommandLineInterface& cli)
{
	char szFileName[_MAX_PATH];
	sprintf_s(szFileName, _MAX_PATH - 1, "%s", strFile.c_str());
	param[2] = szFileName;

	int nResult = cli.Run(3, param.get());
	if (nResult == 0)
	{
		std::cout << nResult << " : ���� [" << strFile.c_str() << " ] ���!" << std::endl;
	}
	else
	{
		std::cout << nResult << " : ���� [" << strFile.c_str() << " ] ʧ��!" << std::endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	google::protobuf::internal::scoped_array<const char*> param(new const char*[3]);
	param[0] = "-I=.";
	param[1] = "--cpp_out=.";//���Ŀ¼

	google::protobuf::compiler::CommandLineInterface cli;
	cli.AllowPlugins("protoc-");

	google::protobuf::compiler::cpp::CppGenerator cpp_generator;
	cli.RegisterGenerator("--cpp_out", &cpp_generator,
		"Generate C++ header and source.");


	std::cout << "**********************************************************\r\n";
	std::cout << "                        ˵��\r\n";
	std::cout << "   ����������proto�ļ���(*Ϊ���������ļ�)\r\n";
	std::cout << "**********************************************************\r\n";

	std::string strCommand;
	while (true)
	{
		std::cout << ">>";
		std::cin >> strCommand;
		if (strCommand.compare("exit") == 0)
		{
			break;
		}

		strCommand += ".proto";
		if (strCommand == "*.proto")
		{
			CompileAllProtoFile(param, cli);
		}
		else
		{
			CompileProtoFile(strCommand, param, cli);
		}
	}

	return 0;
}

