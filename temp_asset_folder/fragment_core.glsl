#version 440 core
in vec3 Normal;
out vec4 FragColor;

void main() {
    float c = dot(Normal, vec3(0.8, 0.7, 0.6));
    FragColor = vec4(c, c, c, 1.0);  // Add 1.0 as the alpha component
}