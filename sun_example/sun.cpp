#include <iostream>
#include <fstream>
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <cstddef>
#include <cstdlib>


// settings
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 576;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void generateCubeData(float size, glm::vec3 color, std::vector<float>& vertices, std::vector<unsigned int>& indices);

//sun
float get_sun_rotate_angle_around_itself(float day);


const char *vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;

    out vec3 vertexColor;

    uniform mat4 model;
    uniform mat4 view;
    uniform mat4 projection;

    void main() {
        gl_Position = projection * view * model * vec4(aPos, 1.0);
        vertexColor = aColor;
    }
)";

const char *fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    in vec3 vertexColor;

    void main() {
        FragColor = vec4(vertexColor, 1.0);
    }
)";






int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Multi-Colored Cube", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    std::vector<float> vertices_sun, vertices_earth, vertices_moon;
    std::vector<unsigned int> indices_sun, indices_earth, indices_moon;

    //sun (20 x 20 x 20) - yellow
    generateCubeData(20.0f, glm::vec3(1.0f, 1.0f, 0.0f), vertices_sun, indices_sun);




    unsigned int VAO_sun, VBO_sun, EBO_sun;

    // Generate and bind the first set of VAO, VBO, EBO
    glGenVertexArrays(1, &VAO_sun);
    glGenBuffers(1, &VBO_sun);
    glGenBuffers(1, &EBO_sun);
    glBindVertexArray(VAO_sun);
    glBindBuffer(GL_ARRAY_BUFFER, VBO_sun);
    glBufferData(GL_ARRAY_BUFFER, vertices_sun.size() * sizeof(float), vertices_sun.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_sun);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_sun.size() * sizeof(unsigned int), indices_sun.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)) );
    glEnableVertexAttribArray(1);


    //render
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.3f, 0.4f, 0.5f, 1.0f);

    // render loop
    // -----------
    float day = 0, inc = 1.0f/24;
    float sun_rotation;

    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        //render
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::lookAt(glm::vec3(120.0f, 100.0f, 80.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)); 
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), (16.0f / 9.0f), 0.1f, 1000.0f);

        unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
        unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
        unsigned int projLoc = glGetUniformLocation(shaderProgram, "projection");
 
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));      



        day += inc;
        sun_rotation = get_sun_rotate_angle_around_itself(day);

        // Render the sun
        glBindVertexArray(VAO_sun); 
        model = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(sun_rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
        //glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));  
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));  
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO_sun);
    glDeleteBuffers(1, &VBO_sun);
    glDeleteBuffers(1, &EBO_sun);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}




//key board control
void processInput(GLFWwindow *window)
{
    //press escape to exit
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}







void generateCubeData(float size, glm::vec3 color, std::vector<float>& vertices, std::vector<unsigned int>& indices) {
    float halfSize = size / 2.0f;

    float cubeVertices[] = {
        //Front Face (z = 1) Red: rgb (1,0,0)
        -halfSize, -halfSize,  halfSize, 1.0f, 0.0f, 0.0f,
         halfSize, -halfSize,  halfSize, 1.0f, 0.0f, 0.0f,
         halfSize,  halfSize,  halfSize, 1.0f, 0.0f, 0.0f,
        -halfSize,  halfSize,  halfSize, 1.0f, 0.0f, 0.0f,

        //Back Face (z = -1) Green: rgb (0,1,0)
        -halfSize, -halfSize, -halfSize, 0.0f, 1.0f, 0.0f,
         halfSize, -halfSize, -halfSize, 0.0f, 1.0f, 0.0f,
         halfSize,  halfSize, -halfSize, 0.0f, 1.0f, 0.0f,
        -halfSize,  halfSize, -halfSize, 0.0f, 1.0f, 0.0f,

        //Left Face (x = -1) Blue: rgb (0,0,1)
        -halfSize, -halfSize, -halfSize, 0.0f, 0.0f, 1.0f,
        -halfSize,  halfSize, -halfSize, 0.0f, 0.0f, 1.0f,
        -halfSize,  halfSize,  halfSize, 0.0f, 0.0f, 1.0f,
        -halfSize, -halfSize,  halfSize, 0.0f, 0.0f, 1.0f,

        //Right Face (x = 1) Aqua: rgb (0,1,1)
         halfSize, -halfSize, -halfSize, 0.0f, 1.0f, 1.0f,
         halfSize,  halfSize, -halfSize, 0.0f, 1.0f, 1.0f,
         halfSize,  halfSize,  halfSize, 0.0f, 1.0f, 1.0f,
         halfSize, -halfSize,  halfSize, 0.0f, 1.0f, 1.0f,

        //Top Face (y = 1) Fuchsia: rgb (1,0,1)
        -halfSize,  halfSize, -halfSize, 1.0f, 0.0f, 1.0f,
         halfSize,  halfSize, -halfSize, 1.0f, 0.0f, 1.0f,
         halfSize,  halfSize,  halfSize, 1.0f, 0.0f, 1.0f,
        -halfSize,  halfSize,  halfSize, 1.0f, 0.0f, 1.0f,

        //Bottom Face (y = -1) Yellow: rgb (1,1,0)
        -halfSize, -halfSize, -halfSize, 1.0f, 1.0f, 0.0f,
         halfSize, -halfSize, -halfSize, 1.0f, 1.0f, 0.0f,
         halfSize, -halfSize,  halfSize, 1.0f, 1.0f, 0.0f,
        -halfSize, -halfSize,  halfSize, 1.0f, 1.0f, 0.0f
    }; 

    unsigned int cubeIndices[] = {
        //Front 
         0,  1,  2,  2,  3,  0,
        //Back 
         4,  5,  6,  6,  7,  4,
        //Left 
         8,  9, 10, 10, 11,  8,
        //Right 
        12, 13, 14, 14, 15, 12,
        //Top 
        16, 17, 18, 18, 19, 16,
        //Bottom 
        20, 21, 22, 22, 23, 20,
    }; 

    vertices.insert(vertices.end(), std::begin(cubeVertices), std::end(cubeVertices));
    indices.insert(indices.end(), std::begin(cubeIndices), std::end(cubeIndices));
}




//sun
float get_sun_rotate_angle_around_itself(float day) {
    return (360.0f / 27.0f) * day;
}
