#pragma once
#include "Book/Utility.hpp"
#include<Control/Hitbox.hpp>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

class Layer:public sf::Drawable 
{
public:
    enum Type {
        TileLayer,
        ImageLayer,
        ObjectGroup
    };
    static std::string toString(Type type) {
        switch (type) {
            case TileLayer: return "tilelayer";
            case ImageLayer: return "imagelayer";
            case ObjectGroup: return "objectgroup";
            default: return "unknown";
        }
    }
    Layer(): type(TileLayer), visible(true) {}
    virtual ~Layer(){}
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const
    {
        throw std::runtime_error("Draw function not implemented for this layer type.");
    }
    std::string name ; 
    Type type;
    bool visible;
}; 
struct Tileset {
    std::string File ; 
    sf::Texture texture;
    int firstGid;
    int tileWidth;
    int tileHeight;
    int columns;
    int tileCount;
};
class TileLayer: public Layer  
{
public:
    TileLayer()
    {
        visible = true ; 
    }
    ~TileLayer()
    {

    }
    virtual void setPosition(float x, float y) {
        position = sf::Vector2f(x, y);
    }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const override
    {
        if (visible) 
        {
            for(size_t i=0;i<vertices.size();i++)
            {
                states.texture = &tilesets[i].texture; // Set the texture for the current tileset
                target.draw(vertices[i], states);    
            }
        }
    }
    std::vector<int> data;
    std::vector<sf::VertexArray> vertices;
    std::vector<Tileset>tilesets;
    sf::Vector2f position;
    int width;
    int height;
}; 
class ImageLayer : public Layer 
{
public:
    ImageLayer()
    {
        visible = true ; 
    }
    ~ImageLayer() {
    }
    virtual void setPosition(float x, float y) {
        position = sf::Vector2f(x, y);
        sprite.setPosition(x, y);
    }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const override
    {
        if(visible)
        {
            states.texture = &texture ; 
            target.draw(sprite, states) ; 
        }
    }
    std::string File;
    sf::Texture texture;
    sf::Vector2f position;
    sf::Sprite sprite;
};

class ObjectLayer : public Layer
{
public:
    ObjectLayer(){

    }
    ~ObjectLayer(){
        for(auto &texture : ObjectsTextures) {
            delete texture; // Free the texture memory
        }
        for(auto &sprite : ObjectsSprite) {
            delete sprite; // Free the sprite memory
        }
        for(auto &collider : colliders) {
            delete collider; // Free the collider memory
        }
    } 
    virtual void setPosition(float x, float y) {
        position = sf::Vector2f(x, y);
    }
    std::vector<Hitbox*>colliders ; 
    std::vector<sf::Texture*>ObjectsTextures; // Textures of objects in the layer
    std::vector<sf::Sprite*>ObjectsSprite; // Sprites of objects in the layer
    std::vector<Hitbox*> hitboxes ;
    sf::Vector2f position;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const override
    {
        // if (visible) 
        {
            for(auto & collider : colliders) 
            {
                sf::RectangleShape shape(sf::Vector2f(collider->hitbox.width, collider->hitbox.height));
                shape.setPosition(collider->hitbox.left, collider->hitbox.top);
                shape.setFillColor(sf::Color(255, 0, 0, 128)); // semi-transparent red for visibility
                target.draw(shape, states); // Draw the collider
            }
            for(size_t i = 0; i < ObjectsSprite.size(); ++i) 
            {
                states.texture = ObjectsTextures[i];
                target.draw(*ObjectsSprite[i], states); // Draw the object sprite
            }
            for(auto & hitbox : hitboxes) 
            {
                sf::RectangleShape shape(sf::Vector2f(hitbox->hitbox.width, hitbox->hitbox.height));
                shape.setPosition(hitbox->hitbox.left, hitbox->hitbox.top); 
                shape.setFillColor(sf::Color(0, 255, 0, 128)); // semi-transparent green for visibility
                target.draw(shape, states); // Draw the hitbox
            }
        }
    }
};

class TileMap : public sf::Drawable 
{        
private:
    std::vector<std::vector<Tileset>> tilesets;
public:
    TileMap();
    ~TileMap() ; 
    
    sf::Vector2f startingPoint; 
    std::string File;
    std::vector<Layer*> layers;
    
    bool loadFromFile(const std::string& jsonFile);
    bool load(const std::string& jsonFile, int x, int y);
    bool handleEvent(const sf::Event& event) ;
    bool update(sf::Time dt) ;
    void draw(sf::RenderTarget& target, sf::RenderStates states)const;
};
