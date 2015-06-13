#include "network.h"

Network::Network(std::vector<int> sizes)
{
    _num_layers = sizes.size();

    _sizes = sizes;

    _biases = Matrix2D(_sizes);
    _biases.randInit();

    _weights = Matrix3D(_sizes);
    _weights.randInit();
}

Vector Network::sigmoid(Vector z)
{
    Vector ret(z.GetCount());
    for(unsigned int i =0; i<z.GetCount();i++)
        ret.SetItem(i, 1.0 / (1.0 + exp(-z.GetItem(i))));
    return ret;
}

Vector Network::sigmoid_prime(Vector z)
{
    Vector ret(z.GetCount());
    Vector sigm(z.GetCount());
    sigm = sigmoid(z);
    for(unsigned int i = 0; i <z.GetCount(); i++)
        ret.SetItem(i, sigm.GetItem(i) * (1 - sigm.GetItem(i)));
    return ret;
}

Vector Network::feedforward(Vector a)
{
    for(unsigned int i = 0; i< _weights.GetMatrix2DCount();i++){
        Matrix2D w_i = _weights.GetMatrix2D(i);
        int s = _biases.GetVector(i).GetCount();
        Vector new_a(s);
        for (int j = 0; j< s; j++)
            new_a.SetItem(j, w_i.dot(a).GetItem(j) + _biases.GetData()[i].GetData()[j]);
        a = sigmoid(new_a);
    }
    return a;
}

unsigned int Network::evaluate(DataSet testDataSet)
{
    unsigned int correct = 0;
    for(unsigned int i = 0; i < testDataSet.GetDataCount(); i++){
        Data testData = testDataSet.GetData()[i];
        Vector tv = feedforward(testData.GetImageData());
        double imgClass = tv.GetMax();
        if (imgClass == testData.GetImageClass())
            correct++;
    }
    return correct;
}

void Network::SGD(DataSet dataset,int epochs, int mini_batch_size, double eta, DataSet testDataSet)
{
    std::ofstream myfile;
    //myfile.open("learning_results.txt");

    unsigned int n = dataset.GetDataCount();

    //myfile << n << std::endl;

    for (unsigned int j = 0; j< epochs; j++){
        dataset.Shuffle();
        for (int i = 0; i <= n-mini_batch_size; i+=mini_batch_size){
            DataSet mini_batch = DataSet(dataset.GenerateMiniBatch(i,mini_batch_size));
            updateMiniBatch(eta,mini_batch);
        }

        //myfile << j << " " << evaluate(testDataSet) << std::endl;
    }
    //myfile.close();

    struct stat buffer;
    std::string name = "biases.txt";
    //ha letezik a file
    if (stat(name.c_str(), &buffer) == 0){
        remove(name.c_str());
    }
    _biases.writeData(name);

    struct stat buffer2;
    std::string name2 = "weights.txt";
    //ha letezik a file
    if (stat(name2.c_str(), &buffer2) == 0){
        remove(name2.c_str());
    }
    _weights.writeData(name2);
}

void Network::updateMiniBatch(double eta, DataSet mini_batch)
{
    Matrix2D nabla_b(_sizes);
    nabla_b.zeros();
    Matrix3D nabla_w(_sizes);
    nabla_w.zeros();
    for(unsigned int i = 0; i < mini_batch.GetDataCount(); i++){
        Data mini_batch_row = mini_batch.GetData()[i];



        Matrix2D nabla_b2(_sizes);
        nabla_b2.zeros();
        Matrix3D nabla_w2(_sizes);
        nabla_w2.zeros();

        Vector activation = mini_batch_row.GetImageData();
        Matrix2D activations(_sizes,0);
        activations.SetDataRow(0,activation);
        Matrix2D zs(_sizes);

        for(unsigned int j = 0; j< _biases.GetVectorCount(); j++){
            Vector z(_biases.GetVector(j).GetCount());
            z.SetData(_weights.GetMatrix2D(j).dot(activation).add(_biases.GetVector(j)));

            zs.SetDataRow(j,z);
            activation = sigmoid_prime(z);
            activations.SetDataRow(j+1,activation);
        }

        Vector outActivation = activations.GetVector(activations.GetVectorCount()-1);
        Vector preferedOutput(outActivation.GetCount());
        preferedOutput.SetItem(mini_batch_row.GetImageClass(),1.0);

        Vector delta = cost_derivative(outActivation,preferedOutput).HadamardProd(sigmoid_prime(zs.GetVector(zs.GetVectorCount()-1)));

        nabla_b2.SetDataRow(nabla_b2.GetVectorCount()-1,delta);

        nabla_w2.SetData(nabla_w2.GetMatrix2DCount()-1,dot(delta,activations.GetVector(activations.GetVectorCount()-2)));

        for (unsigned int j = 2; j<_num_layers; j++){
            Vector z = zs.GetVector(zs.GetVectorCount()-j);
            Vector spv = sigmoid_prime(z);
            delta = dot(_weights.GetMatrix2D(_weights.GetMatrix2DCount()-j+1),delta).HadamardProd(spv);

            nabla_b2.SetDataRow(nabla_b2.GetVectorCount()-j,delta);
            nabla_w2.SetData(nabla_w2.GetMatrix2DCount()-j,dot(delta,activations.GetVector(activations.GetVectorCount()-j-1)));
        }
        Nablas ns(nabla_b2,nabla_w2);


        Matrix2D delta_nabla_b = ns._nabla_b;
        Matrix3D delta_nabla_w = ns._nabla_w;
        nabla_b = nabla_b.add(delta_nabla_b);
        nabla_w = nabla_w.add(delta_nabla_w);
    }
    _weights = _weights.sub(nabla_w.multiplyByScalar(eta/(double)mini_batch.GetDataCount()));
    _biases = _biases.sub(nabla_b.multiplyByScalar(eta/(double)mini_batch.GetDataCount()));
}

Vector Network::cost_derivative(Vector output_activations,Vector y)
{
    Vector delta = output_activations.sub(y);
    return delta;
}

Matrix2D Network::dot(Vector v1,Vector v2)
{
    Matrix2D ret(v1.GetCount(),v2.GetCount());
    Vector rowVector(v2.GetCount());
    for(unsigned int i  = 0; i < v1.GetCount(); i++){
        for(unsigned int j  = 0; j < v2.GetCount(); j++){
            rowVector.SetItem(j,v1.GetItem(i)*v2.GetItem(j));
        }
        ret.SetDataRow(i,rowVector);
    }
    return ret;
}

Vector Network::dot(Matrix2D m,Vector v)
{
    Vector row(m.GetColumnCount());
    double value;
    for(unsigned int i  = 0; i < m.GetColumnCount(); i++){
        value = 0;
        for(unsigned int j  = 0; j < v.GetCount(); j++){
            value+= m.getItem(j,i) * v.GetItem(j);
        }
        row.SetItem(i,value);
    }
    return row;
}
