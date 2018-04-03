#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QSize>
#include <QComboBox>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QtDebug>
#include <QStringList>
#include <QApplication>

class ComboBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit ComboBoxDelegate(QObject *parent = 0);

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

private:
    QStringList priority;
    QStringList status;

signals:

public slots:


};

#endif // DELEGATE_H
