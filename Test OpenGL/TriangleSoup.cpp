#include "TriangleSoup.hpp"
#include <iostream>

/* Constructor: initialize a TriangleSoup object to all zeros */
TriangleSoup::TriangleSoup() {
	vao = 0;
	vertexbuffer = 0;
	indexbuffer = 0;
	vertexarray = NULL;
	indexarray = NULL;
	nverts = 0;
	ntris = 0;
}


/* Destructor: clean up allocated data in a TriangleSoup object */
TriangleSoup::~TriangleSoup() {
    clean();
};


void TriangleSoup::clean() {

	if(glIsVertexArray(vao)) {
		glDeleteVertexArrays(1, &vao);
	}
	vao = 0;

	if(glIsBuffer(vertexbuffer)) {
		glDeleteBuffers(1, &vertexbuffer);
	}
	vertexbuffer = 0;

	if(glIsBuffer(indexbuffer)) {
		glDeleteBuffers(1, &indexbuffer);
	}
	indexbuffer = 0;

	if(vertexarray) {
		delete[] vertexarray;
		vertexarray = NULL;
	}
	if(indexarray) 	{
		delete[] indexarray;
		indexarray = NULL;
	}
	nverts = 0;
	ntris = 0;
}

void TriangleSoup::createSquare(float xsize, float ysize) {
    // The data array contains 8 floats per vertex:
    // coordinate xyz, normal xyz, texcoords st
    float zsize =1;
    const GLfloat vertex_array_data[] = {
        -xsize, -ysize, -zsize,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Vertex 0
        xsize, -ysize, -zsize,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Vertex 1
        -xsize,  ysize, -zsize,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  // Vertex 2
        xsize,  ysize, -zsize,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  // Vertex 3
    };
    
    const GLuint index_array_data[] = {
        0,3,1,
        0,2,3,
    };
    
    nverts = 4;
    ntris = 2;
    
    vertexarray = new GLfloat[8*nverts];
    indexarray = new GLuint[3*ntris];

    for(int i=0; i<8*nverts; i++) {
        vertexarray[i]=vertex_array_data[i];
    }
    for(int i=0; i<3*ntris; i++) {
        indexarray[i]=index_array_data[i];
    }
    
}

/* Create a simple box geometry */
/* TODO: Split to 24 vertices, get the normals and texcoords right. */
void TriangleSoup::createBox(float xsize, float ysize, float zsize) {

    // The data array contains 8 floats per vertex:
    // coordinate xyz, normal xyz, texcoords st
    const GLfloat vertex_array_data[] = {
        -xsize, -ysize, -zsize,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Vertex 0
         xsize, -ysize, -zsize,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Vertex 1
        -xsize,  ysize, -zsize,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  // Vertex 2
         xsize,  ysize, -zsize,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  // Vertex 3
        -xsize, -ysize,  zsize,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Vertex 0
         xsize, -ysize,  zsize,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Vertex 1
        -xsize,  ysize,  zsize,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,  // Vertex 2
         xsize,  ysize,  zsize,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f  // Vertex 3
    };
    
    const GLuint index_array_data[] = {
        0,3,1,
        0,2,3,
        1,4,0,
        1,5,4,
        4,2,0,
        4,6,2,
        1,3,7,
        1,7,5,
        7,2,6,
        7,3,2,
        4,5,7,
        4,7,6
    };

    nverts = 8;
    ntris = 12;

    vertexarray = new GLfloat[8*nverts];
    indexarray = new GLuint[3*ntris];

    for(int i=0; i<8*nverts; i++) {
        vertexarray[i]=vertex_array_data[i];
    }
    for(int i=0; i<3*ntris; i++) {
        indexarray[i]=index_array_data[i];
    }

}

void TriangleSoup::updateVertexArray(float x[], float y[], float z[]){
    //Changes to 4 because we use a square instead of a box right now **********************
    //nverts = 8;
    vertexarray = new GLfloat[8*nverts];
    int k = 0;
    for(int i=0; i<nverts; i++) {
        vertexarray[k]=x[i];
        vertexarray[k+1]=y[i];
        vertexarray[k+2]=z[i];
        k +=8;
    }
}

void TriangleSoup::generateVAO(){
	// Generate one vertex array object (VAO) and bind it
	glGenVertexArrays(1, &(vao));
	glBindVertexArray(vao);

	// Generate two buffer IDs
	glGenBuffers(1, &vertexbuffer);
	glGenBuffers(1, &indexbuffer);

 	// Activate the vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
 	// Present our vertex coordinates to OpenGL
	glBufferData(GL_ARRAY_BUFFER,
		8*nverts * sizeof(GLfloat), vertexarray, GL_STATIC_DRAW);
	// Specify how many attribute arrays we have in our VAO
	glEnableVertexAttribArray(0); // Vertex coordinates
	glEnableVertexAttribArray(1); // Normals
	glEnableVertexAttribArray(2); // Texture coordinates
	// Specify how OpenGL should interpret the vertex buffer data:
	// Attributes 0, 1, 2 (must match the lines above and the layout in the shader)
	// Number of dimensions (3 means vec3 in the shader, 2 means vec2)
	// Type GL_FLOAT
	// Not normalized (GL_FALSE)
	// Stride 8 floats (interleaved array with 8 floats per vertex)
	// Array buffer offset 0, 3 or 6 floats (offset into first vertex)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
		8*sizeof(GLfloat), (void*)0); // xyz coordinates
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
		8*sizeof(GLfloat), (void*)(3*sizeof(GLfloat))); // normals
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
		8*sizeof(GLfloat), (void*)(6*sizeof(GLfloat))); // texcoords

 	// Activate the index buffer
 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
 	// Present our vertex indices to OpenGL
 	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
	 	3*ntris*sizeof(GLuint), indexarray, GL_STATIC_DRAW);

	// Deactivate (unbind) the VAO and the buffers again.
	// Do NOT unbind the index buffer while the VAO is still bound.
	// The index buffer is an essential part of the VAO state.
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
 	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
};

/* Print data from a TriangleSoup object, for debugging purposes */
void TriangleSoup::print() {
     int i;

     printf("TriangleSoup vertex data:\n\n");
     for(i=0; i<nverts; i++) {
         printf("%d: %8.2f %8.2f %8.2f\n", i,
         vertexarray[8*i], vertexarray[8*i+1], vertexarray[8*i+2]);
     }
     printf("\nTriangleSoup face index data:\n\n");
     for(i=0; i<ntris; i++) {
         printf("%d: %d %d %d\n", i,
         indexarray[3*i], indexarray[3*i+1], indexarray[3*i+2]);
     }
};


/* Render the geometry in a TriangleSoup object */
void TriangleSoup::render() {

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 3 * ntris, GL_UNSIGNED_INT, (void*)0);
	// (mode, vertex count, type, element array buffer offset)
	glBindVertexArray(0);

};

/*
 * private
 * printError() - Signal an error.
 * Simple printf() to console for portability.
 */
void TriangleSoup::printError(const char *errtype, const char *errmsg) {
  fprintf(stderr, "%s: %s\n", errtype, errmsg);
};
