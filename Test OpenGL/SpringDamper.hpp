//  Spring.hpp
// Class used to add the spring force and damper force of the two masses connected by the spring and
// damper.


#ifndef Spring_hpp
#define Spring_hpp

#include "Mass.hpp"



class SpringDamper {
public:
    
    Mass* mass1;    //One mass connected to the spring and damper
    Mass* mass2;    //Another mass connected to the spring and damper.
    
    float springConstant;
    float springLength;
    float springMax;
    float springMin;
    float damperConstant;
    
    //Constructor
    SpringDamper(Mass* mass1, Mass* mass2, float springConstant, float springMax, float springMin, float springLength, float damperConstant);
    
    //Function to add the spring force and damper force to the masses
    void addSDForceX();
    void addSDForceY();
    void addSDForceZ();
    void addSDForce();
};

#endif /* Spring_hpp */
