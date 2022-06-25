#include "window.h"
#include "./ui_window.h"
#include <QDebug>
#include <QMessageBox>
#include <tuple>
#include <random>

Window::Window(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Window), sudoku()
{
    ui->setupUi(this);
    populateSudokuTable();
    LoadLevelWindow();
}

void Window::populateSudokuTable()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            ui->sudokuTable->setItem(i, j, new QTableWidgetItem);
        }
    }
}

Window::~Window()
{
    delete ui;
}

void Window::on_resetButton_clicked()
{
    populateSudokuTable();
    LoadLevelWindow();
    ui->sudokuTable->setSelectionMode(QAbstractItemView::SingleSelection);
}

void Window::createEmptyItem(int row, int column)
{
    ui->sudokuTable->item(row, column)->setBackground(DEFAULT_CELL_COLOR);
    ui->sudokuTable->item(row, column)->setTextAlignment(Qt::AlignCenter);
}

void Window::createLoadedItem(int row, int column)
{
    ui->sudokuTable->item(row, column)->setText(QString::number(sudoku.board[row][column].number));
    ui->sudokuTable->item(row, column)->setBackground(LOADED_CELL_COLOR);
    ui->sudokuTable->item(row, column)->setTextAlignment(Qt::AlignCenter);
    ui->sudokuTable->item(row, column)->setFlags(ui->sudokuTable->item(row, column)->flags() ^ Qt::ItemIsEditable);
}

void Window::sendNoSolutionMessage()
{
    QMessageBox::information(
        this,
        tr("Sudoku"),
        tr("There are no solutions for this configuratioin."));
}

void Window::sendInvalidBoardMessage()
{
    QMessageBox::warning(
        this,
        tr("Sudoku"),
        tr("The board is invalid. Try to fix it."));
}

void Window::deselectAllCells()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            ui->sudokuTable->item(i, j)->setSelected(false);
        }
    }
}

void Window::on_decrementLevel_clicked()
{
    // read label, decrement and chenge level if its a valid number
    int currentLevelInt = ui->currentLevel->text().toInt() - 1;
    if (currentLevelInt >= sudoku.MIN_LEVEL && currentLevelInt <= sudoku.MAX_LEVEL)
    {
        ui->currentLevel->setText(QString::number(currentLevelInt));
        populateSudokuTable();
        LoadLevelWindow();
    }
}

void Window::on_incrementLevel_clicked()
{
    // read label, increment and chenge level if its a valid number
    int currentLevelInt = ui->currentLevel->text().toInt() + 1;
    if (currentLevelInt >= sudoku.MIN_LEVEL && currentLevelInt <= sudoku.MAX_LEVEL)
    {
        ui->currentLevel->setText(QString::number(currentLevelInt));
        populateSudokuTable();
        LoadLevelWindow();
    }
}

void Window::LoadLevelWindow()
{
    sudoku.LoadBoardFromFile(ui->currentLevel->text().toInt());

    deselectAllCells();
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (sudoku.board[i][j].number == sudoku.EMPTY_CELL_VALUE)
            {
                createEmptyItem(i, j);
            }
            else
            {
                createLoadedItem(i, j);
                sudoku.board[i][j].isFilled = true;
            }
        }
    }
}

void Window::on_sudokuTable_cellChanged(int row, int column)
{
    QTableWidgetItem *item = ui->sudokuTable->item(row, column);

    // clean cell if entered number is invalid
    if (!sudoku.IsNumber(item->text()) || item->text().toInt() > 9 || item->text().toInt() < 1)
    {
        item->setText("");
        sudoku.board[row][column].number = sudoku.EMPTY_CELL_VALUE;
        sudoku.board[row][column].isFilled = false;
        sudoku.board[row][column].isValid = true;
        ui->sudokuTable->item(row, column)->setBackground(DEFAULT_CELL_COLOR);
        return;
    }

    // actualize board, check for valid place and color accordingly
    if (item->isSelected())
    {
        int number = item->text().toInt();
        sudoku.board[row][column].number = number;
        sudoku.board[row][column].isFilled = true;
        if (!sudoku.IsValidPlace(row, column, number) && number != sudoku.EMPTY_CELL_VALUE)
        {
            ui->sudokuTable->item(row, column)->setBackground(WRONG_CELL_COLOR);
            sudoku.board[row][column].isValid = false;
        }
        else
        {
            ui->sudokuTable->item(row, column)->setBackground(DEFAULT_CELL_COLOR);
            sudoku.board[row][column].isValid = true;
        }
    }
}

void Window::on_solveButton_clicked()
{
    if (!sudoku.IsValidBoard())
    {
        sendInvalidBoardMessage();
        return;
    }

    if (!sudoku.SolveBoard(sudoku.board))
    {
        sendNoSolutionMessage();
        return;
    }

    deselectAllCells();

    for (int row = 0; row < 9; ++row)
    {
        for (int column = 0; column < 9; ++column)
        {
            if (!sudoku.board[row][column].isFilled)
            {
                // actualize board and make cell not editable
                QString strNumber = QString::number(sudoku.board[row][column].number);
                QTableWidgetItem *item = ui->sudokuTable->item(row, column);
                item->setText(strNumber);
                item->setBackground(SOLVED_CELL_COLOR);
                item->setFlags(item->flags() ^ Qt::ItemIsEditable);
                item->setSelected(false);
            }
        }
    }

    ui->sudokuTable->setSelectionMode(QAbstractItemView::NoSelection);
}

void Window::on_hintButton_clicked()
{
    if (!sudoku.IsValidBoard())
    {
        sendInvalidBoardMessage();
        return;
    }

    QVector<QVector<Cell>> &boardCopy(sudoku.board);

    if (!sudoku.SolveBoard(boardCopy))
    {
        sendNoSolutionMessage();
        return;
    }

    deselectAllCells();

    std::vector<std::tuple<int, int>> solvedCellsCoordinates;

    // populate vector with solved cells
    for (int row = 0; row < 9; ++row)
    {
        for (int column = 0; column < 9; ++column)
        {
            if (!boardCopy[row][column].isFilled)
            {
                solvedCellsCoordinates.push_back(std::make_tuple(row, column));
            }
        }
    }

    if (solvedCellsCoordinates.size() == 0)
    {
        return;
    }

    // choose random solved cell
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, solvedCellsCoordinates.size() - 1);
    int randomVectorIndex = distr(gen);

    std::tuple<int, int> solvedCellCoordinates = solvedCellsCoordinates[distr(gen)];

    int row = std::get<0>(solvedCellsCoordinates[randomVectorIndex]);
    int column = std::get<1>(solvedCellsCoordinates[randomVectorIndex]);

    // actualize real board
    sudoku.board[row][column].number = boardCopy[row][column].number;
    sudoku.board[row][column].isValid = true;
    sudoku.board[row][column].isFilled = true;

    // actualize board
    QString strNumber = QString::number(sudoku.board[row][column].number);
    QTableWidgetItem *item = ui->sudokuTable->item(row, column);
    item->setText(strNumber);
    item->setBackground(SOLVED_CELL_COLOR);
    item->setFlags(item->flags() ^ Qt::ItemIsEditable);
    item->setSelected(false);
}
