#include "Chunk.hpp"
#include "Camera.hpp"
#include "shaderClass.hpp"
#include <GLFW/glfw3.h>
#include <glm/ext/vector_float3.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

/*-------------------------------------------------------------------------------------------------------------*/
// Chunk Class Definitions
Chunk::Chunk(Camera camera){
    cameraObject = camera;

    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            for(int k = 0; k < 16; k++){
                voxels[i][j][k] = new Voxel(glm::vec3(i, j, k), glm::vec3(1.0f), "include/shaders/vertLit.vs", "include/shaders/fragLit.fs");
            }
        }
    }
}

Chunk::~Chunk(){
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            for(int k = 0; k < 16; k++){
                delete voxels[i][j][k];
            }
        }
    }
}

void Chunk::drawChunk_solid_color(Camera UpdatedCamera, glm::vec3 lightPos){\
    cameraObject = UpdatedCamera;
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            for(int k = 0; k < 16; k++){
                if(voxels[i][j][k]->isActive())
                    voxels[i][j][k]->drawLitVoxel(cameraObject, lightPos);
            }
        }
    }
}

void Chunk::drawChunk_wireframe(Camera UpdatedCamera, glm::vec3 lightPos){
    cameraObject = UpdatedCamera;
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            for(int k = 0; k < 16; k++){
                if(voxels[i][j][k]->isActive())
                    voxels[i][j][k]->drawLitVoxel(cameraObject, lightPos);
            }
        }
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
