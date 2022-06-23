#include "sudoku.h"
#include <fstream>
#include <iostream>

Sudoku::Sudoku() : board(9, QVector<Cell>(9, EMPTY))
{
}

Sudoku::~Sudoku()
{
}

void Sudoku::LoadBoardFromFile(int board_number)
{
    std::ifstream ifs;
    ifs.open(SUDOKU_GRID_FILE_NAME);

    if (!ifs.good())
    {
        std::cout << "Could not open input file: " << SUDOKU_GRID_FILE_NAME << std::endl;
        exit(1);
    }

    std::string line;
    while (std::getline(ifs, line))
    {
        if (line != "" && line[0] == '#' && stoi(line.substr(1, line.length())) == board_number)
        {
            std::getline(ifs, line);

            for (int i = 0; i < 9; ++i)
            {
                for (int j = 0; j < 9; ++j)
                {
                    if (line[j] != 0)
                    {
                        board[i][j].number = line[j] - '0';
                    }
                }
                std::getline(ifs, line);
            }
        }
    }
}

bool Sudoku::IsValidRow(int numberRow, int numberColumn, int number)
{
    for (int column = 0; column < 9; ++column)
    {
        if (column != numberColumn && board[numberRow][column].number == number)
        {
            return false;
        }
    }
    return true;
}

bool Sudoku::IsValidColumn(int numberRow, int numberColumn, int number)
{
    for (int row = 0; row < 9; ++row)
    {
        if (row != numberRow && board[row][numberColumn].number == number)
        {
            return false;
        }
    }
    return true;
}

bool Sudoku::IsValidSquare(int numberRow, int numberColumn, int number)
{
    int row = 3 * (numberRow / 3);
    int column = 3 * (numberColumn / 3);

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if ((row + i != numberRow || column + j != numberColumn) && (board[row + i][column + j].number == number))
            {
                return false;
            }
        }
    }
    return true;
}

bool Sudoku::IsValidPlace(int row, int column, int number)
{
    return (IsValidRow(row, column, number) && IsValidColumn(row, column, number) && IsValidSquare(row, column, number));
}

bool Sudoku::IsValidBoard(){
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
             if (!board[i][j].isValid){
                 return false;
             }
        }
    }
    return true;
}

bool Sudoku::IsNumber(const QString &str)
{
    bool ok;
    str.toInt(&ok, 10);
    return ok;
}

bool Sudoku::Backtrack(int row, int column, QVector<QVector<Cell>> & board){
    int next_row = (column == 8) ? (row + 1) : row;
    int next_column = (column + 1) % 9;

    if (row == 9)
    {
        return true;
    }

    if (board[row][column].number != EMPTY)
    {
        return Backtrack(next_row, next_column, board);
    }

    for (auto number : board[row][column].possibleNumbers)
    {
        board[row][column].number = number;

        if (IsValidPlace(row, column, number) && Backtrack(next_row, next_column, board))
        {
            return true;
        }

        board[row][column].number = EMPTY;
    }

    return false;
}

bool Sudoku::SolveBoard(QVector<QVector<Cell>> & board)
{
    if (Backtrack(0, 0 , board)){
        return true;
    }
    return false;

}
