#pragma once

#include <vector>
#include <algorithm>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>

#include "matrix.h"
#include "matrix3d.h"
#include "dataset.h"
#include "nablas.h"

class Network
{
protected:

public:
    int              _num_layers;
    std::vector<int> _sizes;
    Matrix2D         _biases;
    Matrix3D         _weights;

    std::ofstream myfile;

    Network(std::vector<int> sizes);

    Vector sigmoid(Vector z);
    Vector sigmoid_prime(Vector z);
    Vector feedforward(Vector a);
    void SGD(DataSet dataset,int epochs, int mini_batch_size, double eta, DataSet testDataSet);
    void updateMiniBatch(double eta, DataSet mini_batch);
    Vector cost_derivative(Vector output_activations,Vector y);
    unsigned int evaluate(DataSet testDataSet);
    Matrix2D dot(Vector v1,Vector v2);
    Vector dot(Matrix2D m,Vector v);
};


