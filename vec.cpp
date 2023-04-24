#include "vec.hpp"

Pos::Pos(GLfloat x, GLfloat y, GLfloat z){
    this->x = x;
    this->y = y;
    this->z = z;
}
Pos::Pos(){
    this->x = 0;
    this->y = 0;
    this->z = 0;
}
