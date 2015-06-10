#include <QtGui/QApplication>
#include "mainwindow.h"
#include "network.h"
#include <QDebug>
#include <QDirIterator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    srand (time(NULL));
     qDebug() << "hello beautiful world!";

     std::vector<int> array(3);
     array[0] = 625;
     array[1] = 10;
     array[2] = 3;

     std::vector<int> array2(2);
     array2[0] = 625;
     array2[1] = 3;

     DataSet d = DataSet();
     QString path = "D:/Egyetem/Allamvizsga/TestLearning";
     d.LoadData(25,path);

     DataSet d2 = DataSet();
     QString path2 = "D:/Egyetem/Allamvizsga/Tests";
     d2.LoadData(25,path2);

     Network net(array2);
     net.SGD(d,300,10,0.6,d2);
     qDebug() <<"kesz";
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
