#include <iostream>
#include <vector>

using namespace std;

const int BOARD_SIZE = 4;

void init_board(vector<vector<int>> &board)
{
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            board[row][col] = 0;
        }
    }
}

void init_game(bool &is_game_over, bool &is_won, vector<vector<int>> &board)
{
    srand(time(NULL));
    is_game_over = false;
    init_board(board);
}

void spawn_random_two(bool &is_game_over, vector<vector<int>> &board)
{
    vector<int *> empty_cells = {};

    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            if (board[row][col] == 0)
            {
                empty_cells.push_back(&board[row][col]);
            }
        }
    }

    if (empty_cells.size() == 0)
    {
        is_game_over = true;
        return;
    }

    int random_index = rand() % empty_cells.size();
    *empty_cells[random_index] = 2;
}

void print_board(vector<vector<int>> &board)
{
    cout << endl;

    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE; col++)
        {
            if (board[row][col] != 0)
            {
                cout << "\033[31m" << board[row][col] << "\033[0m";
            }
            else
            {
                cout << board[row][col];
            }
            if (col == BOARD_SIZE - 1)
            {
                cout << endl;
            }
            else
            {
                cout << "\t";
            }
        }
    }
}

char get_input()
{
    char input;

    while (true)
    {
        cout << "Enter w, a, s, or d: ";
        cin >> input;

        if (input == 'w' || input == 'a' || input == 's' || input == 'd')
        {
            return input;
        }

        cout << "Invalid, try again." << endl;
    }
}

void move_down(bool &is_won, vector<vector<int>> &board)
{
    for (int col = 0; col < BOARD_SIZE; col++)
    {
        for (int row = BOARD_SIZE - 1; row > 0; row--)
        {
            if (board[row][col] == 0)
            {
                for (int aboveRow = row - 1; aboveRow >= 0; aboveRow--)
                {
                    if (board[aboveRow][col] != 0)
                    {
                        board[row][col] = board[aboveRow][col];
                        board[aboveRow][col] = 0;
                        break;
                    }
                }
            }
            if (board[row][col] != 0)
            {
                for (int aboveRow = row - 1; aboveRow >= 0; aboveRow--)
                {
                    if (board[aboveRow][col] != 0 && board[aboveRow][col] != board[row][col])
                        break;

                    if (board[aboveRow][col] == board[row][col])
                    {
                        board[row][col] *= 2;

                        if (board[row][col] == 2048)
                            is_won = true;

                        board[aboveRow][col] = 0;
                        break;
                    }
                }
            }
        }
    }
}

void move_right(bool &is_won, vector<vector<int>> &board)
{
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = BOARD_SIZE - 1; col > 0; col--)
        {
            if (board[row][col] == 0)
            {
                for (int leftCol = col - 1; leftCol >= 0; leftCol--)
                {
                    if (board[row][leftCol] != 0)
                    {
                        board[row][col] = board[row][leftCol];
                        board[row][leftCol] = 0;
                        break;
                    }
                }
            }
            if (board[row][col] != 0)
            {
                for (int leftCol = col - 1; leftCol >= 0; leftCol--)
                {
                    if (board[row][leftCol] != 0 && board[row][leftCol] == board[row][col])
                        break;

                    if (board[row][leftCol] == board[row][col])
                    {
                        board[row][col] *= 2;

                        if (board[row][col] == 2048)
                            is_won = true;

                        board[row][leftCol] = 0;
                        break;
                    }
                }
            }
        }
    }
}

void reverse_horizontally(vector<vector<int>> &board)
{
    for (int row = 0; row < BOARD_SIZE; row++)
    {
        for (int col = 0; col < BOARD_SIZE / 2; col++)
        {
            int temp = board[row][col];
            board[row][col] = board[row][BOARD_SIZE - col - 1];
            board[row][BOARD_SIZE - col - 1] = temp;
        }
    }
}

void reverse_vertically(vector<vector<int>> &board)
{
    for (int col = 0; col < BOARD_SIZE; col++)
    {
        for (int row = 0; row < BOARD_SIZE / 2; row++)
        {
            int temp = board[row][col];
            board[row][col] = board[BOARD_SIZE - row - 1][col];
            board[BOARD_SIZE - row - 1][col] = temp;
        }
    }
}

void move_left(bool &is_won, vector<vector<int>> &board)
{
    reverse_horizontally(board);
    move_right(is_won, board);
    reverse_horizontally(board);
}

void move_up(bool &is_won, vector<vector<int>> &board)
{
    reverse_vertically(board);
    move_down(is_won, board);
    reverse_vertically(board);
}

int main()
{
    bool is_game_over = false;
    bool is_won = false;
    vector<vector<int>> board(BOARD_SIZE, vector<int>(BOARD_SIZE));

    init_game(is_game_over, is_won, board);

    while (is_game_over == false)
    {
        spawn_random_two(is_game_over, board);
        print_board(board);

        char input = get_input();

        switch (input)
        {
        case 's':
            move_down(is_won, board);
            break;
        case 'd':
            move_right(is_won, board);
            break;
        case 'a':
            move_left(is_won, board);
            break;
        case 'w':
            move_up(is_won, board);
            break;
        default:
            cout << "Invalid, try again." << endl;
            break;
        }
    }

    if (is_won)
    {
        cout << "You won." << endl;
    }
    else
    {
        cout << "take the L lmao." << endl;
    }
}