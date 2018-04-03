#include "matrix.h"
#include <iostream>

Matrix::Matrix(QObject *parent)
    : QAbstractTableModel(parent)
{
    matrix_data = std::make_unique< std::unique_ptr <double[]>[] >(10);
    for (int i = 0; i < 10; ++i)
    {
        matrix_data[i] = std::make_unique<double[]>(10);
        for(int j = 0; j < 10; ++j)
        {
            matrix_data[i][j] = 0;
        }
    }
}

 Matrix& Matrix::operator = (Matrix&& rhs)
 {
    insertColumns (0, rhs.rowCount(QModelIndex()), QModelIndex());
    insertRows(0, rhs.columnCount(QModelIndex()), QModelIndex());
    matrix_data = std::move(rhs.matrix_data);
    rhs.matrix_data = nullptr;
    return *this;
 }

int Matrix::rowCount(const QModelIndex &parent = QModelIndex()) const
{
    Q_UNUSED(parent);
    return num_rows;
}

int Matrix::columnCount(const QModelIndex &parent = QModelIndex()) const
{
    Q_UNUSED(parent);
    return num_columns;
}

QVariant Matrix::data(const QModelIndex &index, int role = Qt::DisplayRole) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= (int)num_rows || index.row() < 0)
        return QVariant();

    if (index.column() >= (int)num_columns || index.column() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        return matrix_data[index.row()][index.column()];
    }
    return QVariant();
}

bool Matrix::insertRow(int row, const QModelIndex &parent = QModelIndex())
{
   return insertRows(row, 1, parent);
}

bool Matrix::insertColumn(int column, const QModelIndex &parent = QModelIndex())
{
    return insertColumns(column, 1, parent);
}

bool Matrix::removeRow(int row, const QModelIndex &parent = QModelIndex())
{
    return removeRows(row, 1, parent);
}

bool Matrix::removeColumn(int column, const QModelIndex &parent)
{
    return removeColumns(column, 1, parent);
}

QModelIndex Matrix::index(int row, int column, const QModelIndex &parent = QModelIndex()) const
{
    Q_UNUSED(parent);
    return QAbstractItemModel::createIndex(row, column);
}

bool Matrix::setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        matrix_data[index.row()][index.column()] = value.toDouble();
        emit(dataChanged(index, index));
        return true;
    }

    return false;
}

bool Matrix::insertRows(int position, int rows, const QModelIndex &index = QModelIndex())
{
    if(!rows)
        return false;

    beginInsertRows(index, position, position + rows - 1);
    num_rows += rows;
    endInsertRows();

    return true;
}

bool Matrix::removeRows(int position, int rows, const QModelIndex &index = QModelIndex())
{
    if (!rows)
        return false;

    beginRemoveRows(index, position, position + rows - 1);
    if (num_rows - rows >= 0) {
        num_rows -= rows;
        for (;rows--; ++position)
        {
            for(int j = 0; j < num_columns; ++j)
            {
                matrix_data[position][j] = 0;
            }
        }
    }
    endRemoveRows();

    return true;
}

bool Matrix::insertColumns(int column, int count, const QModelIndex &parent = QModelIndex())
{
    if(!count)
        return false;

    beginInsertColumns(parent, column, column + count - 1);
    num_columns += count;
    endInsertColumns();
    return true;
}

bool Matrix::removeColumns(int column, int count, const QModelIndex &parent = QModelIndex())
{
    if(!count)
        return false;

    beginRemoveColumns(parent, column, column + count - 1);
    if (num_columns - count >= 0)
    {
        num_columns -= count;
        for (;count--; column--)
        {
            for(int j = 0; j < num_rows; ++j)
            {
                matrix_data[j][column] = 0;
            }
        }
    }
    endRemoveColumns();

    return true;
}

Qt::ItemFlags Matrix::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

void Matrix::setRowCount(int rows)
{
    num_rows = rows >= 10 ? 10 : rows;
}

void Matrix::setColumnCount(int columns)
{
    num_columns = columns >= 10 ? 10 : columns;
}

Matrix&& Matrix::operator * (Matrix& rhs)
{
    Matrix *product = new Matrix(static_cast<QObject&>(rhs).parent());

    if(this->columnCount(QModelIndex()) != rhs.rowCount(QModelIndex()))
        return std::move(*product);

    product->insertRows(0, rowCount());
    product->insertColumns(0, rhs.columnCount());

    double sum = 0.0;
    int rows = this->rowCount();
    int cols = rhs.columnCount();
    int width = this->columnCount();

    QModelIndex index = QModelIndex();

    for (int i = 0, j, k; i < rows; ++i)  // for each row of mx1
    {
        for (j = 0; j < cols; ++j)  // for each colum of mx2
        {

            for (k = 0, sum = 0; k < width; ++k) // for each element of row / colum of mx1 / mx2
            {
                sum += (this->data(this->index(i, k, index)).toDouble()
                        * rhs.data(rhs.index(k, j, index)).toDouble()
                        );
            }
            product->setData(product->index(i, j, index), sum);
        }
    }
    return std::move(*product);
}

Matrix&& Matrix::operator + (Matrix& rhs)
{
    Matrix *sum = new Matrix(static_cast<QObject&>(rhs).parent());

    if(this->columnCount(QModelIndex()) != rhs.columnCount(QModelIndex())
            || this->rowCount(QModelIndex()) != rhs.rowCount(QModelIndex()))
        return std::move(*sum);

    sum->insertRows(0, rowCount());
    sum->insertColumns(0, rhs.columnCount());

    QModelIndex index = QModelIndex();

    int rows = this->rowCount();
    int cols = this->columnCount();

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            sum->setData(sum->index(i, j, index),
                        this->data(sum->index(i, j, index)).toDouble()
                        + rhs.data(rhs.index(i, j, index)).toDouble());
        }
    }

    return  std::move(*sum);
}


Matrix&& Matrix::operator -(Matrix &rhs)
{
    Matrix *diff = new Matrix(static_cast<QObject&>(rhs).parent());

    if(this->columnCount(QModelIndex()) != rhs.columnCount(QModelIndex())
            || this->rowCount(QModelIndex()) != rhs.rowCount(QModelIndex()))
        return std::move(*diff);

    diff->insertRows(0, rowCount());
    diff->insertColumns(0, rhs.columnCount());

    QModelIndex index = QModelIndex();

    int rows = this->rowCount();
    int cols = this->columnCount();

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            diff->setData(diff->index(i, j, index),
                        this->data(diff->index(i, j, index)).toDouble()
                        - rhs.data(rhs.index(i, j, index)).toDouble());
        }
    }
    return std::move(*diff);
}


