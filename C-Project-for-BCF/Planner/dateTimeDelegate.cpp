#include "dateTimeDelegate.h"

DateTimeDelegate::DateTimeDelegate(QObject *parent)
    :QStyledItemDelegate(parent)
{

}

QWidget* DateTimeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
       return new QDateTimeEdit(parent);
}

void DateTimeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
       QDateTimeEdit *el = static_cast<QDateTimeEdit*>(editor);

       el->setDateTime(index.model()->data(index, Qt::EditRole).toDateTime());

}

void DateTimeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
        QDateTimeEdit *el = static_cast<QDateTimeEdit*>(editor);
        model->setData(index, el->dateTime(), Qt::EditRole);
}





