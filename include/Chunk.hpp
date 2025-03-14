#pragma once

#include <glm/ext/vector_float3.hpp>
#include <glm/geometric.hpp>
#include "Camera.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "../include/shaderClass.hpp"

using namespace std;

/*------------------------------------------------------------------------------------------------------------*/
// Voxel Class
class Voxel{
public:
    Voxel( glm::vec3 PositionVector, glm::vec3 ScaleVector, const char* VSPath, const char* FSPath);
    ~Voxel();
    void drawVoxel(Camera camera);
    void drawLitVoxel(Camera camera, glm::vec3 lightPos);
    void ChunkDrawFunction(Camera camera, glm::vec3 Light_Position, Shader* SharedChunkShader);
    void SetActive();
    void setInactive();
    bool isActive();

private:
    bool id; // 0 = empty, 1 = To Be Rendered
    glm::vec3 scale;
    glm::vec3 position;
    unsigned int VAO;
    unsigned int VBO;
    float Vertices[180];
    Shader* shader;
};

/*-------------------------------------------------------------------------------------------------------------*/
// Chunk Class
class Chunk{
public:
    Chunk(Camera camera);
    Chunk(Shader* shader) : SharedChunkShader(shader){}
    ~Chunk();
    void drawChunk_solid_color(Camera UpdatedCamera, glm::vec3 lightPos);
    void drawChunk_wireframe(Camera UpdatedCamera, glm::vec3 lightPos);
    void drawChunk_lit(Camera UpdatedCamera, glm::vec3 Light_Position);

private:
    Camera cameraObject;
    Shader* SharedChunkShader;
    Voxel* voxels[16][16][16];
};