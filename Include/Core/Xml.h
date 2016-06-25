/************************************************************************
*	@file		��	Xml.h
*	@brief		��	tinyxml��װ
*	@author		��	fz
*	@date		��	16.1
************************************************************************/
#pragma once

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

enum XmlAttributeError
{
	XAE_Success,
	XAE_NameError,
	XAE_ValueError,
};

class XmlElement : public rapidxml::xml_node<>
{
public:
	XmlElement();
	~XmlElement();

	/*
	<Address Port="23001">127.0.0.1</Address>
	ͨ��GetNode("Address")�����ڵ�
	ͨ��GetNode("Address")->value()��ȡ127.0.0.1
	ͨ��GetNode("Address")->Attribute("Port")��ȡ23001
	*/
	// ��ȡ�ڵ�
	XmlElement* GetNode( const char *name = 0, std::size_t name_size = 0, bool case_sensitive = true ) const;

	// nameΪ��Ĭ��Ϊ��һ��ͬ���ڵ�
	XmlElement* NextSibling(const char *name = 0, std::size_t name_size = 0, bool case_sensitive = true) const;

	const char* Attribute( const char* name ) const;
	const char* Attribute( const char* name, int* iVal ) const;
	const char* Attribute( const char* name, double* dVal ) const;
};

class XmlDocument : public rapidxml::xml_document<>
{
public:
	XmlDocument();
	~XmlDocument();

	// �����ļ�
	void LoadFile( const char* szFileName );

	// ����Ԫ��
	XmlElement* FirstChildElement( const char *name = 0, std::size_t name_size = 0, bool case_sensitive = true ) const;

private:
	rapidxml::file<> * pFile;
};