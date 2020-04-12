#include <iostream>
#include<stdio.h>
#include<string>
#define maxVertices 10
#define maxEdges 30
#define maxWeight 20000
using namespace std;
typedef string Type;
typedef int Weight;

typedef struct
{
    int numVertices,numEdges;
    Type VerticesList[maxVertices];
    Weight Edge[maxVertices][maxVertices];
}MGraph;

int GetVertexPos(MGraph& G,Type x)
{
    for(int i=0;i<G.numVertices;i++)
        if(G.VerticesList[i]==x) return i;
    return -1;
}
int numberOfVertices(MGraph& G)
{
    return G.numVertices;
}
void createMGraph(MGraph& G,Type v[],int verticenum,Type ed[][2],Weight c[],int edgenum)
{

    G.numVertices=verticenum;
    G.numEdges=edgenum;
    int i,j,k;
    for(i=0;i<G.numVertices;i++)
    {
        G.VerticesList[i]=v[i];
        for(j=0;j<G.numVertices;j++)
            G.Edge[i][j]=(i==j)?0:maxWeight;
    }
    for(k=0;k<G.numEdges;k++)
    {
        i= GetVertexPos(G,ed[k][0]);
        j= GetVertexPos(G,ed[k][1]);
        G.Edge[i][j]=c[k];
    }
}
void ShortestPath(MGraph& G,Type start_city,Weight dist[],int path[])    //��ͨ��Dijkstra�㷨
{
    int source_index=GetVertexPos(G,start_city);
    int n=G.numVertices;int already_find[maxVertices];         //���·�����㼯
    int i,j,k;
    Weight w,min_weight;
    for(i=0;i<n;i++)
    {
        dist[i]=G.Edge[source_index][i];         //·������dist�����ʼ��
        already_find[i]=0;                  //��ʶ����i�Ƿ�������·��
        if(i!=source_index&&dist[i]<maxWeight) path[i]=source_index;      //·��path�����ʼ��
        else path[i]=-1;
    }
    already_find[source_index]=1;       //��ʼ����source_index���뵽���·�����㼯��
    dist[source_index]=0;
    for(i=0;i<n-1;i++)
    {
        min_weight=maxWeight;
        int temp_index=source_index;           //ѡ�������·�����㼯�о������·���Ķ���temp_index
        for(j=0;j<n;j++)
           if(!already_find[j]&&dist[j]<min_weight) {temp_index=j;min_weight=dist[j];}
        already_find[temp_index]=1;
        for(k=0;k<n;k++)
        {
            w=G.Edge[temp_index][k];
            if(!already_find[k]&&w<maxWeight&&dist[temp_index]+w<dist[k])       //�޸ľ���temp_index�����������·������
            {
                dist[k]=dist[temp_index]+w;
                path[k]=temp_index;
            }
        }
    }

}
void print_least_flight_time_Path(MGraph& G,Type start_city, Weight dist[],int path[])   //�������ʱ�����ٵ�·��
{
    int v=GetVertexPos(G,start_city);
    cout<<"��"<<G.VerticesList[v]<<"���������з���ʱ����̵����ź���Ϊ��"<<endl;
    int i,j,k,n=numberOfVertices(G);
    int d[maxVertices];
    for(i=0;i<n;i++)
    {
        if(i!=v)
        {
            j=i; k=0;
            while(j!=v) {d[k++]=j; j=path[j];}
            d[k++]=v;
            cout<<"��"<<G.VerticesList[i]<<"�����ź���Ϊ:";
            while(k>0) cout<<G.VerticesList[d[--k]]<<" ";
            cout<<"     ��̷���ʱ��Ϊ:"<<dist[i]<<"����"<<endl;
        }
    }
}

int main()
{
    Type cities[8]={"����","�Ϻ�","��³ľ��","����","����","����","����","�人"};
    Type flight_routes[16][2]={{"����","�Ϻ�"},{"�Ϻ�","����"},{"����","��³ľ��"},
    {"��³ľ��","����"},{"����","����"},{"����","����"},{"����","����"},{"����","����"},
    {"����","����"},{"����","����"},{"����","�人"},{"�人","����"},{"��³ľ��","����"},{"����","��³ľ��"},{"�人","����"},{"����","�人"}};
    Weight flight_time[16]={65,65,115,55,95,100,140,80,85,85,90,90,165,165,100,100};
    Weight flight_time_dist[8];
    int flight_time_path[8];
    MGraph flight_time_graph;
    createMGraph(flight_time_graph,cities,8,flight_routes,flight_time,16);

    string start_city;
    cout<<"��������ʼ���У�";
    cin>>start_city;

    ShortestPath(flight_time_graph,start_city,flight_time_dist,flight_time_path);
    print_least_flight_time_Path(flight_time_graph,start_city,flight_time_dist,flight_time_path);




    return 0;
}
