#include "dataset.h"

DataSet::DataSet()
{
    _data_count = 101;
    _data.resize(101);
}

DataSet::DataSet(std::vector<Data> data)
{
    _data_count = data.size();
    _data = data;
}

std::vector<Data> DataSet::GetData()
{
    return _data;
}

unsigned int DataSet::GetDataCount()
{
    return _data_count;
}

void DataSet::LoadData(unsigned int dim,QString parent_folder)
{
    QStringList all_paths;
    QDirIterator dirIt(parent_folder,QDirIterator::Subdirectories);
    while (dirIt.hasNext()) {
        dirIt.next();
        if (QFileInfo(dirIt.filePath()).isFile())
           all_paths <<dirIt.filePath();
    }

    _data_count = all_paths.size();
    _data.resize(_data_count);

    for (int i = 0; i<_data_count; i++){
        _data[i] = Data();
        _data[i].LoadData(all_paths[i],dim);
    }
}

std::vector<Data> DataSet::Shuffle()
{
    std::random_shuffle(_data.begin(),_data.end());
    return _data;
}

std::vector<Data> DataSet::GenerateMiniBatch(unsigned int startIndex, unsigned int batchSize)
{
    std::vector<Data> miniBatch;
    miniBatch.resize(batchSize);
    for(unsigned int i = startIndex; i < startIndex+batchSize; i++)
        miniBatch[i-startIndex] = _data[i];
    return miniBatch;
}

