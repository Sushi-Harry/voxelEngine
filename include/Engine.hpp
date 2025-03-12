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

    void processMovement(GLFWwindow *window);

private:
    GLFWwindow* window;
    Camera camera;
    Chunk* newChunk;
    float lastFrame = 0.0f;
    float deltaTime = 0.0f;

    bool initGLFW();
    bool initGLEW();
};

#endif // ENGINE_H