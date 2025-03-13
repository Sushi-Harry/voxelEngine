#ifndef ENGINE_H
#define ENGINE_H

#include "Camera.hpp"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "Chunk.hpp"

class Engine{

public:
    Engine(int WIDTH, int HEIGHT, const char* TITLE);
    ~Engine();

    void chunkInitialization();

    bool isRunning();
    void Update();

    static void framebuffer_size_callback(GLFWwindow* window, int WIDTH, int HEIGHT);
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void processMovement(GLFWwindow *window);

private:
    GLFWwindow* window;
    Camera camera;
    Chunk* newChunk;
    lightObject* light;
    
    float lastFrame = 0.0f;
    float deltaTime = 0.0f;
    
    bool firstmouse = true;
    float lastX = 800.0f/2.0f;
    float lastY = 600.0/2.0f;
    float yaw = -90.0f;
    float pitch = 0.0f;
    float fov = 45.0f;

    bool initGLFW();
    bool initGLEW();
};

#endif // ENGINE_H