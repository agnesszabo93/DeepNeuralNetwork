#pragma once

#include <vector>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>

class Vector
{
protected:
    unsigned int _count;
    std::vector<double> _data;
public:
    Vector();
    Vector(unsigned int count);
    void randInit();
    void zeros();
    unsigned int GetCount() const;
    std::vector<double> GetData() const;
    double GetItem(unsigned int i);
    void SetData(std::vector<double> data);
    void printData();
    Vector add(Vector v);
    Vector sub(Vector v);
    Vector multiplyByScalar(double s);
};

