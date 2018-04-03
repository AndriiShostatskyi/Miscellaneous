#include "comboBoxDelegate.h"

ComboBoxDelegate::ComboBoxDelegate(QObject *parent)
    :QStyledItemDelegate(parent)
{
    priority.append("Low");
    priority.append("Middle");
    priority.append("Heigh");

    status.append("Not completed");
    status.append("Completed");
}

QWidget* ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *combo = new QComboBox(parent);
    if(index.column() == 3)
       combo->addItems(status);
    else
       combo->addItems(priority);
    return combo;
}

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    int value = index.model()->data(index, Qt::EditRole).toUInt();
    comboBox->setCurrentIndex(value);
}

void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    model->setData(index, comboBox->currentIndex(), Qt::EditRole);
}






