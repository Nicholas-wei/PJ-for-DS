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
	int type;//��ͨ��������
	int departure_hour;
	int departure_min;
	int arrivial_hour;
	int arrivial_min;
	int price;
	int dayspan;//�Ƿ񾭹����쵽�
	bool add_ticket(string src, string dst, int type, int d_hour, int d_min, int a_hour, int a_min,int dayspan,int price);
	bool delete_ticket(int index);
public:
	bool add_ticket();
	bool delete_ticket();
	int print_ticket_table();
};






bool time_spilt(string dep_time, int& h, int& m)
{
	//�ָ��ַ�����ʱ�䣬������ʽ���Ҵ�����intԪ����
	string::const_iterator iter = dep_time.begin();
	while (*iter != ':'&&iter!=dep_time.end()-1)iter++;
	if (iter == dep_time.end()||iter==dep_time.begin()||iter==dep_time.end()-1)
	{
		//��Ӧû��ð�ţ�û��hour,û��minute
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
		cout << "���г�������";
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
	int type=0;//��ͨ��������
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
		cout << "���������Ʊ������" << endl;
		if (cin >> ticket_num)break;
		else
		{
			cout << "�����������������\n";
			cin.clear();
			cin.ignore();
		}
	}
	for (int i = 0; i < ticket_num; i++)
	{
		cout << "���������������Ʊ�۵���Ϣ:" << endl;
		cout << "���������������: ";
		cin >> src;
		cout << endl;
		cout << "������Ŀ�ĵ�����: ";
		cin >> dst;
		cout << endl;
		while (1)
		{
			cout << "�����뽻ͨ���ߣ�0����𳵣�1����ɻ�: ";
			cin >> type;
			if (!(type == 0 || type == 1))
			{
				cout << "��������������������";
				cin.clear();
			}
			else break;
		}
		cout << endl;
		while (1)
		{
			cout << "���������ʱ�̣��á������ָ�,��24Сʱ������,24ʱ��ת��Ϊ0ʱ����:";
			cin >> dep_time;
			result = time_spilt(dep_time, departure_hour, departure_min);
			if (result == false)
			{
				while (1)
				{
					cout << "���������������������ȡ��������r�������룬����qȡ������\n";
					cout << "����������q����r:";
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
		cout << "�����뵽��ʱ�̣��á������ָ�,��24Сʱ������:";
		cin >> arrivial_time;
		result = time_spilt(arrivial_time, arrivial_hour, arrivial_min);
		cout << endl;
		while (1)
		{
			cin.clear();
			cout << "�ó�Ʊ�Ƿ���쵽����������������������������������0��";
			if (cin >> dayspan)break;
			else
			{
				cout << "�����������������\n";
				cin.clear();
				cin.ignore();
			}
		}
		cout << "������Ʊ��:";
		cin >> price;
		cout << endl;
		if (result == false)
		{
			while (1)
			{
				cout << "���������������������ȡ��������r�������룬����qȡ������\n";
				cout << "����������q����r:";
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
	//���õķ����Ƕ�ȡ�ļ�ȫ�����ݵ��ڶ����ļ��У�ɾ��ĳһ�У�֮���ٰ�����ļ�д��ȥ
	ofstream offile("temp.txt", ios::out);
	if (!fp.is_open()||!offile.is_open())
	{
		cout << "���ļ�����" << endl;
		return false;
	}
	string line;
	int count = 1;
	while (getline(fp, line))
	{
		if (count != n )//�жϲ�����n���浽��ʱ�ļ���
			offile << line << endl;
		count++;
	}
	//֮����ļ��ٴ��ȥ
	offile.close();
	fp.close();
	ifstream fp2("temp.txt");
	ofstream offile2("ticket_info.txt",ios::trunc);
	
	if (!fp2.is_open() || !offile2.is_open())
	{
		cout << "���ļ�����" << endl;
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
		cout << "������Ҫɾ����Ʊ�ı��,��С��" << 1 << "��" << ticket_count << "֮��";
		if (cin >> num&&num<=ticket_count)break;
		else
		{
			cout << "�����������������\n";
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
		cout << "���ļ�����" << endl;
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
		cout << "Ʊ����ţ�" << count++ << endl;
		cout << "��ʼ�أ�" << info.src << endl;
		cout << "Ŀ�ĵأ�" << info.dst << endl;
		if (info.departure_hour < 10 && info.departure_min < 10)
		{
			cout << "����ʱ��" <<"0"<< info.departure_hour << ":" <<"0"<< info.departure_min << endl;
		}
		if (info.departure_hour >= 10 && info.departure_min < 10)
		{
			cout << "����ʱ��" << info.departure_hour << ":" << "0" << info.departure_min << endl;
		}
		if (info.departure_hour < 10 && info.departure_min>=10)
		{
			cout << "����ʱ��" << "0" << info.departure_hour << ":" <<info.departure_min << endl;
		}
		if (info.departure_hour >= 10 && info.departure_min >= 10)
		{
			cout << "����ʱ��" << info.departure_hour << ":" << info.departure_min << endl;
		}
		if (info.arrivial_hour < 10 && info.arrivial_min < 10)
		{
			cout << "����ʱ��" << "0" << info.arrivial_hour << ":" << "0" << info.arrivial_min << endl;
		}
		if (info.arrivial_hour >= 10 && info.arrivial_min < 10)
		{
			cout << "����ʱ��" << info.arrivial_hour << ":" << "0" << info.arrivial_min << endl;
		}
		if (info.arrivial_hour < 10 && info.arrivial_min >= 10)
		{
			cout << "����ʱ��" << "0" << info.arrivial_hour << ":" << info.arrivial_min << endl;
		}
		if (info.arrivial_hour >= 10 && info.arrivial_min >= 10)
		{
			cout << "����ʱ��" << info.arrivial_hour << ":" << info.arrivial_min << endl;
		}
		cout << "����������" << info.dayspan << endl;
		cout << "Ʊ�ۣ�" << info.price << endl;
		cout << "*********************************" << endl;
	}
	in.close();
	return --count;
}

