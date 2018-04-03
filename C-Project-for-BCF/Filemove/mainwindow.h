#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QFileSystemModel>
#include <QFileInfo>
#include <QMessageBox>
#include <QFile>
#include <QDir>

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
    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    bool source_valid = false;
    bool destination_valid = false;
};

#endif // MAINWINDOW_H
