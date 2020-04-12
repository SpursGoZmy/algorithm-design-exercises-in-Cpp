#include <iostream>
#include<cstdlib>
#include<ctime>
#define ship_number 1440   //船数量
using namespace std;
typedef struct    //定义船结点
{
    int interval_time;   //相邻两船到达的间隔时间
    int stay_time;       //停留时间
    int wait_time;       //等待时间
}shipnode;

int evaluate_cost()    //估算费用函数
{
    int total_wait_time=0;
    shipnode Ships[ship_number];
    for(int i=0;i<ship_number;i++)    //利用随机数赋值给间隔时间和停留时间
    {
        int random_stay_time=(rand()%41)+4;
        int random_interval_time=(rand()%31)+15;
        Ships[i].stay_time=random_stay_time;
        Ships[i].interval_time=random_interval_time;
    }
    Ships[0].interval_time=0;
    Ships[0].wait_time=0;
    for(int i=1;i<ship_number;i++)
    {
        int last_ship_use_dock_time=Ships[i-1].stay_time+Ships[i-1].wait_time;   //进行判断，每艘船的等待时间=上一艘船的等待时间+上一艘船的停留时间-这艘船的间隔时间
        if(last_ship_use_dock_time>Ships[i].interval_time)
        {
            Ships[i].wait_time=last_ship_use_dock_time-Ships[i].interval_time;
            total_wait_time+=Ships[i].wait_time;
        }
        else
        {
            Ships[i].wait_time=0;
        }
    }
    cout<<"cost is "<<total_wait_time*1000<<endl;
    return total_wait_time*1000;
}

int main()
{
    srand(int(time(0)));
    int total_cost=0;
    for(int i=0;i<20;i++)
        total_cost+=evaluate_cost();
    cout<<"average cost is "<<total_cost/20;  //计算费用平均值
    cout<<endl;
    if(total_cost/20>13500000)
        cout<<"应该扩建码头"<<endl;
    else
        cout<<"无需扩建码头"<<endl;
    return 0;
}
