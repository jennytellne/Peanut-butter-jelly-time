//  Mass.cpp
// This class creates a mass with a weight, position, velocity and force.

#include "Mass.hpp"

//Constructor
Mass::Mass(float weight){
    this->weight = weight;
    this->velocity.x = 0;
    this->velocity.y = 0;
    this->velocity.z = 0;
}

//Function used to add forces to the mass
void Mass::applyForce(Vector force){
    this->force.x += force.x;
    this->force.y += force.y;
    this->force.z += force.z;
}

void Mass::applyGravity(float gravity){
    this->force.y += gravity;
}

//Function used to set starting position of mass
void Mass::setStartPos(float x, float y, float z){
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
    
}

void Mass::setVelocity(float vel_x, float vel_y, float vel_z){
    this->velocity.x = vel_x;
    this->velocity.y = vel_y;
    this->velocity.z = vel_z;
}

void Mass::setVelocityX(float vel_x){
    this->velocity.x = vel_x;
}

void Mass::setVelocityY(float vel_y){
    this->velocity.y = vel_y;
}

void Mass::setVelocityZ(float vel_z){
    this->velocity.z = vel_z;
}


//Sets the force of the mass to zero
void Mass::init(){
    force.x = 0;
    force.y = 0;
    force.z = 0;
}

//Simulates using the Euler method
void Mass::simulateEuler(float dt){
    velocity.x += (force.x / weight) * dt;
    velocity.y += (force.y / weight) * dt;
    velocity.z += (force.z / weight) * dt;
    
    position.x += velocity.x * dt;
    position.y += velocity.y * dt;
    position.z += velocity.z * dt;
}
