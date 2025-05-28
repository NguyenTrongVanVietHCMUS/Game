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
    ObjectLayer() {}
    ~ObjectLayer() {}
    std::vector<Hitbox> hitboxes;
};

class TileMap : public sf::Drawable {
private:

    std::vector<Layer*> layers;
    std::vector<Tileset> tilesets;
public:
    std::string File;
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
