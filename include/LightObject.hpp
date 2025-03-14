#pragma once
#include "Camera.hpp"
#include "Chunk.hpp"

class LightObject{
public:
    LightObject();
    ~LightObject();

    void DrawLightObject(Camera cam);
    glm::vec3 LightColor();
    glm::vec3 LightPosition();
private:
    glm::vec3 Position;
    Voxel* LightBody;
};