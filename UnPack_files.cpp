#include "StdAfx.h"
#include "UnPack_files.h"


UnPack_file::UnPack_file(void)
{
	memset(&fh, 0x0, sizeof(fh));
	memset(ObjectFilePathName, 0x0, sizeof(ObjectFilePathName));
}


UnPack_file::~UnPack_file(void)
{
}




//���(Ϊ�˽�ʡʱ�䲻д��������,���Ը��������Լ����)
void UnPack_file::DoUnCAB(char *CabFilePathName, char*OutputPath)
{
	FILE *pCAB = NULL;
	FILE *pWork = NULL;
	long off = 0;
	//cout << "off: " << off << endl;
	off = sizeof(fh);
	//cout << "off: " << off << endl;
	pCAB = fopen(CabFilePathName, "rb");


	//���ļ�ͷ
	fseek(pCAB, -off, SEEK_END);
	memset(&fh, 0x0, sizeof(fh));
	fread(&fh, sizeof(fh), 1, pCAB);
	fseek(pCAB, 0, SEEK_SET);

	//printCAB();


	//����������ļ��ŵ���ǰĿ¼��
	for (int i = 0; i < fh.FileCount; i++)
	{
		unsigned char *pTmpData = NULL;
		pTmpData = new unsigned char[fh.FileLen[i]];
		fread(pTmpData, fh.FileLen[i], 1, pCAB);
		//ֻȡ�ļ���,��Ҫ�����ļ���·����
		char tmpFileName[MAX_PATH];
		string aaa;
		cout << "fh.FileName: " << fh.FileName[i] << endl; //����
		aaa.assign(fh.FileName[i], strlen(fh.FileName[i]));
		char ptmpC[MAX_PATH];
		strcpy(ptmpC, aaa.c_str());
		cout << "ptmpC:" << ptmpC << endl;

		memset(tmpFileName, 0x0, sizeof(tmpFileName));
		strcpy(tmpFileName, ptmpC);
		cout << "tmpFileName: " << tmpFileName << endl;
		//ȡCAB�ļ�·��
		char tmpPathName[MAX_PATH];
		memset(tmpPathName, 0x0, sizeof(tmpPathName));
		strcpy(tmpPathName, OutputPath);
		cout << "CabFilePathName" << CabFilePathName << endl;
		//char* tmpC = tmpPathName + strlen(tmpPathName);
		//while ('\\' != *tmpC)
		//{
		//	tmpC--;
		//}
		//tmpC++;
		//*tmpC = '\0';
		strcat(tmpPathName, tmpFileName);
		cout << "OutputPath: " << OutputPath << endl;
		cout << "tmpPathName: " << tmpPathName << endl;
		pWork = fopen(tmpPathName, "wb");
		if (pWork == NULL)
		{
			CheckTargetPath(tmpPathName);
			pWork = fopen(tmpPathName, "wb");
		}
		fwrite(pTmpData, fh.FileLen[i], 1, pWork);
		fclose(pWork);
		delete[] pTmpData;
	}


	fclose(pCAB);
}


//��ʾ������ļ���Ϣ
void UnPack_file::printCAB()
{
	cout << "�ļ�����Ϣ����:" << endl;
	cout << "�ļ�����:" << fh.FileCount << endl;
	for (int i = 0; i < fh.FileCount; i++)
	{
		cout << fh.FileName[i] << "\t\t\t\t" << fh.FileLen[i] << "�ֽ�" << endl;
	}
}


//�����ļ���
void UnPack_file::CheckTargetPath(string targetPath)
{
	//Log &log = Log::getLog("main", "CheckTargetPath");
	int e_pos = targetPath.length();
	int f_pos = targetPath.find("\\", 0);
	string subdir;
	do
	{
		e_pos = targetPath.find("\\", f_pos + 2);
		if (e_pos != -1)
		{
			subdir = targetPath.substr(0, e_pos);
			if (_mkdir(subdir.c_str()) == 0)
				printf("creat success %s", subdir.c_str());
			else
				printf("creat fail %s", subdir.c_str());
		}
		f_pos = e_pos;
	} while (f_pos != -1);
}
