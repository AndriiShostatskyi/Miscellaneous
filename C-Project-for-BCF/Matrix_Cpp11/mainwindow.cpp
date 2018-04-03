#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <memory>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    matrix1 = new Matrix(this);
    matrix2 = new Matrix(this);
    matrix3 = new Matrix(this);

    rows_m1 = cols_m1 = rows_m2 = cols_m2 = 0;

    ui->Matrix_1->setModel(matrix1);
    ui->Matrix_2->setModel(matrix2);
    ui->Matrix_3->setModel(matrix3);

    ui->spinBox->setMaximum(10);
    ui->spinBox_2->setMaximum(10);
    ui->spinBox_3->setMaximum(10);
    ui->spinBox_4->setMaximum(10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinBox_valueChanged(const QString &arg1)
{
    if (arg1.toInt() > rows_m1 && rows_m1  < 10) {
        matrix1->insertRow(rows_m1++, QModelIndex());
    }
    else if (arg1.toInt() < rows_m1 && rows_m1 > 0){
        matrix1->removeRow(--rows_m1, QModelIndex());
    }
}

void MainWindow::on_spinBox_2_valueChanged(const QString &arg1)
{
    if (arg1.toInt() > cols_m1 && cols_m1 < 10) {
        matrix1->insertColumn(cols_m1++, QModelIndex());
    }
    else if (arg1.toInt() < cols_m1 && cols_m1 > 0){
        matrix1->removeColumn(--cols_m1, QModelIndex());
    }
}

void MainWindow::on_spinBox_4_valueChanged(const QString &arg1)
{
    if (arg1.toInt() > rows_m2 && rows_m2  < 10) {
        matrix2->insertRow(rows_m2++, QModelIndex());
    }
    else if (arg1.toInt() < rows_m2 && rows_m2 > 0){
        matrix2->removeRow(--rows_m2, QModelIndex());
    }
}

void MainWindow::on_spinBox_3_valueChanged(const QString &arg1)
{
    if (arg1.toInt() > cols_m2 && cols_m2 < 10) {
        matrix2->insertColumn(cols_m2++, QModelIndex());
    }
    else if (arg1.toInt() < cols_m2 && cols_m2 > 0){
        matrix2->removeColumn(--cols_m2, QModelIndex());
    }
}

void MainWindow::on_pushButton_clicked()
{
    matrix3->removeRows(0, matrix3->rowCount(QModelIndex()), QModelIndex());
    matrix3->removeColumns(0,matrix3->columnCount(QModelIndex()), QModelIndex());

    switch (ui->comboBox->currentIndex())
    {
    case 0:
        if (matrix1->rowCount(QModelIndex()) == matrix2->rowCount(QModelIndex())
                && matrix1->columnCount(QModelIndex()) == matrix2->columnCount(QModelIndex()))
        {
           *matrix3 =*matrix1 + *matrix2;
        }
        else
        {
            QMessageBox::warning(this, "Warning!", "You cannot add matrices because "
                                                   "their dimensions are not the same.");
        }
        break;
    case 1:
        if (matrix1->rowCount(QModelIndex()) == matrix2->rowCount(QModelIndex())
                && matrix1->columnCount(QModelIndex()) == matrix2->columnCount(QModelIndex()))
        {
            *matrix3 = *matrix1 - *matrix2;
        }
        else
        {
            QMessageBox::warning(this, "Warning!", "You cannot subtract matrices because "
                                                   "their dimensions are not the same.");
        }
        break;
    case 2:
        if (matrix1->columnCount(QModelIndex()) == matrix2->rowCount(QModelIndex()))
        {
            *matrix3 =*matrix1 * *matrix2;
        }
        else
        {
            QMessageBox::warning(this, "Warning!", "You cannot multiply matrices - check dimensions"
                                                   " needed for maltiplication.");
        }
        break;
    default:
        break;
    }
}
