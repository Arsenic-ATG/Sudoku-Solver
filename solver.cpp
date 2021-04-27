#include <fstream>
#include <iostream>
#include <cmath>
#include <vector>

/**** sudoku class ****/
class sudoku {
    const int MAX;
    std::vector <std::vector<int>> board;
    bool is_solved;
    bool is_full();
    int find_possible_values(std::vector<int> &, int , int );

public:
    sudoku() : MAX(9)
    {
        is_solved = false;

        // resize the vector
        board.resize(MAX);
        for (int i = 0; i < MAX; ++i)
            board[i].resize(MAX);

        // generate a blank board
        for (int i = 0; i < MAX; ++i)
            for (int j = 0; j < MAX; ++j)
                board[i][j] = 0;
    }

    // TODO: create generate_sudoku() to generate a random board on call
    // void take_input();
    // void display_solution();
    void solve();
    friend std::istream &operator >>( std::istream  &input,sudoku &);
    friend std::ostream &operator <<( std::ostream &, const sudoku &);

};

/**** function definitions ****/

std::istream &operator >>( std::istream  &input , sudoku &s)
{
    for(int i = 0 ; i < (s.MAX) ; i++)
        for(int j = 0 ; j < (s.MAX) ; j++)
            input>>s.board[i][j];

    return input;
}

// pretty print sudoku board to console
std::ostream &operator <<( std::ostream & output, const sudoku &s)
{
    for(int i = 0;i < (s.MAX) ;i++)
    {   
        if(i%3 == 0 && i)
        {
             for(int j = 0;j < 24; j++)
                {
                    output<<"=";
                }
                output<<'\n';
        }   

        for(int j = 0;j < (s.MAX); j++)
        {
            if(j%3 == 0 && j) 
                output<<"|| ";
            output<<s.board[i][j]<<" ";
        }
        output<<std::endl;
    }
    output<<"\n\n*************************************************\n\n";

    return output;
}

//to check whether the board is full or not
bool sudoku::is_full()
{
    for(int i = 0 ; i < (MAX) ; i++)
        for(int j = 0 ; j < (MAX) ; j++)
            if(board[i][j] == 0)
                return false;
    return true;
}

int sudoku::find_possible_values(std::vector<int> &possible_values, int r, int c)
{
    int n = 0;
    int i,j;
    const int s = static_cast<int>(sqrt((MAX)));
    std::vector<int> b(MAX+1,0);

    // Note numbers appeared in current row
    for(i = 0; i < (MAX) ; i++)
        b[board[r][i]] = 1;

    // Note numbers appeared in current column
    for(i = 0; i < (MAX) ; i++)
        b[board[i][c]] = 1;

    // Note numbers appeared in current block
    r = (r/s)*s, c = (c/s)*s;
    for(i = r; i < r+s; i++)
        for(j = c ; j < c+s ; j++)
            b[board[i][j]] = 1;

    // Fill array possible_values[] with numbers that can be filled in that perticular cell
    for(i = 1 ; i <= (MAX); i++)
        if(!b[i])
            possible_values[n++] = i;

    return n;
}


void sudoku::solve()
{
    int i, j, n = 0;
    std::vector<int> possible_values(MAX+1,0);

    // base case
    if(is_solved || is_full())
    {
        is_solved = 1;
        return;
    }

    // find next empty place on board
    bool break_flag = 0;
    for(i = 0 ; i < (MAX) ; i++)
    {
        for(j = 0 ; j < (MAX) ; j++)
            if(!board[i][j])
            {
                break_flag = 1;
                break;
            }

        if(break_flag)
            break;
    }

    // fill the array with all the possible values that we can fill in that empty cell
    n = find_possible_values(possible_values, i, j);
    for(int l = 0 ; l < n ; l++)
    {
        board[i][j] = possible_values[l];
        // solve the updated board
        solve();

        if(is_solved)
            return;
    }

    // nothing worked so reset and backtrack
    board[i][j] = 0;
}


/**** the main() function ****/

int main()
{
    // configuring vars
    sudoku board;

    // Input
    std::cout<<"Enter the Initial "<< 9 <<" X "<< 9 <<" Sudoku "<<std::endl;
    std::cout<<"Instruction: Enter 0 for blank"<<std::endl;   
    std::cin >> board;

    // Processing
    std::cout << "\n\nFinding Solution!\n\n";
    board.solve();

    // output
    std::cout << board;

    return 0;
}