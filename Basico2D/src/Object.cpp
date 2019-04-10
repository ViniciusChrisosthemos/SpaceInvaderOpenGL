#include "Object.h"
#include <stdio.h>

class Object{
public:
    int a;
    void print();
};

void Object::print(){
    printf("%i\n",a);
}
