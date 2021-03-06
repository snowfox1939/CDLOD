#include "FlatMesh.h"

#include <glm/glm.hpp>
#include "utils/glError.hpp"

#include <iostream>
#include <vector>

FlatMesh::FlatMesh(int width, int height)
{
    glCheckError(__FILE__,__LINE__);
    ////////////////////////////
    //
    // creation of the mesh
    //
    ////////////////////////////
    std::vector<glm::vec3> vertices;
    std::vector<GLuint> index;


    for(int y = 0; y<=height; ++y)
    for(int x = 0; x<=width; ++x)
    {
        float xx = (x-width/2);
        float yy = (y-height/2);
        xx = x;
        yy = y;
        vertices.push_back(glm::vec3(xx/width,0.0,yy/height));
    }

    for(int y = 0; y<height; ++y)
    for(int x = 0; x<width; ++x)
    {
        index.push_back((x+0) + (width+1)*(y+0));
        index.push_back((x+1) + (width+1)*(y+0));
        index.push_back((x+1) + (width+1)*(y+1));

        index.push_back((x+1) + (width+1)*(y+1));
        index.push_back((x+0) + (width+1)*(y+1));
        index.push_back((x+0) + (width+1)*(y+0));
    }

    pointCount = index.size();
    ////////////////////////////
    //
    // creation of the vertex array buffer
    //
    ////////////////////////////

    // vbo
    glGenBuffers( 1, &vbo );
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // ibo
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(GLuint), index.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // vao
    glGenVertexArrays( 1, &vao);
    glBindVertexArray(0);
}


FlatMesh::~FlatMesh()
{
    //delete buffers!
    glDeleteBuffers(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);

}

void FlatMesh::bind() {
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

int FlatMesh::getPointCount() {
    return pointCount;
}
