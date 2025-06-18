#pragma once

#include <string_view>
#include <glad/glad.h>

struct Texture2DConfig {
    GLenum wrap_s           = GL_REPEAT;
    GLenum wrap_t           = GL_REPEAT;
    GLenum min_filter       = GL_LINEAR_MIPMAP_LINEAR;
    GLenum mag_filter       = GL_LINEAR;
    bool flip_vertically    = true;
};

class Texture2D {
public:
    Texture2D();
    ~Texture2D();

    bool load_from_file(
        std::string_view image_path,
        const Texture2DConfig& texture_config = Texture2DConfig()
    );

    void bind(GLuint unit = 0) const;
    void unbind() const;

    int width() const;
    int height() const;
    GLuint id() const;

public:
    GLuint  m_texture_id;
    int     m_texture_width;
    int     m_texture_height;
};