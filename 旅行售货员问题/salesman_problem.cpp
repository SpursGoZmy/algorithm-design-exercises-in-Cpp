#include <iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#define citynumber 10  //Ԥ�����������

using namespace std;
typedef string Type; //������������
typedef int Weight;  //����Ȩֵ��������
typedef struct
{
    int lastcity,nextcity;  //lastcityΪǰ�����У����ܶ�·���ϵ���һ�����У�nextcityΪ��̳��У����ܶ�·���ϵ���һ������
    Type cityname;        //��������
}citynode; //���н�㶨��
typedef struct
{
    citynode citylist[citynumber];    //�����б�
    Weight Edge[citynumber][citynumber];    //�ڽӾ���
}CityGraph; //��������ͼ����

void createCityGraph(CityGraph& G,Type city_name_list[],Weight travel_cost[][citynumber])  //��ʼ����������ͼ
// city_name_listΪ�������ֵ��б�travel_costΪ��άȨֵ����,lastcity��nextcity��ʼ��Ϊ-1
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

int find_path(CityGraph& G)  //����ܶ�·��������Ѱ��·����̵ĳ��У�����ÿ�����е�ǰ���ͺ�̣�����Ҫע������γɻ�·�����9��·����������
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
                        if(G.citylist[j].nextcity!=-1)  //�ж��Ƿ��γɻ�·
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
            G.citylist[source_city].nextcity=destination_city;  //����ǰ���ͺ��
            G.citylist[destination_city].lastcity=source_city;

            totalcost+=mincost;
        }
    return totalcost;
}
void print_path(CityGraph& G)  //��ӡ���ܶ�·����
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

int getvertexPos(CityGraph& G,Type cityname)  //���ݳ������ֵõ����б��
{
    for(int i=0;i<citynumber;i++)
        if(G.citylist[i].cityname==cityname) return i;
    return -1;
}

void find_circle(CityGraph& G,Type cityname)  //����ܶٻ�·�����ݳ��б������ȫ���У������ж��Ƿ�·���Ƿ���У�ͬʱ���������С��·����
{
    int circle_num=0;
    int int_array[citynumber-1];
    int path_array[citynumber+1];  //����·������
    int least_cost=100000;
    int start_num=getvertexPos(G,cityname);  //ȷ����ʼ����
    int j=0;
    for(int i=0;i<citynumber-1;i++)  //�ֽ���ȥ��ʼ���б�ŵ�9������������Ϊȫ����ʹ�ã���0,1,2,4,5,6..
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
        int flag=0;   //�����Ƿ��ж�·
        int temp_array[citynumber+1];  //temp_array���������·�����飬ÿһ��ȫ���и���һ�Σ���һ�������һ������Ϊ��ʼ���б��
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
                flag=1;   //flag�ж��Ƿ��·
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
    }while(next_permutation(int_array,int_array+9));   //����stl��ȫ���к���next_permutation��int_arrayȫ���У�Ȼ����temp_array

    cout<<"Hamiltonian circle is follow:"<<cityname<<" is start-city for instance"<<endl;  //��ӡ���ܶٻ�·
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
    Type city_list[citynumber]={"�Ϻ�","����","����","֣��","�ɶ�","�ൺ","����","�人","����","����"};
    Weight cost[citynumber][citynumber];
    CityGraph mygraph;
    srand(int(time(0)));
    for(int i=0;i<citynumber;i++)   //ͨ���������ֵȨֵ���飬����Ϊ1-200
        for(int j=0;j<citynumber;j++)
        {
            if(i!=j)
                {
                    cost[i][j]=rand()%200+1;
                }

        }
    createCityGraph(mygraph,city_list,cost);
    cout<<"city list and cost matrix are as follows:"<<endl;  //���������б���ڽӾ���
    for(int i=0;i<citynumber;i++)
    {
        for(int j=0;j<citynumber;j++)
            cout<<"\t"<<mygraph.Edge[i][j]<<" ";
        cout<<endl;
    }
    cout<<"���� ";
    for(int i=0;i<10;i++)
        cout<<"\t"<<mygraph.citylist[i].cityname<<" ";
    cout<<endl;
    //����ܶ�·����û�и�����ʼ����
    cout<<"Hamiltonian path is as follows ,no given start-city:"<<endl;
    cout<<"-----------------------------"<<endl;
    find_path(mygraph);
    print_path(mygraph);

    cout<<"���� ";
    for(int i=0;i<10;i++)
        cout<<"\t"<<mygraph.citylist[i].cityname<<" ";
    cout<<endl;
    cout<<"ǰ�� ";
    for(int i=0;i<10;i++)
        cout<<"\t"<<mygraph.citylist[i].lastcity<<" ";
    cout<<endl;
    cout<<"��� ";
    for(int i=0;i<10;i++)
        cout<<"\t"<<mygraph.citylist[i].nextcity<<" ";
    cout<<endl;
    cout<<"-----------------------------"<<endl;
    //����ܶٻ�·���ƶ���ʼ����Ϊ�����족��Ϊ����
    find_circle(mygraph,"����");
    return 0;
}
