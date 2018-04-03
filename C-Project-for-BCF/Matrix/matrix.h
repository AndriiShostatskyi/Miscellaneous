#ifndef MATRIX_H
#define MATRIX_H

#include <QObject>
#include <QtGui>
#include <QtCore>
#include <QScopedArrayPointer>

class Matrix : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit Matrix(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;

    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

    bool insertRow(int row, const QModelIndex &parent);
    bool insertColumn(int column, const QModelIndex &parent);
    bool removeRow(int row, const QModelIndex &parent);
    bool removeColumn(int column, const QModelIndex &parent);

    bool insertRows(int position, int rows,const QModelIndex &index);
    bool removeRows(int position, int rows, const QModelIndex &index);
    bool insertColumns(int column, int count, const QModelIndex &parent);
    bool removeColumns(int column, int count, const QModelIndex &parent);

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QModelIndex index(int row, int column, const QModelIndex &parent) const;

    void setRowCount( int);
    void setColumnCount( int);

    void add(const Matrix &rhs, Matrix &sum);
    void subtract(const Matrix &rhs, Matrix &diff);
    void maltiply(const Matrix &rhs, Matrix &product);

signals:

public slots:

protected:
    QScopedArrayPointer < QScopedArrayPointer<double> >  matrix_data;
    int num_rows;
    int num_columns;
};

#endif // MATRIX_H
