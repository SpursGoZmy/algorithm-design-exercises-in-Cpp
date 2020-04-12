#include <iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#define citynumber 10  //预定义城市数量

using namespace std;
typedef string Type; //顶点数据类型
typedef int Weight;  //边上权值数据类型
typedef struct
{
    int lastcity,nextcity;  //lastcity为前驱城市，哈密顿路径上的上一个城市，nextcity为后继城市，哈密顿路径上的下一个城市
    Type cityname;        //城市名字
}citynode; //城市结点定义
typedef struct
{
    citynode citylist[citynumber];    //城市列表
    Weight Edge[citynumber][citynumber];    //邻接矩阵
}CityGraph; //城市有向图定义

void createCityGraph(CityGraph& G,Type city_name_list[],Weight travel_cost[][citynumber])  //初始化城市有向图
// city_name_list为城市名字的列表，travel_cost为二维权值数组,lastcity和nextcity初始化为-1
{
    for(int i=0;i<citynumber;i++)
    {
        G.citylist[i].cityname=city_name_list[i];
        G.citylist[i].lastcity=-1;
        G.citylist[i].nextcity=-1;
    }
    for(int i=0;i<citynumber;i++)
        for(int j=0;j<citynumber;j++)
        {
            if(i==j) G.Edge[i][j]=0;
            else G.Edge[i][j]=travel_cost[i][j];
        }
}

int find_path(CityGraph& G)  //求哈密顿路径，依次寻找路径最短的城市，更新每个城市的前驱和后继，但是要注意避免形成回路，最后将9个路径连起来。
{
    int totalcost=0;
    int source_city,destination_city;
    for(int k=0;k<citynumber-1;k++)
        {
            int mincost=202;
            for(int i=0;i<citynumber;i++)
            {
                if(G.citylist[i].nextcity==-1)
                {
                    for(int j=0;j<citynumber;j++)
                    {
                        int iscircle=0;
                        if(G.citylist[j].nextcity!=-1)  //判断是否形成回路
                        {
                            int m=G.citylist[j].nextcity;
                            if(m==i) iscircle=1;
                            while(G.citylist[m].nextcity!=-1)
                            {
                                m=G.citylist[m].nextcity;
                            }
                            if(m==i) iscircle=1;
                        }
                        if(G.citylist[j].lastcity==-1&&iscircle==0)
                        {
                            if(i!=j&&G.Edge[i][j]<mincost)
                            {
                                mincost=G.Edge[i][j];
                                source_city=i;
                                destination_city=j;
                            }
                        }
                    }
                }
            }
            G.citylist[source_city].nextcity=destination_city;  //更新前驱和后继
            G.citylist[destination_city].lastcity=source_city;

            totalcost+=mincost;
        }
    return totalcost;
}
void print_path(CityGraph& G)  //打印哈密顿路径。
{
    int firstcity,test_int1=0,total_cost=0,source_city;
    for(int i=0;i<citynumber;i++)
    {
        if(G.citylist[i].lastcity==-1)
        {
            firstcity=i;
            test_int1++;
        }
    }
    source_city=firstcity;
    while(G.citylist[source_city].nextcity!=-1)
    {
        int destination_city=G.citylist[source_city].nextcity;
        cout<<G.citylist[source_city].cityname<<"--->"<<G.citylist[destination_city].cityname<<" cost is "<<G.Edge[source_city][destination_city]<<endl;
        total_cost+=G.Edge[source_city][destination_city];
        source_city=destination_city;
    }
    cout<<"total cost is "<<total_cost<<endl;

}

int getvertexPos(CityGraph& G,Type cityname)  //根据城市名字得到城市编号
{
    for(int i=0;i<citynumber;i++)
        if(G.citylist[i].cityname==cityname) return i;
    return -1;
}

