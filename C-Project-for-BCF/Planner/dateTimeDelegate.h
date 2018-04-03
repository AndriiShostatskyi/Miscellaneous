#ifndef DATETIMEDELEGATE_H
#define DATETIMEDELEGATE_H

#include <QObject>
#include <QStyledItemDelegate>
#include <QModelIndex>
#include <QObject>
#include <QSize>
#include <QDateTimeEdit>
#include <QtDebug>
#include <QStringList>

class DateTimeDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit DateTimeDelegate(QObject *parent = 0);

    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;

    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

signals:

public slots:


};

#endif // DELEGATE_H
