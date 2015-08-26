#include <Sprite.hpp>

#include <zeno/Graphics.hpp>
#include <zeno/Graphics/ShaderManager.hpp>

#include <GL/glew.h>

#include <iostream>

Sprite::Sprite(void) :
m_Texture(nullptr),
m_Colour(zeno::Colour::White),
m_AnimationFrame(0)
{
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);

    //~ Positions
    glGenBuffers(1, &m_PositionVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_PositionVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 3, nullptr, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, zenoGLEWDefinitions::FLOATS_IN_POSITION, GL_FLOAT, GL_FALSE, 0, nullptr);

    //~ Colours
    glGenBuffers(1, &m_ColourVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_ColourVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_STATIC_DRAW);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, zenoGLEWDefinitions::FLOATS_IN_COLOUR, GL_FLOAT, GL_FALSE, 0, nullptr);

    //~ Texture Coordinates
    glGenBuffers(1, &m_TexCoordVBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_TexCoordVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 2, nullptr, GL_STATIC_DRAW);

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, zenoGLEWDefinitions::FLOATS_IN_TEXTURE, GL_FLOAT, GL_FALSE, 0, nullptr);

    updatePosition();
    updateColours();
}
Sprite::~Sprite(void)
{
    glDeleteVertexArrays(1, &m_VAO);

    glDeleteBuffers(1, &m_PositionVBO);
    glDeleteBuffers(1, &m_ColourVBO);
    glDeleteBuffers(1, &m_TexCoordVBO);
}


void Sprite::setTexture(zeno::Texture *_texture)
{
    m_Texture = _texture;
}

void Sprite::addTextureRect(const zeno::FloatRect& _rect)
{
    m_AnimationRects.push_back(_rect);
}

void Sprite::render(const zeno::Mat4x4& _transform) const
{
    zeno::ShaderManager::getInstance().getShader("Sprite").bind();
    zeno::ShaderManager::getInstance().getShader("Sprite").passUniform("View", _transform);

    m_Texture->bind();
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    m_Texture->unbind();

    zeno::ShaderManager::getInstance().getShader("Sprite").unbind();
}

void Sprite::setAnimationFrame(unsigned int _index)
{
    m_AnimationFrame = _index;

    updatePosition();
    updateTextureCoords();
}

void Sprite::setColour(const zeno::Colour& _colour)
{
    m_Colour = _colour;

    updateColours();
}


void Sprite::updatePosition(void)
{
    zeno::FloatRect coords;

    if (m_AnimationRects.size() > 0)
    {
        coords = m_AnimationRects.at(m_AnimationFrame);
    }

    std::vector<float> pos = {
            0.0f,             0.0f,              0.0f,
            coords.width,     0.0f,              0.0f,
            coords.width,     coords.height,     0.0f,

            0.0f,             0.0f,              0.0f,
            coords.width,     coords.height,     0.0f,
            0.0f,             coords.height,     0.0f,
    };

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_PositionVBO);

    glBufferSubData(GL_ARRAY_BUFFER, 0, pos.size() * sizeof(float), pos.data());
}
void Sprite::updateColours(void)
{
    std::vector<float> col = {
            m_Colour.r, m_Colour.g, m_Colour.b, m_Colour.a,
            m_Colour.r, m_Colour.g, m_Colour.b, m_Colour.a,
            m_Colour.r, m_Colour.g, m_Colour.b, m_Colour.a,

            m_Colour.r, m_Colour.g, m_Colour.b, m_Colour.a,
            m_Colour.r, m_Colour.g, m_Colour.b, m_Colour.a,
            m_Colour.r, m_Colour.g, m_Colour.b, m_Colour.a
    };

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_ColourVBO);

    glBufferSubData(GL_ARRAY_BUFFER, 0, col.size() * sizeof(float), col.data());
}
void Sprite::updateTextureCoords(void)
{
    zeno::FloatRect coords;

    if (m_AnimationRects.size() > 0)
    {
        coords = m_AnimationRects.at(m_AnimationFrame);
    }

    zeno::Vector2f texSize(static_cast<float>(m_Texture->getSize().x), static_cast<float>(m_Texture->getSize().y));

    if (m_AnimationRects.size() > 0)
    {
        m_AnimationRects.at(m_AnimationFrame);
    }

    std::vector<float> tex = {
            (coords.left) / texSize.x,                    (coords.bot) / texSize.y,
            (coords.left + coords.width) / texSize.x,     (coords.bot) / texSize.y,
            (coords.left + coords.width) / texSize.x,     (coords.bot + coords.height) / texSize.y,

            (coords.left) / texSize.x,                    (coords.bot) / texSize.y,
            (coords.left + coords.width) / texSize.x,     (coords.bot + coords.height) / texSize.y,
            (coords.left) / texSize.x,                    (coords.bot + coords.height) / texSize.y
    };

    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_TexCoordVBO);

    glBufferSubData(GL_ARRAY_BUFFER, 0, tex.size() * sizeof(float), tex.data());
}