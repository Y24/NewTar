// PacketFile.cpp : �������̨Ӧ�ó������ڵ㡣


#include "stdafx.h"
//#include "SearchAllFile.h"
//#include "MyCab.h"

#include "Pack_files.h"
#include "UnPack_files.h"
int main()
{
	//vector<string> vec_file;
	//vector<string>::iterator itemFileName;
	char filePacketPath[MAX_PATH] = "C:\\Users\\HP\\Desktop\\test\\test_file";
	char filePutPath[MAX_PATH] = "C:\\Users\\HP\\Desktop\\test\\output\\test_output.cab";
	
	char OutputPath[MAX_PATH] = "C:\\Users\\HP\\Desktop\\test\\output\\output_files\\";
	//CSerchAllFile::getInstance()->get_filelist(filePacketPath, vec_file);




	//--------------------�������--------------------
	//��������
	Pack_file mc;
	//��������ļ�
	mc.SetOutPutFile(filePutPath);
	//���ô��·��
	mc.SetfilePath(filePacketPath);
	//�����Ҫ������ļ�
	mc.get_filelist(filePacketPath);
	//��Ӵ���ļ�
	mc.AddFile();
	//ִ�д��
	mc.DoMakeCAB();


	//--------------------�����--------------------
	//��������
	UnPack_file umc;
	//���ý��·��
	//ִ�н��
	umc.DoUnCAB(filePutPath, OutputPath);


	cin.clear();
	cin.get();


	return 0;
}

