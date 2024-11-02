#version 440 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 inputNormal;
layout (location = 2) in vec3 aColor;  // Color attribute

out vec3 vertexColor;
out vec3 Normal;

uniform mat4 MVP;

void main() {
    gl_Position = MVP * vec4(aPos.x, aPos.y, aPos.z, 1.0);
    Normal = inputNormal;
    vertexColor = aColor;
}
