#version 440 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal; // Normal attribute
layout (location = 2) in vec3 aColor;  // Color attribute

out vec3 vertexColor;
out vec3 Normal; // Pass normal to fragment shader

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    vertexColor = aColor;
    Normal = normalize(aNormal); // Normalize the normal vector
}


