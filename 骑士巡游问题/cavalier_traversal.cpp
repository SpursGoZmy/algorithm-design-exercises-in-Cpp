#include <iostream>
#define chess_board_size 8
using namespace std;
int chess_board[chess_board_size][chess_board_size];
int chess_map[chess_board_size][chess_board_size];
bool find_path(int x_coordinate, int y_coordinate, int total_steps)
{
    if (x_coordinate<0||x_coordinate>chess_board_size-1||y_coordinate<0|| y_coordinate>chess_board_size-1)
    {
        return false;
    }
    if (chess_board[x_coordinate][y_coordinate] != 0)
    {
        return false;
    }
    if (total_steps==chess_board_size*chess_board_size-1)
    {
        chess_board[x_coordinate][y_coordinate]=chess_board_size*chess_board_size;
        return true;
    }
    total_steps++;
    chess_board[x_coordinate][y_coordinate]=total_steps;

    if(find_path(x_coordinate+1,y_coordinate+2,total_steps)) return true;
    if(find_path(x_coordinate+1,y_coordinate-2,total_steps)) return true;
    if(find_path(x_coordinate+2,y_coordinate+1,total_steps)) return true;
    if(find_path(x_coordinate+2,y_coordinate-1,total_steps)) return true;
    if(find_path(x_coordinate-1,y_coordinate+2,total_steps)) return true;
    if(find_path(x_coordinate-1,y_coordinate-2,total_steps)) return true;
    if(find_path(x_coordinate-2,y_coordinate+1,total_steps)) return true;
    if(find_path(x_coordinate-2,y_coordinate-1,total_steps)) return true;
    chess_board[x_coordinate][y_coordinate]=0;
    return false;
}
void print_path(int arrays[][chess_board_size])
{
    cout<<"+";
    for(int i=0;i<chess_board_size;i++)
        cout<<"---+";
    cout<<endl;
    for(int i=0;i<chess_board_size;i++)
    {
        cout<<"|";
        for(int j=0;j<chess_board_size;j++)
        {
            cout.width(3);
            cout<<arrays[i][j]<<"|";
        }
        cout<<endl;
        cout<<"+";
        for(int j=0;j<chess_board_size;j++)
            cout<<"---+";
        cout<<endl;
    }
}
bool if_possible(int x,int y)
{
    if(x<0||x>chess_board_size-1||y<0||y>chess_board_size-1)
    {
        return false;
    }
    if(chess_map[x][y]!=0)
    {
        return false;
    }
    return true;
}
int number_of_path(int x,int y)
{
    int possible_path_num=0;
    if(if_possible(x+1,y+2)) possible_path_num++;
    if(if_possible(x+1,y-2)) possible_path_num++;
    if(if_possible(x+2,y+1)) possible_path_num++;
    if(if_possible(x+2,y-1)) possible_path_num++;
    if(if_possible(x-1,y+2)) possible_path_num++;
    if(if_possible(x-1,y-2)) possible_path_num++;
    if(if_possible(x-2,y+1)) possible_path_num++;
    if(if_possible(x-2,y-1)) possible_path_num++;
    return possible_path_num;
}
void find_path2(int m,int n)
{
    int steps=1;
    int x=m,y=n;
    int temp_x,temp_y;
    chess_map[x][y]=steps;
    for(int i=0;i<chess_board_size*chess_board_size-1;i++)
    {
        int min_path_number=30;
        if(min_path_number>number_of_path(x+1,y+2)&&number_of_path(x+1,y+2)>=0&&if_possible(x+1,y+2))  //1
        {
            temp_x=x+1;
            temp_y=y+2;
            min_path_number=number_of_path(x+1,y+2);
        }
        if(min_path_number>number_of_path(x+1,y-2)&&number_of_path(x+1,y-2)>=0&&if_possible(x+1,y-2))  //2
        {
            temp_x=x+1;
            temp_y=y-2;
            min_path_number=number_of_path(x+1,y-2);
        }
        if(min_path_number>number_of_path(x+2,y+1)&&number_of_path(x+2,y+1)>=0&&if_possible(x+2,y+1))  //3
        {
            temp_x=x+2;
            temp_y=y+1;
            min_path_number=number_of_path(x+2,y+1);
        }
        if(min_path_number>number_of_path(x+2,y-1)&&number_of_path(x+2,y-1)>=0&&if_possible(x+2,y-1))  //4
        {
            temp_x=x+2;
            temp_y=y-1;
            min_path_number=number_of_path(x+2,y-1);
        }
        if(min_path_number>number_of_path(x-1,y+2)&&number_of_path(x-1,y+2)>=0&&if_possible(x-1,y+2))  //5
        {
            temp_x=x-1;
            temp_y=y+2;
            min_path_number=number_of_path(x-1,y+2);
        }
        if(min_path_number>number_of_path(x-1,y-2)&&number_of_path(x-1,y-2)>=0&&if_possible(x-1,y-2))  //6
        {
            temp_x=x-1;
            temp_y=y-2;
            min_path_number=number_of_path(x-1,y-2);
        }
        if(min_path_number>number_of_path(x-2,y+1)&&number_of_path(x-2,y+1)>=0&&if_possible(x-2,y+1))   //7
        {
            temp_x=x-2;
            temp_y=y+1;
            min_path_number=number_of_path(x-2,y+1);
        }
        if(min_path_number>number_of_path(x-2,y-1)&&number_of_path(x-2,y-1)>=0&&if_possible(x-2,y-1))  //8
        {
            temp_x=x-2;
            temp_y=y-1;
            min_path_number=number_of_path(x-2,y-1);
        }
        steps++;
        x=temp_x;
        y=temp_y;
        chess_map[x][y]=steps;
    }
}
int main()
{
       int x,y;
       cout<<"请输入起始坐标，空格隔开"<<endl;
       cin>>x>>y;
       cout<<"巡游路径为（回溯）:"<<endl;
       find_path(x,y,0);
       print_path(chess_board);
       cout<<endl;
       cout<<"巡游路径为（贪心）(以（3,3）为例:"<<endl;
       find_path2(3,3);
       print_path(chess_map);
//       for(int i=0;i<8;i++)
//       {
//           for(int j=0;j<8;j++)
//                cout<<chess_map[i][j]<<" ";
//            cout<<endl;
//       }
    return 0;
}

