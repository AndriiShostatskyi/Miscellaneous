#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Source file path and name
void MainWindow::on_lineEdit_2_textChanged(const QString &arg1)
{
    QFile file;
    file.setFileName(arg1);

    if(file.open(QIODevice::ReadOnly))
    {
        ui->label_2->setText("<font color='green'> File exists. </font>");
        source_valid = true;
        file.close();
    }
    else
    {
        ui->label_2->setText("<font color='red'> No such file found. </font>");
        source_valid = false;
    }
}

// Destination file path and name
void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    QFile file;
    file.setFileName(arg1);

    if(file.open(QIODevice::ReadOnly))
    {
         ui->label->setText("<font color='red'> File with the same name already exists. </font>");
         destination_valid = false;
         file.close();
    }
    else
    {
        if (arg1[arg1.size()-1] == '\\' || arg1[arg1.size()-1] == '/')
        {
            ui->label->setText("<font color='red'> File with the same name does not exist."
                               " But enter name of the destination file. </font>");
            destination_valid = false;
        }
        else
        {
            ui->label->setText("<font color='green'> File with the same name does not exist.");
            destination_valid = true;
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    if (!source_valid || !destination_valid)
        return;

    QDir mydir;
    QFile file;

    try {
        if (!mydir.rename(ui->lineEdit_2->text(), ui->lineEdit->text()))
        {
            if(!file.copy(ui->lineEdit_2->text(), ui->lineEdit->text())) {
                throw -1;
            } else {
                 file.remove(ui->lineEdit_2->text());
            }
        }
        ui->label->setText("<font color='green'> Success! </font>");
    }
    catch (int)
    {
         QMessageBox::warning(this, "Error!", "Could not move or copy-remove file. "
                                              "Probably, source and destination are not on the same partition");
    }
    catch(exception& e)
    {
        QMessageBox::warning(this, "Error!", "Could not move or copy-remove file." + QString(e.what()));
    }

}
