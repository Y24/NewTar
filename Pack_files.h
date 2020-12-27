#pragma once


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

#include <string>
#include <vector>
#include <fstream>
#include <windows.h>
#include <conio.h>
//#include <error.h>
#include <direct.h>
using namespace std;




class Pack_file
{
private:
	FileHead fh;//�ļ�ͷ
	char ObjectFilePathName[MAX_PATH];//���ɴ���ļ�λ�ü�����
	char ObjectFilefoldPath[MAX_PATH];//��Ҫ������ļ���λ��

	vector<string> filelist; //



public:
	Pack_file(void);
	~Pack_file(void);


	//����ļ�������
	void AddFile();
	//���ô��·��
	void SetfilePath(char * filePutPath);
	//���ô������ļ�
	void SetOutPutFile(char * OutFile);
	//��ȡ�ļ���С(�����Զ����Ʒ�ʽ�򿪵��ļ�ָ��)
	long GetFileSize(FILE *pf);
	//��������ļ�
	void DoMakeCAB();
	//���(Ϊ�˽�ʡʱ�䲻д��������,���Ը��������Լ����)
	//void DoUnCAB(char *CabFilePathName);
	//�õ���Ҫ������ļ�
	void get_filelist(char *foldname);
	//void ReadFile(const char* fileName);
	//void WriteFile(string fileName);

private:
	//��ʾ������ļ���Ϣ
	void printCAB();
	//�����ļ���
	void CheckTargetPath(string targetPath);
};
