#include "Engine.hpp"
#include "Camera.hpp"
#include "shaderClass.hpp"
#include <GLFW/glfw3.h>

Engine::Engine(int WIDTH, int HEIGHT, const char* TITLE){
    if(!initGLFW()){
        std::cerr << "FAILED TO INITIALIZE GLFW!\n";
        return;
    }

    window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
    if(!window){
        std::cerr << "FAILED TO INITIALIZE WINDOW\n";
        return;
    }
    glfwMakeContextCurrent(window);

    if(!initGLEW()){
        std::cerr << "FAILED TO INITIALIZE GLEW\n";
        return;
    }
    glViewport(0,0,800,600);
    glfwSwapInterval(1);
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

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    newChunk->drawChunk_solid_color(camera);
    processMovement(window);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
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