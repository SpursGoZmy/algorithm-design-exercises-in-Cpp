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
    //不加限界函数的普通方法
//    x[i]=true;
//    current_sum+=data[i];
//    backtrack(i+1);
//    x[i]=false;
//    current_sum-=data[i];
//    backtrack(i+1);



    if(data[i]>=0)        //data[i]大于等于0
    {
        if((current_sum+left_positive_sum>=sum)&&(current_sum+data[i]<=sum))   //可能选择data[i]
        {
            x[i]=true;
            current_sum+=data[i];
            left_positive_sum-=data[i];
            backtrack(i+1);
            x[i]=false;
            left_positive_sum+=data[i];
            current_sum-=data[i];
        }
        if(current_sum+left_positive_sum-data[i]>=sum)         //可能不选data[i]
        {
            x[i]=false;
            left_positive_sum-=data[i];
            backtrack(i+1);
            left_positive_sum+=data[i];
        }
    }
    if(data[i]<0)      //data[i]小于0
    {
        if(current_sum+data[i]+left_positive_sum>=sum)     //可能选择data[i]
        {
            x[i]=true;
            current_sum+=data[i];
            left_negative_sum=left_negative_sum-data[i];
            backtrack(i+1);
            x[i]=false;
            current_sum-=data[i];
            left_negative_sum+=data[i];
        }
        if((current_sum+left_negative_sum<=sum)&&(current_sum+left_positive_sum>=sum))     //可能不选择data[i]
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
    cout<<"集合中数字为："<<endl;
    for(int i=0;i<10;i++)
        cout<<a[i]<<" ";
    cout<<endl;
    cout<<"所有满足和为12的数字集合有:"<<endl;

    Subset_sum_problem test(10,12,a);

    return 0;
}
