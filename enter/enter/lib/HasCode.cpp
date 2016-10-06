
#include "HasCode.h"  


void prepareCryptTable()
{
	//seed Ϊ1048577
	unsigned long seed = 0x00100001, index1 = 0, index2 = 0, i;

	for (index1 = 0; index1 < 0x100; ++index1)//ѭ��256��
	{
		for (index2 = index1, i = 0; i < 5; ++i, index2 += 0x100)//һindex1Ϊ��׼������256��ѭ��5��
		{
			unsigned long temp1, temp2;
			seed = (seed * 125 + 3) % 0x2AAAAB;//2446790
			//ȡseed�������ֽڣ�����������16λ
			temp1 = (seed & 0xFFFF) << 0x10;
			seed = (seed * 125 + 3) % 0x2AAAAB;
			temp2 = (seed & 0xFFFF);
			cryptTable[index2] = (temp1 | temp2);
		}
	}
}

unsigned long HashString(const std::string& key, unsigned long dwHashType)
{
	unsigned char *ckey = (unsigned char *)key.c_str();
	unsigned long seed1 = 0x7FED7FED, seed2 = 0xEEEEEEEE;
	int ch;
	
	while (*ckey != 0)
	{
		//ch = toupper(*ckey++);
		ch = _toupper(*ckey++);
		seed1 = cryptTable[(dwHashType << 8) + ch] ^ (seed1 + seed2);
		seed2 = ch + seed1 + seed2 + (seed2 << 5) + 3;
	}
	return seed1;
}