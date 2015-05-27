#include "network.h"

#include <algorithm>
#include <math.h>
#include <QDebug>

Network::Network(std::vector<int> sizes)
{
    _num_layers = sizes.size();

    _sizes = sizes;

    _biases = Matrix2D(_sizes);
    _biases.randInit();

    _weights = Matrix3D(_sizes);
    _weights.randInit();
    /*qDebug() << "biases";
    _biases.printData();
    qDebug() << "wights";
    _weights.printData();*/
}

std::vector<double> Network::sigmoid(std::vector<double> z)
{
    std::vector<double> ret(z.size());
    for(int i =0; i<z.size();i++)
        ret[i] = (double)1.0 / (double)(1.0 + exp(-z[i]));
    return ret;
    /*std::vector<double> ret(z.size());
    for(int i =0; i<z.size();i++)
        ret[i] = tanh(z[i]);
    return ret;*/
}

std::vector<double> Network::sigmoid_prime(std::vector<double> z)
{
    std::vector<double> ret(z.size());
    std::vector<double> sigm(z.size());
    sigm = sigmoid(z);
    for(unsigned int i = 0; i <sigm.size(); i++)
        ret[i] = sigm[i] * (1 - sigm[i]);
    return ret;
    /*std::vector<double> ret(z.size());
    std::vector<double> sigm(z.size());
    sigm = sigmoid(z);
    for(unsigned int i = 0; i <sigm.size(); i++)
        ret[i] = 1.0 - sigm[i]*sigm[i];
    return ret;*/
}

std::vector<double> Network::feedforward(std::vector<double> a)
{

    for(int i = 0; i< _weights.GetMatrix2DCount();i++){
        Matrix2D w_i = _weights.GetData()[i];
        int s = _biases.GetData()[i].GetCount();
        std::vector<double> new_a(s);
        for (int j = 0; j< s; j++)
            new_a[j] = w_i.dot(a)[j] + _biases.GetData()[i].GetData()[j];

        a = sigmoid(new_a);
    }
    return a;
}

void Network::SGD(DataSet dataset,int epochs, int mini_batch_size, double eta)
{
    Data testData = Data();
    testData.LoadData("D:/00/1.png");

    /*qDebug() <<"elso feedforward";
    std::vector<double> tv = feedforward(testData.GetImageData());
    Vector tvv(tv.size());
    tvv.SetData(tv);
    tvv.printData();*/

    unsigned int n = dataset.GetDataCount();
    for (unsigned int j = 0; j< epochs; j++){
        dataset = DataSet(dataset.Shuffle());
        for (int i = 0; i < n-mini_batch_size; i+=mini_batch_size){
            DataSet mini_batch = DataSet(dataset.GenerateMiniBatch(i,mini_batch_size));
            updateMiniBatch(eta,mini_batch);
        }

        /*std::vector<double> tv = feedforward(testData.GetImageData());
        Vector tvv(tv.size());
        tvv.SetData(tv);
        tvv.printData();*/
    }
}

void Network::updateMiniBatch(double eta, DataSet mini_batch)
{
    Matrix2D nabla_b(_sizes);
    nabla_b.zeros();
    Matrix3D nabla_w(_sizes);
    nabla_w.zeros();
    for(unsigned int i = 0; i < mini_batch.GetDataCount(); i++){
        Data mini_batch_row = mini_batch.GetData()[i];
        Nablas n = backprop(mini_batch_row);
        //qDebug() << "delta nabla b";
        Matrix2D delta_nabla_b = n._nabla_b;
        //delta_nabla_b.printData();
        Matrix3D delta_nabla_w = n._nabla_w;
        nabla_b = nabla_b.add(delta_nabla_b);
        nabla_w = nabla_w.add(delta_nabla_w);
    }
    _weights = _weights.sub(nabla_w.multiplyByScalar(eta/mini_batch.GetDataCount()));
    _biases = _biases.sub(nabla_b.multiplyByScalar(eta/mini_batch.GetDataCount()));
}

