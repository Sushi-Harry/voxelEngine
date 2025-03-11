#ifndef ENGINE_H
#define ENGINE_H

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

private:
    GLFWwindow* window;
    Voxel* voxel1;

    bool initGLFW();
    bool initGLEW();
};

#endif // ENGINE_H