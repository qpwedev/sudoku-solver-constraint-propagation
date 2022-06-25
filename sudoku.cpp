#include "sudoku.h"
#include <fstream>
#include <iostream>
#include <QDebug>

Sudoku::Sudoku() : board(9, QVector<Cell>(9, EMPTY_CELL_VALUE)) {}

Sudoku::~Sudoku() {}

void Sudoku::LoadBoardFromFile(int board_number)
{
    std::ifstream ifs;
    ifs.open(SUDOKU_GRID_FILE_NAME);

    CreateNewBoard();

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

void Sudoku::CreateNewBoard()
{
    QVector<QVector<Cell>> newBoard(9, QVector<Cell>(9, EMPTY_CELL_VALUE));
    board = newBoard;
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

bool Sudoku::IsValidBoard()
{
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 9; ++j)
        {
            if (!board[i][j].isValid)
            {
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

bool Sudoku::Backtrack(int row, int column, QVector<QVector<Cell>> &board)
{
    int next_row = (column == 8) ? (row + 1) : row;
    int next_column = (column + 1) % 9;

    if (row == 9)
    {
        return true;
    }

    if (board[row][column].number != EMPTY_CELL_VALUE)
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

        board[row][column].number = EMPTY_CELL_VALUE;
    }

    return false;
}

bool Sudoku::Elimination(QVector<QVector<Cell>> &board)
{
    bool modified = false;

    for (int row = 0; row < 9; row++)
    {
        for (int column = 0; column < 9; column++)
        {
            if (board[row][column].hasValue())
            {
                if (PropagateEliminationConstraint(row, column, board))
                {
                    modified = true;
                }
            }
        }
    }

    return modified;
}

bool Sudoku::PropagateEliminationConstraint(int numberRow, int numberColumn, QVector<QVector<Cell>> &board)
{
    bool modified = false;
    int number = board[numberRow][numberColumn].number;

    // row number elimination
    for (int column = 0; column < 9; ++column)
    {
        if ((column != numberColumn) && board[numberRow][column].deleteConstraintNumber(number))
        {
            modified = true;
        }
    }

    // column number elimination
    for (int row = 0; row < 9; ++row)
    {
        if ((row != numberRow) && board[row][numberColumn].deleteConstraintNumber(number))
        {
            modified = true;
        }
    }

    // square number elimination
    int initialRow = 3 * (numberRow / 3);
    int initialColumn = 3 * (numberColumn / 3);

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (!(initialRow + i == numberRow && initialColumn + j == numberColumn) && board[initialRow + i][initialColumn + j].deleteConstraintNumber(number))
            {
                modified = true;
            }
        }
    }

    return modified;
}

bool Sudoku::CheckOnlyChoiseExistance(int numberRow, int numberColumn, int possibleNumber, QVector<QVector<Cell>> &board){
    // check row
    for (int column = 0; column < 9; ++column)
    {
        if ((column != numberColumn))
        {
            if (board[numberRow][column].hasValue())
            {
                if (board[numberRow][column].number == possibleNumber)
                {
                    return false;
                }
            }
            else
            {
                for (auto contenderNumber : board[numberRow][column].possibleNumbers)
                {
                    if (contenderNumber == possibleNumber)
                    {
                        return false;
                    }
                }
            }
        }
    }


    // check columnn
    for (int row = 0; row < 9; ++row)
    {
        if ((row != numberRow))
        {
            if (board[row][numberColumn].hasValue())
            {
                if (board[row][numberColumn].number == possibleNumber)
                {
                    return false;
                }
            }
            else
            {
                for (auto contenderNumber : board[row][numberColumn].possibleNumbers)
                {
                    if (contenderNumber == possibleNumber)
                    {
                        return false;
                    }
                }
            }
        }
    }


    int initialRow = 3 * (numberRow / 3);
    int initialColumn = 3 * (numberColumn / 3);

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (!(initialRow + i == numberRow && initialColumn + j == numberColumn))
            {

                if (board[initialRow + i][initialColumn + j].hasValue())
                {
                    if (board[initialRow + i][initialColumn + j].number == possibleNumber)
                    {
                        return false;
                    }
                }
                else
                {
                    for (auto contenderNumber : board[initialRow + i][initialColumn + j].possibleNumbers)
                    {
                        if (contenderNumber == possibleNumber)
                        {
                            return false;
                        }
                    }
                }
            }
        }
    }

    return true;
}


bool Sudoku::OnlyChoice(QVector<QVector<Cell>> &board)
{
    bool modified = false;

    for (int row = 0; row < 9; row++)
    {
        for (int column = 0; column < 9; column++)
        {
            if (!board[row][column].hasValue())
            {
                for (auto possibleNumber : board[row][column].possibleNumbers)
                {
                    if (CheckOnlyChoiseExistance(row, column, possibleNumber, board) && IsValidPlace(row, column, possibleNumber))
                    {
                        board[row][column] = possibleNumber;
                        modified = true;
                        break;
                    }
                }
            }
        }
    }

    return modified;
}

bool Sudoku::ConstraintPropagation(QVector<QVector<Cell>> &board)
{
    bool modifiedElimination = Elimination(board);
    bool modifiedOnlyChoice = OnlyChoice(board);

    return modifiedElimination || modifiedOnlyChoice;
}

bool Sudoku::SolveBoard(QVector<QVector<Cell>> &board)
{
    while (ConstraintPropagation(board))
    {
    }

    if (Backtrack(0, 0, board))
    {
        return true;
    }

    return false;
}
