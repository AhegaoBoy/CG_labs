#ifndef LAB_6_SIMPLEOBJECT_H
#define LAB_6_SIMPLEOBJECT_H
#include <iostream>

class GameObject {
protected:
    float x, y, z; // Позиции объекта

public:
    GameObject(float x, float y, float z) : x(x), y(y), z(z) {}

    virtual void update(double deltaTime) {}
    virtual void render() const {
        std::cout << "Rendering object at position (" << x << ", " << y << ", " << z << ")" << std::endl;
    }
};
#endif //LAB_6_SIMPLEOBJECT_H
