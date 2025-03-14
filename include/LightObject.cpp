#include "LightObject.hpp"
#include "Camera.hpp"
#include <glm/ext/vector_float3.hpp>

LightObject::LightObject(){
    Position = glm::vec3(0.0f, 0.0f, 0.0f);
    LightBody = new Voxel(Position, glm::vec3(5.0f), "include/shaders/vertBase.vs", "include/shaders/fragBase.fs");
    std::cout << "Voxel Position: " << Position.x << "," << Position.y << "," << Position.z << std::endl;
}

LightObject::~LightObject(){
    delete LightBody;
}

void LightObject::DrawLightObject(Camera cam){
    LightBody->drawVoxel(cam);
}

glm::vec3 LightObject::LightPosition(){
    return Position;
}