//
// Created by jbili on 19.07.2021.
//

#ifndef CLUSEK_RT_PADDINGCALCULATOR_H
#define CLUSEK_RT_PADDINGCALCULATOR_H


namespace PaddingCalculator
{
    template<class T>
    T Calculate(T value, T padding);

    template<class T>
    T Calculate(T value, T padding)
    {
        if (value % padding != 0)
            return value + (padding - (value % padding));
        else
            return value;
    }
};


#endif //CLUSEK_RT_PADDINGCALCULATOR_H
