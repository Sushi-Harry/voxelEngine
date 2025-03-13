#include "Engine.hpp"
#include "Camera.hpp"
#include "shaderClass.hpp"
#include <GLFW/glfw3.h>
#include <cmath>
#include <glm/geometric.hpp>
#include <glm/trigonometric.hpp>

Engine::Engine(int WIDTH, int HEIGHT, const char* TITLE){
    if(!initGLFW()){
        std::cerr << "FAILED TO INITIALIZE GLFW!\n";
        return;
    }

    window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, nullptr, nullptr);
    if(!window){
        std::cerr << "FAILED TO INITIALIZE WINDOW\n";
        return;
    }
    glfwMakeContextCurrent(window);
    // Framebuffer Size Callback (I barely get this user pointer thing. Thanks C++ and GLFW)
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetWindowUserPointer(window, this);
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if(!initGLEW()){
        std::cerr << "FAILED TO INITIALIZE GLEW\n";
        return;
    }
    glViewport(0,0,800,600);
    glfwSwapInterval(1);

    // Lighting initialisation
    light = new lightObject(glm::vec3(10.0f, 20.0f, 0.0f), camera);
}

Engine::~Engine(){
    glfwDestroyWindow(window);
    glfwTerminate();
}

bool Engine::initGLFW(){
    if(!glfwInit()){
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glEnable(GL_DEPTH_TEST);
    return true;
}

bool Engine::initGLEW(){
    glewExperimental = GL_TRUE;
    return glewInit() == GLEW_OK;
}

void Engine::chunkInitialization(){
    newChunk = new Chunk(camera);
}

bool Engine::isRunning(){
    return !glfwWindowShouldClose(window);
}

void Engine::Update(){

    float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // light->drawLight();
    
    newChunk->drawChunk_solid_color(camera, glm::vec3(-10.0f, 5.0f, 0.0f));
    processMovement(window);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
}

void Engine::framebuffer_size_callback(GLFWwindow* window, int WIDTH, int HEIGHT){
    Engine* engineInstance = static_cast<Engine*>(glfwGetWindowUserPointer(window));
    if(engineInstance){
        glViewport(0, 0, WIDTH, HEIGHT);
    }
}

void Engine::mouse_callback(GLFWwindow* window, double xposIn, double yposIn){
    Engine* engineInstance = static_cast<Engine*>(glfwGetWindowUserPointer(window));
    
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if(engineInstance->firstmouse){
        engineInstance->lastX = xpos;
        engineInstance->lastY = ypos;
        engineInstance->firstmouse = false;
    }

    float xOffset = xpos - engineInstance->lastX;
    float yOffset = engineInstance->lastY - ypos;
    engineInstance->lastX = xpos;
    engineInstance->lastY = ypos;

    engineInstance->camera.ProcessMouseMovement(xOffset, yOffset);
}

void Engine::processMovement(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}