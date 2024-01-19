#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

const int EASY_ROWS = 9;
const int EASY_COLS = 9;
const int EASY_MINES = 10;

const int MEDIUM_ROWS = 16;
const int MEDIUM_COLS = 16;
const int MEDIUM_MINES = 40;

const int EXPERT_ROWS = 16;
const int EXPERT_COLS = 30;
const int EXPERT_MINES = 99;

vector<vector<char>> gameBoard;
vector<vector<bool>> revealed;
int rows, cols, numMines;

void initializeGame()
{
    gameBoard.assign(rows, vector<char>(cols, ' '));
    revealed.assign(rows, vector<bool>(cols, false));
}

void printBoard()
{
    cout << "DEVELOPED BY NGUYEN HO QUANG KHAI" << endl << endl;

    cout << "    ";
    for (int i = 0; i < cols; i++)
        cout << i + 1 << " ";
    cout << endl;

    for (int i = 0; i < rows; i++)
    {
        cout << "  " << i + 1 << " ";
        for (int j = 0; j < cols; j++)
        {
            if (revealed[i][j])
            {
                if (gameBoard[i][j] == 'X')
                    cout << "\033[1;31m" << gameBoard[i][j] << " ";
                else
                    cout << gameBoard[i][j] << " ";
            }
            else
            {
                cout << "- ";
            }
        }
        cout << endl;
    }
}

void placeMines()
{
    srand(time(NULL));

    int count = 0;
    while (count < numMines)
    {
        int randRow = rand() % rows;
        int randCol = rand() % cols;

        if (gameBoard[randRow][randCol] != 'X')
        {
            gameBoard[randRow][randCol] = 'X';
            count++;
        }
    }
}

bool isValid(int row, int col)
{
    return (row >= 0 && row < rows && col >= 0 && col < cols);
}

int countAdjacentMines(int row, int col)
{
    int count = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            int newRow = row + i;
            int newCol = col + j;
            if (isValid(newRow, newCol) && gameBoard[newRow][newCol] == 'X')
                count++;
        }
    }
    return count;
}

void revealCell(int row, int col)
{
    if (!isValid(row, col) || revealed[row][col])
        return;

    revealed[row][col] = true;

    if (gameBoard[row][col] == 'X')
        return;

    int count = countAdjacentMines(row, col);
    gameBoard[row][col] = count + '0';

    if (count == 0)
    {
        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                int newRow = row + i;
                int newCol = col + j;
                revealCell(newRow, newCol);
            }
        }
    }
}

bool hasWon()
{
    int numUnrevealed = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (!revealed[i][j])
                numUnrevealed++;
        }
    }
    return numUnrevealed == numMines;
}

void playGame()
{
    initializeGame();
    placeMines();

    bool gameOver = false;

    while (!gameOver)
    {
        printBoard();

        int row, col;
        cout << "Nhap so thu tu hang: ";
        cin >> row;
        cout << "Nhap so thu hang cot: ";
        cin >> col;

        row--;
        col--;

        if (!isValid(row, col))
        {
            cout << "Invalid cell. Please try again." << endl;
            continue;
        }

        if (gameBoard[row][col] == 'X')
        {
            cout << "Ban thua roi! Ban trung bom. Game over!" << endl;
            gameOver = true;
        }
        else
        {
            revealCell(row, col);
            if (hasWon())
            {
                printBoard();
                cout << "Chuc mung! Ban da thang!" << endl;
                gameOver = true;
            }
        }
    }
}

int main()
{
    int choice;
    cout << "===== MINESWEEPER =====" << endl;
    cout << "1. Start game" << endl;
    cout << "2. Quit game" << endl;
    cout << "3. Mode" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        rows = EASY_ROWS;
        cols = EASY_COLS;
        numMines = EASY_MINES;
        playGame();
        break;
    case 2:
        cout << "Quitting the game..." << endl;
        break;
    case 3:
        int modeChoice;
        cout << "===== MODE =====" << endl;
        cout << "1. Easy" << endl;
        cout << "2. Medium" << endl;
        cout << "3. Expert" << endl;
        cout << "Enter your choice: ";
        cin >> modeChoice;

        switch (modeChoice)
        {
        case 1:
            rows = EASY_ROWS;
            cols = EASY_COLS;
            numMines = EASY_MINES;
            playGame();
            break;
        case 2:
            rows = MEDIUM_ROWS;
            cols = MEDIUM_COLS;
            numMines = MEDIUM_MINES;
            playGame();
            break;
        case 3:
            rows = EXPERT_ROWS;
            cols = EXPERT_COLS;
            numMines = EXPERT_MINES;
            playGame();
            break;
        default:
            cout << "Invalid choice. Quitting the game..." << endl;
        }
        break;
    default:
        cout << "Invalid choice. Quitting the game..." << endl;
    }

    return 0;
}
