#ifndef DELUGE_SPRITE_HPP
#define DELUGE_SPRITE_HPP

#include <string>
#include <vector>

#include <zeno/System/Rect.hpp>
#include <zeno/System/Mat4x4.hpp>
#include <zeno/System/Transformable2D.hpp>
#include <zeno/Graphics/Colour.hpp>
#include <zeno/Graphics/Texture.hpp>

class Sprite : public zeno::Transformable2D
{
public:
    Sprite(void);
    ~Sprite(void);

    void setTexture(zeno::Texture *_texture);

    void addTextureRect(const zeno::FloatRect& _rect);

    void render(const zeno::Mat4x4& _transform) const;

    void setAnimationFrame(unsigned int _index);

    void setColour(const zeno::Colour& _colour);

private:
    void updatePosition(void);
    void updateColours(void);
    void updateTextureCoords(void);

private:
    unsigned int m_VAO;

    unsigned int m_PositionVBO;
    unsigned int m_ColourVBO;
    unsigned int m_TexCoordVBO;

    zeno::Texture *m_Texture;

    zeno::Colour m_Colour;

    std::vector<zeno::FloatRect> m_AnimationRects;

    unsigned int m_AnimationFrame;
};

#endif //~ DELUGE_SPRITE_HPP
