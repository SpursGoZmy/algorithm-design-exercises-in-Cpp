#include <iostream>
#include<algorithm>

#define maxSize 20
#define size 30
using namespace std;
typedef struct      //边结点
{
    int v1,v2;
    int cost;
}EdgeNode;
typedef struct         //最小生成树
{
    EdgeNode edgeValue[maxSize];
    int edeg_number=0;
}MinSpanTree;


typedef struct         //并查集
{
    int parent[size];
}UFSets;

typedef struct          //一个普通结点用来从边结点数组得到图的邻接矩阵存储表示
{
    int data;
    int flag=0;
}Node;
void Initial(UFSets& S)        //并查集的操作
{
    for(int i=0;i<size;i++) S.parent[i]=-1;
}
int Find(UFSets& S,int x)
{
    while(S.parent[x]>=0) x=S.parent[x];
    return x;
}
void Merge(UFSets& S,int R1,int R2)
{
    if(R2==R1) return;
    S.parent[R1]= S.parent[R1]+S.parent[R2];
    S.parent[R2]=R1;
}


bool cmp(EdgeNode A,EdgeNode B)
{
    if(A.cost<=B.cost) return true;
    return false;
}

void printMinSpanTree(MinSpanTree& T)      //打印最小生成树
{
    for(int i=0;i<T.edeg_number;i++)
    {
        cout<<T.edgeValue[i].v1<<" "<<T.edgeValue[i].v2<<" cost:"<<T.edgeValue[i].cost<<endl;
    }
}

void Kruskal_MST(EdgeNode arr[],MinSpanTree& T,int edge_number)
{
    EdgeNode w;
    UFSets Uset;
    Initial(Uset);
    int k=0,j=0;
    sort(arr,arr+edge_number,cmp);
    while(k<edge_number)
    {
        w=arr[j];
        int u=Find(Uset,w.v1);
        int v=Find(Uset,w.v2);
        if(u!=v)
        {
            T.edgeValue[T.edeg_number].v1=w.v1;
            T.edgeValue[T.edeg_number].v2=w.v2;
            T.edgeValue[T.edeg_number++].cost=w.cost;
            Merge(Uset,u,v);
        }
        j++;
        k++;
    }

}

void Prim(int vertex_number,int c[][8],MinSpanTree& T)
{
    int lowcost[vertex_number+1];
    int closest[vertex_number+1];
    bool s[vertex_number+1];
    s[1]=true;
    for(int i=2;i<=vertex_number;i++)
    {
        lowcost[i]=c[1][i];
        closest[i]=1;
        s[i]=false;
    }
    for(int i=1;i<vertex_number;i++)
    {
        int min=20000;
        int j=1;
        for(int k=2;k<=vertex_number;k++)
        {
            if((lowcost[k]<min)&&(!s[k]))
            {
                min=lowcost[k];
                j=k;
            }
        }
        T.edgeValue[T.edeg_number].v1=j;
        T.edgeValue[T.edeg_number].v2=closest[j];
        T.edgeValue[T.edeg_number++].cost=c[(closest[j])][j];
        s[j]=true;
        for(int k=2;k<=vertex_number;k++)
            if((c[j][k]<lowcost[k])&&(!s[k]))
        {
            lowcost[k]=c[j][k];
            closest[k]=j;
        }

    }
}

int main()
{
    EdgeNode edgearray[9]={{1,2,28},{2,3,16},{3,4,12},{4,5,22},{5,6,25},{6,1,10},{2,7,14},{5,7,24},{4,7,18}};
    MinSpanTree T;
    MinSpanTree Q;
    cout<<"Kruskal方法:"<<endl;
    Kruskal_MST(edgearray,T,9);
    printMinSpanTree(T);
    cout<<endl;

    //Node 数组用于初始化 二维权重数组m[8][8]
    Node c[8][8];
    for(int i=0;i<9;i++)
    {
        int u=edgearray[i].v1;
        int v=edgearray[i].v2;
        c[u][v].data=c[v][u].data=edgearray[i].cost;
        c[u][v].flag=c[v][u].flag=1;
    }
    int m[8][8];
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
    {
         if(c[i][j].flag==1)
            m[i][j]=c[i][j].data;
         else
            m[i][j]=20000;
    }
    cout<<"Prim方法:"<<endl;
    Prim(7,m,Q);
    printMinSpanTree(Q);

    return 0;
}