void find_circle(CityGraph& G,Type cityname)  //求哈密顿回路，根据城市编号数组全排列，依次判断是否路径是否可行，同时求出费用最小的路径。
{
    int circle_num=0;
    int int_array[citynumber-1];
    int path_array[citynumber+1];  //最后的路径数组
    int least_cost=100000;
    int start_num=getvertexPos(G,cityname);  //确定起始城市
    int j=0;
    for(int i=0;i<citynumber-1;i++)  //现将除去起始城市编号的9个数依次排序，为全排列使用，如0,1,2,4,5,6..
    {
        if(j==start_num)
        {
            j++;
            int_array[i]=j;
            j++;
        }
        else
        {
            int_array[i]=j;
            j++;
        }
    }

    do
    {
        int temp_cost=0;
        int flag=0;   //检验是否有断路
        int temp_array[citynumber+1];  //temp_array存放完整的路径数组，每一次全排列更新一次，第一个和最后一个数字为起始城市编号
        temp_array[0]=temp_array[citynumber]=start_num;
        for(int i=1;i<citynumber;i++)
            temp_array[i]=int_array[i-1];
        for(int i=0;i<citynumber;i++)
        {
            int m=temp_array[i];
            int n=temp_array[i+1];
            if(G.Edge[m][n]>0)
            {
                temp_cost+=G.Edge[m][n];
            }
            else
            {
                flag=1;   //flag判断是否断路
                break;
            }
        }
        if(flag==1) continue;
        if(flag==0)
        {
            if(temp_cost<least_cost)
            {
                least_cost=temp_cost;
                circle_num++;
                for(int i=0;i<citynumber+1;i++)
                    path_array[i]=temp_array[i];
            }
        }
    }while(next_permutation(int_array,int_array+9));   //利用stl中全排列函数next_permutation对int_array全排列，然后存进temp_array

    cout<<"Hamiltonian circle is follow:"<<cityname<<" is start-city for instance"<<endl;  //打印哈密顿回路
    for(int i=0;i<citynumber;i++)
    {
        int m=path_array[i];
        int n=path_array[i+1];
        cout<<G.citylist[m].cityname<<"-->"<<G.citylist[n].cityname<<" cost is "<<G.Edge[m][n]<<endl;

    }
    if(circle_num==0) cout<<"No circle founded"<<endl;
    cout<<"least cost is "<<least_cost<<endl;
}
int main()
{
    Type city_list[citynumber]={"上海","北京","重庆","郑州","成都","青岛","西安","武汉","杭州","大连"};
    Weight cost[citynumber][citynumber];
    CityGraph mygraph;
    srand(int(time(0)));
    for(int i=0;i<citynumber;i++)   //通过随机数赋值权值数组，费用为1-200
        for(int j=0;j<citynumber;j++)
        {
            if(i!=j)
                {
                    cost[i][j]=rand()%200+1;
                }

        }
    createCityGraph(mygraph,city_list,cost);
    cout<<"city list and cost matrix are as follows:"<<endl;  //给出城市列表和邻接矩阵
    for(int i=0;i<citynumber;i++)
    {
        for(int j=0;j<citynumber;j++)
            cout<<"\t"<<mygraph.Edge[i][j]<<" ";
        cout<<endl;
    }
    cout<<"城市 ";
    for(int i=0;i<10;i++)
        cout<<"\t"<<mygraph.citylist[i].cityname<<" ";
    cout<<endl;
    //求哈密顿路径，没有给定起始城市
    cout<<"Hamiltonian path is as follows ,no given start-city:"<<endl;
    cout<<"-----------------------------"<<endl;
    find_path(mygraph);
    print_path(mygraph);

    cout<<"城市 ";
    for(int i=0;i<10;i++)
        cout<<"\t"<<mygraph.citylist[i].cityname<<" ";
    cout<<endl;
    cout<<"前驱 ";
    for(int i=0;i<10;i++)
        cout<<"\t"<<mygraph.citylist[i].lastcity<<" ";
    cout<<endl;
    cout<<"后继 ";
    for(int i=0;i<10;i++)
        cout<<"\t"<<mygraph.citylist[i].nextcity<<" ";
    cout<<endl;
    cout<<"-----------------------------"<<endl;
    //求哈密顿回路，制定起始城市为“重庆”作为例子
    find_circle(mygraph,"重庆");
    return 0;
}
