#include <iostream>
#include<iomanip>
#include<algorithm>
#include<stdio.h>
#define N 5
#define Capacity 10
using namespace std;

 void knapsack(int v[],int w[],int c,int m[][Capacity+1])
{
    int n=N;
    int jMax=min(w[n]-1,c);
    for(int j=0;j<=jMax;j++)
        m[n][j]=0;
    for(int j=w[n];j<=c;j++)
        m[n][j]=v[n];
    for(int i=n-1;i>=1;i--)
    {
        jMax=min(w[i]-1,c);
        for(int j=0;j<=jMax;j++)
            m[i][j]=m[i+1][j];
        for(int j=w[i];j<=c;j++)
            m[i][j]=max(m[i+1][j],m[i+1][j-w[i]]+v[i]);
    }
}
 void traceback(int m[][Capacity+1],int w[],int c,int x[])
{
    int n=N;
    for(int i=1;i<n;i++)
        if(m[i][c]==m[i+1][c]) x[i]=0;
        else
        {
            x[i]=1;
            c-=w[i];
        }
    x[n]=(m[n][c]>0)?1:0;
}
 void init(int v[],int w[])
{
    for(int i=1;i<N+1;i++)
        {
            v[i]=rand()%10+1;
            w[i]=rand()%5+1;
        }
}



int main()
{
    int value[N+1];
    int weight[N+1];
    int m[N+1][Capacity+1];
    int knapsack_capacity;
    int if_selected[N+1];
    init(value,weight);
    cout<<"物品重量为:"<<endl;
    for(int i=1;i<N+1;i++)
    {
        cout<<weight[i]<<" ";
    }
    cout<<endl;
    cout<<"物品价值为:"<<endl;
    for(int i=1;i<N+1;i++)
    {
        cout<<value[i]<<" ";
    }
    cout<<endl;
    knapsack(value,weight,Capacity,m);
    traceback(m,weight,Capacity,if_selected);
    cout<<"列标为 ";
    for(int i=0;i<Capacity+1;i++)
        cout<<setw(3)<<i<<" ";
    cout<<endl;
    cout<<"数组m[i][j]为"<<endl;

    for(int i=1;i<N+1;i++)
    {
        cout<<"       ";
        for(int j=0;j<Capacity+1;j++)
        {

            cout<<setw(3)<<m[i][j]<<" ";
        }
        cout<<endl;
    }
    for(int i=1;i<N+1;i++)
    {
        if(if_selected[i]==1)
            cout<<"选择物品"<<i<<endl;
    }
    return 0;
}
