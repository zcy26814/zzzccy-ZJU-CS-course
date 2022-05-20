// generatedata.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <cstring> 
#include <cstdlib>
#include <string>
using namespace std;
int main()   //生成createnum个vector，并挑选1000个并改变其大小
{
	int createnum, picknum=1000;
	int tIndex, tSize;
	int type;
	string stype;
	string filename;
	cout << "Input # for quit." << endl;
	while (1)
	{
		cout << "Input the filename: ";
		cin >> filename;
		if (!strcmp(filename.c_str(), "#")) break;
		cout << "Input the number of vectors to be created: ";
		cin >> createnum;
		ofstream fout(filename.c_str(), ios::out);
		if (!fout)
		{
			cout << "Error opening file." << endl;
			return 0;
		}
		fout << createnum << endl;
		for (int i = 0; i < createnum; i++)
		{
			tSize = (int)((float)rand() / (float)RAND_MAX * 10000);
			type = (int)((float)rand() / (float)RAND_MAX * 4) + 1;
			switch (type)
			{
			case 1: stype = "int"; break;
			case 2: stype = "float"; break;
			case 3: stype = "double"; break;
			case 4: stype = "class"; break;
			default: break;
			}
			fout << tSize << " " << stype << endl;
		}
		for (int i = 0; i < picknum; i++)
		{
			tIndex = (int)((float)rand() / (float)RAND_MAX * 10000);
			tSize = (int)((float)rand() / (float)RAND_MAX * 10000);
			if (i == picknum - 1) fout << tIndex << " " << tSize;
			else fout << tIndex << " " << tSize << endl;
		}
		fout.close();
		cout << "创建完成!" << endl;
	}
	system("pause");
	return 0;
}

