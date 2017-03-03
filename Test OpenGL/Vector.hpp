//  Vector.hpp
// This class is used to create vectors to store coordinates in.

#ifndef Vector_hpp
#define Vector_hpp


#include <iostream>
#include <cmath>

using namespace std;

class Vector {
public:
    float x; // the x value of the Vector
    float y; // the y value of the Vector
    float z; // the z value of the Vector
    
    //Constructors
    Vector();
    Vector(float x, float y, float z);
    Vector(Vector const &vector);
    
    //Mathematical operations
    Vector add(Vector v);
    Vector sub(Vector v);
    Vector mult(Vector v);
    Vector divide(Vector v);
    
    float length();
    void normalize();
    
    string toString();

};

#endif /* Vector_hpp */
