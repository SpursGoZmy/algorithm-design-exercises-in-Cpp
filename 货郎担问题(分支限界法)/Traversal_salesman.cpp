#include <iostream>
#define vertex_number 4
#define heapSize 50
#define maxValue 500
using namespace std;
//���������
class HeapNode
{
public:
    float cost_lower_bound;//������������
    float current_cost;//��ǰ����
    float rest_cost; //ʣ��δ̽�����ķ�������
    int s;
    int x[vertex_number];
    HeapNode(float lower_bound,float ano_cc,float ano_rs,int ss,int xx[])
    {
        cost_lower_bound=lower_bound;
        current_cost=ano_cc;
        rest_cost=ano_rs;
        s=ss;
        for(int i=0;i<vertex_number;i++)
            x[i]=xx[i];
    }
    HeapNode(){}
    HeapNode(HeapNode& h)
    {
        this->cost_lower_bound=h.cost_lower_bound;
        this->current_cost=h.current_cost;
        this->rest_cost=h.rest_cost;
        this->s=h.s;
        for(int i=0;i<vertex_number;i++)
            this->x[i]=h.x[i];
    }
};
//����С����
typedef HeapNode HElemType;
typedef struct
{
    HElemType elem[heapSize];
    int curSize;
}minHeap;

void siftDown(minHeap& H,int i,int m)
{
    HElemType temp=H.elem[i];
    for(int j=2*i+1;j<=m;j=2*j+1)
    {
        if(j<m&&H.elem[j].cost_lower_bound>H.elem[j+1].cost_lower_bound) j++;
        if(temp.cost_lower_bound<=H.elem[j].cost_lower_bound) break;
        else
        {
            H.elem[i]=H.elem[j];
            i=j;
        }
    }
    H.elem[i]=temp;
}
void siftUp(minHeap& H,int start)
{
    HElemType temp=H.elem[start];
    int j=start, i=(j-1)/2;
    while(j>0)
    {
        if(H.elem[i].cost_lower_bound<=temp.cost_lower_bound) break;
        else
        {
            H.elem[j]=H.elem[i];
            j=i;
            i=(i-1)/2;
        }
    }
    H.elem[j]=temp;
}
bool Insert(minHeap& H,HElemType x)
{
    if(H.curSize== heapSize)
    {
        cout<<"������"<<endl;
        return false;
    }
    H.elem[H.curSize]=x;
    siftUp(H,H.curSize);
    H.curSize++;
    return true;
}
void creatMinHeap(minHeap& H,int n)
{
   // for(int i=0;i<n;i++) H.elem[i]=arr[i];
    H.curSize=n;
//    for(int i=(H.curSize-2)/2;i>=0;i--)
//        siftDown(H,i,H.curSize-1);
}
bool Remove(minHeap& H,HElemType& x)
{
    if(H.curSize==0)
    {
        cout<<"С����Ϊ��"<<endl;
        return false;
    }
    x=H.elem[0];
    H.elem[0]=H.elem[H.curSize-1];
    H.curSize--;
    siftDown(H,0,H.curSize-1);
    return true;
}
void traversal_salesman(float cost[][vertex_number+1])
{
    int n=vertex_number;
    minHeap heap;
    creatMinHeap(heap,0);
    float minOut[n+1];
    float minSum=0;
    for(int i=1;i<=n;i++)
    {
        float min=maxValue;
        for(int j=1;j<=n;j++)
        {
            if(cost[i][j]<maxValue&&cost[i][j]<min)
                min=cost[i][j];
        }
        if(min==maxValue) {cout<<"����ͨͼ�������ڹ��ܶٻ�·"<<endl; return;}
        minOut[i]=min;
        minSum+=min;
    }
//    for(int i=1;i<=n;i++)
//        cout<<minOut[i]<<" ";
//    cout<<endl;
    int x[vertex_number];
    for(int i=0;i<n;i++) x[i]=i+1;
    HeapNode enode(0,0,minSum,0,x);
//    for(int i=0;i<n;i++)
//        cout<<enode.x[i]<<" ";
//    cout<<endl;
    float best_cost=maxValue;
    while(enode.s<n-1)
    {
        for(int i=0;i<vertex_number;i++)
            x[i]=enode.x[i];
        if(enode.s==n-2)   //��ǰ��չ�ڵ���Ҷ�ڵ�ĸ��ڵ�
        {
            if(cost[x[n-2]][x[n-1]]<maxValue&&cost[x[n-1]][1]<maxValue&&enode.current_cost+cost[x[n-2]][x[n-1]]+cost[x[n-1]][1]<best_cost)
            {
                best_cost=enode.current_cost+cost[x[n-2]][x[n-1]]+cost[x[n-1]][1];
                enode.current_cost=best_cost;
                enode.cost_lower_bound=best_cost;
                enode.s++;
                Insert(heap,enode);
            }

        }
        else         //������ǰ��չ�ڵ�Ķ��ӽڵ�
        {
            for(int i=enode.s+1;i<n;i++)
                if(cost[x[enode.s]][x[i]]<maxValue)
            {
                float cc=enode.current_cost+cost[x[enode.s]][x[i]];
                float rcost=enode.rest_cost-minOut[x[enode.s]];
                float b=cc+rcost;
                if(b<best_cost)
                {
                    int xx[n];
                    for(int j=0;j<n;j++)
                        xx[j]=x[j];
                    xx[enode.s+1]=x[i];
                    xx[i]=x[enode.s+1];
                    HeapNode new_node(b,cc,rcost,enode.s+1,xx);
                    Insert(heap,new_node);
                }
            }
        }
        //�ж�С�����Ƿ�Ϊ�գ����Ƿ��л��㣬ȡ��ʹ���Ϊ��չ�ڵ�
        if(heap.curSize!=0)
            Remove(heap,enode);
        else
            {  cout<<"С�����ѿ�"<<endl;
               break;}

    }
    for(int i=0;i<n;i++)
        cout<<x[i]<<" ";
    cout<<x[0];
    cout<<endl;
    cout<<"best cost is "<<best_cost;
    return;
}
int main()
{
    //���þ���ֵ
    float cost[vertex_number+1][vertex_number+1];
    for(int i=1;i<=vertex_number;i++)
        {   for(int j=1;j<=vertex_number;j++)
            {
                cost[i][j]=maxValue;
            }
        }
    cost[1][2]=cost[2][1]=30;
    cost[1][3]=cost[3][1]=6;
    cost[1][4]=cost[4][1]=4;
    cost[3][2]=cost[2][3]=5;
    cost[3][4]=cost[4][3]=20;
    cost[2][4]=cost[4][2]=10;

    traversal_salesman(cost);
    return 0;
}
