#include <stdio.h>
#include"TSql.h"
#include "HasCode.h"
#include "bplustree.h"

template<typename T>
int TSql::getType()const
{
	return typeid(T) == typeid(int) ? 0 : 1;
}

template<typename T>
void TSql::set(const std::string& key, const T& value)
{
	unsigned long iKey = HashString(key, 1);
	int type = getType<T>();
	SqlData<T>* pItem = static_cast<SqlData<T>*>(bplus_tree_get(m_pTree, iKey, type));

	if (pItem == nullptr)
	{
		bplus_tree_put(m_pTree, iKey, nullptr, type);

		pItem = new SqlData<T>();
		pItem->value = value; 
		bplus_tree_put(m_pTree, iKey, pItem, type);
	}
	else
	{
		pItem->value = value;
	}
}

template <typename T>
T TSql::get(const std::string& key)
{
	unsigned long iKey = HashString(key, 1);
	int type = getType<T>();
	SqlData<T>* pItem = static_cast<SqlData<T>*>(bplus_tree_get(m_pTree, iKey, type));

	if (pItem == nullptr)
	{
		return T();
	}
	else
	{
		return pItem->value;
	}
}


bool TSql::open(const std::string& sqlPath)
{
	FILE* fp = nullptr;
	m_sqlPath = sqlPath;

	fopen_s(&fp, sqlPath.c_str(), "r");
	if (fp == nullptr)
	{
		return true;
	}

	while (!feof(fp))
	{
		unsigned long key = 0;
		fread_s(&key, sizeof(unsigned long), sizeof(unsigned long), 1, fp);

		if (key == 0)
		{
			continue;
		}

		int type = 0;
		fread_s(&type, 1, 1, 1, fp);

		if (type == 0)
		{
			int value = 0;
			fread_s(&value, sizeof(int), sizeof(int), 1, fp);

			SqlData<int>* pItem = new SqlData<int>();
			pItem->value = value;

			bplus_tree_put(m_pTree, key, pItem, type);
		}
		else if (type == 1)
		{
			int len = 0;
			fread_s(&len, 1, 1, 1, fp);
			char* value = new char[len + 1];
			fread_s(value, len, len, 1, fp);
			value[len] = 0;

			SqlData<std::string>* pItem = new SqlData<std::string>();
			pItem->value = std::string(value);
			delete[] value;
//			bplus_tree_put(m_pTree,key,pItem)
			bplus_tree_put(m_pTree, key, pItem, type);
		}
	}

	fclose(fp);

	return true;
}

void TSql::close()
{
	FILE* fp = nullptr;

	fopen_s(&fp, m_sqlPath.c_str(), "w");
	if (fp == nullptr)
	{
		return;
	}

	struct bplus_leaf *leaf = (struct bplus_leaf *)m_pTree->head[0];
	if (leaf != NULL)
	{
		while (leaf != NULL)
		{
			for (int j = 0; j < leaf->entries; ++j)
			{
				fwrite(&leaf->key[j], sizeof(unsigned long), 1, fp);
				fwrite(&leaf->datatype[j], 1, 1, fp);

				if (leaf->datatype[j] == 0) // int
				{
					SqlData<int>* pItem = reinterpret_cast<SqlData<int>*>(leaf->data[j]);
					fwrite(&pItem->value, sizeof(int), 1, fp);
				}
				else if (leaf->datatype[j] == 1) // string
				{
					SqlData<std::string>* pItem = reinterpret_cast<SqlData<std::string>*>(leaf->data[j]);
					int len = pItem->value.length();
					fwrite(&len, 1, 1, fp);
					fwrite(pItem->value.c_str(), len, 1, fp);
				}
			}
			leaf = leaf->next;
		}
	}

	fclose(fp);
}