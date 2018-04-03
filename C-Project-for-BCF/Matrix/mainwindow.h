#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractItemModel>
#include <QtGui>
#include <QtCore>
#include <QMessageBox>
#include "matrix.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_spinBox_valueChanged(const QString &arg1);

    void on_spinBox_2_valueChanged(const QString &arg1);

    void on_spinBox_4_valueChanged(const QString &arg1);

    void on_spinBox_3_valueChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;

    Matrix *matrix1;
    Matrix *matrix2;
    Matrix *matrix3;

    int rows_m1;
    int cols_m1;

    int rows_m2;
    int cols_m2;

};

#endif // MAINWINDOW_H
