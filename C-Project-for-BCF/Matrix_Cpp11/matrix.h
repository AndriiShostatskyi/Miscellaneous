#ifndef MATRIX_H
#define MATRIX_H

#include <QObject>
#include <QtGui>
#include <QtCore>
#include <QScopedArrayPointer>
#include <memory>

class Matrix : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit Matrix(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    bool insertRow(int row, const QModelIndex &parent);
    bool insertColumn(int column, const QModelIndex &parent);
    bool removeRow(int row, const QModelIndex &parent);
    bool removeColumn(int column, const QModelIndex &parent);

    bool insertRows(int position, int rows,const QModelIndex &index) override;
    bool removeRows(int position, int rows, const QModelIndex &index) override;
    bool insertColumns(int column, int count, const QModelIndex &parent) override;
    bool removeColumns(int column, int count, const QModelIndex &parent) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;

    void setRowCount( int);
    void setColumnCount( int);

    Matrix&& operator + (Matrix& rhs);
    Matrix&& operator - (Matrix& rhs);
    Matrix&& operator * (Matrix& rhs);
    Matrix& operator = ( Matrix&& rhs);

signals:

public slots:

protected:
    int num_rows{0};
    int num_columns{0};
public:
    std::unique_ptr< std::unique_ptr <double[]>[] > matrix_data;
};

#endif // MATRIX_H
