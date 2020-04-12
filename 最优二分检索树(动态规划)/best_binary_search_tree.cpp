#include <iostream>
#define N 5
using namespace std;


void OptimalBinarySearchTree(float *a,float *b,int n,float m[][N+2],int s[][N+1],float w[][N+2])
{
    for (int i = 0; i <= n; i++)  {
       w[i+1][i]=a[i];      //����ֵ
       m[i+1][i]=0; }
    for (int r = 0; r < n; r++) //rΪ��������
       for(int i=1; i<=n-r; i++) {
          int j=i+r;   // jΪ����tij���յ��±�
          w[i][j]=w[i][j-1]+a[j]+b[j];
          m[i][j]=m[i+1][j];
          s[i][j]=i;
          for (int k=i+1; k<=j; k++) {    //����С��m(i,k-1)+m(k+1,j)
             float t=m[i][k-1]+m[k+1][j];
             if (t<m[i][j]) { m[i][j]=t;  s[i][j]=k; }
           }
           m[i][j]+=w[i][j];
      }
}

int main()
{
    float a[N+1]={0.05,0.10,0.05,0.05,0.05,0.10};
    float b[N+1]={0,0.15,0.10,0.05,0.10,0.20};
    float m[N+2][N+2];
    int s[N+1][N+1];
    float w[N+2][N+2];
    OptimalBinarySearchTree(a,b,5,m,s,w);
    cout<<"��Сƽ��·��Ϊ "<<m[1][N]<<endl;
    cout<<"���ڵ�Ϊ "<<s[1][N]<<endl;
    return 0;
}
