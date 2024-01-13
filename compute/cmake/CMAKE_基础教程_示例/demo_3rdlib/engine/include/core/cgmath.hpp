#pragma once

class Cgmath
{
public:
    Cgmath();
    virtual ~Cgmath();

    double Squre2(double data, int index)
    {
        double temp = data;
        for (int i = 0; i < index; i++)
        {
            temp = 0.5 * (temp + 2 / temp);
        }
        return temp;
    };
};