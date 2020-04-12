#include <iostream>
#include<time.h>
#include<algorithm>
#include<stdio.h>
#include<stdlib.h>
#define maxSize 10000
#define heapSize 10000
using namespace std;
typedef int DataType;
typedef struct
{
    DataType data[maxSize];
    int data_num;
}DataList;

typedef struct
{
    DataType data[heapSize];
    int data_num;
}maxHeap;
void Swap(DataList& L,int a,int b)
{
    DataType temp=L.data[a];
    L.data[a]=L.data[b];
    L.data[b]=temp;
}
void createDataList(DataList& L,DataType A[],int n)
{
    for(int i=0;i<n;i++)
        L.data[i]=A[i];
    L.data_num=n;
}

void InsertSort(DataList& L)
{
    DataType temp_element;
    int j;
    for(int i=1;i<=L.data_num-1;i++)
        if(L.data[i]<L.data[i-1])
        {
            temp_element=L.data[i];
            for( j=i-1;j>=0&&temp_element<L.data[j];j--)
                L.data[j+1]=L.data[j];
            L.data[j+1]=temp_element;
        }
}

void BubbleSort(DataList& L)
{
    for(int i=0;i<=L.data_num-2;i++)
    {
        int exchange=0;
        for(int j=L.data_num-1;j>=i+1;j--)
            if(L.data[j-1]>L.data[j])
            {
                Swap(L,j-1,j);
                exchange=1;
            }
            if(exchange==0) return;
    }
}
void QuickSort(DataList& L)
{
    sort(L.data,L.data+L.data_num);
}
void shiftDown(maxHeap& H,int start_index,int end_index)
{
    if(start_index==end_index) return;
    int i=start_index;
    int j=2*i+1;
    DataType temp=H.data[i];
    while(j<=end_index)
    {
        if(j<end_index&&H.data[j]<H.data[j+1]) j++;
        if(temp>=H.data[j]) break;
        else
        {
            H.data[i]=H.data[j];
            i=j;
            j=2*j+1;
        }
    }
    H.data[i]=temp;
}
void createMaxHeap(maxHeap& H,DataType arr[],int n)
{
    for(int i=0;i<n;i++)
    {
        H.data[i]=arr[i];
    }
    H.data_num=n;
    for(int i=(H.data_num-2)/2;i>=0;i--)
        shiftDown(H,i,H.data_num-1);
}
void HeapSort(maxHeap& H)
{
    for(int i=H.data_num-1;i>0;i--)
    {
        DataType temp=H.data[0];
        H.data[0]=H.data[i];
        H.data[i]=temp;
        shiftDown(H,0,i-1);
    }
}
int main()
{
    int myarrayA[maxSize],myarrayB[maxSize],myarrayC[maxSize];
    clock_t start,finish;
    double duration;
    for(int i=0;i<maxSize;i++)
        myarrayA[i]=rand()%maxSize;
    for(int i=0;i<maxSize;i++)
        myarrayB[i]=rand()%maxSize;
    for(int i=0;i<maxSize;i++)
        myarrayC[i]=rand()%maxSize;
    DataList myList;
    //InsertSort      ²åÈëÅÅÐò
    createDataList(myList,myarrayA,maxSize);
    start=clock();
    InsertSort(myList);
    finish=clock();
    duration=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"Time of InsertSort is "<<duration<<" seconds"<<endl;

    //BubbleSort    Ã°ÅÝÅÅÐò
    createDataList(myList,myarrayB,maxSize);
    start=clock();
    BubbleSort(myList);
    finish=clock();
    duration=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"Time of BubbleSort is "<<duration<<" seconds"<<endl;

    //QuickSort    ¿ìËÙÅÅÐò
    createDataList(myList,myarrayC,maxSize);
    start=clock();
    QuickSort(myList);
    finish=clock();
    duration=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"Time of QuickSort is "<<duration<<" seconds"<<endl;

    //HeapSort    ¶ÑÅÅÐò
    maxHeap myHeap;
    createMaxHeap(myHeap,myarrayA,heapSize);
    start=clock();
    HeapSort(myHeap);
    finish=clock();
    duration=(double)(finish-start)/CLOCKS_PER_SEC;
    cout<<"Time of HeapSort is "<<duration<<" seconds"<<endl;

    return 0;
}
