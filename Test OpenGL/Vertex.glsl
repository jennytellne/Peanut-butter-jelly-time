
/* ------------------------------------------
#version 330 core
uniform float time;
uniform mat4 M1;
layout (location = 0) in vec3 Position;
layout (location = 1) in vec3 Color ;
out vec3 interpolatedColor ;
void main() {
    //vec3 a = vec3(1.0,0.0,0.0); Addera a till position för att translera, *a för att skala
    gl_Position = M1*vec4(Position,1.0);
    // Transform (x,y,z) vertex coordinates with a 4x4 matrix T
    //gl_Position = T*R*vec4(Position, 1.0);
    interpolatedColor = Color ; // Pass interpolated color to fragment shader
} ------------------------------------------ */

#version 330 core
uniform mat4 M1;
layout(location=0)in vec3 Position;
layout(location=1)in vec3 Normal;
layout(location=2) in vec2 TexCoord;
out vec3 interpolatedNormal;
out vec2 st;
void main(){
    gl_Position = vec4(Position, 1.0); // Special , required output
    vec3 transformedNormal = mat3(M1)*Normal;
    interpolatedNormal = normalize(transformedNormal);
    //interpolatedNormal = Normal; // Will be interpolated across the triangle
    st = TexCoord; // Will also be interpolated across the triangle
}


