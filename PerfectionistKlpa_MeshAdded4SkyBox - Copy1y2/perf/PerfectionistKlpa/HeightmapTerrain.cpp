// HeightmapTerrain.cpp

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <windows.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include "stb_image.h"
#include "HeightmapTerrain.h"
//#define STB_IMAGE_IMPLEMENTATION    
//#include "stb_image.h"

HeightmapTerrain::HeightmapTerrain(const char* heightmapPath, int size, float maxHeight)
    : m_size(size), m_maxHeight(maxHeight)
{
    // Load heightmap from file
    std::ifstream file(heightmapPath, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Failed to open heightmap file\n";
        return;
    }

    std::streamsize fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    m_heightmap.resize(fileSize);
    if (!file.read(reinterpret_cast<char*>(m_heightmap.data()), fileSize)) {
        std::cerr << "Failed to read heightmap file\n";
        return;
    }

    // Create vertex buffer
    std::vector<float> vertices;
    for (int z = 0; z < size; z++) {
        for (int x = 0; x < size; x++) {
            float y = m_heightmap[z * size + x] / 256.0f * maxHeight;
            vertices.push_back((float)x / size);
            vertices.push_back(y);
            vertices.push_back((float)z / size);
        }
      

    }
    glGenVertexArrays(2, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(2, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    system("Color 0e");
    std::cout << "Vertices are (" << vertices.size() <<
        ")  while (" <<
        vertices.size() / 3 << ") Triangles are created" << "   ";
}
/* openAI render method that I asked to write for me 
void HeightmapTerrain::render() {
    // Bind vertex array and buffer objects
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    // Enable vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // Draw the terrain as triangles
    glDrawArrays(GL_TRIANGLES, 0, m_size * m_size * 6);

    // Disable vertex attributes
    glDisableVertexAttribArray(0);

    // Unbind vertex array and buffer objects
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}



*/

/*
original stuff render 
void HeightmapTerrain::render() {
    // Bind vertex array and buffer objects
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    // Enable vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // Draw the terrain as triangles
    glDrawArrays(GL_TRIANGLES, 0, m_size * m_size * 6);

    // Disable vertex attributes
    glDisableVertexAttribArray(0);

    // Unbind vertex array and buffer objects
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


*/

void HeightmapTerrain::render() {
    // Bind vertex array and buffer objects
    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

    // Enable vertex attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // Draw the terrain as triangles
    glDrawArrays(GL_TRIANGLES, 0, m_size * m_size * 6);

    // Disable vertex attributes
    glDisableVertexAttribArray(0);

    // Unbind vertex array and buffer objects
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

