#include "scheduler.h"
#include "ui_scheduler.h"
#include <QSqlRecord>
#include <QMessageBox>

Scheduler::Scheduler(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Scheduler)
{
    ui->setupUi(this);

    dt_delegate = new DateTimeDelegate(this);
    cb_delegate = new ComboBoxDelegate(this);
    db = new DataBase();
    db->connectToDataBase();

    this->setupModel(TABLE,
                     QStringList() << trUtf8("id")
                                   << trUtf8("Plan")
                                   << trUtf8("Deadline")
                                   << trUtf8("Status")
                                   << trUtf8("Importance")
                                   << trUtf8("Urgency")
               );

    this->createUI();

    setPersistant();
    ui->tableView->setColumnWidth(1, 240);
    ui->tableView->setColumnWidth(2, 130);
    ui->tableView->setColumnWidth(3, 125);
    ui->tableView->setColumnWidth(4, 90);
    ui->tableView->setColumnWidth(5, 90);

}

void Scheduler::setPersistant()
{
    for ( int i = 0; i < model->rowCount(); ++i )
      {
      ui->tableView->openPersistentEditor( model->index(i, 2) );
      ui->tableView->openPersistentEditor( model->index(i, 3) );
      ui->tableView->openPersistentEditor( model->index(i, 4) );
      ui->tableView->openPersistentEditor( model->index(i, 5) );
     }
}

void Scheduler::setupModel(const QString &tableName, const QStringList &headers)
{
    model = new QSqlTableModel(this);
    model->setTable(tableName);
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->setSort(0,Qt::AscendingOrder);

    for(int i = 0, j = 0; i < model->columnCount(); i++, j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
}

void Scheduler::createUI()
{
    ui->pushButton->setDisabled(1);
    ui->pushButton_2->setDisabled(1);

    ui->tableView->setModel(model);

    ui->tableView->setItemDelegateForColumn(2, dt_delegate);
    ui->tableView->setItemDelegateForColumn(3, cb_delegate);
    ui->tableView->setItemDelegateForColumn(4, cb_delegate);
    ui->tableView->setItemDelegateForColumn(5, cb_delegate);
    ui->tableView->setColumnHidden(0, true);    // Скрываем колонку с id записей

    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers( QAbstractItemView::AllEditTriggers);

    model->select();
    connect(
      ui->tableView->selectionModel(),
      SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
      SLOT(slotLoadTransaction(const QItemSelection &, const QItemSelection &))
     );
}


void Scheduler::slotLoadTransaction(const QItemSelection & arg1, const QItemSelection &arg2)
{
    if(ui->tableView->selectionModel()->selectedRows().size() )
        ui->pushButton_2->setEnabled(1);
    else ui->pushButton_2->setDisabled(1);
}


Scheduler::~Scheduler()
{
    delete ui;
}

void Scheduler::on_pushButton_clicked()
{
    QSqlRecord record = model->record();
    int row_count = model->rowCount();

    record.setValue(0, model->record(row_count - 1).value("ID").toInt() + 1);
    record.setValue(1,QVariant(ui->lineEdit->text()));
    record.setValue(2,QVariant(ui->dateTimeEdit->text()));
    record.setValue(3,QVariant(tr("0")));
    record.setValue(4,QVariant(ui->comboBox->currentIndex()));
    record.setValue(5,QVariant(ui->comboBox_2->currentIndex()));

    model->insertRecord(-1, record);

    ui->tableView->openPersistentEditor( model->index(row_count, 2) );
    ui->tableView->openPersistentEditor( model->index(row_count, 3) );
    ui->tableView->openPersistentEditor( model->index(row_count, 4) );
    ui->tableView->openPersistentEditor( model->index(row_count, 5) );

}

void Scheduler::on_lineEdit_textChanged(const QString &arg1)
{
    if(arg1.size()) {
        ui->pushButton->setEnabled(1);
    }
    else ui->pushButton->setDisabled(1);
}

void Scheduler::on_pushButton_2_clicked()
{
    for (int i = 0; i < ui->tableView->selectionModel()->selectedRows().size(); ++i) {
        model->removeRow(ui->tableView->selectionModel()->selectedRows()[i].row());
    }
     model->select();
     setPersistant();
}
