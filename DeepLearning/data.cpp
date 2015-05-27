#include "data.h"

#include <QImage>
#include<QStringList>

Data::Data()
{
}


Data::Data(std::vector<double> imageData, unsigned int imageClass)
{
    _imageData = imageData;
    _imageClass = imageClass;
}

std::vector<double> Data::GetImageData()
{
    return _imageData;
}

unsigned int Data::GetImageClass()
{
    return _imageClass;
}

void Data::LoadData(QString path)
{
    QStringList pieces = path.split( "/" );
    _imageClass = pieces.value( pieces.length() - 2 ).toInt();
    unsigned int size = 25;
    _imageData.resize(size*size);
    QImage * image = new QImage();
    if(image->load(path))
    {
        QImage scaledImage = image->scaled(size,size,Qt::IgnoreAspectRatio,Qt::FastTransformation);
        int grey;
        for(int i = 0;i< size;i++)
        {
            for (int j= 0; j< size;j++){
                grey = qGray(scaledImage.pixel(j,i));
                _imageData[i*size+j] = (double)grey/255;
            }
        }
    }
}
