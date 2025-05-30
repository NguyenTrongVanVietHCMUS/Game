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
        // This function should be overridden in derived classes
        throw std::runtime_error("Draw function not implemented for this layer type.");
    }
    std::string name ; 
    Type type;
    bool visible;
    // Position of the layer
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
        if (visible) 
        {
            // assert(ObjectsTextures.size() == ObjectsSprite.size() && ObjectsTextures.size() ==2 ); // Ensure we have at most 2 textures and sprites
            for(auto & collider : colliders) 
            {
                // std::cout<< "Drawing collider at position: " << collider->hitbox.left << ", " << collider->hitbox.top << std::endl;
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
                // std::cout<< "Drawing hitbox at position: " << hitbox->hitbox.left << ", " << hitbox->hitbox.top << std::endl;
                sf::RectangleShape shape(sf::Vector2f(hitbox->hitbox.width, hitbox->hitbox.height));
                shape.setPosition(hitbox->hitbox.left, hitbox->hitbox.top);
                shape.setFillColor(sf::Color(0, 255, 0, 128)); // semi-transparent green for visibility
                target.draw(shape, states); // Draw the hitbox
            }
        }
    }
};
class TileMap : public sf::Drawable {
private:

std::vector<Tileset> tilesets;
public:
    std::string File;
    std::vector<Layer*> layers;
    TileMap();
    TileMap(const TileMap& map) ;
    ~TileMap() ; 
    bool loadFromFile(const std::string& jsonFile);
    
    void setLayerVisible(size_t layerIndex, bool visible);
    bool isLayerVisible(size_t layerIndex) const;

    bool handleEvent(const sf::Event& event) ;
    bool update(sf::Time dt) ;
    void draw(sf::RenderTarget& target, sf::RenderStates states)const;
};
