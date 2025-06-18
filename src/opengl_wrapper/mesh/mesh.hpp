#pragma once

#include <vector>
#include <glad/glad.h>

class Mesh {
public:
    Mesh(
        const std::vector<GLfloat>& vertices,
        const std::vector<GLuint>& indices,

        // e.g., position (vec3), texcoord (vec2) => attribute_sizes = {3, 2}
        const std::vector<GLsizei>& attribute_sizes
    );

    ~Mesh();

    /*
        Just making sure that these functions
        does not touch the member variables
    */
    void bind() const;
    void unbind() const;
    void draw() const;

private:
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;

    GLsizei m_index_count;
};