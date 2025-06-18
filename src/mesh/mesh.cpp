#include <iostream>
#include "mesh.hpp"

Mesh::Mesh(
    const std::vector<GLfloat>& vertices,
    const std::vector<GLuint>& indices,
    const std::vector<GLsizei>& attribute_sizes)
    : m_index_count(static_cast<GLsizei>(indices.size())) {
    
    GLsizei vertex_size = 0;

    for (auto size : attribute_sizes)
    {
        vertex_size += size;
    }

    glGenVertexArrays(1, &m_vao);

    if (m_vao == 0)
    {
        std::cerr << "Failed to generate VAO!" << "\n";
    }

    glGenBuffers(1, &m_vbo);

    if (m_vbo == 0)
    {
        std::cerr << "Failed to generate VBO!" << "\n";
    }

    glGenBuffers(1, &m_ebo);

    if (m_ebo == 0)
    {
        std::cerr << "Failed to generate EBO!" << "\n";
    }

    glBindVertexArray(m_vao);

    // VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);

    // EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    // Attributes
    GLsizei offset = 0;
    GLsizei stride = vertex_size * sizeof(GLfloat);

    for (GLuint i = 0; i < attribute_sizes.size(); i++)
    {
        glEnableVertexAttribArray(i);

        glVertexAttribPointer(
            i,                                  // Index of the attribute
            attribute_sizes[i],                 // Size
            GL_FLOAT,                           // Type
            GL_FALSE,                           // Normalized
            stride,                             // Stride
            (void*)(offset * sizeof(GLfloat))   // Offset to the start
        );

        offset += attribute_sizes[i];
    }

    glBindVertexArray(0);
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
    glDeleteVertexArrays(1, &m_vao);
}

void Mesh::bind() const {
    glBindVertexArray(m_vao);
}

void Mesh::unbind() const {
    glBindVertexArray(0);
}

void Mesh::draw() const {
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}