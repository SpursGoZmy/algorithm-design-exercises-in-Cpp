#include <iostream>
#include<cstdlib>
#include<iomanip>
using namespace std;

class Matrix
{
public:
    int N;
    int **matrix;
    Matrix(int n):N(n)
    {
        matrix=new int*[N];
        for(int i=0;i<N;i++)
            matrix[i]=new int[N];
        for(int i=0;i<N;i++)
            for(int j=0;j<N;j++)
        {
            matrix[i][j]=0;
        }
    }
    Matrix(const Matrix& ano_matrix)
    {
        this->N=ano_matrix.N;
        this->matrix=new int*[N];
        for(int i=0;i<N;i++)
            this->matrix[i]=new int[N];
        for(int i=0;i<this->N;i++)
            for(int j=0;j<this->N;j++)
                  this->matrix[i][j]=ano_matrix.matrix[i][j];
    }
    Matrix& operator=(const Matrix& ano_matrix);
    Matrix operator+(const Matrix& ano_matrix);
    Matrix operator-(const Matrix& ano_matrix);
    Matrix operator*(const Matrix& ano_matrix);
    void print_matrix();
    void random_init();
    ~Matrix()
    {
        delete[] matrix;
    }

};
Matrix& Matrix::operator=(const Matrix& ano_matrix)
{
    if(ano_matrix.N!=this->N)
        cout<<"数组维数不同，无法赋值"<<endl;
    else
    {
        for(int i=0;i<this->N;i++)
            for(int j=0;j<this->N;j++)
                  this->matrix[i][j]=ano_matrix.matrix[i][j];

    }
    return *this;
}
Matrix Matrix::operator+(const Matrix& ano_matrix)
{
    Matrix sum(ano_matrix.N);
    if(ano_matrix.N!=this->N)
        cout<<"数组维数不同，无法相加"<<endl;
    else
    {
        for(int i=0;i<this->N;i++)
            for(int j=0;j<this->N;j++)
                 sum.matrix[i][j]=this->matrix[i][j]+ano_matrix.matrix[i][j];
    }
    return sum;
}
Matrix Matrix::operator-(const Matrix& ano_matrix)
{
    Matrix subtraction(ano_matrix.N);
    if(ano_matrix.N!=this->N)
        cout<<"数组维数不同，无法相减"<<endl;
    else
    {
        for(int i=0;i<this->N;i++)
            for(int j=0;j<this->N;j++)
                 subtraction.matrix[i][j]=this->matrix[i][j]-ano_matrix.matrix[i][j];
    }
    return subtraction;
}
Matrix Matrix::operator*(const Matrix& ano_matrix)
{
    Matrix mul(ano_matrix.N);
    if(ano_matrix.N!=this->N)
        cout<<"数组维数不同，无法相乘"<<endl;
    else
    {
        for(int i=0;i<this->N;i++)
            for(int j=0;j<this->N;j++)
            {
                mul.matrix[i][j]=0;
                for(int k=0;k<this->N;k++)
                    mul.matrix[i][j]+=this->matrix[i][k]*ano_matrix.matrix[k][j];
            }

    }
    return mul;
}
void Matrix::print_matrix()
{
    for(int i=0;i<this->N;i++)
    {
        for(int j=0;j<this->N;j++)
            cout<<setw(4)<<this->matrix[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}
void Matrix::random_init()
{
    for(int i=0;i<this->N;i++)
            for(int j=0;j<this->N;j++)
        {
            this->matrix[i][j]=rand()%5;
        }
}
void Strassen(Matrix& A, Matrix& B,Matrix& C)
{
    int m=A.N/2;
    Matrix A11(m);Matrix A12(m);Matrix A21(m);Matrix A22(m);
    Matrix B11(m);Matrix B12(m);Matrix B21(m);Matrix B22(m);
    Matrix C11(m);Matrix C12(m);Matrix C21(m);Matrix C22(m);
    Matrix M1(m);Matrix M2(m);Matrix M3(m);Matrix M4(m);Matrix M5(m);Matrix M6(m);Matrix M7(m);
    Matrix temp_1(m);Matrix temp_2(m);
    if(A.N==2)
        C=A*B;
    else
    {
        for(int i=0;i<m;i++)
            for(int j=0;j<m;j++)
            {
               A11.matrix[i][j] = A.matrix[i][j];
               A12.matrix[i][j] = A.matrix[i][j+m];
               A21.matrix[i][j] = A.matrix[i+m][j];
               A22.matrix[i][j] = A.matrix[i+m][j+m];

               B11.matrix[i][j] = B.matrix[i][j];
               B12.matrix[i][j] = B.matrix[i][j+m];
               B21.matrix[i][j] = B.matrix[i+m][j];
               B22.matrix[i][j] = B.matrix[i+m][j+m];
            }
        //计算M1
        temp_1=B12-B22;
        Strassen(A11,temp_1,M1);
        //计算M2
        temp_1=A11+A12;
        Strassen(temp_1,B22,M2);
        //计算M3
        temp_1=A21+A22;
        Strassen(temp_1,B11,M3);
        //计算M4
        temp_1=B21-B11;
        Strassen(A22,temp_1,M4);
        //计算M5
        temp_1=A11+A22;
        temp_2=B11+B22;
        Strassen(temp_1,temp_2,M5);
        //计算M6
        temp_1=A12-A22;
        temp_2=B21+B22;
        Strassen(temp_1,temp_2,M6);
        //计算M7
        temp_1=A11-A21;
        temp_2=B11+B12;
        Strassen(temp_1,temp_2,M7);
        //计算C11,C12,C13,C14
        C11=M5+M4-M2+M6;
        C12=M1+M2;
        C21=M3+M4;
        C22=M5+M1-M3-M7;

        //合并四个矩阵至C
        for(int i=0; i<m; i++)
           for(int j=0; j<m; j++) {
               C.matrix[i][j] = C11.matrix[i][j];
               C.matrix[i][j+m] = C12.matrix[i][j];
               C.matrix[i+m][j] = C21.matrix[i][j];
               C.matrix[i+m][j+m] = C22.matrix[i][j];
            }

    }
}
int main()
{
    Matrix A(8);
    Matrix B(8);
    Matrix C(8);

    A.random_init();
    B.random_init();
    Strassen(A,B,C);
    A.print_matrix();
    cout<<endl;
    B.print_matrix();
    cout<<endl;
    C.print_matrix();

    return 0;
}
