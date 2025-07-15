#pragma once
#include "Book/Utility.hpp"
#include<Control/Hitbox.hpp>
#include <nlohmann/json.hpp>
#include <Book/Entity.hpp>
#include <Book/Object.hpp>
#include<set>
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
    Hitbox area;// Area of the layer, if applicable

}; 
struct Tileset {
    std::string type = "Object";
    std::string File ; 
    sf::Texture texture;
    int firstGid;
    int tileWidth;
    int tileHeight;
    int columns;
    int tileCount;  
    Hitbox hitbox; 
    Tileset() = default;
};
class TileLayer: public Layer  
{
public:
    TileLayer()
    {
		type = Layer::TileLayer; // Set the type of the layer
		name = "Tile Layer"; // Default name for the layer
        width = height = 0; 
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
    ObjectLayer()
    {

    }
    ~ObjectLayer()
    {

    } 
    virtual void setPosition(float x, float y) {
        position = sf::Vector2f(x, y);
    }
    std::vector<Entity*> entities; 
    sf::Vector2f position;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const override
    {
        // do nothing becauase having entities already ; 
    }
};

class TileMap : public sf::Drawable 
{       
private:
    void updateQueueEntities();    

private:
    std::vector<std::vector<Tileset>> tilesets;
    bool load(const std::string& jsonFile, int x, int y, int height, int width); 
    bool isCollide(Entity* entity1, Entity* entity2) const {
        return entity1->getHitbox().hitbox.intersects(entity2->getHitbox().hitbox);
	}
    void handleCollision(); 
private: 
    std::string File;
    std::vector<Layer*> layers;  
public:

    TileMap();
    ~TileMap();     
    std::vector<Entity*> PushQueueEntities; // Queue for entities to be pushed
    std::vector<Entity*> PopQueueEntities; // Queue for entities to be popped

    std::vector<Entity*> entities; 
    sf::Vector2f startingPoint; 
    bool loadFromFile(const std::string& jsonFile); 
    bool handleEvent(const sf::Event& event, sf::RenderWindow* window);
    bool update(const sf::Time& dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states)const; 
};
