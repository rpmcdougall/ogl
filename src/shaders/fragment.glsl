#version 330 core

//take in fragment color from vertex shader
in vec3 fragmentColor;
out vec3 color;
void main() {
    //Use colors passed in from vertex shader
    color = fragmentColor;
}
