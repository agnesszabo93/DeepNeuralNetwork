#include "data.h"

#include <QImage>
#include<QStringList>

Data::Data()
{
}


Data::Data(Vector imageData, unsigned int imageClass)
{
    _imageData.SetData(imageData.GetData());
    _imageClass = imageClass;
}



Vector Data::GetImageData()
{
    return _imageData;
}

unsigned int Data::GetImageClass()
{
    return _imageClass;
}

void Data::LoadData(QString path,unsigned int dim)
{
    QStringList pieces = path.split( "/" );
    _imageClass = pieces.value( pieces.length() - 2 ).toInt();
    _imageData=Vector(dim*dim);
    QImage * image = new QImage();
    if(image->load(path))
    {

        for(unsigned int i = 0; i< image->width(); i++){
            for(unsigned int j = 0; j< image->height(); j++){
                QRgb rgba = image->pixel(i,j);

                double r = (double) qRed(rgba)/255;
                double g = (double) qGreen(rgba)/255;
                double b = (double) qBlue(rgba)/255;
                double c_max = std::max(std::max(r,g),b);
                double c_min = std::min(std::min(r,g),b);
                double D = c_max - c_min;
                double H = 0;
                double L = 0;

                if (D == 0)
                    H = 0;
                else if (c_max==r)
                    H = 60*((g-b)/D);
                else if (c_max==g)
                    H = 60*(2+(b-r)/D);
                else if (c_max==b)
                    H = 60*(4+(r-g)/D);

                if (H<0)
                    H+=360;

                if (c_max==0)
                    L = 0;
                else
                    L = D/c_max;

                if ((((H >=0 && H <=20) ||  (H>=340)) && c_max >0.2 && L>0.3) || (c_max<=0.3))
                {
                    image->setPixel(i,j,0);
                }
                else
                    image->setPixel(i,j,qRgb(255, 255, 255));
                /*if (c_max<0.3)
                    image->setPixel(i,j,0);
                else
                    image->setPixel(i,j,qRgb(255, 255, 255));*/
            }
        }

        //image->save(path);


        QImage scaledImage = image->scaled(dim,dim,Qt::IgnoreAspectRatio,Qt::FastTransformation);
        for(int i = 0;i< dim;i++)
        {
            for (int j= 0; j< dim;j++){
                _imageData.SetItem(i*dim+j, qGray(scaledImage.pixel(i,j))/255);
            }
        }
    }
}
