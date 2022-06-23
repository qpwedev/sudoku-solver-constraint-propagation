#include "window.h"
#include "./ui_window.h"
#include <QDebug>
#include <QMessageBox>

Window::Window(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::Window), sudoku()
{
    ui->setupUi(this);
    populateSudokuTable();
    LoadLevelWindow();
}

void Window::populateSudokuTable(){
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
    QColor color = QColor::fromRgb(162, 170, 173);
    ui->sudokuTable->item(row, column)->setBackground(color);
    ui->sudokuTable->item(row, column)->setTextAlignment(Qt::AlignCenter);
}

void Window::createLoadedItem(int row, int column)
{
    ui->sudokuTable->item(row, column)->setText(QString::number(sudoku.board[row][column].number));
    QColor color = QColor::fromRgb(58, 58, 58);
    ui->sudokuTable->item(row, column)->setBackground(color);
    ui->sudokuTable->item(row, column)->setTextAlignment(Qt::AlignCenter);
    ui->sudokuTable->item(row, column)->setFlags(ui->sudokuTable->item(row, column)->flags() ^ Qt::ItemIsEditable);
}

void Window::sendNoSolutionMessage(){
    QMessageBox::information(
        this,
        tr("Sudoku"),
        tr("There are no solutions for this configuratioin.") );
}

void Window::sendInvalidBoardMessage(){
    QMessageBox::warning(
        this,
        tr("Sudoku"),
        tr("The board is invalid. Try to fix it.") );
}

void Window::deselectAllCells(){
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            ui->sudokuTable->item(i,j)->setSelected(false);
        }
    }
}


void Window::on_solveButton_clicked()
{
    if (!sudoku.IsValidBoard()){
        sendInvalidBoardMessage();
        return;
    }

    if (!sudoku.SolveBoard(sudoku.board))
    {
        sendNoSolutionMessage();
        return;
    }

    deselectAllCells();

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (!sudoku.board[i][j].isLoaded)
            {
                QString str = QString::number(sudoku.board[i][j].number);
                ui->sudokuTable->item(i, j)->setText(str);
                QColor color = QColor::fromRgb(139, 0, 255);
                ui->sudokuTable->item(i, j)->setBackground(color);
                ui->sudokuTable->item(i, j)->setFlags(ui->sudokuTable->item(i, j)->flags() ^ Qt::ItemIsEditable);
                ui->sudokuTable->item(i, j)->setSelected(false);               
            }

        }
    }
    ui->sudokuTable->setSelectionMode(QAbstractItemView::NoSelection);
}



void Window::on_decrementLevel_clicked()
{
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
            if (sudoku.board[i][j].number == sudoku.EMPTY)
            {
                createEmptyItem(i, j);
            }
            else
            {
                createLoadedItem(i, j);
                sudoku.board[i][j].isLoaded = true;
            }
        }
    }
}

void Window::on_sudokuTable_cellChanged(int row, int column)
{
    QTableWidgetItem *item = ui->sudokuTable->item(row, column);

    if (!sudoku.IsNumber(item->text()) || item->text().toInt() > 9 || item->text().toInt() < 1)
    {
        item->setText("");
        sudoku.board[row][column].number = sudoku.EMPTY;
        sudoku.board[row][column].isLoaded = false;
        sudoku.board[row][column].isValid = true;
        QColor color = QColor::fromRgb(162, 170, 173);
        ui->sudokuTable->item(row, column)->setBackground(color);
        return;
    }
    if (item->isSelected())
    {
        int number = item->text().toInt();
        sudoku.board[row][column].number = number;
        sudoku.board[row][column].isLoaded = true;
        if (!sudoku.IsValidPlace(row, column, number) && number != sudoku.EMPTY)
        {
            QColor color = QColor::fromRgb(161, 40, 48);
            ui->sudokuTable->item(row, column)->setBackground(color);
            sudoku.board[row][column].isValid = false;
        }
        else
        {
            QColor color = QColor::fromRgb(162, 170, 173);
            ui->sudokuTable->item(row, column)->setBackground(color);
            sudoku.board[row][column].isValid = true;
        }
    }
}

void Window::on_hintButton_clicked()
{
    if (!sudoku.IsValidBoard()){
        sendInvalidBoardMessage();
        return;
    }

    QVector<QVector<Cell>> & boardCopy(sudoku.board);

    if (!sudoku.SolveBoard(boardCopy))
    {
        sendNoSolutionMessage();
        return;
    }

    deselectAllCells();

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (!boardCopy[i][j].isLoaded)
            {
                sudoku.board[i][j].number = boardCopy[i][j].number;
                sudoku.board[i][j].isValid = true;
                sudoku.board[i][j].isLoaded = true;
                QString str = QString::number(sudoku.board[i][j].number);
                ui->sudokuTable->item(i, j)->setText(str);
                QColor color = QColor::fromRgb(139, 0, 255);
                ui->sudokuTable->item(i, j)->setBackground(color);
                ui->sudokuTable->item(i, j)->setFlags(ui->sudokuTable->item(i, j)->flags() ^ Qt::ItemIsEditable);
                ui->sudokuTable->item(i, j)->setSelected(false);
                return;
            }
        }
    }
}

