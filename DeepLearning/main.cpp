#include <QtGui/QApplication>
#include "mainwindow.h"
#include "network.h"
#include <QDebug>
#include <QDirIterator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();
    srand (time(NULL));
     qDebug() << "hello beautiful world!";

     std::vector<int> array(3);
     array[0] = 625;
     array[1] = 30;
     array[2] = 2;

     std::vector<int> array2(2);
     array2[0] = 1;
     array2[1] = 1;

     /*std::vector<double> array3(2);

     Network net(array);
     net._weights.printData();

     net._weights.GetData()[0].dot(array3);*/

     DataSet d = DataSet();
     d.LoadData();
     //d = DataSet(d.Shuffle());

     Network net(array);

     qDebug() <<"biases kesz";
     net._biases.printData();
     net.SGD(d,300,10,1.5);
     qDebug() <<"tanulas kesz";
     /*qDebug() <<"biases kesz";
     net._biases.printData();

     Data testData = Data();
     testData.LoadData("D:/01/1.png");

     std::vector<double> tv = net.feedforward(testData.GetImageData());
     Vector tvv(tv.size());
     tvv.SetData(tv);
     tvv.printData();*/
/*     Network n = Network(array);
     qDebug() << "biases";
     n._biases.printData();
     qDebug() << "weigths";
     n._weights.printData();
     std::vector<double> vee = n.feedforward(array2,0);

     qDebug() << "feedforward eredmeny:";
     for(int i =0;i<vee.size();i++)
         qDebug() << vee[i];

*/

    return a.exec();
}
