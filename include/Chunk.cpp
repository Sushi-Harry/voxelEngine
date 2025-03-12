#include "Chunk.hpp"
#include "Camera.hpp"
#include "shaderClass.hpp"
#include <GLFW/glfw3.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

/*-------------------------------------------------------------------------------------------------------------*/
// Voxel Class Definitions
Voxel::Voxel(glm::vec3 PositionVector, glm::vec3 ScaleVector){

    float Vertices[] = {
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f
    };

    position = PositionVector;
    scale = glm::vec3(1.0f);

    id = 1;

    shader = new Shader("include/shaders/baseVoxelVert.vs", "include/shaders/baseVoxelFrag.fs");

    // EBO and VBO and VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
}

Voxel::~Voxel() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    delete shader;
}

void Voxel::SetActive(){
    id = 1;
}

void Voxel::setInactive(){
    id = 0;
}

void Voxel::drawVoxel(Camera camera){

    if(id == 1){
        // Activate Shader
        shader->useShader();
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        unsigned int modelLoc = glGetUniformLocation(shader->shaderID, "model");
        unsigned int viewLoc = glGetUniformLocation(shader->shaderID, "view");
        unsigned int projectionLoc = glGetUniformLocation(shader->shaderID, "projection");
        model = glm::scale(model, scale);
        model = glm::translate(model, position);
        view = camera.GetViewMatrix();
        projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);


        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);}
}

bool Voxel::isActive(){
    return id;
}

/*-------------------------------------------------------------------------------------------------------------*/
// Chunk Class Definitions
Chunk::Chunk(Camera camera){
    cameraObject = camera;

    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            for(int k = 0; k < 16; k++){
                voxels[i][j][k] = new Voxel(glm::vec3(i, j, k), glm::vec3(1.0f));
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

void Chunk::drawChunk_solid_color(Camera UpdatedCamera){\
    cameraObject = UpdatedCamera;
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            for(int k = 0; k < 16; k++){
                if(voxels[i][j][k]->isActive())
                    voxels[i][j][k]->drawVoxel(cameraObject);
            }
        }
    }
}

void Chunk::drawChunk_wireframe(Camera UpdatedCamera){
    cameraObject = UpdatedCamera;
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 16; j++){
            for(int k = 0; k < 16; k++){
                if(voxels[i][j][k]->isActive())
                    voxels[i][j][k]->drawVoxel(cameraObject);
            }
        }
    }
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

/*-------------------------------------------------------------------------------------------------------------*/
// Frustum Definitions
// Frustum creatFrustumFromCamera()