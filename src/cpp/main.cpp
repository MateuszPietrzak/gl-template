#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include "../../include/Shader.h"
#include "../../include/Camera.h"
#include "../../include/Model.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../../include/Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


int WIDTH = 1200, HEIGHT = 800;

float delta_time = 0.0f;
float last_frame = 0.0f;

Camera* cam;
GLFWwindow* window;
glm::mat4 projection;

void init();
void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void mouseCallback(GLFWwindow* window, double x_pos, double y_pos);
void processInput(GLFWwindow* window);


int main() {
    init();

    auto model_shader = new Shader("src/glsl/model_shader.vert", "src/glsl/model_shader.frag");

    auto scene = new Model("assets/scene.obj");

    cam = new Camera(WIDTH, HEIGHT);

    projection = glm::perspective((float)(M_PI / 4), (float)(WIDTH) / (float)(HEIGHT), 0.1f, 300.0f);

    model_shader->use();
    model_shader->setMat4("projection", projection);

    auto light_direction = glm::normalize(glm::vec3(1.0f, 10.0f, 1.0f));
    model_shader->setVec3("light_direction", light_direction);

    while(!glfwWindowShouldClose(window)) {
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        model_shader->setMat4("view", cam->getMatrix());

        // Here you can set the model's transformation.
        auto model = glm::mat4(1.0f);
        model_shader->setMat4("model", model);

        scene->draw(model_shader);

        glfwSwapBuffers(window);
        glfwPollEvents();

        delta_time = glfwGetTime() - last_frame;
        last_frame = glfwGetTime();
    }

    glfwTerminate();

    return 0;
}


void init() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(WIDTH, HEIGHT, "OpenGL", NULL, NULL);
    if(window == NULL) {
        std::cout << "Failed to create a window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glEnable(GL_DEPTH_TEST);

    glViewport(0, 0, WIDTH, HEIGHT);

    glClearColor(0.2, 0.5, 0.8, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouseCallback);
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    WIDTH = width;
    HEIGHT = height;
    projection = glm::perspective((float)(M_PI / 4), (float)(WIDTH) / (float)(HEIGHT), 0.1f, 300.0f);
}

void mouseCallback(GLFWwindow* window, double x_pos, double y_pos) {
    cam->processMouse(x_pos, y_pos, delta_time);
}

void processInput(GLFWwindow* window) {
    cam->processKeyboard(window, delta_time);
}
