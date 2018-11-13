#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;

//values stay constant for whole mesh
uniform mat4 MVP;

void main() {
  // Output position of the vertex, in clip space : MVP * position
  gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
}
