#include <iostream>
#include<algorithm>
using namespace std;
#define maxsize 15

class Subset_sum_problem
{
private:
    int data_number;
    int* data;
    int sum;
    bool* x;
public:
    static int current_sum;
    static int left_positive_sum;
    static int left_negative_sum;

    Subset_sum_problem(int number,int target_sum,int a[])
    {
        data_number=number;
        sum=target_sum;
        x=new bool[data_number];
        data=new int[data_number];
        sort(a,a+data_number);
        for(int i=0;i<data_number;i++)
            {
                data[i]=a[i];

                x[i]=false;
                if(a[i]<0)
                    left_negative_sum+=a[i];
                else
                    left_positive_sum+=a[i];
            }

        backtrack(0);
    }
    void backtrack(int i);
    void print();

};

int Subset_sum_problem::current_sum=0;
int Subset_sum_problem::left_negative_sum=0;
int Subset_sum_problem::left_positive_sum=0;


void Subset_sum_problem::backtrack(int i)
{
    if(i>=data_number)
        return;
    if(current_sum+data[i]==sum)
    {
        x[i]=true;
        print();
        x[i]=false;

    }
    //�����޽纯������ͨ����
//    x[i]=true;
//    current_sum+=data[i];
//    backtrack(i+1);
//    x[i]=false;
//    current_sum-=data[i];
//    backtrack(i+1);



    if(data[i]>=0)        //data[i]���ڵ���0
    {
        if((current_sum+left_positive_sum>=sum)&&(current_sum+data[i]<=sum))   //����ѡ��data[i]
        {
            x[i]=true;
            current_sum+=data[i];
            left_positive_sum-=data[i];
            backtrack(i+1);
            x[i]=false;
            left_positive_sum+=data[i];
            current_sum-=data[i];
        }
        if(current_sum+left_positive_sum-data[i]>=sum)         //���ܲ�ѡdata[i]
        {
            x[i]=false;
            left_positive_sum-=data[i];
            backtrack(i+1);
            left_positive_sum+=data[i];
        }
    }
    if(data[i]<0)      //data[i]С��0
    {
        if(current_sum+data[i]+left_positive_sum>=sum)     //����ѡ��data[i]
        {
            x[i]=true;
            current_sum+=data[i];
            left_negative_sum=left_negative_sum-data[i];
            backtrack(i+1);
            x[i]=false;
            current_sum-=data[i];
            left_negative_sum+=data[i];
        }
        if((current_sum+left_negative_sum<=sum)&&(current_sum+left_positive_sum>=sum))     //���ܲ�ѡ��data[i]
        {
            x[i]=false;
            left_negative_sum=left_negative_sum-data[i];
            backtrack(i+1);
            left_negative_sum+=data[i];
        }
    }

}
void Subset_sum_problem::print()
{
    for(int i=0;i<data_number;i++)
    {
        if(x[i]==true)
            cout<<data[i]<<" ";
    }
    cout<<endl;
}
int main()
{
    int a[10]={-1,0,1,2,3,5,6,8,9,10};
    cout<<"����������Ϊ��"<<endl;
    for(int i=0;i<10;i++)
        cout<<a[i]<<" ";
    cout<<endl;
    cout<<"���������Ϊ12�����ּ�����:"<<endl;

    Subset_sum_problem test(10,12,a);

    return 0;
}
