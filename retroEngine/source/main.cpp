#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include "shader.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

#define PI 3.14159265
const char *transformvertexShaderSource ="#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "uniform mat4 transform;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = transform * vec4(aPos, 1.0);\n"
    "   ourColor = aColor;\n"
    "}\0";

const char *vertexShaderSource ="#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aColor;\n"
    "out vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos, 1.0);\n"
    "   ourColor = aColor;\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 ourColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(ourColor, 1.0f);\n"
    "}\n\0";

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "RetroEngine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Shader bgShader(vertexShaderSource, fragmentShaderSource);
    Shader chShader(transformvertexShaderSource, fragmentShaderSource);
    Shader houseShader(vertexShaderSource, fragmentShaderSource);

    float bgvertices[] = {
         1.0f,  1.0f, -0.5f,  0.0f, 0.3f, 0.1f,// top right
         1.0f,  0.2f, -0.5f,  0.0f, 0.3f, 0.1f,// bottom right
        -1.0f,  0.2f, -0.5f,  0.0f, 0.3f, 0.1f,// bottom left
        -1.0f,  1.0f, -0.5f,  0.0f, 0.3f, 0.1f,// top left 

        1.0f, -0.2f, -0.5f,  0.0f, 0.3f, 0.1f,
        1.0f, -1.0f, -0.5f,  0.0f, 0.3f, 0.1f,
        0.2f, -1.0f, -0.5f,  0.0f, 0.3f, 0.1f,
        0.2f, -0.2f, -0.5f,  0.0f, 0.3f, 0.1f,

        -1.0f, -0.2f, -0.5f,  0.0f, 0.3f, 0.1f,
        -1.0f, -1.0f, -0.5f,  0.0f, 0.3f, 0.1f,
        -0.2f, -1.0f, -0.5f,  0.0f, 0.3f, 0.1f,
        -0.2f, -0.2f, -0.5f,  0.0f, 0.3f, 0.1f,
    };
    unsigned int bgindices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3,   // second Triangle
        4, 5, 7,
        5, 6, 7,
        8, 9, 11,
        9, 10, 11
    };

    float chvertices[]={
         0.04f,  0.04f, 0.0f,  0.6f, 0.3f, 0.1f,// top right
         0.04f,  -0.04f, 0.0f,  0.6f, 0.3f, 0.1f,// bottom right
         -0.04f,  -0.04f, 0.0f,  0.6f, 0.3f, 0.1f,// bottom left
         -0.04f,  0.04f, 0.0f,  0.6f, 0.3f, 0.1f,// top left 
    };

    unsigned int chindices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3,   // second Triangle
    };

    float housevertices[] = {
         -0.3f,  0.7f, 0.5f,  0.8f, 0.4f, 0.9f,// top right
         -0.2f,  0.6f, 0.5f,  0.8f, 0.4f, 0.9f,// bottom right
         -0.6f,  0.6f, 0.5f,  0.8f, 0.4f, 0.9f,// bottom left
         -0.5f,  0.7f, 0.5f,  0.8f, 0.4f, 0.9f,// top left 

        -0.2f, 0.6f, 0.5f,  0.9f, 0.9f, 0.9f,
        -0.2f, 0.4f, 0.5f,  0.9f, 0.9f, 0.9f,
        -0.6f, 0.4f, 0.5f,  0.9f, 0.9f, 0.9f,
        -0.6f, 0.6f, 0.5f,  0.9f, 0.9f, 0.9f,
    };
    unsigned int houseindices[] = {  // note that we start from 0!
        0, 1, 3,  // first Triangle
        1, 2, 3,   // second Triangle
        4, 5, 7,
        5, 6, 7
    };

    unsigned int VBOs[3], VAOs[3], EBOs[3];
    glGenVertexArrays(3, VAOs); 
    glGenBuffers(3, VBOs);
    glGenBuffers(3, EBOs);


    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(bgvertices), bgvertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(bgindices), bgindices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glBindVertexArray(VAOs[1]);	
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(chvertices), chvertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(chindices), chindices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(VAOs[2]);	
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(housevertices), housevertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(houseindices), houseindices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    

    std::cout << "se ha iniciado correctamente el juego " <<std::endl;
    float i = 0;
    float j = 0;
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        bgShader.use();
        glBindVertexArray(VAOs[0]); 
        glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);

        houseShader.use();
        glBindVertexArray(VAOs[2]); 
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
        
        chShader.use();
        glm::mat4 transform = glm::mat4(1.0f);
        transform = glm::translate(transform, glm::vec3(std::sin(i) * 0.8f, 0.0f, 0.0f));
        i += 0.001;
        unsigned int transformLoc = glGetUniformLocation(chShader.ID, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));

        glBindVertexArray(VAOs[1]); 
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glDeleteVertexArrays(3, VAOs);
    glDeleteBuffers(3, VBOs);
    glDeleteBuffers(3, EBOs);

    glfwTerminate();
    return 0;
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

