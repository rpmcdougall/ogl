#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "ShaderUtils.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


using namespace glm;

int main() {


    // An array of 3 vectors which represents 3 vertices
    static const GLfloat g_vertex_buffer_data[] = {
            -1.0f, -1.0f, 0.0f,
            1.0f, -1.0f, 0.0f,
            0.0f,  1.0f, 0.0f,
    };

    //Init glfw
    glewExperimental = GL_TRUE;
    if(!glfwInit()) {
        fprintf(stderr, "Failed to init GLFW...\n");
        getchar();
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

    GLFWwindow* window;
    window = glfwCreateWindow(1024,768, "Tutorial 01", NULL, NULL);
    if(!window) {
        fprintf( stderr, "Failed to open GLFW window.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }


    //Configure Vertex Array Object
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    //Define Vertex Buffer, Bind and Provide to OpenGL
    GLuint vertexBuffer;
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    /*
     * glBufferData — creates and initializes a buffer object's data store http://docs.gl/gl3/glBufferData
     */
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);


    //Capture escape key being pressed
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    //Load shaders
    GLuint programID = ShaderUtils::LoadShaders( "shaders/vertex.glsl", "shaders/fragment.glsl" );



    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 4.0f/3.0f, 0.1f, 100.0f );
    glm::mat4 View = glm::lookAt(
            glm::vec3(4,3,3), // Camera is at (4,3,3), in World Space
            glm::vec3(0,0,0), // and looks at the origin
            glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );

    //Model matrix : model will be at origin
    glm::mat4 Model = glm::mat4(1.0f);

    //MVP : multiplication of 3 matrices
    glm::mat4 mvp = Projection * View * Model;

    //Provide to GLSL
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");








    do {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //DRAW STUFF HERE
        //Use shader
        glUseProgram(programID);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

        //Send transformation to currently bound shader
        //Each model will have different mvp matrix, apply in main loop
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);
        glVertexAttribPointer(
                0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
        );


// Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
        glDisableVertexAttribArray(0);


        //Swapbuffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

        // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );


    return 0;
}