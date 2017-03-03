//  Mass.hpp
// This class creates a mass with a weight, position, velocity and force.

#ifndef Mass_hpp
#define Mass_hpp


#include "Vector.hpp"


class Mass {
public:
    float weight;           // The weight
    Vector position;		// Position in space
    Vector velocity;        // Velocity
    Vector force;           // Force applied on the mass
    
    //Constructor
    Mass(float m);

    //Function used to add forces to the mass
    void applyForce(Vector force);
    
    void applyGravity(float gravity);
    
    //Function used to set starting position of mass
    void setStartPos(float x, float y, float z);
    
    void setVelocity(float vel_x, float vel_y, float vel_z);
    
    void setVelocityX(float vel_x);
    void setVelocityY(float vel_y);
    void setVelocityZ(float vel_z);

    //Sets the force of the mass to zero
    void init();
    
    //Simulates using the Euler method
    void simulateEuler(float dt);
    
};


#endif /* Mass_hpp */
