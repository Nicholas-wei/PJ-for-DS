#pragma once
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning(disable:4996)
#include<string>
#include<iostream>
#include<fstream>
int ticket_num=0;
using namespace std;
class ticket_info
{
protected:
	//long index;
	string src;
	string dst;
	int type;//交通工具种类
	int departure_hour;
	int departure_min;
	int arrivial_hour;
	int arrivial_min;
	int price;
	int dayspan;//是否经过多天到达？
	bool add_ticket(string src, string dst, int type, int d_hour, int d_min, int a_hour, int a_min,int dayspan,int price);
	bool delete_ticket(int index);
public:
	bool add_ticket();
	bool delete_ticket();
	int print_ticket_table();
};






bool time_spilt(string dep_time, int& h, int& m)
{
	//分割字符串成时间，分钟形式并且传递至int元素中
	string::const_iterator iter = dep_time.begin();
	while (*iter != ':'&&iter!=dep_time.end()-1)iter++;
	if (iter == dep_time.end()||iter==dep_time.begin()||iter==dep_time.end()-1)
	{
		//对应没有冒号，没有hour,没有minute
		return false;
	}
	string hr;
	string min;
	hr = dep_time.substr(0, iter - dep_time.begin());
	min = dep_time.substr(iter - dep_time.begin() + 1, dep_time.end() - iter);
	string::const_iterator iter_h = hr.begin();
	string::const_iterator iter_m = min.begin();
	if (hr.size() == 1)
	{
		h = *iter_h - 48;
	}
	if (hr.size() == 2)
	{
		int temp1 = 0;
		int temp2 = 0;
		temp1 = (*iter_h++ - 48)*10;
		temp2 = *iter_h - 48;
		h = temp1 + temp2;
	}
	if (!(h >= 0 && h <= 23))return false;
	if (min.size() == 1)
	{
		m = *iter_h - 48;
	}
	if (min.size() == 2)
	{
		int temp1 = 0;
		int temp2 = 0;
		temp1 = (*iter_m++ - 48) * 10;
		temp2 = *iter_m - 48;
		m = temp1 + temp2;
	}
	if (!(m >= 0 && m <= 59))return false;
	return true;
}



bool ticket_info::add_ticket(string src, string dst, int type, int d_hour, int d_min, int a_hour, int a_min,int dayspan ,int price)
{
	FILE* fp = fopen("ticket_info.txt", "a+");
	if (fp == NULL)
	{
		cout << "Error in open file!";
		return false;
	}
	int condition = 0;
	int src_size = src.size();
	int dst_size = dst.size();
	char* source = new char[src_size+1];
	char* destination = new char[dst_size+1];
	for (int i = 0; i <= src_size; i++)
	{
		source[i] = src[i];
	}
	for (int i = 0; i <= dst_size; i++)
	{
		destination[i] = dst[i];
	}
	condition = fprintf(fp,"%s %s %d %d %d %d %d %d %d \n",source,destination, type, d_hour, d_min, a_hour, a_min, dayspan,price);
	fclose(fp);
	if (condition > 0)return true;
	else
	{
		cout << "运行出现问题";
		return false;
	}
}


bool ticket_info::add_ticket()
{
	bool result;
	//long ticket_num;
	string src;
	string dst;
	string dep_time;
	string arrivial_time;
	int type=0;//交通工具种类
	int departure_hour=0;
	int departure_min=0;
	int arrivial_hour=0;
	int arrivial_min=0;
	int price=0;
	int dayspan = 0;
	int month = 0;
	int day = 0;
	while (1)
	{
		cin.clear();
		cout << "请输入添加票的张数" << endl;
		if (cin >> ticket_num)break;
		else
		{
			cout << "输入错误，请重新输入\n";
			cin.clear();
			cin.ignore();
		}
	}
	for (int i = 0; i < ticket_num; i++)
	{
		cout << "接下来请输入添加票价的信息:" << endl;
		cout << "请输入出发地名称: ";
		cin >> src;
		cout << endl;
		cout << "请输入目的地名称: ";
		cin >> dst;
		cout << endl;
		while (1)
		{
			cout << "请输入交通工具，0代表火车，1代表飞机: ";
			cin >> type;
			if (!(type == 0 || type == 1))
			{
				cout << "不符合条件，重新输入";
				cin.clear();
			}
			else break;
		}
		cout << endl;
		while (1)
		{
			cout << "请输入出发时刻，用“：”分割,以24小时制输入,24时请转换为0时输入:";
			cin >> dep_time;
			result = time_spilt(dep_time, departure_hour, departure_min);
			if (result == false)
			{
				while (1)
				{
					cout << "输入有误！请重新输入或者取消，输入r重新输入，输入q取消输入\n";
					cout << "请输入条件q或者r:";
					string cond;
					cin >> cond;
					if (cond == "r")
					{
						break;
					}
					else if (cond == "q")
					{
						return false;
					}
					else
					{
						continue;
					}
				}
				
			}	
			else break;
		}
		cout << endl;
		cout << "请输入到达时刻，用“：”分割,以24小时制输入:";
		cin >> arrivial_time;
		result = time_spilt(arrivial_time, arrivial_hour, arrivial_min);
		cout << endl;
		while (1)
		{
			cin.clear();
			cout << "该车票是否隔天到达？如果是请输入相隔天数，如果不是请输入0：";
			if (cin >> dayspan)break;
			else
			{
				cout << "输入错误，请重新输入\n";
				cin.clear();
				cin.ignore();
			}
		}
		cout << "请输入票价:";
		cin >> price;
		cout << endl;
		if (result == false)
		{
			while (1)
			{
				cout << "输入有误！请重新输入或者取消，输入r重新输入，输入q取消输入\n";
				cout << "请输入条件q或者r:";
				char cond;
				cin >> cond;
				if (cond == 'r')
				{
					i--; break;
				}
				else if (cond == 'q')
				{
					return false;
				}
				else
				{
					continue;
				}
			}
			

		}
		add_ticket(src, dst, type, departure_hour, departure_min, arrivial_hour, arrivial_min,dayspan,price);
	}
	
	return true;
}

