
#include "StdAfx.h"
#include "Pack_files.h"


Pack_file::Pack_file(void)
{
	memset(&fh, 0x0, sizeof(fh));
	memset(ObjectFilePathName, 0x0, sizeof(ObjectFilePathName));
}


Pack_file::~Pack_file(void)
{
}
void Pack_file:: SetfilePath(char * filePutPath)
{
	strcpy(ObjectFilefoldPath, filePutPath);
}


//�����ļ����µ��ļ����б�(����Ƕ���ļ���)
void Pack_file::get_filelist(char *foldname)
{
	HANDLE hFind;
	WIN32_FIND_DATAA fileData;
	string line;
	char fn[MAX_PATH];
	char tmpfn[MAX_PATH];
	strcpy_s(fn, foldname);
	


	//��Ҫ���ļ��������ַ������д���
	if (fn[strlen(fn) - 1] != '\\')
	{
		strcat_s(fn, "\\");
	}


	//����˳�򣬴�ʱfn�Ѽ���"\\"
	strcpy(tmpfn, fn);
	//����*�����
	strcat_s(fn, "*");


	hFind = FindFirstFileA(fn, &fileData);
	FindNextFile(hFind, &fileData);
	while (FindNextFile(hFind, &fileData))
	{
		//���ɨ�赽�ĵ�ǰΪ�ļ���
		if (fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (fileData.cFileName[0] != '.')
			{
				char szFile[MAX_PATH];
				strcpy_s(szFile, tmpfn);
				strcat_s(szFile, fileData.cFileName);
				get_filelist(szFile);
			}
		}
		//ɨ�赽�ļ�
		else
		{
			line = (string)tmpfn;
			line += fileData.cFileName;
			/*if (line.find(".h",0)!=string::npos)
			{
			filelist.push_back(line);
			}
			else
			{
			continue;
			}*/
			filelist.push_back(line);
		}
		//cout<<line<<endl;
	}
}


//����ļ�������
void Pack_file::AddFile()
{	
	vector<string>::iterator itemFileName;
	//���Ҫ������ļ�
	for (itemFileName = filelist.begin(); itemFileName < filelist.end(); itemFileName++)
	{

		if (fh.FileCount >= MAX_FILE_COUNT - 1)
		{
			cout << "���֧��" << MAX_FILE_COUNT << "���ļ�" << endl;
			return;
		}
		strcpy_s(fh.FileName[fh.FileCount], (*itemFileName).c_str());
		fh.FileCount++;
	}

}


//���ô������ļ�
void Pack_file::SetOutPutFile(char * OutFile)
{
	memset(ObjectFilePathName, 0x0, sizeof(ObjectFilePathName));
	strcpy_s(ObjectFilePathName, OutFile);
}


//��ȡ�ļ���С(�����Զ����Ʒ�ʽ�򿪵��ļ�ָ��)
long Pack_file::GetFileSize(FILE *pf)
{
	//ָ���Ƶ��ļ�β
	fseek(pf, 0,/*SEEK_END*/ 2);
	return ftell(pf);
}


//��������ļ�
void Pack_file::DoMakeCAB()
{
	if (fh.FileCount < 1)
	{
		cout << "û���ļ���ӵ����" << endl;
		return;
	}
	if (strlen(ObjectFilePathName) < 1)
	{
		cout << "û��ָ������ļ����λ��" << endl;
		return;
	}


	FILE *pOutFile = NULL;
	FILE *pWorkFile = NULL;


	//��ȡ�����ļ���С
	for (int i = 0; i < fh.FileCount; i++)
	{
		pWorkFile = fopen(fh.FileName[i], "rb");
		if (NULL == pWorkFile)
		{
			cout << "�ļ�:" << fh.FileName[i] << "�޷���ȡ[" << strerror(errno) << "]" << endl;
			return;
		}
		fh.FileLen[i] = GetFileSize(pWorkFile);
		fclose(pWorkFile);
	}


	//����Ƿ��ж�Ӧ���ļ���
	CheckTargetPath(ObjectFilePathName);
	//��ʼ�ϲ�д�ļ�
	pOutFile = fopen(ObjectFilePathName, "wb");
	if (NULL == pOutFile)
	{
		cout << "����ļ�����ʧ��[" << strerror(errno) << "]" << endl;
		return;
	}

	
	//д����ļ�
	for (int i = 0; i < fh.FileCount; i++)
	{
		unsigned char *pTmpData = NULL;
		//cout << "fh.FileName: " << fh.FileName[i] << endl;
		pWorkFile = fopen(fh.FileName[i], "rb");
		if (NULL == pWorkFile)
		{
			cout << "�ļ�:" << fh.FileName[i] << "�޷���ȡ[" << strerror(errno) << "]" << endl;
			fclose(pWorkFile);
			fclose(pOutFile);
			return;
		}
		pTmpData = new unsigned char[fh.FileLen[i]];
		fread(pTmpData, fh.FileLen[i], 1, pWorkFile);
		if (ferror(pWorkFile))
		{
			cout << "�ļ�:" << fh.FileName[i] << "�޷���ȡ[" << strerror(errno) << "]" << endl;
			fclose(pWorkFile);
			fclose(pOutFile);
			return;
		}
		fwrite(pTmpData, fh.FileLen[i], 1, pOutFile);
		if (ferror(pOutFile))
		{
			cout << "�ļ�:" << ObjectFilePathName << "�޷�д��[" << strerror(errno) << "]" << endl;
			fclose(pWorkFile);
			fclose(pOutFile);
			return;
		}
		delete[] pTmpData;
		fclose(pWorkFile);
		//*fh.FileName[i] += strlen(ObjectFilefoldPath);
		string str1 = fh.FileName[i];
		str1 = str1.substr(strlen(ObjectFilefoldPath)+1,MAX_PATH);
		//cout << "Object: " << ObjectFilefoldPath << endl;
		//cout << "strl: " << str1 << endl;
		strcpy(fh.FileName[i], str1.c_str());
		//cout << "fh.FileName modify: " << fh.FileName[i] << endl;

	}
	for (int i = 0; i < fh.FileCount; i++)
	{
		cout << "fh.FileName modify: " << fh.FileName[i] << endl;
	}
	//д���ļ�ͷ

	fwrite(&fh, sizeof(fh), 1, pOutFile);



	

	fclose(pOutFile);
	cout << "������" << endl;
}




//��ʾ������ļ���Ϣ
void Pack_file::printCAB()
{
	cout << "�ļ�����Ϣ����:" << endl;
	cout << "�ļ�����:" << fh.FileCount << endl;
	for (int i = 0; i < fh.FileCount; i++)
	{
		cout << fh.FileName[i] << "\t\t\t\t" << fh.FileLen[i] << "�ֽ�" << endl;
	}
}


//�����ļ���
void Pack_file::CheckTargetPath(string targetPath)
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
