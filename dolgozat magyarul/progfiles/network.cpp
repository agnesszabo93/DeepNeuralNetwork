#include "network.h"

//konstruktor
Network::Network(std::vector<int> sizes)
{
	//retegek beallitasa
    _num_layers = sizes.size();

    _sizes = sizes;

	//biasok inicializalasa
    _biases = Matrix2D(_sizes);
    _biases.randInit();

	//sulyok inicializalasa
    _weights = Matrix3D(_sizes);
    _weights.randInit();
}

//az elozo reteg kimenete segitsegevel kiszamolja a kovetkezo reteg kimenetet
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

//a helyesen kategorizat kepek szama
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

//szochasztikus gradiens csokkentes
void Network::SGD(DataSet dataset,int epochs, int mini_batch_size, double eta, DataSet testDataSet)
{
    unsigned int n = dataset.GetDataCount();

    for (unsigned int j = 0; j< epochs; j++){
		//az adatok osszekeverese
        dataset.Shuffle();
        for (int i = 0; i <= n-mini_batch_size; i+=mini_batch_size){
            DataSet mini_batch = DataSet(dataset.GenerateMiniBatch(i,mini_batch_size));
            updateMiniBatch(eta,mini_batch);
        }
    }

	//a vegso biasok kiirasa hogy felhasznalhato legyen kesobb
    struct stat buffer;
    std::string name = "biases.txt";
    if (stat(name.c_str(), &buffer) == 0){
        remove(name.c_str());
    }
    _biases.writeData(name);

	//a vegso sulyok kiirasa hogy felhasznalhato legyen kesobb
    struct stat buffer2;
    std::string name2 = "weights.txt";
    if (stat(name2.c_str(), &buffer2) == 0){
        remove(name2.c_str());
    }
    _weights.writeData(name2);
}

//backpropagation alkalmazasa a batch-ekre
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

		//a kimenetek kiszamitasa elore haladva
        for(unsigned int j = 0; j< _biases.GetVectorCount(); j++){
            Vector z(_biases.GetVector(j).GetCount());
            z.SetData(_weights.GetMatrix2D(j).dot(activation).add(_biases.GetVector(j)));

            zs.SetDataRow(j,z);
            activation = sigmoid_prime(z);
            activations.SetDataRow(j+1,activation);
        }

        Vector outActivation = activations.GetVector(activations.GetVectorCount()-1);
        Vector preferedOutput(outActivation.GetCount());
		//elvart kimenet felepitese
        preferedOutput.SetItem(mini_batch_row.GetImageClass(),1.0);

		//a kimeneti reteg hibajanak kiszamitasa
        Vector delta = cost_derivative(outActivation,preferedOutput).HadamardProd(sigmoid_prime(zs.GetVector(zs.GetVectorCount()-1)));

        nabla_b2.SetDataRow(nabla_b2.GetVectorCount()-1,delta);

        nabla_w2.SetData(nabla_w2.GetMatrix2DCount()-1,dot(delta,activations.GetVector(activations.GetVectorCount()-2)));

		//backpropagation alkalmazva visszafele a retegek hibainak kiszamitasara
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
	
	//sulyok es biasok megfelelo modositasa
    _weights = _weights.sub(nabla_w.multiplyByScalar(eta/(double)mini_batch.GetDataCount()));
    _biases = _biases.sub(nabla_b.multiplyByScalar(eta/(double)mini_batch.GetDataCount()));
}

