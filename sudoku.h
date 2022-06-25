#pragma once
#include <string>
#include <QVector>
#include "cell.h"

class Sudoku
{
private:
    bool IsValidRow(int numberRow, int numberColumn, int number);

    bool IsValidSquare(int numberRow, int numberColumn, int number);

    bool IsValidColumn(int numberRow, int numberColumn, int number);

    bool Backtrack(int row, int column, QVector<QVector<Cell>> &board);

    const std::string SUDOKU_GRID_FILE_NAME = "../../../../sudoku_grid.txt";

public:
    Sudoku();

    ~Sudoku();

    const int EMPTY_CELL_VALUE = 0;

    const int MIN_LEVEL = 0;

    const int MAX_LEVEL = 50;

    QVector<QVector<Cell>> board;

    bool SolveBoard(QVector<QVector<Cell>> &board);

    void CreateNewBoard();

    bool IsValidPlace(int row, int column, int number);

    void LoadBoardFromFile(int board_number);

    bool IsValidBoard();

    bool IsNumber(const QString &str);

    bool Elimination(QVector<QVector<Cell>> &board);

    bool PropagateEliminationConstraint(int row, int column, QVector<QVector<Cell>> &board);

    bool OnlyChoice(QVector<QVector<Cell>> &board);

    bool ConstraintPropagation(QVector<QVector<Cell>> &board);

    bool CheckOnlyChoiseExistance(int numberRow, int numberColumn, int possibleNumber, QVector<QVector<Cell>> &board);

    bool OnlyChoiceSquare(int numberRow, int numberColumn, int possibleNumber, QVector<QVector<Cell>> &board);
};
