#include <QtGui/QApplication>
#include "mainwindow.h"
#include "network.h"
#include <QDirIterator>
#include <iostream>

int main(int argc, char *argv[])
{
    srand (time(NULL));

	//kepek egyszeges meretenek beallitasa
    int size = 25;

	//a halo retegeinek es ezek mereteinek beallitasa
	std::vector<int> array2(2);
    array2[0] = size*size;
    array2[1] = 43;

	//az adatok betoltese
    DataSet d = DataSet();
    QString path = "../../TestLearning";
    d.LoadData(size,path);

    std::cout<< "Learning started" <<std::endl;
	//a halo letrehozasa
    Network net(array2);
	//tanulas megkezdese
    net.SGD(d,300,30,3,d);
    std::cout<< "Learning finished" <<std::endl;
}
