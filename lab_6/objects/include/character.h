#ifndef LAB_6_CHARACTER_H
#define LAB_6_CHARACTER_H
#include <SFML/Graphics.hpp>

class character
{
private:
    sf::Vector2f m_position;

    sf::Sprite m_sprite;

    sf::Texture m_texture;

    bool w_pressed = false;
    bool a_pressed = false;
    bool s_pressed = false;
    bool d_pressed = false;

    float speed;
public:
    character();

    sf::Sprite get_sprite();

    void move_left();
    void move_right();
    void stop_left();
    void stop_right();

    void jump();
    void bend_down();
    void stop_jump();
    void stop_down();

    void update_position(float elapsed_time);
};
#endif //LAB_6_CHARACTER_H
