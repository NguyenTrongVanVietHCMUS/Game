#pragma once 

#include<Book/Entity.hpp>
class Object : public Entity
{
public:
    sf::Texture* texture = new sf::Texture();
    sf::Sprite* sprite = new sf::Sprite();
    Object(std::string name, std::string File, sf::Vector2f position, Hitbox hitbox, float scalex, float scaley) :Entity(name, position, hitbox)
    {
		type = Entity::Type::Object; // Set the type of the entity
        texture = new sf::Texture();
        if (!texture->loadFromFile(File))
        {
            throw std::runtime_error("Failed to load texture from file: " + File);
        }
        sprite->setTexture(*texture);
        sprite->setPosition(position);
        sprite->scale(scalex, scaley); // Scale the sprite based on the provided parameters
    }
    void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.texture = texture;
        target.draw(*sprite, states);
		Entity::draw(target, states); // Call the base class draw method to draw the hitbox 
    }
    ~Object()
    {
        delete texture;
        delete sprite;
    }
};