#include<iostream>
#include"ticket_info.h"
#include"graph.h"
//12.17完成类定义，文件读写输出,读入输出鲁棒性检测ticket_info.h
//12.18完成时刻表和图的连接，从文件读入并输入到图，采用邻接表储存
//12.18思考问题：
//1.隔一天或者多天到达系列车票时间处理办法（添加天数输入）解决
//2.采用每次读取所有票价信息运算到内存邻接表的方法运算(解决）
//3.利用Dijkstra算法的时候，要做两种考虑
//一种是cost_value，直接计算即可
//第二种是time_value，这个要考虑中转时间。目前想到的办法是新建一个临时nodetable表格并修改time_value变量大小，修改为路上花费+(departure-last_arrivial)
//这里必须做假设是每天发车时间固定
//最后还是利用Dijkstra算法得到结果
int main()
{
	ticket_info temp_ticket;
	temp_ticket.add_ticket();
	//temp_ticket.print_ticket_table();
	//temp_ticket.delete_ticket();
	graphlnk my_graph;
	my_graph.building_graph();

}