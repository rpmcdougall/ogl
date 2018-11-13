#version 330 core

//Switch to color buffer
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
//forward fragmentcolor to fragment shader
out vec3 fragmentColor;

//values stay constant for whole mesh
uniform mat4 MVP;

void main() {
  // Output position of the vertex, in clip space : MVP * position
  gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
  fragmentColor = vertexColor;
}
