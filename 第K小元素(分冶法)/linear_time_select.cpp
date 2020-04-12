#include <iostream>
#include<algorithm>
#include<stdlib.h>
#define N 10
using namespace std;
int datum;
bool compare(int i)
{
    return (i<=datum);
}
int my_randomizedSelect(int a[],int p,int r,int k)      //方法1
{
    if(p==r) return a[p];
    int random_int=(rand()%(r-p+1))+p;
    datum=a[random_int];

    int* q=stable_partition(a+p,a+r+1,compare);

    int i=q-a-1;
    int temp=a[i];
    for(int m=p;m<=i;m++)
        if(a[m]==datum) a[m]=temp;
    a[i]=datum;
    int j=i-p+1;
    if(k<=j) return my_randomizedSelect(a,p,i,k);
    else return my_randomizedSelect(a,i+1,r,k-j);
}
int partition1(int a[],int p,int r)
{
    int i=p,
        j=r+1;

    datum=a[p];
    while(true)
    {
        while(a[++i]<datum&&i<r);
        while(a[--j]>datum);
        if(i>=j) break;
        int temp=a[i];
        a[i]=a[j];
        a[j]=temp;
    }
    a[p]=a[j];
    a[j]=datum;
    return j;

}
int randomizedPartition(int a[],int p,int r)
{
    int i=(rand()%(r-p+1))+p;
    int temp=a[i];
    a[i]=a[p];
    a[p]=temp;
    return partition1(a,p,r);
}
int randomizedSelect(int a[],int p,int r,int k)
{
    if(p==r) return a[p];
    int i=randomizedPartition(a,p,r);
    int j=i-p+1;
    if(k<=j) return randomizedSelect(a,p,i,k);
    else return randomizedSelect(a,i+1,r,k-j);
}
int main()
{

    int a[N];
    int b[N];
    for(int i=0;i<N;i++)
        {
            a[i]=rand()%50;
            b[i]=a[i];
        }
    int k;
    int index;
    cout<<"请输入要求数组中第几小的元素,1<=k<=N,N为数组元素个数"<<endl;
    cin>>k;
    //int c=randomizedSelect(a,0,N-1,k);
    int d=my_randomizedSelect(a,0,N-1,k);

    cout<<"数组为:"<<endl;
    for(int i=0;i<N;i++)
    {
        if(b[i]==d)  index=i;
        cout<<b[i]<<" ";
    }
    cout<<endl;
    cout<<"数组第"<<k<<"小的元素是"<<d<<" ,位于"<<index<<"位置"<<endl;
    return 0;
}
