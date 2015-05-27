#pragma once

#include <vector>
#include "matrix.h"

class Matrix3D
{
protected:
    unsigned int _matrix2d_count;
    std::vector<Matrix2D>  _data;
public:
    Matrix3D(std::vector<int> sizes);
    Matrix3D();
    void randInit();
    void zeros();
    std::vector<Matrix2D> GetData() const;
    void SetData(unsigned int i, Matrix2D m);
    unsigned int GetMatrix2DCount() const;
    void printData();
    Matrix3D add(Matrix3D m);
    Matrix3D sub(Matrix3D m);
    Matrix3D multiplyByScalar(double s);
};