bool ticket_info::delete_ticket(int n)
{
	ifstream fp("ticket_info.txt", ios::in);
	//采用的方法是读取文件全部内容到第二个文件中，删掉某一行，之后再把这个文件写回去
	ofstream offile("temp.txt", ios::out);
	if (!fp.is_open()||!offile.is_open())
	{
		cout << "打开文件错误" << endl;
		return false;
	}
	string line;
	int count = 1;
	while (getline(fp, line))
	{
		if (count != n )//判断不等于n，存到临时文件中
			offile << line << endl;
		count++;
	}
	//之后把文件再存回去
	offile.close();
	fp.close();
	ifstream fp2("temp.txt");
	ofstream offile2("ticket_info.txt",ios::trunc);
	
	if (!fp2.is_open() || !offile2.is_open())
	{
		cout << "打开文件错误" << endl;
		return false;
	}
	while (getline(fp2, line))
	{
		offile2 << line << endl;
	}
	offile2.close();
	fp2.close();
	system("del temp.txt");
	return true;
}


bool ticket_info::delete_ticket()
{
	int ticket_count = 0;
	ticket_count = print_ticket_table();
	int num = 0;
	while (1)
	{
		cin.clear();
		cout << "请输入要删除的票的编号,大小在" << 1 << "到" << ticket_count << "之间";
		if (cin >> num&&num<=ticket_count)break;
		else
		{
			cout << "输入错误，请重新输入\n";
			cin.clear();
			cin.ignore();
		}
	}
	bool cond = delete_ticket(num);
	return cond;
}

int ticket_info::print_ticket_table()
{
	ticket_info info;
	ifstream in("ticket_info.txt", ios::in);
	if (!in.is_open())
	{
		cout << "打开文件错误" << endl;
		exit(1);
	}
	int count = 1;
	char src[50];
	char dst[50];
	while (in >> src >> dst >> info.type >> info.departure_hour >> info.departure_min >> info.arrivial_hour >> info.arrivial_min >> info.dayspan>>info.price)
	{
		info.src = src;
		info.dst = dst;
		cout << "*********************************" << endl;
		cout << "票数编号：" << count++ << endl;
		cout << "起始地：" << info.src << endl;
		cout << "目的地：" << info.dst << endl;
		if (info.departure_hour < 10 && info.departure_min < 10)
		{
			cout << "发车时间" <<"0"<< info.departure_hour << ":" <<"0"<< info.departure_min << endl;
		}
		if (info.departure_hour >= 10 && info.departure_min < 10)
		{
			cout << "发车时间" << info.departure_hour << ":" << "0" << info.departure_min << endl;
		}
		if (info.departure_hour < 10 && info.departure_min>=10)
		{
			cout << "发车时间" << "0" << info.departure_hour << ":" <<info.departure_min << endl;
		}
		if (info.departure_hour >= 10 && info.departure_min >= 10)
		{
			cout << "发车时间" << info.departure_hour << ":" << info.departure_min << endl;
		}
		if (info.arrivial_hour < 10 && info.arrivial_min < 10)
		{
			cout << "到达时间" << "0" << info.arrivial_hour << ":" << "0" << info.arrivial_min << endl;
		}
		if (info.arrivial_hour >= 10 && info.arrivial_min < 10)
		{
			cout << "到达时间" << info.arrivial_hour << ":" << "0" << info.arrivial_min << endl;
		}
		if (info.arrivial_hour < 10 && info.arrivial_min >= 10)
		{
			cout << "到达时间" << "0" << info.arrivial_hour << ":" << info.arrivial_min << endl;
		}
		if (info.arrivial_hour >= 10 && info.arrivial_min >= 10)
		{
			cout << "到达时间" << info.arrivial_hour << ":" << info.arrivial_min << endl;
		}
		cout << "经历天数：" << info.dayspan << endl;
		cout << "票价：" << info.price << endl;
		cout << "*********************************" << endl;
	}
	in.close();
	return --count;
}

