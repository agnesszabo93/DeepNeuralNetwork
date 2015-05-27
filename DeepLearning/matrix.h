#pragma once

#include <vector>

#include "vector.h"

class Matrix2D
{
protected:
    unsigned int _vector_count;
    unsigned int _row_count;
    unsigned int _column_count;
    std::vector<Vector> _data;
public:
    Matrix2D();
    Matrix2D(std::vector<int> sizes);
    Matrix2D(std::vector<int> sizes,int a);
    Matrix2D(unsigned int row_count, unsigned int column_count);
    void randInit();
    void zeros();
    double getItem(unsigned int i, unsigned int j);
    unsigned int GetVectorCount() const;
    unsigned int GetRowCount() const;
    unsigned int GetColumnCount() const;
    void SetDataRow(unsigned int i, Vector v);
    std::vector<Vector> GetData() const;
    std::vector<double> dot(std::vector<double> v);
    void printData();
    Matrix2D add(Matrix2D);
    Matrix2D sub(Matrix2D);
    Matrix2D multiplyByScalar(double s);
};