std::vector<double> Network::cost_derivative(std::vector<double> output_activations,std::vector<double> y)
{
    std::vector<double> delta(y.size());
    for(unsigned int i = 0; i<y.size();i++)
        delta[i] = output_activations[i]-y[i];
    return delta;
}

std::vector<double> Network::elementwiseProduct(std::vector<double> v1,std::vector<double> v2)
{
    std::vector<double> prod(v1.size());
    for(int i = 0; i<v1.size();i++)
        prod[i] = v1[i] * v2[i];
    return prod;
}

Matrix2D Network::dot(std::vector<double> v1,std::vector<double> v2)
{
    Matrix2D ret(v1.size(),v2.size());
    Vector rowVector(v2.size());
    std::vector<double> row(v2.size());
    for(unsigned int i  = 0; i < v1.size(); i++){
        for(unsigned int j  = 0; j < v2.size(); j++){
            row[j] = v1[i]*v2[j];
        }
        rowVector.SetData(row);
        ret.SetDataRow(i,rowVector);
    }
    return ret;
}

std::vector<double> Network::dot(Matrix2D m,std::vector<double> v)
{
    std::vector<double> row(m.GetColumnCount());
    for(unsigned int i  = 0; i < m.GetColumnCount(); i++){
        row[i] = 0;
        for(unsigned int j  = 0; j < v.size(); j++){
            row[i]+= m.getItem(j,i) * v[j];
        }
    }
    return row;
}

Nablas Network::backprop(Data mini_batch_row)
{
    Matrix2D nabla_b(_sizes);
    nabla_b.zeros();
    Matrix3D nabla_w(_sizes);
    nabla_w.zeros();

    std::vector<double> activation = mini_batch_row.GetImageData();
    Vector activationVector(activation.size());
    activationVector.SetData(activation);
    Matrix2D activations(_sizes,0);
    activations.SetDataRow(0,activationVector);
    Matrix2D zs(_sizes);

    for(unsigned int i = 0; i< _biases.GetVectorCount(); i++){
        std::vector<double> z(_biases.GetData()[i].GetCount());
        for (int j = 0; j< _biases.GetData()[i].GetCount(); j++)
            z[j] = _weights.GetData()[i].dot(activation)[j] + _biases.GetData()[i].GetData()[j];
        Vector zVector(z.size());
        zs.SetDataRow(i,zVector);
        activation = sigmoid_prime(z);
        Vector newActivationVector(activation.size());
        newActivationVector.SetData(activation);
        activations.SetDataRow(i+1,newActivationVector);
    }

    std::vector<double> outActivation = activations.GetData()[activations.GetVectorCount()-1].GetData();
    std::vector<double> preferedOutput(outActivation.size());
    preferedOutput[mini_batch_row.GetImageClass()-1]  = 1;

    std::vector<double> delta = elementwiseProduct(cost_derivative(outActivation,preferedOutput),sigmoid(zs.GetData()[zs.GetVectorCount()-1].GetData()));

    Vector deltaVector(delta.size());
    deltaVector.SetData(delta);
    nabla_b.SetDataRow(nabla_b.GetVectorCount()-1,deltaVector);

    nabla_w.SetData(nabla_w.GetMatrix2DCount()-1,dot(delta,activations.GetData()[activations.GetVectorCount()-2].GetData()));

    for (unsigned int i = 2; i<_num_layers; i++){
        std::vector<double> z = zs.GetData()[zs.GetVectorCount()-i].GetData();
        std::vector<double> spv = sigmoid_prime(z);
        delta = elementwiseProduct(dot(_weights.GetData()[_weights.GetMatrix2DCount()-i+1],delta),spv);
        Vector newDeltaVector(delta.size());
        newDeltaVector.SetData(delta);
        nabla_b.SetDataRow(nabla_b.GetVectorCount()-i,newDeltaVector);
        nabla_w.SetData(nabla_w.GetMatrix2DCount()-i,dot(delta,activations.GetData()[activations.GetVectorCount()-i-1].GetData()));
    }

    Nablas ns(nabla_b,nabla_w);
    return ns;
}
