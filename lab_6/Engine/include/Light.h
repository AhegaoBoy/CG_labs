#ifndef LAB_6_LIGHT_H
#define LAB_6_LIGHT_H
#include<iostream>
class light
{
    float intensity;
public:
    light(float init_intensity) : intensity(init_intensity){};

    void apply_lighting() const
    {
        std::cout<<"Light on";
    }
};
#endif //LAB_6_LIGHT_H
