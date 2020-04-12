#include <iostream>
#include<cstdlib>
#include<ctime>
#define ship_number 1440   //������
using namespace std;
typedef struct    //���崬���
{
    int interval_time;   //������������ļ��ʱ��
    int stay_time;       //ͣ��ʱ��
    int wait_time;       //�ȴ�ʱ��
}shipnode;

int evaluate_cost()    //������ú���
{
    int total_wait_time=0;
    shipnode Ships[ship_number];
    for(int i=0;i<ship_number;i++)    //�����������ֵ�����ʱ���ͣ��ʱ��
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
        int last_ship_use_dock_time=Ships[i-1].stay_time+Ships[i-1].wait_time;   //�����жϣ�ÿ�Ҵ��ĵȴ�ʱ��=��һ�Ҵ��ĵȴ�ʱ��+��һ�Ҵ���ͣ��ʱ��-���Ҵ��ļ��ʱ��
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
    cout<<"average cost is "<<total_cost/20;  //�������ƽ��ֵ
    cout<<endl;
    if(total_cost/20>13500000)
        cout<<"Ӧ��������ͷ"<<endl;
    else
        cout<<"����������ͷ"<<endl;
    return 0;
}
