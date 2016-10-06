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
		概述：打开数据库
		参数：base_path 数据存放路径
		返回值：打开成功返回true，否则返回false
	*/
	bool open(const std::string& sql_path);
	/*
		概述：关闭数据库
	*/
	void close();
	/*
		概述：根据key返回string的值
	*/
	std::string getStr(const std::string& key)const;
	/*
		概述：返回key对应的int型value
	*/
	int getInt(const std::string& key)const;
	/*
		概述：设置key-value（string）如果存在key则覆盖对应的string的值
	*/
	void setStr(const std::string& key,const std::string& value);
	/*
		概述：设置key-value（int）如果存在key则覆盖对应的int的值
	*/
	void setInt(const std::string& key,const int& value);

public :
	/*
		概述：数据库默认最大数据量，可修改
	*/
	static const int DATA_MAX_COUNT = 10240;

private :
	SqlData m_datas[TSql::DATA_MAX_COUNT];
	
	/*
		概述：数据存放路径
	*/
	std::string m_sqlPath;
};
