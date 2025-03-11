#include "include/Engine.hpp"

int main(){
    Engine engine(800, 600, "VoxelEngine");
    engine.chunkInitialization();

    while (engine.isRunning()) {
        engine.Update();
    }

    return 0;
}