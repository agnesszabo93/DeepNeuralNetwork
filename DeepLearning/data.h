#pragma once

#include <QString>
#include <vector>

#include "vector.h"

class Data
{
protected:
    Vector _imageData;
    unsigned int _imageClass;
public:
    Data();
    Data(Vector imageData, unsigned int imageClass);

    Vector GetImageData();
    unsigned int GetImageClass();

    void LoadData(QString path,unsigned int dim);
};

