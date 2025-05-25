#pragma once 
#include<Book/Utility.hpp>
#include<Book/Entity.hpp>
#include<Book/TileMap.hpp>
class World : public sf::Drawable
{
protected:
    std::vector<Entity*> entities ;  
    std::vector<Entity*> objects ; 
public : 
    World();
    World(const World& other); // Copy constructor
    ~World();
    TileMap map ; 
    
    bool loadFromFile(const std::string& jsonFile);
    void setLayerVisible(size_t layerIndex, bool visible);
    bool isLayerVisible(size_t layerIndex) const;

    virtual bool handleEvent(const sf::Event& event) ;
    virtual bool update(sf::Time dt) ;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

}; 