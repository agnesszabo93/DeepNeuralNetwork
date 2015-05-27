#pragma once

#include <QString>
#include <vector>

class Data
{
protected:
    std::vector<double> _imageData;
    unsigned int _imageClass;
public:
    Data();
    Data(std::vector<double> imageData, unsigned int imageClass);
    std::vector<double> GetImageData();
    unsigned int GetImageClass();
    void LoadData(QString path);
};

