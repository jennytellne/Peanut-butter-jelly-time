/* TriangleSoup.hpp */
/*
 * A class to manage a basic vertex array and index array
 * in an OpenGL vertex array object. */
/* Usage: The methods createXXX() create geometry from fixed
 * arrays or procedural descriptions.
 * The method loadOBJ() loads geometry from an OBJ file.
 * Only the mesh is loaded. Material information is ignored.
 * Only triangles are supported. OBJ files with quads are rejected.
 * Call render() to draw the mesh in OpenGL. */
/* Author: Stefan Gustavson 2013-2014 (stefan.gustavson@liu.se)
 * This code is in the public domain.
 *
 *
 * Code modified and completed by Sofia Linevik and Jenny Tellne 2017
 */

#ifndef TRIANGLESOUP_HPP // Avoid including this header twice
#define TRIANGLESOUP_HPP

#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#endif

#include <GLFW/glfw3.h>   // To use OpenGL datatypes

#include <cstdio>  // For C-style file input in readOBJ()
#include <cmath>   // For sin() and cos() in soupCreateSphere()
#include <cstring> // For strcmp() - a leftover from the C version

// Some <cmath> headers define M_PI, some don't. Make sure we have it.
#ifndef M_PI
#define M_PI (3.14159265359)
#endif // M_PI

#include "Utilities.hpp"  // To be able to use OpenGL extensions

/* A struct to hold geometry data and send it off for rendering */
class TriangleSoup {

public:

    // All data members are private. They are accessed only by methods in the class.
    GLuint vao;          // Vertex array object, the main handle for geometry
    GLuint vertexbuffer; // Buffer ID to bind to GL_ARRAY_BUFFER
    GLuint indexbuffer;  // Buffer ID to bind to GL_ELEMENT_ARRAY_BUFFER
    GLfloat *vertexarray; // Vertex array on interleaved format: x y z nx ny nz s t
    GLuint *indexarray;   // Element index array
    
    int nverts; // Number of vertices in the vertex array
    int ntris;  // Number of triangles in the index array (may be zero)

/* Constructor: initialize a triangleSoup object to all zeros */
TriangleSoup();

/* Destructor: clean up allocated data in a triangleSoup object */
~TriangleSoup();

/* Clean up allocated data in a triangleSoup object */
void clean();
    
void createSquare(float xsize, float ysize);

/* Create a simple box geometry */
void createBox(float xsize, float ysize, float zsize);

void generateVAO();
    
void updateVertexArray(float x[], float y[], float z[]);

/* Print data from a triangleSoup object, for debugging purposes */
void print();

/* Render the geometry in a triangleSoup object */
void render();

private:

void printError(const char *errtype, const char *errmsg);

};

#endif // TRIANGLESOUP_HPP
