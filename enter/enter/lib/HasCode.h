#pragma once  

#include <string>  
/**
* 概述：将字母转换为大写
*/
#define _toupper(__c) ((__c) & ~32)
/**
* 概述：将字母转换为小写
*/
#define _tolower(__c) ((__c) | 32) 
unsigned long cryptTable[0x500];

void prepareCryptTable();

unsigned long HashString(const std::string& key, unsigned long dwHashType);