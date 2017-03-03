//  Vector.cpp
// This class is used to create vectors to store coordinates in.


#include "Vector.hpp"

//Default constructor
Vector::Vector(){
    x = 0;
    y = 0;
    z = 0;
}

//Constructor
Vector::Vector(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

//Copy constructor
Vector::Vector(Vector const &vector){
    x = vector.x;
    y = vector.y;
    z = vector.z;
}


//Function to add vectors
Vector Vector::add(Vector v){
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

//Function to subtract vectors
Vector Vector::sub(Vector v){
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

//Function to multiply vectors
Vector Vector::mult(Vector v){
    x *= v.x;
    y *= v.y;
    z *= v.z;
    return *this;
}

//Function to divide vectors
Vector Vector::divide(Vector v){
    x /= v.x;
    y /= v.y;
    z /= v.z;
    return *this;
}

//Returns the length of the vector
float Vector::length(){
    return (float) sqrt(x * x + y * y + z * z);
};

//Normalizes the vector
void Vector::normalize(){
    float length = sqrt(x * x + y * y + z * z);
    
    if (length == 0)
        return;
    
    x /= length;
    y /= length;
    z /= length;
}

//Returns the coordinates of the vector as a string
string Vector::toString() {
    return to_string(x) + ", " + to_string(y) + ", " + to_string(z);
}

