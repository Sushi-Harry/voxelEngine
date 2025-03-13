#include "Camera.hpp"
#include "Chunk.hpp"

lightObject::lightObject(glm::vec3 lightPos, Camera inputCamObject){
    lightVoxel = new Voxel(lightPos, glm::vec3(1.0f), "include/shaders/vertBase.vs", "include/shaders/fragBase.fs");
    camera = inputCamObject;
}

lightObject::~lightObject(){
    delete lightVoxel;
}

void lightObject::drawLight(){
    lightVoxel->drawVoxel(camera);
}