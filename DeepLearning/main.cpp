#include <QtGui/QApplication>
#include "mainwindow.h"
#include "network.h"
#include <QDirIterator>
#include <iostream>

int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    srand (time(NULL));

     int size = 25;

     std::vector<int> array(3);
     array[0] = size*size;
     array[1] = 10;
     array[2] = 3;

     std::vector<int> array2(2);
     array2[0] = size*size;
     array2[1] = 3;

     DataSet d = DataSet();
     //QString path2 = "../../FullIJCNN2013/FullIJCNN2013/";
     QString path2 = "../../TestLearning";
     d.LoadData(size,path2);

     std::cout<< "Learning started" <<std::endl;
     Network net(array2);
     net.SGD(d,100,10,0.5,d);
     std::cout<< "Learning finished" <<std::endl;

    //return a.exec();
}
