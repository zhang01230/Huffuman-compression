#define _CRT_SECURE_NO_WARNINGS
#include"file.h"
#include<Windows.h>

void menu()
{
	while (1)
	{
		Sleep(1000);
		system("cls");
		cout << "********************************" << endl;
		cout << "           1.压缩" << endl;
		cout << "           2.解压" << endl;
		cout << "           0.退出" << endl;
		cout << "********************************" << endl;

		int key = 0;
		cout << "请选择：";
		cin >> key;
		cout << endl;

		string route;
		FileInfo fl;
		if(key==1)
		{
			route = "";
			cout << "请输入文件名：";
			cin >> route;
			cout << endl;
			fl.compression(route.c_str());
		}
		else if(key==2)
		{
			route = "";
			cout << "请输入文件名：";
			cin >> route;
			cout << endl;
			fl.uncompression(route.c_str());
		}
		else
		{
			_exit(0);
		}
	}
}