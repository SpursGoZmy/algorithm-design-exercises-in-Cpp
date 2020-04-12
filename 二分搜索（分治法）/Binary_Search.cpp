#include <iostream>

using namespace std;

int Binary_Search(int a[],int array_length,int target_element)
{
    int left=0,right=array_length-1;
    while(left<=right)
    {
        int middle =(left+right)/2;
        if(target_element==a[middle])
            return middle+1;
        else if(target_element>a[middle])
            left=middle+1;
        else
            right=middle-1;
    }
    return -1;
}
int main()
{

    int array_lengh;
    cout<<"���������鳤�ȣ�"<<endl;
    cin>>array_lengh;
    int a[array_lengh];
    cout<<"����������Ԫ��:"<<endl;
    for(int i=0;i<array_lengh;i++)
        cin>>a[i];
    int target_element;
    cout<<"������Ҫ���ҵ�Ԫ��:"<<endl;
    cin>>target_element;
    int result=Binary_Search(a,array_lengh,target_element);
    if(result>0)
        cout<<"����Ԫ�ش��ڵ�"<<result<<"λ"<<endl;
    else
        cout<<"����Ԫ�ز�����"<<endl;
    return 0;
}
