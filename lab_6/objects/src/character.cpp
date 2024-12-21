#include <character.h>
#include <filesystem>
character::character()
{
    speed = 400;

    m_texture.loadFromFile("/mnt/a/mai_stuff/Computer_grafics/lab_6/pictures/rabotyaga.png");
    m_sprite.setTexture(m_texture);

    m_position.x = 500;
    m_position.y = 800;
}

sf::Sprite character::get_sprite()
{
    return m_sprite;
}

void character::move_left()
{
    a_pressed = true;
}

void character::move_right()
{
    d_pressed = true;
}

void character::jump()
{
    w_pressed = true;
}

void character::bend_down()
{
    s_pressed = true;
}



void character::stop_left()
{
    a_pressed = false;
}

void character::stop_right()
{
    d_pressed = false;
}

void character::stop_jump()
{
    w_pressed = false;
}

void character::stop_down()
{
    s_pressed = false;
}
void character::update_position(float elapsed_time)
{
    if(d_pressed)
        m_position.x += speed * elapsed_time;

    if(a_pressed)
        m_position.x -= speed * elapsed_time;

    if(w_pressed)
        m_position.y -= speed * elapsed_time;

    if(s_pressed)
        m_position.y += speed * elapsed_time;

    m_sprite.setPosition(m_position);
}