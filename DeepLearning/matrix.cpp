#include "matrix.h"
#include <time.h>
#include <QDebug>

Matrix2D::Matrix2D()
{
}

Matrix2D::Matrix2D(std::vector<int> sizes)
{
    _row_count = sizes.size()-1;
    _vector_count = sizes.size()-1;
    _data.resize(_vector_count);
    for (unsigned int i = 0; i < _vector_count; ++i)
        _data[i] = Vector(sizes[i+1]);
}

Matrix2D::Matrix2D(std::vector<int> sizes, int a)
{
    _row_count = sizes.size();
    _vector_count = sizes.size();
    _data.resize(_vector_count);
    for (unsigned int i = 0; i < _vector_count; ++i)
        _data[i] = Vector(sizes[i]);
}

Matrix2D::Matrix2D(unsigned int row_count, unsigned int column_count)
{
    _vector_count = row_count;
    _row_count = row_count;
    _column_count = column_count;
    _data.resize(_row_count);
    for (unsigned int i = 0; i < row_count; ++i)
        _data[i] = Vector(column_count);
}

void Matrix2D::randInit()
{
    for(unsigned int i = 0; i<_row_count; i++)
        _data[i].randInit();
    qDebug() << endl;
}

void Matrix2D::zeros()
{
    for(unsigned int i = 0; i<_row_count; i++)
        _data[i].zeros();
}

unsigned int Matrix2D::GetVectorCount() const
{
    return _vector_count;
}

unsigned int Matrix2D::GetRowCount() const
{
    return _row_count;
}

unsigned int Matrix2D::GetColumnCount() const
{
    return _column_count;
}

std::vector<Vector> Matrix2D::GetData() const
{
    return _data;
}

double Matrix2D::getItem(unsigned int i, unsigned int j)
{
    return _data[i].GetItem(j);
}

void Matrix2D::SetDataRow(unsigned int i, Vector v)
{
    _data[i] = v;
}

//matrix szorzata egy oszlopvektorral
std::vector<double> Matrix2D::dot(std::vector<double> v)
{
    if (v.size() != _column_count)
        qDebug() << "Nem megfelelo meretek a szorzashoz!!!!" << _column_count <<"  "<<v.size();
    std::vector<double> a(_row_count);
    for (unsigned int j = 0; j<_row_count; j++){
        a[j] = 0;
        for (int i = 0; i<_column_count; i++){
            a[j] += _data[j].GetData()[i]*v[i];
        }
    }
    return a;
}

void Matrix2D::printData()
{
    qDebug() << "2d";
    for (unsigned int i = 0; i < _vector_count; i++)
        _data[i].printData();
}

Matrix2D Matrix2D::add(Matrix2D m)
{
    Matrix2D ret = m;
    for(unsigned int i = 0; i < m.GetVectorCount(); i++){
        Vector v = _data[i].add(m.GetData()[i]);
        ret.SetDataRow(i,v);
    }
    return ret;
}

Matrix2D Matrix2D::sub(Matrix2D m)
{
    Matrix2D ret = m;
    for(unsigned int i = 0; i < m.GetVectorCount(); i++){
        Vector v = _data[i].sub(m.GetData()[i]);
        ret.SetDataRow(i,v);
    }
    return ret;
}

Matrix2D Matrix2D::multiplyByScalar(double s)
{
    Matrix2D ret = *this;
    for(unsigned int i = 0; i < _vector_count; i++){
        Vector v = _data[i].multiplyByScalar(s);
        ret.SetDataRow(i,v);
    }
    return ret;
}
