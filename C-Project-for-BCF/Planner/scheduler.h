#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QTableView>
#include "comboBoxDelegate.h"
#include "dateTimeDelegate.h"
#include "database.h"

namespace Ui {
class Scheduler;
}

class Scheduler : public QMainWindow
{
    Q_OBJECT

public:
    explicit Scheduler(QWidget *parent = 0);
    ~Scheduler();

private slots:
    void on_pushButton_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

   void slotLoadTransaction(const QItemSelection &, const QItemSelection &);

   void on_pushButton_2_clicked();

private:
    Ui::Scheduler *ui;
    DataBase        *db;
    QSqlTableModel  *model;
    DateTimeDelegate *dt_delegate;
    ComboBoxDelegate *cb_delegate;

private:
    /* Также присутствуют два метода, которые формируют модель
     * и внешний вид TableView
     * */
    void setupModel(const QString &tableName, const QStringList &headers);
    void createUI();
    void setPersistant();

};

#endif // SCHEDULER_H
