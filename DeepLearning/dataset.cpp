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

void DataSet::LoadData()
{
    QStringList all_paths;
    QString parent_folder = "D:/Egyetem/Allamvizsga/TestLearning";
    QDirIterator dirIt(parent_folder,QDirIterator::Subdirectories);
    while (dirIt.hasNext()) {
        dirIt.next();
        if (QFileInfo(dirIt.filePath()).isFile())
           all_paths <<dirIt.filePath();
    }

    _data_count = all_paths.size();

    for (int i = 0; i<all_paths.size(); i++){
        _data[i] = Data();
        _data[i].LoadData(all_paths[i]);
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

