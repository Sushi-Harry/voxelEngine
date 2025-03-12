#include <glm/ext/vector_float3.hpp>
#include "Camera.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "../include/shaderClass.hpp"

using namespace std;

/*-------------------------------------------------------------------------------------------------------------*/
// Plane Struct for Frustum Culling
struct Plane{
    // Unit Vector
    glm::vec3 normal = glm::vec3(0.0f, 1.0f, 0.0f);
    // Distance from origin (initialized to be equal to 0.0f)
    float distance = 0.0f;

};

/*-------------------------------------------------------------------------------------------------------------*/
// Frustum Class
struct Frustum{
    Plane topFace;
    Plane bottomFace;

    Plane rightFace;
    Plane leftFace;

    Plane farFace;
    Plane nearFace;
};

/*------------------------------------------------------------------------------------------------------------*/
// Voxel Class
class Voxel{
public:
    Voxel( glm::vec3 PositionVector, glm::vec3 ScaleVector);
    ~Voxel();
    void drawVoxel(Camera camera);
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
    ~Chunk();
    void drawChunk_solid_color(Camera UpdatedCamera);
    void drawChunk_wireframe(Camera UpdatedCamera);

private:
    Camera cameraObject;
    Voxel* voxels[16][16][16];
};
