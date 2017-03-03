//  Spring.cpp
// Class used to add the spring force and damper force of the two masses connected by the spring and
// damper.


#include "SpringDamper.hpp"

//Constructor
SpringDamper::SpringDamper(Mass* mass1, Mass* mass2, float springConstant, float springMax, float springMin, float springLength, float damperConstant){
    
    this->springConstant = springConstant;
    this->springLength = springLength;
    this->springMax = springMax;
    this->springMin = springMin;
    this->damperConstant = damperConstant;
    this->mass1 = mass1;
    this->mass2 = mass2;
    
}

void SpringDamper::addSDForce(){
    
    // Vector between the two masses
    Vector springVector;
    springVector.x = mass1->position.x - mass2->position.x;
    springVector.y = mass1->position.y - mass2->position.y;
    springVector.z = mass1->position.z - mass2->position.z;
    
    //The distance betwee the two masses
    float distance = springVector.length();
    
    Vector force;                         // Force Initially Has A Zero Value
    
    // The Spring Force Is Added To The Force
    force.x += -springConstant * (distance - springLength) * (springVector.x / distance);
    force.y += -springConstant * (distance - springLength) * (springVector.y / distance);
    force.z += -springConstant * (distance - springLength) * (springVector.z / distance);
    
    //The Damping Force is added
    force.x += -(mass1->velocity.x - mass2->velocity.x) * damperConstant;
    force.y += -(mass1->velocity.y - mass2->velocity.y) * damperConstant;
    force.z += -(mass1->velocity.z - mass2->velocity.z) * damperConstant;
    
    // With This Addition We Obtain The Net Force Of The Spring
    // Force Is Applied To mass1
    mass1->applyForce(force);
    
    //The negative fore is added to mass 2.
    Vector neg_force;
    neg_force.x = -force.x;
    neg_force.y = -force.y;
    neg_force.z = -force.z;
    mass2->applyForce(neg_force);
}


//Function to add the spring force and damper force to the masses
void SpringDamper::addSDForceX(){
    
    // Vector between the two masses
    Vector springVector;
    springVector.x = mass1->position.x - mass2->position.x;
    springVector.y = mass1->position.y - mass2->position.y;
    springVector.z = mass1->position.z - mass2->position.z;
    
    //The distance betwee the two masses
    float distance = springVector.length();
    
    Vector force;                         // Force Initially Has A Zero Value
    
    if (distance != 0)                         // To Avoid A Division By Zero... Check If r Is Zero
        if (distance <= springMin || distance >= springMax) {
            mass1->setVelocityX(0);
            mass2->setVelocityX(0);
            
        }
    // The Spring Force Is Added To The Force
    force.x += -springConstant * (distance - springLength) * (springVector.x / distance);
    force.y += -springConstant * (distance - springLength) * (springVector.y / distance);
    force.z += -springConstant * (distance - springLength) * (springVector.z / distance);
    
    //The Damping Force is added
    force.x += -(mass1->velocity.x - mass2->velocity.x) * damperConstant;
    force.y += -(mass1->velocity.y - mass2->velocity.y) * damperConstant;
    force.z += -(mass1->velocity.z - mass2->velocity.z) * damperConstant;
    
    // With This Addition We Obtain The Net Force Of The Spring
    // Force Is Applied To mass1
    mass1->applyForce(force);
    
    //The negative fore is added to mass 2.
    Vector neg_force;
    neg_force.x = -force.x;
    neg_force.y = -force.y;
    neg_force.z = -force.z;
    mass2->applyForce(neg_force);
}

//Function to add the spring force and damper force to the masses
void SpringDamper::addSDForceY(){
    
    // Vector between the two masses
    Vector springVector;
    springVector.x = mass1->position.x - mass2->position.x;
    springVector.y = mass1->position.y - mass2->position.y;
    springVector.z = mass1->position.z - mass2->position.z;
    
    //The distance betwee the two masses
    float distance = springVector.length();
    
    Vector force;                         // Force Initially Has A Zero Value
    
    if (distance != 0)                         // To Avoid A Division By Zero... Check If r Is Zero
        if (distance <= springMin || distance >= springMax) {
            mass1->setVelocityY(0);
            mass2->setVelocityY(0);
            
        }
    // The Spring Force Is Added To The Force
    force.x += -springConstant * (distance - springLength) * (springVector.x / distance);
    force.y += -springConstant * (distance - springLength) * (springVector.y / distance);
    force.z += -springConstant * (distance - springLength) * (springVector.z / distance);
    
    //The Damping Force is added
    force.x += -(mass1->velocity.x - mass2->velocity.x) * damperConstant;
    force.y += -(mass1->velocity.y - mass2->velocity.y) * damperConstant;
    force.z += -(mass1->velocity.z - mass2->velocity.z) * damperConstant;
    
    // With This Addition We Obtain The Net Force Of The Spring
    // Force Is Applied To mass1
    mass1->applyForce(force);
    
    //The negative fore is added to mass 2.
    Vector neg_force;
    neg_force.x = -force.x;
    neg_force.y = -force.y;
    neg_force.z = -force.z;
    mass2->applyForce(neg_force);
}


//Function to add the spring force and damper force to the masses
void SpringDamper::addSDForceZ(){
    
    // Vector between the two masses
    Vector springVector;
    springVector.x = mass1->position.x - mass2->position.x;
    springVector.y = mass1->position.y - mass2->position.y;
    springVector.z = mass1->position.z - mass2->position.z;
    
    //The distance betwee the two masses
    float distance = springVector.length();
    
    Vector force;                         // Force Initially Has A Zero Value
    
    if (distance != 0)                         // To Avoid A Division By Zero... Check If r Is Zero
        if (distance <= springMin || distance >= springMax) {
            mass1->setVelocityZ(0);
            mass2->setVelocityZ(0);
            
        }
    // The Spring Force Is Added To The Force
    force.x += -springConstant * (distance - springLength) * (springVector.x / distance);
    force.y += -springConstant * (distance - springLength) * (springVector.y / distance);
    force.z += -springConstant * (distance - springLength) * (springVector.z / distance);
    
    //The Damping Force is added
    /*force.x += -(mass1->velocity.x - mass2->velocity.x) * damperConstant;
    force.y += -(mass1->velocity.y - mass2->velocity.y) * damperConstant;
    force.z += -(mass1->velocity.z - mass2->velocity.z) * damperConstant;*/
    
    force.x += - damperConstant*((mass1->velocity.x - mass2->velocity.x)*springVector.x+(mass1->velocity.y - mass2->velocity.y)*springVector.y+(mass1->velocity.z - mass2->velocity.z)*springVector.z)*springVector.x/(distance*distance);
    
    force.y += - damperConstant*((mass1->velocity.x - mass2->velocity.x)*springVector.x+(mass1->velocity.y - mass2->velocity.y)*springVector.y+(mass1->velocity.z - mass2->velocity.z)*springVector.z)*springVector.y/(distance*distance);
    
    force.z += - damperConstant*((mass1->velocity.x - mass2->velocity.x)*springVector.x+(mass1->velocity.y - mass2->velocity.y)*springVector.y+(mass1->velocity.z - mass2->velocity.z)*springVector.z)*springVector.z/(distance*distance);
    
    // With This Addition We Obtain The Net Force Of The Spring
    // Force Is Applied To mass1
    mass1->applyForce(force);
    
    //The negative fore is added to mass 2.
    Vector neg_force;
    neg_force.x = -force.x;
    neg_force.y = -force.y;
    neg_force.z = -force.z;
    mass2->applyForce(neg_force);
}

