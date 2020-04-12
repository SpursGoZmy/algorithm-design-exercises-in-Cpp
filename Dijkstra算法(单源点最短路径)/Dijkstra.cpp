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
void ShortestPath(MGraph& G,Type start_city,Weight dist[],int path[])    //普通的Dijkstra算法
{
    int source_index=GetVertexPos(G,start_city);
    int n=G.numVertices;int already_find[maxVertices];         //最短路径顶点集
    int i,j,k;
    Weight w,min_weight;
    for(i=0;i<n;i++)
    {
        dist[i]=G.Edge[source_index][i];         //路径长度dist数组初始化
        already_find[i]=0;                  //标识顶点i是否求得最短路径
        if(i!=source_index&&dist[i]<maxWeight) path[i]=source_index;      //路径path数组初始化
        else path[i]=-1;
    }
    already_find[source_index]=1;       //起始顶点source_index加入到最短路径顶点集中
    dist[source_index]=0;
    for(i=0;i<n-1;i++)
    {
        min_weight=maxWeight;
        int temp_index=source_index;           //选不在最短路径顶点集中具有最短路径的顶点temp_index
        for(j=0;j<n;j++)
           if(!already_find[j]&&dist[j]<min_weight) {temp_index=j;min_weight=dist[j];}
        already_find[temp_index]=1;
        for(k=0;k<n;k++)
        {
            w=G.Edge[temp_index][k];
            if(!already_find[k]&&w<maxWeight&&dist[temp_index]+w<dist[k])       //修改经过temp_index到其他顶点的路径长度
            {
                dist[k]=dist[temp_index]+w;
                path[k]=temp_index;
            }
        }
    }

}
void print_least_flight_time_Path(MGraph& G,Type start_city, Weight dist[],int path[])   //输出飞行时间最少的路径
{
    int v=GetVertexPos(G,start_city);
    cout<<"从"<<G.VerticesList[v]<<"到其他城市飞行时间最短的最优航线为："<<endl;
    int i,j,k,n=numberOfVertices(G);
    int d[maxVertices];
    for(i=0;i<n;i++)
    {
        if(i!=v)
        {
            j=i; k=0;
            while(j!=v) {d[k++]=j; j=path[j];}
            d[k++]=v;
            cout<<"到"<<G.VerticesList[i]<<"的最优航线为:";
            while(k>0) cout<<G.VerticesList[d[--k]]<<" ";
            cout<<"     最短飞行时间为:"<<dist[i]<<"分钟"<<endl;
        }
    }
}

int main()
{
    Type cities[8]={"北京","上海","乌鲁木齐","西安","广州","昆明","拉萨","武汉"};
    Type flight_routes[16][2]={{"北京","上海"},{"上海","北京"},{"北京","乌鲁木齐"},
    {"乌鲁木齐","北京"},{"北京","西安"},{"西安","北京"},{"西安","广州"},{"广州","西安"},
    {"拉萨","昆明"},{"昆明","拉萨"},{"拉萨","武汉"},{"武汉","拉萨"},{"乌鲁木齐","昆明"},{"昆明","乌鲁木齐"},{"武汉","广州"},{"广州","武汉"}};
    Weight flight_time[16]={65,65,115,55,95,100,140,80,85,85,90,90,165,165,100,100};
    Weight flight_time_dist[8];
    int flight_time_path[8];
    MGraph flight_time_graph;
    createMGraph(flight_time_graph,cities,8,flight_routes,flight_time,16);

    string start_city;
    cout<<"请输入起始城市：";
    cin>>start_city;

    ShortestPath(flight_time_graph,start_city,flight_time_dist,flight_time_path);
    print_least_flight_time_Path(flight_time_graph,start_city,flight_time_dist,flight_time_path);




    return 0;
}
