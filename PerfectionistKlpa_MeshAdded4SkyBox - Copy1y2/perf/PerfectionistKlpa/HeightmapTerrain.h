// HeightmapTerrain.h

#pragma once

#include <vector>

class HeightmapTerrain {
public:
    HeightmapTerrain(const char* heightmapPath, int size, float maxHeight);

    void render();

public:
    std::vector<float> m_heightmap;
    int m_size;
    float m_maxHeight;

    GLuint m_vao;
    GLuint m_vbo;
};

