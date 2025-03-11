#include <glm/ext/vector_float3.hpp>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "../include/shaderClass.hpp"

using namespace std;
class Voxel{

public:
    Voxel( glm::vec3 PositionVector, glm::vec3 ScaleVector);
    ~Voxel();
    void drawVoxel();

private:
    int id; // 0 = empty, 1 = To Be Rendered
    glm::vec3 scale;
    glm::vec3 position;
    unsigned int VAO;
    unsigned int VBO;
    float Vertices[180];
    Shader* shader;
};

class Chunk{

public:
    Chunk();
    ~Chunk();

private:
    Voxel voxelArray_3D[16][16][16];
};

class testVoxelClass{

public:
    testVoxelClass(float* vertexData[8]);
    ~testVoxelClass();

private:
    Voxel voxel;

};