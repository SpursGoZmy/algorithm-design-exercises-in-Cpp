#include <iostream>
#include<algorithm>
using namespace std;
typedef struct
{
    double weight;
    double value;
}Object;

bool cmp(Object A,Object B)
{
    double a=A.value/A.weight;
    double b=B.value/B.weight;
    if(a>=b) return true;
    else return false;
}
class Knapsack
{
private:
    double knapsack_capacity;
    int object_number;

    static double current_weight;
    static double current_value;



    public:
    static double bestvalue;
    static int* x;

    double* weight;
    double* value;
    Knapsack(Object obj[],int n,double capacity)
    {
        object_number=n;
        knapsack_capacity=capacity;
        sort(obj,obj+n,cmp);
        weight=new double[n+1];
        value=new double[n+1];

        for(int i=1;i<=n;i++)
        {
            weight[i]=obj[i-1].weight;
            value[i]=obj[i-1].value;
        }
        backtrack(1);
    }
    void  backtrack(int i);
    double bound(int i);

};
double Knapsack::current_value=0.0;
double Knapsack::current_weight=0.0;
double Knapsack::bestvalue=0.0;
int* Knapsack::x=new int[5];

void Knapsack::backtrack(int i)
{
    if(i>object_number)
    {
        bestvalue=current_value;
        //for(int i=1;i<=)
        return;
    }
    if(current_weight+weight[i]<=knapsack_capacity)
    {
        x[i]=1;
        current_weight+=weight[i];
        current_value+=value[i];
        backtrack(i+1);
        current_weight-=weight[i];
        current_value-=value[i];

    }
    if(bound(i+1)>bestvalue)
    {
        x[i]=0;
        backtrack(i+1);
    }
}
double Knapsack::bound(int i)
{
    double cleft=knapsack_capacity-current_weight;
    double bound =current_value;
    while(i<=object_number&&weight[i]<=cleft)
    {
        cleft-=weight[i];
        bound+=value[i];
        i++;
    }
    if(i<=object_number)
        bound+=value[i]*cleft/weight[i];
    return bound;
}
int main()
{
    Object obj[4]={{3,9},{5,10},{2,7},{1,4}};
    Knapsack myknapsack(obj,4,7);
    cout<<"背包容量为7"<<endl;
    cout<<"最优价值为:"<<endl;
    cout<<Knapsack::bestvalue<<endl;
    cout<<"物品重量为:"<<endl;
    for(int i=1;i<5;i++)
        cout<<myknapsack.weight[i]<<" ";
    cout<<endl;
    cout<<"物品价值为:"<<endl;
    for(int i=1;i<5;i++)
        cout<<myknapsack.value[i]<<" ";
    cout<<endl;
    cout<<"物品选择为:"<<endl;
    for(int i=1;i<5;i++)
        cout<<Knapsack::x[i]<<" ";
    return 0;
}
