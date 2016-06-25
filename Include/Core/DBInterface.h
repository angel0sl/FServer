/***********************************************************************
*FileName	:  DBInterface
*Author		:  fz
*Date		:  2016.1.13
*Description:  mysqlpp�ķ�װ��,ֱ�Ӽ̳м���
************************************************************************/
#pragma once
#include <string>
#include <mysql++.h>

typedef mysqlpp::SQLQueryParms    SqlParams;
typedef mysqlpp::SQLTypeAdapter   SqlType;
typedef mysqlpp::StoreQueryResult SqlResult;		// select
typedef mysqlpp::SimpleResult	  SqlExcuteResult;	// update delete insert
typedef mysqlpp::Row              SqlRow;
typedef mysqlpp::sql_int_unsigned SqlUInt32;
typedef mysqlpp::sql_bigint_unsigned SqlBigInt;

#define RECONNECT_COUNT 10	//�������ݿ�Ĵ���,�������Ϊ1����

/*���ݿ�ʵ��������*/
class DBInterface
{
	std::string m_name;					//���ݿ���
	std::string m_user;					//��¼���û���
	std::string m_password;				//��¼������
	std::string m_host;					//���ݿ��ַ
	unsigned int m_port;				//���ݿ�˿�
	mysqlpp::Connection m_connection;	//���ݿ�����
public:
	DBInterface();
	virtual~DBInterface();

	/*��ʼ�����ݿ��������*/
	void Init(const std::string& name, const std::string& user, const std::string& password, const std::string& host, unsigned int port);
	/*�������ݿ�*/
	bool Connect();
	/*�Ͽ����ݿ�����*/
	void DisConnect();
	/*��������*/
	bool ReConnect(int count = 0);
	/*SQL����*/
	bool SqlExcute(const char* sql, SqlParams& sqlParams, SqlResult& sqlResult);//SELECT
	bool SqlExcute(const char* sql, SqlParams& sqlParams, SqlExcuteResult& sqlResult);//INSERT UPDATE DELETE
	
};
