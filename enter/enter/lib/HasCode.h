#pragma once  

#include <string>  
/**
* ����������ĸת��Ϊ��д
*/
#define _toupper(__c) ((__c) & ~32)
/**
* ����������ĸת��ΪСд
*/
#define _tolower(__c) ((__c) | 32) 
unsigned long cryptTable[0x500];

void prepareCryptTable();

unsigned long HashString(const std::string& key, unsigned long dwHashType);