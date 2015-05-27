#include <time.h>
#include <QDebug>

#include "vector.h"

Vector::Vector()
{
}


Vector::Vector(unsigned int count)
{
    _count = count;
    _data.resize(_count);
}

void Vector::randInit()
{
    for(int i = 0; i<_count; i++){
        _data[i] = (double)rand() /(101*30*RAND_MAX);
    }
}

void Vector::zeros()
{
    for(int i = 0; i<_count; i++)
        _data[i] = 0;
}

unsigned int Vector::GetCount()  const
{
    return _count;
}

std::vector<double> Vector::GetData() const
{
    return _data;
}

double Vector::GetItem(unsigned int i)
{
    return _data[i];
}

void Vector::SetData(std::vector<double> data)
{
    _data = data;
}

void Vector::printData()
{
    qDebug() << "1d";
    for (unsigned int i = 0; i < _count; i++)
        qDebug() << _data[i];
}

Vector Vector::add(Vector v)
{
    Vector retV(v.GetCount());
    std::vector<double> ret(v.GetCount());
    for(unsigned int i = 0; i < v.GetCount(); i++){
        ret[i] = v.GetItem(i) + _data[i];
        if (ret[i] != ret[i])
            ret[i] = 0;
    }
    retV.SetData(ret);
    return retV;

}

Vector Vector::sub(Vector v)
{
    if (_count != v.GetCount())
        qDebug() <<" nem megfelelo meretek a vektorok kivonasanal!" << _count<<" "<<v.GetCount();
    Vector retV(v.GetCount());
    std::vector<double> ret(v.GetCount());
    for(unsigned int i = 0; i < v.GetCount(); i++){
        ret[i] = _data[i] - v.GetItem(i);
        if (ret[i] != ret[i])
            ret[i] = 0;
    }
    retV.SetData(ret);
    return retV;
}

Vector Vector::multiplyByScalar(double s)
{
    Vector retV(_count);
    std::vector<double> ret(_count);
    for(unsigned int i = 0; i < _count; i++){
        ret[i] = _data[i] * s;
        if (ret[i] != ret[i])
            ret[i] = 0;
    }
    retV.SetData(ret);
    return retV;
}
