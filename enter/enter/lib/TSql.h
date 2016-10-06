#pragma once
#include<string>
struct SqlData
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
	/*
		����������key����string��ֵ
	*/
	std::string getStr(const std::string& key)const;
	/*
		����������key��Ӧ��int��value
	*/
	int getInt(const std::string& key)const;
	/*
		����������key-value��string���������key�򸲸Ƕ�Ӧ��string��ֵ
	*/
	void setStr(const std::string& key,const std::string& value);
	/*
		����������key-value��int���������key�򸲸Ƕ�Ӧ��int��ֵ
	*/
	void setInt(const std::string& key,const int& value);

public :
	/*
		���������ݿ�Ĭ����������������޸�
	*/
	static const int DATA_MAX_COUNT = 10240;

private :
	SqlData m_datas[TSql::DATA_MAX_COUNT];
	
	/*
		���������ݴ��·��
	*/
	std::string m_sqlPath;
};
