#pragma once
#pragma once


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
//#include <error.h>
#include <direct.h>
using namespace std;







class UnPack_file
{
private:
	FileHead fh;//�ļ�ͷ
	char ObjectFilePathName[MAX_PATH];//���ɴ���ļ�λ�ü�����
	//char OutputPath[MAX_PATH]; //��ѹ���ļ����λ��


public:
	UnPack_file(void);
	~UnPack_file(void);

	void DoUnCAB(char *CabFilePathName,char*OutputPath);


private:
	//��ʾ������ļ���Ϣ
	void printCAB();
	//�����ļ���
	void CheckTargetPath(string targetPath);
};