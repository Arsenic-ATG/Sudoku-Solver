#include<iostream>
#include <cstdio>
using namespace std;
#include<math.h>

//This is the limit of size of sudoku board for now
//You can increase it, but at little cost on performance
#define MAX 10

int takeInput(int sudoku[MAX][MAX])
{
    int size = 9;       //just in case if I want to increase the size in future
    /*do
    {
        cout<<"Choose the size of board from\nEnter 1 for 9 X 9\nEnter 2 for 16 X 16\nEnter 3 for 25 X 25\n";
        cout<<"Your Selection:\t";
        cin>>size;
        switch(size)
        {
            case 1:
                size = 9;
                break;
            case 2:
                size = 16;
                break;
            case 3:
                size = 25;
                break;
            default:
                cout<<"Invalid Selection"<<endl;
                break;
        }
    }while(!size); //until valid board size is selected*/

    cout<<"Enter the Initial "<<size<<" X "<<size<<" Sudoku "<<endl;
    cout<<"Instruction: Enter 0 for blank"<<endl;
    
    for(int i=0;i<size;i++)
        for(int j=0;j<size; j++)
            cin>>sudoku[i][j];

    return size;
}

//Function to display solved Sudoku Board
void displaySolution(int sudoku[MAX][MAX], int size)
{
    for(int i=0;i<size;i++)
    {   
        if(i%3==0 && i)
        {
             for(int j=0;j<24; j++)
                {
                    cout<<"=";
                }
                cout<<endl;
        }   

        for(int j=0;j<size; j++)
        {
            if(j%3==0 && j) 
                cout<<"|| ";
            printf("%d ", sudoku[i][j]);     //for faster printing I have used printf instead of cout
        }
        cout<<endl;
    }
    cout<<"\n\n*************************************************\n\n";
}

//to check weater the sudoku is full or not
bool isFull(int sudoku[MAX][MAX], int size)
{
    int i,j;    
    for(i=0;i<size;i++)
        for(j=0;j<size;j++)
            if(!sudoku[i][j])
                return false;
    return true;
}

int findPossibleValues(int sudoku[MAX][MAX], int size, int a[], int r, int c)
{
    int n=0;
    int i,j;
    int s=(int)(sqrt(size));
    int b[MAX+1]={0};

    //Note no.s appeared in current row
    for(i=0; i<size; i++)
        b[sudoku[r][i]]=1;

    //Note no.s appeared in current column
    for(i=0; i<size; i++)
        b[sudoku[i][c]]=1;

    //Note no.s appeared in current block
    r=(r/s)*s, c=(c/s)*s;
    for(i=r; i<r+s; i++)
        for(j=c; j<c+s;j++)
            b[sudoku[i][j]]=1;

    //Fill array a[] with no.s unappeared in current row, column and block
    for(i=1;i<=size; i++)
        if(!b[i])
            a[n++]=i;

    return n;
}


void SolveSudoku(int sudoku[MAX][MAX], int size, int &solution_num, bool &solved_flag, bool &enough)
{
    int i,j, a[MAX+1]={0}, n=0;

    if(enough) //true if user does not want more solutions
        return;

    if(isFull(sudoku, size))    //true if now sudoku board is solved completely
    {

        if(!solved_flag)
            cout<<"Sudoku Solved Successfully!"<<endl;
        solved_flag = 1;

        //show the solution
       //cout<<"\n\nSolution no. "<<(solution_num++)<<endl;
        cout<<"Solution :- \n";
        displaySolution(sudoku, size);

        /*//users' choice
        char more;
        cout<<"Do you want more solutions?"<<endl;
        cout<<"Press 1 for 'YES', anything OTHERWISE:\t";
        cin>>more;*/
        //cout<<"\n\n*************************************************\n\n";

        return;
    }

    int break_flag = 0;
    for(i=0;i<size;i++)
    {
        for(j=0;j<size;j++)
            if(!sudoku[i][j])
            {
                break_flag = 1;
                break;
            }
        if(break_flag)
            break;
    }

    //check possibilities at that empty place
    n = findPossibleValues(sudoku, size, a, i, j);
    for(int l=0;l<n;l++)
    {
        sudoku[i][j]=a[l];
        //now solve the updated board
        SolveSudoku(sudoku, size, solution_num, solved_flag, enough);
    }

    sudoku[i][j]=0;
}

int main()
{
    int sudoku[MAX][MAX] = {0}, size;   //sudoku created here
    size = takeInput(sudoku);

    int solution_num = 1;
    bool solved_flag = 0;
    bool enough = false;

    //Processing
    cout<<"Finding Solutions!\n\n"<<endl;
    SolveSudoku(sudoku, size, solution_num, solved_flag, enough);

    //Exit if the board is invalid
    if(!solved_flag)
        cout<<"Invalid Board!"<<endl;

    cout<<"Exiting!\n\n"<<endl;

    return 0;
}
