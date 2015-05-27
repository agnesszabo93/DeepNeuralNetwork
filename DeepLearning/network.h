#pragma once

#include <vector>
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

    Network(std::vector<int> sizes);
    std::vector<double> sigmoid(std::vector<double> z);
    std::vector<double> sigmoid_prime(std::vector<double> z);
    std::vector<double> feedforward(std::vector<double> a);
    void SGD(DataSet dataset,int epochs, int mini_batch_size, double eta);
    void updateMiniBatch(double eta, DataSet mini_batch);
    Nablas backprop(Data mini_batch_row);
    std::vector<double> cost_derivative(std::vector<double> output_activations,std::vector<double> y);
    std::vector<double> elementwiseProduct(std::vector<double> v1,std::vector<double> v2);
    Matrix2D dot(std::vector<double> v1,std::vector<double> v2);
    std::vector<double> dot(Matrix2D m,std::vector<double> v);
};


