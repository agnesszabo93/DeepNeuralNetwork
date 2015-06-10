#pragma once

#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <QDirIterator>
#include <QDebug>

#include "data.h"
#include "matrix.h"
#include "matrix3d.h"

class DataSet
{
protected:
    unsigned int _data_count;
    std::vector<Data> _data;
public:
    DataSet();
    DataSet(std::vector<Data> data);

    std::vector<Data> GetData();
    unsigned int GetDataCount();

    void LoadData(unsigned int dim,QString parent_folder);
    std::vector<Data> Shuffle();
    std::vector<Data> GenerateMiniBatch(unsigned int startIndex, unsigned int batchSize);
};

