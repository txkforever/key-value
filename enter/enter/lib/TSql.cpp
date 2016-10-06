#include <stdio.h>
#include"TSql.h"


bool TSql::open(const std::string& sql_path)
{
	bool flag = true;

	FILE* fp = nullptr;
	this->m_sqlPath = sql_path;

	fopen_s(&fp, sql_path.c_str(), "r");
	if (fp == nullptr)return flag;
	try
	{
		int index = 0;
		while (!feof(fp))
		{
			/*
			* 1.key的长度
			* 2.将key的值取出
			* 3.将key值存入m_datas中
			*/
			int key_len = 0;
			fread_s(&key_len, 1, 1, 1, fp);

			if (key_len == 0)continue;

			char* key = new char[key_len + 1];
			fread_s(key, key_len, key_len, 1, fp);
			key[key_len] = 0;
			m_datas[index].key = std::string(key);
			delete[] key;
			key = nullptr;

			/*
			* 获取key对应的string value，如果有的话
			*/
			int value_str_len = 0;
			fread_s(&value_str_len, 1, 1, 1, fp);

			if (0 != value_str_len)
			{
				char* value_str = new char[value_str_len + 1];
				fread_s(value_str, value_str_len, value_str_len, 1, fp);
				value_str[value_str_len] = 0;
				m_datas[index].value_str = std::string(value_str);
				delete[] value_str;
				value_str = nullptr;
			}

			//key - int
			int value_int = 0;
			fread_s(&value_int, 4, 4, 1, fp);
			m_datas[index].value_int = value_int;

			++index;
		}
		fclose(fp);
		fp = nullptr;
	}
	catch (std::exception e)
	{
		flag = false;
		if (fp != nullptr) {
			fclose(fp);
			fp = nullptr;
		}
	}
	
	return flag;
}
void TSql::close()
{
	FILE* fp = nullptr;

	fopen_s(&fp, m_sqlPath.c_str(), "w");
	if (fp == nullptr)
	{
		return;
	}

	for (int i = 0; i < TSql::DATA_MAX_COUNT; ++i)
	{
		int key_len = m_datas[i].key.length();
		fwrite(&key_len, 1, 1, fp);

		if (key_len == 0)
		{
			continue;
		}

		fwrite(m_datas[i].key.c_str(), key_len, 1, fp);

		int value_len = m_datas[i].value_str.length();
		fwrite(&value_len, 1, 1, fp);

		if (value_len != 0)
		{
			fwrite(m_datas[i].value_str.c_str(), value_len, 1, fp);
		}

		fwrite(&m_datas[i].value_int, 4, 1, fp);
	}

	fclose(fp);
}
std::string TSql::getStr(const std::string& key) const
{
	for (int i = 0; i < TSql::DATA_MAX_COUNT; ++i)
	{
		if (m_datas[i].key == key)
		{
			return m_datas[i].value_str;
		}
	}
	return std::string();
}


void TSql::setStr(const std::string& key, const std::string& value)
{
	for (int i = 0; i < TSql::DATA_MAX_COUNT; ++i)
	{
		if (m_datas[i].key == key)
		{
			m_datas[i].value_str = key;
			return;
		}
		else if (m_datas[i].key.empty())
		{
			m_datas[i].key = key;
			m_datas[i].value_str = value;
			m_datas[i].value_int = 0;
			return;
		}
	}
}

int TSql::getInt(const std::string& key) const
{
	for (int i = 0; i < TSql::DATA_MAX_COUNT; ++i)
	{
		if (m_datas[i].key == key)
		{
			return m_datas[i].value_int;
		}
	}

	return -1;
}

void TSql::setInt(const std::string& key, const int& value)
{
	for (int i = 0; i < TSql::DATA_MAX_COUNT; ++i)
	{
		if (m_datas[i].key == key)
		{
			m_datas[i].value_int = value;
			return;
		}
		else if (m_datas[i].key.empty())
		{
			m_datas[i].key = key;
			m_datas[i].value_str = std::string();
			m_datas[i].value_int = value;
			return;
		}
	}
}

