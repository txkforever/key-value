#pragma once
#include<string>
#include"bplustree.h"

template<typename T>
struct SqlData
{
	T value;
};

struct MetaSql
{
	std::string key;
	std::string value_str;
	int value_int;
};

class TSql {

public:
	TSql();
	TSql(const std::string& sql_path);
public:
	/**
		�����������ݿ�
		������base_path ���ݴ��·��
		����ֵ���򿪳ɹ�����true�����򷵻�false
	*/
	bool open(const std::string& sql_path);
	/*
		�������ر����ݿ�
	*/
	void close();
	
	std::string getStr(const std::string& key)const;
	
	template<typename T>
	T get(const std::string& key);
	
	template<typename T>
	void TSql::set(const std::string& key, const T& value);

	template<typename T>
	int getType()const;

public :
	/*
		���������ݿ�Ĭ����������������޸�
	*/
	static const int DATA_MAX_COUNT = 10240;

private :
	MetaSql m_datas[TSql::DATA_MAX_COUNT];
	bplus_tree* m_pTree;
	/*
		���������ݴ��·��
	*/
	std::string m_sqlPath;
};
