
// make sure to make a file named "ids.txt" in the same folder where the cpp file is
          
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<iomanip>
#include<conio.h>
#include<windows.h>
#include<string>
#include<fstream>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
using namespace std;
//Function protypes
const int length = 5;
//board related
void init(int[][length]);
void goal(int[][length]);
void board(int[][length], int[][length]);

// move related
void print_path(char[]);
void legal_moves(int[][length], int[]);
bool valid_input(int, int[]);
void make_Move(int[][length], int);

// logical
bool is_Solveable(int[][length], int[][length]);
bool is_Goal(int[][length], int[][length]);

// menu related
void mainMenu();
bool goBack();
void playGame(int init_board[][length], int goal_board[][length], int valid_moves[], int id);
void howToPlay();

//file handling related
void filehandlingout(int, int[][length], int[][length]);
void filehandlingin(int, int[][length], int[][length]);
void showid();
void storeid(int);
bool idFound(int);

//array to store all moves 
char moves[1000];
int randomizer()
{
    return rand() % 4;
}
int main()
{

    mainMenu();
    return 1;
    //return 0;
}

//MAIN MENU PRINT
void mainMenu()
{

    char x;
    bool flag = true;

    srand(time(0));


    int init_board[length][length]{ 0 };
    int goal_board[length][length]{ 0 };
    int valid[length][length]{ 0 };
    int input[4]{};
    int valid_moves[4]{};
    int index = 0;
    int num = 0, id;
    bool moveable = false;
    char cont;

    do
    {
        system("cls");
        SetConsoleTextAttribute(hConsole, 3);
        cout << "\t\t\tWelcome to 24-Puzzle game ;)\n";

        cout << "1) New Game\n"
            << "2) Load Game\n"
            << "3) How to Play?\n"
            << "4) Exit\n"
            << "\n\nChoose one: ";
        cin >> x;
        cin.ignore();
        switch (x)
        {
        case'1':
        {
            /// randomly generates an id that ranges from 1000 to 10000
            id = rand() % 9000 + 1000;

            init(init_board);
            do
            {
                goal(goal_board);
            } while (!(is_Solveable(init_board, goal_board)));
            playGame(init_board, goal_board, valid_moves, id);    //STARTS THE GAME
            flag = goBack();
            break;
        }
        case'2':
        {
            cout << "\nPrevious id were: \n";
            showid();
            int idtogive;
            do {
                cout << "Enter your id: ";
                cin >> idtogive;
                if (!idFound(idtogive))
                    cout << "\nPlease enter a valid id!\n";
            } while (!idFound(idtogive));
            filehandlingin(idtogive, init_board, goal_board);
            id = idtogive;
            playGame(init_board, goal_board, valid_moves, id);
            flag = goBack();
            break;
        }
        case'3':
        {
            howToPlay();

            flag = goBack();
            break;
        }
        case'4':
        {
            ////exit()
            flag = false;
            break;
        }
        default:
        {
            cout << "Invalid Choice\n Try again";
            flag = true;
            break;
        }
        }
    } while (flag);
}
// play game function
void playGame(int init_board[][length], int goal_board[][length], int valid_moves[], int id)
{
    bool flag = true;
    while (flag)
    {

        system("cls");
        SetConsoleTextAttribute(hConsole, 3);
        cout << "\t\t\tWelcome to 24-Puzzle game ;)\n";
        cout << "\t\t\t\tYour id is: " << id << endl;
        SetConsoleTextAttribute(hConsole, 6);
        cout << "\nInitial Board\t\t\t      Goal board\n";
        board(init_board, goal_board);
        legal_moves(init_board, valid_moves);
        if (is_Goal(init_board, goal_board))
        {
            cout << setw(50) << "***************************\n";
            cout << setw(44) << "CONGRATULATIONS\n";
            cout << setw(52) << "***************************\n\n\n";
            break;
        }
        //cout << "\n \n valid moves: ";
        //for (int i = 0; i < 4; i++)
        //{
        //    cout << ptr[i] << " ";
        //}
        int key;
        SetConsoleTextAttribute(hConsole, 2);
        cout << "\nMake move(press 1 to stop): ";
        do {
            key = _getch();
            //key = randomizer();
            if (key == '1')
            {
                if (!idFound(id))
                    storeid(id);
                filehandlingout(id, init_board, goal_board);
                flag = false;
                break;
            }
        } while (!(valid_input(key, valid_moves) && !(is_Goal(init_board, goal_board))));

        if (is_Goal(init_board, goal_board) && flag)
        {
            continue;
        }
        make_Move(init_board, key);
    }
    print_path(moves);
}
// initial state 
void init(int init_board[][length])
{

    int temp = 0, i = 0, j = 0;
    bool flag = true;

    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            init_board[i][j] = -1;
        }
    }
    for (int k = 1; k <= length * length - 1; k++)
    {
        flag = true;
        while (flag)
        {
            flag = true;
            i = rand() % length;
            j = rand() % length;
            if (init_board[i][j] == -1)
            {
                init_board[i][j] = k;
                flag = 0;
            }
        }

    }
    //board(init_board);



}
// goal state
void goal(int goal_board[][length])
{

    int temp = 0, i = 0, j = 0;
    bool flag = true;
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            goal_board[i][j] = -1;
        }
    }

    for (int k = 1; k <= length * length - 1; k++)
    {
        flag = true;
        while (flag)
        {
            flag = true;
            i = rand() % length;
            j = rand() % length;
            if (goal_board[i][j] == -1)
            {
                goal_board[i][j] = k;
                flag = 0;
            }
        }

    }

}
/// Valid moves functions returns array of valid moves, 0 == up, 1 == down, 2 === left, 3 == right ////
void legal_moves(int init_board[][length], int valid[])
{
    //static int valid[4]{0};
    for (int i = 0; i < 4; i++)
    {
        valid[i] = -1;
    }

    int row = 0, col = 0;

    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            if (-1 == init_board[i][j])
            {
                row = i;
                col = j;
                break;
            }
        }
    }

    if (row > 0 && row < length - 1)
    {
        if (col > 0 && col < length - 1)
        {
            for (int i = 0; i < 4; i++)
            {
                valid[i] = i;
            }
        }

        else if (col == 0)
        {
            valid[0] = 0, valid[1] = 1, valid[3] = 3;
        }
        else if (col == length - 1)
        {
            valid[0] = 0, valid[1] = 1, valid[2] = 2;
        }
    }
    else if (row == 0)
    {
        if (col > 0 && col < length - 1)
        {
            for (int i = 0; i < 4; i++)
            {
                valid[i] = i;
            }
            valid[1] = -1;
        }
        else if (col == 0)
        {
            valid[0] = 0, valid[3] = 3;
        }
        else if (col == length - 1)
        {
            valid[0] = 0, valid[2] = 2;
        }

    }
    else if (row == length - 1)
    {
        if (col > 0 && col < length - 1)
        {
            for (int i = 0; i < 4; i++)
            {
                valid[i] = i;
            }
            valid[0] = -1;
        }
        else if (col == 0)
        {
            valid[1] = 1, valid[3] = 3;
        }
        else if (col == length - 1)
        {
            valid[1] = 1, valid[2] = 2;
        }

    }


}
/// valid input function returns true if input is valid
bool valid_input(int move, int valid[])
{
    int m = move;
    bool flag = false;
    switch (move) {

    case 72:
        m = 0;  // key up will make the blank space go down
        break;
    case 80:
        m = 1;
        break;
    case 75:
        m = 3;
        break;
    case 77:
        m = 2;
        break;
    }
    for (int i = 0; i < 4; ++i)
    {
        if (valid[i] == m)
        {
            flag = true;
            break;
        }
    }
    return flag;
}
///solvable functions returns true if both boards have same inversions
bool is_Solveable(int init[][length], int goal[][length])
{
    bool flag = false;
    int inversions_int = 0, inversions_goal = 0;
    int init_1d[length * length]{}, goal_1d[length * length]{};
    //converting the 2d arrays into 1d.
    int k = 0;
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            init_1d[k++] = init[i][j];
        }
    }
    k = 0;
    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            goal_1d[k++] = goal[i][j];
        }
    }
    //finding the inversions
    for (int i = 0; i < length * length; i++)
    {
        for (int j = i + 1; j < length * length; j++)
        {
            if (init_1d[i] > init_1d[j])
            {
                inversions_int++;
            }
        }
    }
    for (int i = 0; i < length * length; i++)
    {
        for (int j = i + 1; j < length * length; j++)
        {
            if (goal_1d[i] > goal_1d[j])
            {
                inversions_goal++;
            }
        }
    }
    // checking if the inversions of both boards
    if ((inversions_int % 2 == inversions_goal % 2))
    {
        flag = true;
    }
    return flag;
}
bool is_Goal(int init[][length], int goal[][length])
{
    bool flag = true;
    for (int i = 0; i < length; ++i)
    {
        for (int j = 0; j < length; ++j)
        {
            if (init[i][j] != goal[i][j])
            {
                flag = false;
            }
        }
    }
    return flag;
}
void make_Move(int init[][length], int move)
{
    int row = 0, col = 0;

    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            if (-1 == init[i][j])
            {
                row = i;
                col = j;
                break;
            }
        }
    }
    int temp;
    static int i = 0;
    switch (move) {
    case 72:

        temp = init[row + 1][col];
        init[row + 1][col] = init[row][col];
        init[row][col] = temp;
        moves[i++] = 'U';   // key up will make the blank space go down
        break;
    case 80:
        temp = init[row - 1][col];
        init[row - 1][col] = init[row][col];
        init[row][col] = temp;  // key down will make the blank space go up
        moves[i++] = 'D';
        break;
    case 75:
        temp = init[row][col + 1];
        init[row][col + 1] = init[row][col];
        init[row][col] = temp;  // key right will make the blank space go left
        moves[i++] = 'L';
        break;
    case 77:
        temp = init[row][col - 1];
        init[row][col - 1] = init[row][col];
        init[row][col] = temp;  // key left will make the blank space go right
        moves[i++] = 'R';
        break;
    }

}
/// print board
void board(int arr[][length], int arr1[][length])
{

    SetConsoleTextAttribute(hConsole, 6);
    cout << " ------------------------------       ------------------------------ " << endl;
    for (int i = 0; i < length; i++)
    {
        SetConsoleTextAttribute(hConsole, 5);
        for (int j = 0; j < length; j++)
        {
            if (arr[i][j] == -1)
            {
                cout << "|" << setw(5) << " ";
            }
            else
            {
                cout << "|" << setw(4) << arr[i][j] << " ";
            }


        }

        cout << " |     ";
        SetConsoleTextAttribute(hConsole, 3);
        for (int k = 0; k < length; k++)
        {

            if (arr1[i][k] == -1)
            {
                cout << "|" << setw(5) << " ";
            }
            else
            {
                cout << "|" << setw(4) << arr1[i][k] << " ";
            }


        }

        cout << " |     " << endl;
        SetConsoleTextAttribute(hConsole, 6);

        if (4 == i)
        {
            cout << " ------------------------------       ------------------------------ " << endl;
        }
        else
            cout << " ----- ----- ----- ----- ------       ----- ----- ----- ----- ------" << endl;
    }
}
// prints the path that is entered to reach the goal state
void print_path(char moves[])

