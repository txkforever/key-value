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
		概述：打开数据库
		参数：base_path 数据存放路径
		返回值：打开成功返回true，否则返回false
	*/
	bool open(const std::string& sql_path);
	/*
		概述：关闭数据库
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
		概述：数据库默认最大数据量，可修改
	*/
	static const int DATA_MAX_COUNT = 10240;

private :
	MetaSql m_datas[TSql::DATA_MAX_COUNT];
	bplus_tree* m_pTree;
	/*
		概述：数据存放路径
	*/
	std::string m_sqlPath;
};
