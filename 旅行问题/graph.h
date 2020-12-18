#pragma once
#include<iostream>
#include<vector>
#include<fstream>

using namespace std;
//采用邻接表形式储存
class ticket_info;
struct edge//定义参考清华教材
{
	int time;
	int money;
	char dest[50]="0";
	edge* next;
	edge() { time = 0; money = 0; next = nullptr; }
	//edge(char* t_dest,int t_time, int t_money) :dest(t_dest), money(t_money),time(t_time), next(nullptr) {}

};


struct vertex
{
	char name[50];
	edge* adj;
};


class graphlnk
{
public:
	bool building_graph();//从文件读入ticket_info并建立图
private:
	vector<vertex> nodetable;
	bool insert(char* src, char* dst, int money, int time);
}globle_graph;


int convert_time(int d_h, int d_m, int a_h, int a_m,int dayspan)
{
	int result = 0;
	int t_hour = 0;
	int t_min;
	result += dayspan * 1440;//按照分钟计算
	if (d_h <= a_h)
	{
		//没有跨越24点
		if(d_m<=a_m)
		t_hour = a_h - d_h;
		else
		{
			t_hour = a_h - d_h-1;
		}
	}
	else
	{
		if (d_m <= a_m)
		t_hour = 24 - d_h + a_h;
		else
		{
			t_hour = 24 - d_h + a_h - 1;
		}
	}
	if (d_m <= a_m)
	{
		t_min = a_m - d_m;
	}
	else
	{
		t_min = 60 - d_m + a_m;
	}
	result += t_min + t_hour * 60;
	return result;

}


bool graphlnk::insert(char* arg_src,char* arg_dst, int arg_money, int arg_time)
{
	edge* t_edge = new edge;
	int index = 0;
	int written = 0;
	for (; index < nodetable.size(); index++)
	{
		if (nodetable[index].name == arg_src)
		{
			//表内已经有这个城市
			int i = 0;
			strcpy(t_edge->dest, arg_dst);
			t_edge->money = arg_money;
			t_edge->time = arg_time;
			t_edge->next = nodetable[index].adj;
			nodetable[index].adj = t_edge;
			written = 1;
		}
	}
	if (!written)
	{
		vertex temp;
		strcpy(temp.name, arg_src);
		strcpy(t_edge->dest, arg_dst);
		t_edge->money = arg_money;
		t_edge->time = arg_time;
		temp.adj = t_edge;
		nodetable.push_back(temp);
	}
	return true;
}

bool graphlnk::building_graph()
{
	int type;//交通工具种类
	int departure_hour;
	int departure_min;
	int arrivial_hour;
	int arrivial_min;
	int price;
	int dayspan;//是否经过多天到达？
	int time=0;
	cout << "正在建立图" << endl;
	char src[50];
	char dst[50];
	int count = 0;
	ifstream in("ticket_info.txt", ios::in);
	if (!in.is_open())
	{
		cout << "打开文件错误" << endl;
		exit(1);
	}
	while (in >> src >> dst >> type >> departure_hour >> departure_min >> arrivial_hour >> arrivial_min >> dayspan >> price)
	{
		time = convert_time(departure_hour, departure_min, arrivial_hour, arrivial_min,dayspan);
		globle_graph.insert(src,dst,price, time);
	}
	cout << "图建立完毕" << endl;
}