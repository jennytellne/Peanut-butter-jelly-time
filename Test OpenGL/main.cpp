
/*
 * A C++ framework for OpenGL programming in TNM046 for MT1 2014.
 *
 * This is a small, limited framework, designed to be easy to use
 * for students in an introductory computer graphics course in
 * the first year of a M Sc curriculum. It uses custom code
 * for some things that are better solved by external libraries
 * like GLEW and GLM, but the emphasis is on simplicity and
 * readability, not generality.
 * For the window management, GLFW 3.0 is used for convenience.
 * The framework should work in Windows, MacOS X and Linux.
 * Some Windows-specific stuff for extension loading is still
 * here. GLEW could have been used instead, but for clarity
 * and minimal dependence on other code, we rolled our own extension
 * loading for the things we need. That code is short-circuited on
 * platforms other than Windows. This code is dependent only on
 * the GLFW and OpenGL libraries. OpenGL 3.3 or higher is required.
 *
 * Author: Stefan Gustavson (stegu@itn.liu.se) 2013-2014
 * This code is in the public domain.
 *
 *
 * Code modified and completed by Sofia Linevik and Jenny Tellne 2017
 */

// File and console I/O for logging and error reporting
#include <iostream>
#include <cmath>
// In MacOS X, tell GLFW to include the modern OpenGL headers.
// Windows does not want this, so we make this Mac-only.
#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif

// GLFW 3.x, to handle the OpenGL window
#include <GLFW/glfw3.h>

#include "Utilities.hpp"

#include "Shader.hpp"
#include "TriangleSoup.hpp"
#include "Vector.hpp"
#include "Mass.hpp"
#include "SpringDamper.hpp"




/*
 * main(argc, argv) - the standard C++ entry point for the program
 */

//Sends data to the GPU
void createVertexBuffer(int location, int dimensions, const float *data, int datasize)
{
    GLuint bufferID;
    // Generate buffer, activate it and copy the data
    glGenBuffers(1, &bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glBufferData(GL_ARRAY_BUFFER, datasize, data, GL_STATIC_DRAW);
    // Tell OpenGL how the data is stored in our buffer
    // Attribute location (must match layout(location=#) statement in shader)
    // Number of dimensions (3 -> vec3 in the shader, 2-> vec2 in the shader),
    // type GL_FLOAT, not normalized, stride 0, start at element 0
    glVertexAttribPointer(location, dimensions, GL_FLOAT, GL_FALSE, 0, NULL);
    // Enable the attribute in the currently bound VAO
    glEnableVertexAttribArray(location);
}

void createIndexBuffer(const unsigned int *data, int datasize)
{
    GLuint bufferID;
    // Generate buffer, activate it and copy the data
    glGenBuffers(1, &bufferID);
    // Activate (bind) the index buffer and copy data to it.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferID);
    // Present our vertex indices to OpenGL
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, datasize, data, GL_STATIC_DRAW);
}


using namespace std;

