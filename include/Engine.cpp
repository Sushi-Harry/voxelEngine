#include "Engine.hpp"
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
    voxel1 = new Voxel(glm::vec3(0.0f, 0.0f, -5.0f), glm::vec3(2.0f, 2.0f, 2.0f));
}

bool Engine::isRunning(){
    return !glfwWindowShouldClose(window);
}

void Engine::Update(){
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    voxel1->drawVoxel();
    glfwSwapBuffers(window);
    glfwPollEvents();
}