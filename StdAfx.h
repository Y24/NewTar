#pragma once
#define _CRT_SECURE_NO_WARNINGS

//������ļ�����
#define MAX_FILE_COUNT  1024
//���·���ַ�����
#define MAX_PATH   260
//�ļ�ͷ
struct FileHead
{
	unsigned int FileCount;//�ļ�����
	unsigned int FileLen[MAX_FILE_COUNT];//�ļ���С
	char FileName[MAX_FILE_COUNT][MAX_PATH];//�ļ���
};
