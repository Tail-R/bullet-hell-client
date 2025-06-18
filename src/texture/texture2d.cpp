#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "texture2d.hpp"

Texture2D::Texture2D()
    : m_texture_id(0)
    , m_texture_width(0)
    , m_texture_height(0)
{
    glGenTextures(1, &m_texture_id);
}

Texture2D::~Texture2D() {
    if (m_texture_id != 0)
    {
        glDeleteTextures(1, &m_texture_id);
    }
}

bool Texture2D::load_from_file(
    std::string_view image_path,
    const Texture2DConfig& texture_config
) {

    if (m_texture_id == 0)
    {
        std::cerr << "Texture ID not set" << "\n";

        return false;
    }

    stbi_set_flip_vertically_on_load(texture_config.flip_vertically);

    int channels = 0;
    unsigned char* image_data = nullptr;
    
    // Load texture
    image_data = stbi_load(
        image_path.data(),
        &m_texture_width,
        &m_texture_height,
        &channels,
        0   // Desired channels
    );

    if (image_data == nullptr)
    {
        std::cerr << "Failed to load texture: " << image_path << "\n";
        std::cerr << "stb_image error: " << stbi_failure_reason() << "\n";

        return false;
    }

    GLenum format = (channels == 4) ? GL_RGBA :
                    (channels == 3) ? GL_RGB :
                    (channels == 2) ? GL_RG : GL_RED;

    GLint internal_format = (channels == 4) ? GL_RGBA8 :
                            (channels == 3) ? GL_RGB8 :
                            (channels == 2) ? GL_RG8 : GL_R8;

    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    // Create texture
    glTexImage2D(
        GL_TEXTURE_2D,      // Target e.g. GL_TEXTURE_2D
        0,                  // Mipmap level, usually 0
        internal_format,    // How GPU stores the texture
        m_texture_width,
        m_texture_height,
        0,                  // Border, it must be 0 in modern OpenGL
        format,             // format of the source image data
        GL_UNSIGNED_BYTE,   // Type of each component, e.g. GL_UNSIGNED_BYTE
        image_data          // Pointer to the image data 
    );

    glGenerateMipmap(GL_TEXTURE_2D);

    // Apply user-specified texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, texture_config.wrap_s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, texture_config.wrap_t);    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, texture_config.min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, texture_config.mag_filter);
    
    unbind();

    stbi_image_free(image_data);

    return true;
}

void Texture2D::bind(GLuint unit) const {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
}

void Texture2D::unbind() const {
    glBindTexture(GL_TEXTURE_2D, 0);
}

int Texture2D::width() const {
    return static_cast<int>(m_texture_width);
}

int Texture2D::height() const {
    return static_cast<int>(m_texture_height);
}

GLuint Texture2D::id() const {
    return m_texture_id;
}