{
    SetConsoleTextAttribute(hConsole, 3);
    cout << "\nMoves to reach the current state were: ";
    int size = strlen(moves);
    cout << moves[0];
    for (int i = 1; i < size; ++i)
    {
        cout << ", " << moves[i];
    }
    cout << "\n\n\n";
    SetConsoleTextAttribute(hConsole, 1);
}
// used to store the current state in file 
void filehandlingout(int id, int init[][length], int goal[][length])
{
    ofstream fout;
    string filename = to_string(id);

    fout.open(filename + ".txt");
    if (!fout)
    {
        cout << "file couldnt open\n";
    }
    else
    {
        for (int i = 0; i < length; ++i)
        {
            for (int j = 0; j < length; ++j)
            {
                fout << init[i][j] << " ";
            }
            fout << endl;
        }
        for (int i = 0; i < length; ++i)
        {
            for (int j = 0; j < length; ++j)
            {
                fout << goal[i][j] << " ";
            }
            fout << endl;
        }

    }
}
// used to get the values of boards if the user wants to resume
void filehandlingin(int id, int init[][length], int goal[][length])
{
    fstream fin;

    string filename = to_string(id);

    fin.open(filename + ".txt", ios::in);
    if (!fin)
    {
        cout << "Couldnt open file\n";
    }
    else
    {
        for (int i = 0; i < length; ++i)
        {
            for (int j = 0; j < length; ++j)
            {
                fin >> init[i][j];
            }

        }
        for (int i = 0; i < length; ++i)
        {
            for (int j = 0; j < length; ++j)
            {
                fin >> goal[i][j];
            }

        }

    }
}
// stores an id in id.txt file 
void storeid(int id)
{
    fstream file;
    file.open("ids.txt", ios::app);

    if (!file)
    {
        cout << "Couldnt open file\n";
    }
    else
    {
        file << id << endl;
    }

}
// shows the existing ids
void showid()
{
    fstream file;
    int id;
    file.open("ids.txt", ios::in);
    if (!file)
    {
        cout << "Couldnt open file\n";
    }
    else
    {

        while (!file.eof())
        {

            file >> id;
            if (!file.eof())
            {
                cout << id << endl;

            }

        }
    }
}
bool idFound(int id)
{
    int idtemp;
    bool flag = false;
    fstream file;
    file.open("ids.txt", ios::in);
    if (!file)
    {
        cout << "Couldnt open file\n";
    }
    else
    {
        while (!file.eof())
        {
            file >> idtemp;
            if (!file.eof())
            {
                if (idtemp == id)
                {
                    flag = true;
                    break;
                }
            }
        }
    }
    return flag;
}
// GO BACK TO MAIN MENU
bool goBack()
{
    char press;
    bool flag;
    SetConsoleTextAttribute(hConsole, 3);
    cout << "\nIf you want to go back press any button \nTo exit press 0\n";
    press = _getch();
    if (press != '0')
    {
        flag = true;
    }
    else {
        flag = false;
    }
    return flag;
}
void howToPlay()
{
    system("cls");
    SetConsoleTextAttribute(hConsole, 6);
    cout << "The 24 puzzle game invented and popularized by Noyes Palmer Chapman in the 1870s.\n"
        << "It is played on a 5 - by - 5 grid with 15 square blocks labeled 1 through 15 and a blank square.\nThere are two boards, one is the board you play game at, other"
        << "\nis the goal state we want to achieve.\nYour goal is to rearrange the tiles / blocks so that they are in order specified as goal state\n"
        << "\n\nUse arrow keys to move the blocks\n";
}