int main(int argc, char *argv[])
{
    
    // --- Put this with the variable declarations in main ()
    TriangleSoup myShape;
    
    int width, height;
    //GLuint colorBufferID ; // Vertex colors
    
    const GLFWvidmode *vidmode;  // GLFW struct to hold information about the display
    GLFWwindow *window;    // GLFW struct to hold information about the window
    
    // Declarations : the C++ variable and the location of its GLSL counterpart
    float time;
    GLint location_time;
    Shader myShader;
    
    // Initialise GLFW
    glfwInit();
    
    // Determine the desktop size
    vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    
    // Make sure we are getting a GL context of at least version 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Exclude old legacy cruft from the context. We don't need it, and we don't want it.
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    // Open a square window (aspect 1:1) to fill half the screen height
    window = glfwCreateWindow(vidmode->height/2, vidmode->height/2, "GLprimer", NULL, NULL);
    if (!window)
    {
        cout << "Unable to open window. Terminating." << endl;
        glfwTerminate(); // No window was opened, so we can't continue in any useful way
        return -1;
    }
    
    // Make the newly created window the "current context" for OpenGL
    // (This step is strictly required, or things will simply not work)
    glfwMakeContextCurrent(window);
    
    // ------------------------------------------------------------------------
    // ---- Put this code after glfwMakeContextCurrent(), but before the rendering loop
    // Load extensions (only needed in Microsoft Windows)
    Utilities::loadExtensions();
    
    myShader.createShader("vertex.glsl", "fragment.glsl");
    
    // Show some useful information on the GL context
    cout << "GL vendor:       " << glGetString(GL_VENDOR) << endl;
    cout << "GL renderer:     " << glGetString(GL_RENDERER) << endl;
    cout << "GL version:      " << glGetString(GL_VERSION) << endl;
    cout << "Desktop size:    " << vidmode->width << "x" << vidmode->height << " pixels" << endl;
    
    
    glfwSwapInterval(0);
    
    // Do not wait for screen refresh between frames
    // Do this before the rendering loop
    location_time = glGetUniformLocation(myShader.programID, "time");
    if(location_time == -1) { // If the variable is not found , -1 is returned
        cout << " Unable to locate variable ✬time ✬ in shader !" << endl;
    }
    
    GLint location_M1;
    location_M1 = glGetUniformLocation(myShader.programID,"M1");
    glUseProgram(myShader.programID); // Activate the shader to set its variables
    //glUniformMatrix4fv(location_M1, 1, GL_FALSE,M1); // Copy the value
    
    GLint location_M2;
    location_M2 = glGetUniformLocation(myShader.programID,"M2");
    glUseProgram(myShader.programID); // Activate the shader to set its variables

    
    
    
    // --- Put this before your rendering loop
    // Generate a triangle
    
    /* ***************** */
    //myShape.createTriangle();
    //myShape.createSphere(1.0f, 100);
    myShape.createBox(0.3f, 0.5f, 0.3f);
    //myShape.createSquare(0.5f, 0.5f);
    /* ***************** */
    
    /* OK RESULTAT I NÖDFALL VID REDOVISNING
     float weight = 1.0f;
     float springConstant = 20.0f;
     float springLength = 0.3f;
     float springMax = 0.8f;
     float springMin = 0.1f;
     float dt = 0.0002f;
     float damperConstant = 30.0f;*/
    
    //Initialiserar en array med alla massor och ger startposition
    //Sker endast en gång utanför renderingsloopen
    float weight = 5.0f;
    float springConstant = 20.0f;
    float springLength = 0.3f;
    float springMax = 0.8f;
    float springMin = 0.1f;
    float dt = 0.0001f;
    float damperConstant = 30.0f;
    float gravity = -9.82*weight;
    int nSprings = 24;
    float springConstDiag = 20.0f;
    float damperConstDiag = 20.0f;
    float springLengthDiag = sqrt(springLength*springLength*2);
    float springMaxDiag = sqrt(springMax*springMax*2);
    float springMinDiag = sqrt(springMin*springMin*2);
    Mass** masses;
    masses = new Mass*[myShape.nverts];
    SpringDamper** springs_dampers;
    
    //Changes to 4 because we use a square instead of a box right now **********************
    springs_dampers = new SpringDamper*[nSprings];
    int coord_pos = 0;
    for(int i = 0; i < myShape.nverts; i++){
        masses[i] = new Mass(weight);
        //masses[i]->applyGravity(gravity);
        masses[i]->setStartPos(myShape.vertexarray[coord_pos],myShape.vertexarray[coord_pos+1],myShape.vertexarray[coord_pos+2]);
        coord_pos += 8;
    }
        
    
    // Main loop
    while(!glfwWindowShouldClose(window))
    {
        
        glEnable(GL_CULL_FACE);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        // --- Insert this line into your rendering loop .
        Utilities::displayFPS(window);
        // Get window size. It may start out different from the requested
        // size, and will change if the user resizes the window.
        glfwGetWindowSize( window, &width, &height );
        // Set viewport. This is the pixel rectangle we want to draw into.
        glViewport( 0, 0, width, height ); // The entire window
        
        // Set the clear color and depth, and clear the buffers for drawing
        glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Activate the vertex array object we want to draw (we may have several)
        
        glUseProgram(myShader.programID);
        
        //Spring dampers x-led
        /*int x_index = 0;
        for (int i = 0; i < 2; i++) {
            springs_dampers[i] = new SpringDamper(masses[x_index], masses[x_index+1],
                                                 springConstant, springMax, springMin, springLength, damperConstant);
            springs_dampers[i]->addSDForceX();
            x_index += 2;
            //Spring dampers y-led
        }
        //Spring dampers y-led
        int y_index = 0;
        for (int i = 2; i < 4; i++) {
            springs_dampers[i] = new SpringDamper(masses[y_index], masses[y_index+2],
                                                  springConstant, springMax, springMin, springLength, damperConstant);
            springs_dampers[i]->addSDForceY();
            y_index++;
            
        }
        
        float x[myShape.nverts];
        float y[myShape.nverts];
        float z[myShape.nverts];
        for(int i = 0; i < myShape.nverts; i++){
            masses[i]->simulateEuler(dt);
            x[i] = masses[i]->position.x;
            y[i] = masses[i]->position.y;
            z[i] = masses[i]->position.z;
         
        }
        
        myShape.updateVertexArray(x, y, z);
        myShape.generateVAO(); */
        
                
        // --- Put this in the rendering loop
        // Draw the triangle
        int k = 0;
        for(int i = 0; i < 4; i++){
            //Spring dampers i x-led
            springs_dampers[i] = new SpringDamper(masses[k], masses[k+1],
                                                    springConstant, springMax, springMin, springLength, damperConstant);
            springs_dampers[i]->addSDForceX();
            
            //Spring dampers i z-led
            springs_dampers[i+8] = new SpringDamper(masses[i], masses[i+4],
                                                    springConstant, springMax, springMin, springLength, damperConstant);
            springs_dampers[i+8]->addSDForceZ();
            k+=2;
        }
        
        //Spring dampers i y-led
        springs_dampers[4] = new SpringDamper(masses[0], masses[2],
                                              springConstant, springMax, springMin, springLength, damperConstant);
        springs_dampers[4]->addSDForceY();
        springs_dampers[5] = new SpringDamper(masses[1], masses[3],
                                              springConstant, springMax, springMin, springLength, damperConstant);
        springs_dampers[5]->addSDForceY();
        springs_dampers[6] = new SpringDamper(masses[4], masses[6],
                                              springConstant, springMax, springMin, springLength, damperConstant);
        springs_dampers[6]->addSDForceY();
        springs_dampers[7] = new SpringDamper(masses[5], masses[7],
                                              springConstant, springMax, springMin, springLength, damperConstant);
        springs_dampers[7]->addSDForceY();
        
        //DIAGONAL SPRINGSSSSSSSSSSS
        springs_dampers[12] = new SpringDamper(masses[0], masses[3], springConstDiag,springMinDiag, springMaxDiag, springLengthDiag, damperConstDiag);
        springs_dampers[12]->addSDForce();
        
        springs_dampers[13] = new SpringDamper(masses[1], masses[2], springConstDiag,springMinDiag, springMaxDiag, springLengthDiag, damperConstDiag);
        springs_dampers[13]->addSDForce();
        
        springs_dampers[14] = new SpringDamper(masses[4], masses[7], springConstDiag,springMinDiag, springMaxDiag, springLengthDiag, damperConstDiag);
        springs_dampers[14]->addSDForce();
        
        springs_dampers[15] = new SpringDamper(masses[5], masses[6], springConstDiag,springMinDiag, springMaxDiag, springLengthDiag, damperConstDiag);
        springs_dampers[15]->addSDForce();
        
        springs_dampers[16] = new SpringDamper(masses[0], masses[5], springConstDiag,springMinDiag, springMaxDiag, springLengthDiag, damperConstDiag);
        springs_dampers[16]->addSDForce();
        
        springs_dampers[17] = new SpringDamper(masses[1], masses[4], springConstDiag,springMinDiag, springMaxDiag, springLengthDiag, damperConstDiag);
        springs_dampers[17]->addSDForce();
        
        springs_dampers[18] = new SpringDamper(masses[2], masses[7], springConstDiag,springMinDiag, springMaxDiag, springLengthDiag, damperConstDiag);
        springs_dampers[18]->addSDForce();
        
        springs_dampers[19] = new SpringDamper(masses[3], masses[6], springConstDiag,springMinDiag, springMaxDiag, springLengthDiag, damperConstDiag);
        springs_dampers[19]->addSDForce();
        
        springs_dampers[20] = new SpringDamper(masses[0], masses[6], springConstDiag,springMinDiag, springMaxDiag, springLengthDiag, damperConstDiag);
        springs_dampers[20]->addSDForce();
        
        springs_dampers[21] = new SpringDamper(masses[2], masses[4], springConstDiag,springMinDiag, springMaxDiag, springLengthDiag, damperConstDiag);
        springs_dampers[21]->addSDForce();
        
        springs_dampers[22] = new SpringDamper(masses[1], masses[7], springConstDiag,springMinDiag, springMaxDiag, springLengthDiag, damperConstDiag);
        springs_dampers[22]->addSDForce();
        
        springs_dampers[23] = new SpringDamper(masses[3], masses[5], springConstDiag,springMinDiag, springMaxDiag, springLengthDiag, damperConstDiag);
        springs_dampers[23]->addSDForce();
       /* int x = 0;
        int y = 0;
        int z = 0;
        for (int i = 0; i<2; i++){
            // x-led *************
            springs_dampers[i] = new SpringDamper(masses[x], masses[x+1],
                                                  springConstant, springMax, springMin, springLength, damperConstant);
            springs_dampers[i]->addSDForceX();
            springs_dampers[i+2] = new SpringDamper(masses[x+4], masses[x+5],
                                                  springConstant, springMax, springMin, springLength, damperConstant);
            springs_dampers[i+2]->addSDForceX();
            x = x + 2;
            //y-led **************
            springs_dampers[i+4] = new SpringDamper(masses[y], masses[y+2],
                                                  springConstant, springMax, springMin, springLength, damperConstant);
            springs_dampers[i+4]->addSDForceY();
            springs_dampers[i+6] = new SpringDamper(masses[y+4], masses[y+6],
                                                  springConstant, springMax, springMin, springLength, damperConstant);
            springs_dampers[i+6]->addSDForceY();
            y++;
            
            //z-led
            springs_dampers[i+8] = new SpringDamper(masses[z], masses[z+4],
                                                  springConstant, springMax, springMin, springLength, damperConstant);
            springs_dampers[i+8]->addSDForceZ();
            springs_dampers[i+10] = new SpringDamper(masses[z+2], masses[z+6],
                                                  springConstant, springMax, springMin, springLength, damperConstant);
            springs_dampers[i+10]->addSDForceZ();
            z++;
        }*/
        
        float x_pos[myShape.nverts];
        float y_pos[myShape.nverts];
        float z_pos[myShape.nverts];
        for(int i = 0; i < myShape.nverts; i++){
            masses[i]->simulateEuler(dt);
            x_pos[i] = masses[i]->position.x;
            y_pos[i] = masses[i]->position.y;
            z_pos[i] = masses[i]->position.z;
            
        }
        
        myShape.updateVertexArray(x_pos, y_pos, z_pos);
        myShape.generateVAO();
        
        
        
        /* ***************** */
        myShape.render();
        /* ***************** */
        
        // Swap buffers, i.e. display the image and prepare for next frame.
        glfwSwapBuffers(window);
        
        // Poll events (read keyboard and mouse input)
        glfwPollEvents();
        
        // Exit if the ESC key is pressed (and also if the window is closed).
        if(glfwGetKey(window, GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        
        // Do this in the rendering loop to update the uniform variable " time "
        time = (float)glfwGetTime(); // Number of seconds since the program was started
        glUseProgram(myShader.programID); // Activate the shader to set its variables
        glUniform1f(location_time, time); // Copy the value to the shader program
        
    }
    
    // Close the OpenGL window and terminate GLFW.
    glfwDestroyWindow(window);
    glfwTerminate();
    
    return 0;
}



