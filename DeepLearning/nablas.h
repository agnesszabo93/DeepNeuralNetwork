#pragma once
#include "matrix.h"
#include "matrix3d.h"

class Nablas
{
public:
    Matrix2D _nabla_b;
    Matrix3D _nabla_w;
    Nablas(Matrix2D nabla_b, Matrix3D nabla_w);

};

